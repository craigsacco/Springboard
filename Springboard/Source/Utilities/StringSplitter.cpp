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

#include <cstring>
#include <Springboard/Utilities/StringSplitter.hpp>

using namespace Springboard::Utilities::ArrayReferenceUtils;  // NOLINT

namespace Springboard {
namespace Utilities {

StringSplitter::StringSplitter(ConstCharArray buffer, char token) :
    mBuffer(buffer), mToken(token), mPosition(0)
{
}

ConstCharArray StringSplitter::GetNext()
{
    if (mPosition >= mBuffer.GetSize()) {
        return ConstCharArray::Null();
    }

    size_t start = mPosition;
    size_t length = 0;
    while (true) {
        if (mPosition == mBuffer.GetSize()) {
            return mBuffer.Mid(start, length);
        } else if (mBuffer[mPosition++] == mToken) {
            return mBuffer.Mid(start, length);
        } else {
            length++;
        }
    }
}

void StringSplitter::SkipNext()
{
    GetNext();
}

uint32_t StringSplitter::GetNextAsUInt32(bool* errors)
{
    return ToUInt32(GetNext(), errors);
}

int32_t StringSplitter::GetNextAsInt32(bool* errors)
{
    return ToInt32(GetNext(), errors);
}

float StringSplitter::GetNextAsFloat(bool* errors)
{
    return ToFloat(GetNext(), errors);
}

StringSplitter StringSplitter::GetRemainder() const
{
    return StringSplitter(mBuffer.From(mPosition), mToken);
}

}  // namespace Utilities
}  // namespace Springboard
