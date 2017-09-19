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

#include <hal.h>
#include <Springboard/Core/ExceptionHandling.h>

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
#if CORTEX_USE_FPU
    union vfpu
    {
        struct spfp
        {
            float s0;
            float s1;
            float s2;
            float s3;
            float s4;
            float s5;
            float s6;
            float s7;
            float s8;
            float s9;
            float s10;
            float s11;
            float s12;
            float s13;
            float s14;
            float s15;
        } spfp;
        struct dpfp
        {
            double d0;
            double d1;
            double d2;
            double d3;
            double d4;
            double d5;
            double d6;
            double d7;
        } dpfp;
    } vfpu;
    uint32_t fpscr;
    uint32_t aligner;
#endif  // CORTEX_USE_FPU
};
#pragma pack()

#ifdef __cplusplus
static_assert(sizeof(ExceptionStackFrame.vfpu.spfp) ==
              sizeof(ExceptionStackFrame.vfpu.dpfp),
              "Space for float and double register storage must be identical");
static_assert(sizeof(ExceptionStackFrame) % 8 == 0,
              "Stack frame must have an 8-byte alignment");
#endif

void UnhandledException(volatile struct ExceptionStackFrame* frame)
{
    (void)frame;

    // if running a debug session, trigger a software breakpoint
    if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) {
        asm volatile ("bkpt");
    }

    // loop forever
    while (true) {
    }
}
