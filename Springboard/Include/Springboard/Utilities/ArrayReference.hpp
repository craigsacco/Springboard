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
#include <cstddef>

namespace Springboard {
namespace Utilities {

template <typename T>
class ArrayReference
{
public:
    constexpr ArrayReference(std::nullptr_t) :
        mData(nullptr), mSize(0)
    {
    }

    constexpr ArrayReference(T* data, size_t size) :
        mData(data), mSize(size)
    {
    }

    template <int Size>
    constexpr ArrayReference(T (&data)[Size]) :
        mData(data), mSize(Size)
    {
    }

    constexpr T* GetData() const
    {
        return mData;
    }

    constexpr size_t GetSize() const
    {
        return mSize;
    }

    T& At(size_t i) const
    {
        ASSERT(i <= mSize);
        return *(mData + i);
    }

    ArrayReference<T> Left(size_t n) const
    {
        ASSERT(n <= mSize);
        return ArrayReference<T>(mData, n);
    }

    ArrayReference<T> Right(size_t n) const
    {
        ASSERT(n <= mSize);
        return ArrayReference<T>(mData + (mSize - n), n);
    }

    ArrayReference<T> Mid(size_t i, size_t n) const
    {
        ASSERT(i + n <= mSize);
        return ArrayReference<T>(mData + i, n);
    }

    static constexpr ArrayReference<T> Null()
    {
        return ArrayReference<T>(nullptr);
    }

    static constexpr ArrayReference<T> FromSingleRef(const T& value)
    {
        return ArrayReference<T>(&value, 1);
    }

    static constexpr ArrayReference<T> FromSinglePtr(T* ptr)
    {
        return ArrayReference<T>(ptr, 1);
    }

    static constexpr ArrayReference<T> Construct(T* data, size_t size)
    {
        return ArrayReference<T>(data, size);
    }

private:
    T* mData;
    size_t mSize;
};

typedef ArrayReference<uint8_t> ByteArray;
typedef ArrayReference<const uint8_t> ConstByteArray;

}  // namespace Utilities
}  // namespace Springboard
