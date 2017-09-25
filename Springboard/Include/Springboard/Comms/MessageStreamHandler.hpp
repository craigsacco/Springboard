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

#pragma once

#include <Springboard/Kernel/Thread.hpp>

#if !defined(SPRINGBOARD_MSG_STREAM_HDLR_THREAD_SIZE)
#define SPRINGBOARD_MSG_STREAM_HDLR_THREAD_SIZE     2048
#endif

namespace Springboard {

namespace Infrastructure { class Controller; }

namespace Comms {

#pragma pack(1)

struct MessageGetPropertyRequest
{
    uint16_t resourceId;
    uint16_t propertyId;

    static constexpr size_t LENGTH = 4;
};

struct MessageGetPropertyResponse
{
    uint16_t resourceId;
    uint16_t propertyId;
    ResultCode resultCode;
    uint8_t responseData;

    static constexpr size_t PREAMBLE_LENGTH = 8;
    static constexpr size_t MIN_LENGTH = PREAMBLE_LENGTH + 1;
};

struct MessageSetPropertyRequest
{
    uint16_t resourceId;
    uint16_t propertyId;
    uint8_t responseData;

    static constexpr size_t PREAMBLE_LENGTH = 4;
    static constexpr size_t MIN_LENGTH = PREAMBLE_LENGTH + 1;
};

struct MessageSetPropertyResponse
{
    uint16_t resourceId;
    uint16_t propertyId;
    ResultCode resultCode;

    static constexpr size_t LENGTH = 8;
};

enum class MessageType : uint8_t
{
    GetPropertyRequest,
    GetPropertyResponse,
    SetPropertyRequest,
    SetPropertyResponse,
};

union MessagePayload
{
    MessageGetPropertyRequest getPropertyRequest;
    MessageGetPropertyResponse getPropertyResponse;
    MessageSetPropertyRequest setPropertyRequest;
    MessageSetPropertyResponse setPropertyResponse;
};

struct MessageHeader
{
    static constexpr uint8_t SOF_BYTES[2] = { 0xfd, 0x02 };
    static constexpr uint8_t EOF_BYTES[2] = { 0x03, 0xfc };

    uint8_t sof[sizeof(SOF_BYTES)];
    uint8_t size;  // excludes SOF/EOF, includes self
    uint8_t sequence;
    MessageType type;
    MessagePayload payload;

    static constexpr size_t MIN_LENGTH = 3;  // excludes SOF
};

#pragma pack()

class IStream;

class MessageStreamHandler : public Springboard::Kernel::Thread
{
public:
    MessageStreamHandler(Springboard::Infrastructure::Controller* controller,
                         IStream* stream, const char* name, Priority priority);
    void Run() final;

private:
    bool ReceiveNextByte();
    void HandleRxMessage();
    void HandleRxGetPropertyRequest(MessageHeader* header);
    void HandleRxSetPropertyResponse(MessageHeader* header);
    void ResetRxBuffer();
    void FinaliseTxMessage();
    void SendTxMessage();

    static constexpr size_t BUFFER_SIZE = 256;
    static constexpr uint8_t MAX_MSG_SIZE = BUFFER_SIZE -
        (sizeof(MessageHeader::SOF_BYTES) + sizeof(MessageHeader::EOF_BYTES) +
         1); // minus SOF/EOF/checksum
    static constexpr uint8_t MAX_GET_PROPERTY_RSP_DATA_SIZE = MAX_MSG_SIZE -
        (MessageHeader::MIN_LENGTH +
         MessageGetPropertyResponse::PREAMBLE_LENGTH);

    enum class RxState
    {
        Idle,
        GotSOFChar1,
        GotSOFChar2,
        GotSize,
        GettingMessage,
        GotMessage,
        GotEOFChar1,
        GotEOFChar2,
    };

    Springboard::Infrastructure::Controller* mController;
    IStream* mStream;
    uint8_t mRxBuffer[BUFFER_SIZE];
    uint8_t mRxPos;
    RxState mRxState;
    uint8_t mRxChecksum;
    uint8_t mRxMsgBytesRemaining;
    uint8_t mTxBuffer[BUFFER_SIZE];
};

}  // namespace Comms
}  // namespace Springboard
