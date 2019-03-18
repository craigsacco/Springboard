#pragma once

#include "Springboard/Devices/IDevice.hpp"

namespace Springboard {

namespace Drivers {
namespace GPIO {
class IGPIODriverFactory;
}
}

namespace Devices {

class IDeviceFactory
{
public:
    virtual IDevice* CreateDevice(DeviceConfig_t& config) const = 0;
};

}
}
