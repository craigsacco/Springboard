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

#include <Springboard/InternalHAL/Watchdog.hpp>

namespace Springboard {
namespace InternalHAL {

Watchdog::Watchdog(Driver* driver, const char* name, Priority priority)
    : Thread(name, SPRINGBOARD_HAL_WDG_THREAD_SIZE, priority),
      mDriver(driver), mConfig(), mMutex()
{
    // by default, make the timeout huge (in this case, 32.768 seconds)
    mConfig.pr = 7;
    mConfig.rlr = 0xFFF;
}

bool Watchdog::SetTimeout(uint32_t microseconds)
{
    uint32_t pr = 0;
    uint32_t maximum = ((1000000UL << 2UL) / STM32_LSICLK) * 4096UL;
    while (pr < 6) {
        if (microseconds < maximum) {
            mConfig.pr = pr;
            mConfig.rlr = (microseconds / (maximum / 4096));
            if (mConfig.rlr > 0) {
                mConfig.rlr--;
            }
            mMutex.Lock();
            if (mDriver->state == WDG_READY) {
                wdgStart(mDriver, &mConfig);
            }
            mMutex.Unlock();
            return true;
        } else {
            pr++;
            maximum <<= 1UL;
        }
    }

    return false;
}

void Watchdog::Run()
{
    // freeze the peripheral when in debug (or else it will reboot)
    DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_IWDG_STOP;

    mMutex.Lock();
    wdgStart(mDriver, &mConfig);
    mMutex.Unlock();

    while (true) {
        Sleep_ms(SPRINGBOARD_HAL_WDG_PAT_INTERVAL_MS);

        mMutex.Lock();
        wdgReset(mDriver);
        mMutex.Unlock();
    }

    ASSERT_FAIL_MSG("Watchdog thread should not be stopped");
}

}  // namespace InternalHAL
}  // namespace Springboard
