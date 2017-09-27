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

#include <Springboard/Utilities/ArrayReference.hpp>

namespace Springboard {
namespace Utilities {
namespace ArrayReferenceUtils {

CharArray ArrayFromString(char* ptr)
{
    return CharArray::Construct(ptr, strlen(ptr));
}

ConstCharArray ArrayFromString(const char* ptr)
{
    return ConstCharArray::Construct(ptr, strlen(ptr));
}

void SafeStringCopy(CharArray target, const char* str)
{
    // just to be safe, save one character for a null-terminator
    strncpy(target.GetData(), str, target.GetSize() - 1);
}

uint32_t ToUInt32(ConstCharArray buffer, bool* errors)
{
    bool ok = true;
    size_t pos = 0;
    uint32_t value = 0;

    while (pos < buffer.GetSize()) {
        char b = buffer[pos++];
        if (isdigit(b)) {
            value = (value * 10) + (b - '0');
        } else {
            ok = false;
            break;  // invalid digit found
        }
    }

    if (errors != nullptr) {
        *errors = !ok;
    }
    return value;
}

int32_t ToInt32(ConstCharArray buffer, bool* errors)
{
    uint32_t u = 0;
    bool negative = false;
    bool errors0;

    if (buffer[0] == '-') {
        negative = true;
        u = ToUInt32(buffer.RightFrom(1), &errors0);
    } else {
        u = ToUInt32(buffer, &errors0);
    }

    if (errors0) {
        if (errors != nullptr) {
            *errors = errors0;
        }
        return 0;  // errors found when parsing integer
    }

    bool ok = true;
    if (u > 0x80000000UL) {
        ok = false;
        u = 0;  // number is too big
    }

    int32_t value = static_cast<int32_t>(u);
    if (negative) {
        value = 0 - value;
    }

    if (errors != nullptr) {
        *errors = !ok;
    }
    return value;
}

float ToFloat(ConstCharArray buffer, bool* errors)
{
    bool ok = true;
    size_t pos = 0;
    float value = 0.0f;
    bool negative = false;
    float fractional = 0.0f;

    while (pos < buffer.GetSize()) {
        char b = buffer[pos];
        if (pos == 0 && b == '-') {
            negative = true;
        } else if (isdigit(b)) {
            if (fractional == 0) {
                value = (value * 10.0f) + (b - '0');
            } else {
                value += ((b - '0') * fractional);
                fractional *= 0.1f;
            }
        } else if (b == '.') {
            if (fractional == 0.0f) {
                fractional = 0.1f;
            } else {
                ok = false;
                break;  // second decimal point found
            }
        } else {
            ok = false;
            break;  // invalid digit found
        }
        pos++;
    }

    if (negative) {
        value = 0.0f - value;
    }

    if (errors != nullptr) {
        *errors = !ok;
    }
    return value;
}

}  // namespace ArrayReferenceUtils
}  // namespace Utilities
}  // namespace Springboard
