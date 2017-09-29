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
    size_t length = 0;
    bool verify = false;
    uint8_t actualChecksum = 0;
    uint8_t expectedChecksum = 0;
    size_t expectedChecksumLength = 0;
    MessageState state = MessageState::Idle;

    while (!ShouldTerminate()) {
        bool ok = true;
        bool message = false;
        uint8_t b = mBus->Read();

        if (b == '$' || b == '!') {
            length = 0;
            verify = false;
            actualChecksum = 0;
            state = MessageState::GotStartDelimiter;
        } else {
            switch (state) {
            case MessageState::Idle:
            {
                ok = false;  // out-of-band character
                break;
            }
            case MessageState::GotStartDelimiter:
            case MessageState::GettingMessage:
            {
                if (b == '*') {
                    state = MessageState::GotEndDelimiter;
                    expectedChecksum = 0;
                    expectedChecksumLength = 0;
                } else if (b < 0x20 || b > 0x7e) {
                    ok = false;  // invalid character received
                } else {
                    state = MessageState::GettingMessage;
                }
                break;
            }
            case MessageState::GotEndDelimiter:
            case MessageState::GettingChecksum:
            {
                if (b == '\r') {
                    if (expectedChecksumLength == 0 ||
                        expectedChecksumLength == 2) {
                        state = MessageState::GotCR;
                    } else {
                        ok = false;  // checksum field of malformed length
                    }
                } else if ((b >= '0' && b <= '9') ||
                           (b >= 'A' && b <= 'F') ||
                           (b >= 'a' && b <= 'f')) {
                    state = MessageState::GettingChecksum;
                    verify = true;
                    expectedChecksum <<= 4;
                    if (b >= '0' && b <= '9') {
                        expectedChecksum |= b - '0';
                    } else if (b >= 'A' && b <= 'F') {
                        expectedChecksum |= ((b - 'A') + 10);
                    } else {
                        expectedChecksum |= ((b - 'a') + 10);
                    }
                    expectedChecksumLength++;
                    if (expectedChecksumLength > 2) {
                        ok = false;  // checksum field too long
                    }
                } else {
                    ok = false;  // no hex character or CR character
                }
                break;
            }
            case MessageState::GotCR:
            {
                if (b == '\n') {
                    message = true;
                } else {
                    ok = false;  // no LF character
                }
                break;
            }
            }
        }

        bool reset = false;
        if (ok) {
            if (state == MessageState::GettingMessage) {
                if (length < MAX_MESSAGE_SIZE) {
                    mMessageBuffer[length++] = b;
                    actualChecksum ^= b;
                } else {
                    reset = true;  // message too long - ignore remainder
                }
            }
            if (message) {
                if (verify && expectedChecksum == actualChecksum) {
                    ReceivedMessage(ConstCharArray::Construct(
                        reinterpret_cast<const char*>(mMessageBuffer),
                        length));
                }
                reset = true;  // done handling message
            }
        } else {
            reset = true;  // resetting due to error condition
        }

        if (reset) {
            length = 0;
            verify = false;
            state = MessageState::Idle;
        }
    }
}

}  // namespace ExternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_UART
