#pragma once

#include <Springboard/Common.hpp>
#include <hal.h>

#define SPRINGBOARD_HAL_ENABLE_I2C      HAL_USE_I2C

namespace Springboard {
namespace InternalHAL {

enum GPIOPinMode
{
    Input = PAL_STM32_MODE_INPUT,
    Output = PAL_STM32_MODE_OUTPUT,
    AlternateFunction = PAL_STM32_MODE_ALTERNATE,
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

enum GPIOAlternateFunction
{
    AF_SYS = 0,
    AF_TIM1 = 1,
    AF_TIM2 = 1,
    AF_TIM3 = 2,
    AF_TIM4 = 2,
    AF_TIM5 = 2,
    AF_TIM8 = 3,
    AF_TIM9 = 3,
    AF_TIM10 = 3,
    AF_TIM11 = 3,
    AF_I2C1 = 4,
    AF_I2C2 = 4,
    AF_I2C3 = 4,
    AF_SPI1 = 5,
    AF_SPI2 = 5,
    AF_I2S2 = 5,
    AF_I2S2ext = 5,
    AF_SPI3 = 6,
    AF_I2S1ext = 6,
    AF_I2S3 = 6,
    AF_USART1 = 7,
    AF_USART2 = 7,
    AF_USART3 = 7,
    AF_I2S3Ext = 7,
    AF_UART4 = 8,
    AF_UART5 = 8,
    AF_USART6 = 8,
    AF_CAN1 = 9,
    AF_CAN2 = 9,
    AF_TIM12 = 9,
    AF_TIM13 = 9,
    AF_TIM14 = 9,
    AF_OTGFS = 10,
    AF_OTGHS_10 = 10,
    AF_ETH = 11,
    AF_FSMC = 12,
    AF_SDIO = 12,
    AF_OTGFS_12 = 12,
    AF_DCMI = 13,
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

}
}
