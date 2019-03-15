#pragma once

#include "Springboard/Devices/DeviceFactory.hpp"
#include "Springboard/Drivers/GPIO/GPIODriverFactory.hpp"
#include "Springboard/Devices/DeviceRegistry.hpp"

namespace Springboard {
namespace Devices {

class DeviceBootstrapper
{
public:
    DeviceBootstrapper();

    DeviceRegistry& GetDeviceRegistry()
    {
        return mDeviceRegistry;
    }

private:
    DeviceFactory mDeviceFactory {};
    Springboard::Drivers::GPIO::GPIODriverFactory mGPIODriverFactory {};
    DeviceRegistry mDeviceRegistry { mDeviceFactory, mGPIODriverFactory };
};

}
}
