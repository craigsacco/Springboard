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
#include <Springboard/Kernel/Mutex.hpp>

#if !defined(SPRINGBOARD_HAL_WDG_THREAD_SIZE)
#define SPRINGBOARD_HAL_WDG_THREAD_SIZE     512
#endif

#if !defined(SPRINGBOARD_HAL_WDG_PAT_INTERVAL_MS)
#define SPRINGBOARD_HAL_WDG_PAT_INTERVAL_MS 5
#endif

#if !defined(SPRINGBOARD_HAL_WDG_TIMEOUT_MS)
#define SPRINGBOARD_HAL_WDG_TIMEOUT_MS      100
#endif

namespace Springboard {
namespace InternalHAL {

class Watchdog : public Springboard::Kernel::Thread
{
public:
    typedef WDGDriver Driver;
    typedef WDGConfig Config;

    Watchdog(Driver* driver, const char* name, Priority priority);
    bool SetTimeout(uint32_t microseconds);
    void Run() final;

private:
    Driver* mDriver;
    Config mConfig;
    Springboard::Kernel::Mutex mMutex;
};

}  // namespace InternalHAL
}  // namespace Springboard
