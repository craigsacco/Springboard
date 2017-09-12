/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#include <Springboard/CommonHAL/IDigitalOutput.hpp>
#include <Springboard/InternalHAL/InternalGPIOPin.hpp>

namespace Springboard {
namespace InternalHAL {

class DigitalOutput : public InternalGPIOPin,
                      public Springboard::CommonHAL::IDigitalOutput
{
public:
    DigitalOutput(const Port port, const uint8_t pin,
                  const GPIOPullConfiguration pullConfiguration,
                  const GPIOOutputConfiguration outputConfiguration,
                  const GPIOOutputSpeed outputSpeed)
        : InternalGPIOPin(port, pin)
    {
        SetPinConfiguration(port, pin, GPIOPinMode::Output, pullConfiguration,
                            outputConfiguration, outputSpeed);
    }

    inline bool Get() const final
    {
        return palReadLatch(mPort) & (1UL << mPin);
    }

    inline void Set(bool state = true) final
    {
        palWritePad(mPort, mPin, state);
    }

    inline void Clear() final
    {
        palClearPad(mPort, mPin);
    }

    inline void Toggle() final
    {
        palTogglePad(mPort, mPin);
    }
};

}  // namespace InternalHAL
}  // namespace Springboard
