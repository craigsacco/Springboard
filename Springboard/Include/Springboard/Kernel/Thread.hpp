/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#include <ch.h>
#include <Springboard/Common.hpp>

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
#if CH_VERSION == 1706
        return mThread->name;
#else
        return mThread->p_name;
#endif
    }

    inline Priority GetPriority() const
    {
#if CH_VERSION == 1706
        return mThread->prio;
#else
        return mThread->p_prio;
#endif
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
#if CH_VERSION == 1706
        return mThread->state != CH_STATE_WTSTART;
#else
        return mThread->p_state != CH_STATE_WTSTART;
#endif
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
