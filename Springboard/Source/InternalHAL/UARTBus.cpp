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

#include <Springboard/InternalHAL/UARTBus.hpp>

#if SPRINGBOARD_HAL_ENABLE_UART

namespace Springboard {
namespace InternalHAL {

UARTBus::UARTBus(Bus* bus)
    : mBus(bus), mConfig()
{
    SetConfig(9600, UARTDataBits::Eight, UARTParity::None, UARTStopBits::One);
}

void UARTBus::Start()
{
    sdStart(mBus, &mConfig);
}

void UARTBus::Stop()
{
    sdStop(mBus);
}

void UARTBus::SetConfig(Speed speed, UARTDataBits databits,
                        UARTParity parity, UARTStopBits stopbits)
{
    mConfig.speed = speed;
    mConfig.cr1 = static_cast<uint16_t>(databits) |
                  static_cast<uint16_t>(parity);
    mConfig.cr2 = static_cast<uint16_t>(stopbits);
    mConfig.cr3 = 0;

    // immediately apply new configuration if it has already started
    if (IsStarted()) {
        sdStart(mBus, &mConfig);
    }
}

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_UART
