#pragma once

#include <Springboard/CommonHAL/IDigitalOutput.hpp>
#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <hal.h>

namespace Springboard {
namespace InternalHAL {

class DigitalOutput : public Springboard::CommonHAL::IDigitalOutput
{
public:
    typedef ioportid_t Port;

    DigitalOutput(const Port port, const uint8_t pin,
                  const GPIOPullConfiguration pullConfiguration,
                  const GPIOOutputConfiguration outputConfiguration,
                  const GPIOOutputSpeed outputSpeed)
        : mPort(port), mPin(pin)
    {
        palSetPadMode(port, pin, PAL_STM32_MODE_OUTPUT | pullConfiguration |
                                 outputConfiguration | outputSpeed);
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

private:
    const Port mPort;
    const uint8_t mPin;
};

}
}
