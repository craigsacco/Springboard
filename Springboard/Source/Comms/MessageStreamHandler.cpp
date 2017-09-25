/******************************************************************************
 * MIT License
 *
 * PROJECT SPRINGBOARD
 * -------------------
 * Copyright (c) 2017 <craig.sacco@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *****************************************************************************/

#include <Springboard/Comms/MessageStreamHandler.hpp>
#include <Springboard/Infrastructure/Controller.hpp>
#include <Springboard/Comms/IStream.hpp>

namespace Springboard {
namespace Comms {

constexpr uint8_t MessageHeader::SOF_BYTES[2];
constexpr uint8_t MessageHeader::EOF_BYTES[2];

MessageStreamHandler::MessageStreamHandler(
    Springboard::Infrastructure::Controller* controller,
    IStream* stream, const char* name, Priority priority) :
    Thread(name, SPRINGBOARD_MSG_STREAM_HDLR_THREAD_SIZE, priority),
    mController(controller), mStream(stream)
{
}

void MessageStreamHandler::Run()
{
    ResetRxBuffer();

    while (!ShouldTerminate()) {
        bool gotMessage = ReceiveNextByte();
        if (gotMessage) {
            HandleRxMessage();
            ResetRxBuffer();
        }
    }
}

bool MessageStreamHandler::ReceiveNextByte()
{
    bool byteOk = true;
    bool gotMessage = false;
    volatile uint8_t b = mStream->Read();

    switch (mRxState) {
    case RxState::Idle:
    {
        if (b == MessageHeader::SOF_BYTES[0]) {
            mRxState = RxState::GotSOFChar1;
        } else {
            byteOk = false;
        }
        break;
    }
    case RxState::GotSOFChar1:
    {
        if (b == MessageHeader::SOF_BYTES[1]) {
            mRxState = RxState::GotSOFChar2;
        } else {
            byteOk = false;
        }
        break;
    }
    case RxState::GotSOFChar2:
    {
        if (b <= MAX_MSG_SIZE) {
            mRxState = RxState::GotSize;
            mRxMsgBytesRemaining = b - 1;
        } else {
            byteOk = false;
        }
        break;
    }
    case RxState::GotSize:
    case RxState::GettingMessage:
    {
        if (mRxMsgBytesRemaining == 1) {
            mRxState = RxState::GotMessage;
        } else {
            mRxState = RxState::GettingMessage;
        }
        mRxMsgBytesRemaining--;
        break;
    }
    case RxState::GotMessage:
    {
        if (b == MessageHeader::EOF_BYTES[0]) {
            mRxState = RxState::GotEOFChar1;
        } else {
            byteOk = false;
        }
        break;
    }
    case RxState::GotEOFChar1:
    {
        if (b == MessageHeader::EOF_BYTES[1]) {
            mRxState = RxState::GotEOFChar2;
        } else {
            byteOk = false;
        }
        break;
    }
    case RxState::GotEOFChar2:
    {
        if (b == mRxChecksum) {
            gotMessage = true;
        } else {
            byteOk = false;
        }
        break;
    }
    }

    if (byteOk) {
        mRxBuffer[mRxPos++] = b;
        mRxChecksum ^= b;
    } else {
        mRxPos = 0;
        mRxChecksum = 0;
        mRxState = RxState::Idle;
    }

    return gotMessage;
}

void MessageStreamHandler::HandleRxMessage()
{
    MessageHeader* rxHeader = reinterpret_cast<MessageHeader*>(&mRxBuffer[0]);
    switch (rxHeader->type) {
    case MessageType::GetPropertyRequest:
    {
        HandleRxGetPropertyRequest(rxHeader);
        break;
    }
    case MessageType::SetPropertyRequest:
    {
        HandleRxSetPropertyResponse(rxHeader);
        break;
    }
    default:
    {
        break;
    }
    }
}

void MessageStreamHandler::HandleRxGetPropertyRequest(MessageHeader* rxHeader)
{
    // size of request is unexpected
    if (rxHeader->size != MessageHeader::MIN_LENGTH +
        MessageGetPropertyRequest::LENGTH) {
        return;
    }

    // start filling in TX buffer
    MessageHeader* txHeader = reinterpret_cast<MessageHeader*>(&mTxBuffer[0]);
    memcpy(txHeader->sof, MessageHeader::SOF_BYTES,
           sizeof(MessageHeader::SOF_BYTES));
    txHeader->size = MessageHeader::MIN_LENGTH +
        MessageGetPropertyResponse::PREAMBLE_LENGTH;
    txHeader->sequence = rxHeader->sequence;
    txHeader->type = MessageType::GetPropertyResponse;
    MessageGetPropertyResponse& txResponse =
        txHeader->payload.getPropertyResponse;
    txResponse.resourceId = rxHeader->payload.getPropertyRequest.resourceId;
    txResponse.propertyId = rxHeader->payload.getPropertyRequest.propertyId;

    Resource* resource = mController->FindResource(
        rxHeader->payload.getPropertyRequest.resourceId);
    ByteArray data(&txResponse.responseData, MAX_GET_PROPERTY_RSP_DATA_SIZE);
    if (resource != nullptr) {
        uint8_t len = 0;
        txResponse.resultCode = resource->GetProperty(txResponse.propertyId,
                                                      data, &len);
        txHeader->size += len;
    } else {
        txResponse.resultCode = RC_CONTROLLER_INVALID_RESOURCE_ID;
    }

    FinaliseTxMessage();
}

void MessageStreamHandler::HandleRxSetPropertyResponse(MessageHeader* rxHeader)
{
}

void MessageStreamHandler::ResetRxBuffer()
{
    mRxPos = 0;
    mRxState = RxState::Idle;
    mRxChecksum = 0;
    mRxMsgBytesRemaining = 0;
}

void MessageStreamHandler::FinaliseTxMessage()
{
    MessageHeader* txHeader = reinterpret_cast<MessageHeader*>(&mTxBuffer[0]);
    size_t length = sizeof(MessageHeader::SOF_BYTES) + txHeader->size;
    memcpy(mTxBuffer + length, MessageHeader::EOF_BYTES,
           sizeof(MessageHeader::EOF_BYTES));
    length += sizeof(MessageHeader::EOF_BYTES);

    uint8_t checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum ^= mTxBuffer[i];
    }
    mTxBuffer[length++] = checksum;

    mStream->Write(ConstByteArray::Construct(mTxBuffer, length));
}

}  // namespace Comms
}  // namespace Springboard
