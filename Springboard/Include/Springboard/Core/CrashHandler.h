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

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)
struct ExceptionStackFrame
{
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t pc;
    uint32_t xpsr;
};

struct UnhandledExceptionData
{
    struct ExceptionStackFrame exceptionStackFrame;
    uint8_t exceptionNumber;
    uint32_t cfsrValue;
    uint32_t mmfarAddress;
    uint32_t bfarAddress;
};

#define CRASH_INFO_FIRMWARE_ASSERT_STRING_LENGTH        128

struct FirmwareAssertData
{
    char assertString[CRASH_INFO_FIRMWARE_ASSERT_STRING_LENGTH];
};

union CrashData
{
    struct UnhandledExceptionData unhandledException;
    struct FirmwareAssertData firmwareAssert;
};

#define CRASH_INFO_TYPE_UNHANDLED_EXCEPTION             0
#define CRASH_INFO_TYPE_FIRMWARE_ASSERT                 1

struct CrashInfo
{
    uint8_t type;
    union CrashData data;
};
#pragma pack()

void HandleCrashFA(const char* reason);
void HandleCrashUE(struct ExceptionStackFrame* exceptionStackFrame,
                   uint8_t exceptionNumber,
                   uint32_t cfsrValue,
                   uint32_t mmfarAddress,
                   uint32_t bfarAddress);

#ifdef __cplusplus
}
#endif
