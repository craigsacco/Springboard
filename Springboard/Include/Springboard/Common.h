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

//! \section Common type definitions
typedef uint32_t ResultCode;
#define RC_OK                               ((ResultCode)0)
#define RC_MASK_RESOURCE                    ((ResultCode)0x10000000)
#define RC_RESOURCE_INVALID_TYPE            ((ResultCode)(RC_MASK_RESOURCE + 1))
#define RC_RESOURCE_INVALID_PROPERTY_ID     ((ResultCode)(RC_MASK_RESOURCE + 2))
#define RC_RESOURCE_PROPERTY_NOT_SETABLE    ((ResultCode)(RC_MASK_RESOURCE + 3))
#define RC_RESOURCE_INVALID_PROPERTY_LENGTH ((ResultCode)(RC_MASK_RESOURCE + 4))

//! \section Assertion checking
#define ASSERT(cond)                chDbgAssert(cond, #cond)
#define ASSERT_MSG(cond, msg)       chDbgAssert(cond, msg)
