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

namespace Springboard {
namespace InternalHAL {

#if !SPRINGBOARD_HAL_ENABLE_I2C
class I2CBus;
#endif

class PeripheralFactory
{
public:
    PeripheralFactory();

    void Start();
    I2CBus* GetI2CBus(size_t index);

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
};

}  // namespace InternalHAL
}  // namespace Springboard
