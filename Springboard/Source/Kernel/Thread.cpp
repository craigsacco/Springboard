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

    void* wsp = Springboard::Kernel::AllocateMemoryFromHeap(size);
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
