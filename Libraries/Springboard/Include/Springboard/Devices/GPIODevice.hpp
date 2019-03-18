#pragma once

#include "Springboard/Devices/IDevice.hpp"
#include "Springboard/Drivers/GPIO/IGPIODriver.hpp"

namespace Springboard {

namespace Drivers {
namespace GPIO {
class IGPIODriver;
class IGPIODriverFactory;
}
}

namespace Devices {

class GPIODevice : public IDevice
{
public:
    GPIODevice(Springboard::Drivers::GPIO::IGPIODriverFactory& driverFactory);
    Springboard::Error_t ConfigureDevice(DeviceConfig_t& config, Springboard::Drivers::IDriverLookup& lookup) override final;
    Springboard::Drivers::IDriver* GetDriver() const override final;
    const DeviceConfig_t* GetDeviceConfig() const override final;

protected:
    Springboard::Drivers::GPIO::IGPIODriverFactory& mDriverFactory;
    Springboard::Drivers::GPIO::IGPIODriver* mDriver;
    const DeviceConfig_t* mDeviceConfig;
};

}
}
