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

class Mutex
{
public:
    Mutex()
    {
        chMtxObjectInit(&mMutex);
    }

    inline void Lock()
    {
        chMtxLock(&mMutex);
    }

    inline bool TryLock()
    {
        return chMtxTryLock(&mMutex);
    }

    inline void Unlock()
    {
        chMtxUnlock(&mMutex);
    }

private:
    mutex_t mMutex;
};

class ScopedMutex
{
public:
    explicit ScopedMutex(Mutex* mutex) :
        mMutex(mutex)
    {
        mMutex->Lock();
    }

    ~ScopedMutex()
    {
        mMutex->Unlock();
    }

private:
    Mutex* mMutex;
};

}  // namespace Kernel
}  // namespace Springboard
