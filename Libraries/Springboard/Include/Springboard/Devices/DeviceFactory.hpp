#pragma once

#include "Springboard/Devices/IDeviceFactory.hpp"
#include "Springboard/Drivers/GPIO/IGPIODriverFactory.hpp"

namespace Springboard {

namespace Drivers {
namespace GPIO {
class IGPIODriverFactory;
}
}

namespace Devices {

class DeviceFactory : public IDeviceFactory
{
public:
    DeviceFactory(Springboard::Drivers::GPIO::IGPIODriverFactory& gpioDriverFactory);
    IDevice* CreateDevice(DeviceConfig_t& config) const override final;

private:
    Springboard::Drivers::GPIO::IGPIODriverFactory& mGPIODriverFactory;
};

}
}
