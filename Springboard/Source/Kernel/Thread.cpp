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

#include <Springboard/Kernel/Thread.hpp>
#include <Springboard/Kernel/Kernel.hpp>

namespace Springboard {
namespace Kernel {

Thread::Thread(const char* name, size_t size, Priority priority)
    : mThread(nullptr)
{
    // this function is a variation of chThdCreateFromHeap, except that
    // the thread remains suspended at the end of the call

    // NOTE: when using PORT_ENABLE_GUARD_PAGES, the current
    // version of the chHeapAllocAligned() function in ChibiOS may not return a
    // pointer that is properly aligned to a 32-byte boundary required for MPU
    // page guarding to work correctly. The side of effect is that the thread
    // does not get created. It has been posted to the forums here:
    // http://www.chibios.com/forum/viewtopic.php?f=35&t=4254
    //
    // the workaround is to request a larger amount of memory than requested
    // from the heap and forward the pointer to a 32 byte alignment (or
    // allocate the increased memory to the thread in case it is already
    // aligned)
    void* wsp = Springboard::Kernel::AllocateMemoryFromHeapAligned(
        size + PORT_WORKING_AREA_ALIGN);
    ASSERT(wsp != nullptr);
    uint8_t* tmp = static_cast<uint8_t*>(wsp);
    tmp = reinterpret_cast<uint8_t*>(
        (reinterpret_cast<uint32_t>(tmp) &
         ~(static_cast<uint32_t>(PORT_WORKING_AREA_ALIGN - 1))));
    if (tmp != wsp) {
        tmp += PORT_WORKING_AREA_ALIGN;  // forward to next alignment
    } else {
        size += PORT_WORKING_AREA_ALIGN;  // give thread additional stack
    }
    wsp = static_cast<void*>(tmp);

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
