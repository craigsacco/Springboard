#pragma once

#include "Springboard/Devices/IDevice.hpp"

namespace Springboard {
namespace Devices {

class IDeviceFactory
{
public:
    virtual IDevice* CreateDevice(DeviceConfig_t& config) = 0;
};

}
}
