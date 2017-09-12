/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#include <ch.h>
#include <Springboard/Common.hpp>

namespace Springboard {
namespace Kernel {

class BinarySemaphore
{
public:
    explicit BinarySemaphore(bool taken)
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

}  // namespace Kernel
}  // namespace Springboard
