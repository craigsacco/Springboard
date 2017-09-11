#pragma once

#include <Springboard/InternalHAL/I2CDevice.hpp>

//#if SPRINGBOARD_HAL_ENABLE_I2C

namespace Springboard {

namespace ExternalHAL {

class PCF8574 : public Springboard::InternalHAL::I2CDevice
{
    PCF8574(Springboard::InternalHAL::I2CBus* bus, const Address address);

    uint8_t ReadPort();
    void WritePort(uint8_t outputs);
};

}
}

//#endif // SPRINGBOARD_HAL_ENABLE_I2C
