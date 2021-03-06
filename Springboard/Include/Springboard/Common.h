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

#include <sbconf.h>
#include <ch.h>
#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#include <Springboard/MCUTypes.h>
#include <Springboard/ResultCodes.h>

//! \section Common type definitions
typedef uint32_t ResultCode;
typedef uint16_t ResourceIdentifier;
typedef uint16_t PropertyIdentifier;

//! \section Assertion checking
#define ASSERT(cond)                chDbgAssert(cond, #cond)
#define ASSERT_MSG(cond, msg)       chDbgAssert(cond, msg)
#define ASSERT_FAIL()               chDbgAssert(false)
#define ASSERT_FAIL_MSG(msg)        chDbgAssert(false, msg)
