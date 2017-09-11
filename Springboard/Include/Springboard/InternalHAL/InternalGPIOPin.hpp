#pragma once

#include <Springboard/InternalHAL/InternalHAL.hpp>

namespace Springboard {
namespace InternalHAL {

class InternalGPIOPin
{
public:
    typedef ioportid_t Port;

    InternalGPIOPin(const Port port, const uint8_t pin) :
        mPort(port), mPin(pin)
    {
    }

    inline static void SetPinConfiguration(
        const Port port, const uint8_t pin, const GPIOPinMode mode,
        const GPIOPullConfiguration pullConfiguration = GPIOPullConfiguration::Floating,
        const GPIOOutputConfiguration outputConfiguration = GPIOOutputConfiguration::PushPull,
        const GPIOOutputSpeed outputSpeed = GPIOOutputSpeed::Low_2MHz,
        const GPIOAlternateFunction alternateFunction = GPIOAlternateFunction::AF_SYS)
    {
        palSetPadMode(port, pin, mode | pullConfiguration |
                                 outputConfiguration | outputSpeed |
                                 PAL_STM32_ALTERNATE(alternateFunction));
    }

protected:
    const Port mPort;
    const uint8_t mPin;
};

}
}
