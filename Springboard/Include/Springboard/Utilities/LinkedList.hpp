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
#include <functional>
#include <Springboard/Kernel/Kernel.hpp>

namespace Springboard {
namespace Utilities {

template <typename T>
class LinkedList
{
private:
    struct Item
    {
        Item* next;
        T* data;
    };

public:
    LinkedList() :
        mFirst(nullptr), mLast(nullptr), mSize(0)
    {
    }

    bool Add(T* data)
    {
        Item* item = New();
        if (item == nullptr) {
            return false;
        }

        if (mFirst == nullptr) {
            mFirst = item;
        } else {
            mLast->next = item;
        }
        item->data = data;
        item->next = nullptr;
        mLast = item;
        mSize++;

        return true;
    }

    bool Remove(T* data)
    {
        Item* prev = nullptr;
        Item* item = mFirst;
        while (item != nullptr) {
            if (item->data == data) {
                if (item == mFirst) {
                    mFirst = item->next;
                } else {
                    prev->next = item->next;
                    if (item == mLast) {
                        mLast = prev;
                    }
                }
                mSize--;
                Free(item);
                return true;
            } else {
                prev = item;
                item = item->next;
            }
        }

        return false;
    }

    typedef std::function<bool(T*)> FindDelegateFPtr;

    T* Find(FindDelegateFPtr fn) const
    {
        Item* item = mFirst;
        while (item != nullptr) {
            if (fn(item->data)) {
                return item->data;
            } else {
                item = item->next;
            }
        }

        return nullptr;
    }

    inline size_t GetSize() const
    {
        return mSize;
    }

private:
    inline Item* New()
    {
        return static_cast<Item*>(
            Springboard::Kernel::AllocateMemoryFromHeap(sizeof(Item)));
    }

    inline void Free(Item* item)
    {
        Springboard::Kernel::FreeMemoryFromHeap(item);
    }

    Item* mFirst;
    Item* mLast;
    size_t mSize;
};

typedef ArrayReference<uint8_t> ByteArray;
typedef ArrayReference<const uint8_t> ConstByteArray;

}  // namespace Utilities
}  // namespace Springboard
