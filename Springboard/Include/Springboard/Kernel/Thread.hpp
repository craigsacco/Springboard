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

    virtual void Run() = 0;

protected:
    Thread() = delete;

    Thread(const char* name, Priority priority)
        : mThread(nullptr)
    {
        // shut the compiler up
        (void)name;
        (void)priority;
    }

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

    thread_t* mThread;
};

template <int ThreadSize>
class StaticThread : public Thread
{
public:
    StaticThread(const char* name, Priority priority)
        : Thread(name, priority)
    {
#if CH_VERSION == 1706
        thread_descriptor_t tdp {
            name,
            THD_WORKING_AREA_BASE(mWorkingArea),
            THD_WORKING_AREA_END(mWorkingArea),
            priority,
            StaticThread<ThreadSize>::InternalStart,
            this
        };
        mThread = chThdCreateSuspended(&tdp);
#else
        chSysLock();
        mThread = chThdCreateI(mWorkingArea, ThreadSize, priority,
                               StaticThread<ThreadSize>::InternalStart,
                               this);
        chSysUnlock();
#endif
    }

private:
    static inline void InternalStart(void* ptr)
    {
        static_cast<StaticThread<ThreadSize>*>(ptr)->Run();
    }

    THD_WORKING_AREA(mWorkingArea, ThreadSize);
};

}
}
