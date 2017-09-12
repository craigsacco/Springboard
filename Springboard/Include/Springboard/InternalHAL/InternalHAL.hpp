/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#include <hal.h>
#include <Springboard/Common.hpp>

#define SPRINGBOARD_HAL_ENABLE_I2C      HAL_USE_I2C
#define SPRINGBOARD_HAL_USE_I2C1        STM32_I2C_USE_I2C1
#define SPRINGBOARD_HAL_USE_I2C2        STM32_I2C_USE_I2C2
#define SPRINGBOARD_HAL_USE_I2C3        STM32_I2C_USE_I2C3

namespace Springboard {
namespace InternalHAL {

enum GPIOPinMode
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

enum GPIOPullConfiguration
{
    Floating = PAL_STM32_PUPDR_FLOATING,
    PullUp = PAL_STM32_PUPDR_PULLUP,
    PullDown = PAL_STM32_PUPDR_PULLDOWN,
};

enum GPIOOutputConfiguration
{
    PushPull = PAL_STM32_OTYPE_PUSHPULL,
    OpenDrain = PAL_STM32_OTYPE_OPENDRAIN,
};

enum GPIOOutputSpeed
{
    Low_2MHz = PAL_STM32_OSPEED_LOWEST,
    Medium_25MHz = PAL_STM32_OSPEED_MID1,
    High_50MHz = PAL_STM32_OSPEED_MID2,
    VeryHigh_100MHz = PAL_STM32_OSPEED_HIGHEST,
};

enum I2CMode
{
    I2C = OPMODE_I2C,
    SMBusSlave = OPMODE_SMBUS_DEVICE,
    SMBusHost = OPMODE_SMBUS_HOST,
};

enum I2CDutyCycle
{
    Standard = STD_DUTY_CYCLE,
    Fast_2 = FAST_DUTY_CYCLE_2,
    Fast_16_9 = FAST_DUTY_CYCLE_16_9,
};

void Initialise();

}  // namespace InternalHAL
}  // namespace Springboard
