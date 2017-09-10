#pragma once

#include <Springboard/Common.hpp>
#include <hal.h>

#define SPRINGBOARD_HAL_ENABLE_I2C      HAL_USE_I2C

namespace Springboard {
namespace InternalHAL {

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
    Low = PAL_STM32_OSPEED_LOWEST,
    LowMedium = PAL_STM32_OSPEED_MID1,
    Medium = PAL_STM32_OSPEED_MID2,
    High = PAL_STM32_OSPEED_HIGHEST,
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
    Fast2 = FAST_DUTY_CYCLE_2,
    Fast16_9 = FAST_DUTY_CYCLE_16_9,
};

void Initialise();

}
}
