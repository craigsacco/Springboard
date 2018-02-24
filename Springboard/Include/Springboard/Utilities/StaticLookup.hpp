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

namespace Springboard {
namespace Utilities {

template <typename TKey, typename TValue>
struct StaticLookupEntry
{
    TKey key;
    TValue value;
};

template <typename TKey, typename TValue, int Size>
class StaticLookup
{
public:
    typedef StaticLookupEntry<TKey, TValue> Entry;

    constexpr StaticLookup(const Entry (&entries)[Size]) :
        mEntries(entries)
    {
    }

    bool Find(const TKey key, TValue* value) const
    {
        for (const Entry& entry : mEntries) {
            if (key == entry.key) {
                *value = entry.value;
                return true;
            }
        }

        return false;
    }

    static constexpr size_t LENGTH = Size;

private:
    const StaticLookupEntry<TKey, TValue> mEntries[Size];
};

}  // namespace Utilities
}  // namespace Springboard
