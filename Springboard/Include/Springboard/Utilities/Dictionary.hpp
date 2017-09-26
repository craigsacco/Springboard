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

#include <Springboard/Common.h>
#include <Springboard/Kernel/Kernel.hpp>

namespace Springboard {
namespace Utilities {

template <typename TKey, typename TValue>
class Dictionary
{
private:
    struct Item
    {
        Item* next;
        TKey key;
        TValue value;
    };

public:
    Dictionary() :
        mFirst(nullptr), mLast(nullptr), mSize(0)
    {
    }

    bool Add(TKey key, TValue value)
    {
        Item* item = mFirst;
        while (item != nullptr) {
            if (item->key == key) {
                item->value = value;
                return true;
            } else {
                item = item->next;
            }
        }

        item = New();
        if (item == nullptr) {
            return false;
        }

        if (mFirst == nullptr) {
            mFirst = item;
        } else {
            mLast->next = item;
        }
        item->key = key;
        item->value = value;
        item->next = nullptr;
        mLast = item;
        mSize++;

        return true;
    }

    bool Remove(TKey key)
    {
        Item* prev = nullptr;
        Item* item = mFirst;
        while (item != nullptr) {
            if (item->key == key) {
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

    bool Find(TKey key, TValue* value) const
    {
        Item* item = mFirst;
        while (item != nullptr) {
            if (item->key == key) {
                *value = item->value;
                return true;
            } else {
                item = item->next;
            }
        }

        return false;
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

}  // namespace Utilities
}  // namespace Springboard
