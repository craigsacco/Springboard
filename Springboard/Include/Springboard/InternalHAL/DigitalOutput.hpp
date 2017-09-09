#pragma once

#include <Springboard/Common.hpp>
#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <hal.h>

namespace Springboard {
namespace InternalHAL {

class IDigitalOutput
{
public:
    virtual bool Get() const = 0;
    virtual void Set(bool state = true) = 0;
    virtual void Clear() = 0;
    virtual void Toggle() = 0;
};

class DigitalOutput : public IDigitalOutput
{
public:
    typedef ioportid_t Port;

    DigitalOutput(const Port port, const uint8_t pin,
                  const PullConfiguration pullConfiguration,
                  const OutputConfiguration outputConfiguration,
                  const OutputSpeed outputSpeed)
        : mPort(port), mPin(pin)
    {
        palSetPadMode(port, pin, PAL_STM32_MODE_OUTPUT | pullConfiguration |
                                 outputConfiguration | outputSpeed);
    }

    bool Get() const override final
    {
        return palReadLatch(mPort) & (1UL << mPin);
    }

    void Set(bool state = true) override final
    {
        palWritePad(mPort, mPin, state);
    }

    void Clear() override final
    {
        palClearPad(mPort, mPin);
    }

    void Toggle() override final
    {
        palTogglePad(mPort, mPin);
    }

private:
    const Port mPort;
    const uint8_t mPin;
};

}
}
