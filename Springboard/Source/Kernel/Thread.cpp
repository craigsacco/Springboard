/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#include <Springboard/Kernel/Thread.hpp>

namespace Springboard {
namespace Kernel {

Thread::Thread(const char* name, size_t size, Priority priority)
    : mThread(nullptr)
{
    // this function is a variation of chThdCreateFromHeap, except that
    // the thread remains suspended at the end of the call

    void* wsp = chHeapAllocAligned(nullptr, size, PORT_WORKING_AREA_ALIGN);
    ASSERT(wsp != nullptr);

    thread_descriptor_t td = {
        .name = name,
        .wbase = reinterpret_cast<stkalign_t*>(wsp),
        .wend = reinterpret_cast<stkalign_t*>(
            reinterpret_cast<uint8_t*>(wsp) + size),
        .prio = priority,
        .funcp = Thread::InternalStart,
        .arg = this
    };
    chSysLock();
    mThread = chThdCreateSuspendedI(&td);
    mThread->flags = CH_FLAG_MODE_HEAP;
    chSysUnlock();
}

}  // namespace Kernel
}  // namespace Springboard
