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

#include <hal.h>
#include <Springboard/Common.h>
#include <Springboard/Utilities/ArrayReference.hpp>

//! \section Microcontroller families
#define MCU_FAMILY_STM32F4              0UL

//! \section STM32F4 microcontroller lines
#define MCU_LINE_STM32F405_F407         0UL

//! \section STM32F405/F407 microcontroller variants
#define MCU_VARIANT_STM32F405xE         0UL
#define MCU_VARIANT_STM32F405xG         1UL
#define MCU_VARIANT_STM32F407xE         2UL
#define MCU_VARIANT_STM32F407xG         3UL
#define MCU_VARIANT_STM32F415xG         4UL
#define MCU_VARIANT_STM32F417xE         5UL
#define MCU_VARIANT_STM32F417xG         6UL

//! \section Microcontroller type/family/line/variant declarations
#define MCU_TYPE(family, line, variant)                     \
    ((MCU_FAMILY_##family) << 16U) |                        \
    ((MCU_LINE_##line) << 8U) |                             \
    ((MCU_VARIANT_##variant) << 0U)
#define MCU_FAMILY                      ((MCU_VALUE >> 16UL) & 0xffff)
#define MCU_LINE                        ((MCU_VALUE >> 8UL) & 0xff)
#define MCU_VARIANT                     ((MCU_VALUE >> 0UL) & 0xff)

//! \section I2C presence macros
#define SPRINGBOARD_HAL_ENABLE_I2C      HAL_USE_I2C
#define SPRINGBOARD_HAL_USE_I2C1        STM32_I2C_USE_I2C1
#define SPRINGBOARD_HAL_USE_I2C2        STM32_I2C_USE_I2C2
#define SPRINGBOARD_HAL_USE_I2C3        STM32_I2C_USE_I2C3

//! \section U(S)ART presence macros
#define SPRINGBOARD_HAL_ENABLE_UART     HAL_USE_SERIAL
#define SPRINGBOARD_HAL_USE_UART1       STM32_SERIAL_USE_USART1
#define SPRINGBOARD_HAL_USE_UART2       STM32_SERIAL_USE_USART2
#define SPRINGBOARD_HAL_USE_UART3       STM32_SERIAL_USE_USART3
#define SPRINGBOARD_HAL_USE_UART4       STM32_SERIAL_USE_UART4
#define SPRINGBOARD_HAL_USE_UART5       STM32_SERIAL_USE_UART5
#define SPRINGBOARD_HAL_USE_UART6       STM32_SERIAL_USE_USART6
#define SPRINGBOARD_HAL_USE_UART7       STM32_SERIAL_USE_UART7
#define SPRINGBOARD_HAL_USE_UART8       STM32_SERIAL_USE_UART8

//! \section SPI presence macros
#define SPRINGBOARD_HAL_ENABLE_SPI      HAL_USE_SPI
#define SPRINGBOARD_HAL_USE_SPI1        STM32_SPI_USE_SPI1
#define SPRINGBOARD_HAL_USE_SPI2        STM32_SPI_USE_SPI2
#define SPRINGBOARD_HAL_USE_SPI3        STM32_SPI_USE_SPI3
#define SPRINGBOARD_HAL_USE_SPI4        STM32_SPI_USE_SPI4
#define SPRINGBOARD_HAL_USE_SPI5        STM32_SPI_USE_SPI5
#define SPRINGBOARD_HAL_USE_SPI6        STM32_SPI_USE_SPI6

namespace Springboard {
namespace InternalHAL {

constexpr uint16_t GetMCUFamily()
{
    return static_cast<uint16_t>(MCU_FAMILY);
}

constexpr uint8_t GetMCULine()
{
    return static_cast<uint8_t>(MCU_LINE);
}

constexpr uint8_t GetMCUVariant()
{
    return static_cast<uint8_t>(MCU_VARIANT);
}

#if MCU_FAMILY == MCU_FAMILY_STM32F4
#if MCU_LINE == MCU_LINE_STM32F405_F407
enum class GPIOPinMode : iomode_t
{
    Input = PAL_STM32_MODE_INPUT,
    Output = PAL_STM32_MODE_OUTPUT,
    AlternateFunction_SYS = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(0),
    AlternateFunction_TIM1 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(1),
    AlternateFunction_TIM2 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(1),
    AlternateFunction_TIM3 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(2),
    AlternateFunction_TIM4 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(2),
    AlternateFunction_TIM5 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(2),
    AlternateFunction_TIM8 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(3),
    AlternateFunction_TIM9 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(3),
    AlternateFunction_TIM10 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(3),
    AlternateFunction_TIM11 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(3),
    AlternateFunction_I2C1 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(4),
    AlternateFunction_I2C2 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(4),
    AlternateFunction_I2C3 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(4),
    AlternateFunction_SPI1 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(5),
    AlternateFunction_SPI2 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(5),
    AlternateFunction_I2S2 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(5),
    AlternateFunction_I2S3ext_AF5 = PAL_STM32_MODE_ALTERNATE |
                                    PAL_STM32_ALTERNATE(5),
    AlternateFunction_SPI3 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(6),
    AlternateFunction_I2S2ext = PAL_STM32_MODE_ALTERNATE |
                                PAL_STM32_ALTERNATE(6),
    AlternateFunction_I2S3 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(6),
    AlternateFunction_USART1 = PAL_STM32_MODE_ALTERNATE |
                               PAL_STM32_ALTERNATE(7),
    AlternateFunction_USART2 = PAL_STM32_MODE_ALTERNATE |
                               PAL_STM32_ALTERNATE(7),
    AlternateFunction_USART3 = PAL_STM32_MODE_ALTERNATE |
                               PAL_STM32_ALTERNATE(7),
    AlternateFunction_I2S3ext_AF7 = PAL_STM32_MODE_ALTERNATE |
                                    PAL_STM32_ALTERNATE(7),
    AlternateFunction_UART4 = PAL_STM32_MODE_ALTERNATE |
                              PAL_STM32_ALTERNATE(8),
    AlternateFunction_UART5 = PAL_STM32_MODE_ALTERNATE |
                              PAL_STM32_ALTERNATE(8),
    AlternateFunction_USART6 = PAL_STM32_MODE_ALTERNATE |
                               PAL_STM32_ALTERNATE(8),
    AlternateFunction_CAN1 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(9),
    AlternateFunction_CAN2 = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(9),
    AlternateFunction_TIM12 = PAL_STM32_MODE_ALTERNATE |
                              PAL_STM32_ALTERNATE(9),
    AlternateFunction_TIM13 = PAL_STM32_MODE_ALTERNATE |
                              PAL_STM32_ALTERNATE(9),
    AlternateFunction_TIM14 = PAL_STM32_MODE_ALTERNATE |
                              PAL_STM32_ALTERNATE(9),
    AlternateFunction_OTG_FS = PAL_STM32_MODE_ALTERNATE |
                               PAL_STM32_ALTERNATE(10),
    AlternateFunction_OTG_HS_AF10 = PAL_STM32_MODE_ALTERNATE |
                                    PAL_STM32_ALTERNATE(10),
    AlternateFunction_ETH = PAL_STM32_MODE_ALTERNATE | PAL_STM32_ALTERNATE(11),
    AlternateFunction_FSMC = PAL_STM32_MODE_ALTERNATE |
                             PAL_STM32_ALTERNATE(12),
    AlternateFunction_SDIO = PAL_STM32_MODE_ALTERNATE |
                             PAL_STM32_ALTERNATE(12),
    AlternateFunction_OTG_FS_AF12 = PAL_STM32_MODE_ALTERNATE |
                                    PAL_STM32_ALTERNATE(12),
    AlternateFunction_DCMI = PAL_STM32_MODE_ALTERNATE |
                             PAL_STM32_ALTERNATE(13),
    AnalogInput = PAL_STM32_MODE_ANALOG,
};
#endif  // MCU_LINE == MCU_LINE_STM32F405_F407
#endif  // MCU_FAMILY == MCU_FAMILY_STM32F4

enum class GPIOPullConfiguration : iomode_t
{
    Floating = PAL_STM32_PUPDR_FLOATING,
    PullUp = PAL_STM32_PUPDR_PULLUP,
    PullDown = PAL_STM32_PUPDR_PULLDOWN,
};

enum class GPIOOutputConfiguration : iomode_t
{
    PushPull = PAL_STM32_OTYPE_PUSHPULL,
    OpenDrain = PAL_STM32_OTYPE_OPENDRAIN,
};

enum class GPIOOutputSpeed : iomode_t
{
    Low_2MHz = PAL_STM32_OSPEED_LOWEST,
    Medium_25MHz = PAL_STM32_OSPEED_MID1,
    High_50MHz = PAL_STM32_OSPEED_MID2,
    VeryHigh_100MHz = PAL_STM32_OSPEED_HIGHEST,
};

enum class I2CMode
{
    I2C = OPMODE_I2C,
    SMBusSlave = OPMODE_SMBUS_DEVICE,
    SMBusHost = OPMODE_SMBUS_HOST,
};

enum class I2CDutyCycle
{
    Standard = STD_DUTY_CYCLE,
    Fast_2 = FAST_DUTY_CYCLE_2,
    Fast_16_9 = FAST_DUTY_CYCLE_16_9,
};

enum class SPIClockConfig
{
    Mode0_CPOL0_CPHA0 = 0,
    Mode1_CPOL0_CPHA1 = SPI_CR1_CPHA,
    Mode2_CPOL1_CPHA0 = SPI_CR1_CPOL,
    Mode3_CPOL1_CPHA1 = SPI_CR1_CPOL | SPI_CR1_CPHA,
};

enum class UARTDataBits
{
    Eight = 0,
    Nine = USART_CR1_M,
};

enum class UARTParity
{
    None = 0,
    Even = USART_CR1_PCE,
    Odd = USART_CR1_PCE | USART_CR1_PS,
};

enum class UARTStopBits
{
    ZeroPointFive = USART_CR2_STOP_0,
    One = 0,
    OnePointFive = USART_CR2_STOP_1 | USART_CR2_STOP_0,
    Two = USART_CR2_STOP_1,
};

void Initialise();
const char* GetRTOSName();
const char* GetRTOSVersion();
const char* GetRTOSPortInfo();
const char* GetMCUArchitectureName();
const char* GetMCUArchitectureRevision();
const char* GetMCUCoreVariantName();
uint32_t GetMCUDeviceId();
bool GetMCUUniqueId(Springboard::Utilities::ByteArray buffer);
const char* GetMCUFamilyName();
const char* GetMCULineName();
const char* GetMCUVariantName();

}  // namespace InternalHAL
}  // namespace Springboard
