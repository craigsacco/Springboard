#pragma once

#include <Springboard/Common.hpp>
#include <ch.h>

namespace Springboard {
namespace Kernel {

class BinarySemaphore
{
public:
    BinarySemaphore(bool taken = false)
    {
        chBSemObjectInit(&mSemaphore, taken);
    }

    inline void Wait()
    {
        chBSemWait(&mSemaphore);
    }

    inline void WaitS()
    {
        chBSemWaitS(&mSemaphore);
    }

    inline void Signal()
    {
        chBSemSignal(&mSemaphore);
    }

    inline void SignalI()
    {
        chBSemSignalI(&mSemaphore);
    }

private:
    binary_semaphore_t mSemaphore;
};

}
}
