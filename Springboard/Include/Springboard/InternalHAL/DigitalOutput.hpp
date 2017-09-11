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
        SetPinConfiguration(port, pin, GPIOPinMode::Input, pullConfiguration,
                            outputConfiguration, outputSpeed);
    }

    inline bool Get() const override final
    {
        return palReadLatch(mPort) & (1UL << mPin);
    }

    inline void Set(bool state = true) override final
    {
        palWritePad(mPort, mPin, state);
    }

    inline void Clear() override final
    {
        palClearPad(mPort, mPin);
    }

    inline void Toggle() override final
    {
        palTogglePad(mPort, mPin);
    }
};

}
}
