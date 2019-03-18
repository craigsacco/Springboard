#pragma once

#include "Springboard/Devices/IDevice.hpp"
#include "Springboard/Drivers/GPIO/IGPIODriver.hpp"

namespace Springboard {

namespace Drivers {
namespace GPIO {
class IGPIODriver;
}
}

namespace Devices {

class GPIODevice : public IDevice
{
public:
    GPIODevice();
    Springboard::Error_t ConfigureDevice(DeviceConfig_t& config) override final;
    Springboard::Drivers::IDriver* GetDriver() const override final;
    const DeviceConfig_t* GetDeviceConfig() const override final;

protected:
    Springboard::Drivers::GPIO::IGPIODriver* mDriver;
    const DeviceConfig_t* mDeviceConfig;
};

}
}
