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
#include <cctype>
#include <cstring>

namespace Springboard {
namespace Utilities {

template <typename T>
class ArrayReference
{
public:
    typedef T UnderlyingType;
    typedef T* UnderlyingTypePtr;

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

    T& operator[](std::size_t i)
    {
        ASSERT(i <= mSize);
        return *(mData + i);
    }

    const T& operator[](std::size_t i) const
    {
        ASSERT(i <= mSize);
        return *(mData + i);
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
        ASSERT(i <= mSize);
        ASSERT(i + n <= mSize);
        return ArrayReference<T>(mData + i, n);
    }

    ArrayReference<T> From(size_t i) const
    {
        ASSERT(i <= mSize);
        return ArrayReference<T>(mData + i, mSize - i);
    }

    template <typename TTarget>
    ArrayReference<TTarget> CastTo()
    {
        static_assert(sizeof(T) == sizeof(TTarget),
                      "Target type must be the same size");
        return ArrayReference<TTarget>::Construct(
            reinterpret_cast<TTarget*>(mData), GetSize());
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

protected:
    T* mData;
    size_t mSize;
};

typedef ArrayReference<uint8_t> ByteArray;
typedef ArrayReference<const uint8_t> ConstByteArray;
typedef ArrayReference<char> CharArray;
typedef ArrayReference<const char> ConstCharArray;

namespace ArrayReferenceUtils
{
    CharArray ArrayFromString(char* ptr);
    ConstCharArray ArrayFromString(const char* ptr);
    void SafeStringCopy(CharArray target, const char* str);
    uint32_t ToUInt32(ConstCharArray buffer, bool* errors = nullptr);
    int32_t ToInt32(ConstCharArray buffer, bool* errors = nullptr);
    float ToFloat(ConstCharArray buffer, bool* errors = nullptr);
}

}  // namespace Utilities
}  // namespace Springboard
