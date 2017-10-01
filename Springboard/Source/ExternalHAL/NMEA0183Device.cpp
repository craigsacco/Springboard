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

#include <Springboard/ExternalHAL/NMEA0183Device.hpp>
#include <Springboard/InternalHAL/UARTBus.hpp>

#if SPRINGBOARD_HAL_ENABLE_UART

using Springboard::Utilities::ConstCharArray;

namespace Springboard {
namespace ExternalHAL {

NMEA0183Device::NMEA0183Device(Springboard::InternalHAL::UARTBus* bus,
                               const char* name, Priority priority) :
    Thread(name, SPRINGBOARD_NMEA_0183_THREAD_SIZE, priority),
    mBus(bus)
{
}

void NMEA0183Device::Run()
{
    MessageState messageState = MessageState::Idle;
    size_t messageLength = 0;
    bool verifyMessage = false;
    uint8_t actualChecksum = 0;
    uint8_t expectedChecksum = 0;
    size_t expectedChecksumLength = 0;

    while (!ShouldTerminate()) {
        bool charOk = true;
        bool gotMessage = false;
        uint8_t ch = mBus->Read();

        if (ch == '$' || ch == '!') {
            messageLength = 0;
            verifyMessage = false;
            actualChecksum = 0;
            messageState = MessageState::GotStartDelimiter;
        } else {
            switch (messageState) {
            case MessageState::Idle:
            {
                charOk = false;  // out-of-band character
                break;
            }
            case MessageState::GotStartDelimiter:
            case MessageState::GettingMessage:
            {
                if (ch == '*') {
                    messageState = MessageState::GotEndDelimiter;
                    expectedChecksum = 0;
                    expectedChecksumLength = 0;
                } else if (ch < 0x20 || ch > 0x7e) {
                    charOk = false;  // invalid character received
                } else {
                    messageState = MessageState::GettingMessage;
                }
                break;
            }
            case MessageState::GotEndDelimiter:
            case MessageState::GettingChecksum:
            {
                if (ch == '\r') {
                    if (expectedChecksumLength == 0 ||
                        expectedChecksumLength == 2) {
                        messageState = MessageState::GotCR;
                    } else {
                        charOk = false;  // checksum field of malformed length
                    }
                } else if ((ch >= '0' && ch <= '9') ||
                           (ch >= 'A' && ch <= 'F') ||
                           (ch >= 'a' && ch <= 'f')) {
                    messageState = MessageState::GettingChecksum;
                    verifyMessage = true;
                    expectedChecksum <<= 4;
                    if (ch >= '0' && ch <= '9') {
                        expectedChecksum |= ch - '0';
                    } else if (ch >= 'A' && ch <= 'F') {
                        expectedChecksum |= ((ch - 'A') + 10);
                    } else {
                        expectedChecksum |= ((ch - 'a') + 10);
                    }
                    expectedChecksumLength++;
                    if (expectedChecksumLength > 2) {
                        charOk = false;  // checksum field too long
                    }
                } else {
                    charOk = false;  // no hex character or CR character
                }
                break;
            }
            case MessageState::GotCR:
            {
                if (ch == '\n') {
                    gotMessage = true;
                } else {
                    charOk = false;  // no LF character
                }
                break;
            }
            }
        }

        bool resetBuffer = false;
        if (charOk) {
            if (messageState == MessageState::GettingMessage) {
                if (messageLength < MAX_MESSAGE_SIZE) {
                    mMessageBuffer[messageLength++] = ch;
                    actualChecksum ^= ch;
                } else {
                    resetBuffer = true;  // message too long - ignore remainder
                }
            }
            if (gotMessage) {
                if (verifyMessage && expectedChecksum == actualChecksum) {
                    ReceivedMessage(ConstCharArray::Construct(
                        reinterpret_cast<const char*>(mMessageBuffer),
                        messageLength));
                }
                resetBuffer = true;  // done handling message
            }
        } else {
            resetBuffer = true;  // resetting due to error condition
        }

        if (resetBuffer) {
            messageLength = 0;
            verifyMessage = false;
            messageState = MessageState::Idle;
        }
    }
}

}  // namespace ExternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_UART
