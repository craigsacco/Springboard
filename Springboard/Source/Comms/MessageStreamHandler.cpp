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
#include <Springboard/Comms/IStream.hpp>

namespace Springboard {
namespace Comms {

MessageStreamHandler::MessageStreamHandler(
    IStream* stream, const char* name, Priority priority) :
    Thread(name, SPRINGBOARD_MSG_STREAM_HDLR_THREAD_SIZE, priority),
    mStream(stream)
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
    uint8_t b = mStream->Read();

    switch (mRxState) {
    case RxState::Idle:
    {
        if (b == SOF_BYTES[0]) {
            mRxState = RxState::GotSOFChar1;
        } else {
            byteOk = false;
        }
        break;
    }
    case RxState::GotSOFChar1:
    {
        if (b == SOF_BYTES[1]) {
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
            mRxMsgBytesRemaining = b;
        } else {
            byteOk = false;
        }
        break;
    }
    case RxState::GotSize:
    case RxState::GettingMessage:
    {
        if (mRxMsgBytesRemaining > 0) {
            mRxState = RxState::GettingMessage;
        } else {
            mRxState = RxState::GotMessage;
        }
        mRxMsgBytesRemaining--;
        break;
    }
    case RxState::GotMessage:
    {
        if (b == EOF_BYTES[0]) {
            mRxState = RxState::GotEOFChar1;
        } else {
            byteOk = false;
        }
        break;
    }
    case RxState::GotEOFChar1:
    {
        if (b == EOF_BYTES[1]) {
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
    }

    return gotMessage;
}

void MessageStreamHandler::HandleRxMessage()
{
    MessageHeader* header =
        reinterpret_cast<MessageHeader*>(&(mRxBuffer[sizeof(SOF_BYTES)]));
    switch (header->type) {
    case MessageType::GetPropertyRequest:
    {
        break;
    }
    case MessageType::SetPropertyRequest:
    {
        ConstByteArray data(
            &(header->payload.setPropertyRequest.firstByte),
            header->size - (MessageHeader::MIN_LENGTH +
                            MessageGetPropertyResponse::PREAMBLE_LENGTH));
        break;
    }
    default:
    {
        break;
    }
    }
}

void MessageStreamHandler::ResetRxBuffer()
{
    mRxPos = 0;
    mRxState = RxState::Idle;
    mRxChecksum = 0;
    mRxMsgBytesRemaining = 0;
}

}  // namespace Comms
}  // namespace Springboard
