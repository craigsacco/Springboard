#pragma once

#include <Springboard/InternalHAL/I2CDevice.hpp>

#if SPRINGBOARD_HAL_ENABLE_I2C

namespace Springboard {

namespace ExternalHAL {

class PCF8574 : public Springboard::InternalHAL::I2CDevice
{
public:
    PCF8574(Springboard::InternalHAL::I2CBusBase* bus, const Address address,
            const Speed speed);

    uint8_t ReadPort();
    void WritePort(uint8_t outputs);
};

}
}

#endif // SPRINGBOARD_HAL_ENABLE_I2C
