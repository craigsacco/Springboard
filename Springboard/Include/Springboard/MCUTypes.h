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

//! \section Microcontroller families
#define MCU_FAMILY_STM32F4              0x00UL
#define MCU_FAMILY_STM32F7              0x01UL

//! \section STM32 macros
#define MCU_VARIANT_STM32_FLASH_512k    0x09UL
#define MCU_VARIANT_STM32_FLASH_1M      0x0AUL
#define MCU_VARIANT_STM32_FLASH_2M      0x0BUL
#define MCU_VARIANT_STM32_IN_GROUP(group) \
    ((MCU_TYPE_VALUE & 0xF0UL) == group)

//! \section STM32F4 microcontroller lines
#define MCU_LINE_STM32F405_F415         0x00UL
#define MCU_LINE_STM32F407_F417         0x01UL
#define MCU_LINE_STM32F427_F437         0x02UL
#define MCU_LINE_STM32F429_F439         0x03UL

//! \section STM32F405/F415 microcontroller variants
#define MCU_VARIANT_STM32F405xx         0x00UL
#define MCU_VARIANT_STM32F415xx         0x10UL
#define MCU_VARIANT_STM32F405xE         (MCU_VARIANT_STM32F405xx | \
                                         MCU_VARIANT_STM32_FLASH_512k)
#define MCU_VARIANT_STM32F405xG         (MCU_VARIANT_STM32F405xx | \
                                         MCU_VARIANT_STM32_FLASH_1M)
#define MCU_VARIANT_STM32F415xG         (MCU_VARIANT_STM32F415xx | \
                                         MCU_VARIANT_STM32_FLASH_1M)

//! \section STM32F415/F417 microcontroller variants
#define MCU_VARIANT_STM32F407xx         0x00UL
#define MCU_VARIANT_STM32F417xx         0x10UL
#define MCU_VARIANT_STM32F407xE         (MCU_VARIANT_STM32F407xx | \
                                         MCU_VARIANT_STM32_FLASH_512k)
#define MCU_VARIANT_STM32F407xG         (MCU_VARIANT_STM32F407xx | \
                                         MCU_VARIANT_STM32_FLASH_1M)
#define MCU_VARIANT_STM32F417xE         (MCU_VARIANT_STM32F417xx | \
                                         MCU_VARIANT_STM32_FLASH_512k)
#define MCU_VARIANT_STM32F417xG         (MCU_VARIANT_STM32F417xx | \
                                         MCU_VARIANT_STM32_FLASH_1M)

//! \section STM32F427/F437 microcontroller variants
#define MCU_VARIANT_STM32F427xx         0x00UL
#define MCU_VARIANT_STM32F427xG         (MCU_VARIANT_STM32F427xx | \
                                         MCU_VARIANT_STM32_FLASH_1M)
#define MCU_VARIANT_STM32F427xI         (MCU_VARIANT_STM32F427xx | \
                                         MCU_VARIANT_STM32_FLASH_2M)
#define MCU_VARIANT_STM32F437xx         0x10UL
#define MCU_VARIANT_STM32F437xG         (MCU_VARIANT_STM32F427xx | \
                                         MCU_VARIANT_STM32_FLASH_1M)
#define MCU_VARIANT_STM32F437xI         (MCU_VARIANT_STM32F427xx | \
                                         MCU_VARIANT_STM32_FLASH_2M)

//! \section STM32F437/F439 microcontroller variants
#define MCU_VARIANT_STM32F429xx         0x00UL
#define MCU_VARIANT_STM32F429xE         (MCU_VARIANT_STM32F429xx | \
                                         MCU_VARIANT_STM32_FLASH_512k)
#define MCU_VARIANT_STM32F429xG         (MCU_VARIANT_STM32F429xx | \
                                         MCU_VARIANT_STM32_FLASH_1M)
#define MCU_VARIANT_STM32F429xI         (MCU_VARIANT_STM32F429xx | \
                                         MCU_VARIANT_STM32_FLASH_2M)
#define MCU_VARIANT_STM32F439xx         0x10UL
#define MCU_VARIANT_STM32F439xG         (MCU_VARIANT_STM32F439xx | \
                                         MCU_VARIANT_STM32_FLASH_1M)
#define MCU_VARIANT_STM32F439xI         (MCU_VARIANT_STM32F439xx | \
                                         MCU_VARIANT_STM32_FLASH_2M)

//! \section STM32F7 microcontroller lines
#define MCU_LINE_STM32F746_F756         0x00UL

//! \section STM32F746/F756 microcontroller variants
#define MCU_VARIANT_STM32F746xx         0x00UL
#define MCU_VARIANT_STM32F756xx         0x10UL
#define MCU_VARIANT_STM32F746xE         (MCU_VARIANT_STM32F746xx | \
                                         MCU_VARIANT_STM32_FLASH_512k)
#define MCU_VARIANT_STM32F746xG         (MCU_VARIANT_STM32F746xx | \
                                         MCU_VARIANT_STM32_FLASH_1M)
#define MCU_VARIANT_STM32F756xG         (MCU_VARIANT_STM32F756xx | \
                                         MCU_VARIANT_STM32_FLASH_1M)

//! \section Microcontroller type/family/line/variant declarations
#define MCU_TYPE(family, line, variant)                     \
    (((MCU_FAMILY_##family) << 16UL) |                      \
     ((MCU_LINE_##line) << 8UL) |                           \
     ((MCU_VARIANT_##variant) << 0UL))
#define MCU_FAMILY                      ((MCU_TYPE_VALUE >> 16UL) & 0xFFFFUL)
#define MCU_LINE                        ((MCU_TYPE_VALUE >> 8UL) & 0xFFUL)
#define MCU_VARIANT                     ((MCU_TYPE_VALUE >> 0UL) & 0xFFUL)
