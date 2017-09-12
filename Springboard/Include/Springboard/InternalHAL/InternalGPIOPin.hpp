/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

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
        const GPIOPullConfiguration pullConfiguration =
            GPIOPullConfiguration::Floating,
        const GPIOOutputConfiguration outputConfiguration =
            GPIOOutputConfiguration::PushPull,
        const GPIOOutputSpeed outputSpeed = GPIOOutputSpeed::Low_2MHz)
    {
        palSetPadMode(port, pin, mode | pullConfiguration |
                                 outputConfiguration | outputSpeed);
    }

protected:
    const Port mPort;
    const uint8_t mPin;
};

}  // namespace InternalHAL
}  // namespace Springboard
