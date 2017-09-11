#include <Springboard/ExternalHAL/PCF8574.hpp>

namespace Springboard {
namespace ExternalHAL {

PCF8574::PCF8574(Springboard::InternalHAL::I2CBus* bus, const Address address,
                 const Speed speed)
    : Springboard::InternalHAL::I2CDevice(bus, address, speed)
{
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
