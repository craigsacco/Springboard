#pragma once

#include "Springboard/Devices/DeviceBootstrapper.hpp"

namespace Springboard {
namespace Devices {

DeviceBootstrapper::DeviceBootstrapper()
{
}

IDeviceRegistry& DeviceBootstrapper::GetDeviceRegistry()
{
    return mDeviceRegistry;
}

}
}
