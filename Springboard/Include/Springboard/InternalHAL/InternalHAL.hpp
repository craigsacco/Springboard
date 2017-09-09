#pragma once

#include <Springboard/Common.hpp>
#include <hal.h>

namespace Springboard {
namespace InternalHAL {

enum PullConfiguration
{
    Floating = PAL_STM32_PUPDR_FLOATING,
    PullUp = PAL_STM32_PUPDR_PULLUP,
    PullDown = PAL_STM32_PUPDR_PULLDOWN,
};

enum OutputConfiguration
{
    PushPull = PAL_STM32_OTYPE_PUSHPULL,
    OpenDrain = PAL_STM32_OTYPE_OPENDRAIN,
};

enum OutputSpeed
{
    Low = PAL_STM32_OSPEED_LOWEST,
    LowMedium = PAL_STM32_OSPEED_MID1,
    Medium = PAL_STM32_OSPEED_MID2,
    High = PAL_STM32_OSPEED_HIGHEST,
};

void Initialise();

}
}
