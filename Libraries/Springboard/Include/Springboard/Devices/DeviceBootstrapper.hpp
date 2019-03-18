#pragma once

#include "Springboard/Devices/DeviceFactory.hpp"
#include "Springboard/Devices/DeviceRegistry.hpp"
#include "Springboard/Drivers/GPIO/GPIODriverFactory.hpp"

namespace Springboard {
namespace Devices {

class DeviceBootstrapper
{
public:
    DeviceBootstrapper();
    IDeviceRegistry& GetDeviceRegistry();

private:
    Springboard::Drivers::GPIO::GPIODriverFactory mGPIODriverFactory {};
    DeviceFactory mDeviceFactory { mGPIODriverFactory };
    DeviceRegistry mDeviceRegistry { mDeviceFactory };
};

}
}
