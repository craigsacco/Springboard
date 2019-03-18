#pragma once

#include "Springboard/Common/SpringboardCommon.hpp"
#include "Springboard/Devices/DeviceConfig.hpp"

namespace Springboard {

namespace Drivers {
class IDriver;
class IDriverLookup;
}

namespace Devices {

class IDeviceFactory;

class IDevice
{
public:
    virtual Error_t ConfigureDevice(DeviceConfig_t& config, Springboard::Drivers::IDriverLookup& lookup) = 0;
    virtual Springboard::Drivers::IDriver* GetDriver() const = 0;
    virtual const DeviceConfig_t* GetDeviceConfig() const = 0;
};

}
}
