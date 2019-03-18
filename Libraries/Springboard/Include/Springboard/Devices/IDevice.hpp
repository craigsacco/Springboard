#pragma once

#include "Springboard/Common/SpringboardCommon.hpp"
#include "Springboard/Devices/DeviceConfig.hpp"

namespace Springboard {

namespace Drivers {
class IDriver;
}

namespace Devices {

class IDeviceFactory;

class IDevice
{
public:
    virtual Error_t ConfigureDevice(DeviceConfig_t& config) = 0;
    virtual Springboard::Drivers::IDriver* GetDriver() const = 0;
    virtual const DeviceConfig_t* GetDeviceConfig() const = 0;
};

}
}
