#include <Springboard/ExternalHAL/PCF8574.hpp>

#if SPRINGBOARD_HAL_ENABLE_I2C

namespace Springboard {
namespace ExternalHAL {

PCF8574::PCF8574(Springboard::InternalHAL::I2CBusBase* bus, const Address address,
                 const Speed speed)
    : Springboard::InternalHAL::I2CDevice(bus, address, speed)
{
    ASSERT(address >= 0x20 && address <= 0x27);
}

uint8_t PCF8574::ReadPort()
{
    uint8_t inputs;
    Receive(&inputs, 1);
    return inputs;
}

void PCF8574::WritePort(uint8_t outputs)
{
    Transmit(&outputs, 1);
}

}
}

#endif // #if SPRINGBOARD_HAL_ENABLE_I2C
