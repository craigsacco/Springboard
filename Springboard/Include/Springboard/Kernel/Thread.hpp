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

#include <ch.h>
#include <Springboard/Common.h>

namespace Springboard {
namespace Kernel {

class Thread
{
public:
    typedef tprio_t Priority;
    typedef msg_t ExitCode;

    Thread(const char* name, size_t size, Priority priority);

    inline const char* GetName() const
    {
        return mThread->name;
    }

    inline Priority GetPriority() const
    {
        return mThread->prio;
    }

    inline void SetPriority(Priority priority)
    {
        chThdSetPriority(priority);
    }

    inline void Start()
    {
        chThdStart(mThread);
    }

    inline void StartI()
    {
        chThdStartI(mThread);
    }

    inline bool IsStarted() const
    {
        return mThread->state != CH_STATE_WTSTART;
    }

    inline void Terminate()
    {
        chThdTerminate(mThread);
    }

    inline bool IsTerminated() const
    {
        return chThdTerminatedX(mThread);
    }

    inline static void Sleep_ms(uint32_t milliseconds)
    {
        chThdSleepMilliseconds(milliseconds);
    }

protected:
    virtual void Run() = 0;

    inline void Exit(ExitCode exitcode = 0)
    {
        chThdExit(exitcode);
    }

    inline void Yield()
    {
        chThdYield();
    }

    inline bool ShouldTerminate() const
    {
        return chThdShouldTerminateX();
    }

private:
    static inline void InternalStart(void* ptr)
    {
        static_cast<Thread*>(ptr)->Run();
    }

    thread_t* mThread;
};

}  // namespace Kernel
}  // namespace Springboard
