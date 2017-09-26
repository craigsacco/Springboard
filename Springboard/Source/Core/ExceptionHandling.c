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
};
#pragma pack()

void UnhandledException(volatile struct ExceptionStackFrame* frame)
{
    // capture some vital data
    //  * exception number (3 = hard fault, 4 = MM fault, etc...)
    //  * CFSR register value
    //  * fault address (for MM and bus faults)
    volatile uint8_t exceptionNumber = (uint8_t)(SCB->ICSR & 0xff);
    volatile uint32_t cfsrValue = SCB->CFSR;
    volatile uint32_t faultAddress = 0;
    if (cfsrValue & (1UL << 7)) {
        faultAddress = SCB->MMFAR;
    } else if (cfsrValue & (1UL << 15)) {
        faultAddress = SCB->BFAR;
    }

    (void)frame;
    (void)exceptionNumber;
    (void)faultAddress;

    // if running a debug session, trigger a software breakpoint
    if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) {
        __ASM volatile ("bkpt");  // NOLINT
    }

    // loop forever
    while (true) {
    }
}
