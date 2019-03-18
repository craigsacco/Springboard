#pragma once

#include "Springboard/Devices/DeviceFactory.hpp"
#include "Springboard/Devices/DeviceRegistry.hpp"

namespace Springboard {
namespace Devices {

class DeviceBootstrapper
{
public:
    DeviceBootstrapper();
    IDeviceRegistry& GetDeviceRegistry();

private:
    DeviceFactory mDeviceFactory {};
    DeviceRegistry mDeviceRegistry { mDeviceFactory };
};

}
}
