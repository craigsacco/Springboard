#pragma once

#include "Springboard/Devices/BaseDevice.hpp"
#include "Springboard/Drivers/GPIO/IGPIODriver.hpp"

namespace Springboard {
namespace Devices {

class GPIODevice : public BaseDevice<Springboard::DeviceType_t::GPIO,
                                     Springboard::Drivers::GPIO::IGPIODriver,
                                     Springboard::Drivers::GPIO::DriverConfig_t>
{
public:
    GPIODevice();
    Springboard::Error_t InitialiseDriver(Springboard::Drivers::GPIO::DriverConfig_t* driverConfig) override final;
};

}
}
