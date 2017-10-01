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

#include <Springboard/Core/CrashHandler.h>
#include <hal.h>
#include <string.h>

static inline void TriggerBreakpoint(void)
{
    // if running a debug session, trigger a software breakpoint
    if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) {
        __ASM volatile ("bkpt");  // NOLINT
    }

    // loop forever
    while (true) {
    }
}

static void PersistCrashInfo(struct CrashInfo* info)
{
    (void)info;
}

void HandleCrashFA(const char* reason)
{
    struct CrashInfo info;
    info.type = CRASH_INFO_TYPE_FIRMWARE_ASSERT;
    strncpy(info.data.firmwareAssert.assertString, reason,
            CRASH_INFO_FIRMWARE_ASSERT_STRING_LENGTH - 1);

    PersistCrashInfo(&info);
    TriggerBreakpoint();
}

void HandleCrashUE(struct ExceptionStackFrame* exceptionStackFrame,
                   uint8_t exceptionNumber,
                   uint32_t cfsrValue,
                   uint32_t mmfarAddress,
                   uint32_t bfarAddress)
{
    struct CrashInfo info;
    info.type = CRASH_INFO_TYPE_UNHANDLED_EXCEPTION;
    info.data.unhandledException.exceptionStackFrame = *exceptionStackFrame;
    info.data.unhandledException.exceptionNumber = exceptionNumber;
    info.data.unhandledException.cfsrValue = cfsrValue;
    info.data.unhandledException.mmfarAddress = mmfarAddress;
    info.data.unhandledException.bfarAddress = bfarAddress;

    PersistCrashInfo(&info);
    TriggerBreakpoint();
}
