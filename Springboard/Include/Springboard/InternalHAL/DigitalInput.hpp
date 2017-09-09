#pragma once

#include <Springboard/Common.hpp>
#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <hal.h>

namespace Springboard {
namespace InternalHAL {

class IDigitalInput
{
public:
    virtual bool Get() const = 0;
};

class DigitalInput : public IDigitalInput
{
public:
    typedef ioportid_t Port;

    DigitalInput(const Port port, const uint8_t pin,
                 const PullConfiguration pullConfiguration)
        : mPort(port), mPin(pin)
    {
        palSetPadMode(port, pin, PAL_STM32_MODE_INPUT | pullConfiguration);
    }

    bool Get() const override final
    {
        return palReadPad(mPort, mPin);
    }

private:
    const Port mPort;
    const uint8_t mPin;
};

}
}
