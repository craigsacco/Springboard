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

#include <hal.h>
#include <sbconf.h>
#include <Springboard/Common.h>
#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/InternalHAL/I2CBus.hpp>
#include <Springboard/InternalHAL/UARTBus.hpp>
#include <Springboard/InternalHAL/RealTimeClock.hpp>

#if SPRINGBOARD_HAL_USE_I2C1
#if !defined(SPRINGBOARD_HAL_I2C1_THREAD_PRIORITY)
#error "SPRINGBOARD_HAL_I2C1_THREAD_PRIORITY must be defined when" \
    "SPRINGBOARD_HAL_USE_I2C1 is set"
#endif
#if !defined(SPRINGBOARD_HAL_I2C1_XACTION_DEPTH)
#error "SPRINGBOARD_HAL_I2C1_XACTION_DEPTH must be defined when" \
    "SPRINGBOARD_HAL_USE_I2C1 is set"
#endif
#endif

#if SPRINGBOARD_HAL_USE_I2C2
#if !defined(SPRINGBOARD_HAL_I2C2_THREAD_PRIORITY)
#error "SPRINGBOARD_HAL_I2C2_THREAD_PRIORITY must be defined when" \
    "SPRINGBOARD_HAL_USE_I2C2 is set"
#endif
#if !defined(SPRINGBOARD_HAL_I2C2_XACTION_DEPTH)
#error "SPRINGBOARD_HAL_I2C2_XACTION_DEPTH must be defined when" \
    "SPRINGBOARD_HAL_USE_I2C2 is set"
#endif
#endif

#if SPRINGBOARD_HAL_USE_I2C3
#if !defined(SPRINGBOARD_HAL_I2C3_THREAD_PRIORITY)
#error "SPRINGBOARD_HAL_I2C3_THREAD_PRIORITY must be defined when" \
    "SPRINGBOARD_HAL_USE_I2C3 is set"
#endif
#if !defined(SPRINGBOARD_HAL_I2C3_XACTION_DEPTH)
#error "SPRINGBOARD_HAL_I2C3_XACTION_DEPTH must be defined when" \
    "SPRINGBOARD_HAL_USE_I2C3 is set"
#endif
#endif

#define SPRINGBOARD_HAL_I2C_COUNT           3
#define SPRINGBOARD_HAL_UART_COUNT          8
#define SPRINGBOARD_HAL_RTC_COUNT           1

namespace Springboard {
namespace InternalHAL {

#if !SPRINGBOARD_HAL_ENABLE_I2C
class I2CBus;
#endif

#if !SPRINGBOARD_HAL_ENABLE_UART
class UARTBus;
#endif

class PeripheralFactory
{
public:
    PeripheralFactory();

    void Start();
    I2CBus* GetI2CBus(size_t index) const;
    UARTBus* GetUARTBus(size_t index) const;
    RealTimeClock* GetRTC(size_t index) const;

private:
#if SPRINGBOARD_HAL_ENABLE_I2C
#define SPRINGBOARD_HAL_PF_I2C_DECL(n)                              \
    I2CBus mI2C##n##Bus                                             \
        { &I2CD##n, I2CMode::I2C, "I2C" #n "Bus",                   \
          SPRINGBOARD_HAL_I2C##n##_THREAD_PRIORITY,                 \
          SPRINGBOARD_HAL_I2C##n##_XACTION_DEPTH }
#if SPRINGBOARD_HAL_USE_I2C1
    SPRINGBOARD_HAL_PF_I2C_DECL(1);
#endif
#if SPRINGBOARD_HAL_USE_I2C2
    SPRINGBOARD_HAL_PF_I2C_DECL(2);
#endif
#if SPRINGBOARD_HAL_USE_I2C3
    SPRINGBOARD_HAL_PF_I2C_DECL(3);
#endif
    I2CBus* mI2CBuses[SPRINGBOARD_HAL_I2C_COUNT] = {
#if SPRINGBOARD_HAL_USE_I2C1
        &mI2C1Bus,
#else
        nullptr,
#endif
#if SPRINGBOARD_HAL_USE_I2C2
        &mI2C2Bus,
#else
        nullptr,
#endif
#if SPRINGBOARD_HAL_USE_I2C3
        &mI2C3Bus,
#else
        nullptr,
#endif
    };
#endif  // SPRINGBOARD_HAL_ENABLE_I2C

#if SPRINGBOARD_HAL_ENABLE_UART
#define SPRINGBOARD_HAL_PF_UART_DECL(n) UARTBus mUART##n##Bus { &SD##n }
#if SPRINGBOARD_HAL_USE_UART1
    SPRINGBOARD_HAL_PF_UART_DECL(1);
#endif
#if SPRINGBOARD_HAL_USE_UART2
    SPRINGBOARD_HAL_PF_UART_DECL(2);
#endif
#if SPRINGBOARD_HAL_USE_UART3
    SPRINGBOARD_HAL_PF_UART_DECL(3);
#endif
#if SPRINGBOARD_HAL_USE_UART4
    SPRINGBOARD_HAL_PF_UART_DECL(4);
#endif
#if SPRINGBOARD_HAL_USE_UART5
    SPRINGBOARD_HAL_PF_UART_DECL(5);
#endif
#if SPRINGBOARD_HAL_USE_UART6
    SPRINGBOARD_HAL_PF_UART_DECL(6);
#endif
#if SPRINGBOARD_HAL_USE_UART7
    SPRINGBOARD_HAL_PF_UART_DECL(7);
#endif
#if SPRINGBOARD_HAL_USE_UART8
    SPRINGBOARD_HAL_PF_UART_DECL(8);
#endif
    UARTBus* mUARTBuses[SPRINGBOARD_HAL_UART_COUNT] = {
#if SPRINGBOARD_HAL_USE_UART1
        &mUART1Bus,
#else
        nullptr,
#endif
#if SPRINGBOARD_HAL_USE_UART2
        &mUART2Bus,
#else
        nullptr,
#endif
#if SPRINGBOARD_HAL_USE_UART3
        &mUART3Bus,
#else
        nullptr,
#endif
#if SPRINGBOARD_HAL_USE_UART4
        &mUART4Bus,
#else
        nullptr,
#endif
#if SPRINGBOARD_HAL_USE_UART5
        &mUART5Bus,
#else
        nullptr,
#endif
#if SPRINGBOARD_HAL_USE_UART6
        &mUART6Bus,
#else
        nullptr,
#endif
#if SPRINGBOARD_HAL_USE_UART7
        &mUART7Bus,
#else
        nullptr,
#endif
#if SPRINGBOARD_HAL_USE_UART8
        &mUART8Bus,
#else
        nullptr,
#endif
    };
#endif  // SPRINGBOARD_HAL_ENABLE_UART

    RealTimeClock mRTC1 { &RTCD1 };
    RealTimeClock* mRTCs[SPRINGBOARD_HAL_RTC_COUNT] = { &mRTC1 };
};

}  // namespace InternalHAL
}  // namespace Springboard
