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
        chThdResume(&mThread, MSG_OK);
    }

    inline void StartI()
    {
        chThdResumeI(&mThread, MSG_OK);
    }

    inline void StartS()
    {
        chThdResumeS(&mThread, MSG_OK);
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

    thread_t* mThread;
};

template <int ThreadSize>
class StaticThread : public Thread
{
public:
    StaticThread(const char* name, Priority priority)
        : Thread(name, priority)
    {
        thread_descriptor_t tdp {
            name,
            THD_WORKING_AREA_BASE(mWorkingArea),
            THD_WORKING_AREA_END(mWorkingArea),
            priority,
            StaticThread<ThreadSize>::InternalStart,
            this
        };
        mThread = chThdCreateSuspended(&tdp);
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
