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

#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/Kernel/Thread.hpp>
#include <Springboard/Utilities/ArrayReference.hpp>

#if !defined(SPRINGBOARD_NMEA_0183_THREAD_SIZE)
#define SPRINGBOARD_NMEA_0183_THREAD_SIZE   2048
#endif

#if SPRINGBOARD_HAL_ENABLE_UART

namespace Springboard {

namespace InternalHAL { class UARTBus; }

namespace ExternalHAL {

class NMEA0183Device : public Springboard::Kernel::Thread
{
public:
    NMEA0183Device(Springboard::InternalHAL::UARTBus* bus,
                   const char* name, Priority priority);
    void Run() final;

protected:
    virtual void ReceivedMessage(
        Springboard::Utilities::ConstCharArray message) = 0;

private:
    enum class MessageState : uint8_t
    {
        Idle,
        GotStartDelimiter,
        GettingMessage,
        GotEndDelimiter,
        GettingChecksum,
        GotCR,
    };

    static constexpr size_t MAX_MESSAGE_SIZE = 82;

    Springboard::InternalHAL::UARTBus* mBus;
    uint8_t mMessageBuffer[MAX_MESSAGE_SIZE];
};

}  // namespace ExternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_UART
