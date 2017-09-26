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

class Mailbox
{
public:
    explicit Mailbox(size_t size)
    {
        mData = reinterpret_cast<msg_t*>(chHeapAlloc(nullptr,
                                                     size * sizeof(msg_t)));
        ASSERT(mData != nullptr);

        chMBObjectInit(&mMailbox, mData, size);
    }

    inline void Reset()
    {
        chMBReset(&mMailbox);
    }

    inline void ResetI()
    {
        chMBResetI(&mMailbox);
    }

    inline void Resume()
    {
        chMBResumeX(&mMailbox);
    }

    template <typename T>
    inline void Post(const T& data)
    {
        msg_t result = chMBPost(&mMailbox, (msg_t)&data, TIME_INFINITE);
        ASSERT(result == MSG_OK);
    }

    template <typename T>
    inline void PostI(const T& data)
    {
        msg_t result = chMBPostI(&mMailbox, (msg_t)&data);
        ASSERT(result == MSG_OK);
    }

    template <typename T>
    inline void PostAhead(const T& data)
    {
        msg_t result = chMBPostAhead(&mMailbox, (msg_t)&data, TIME_INFINITE);
        ASSERT(result == MSG_OK);
    }

    template <typename T>
    inline void PostAheadI(const T& data)
    {
        msg_t result = chMBPostAheadI(&mMailbox, (msg_t)&data);
        ASSERT(result == MSG_OK);
    }

    template <typename T>
    inline T& Fetch()
    {
        msg_t data = 0;
        msg_t result = chMBFetch(&mMailbox, &data, TIME_INFINITE);
        ASSERT(result == MSG_OK);
        return *reinterpret_cast<T*>(data);
    }

    template <typename T>
    inline T& FetchI()
    {
        msg_t data = 0;
        msg_t result = chMBFetchI(&mMailbox, &data);
        ASSERT(result == MSG_OK);
        return *reinterpret_cast<T*>(data);
    }

private:
    mailbox_t mMailbox;
    msg_t* mData;
};

}  // namespace Kernel
}  // namespace Springboard
