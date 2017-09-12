/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#include <Springboard/CommonHAL/IDigitalInput.hpp>
#include <Springboard/InternalHAL/InternalGPIOPin.hpp>

namespace Springboard {
namespace InternalHAL {

class DigitalInput : public InternalGPIOPin,
                     public Springboard::CommonHAL::IDigitalInput
{
public:
    DigitalInput(const Port port, const uint8_t pin,
                 const GPIOPullConfiguration pullConfiguration)
        : InternalGPIOPin(port, pin)
    {
        SetPinConfiguration(port, pin, GPIOPinMode::Input, pullConfiguration);
    }

    inline bool Get() const final
    {
        return palReadPad(mPort, mPin);
    }
};

}  // namespace InternalHAL
}  // namespace Springboard
