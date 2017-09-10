#pragma once

#include <Springboard/CommonHAL/IDigitalInput.hpp>
#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <hal.h>

namespace Springboard {
namespace InternalHAL {

class DigitalInput : public Springboard::CommonHAL::IDigitalInput
{
public:
    typedef ioportid_t Port;

    DigitalInput(const Port port, const uint8_t pin,
                 const GPIOPullConfiguration pullConfiguration)
        : mPort(port), mPin(pin)
    {
        palSetPadMode(port, pin, PAL_STM32_MODE_INPUT | pullConfiguration);
    }

    inline bool Get() const override final
    {
        return palReadPad(mPort, mPin);
    }

private:
    const Port mPort;
    const uint8_t mPin;
};

}
}
