#pragma once

#include "Springboard/Common/SpringboardCommon.hpp"

namespace Springboard {

namespace Drivers {
class IDriver;
}

namespace Devices {

struct DeviceConfig_t {
    Springboard::DeviceId_t id;
    Springboard::DeviceType_t type;
    const char* name;
    void* driverConfig;
};

class IDevice
{
public:
    virtual Error_t Configure(DeviceConfig_t& config) = 0;
    virtual Springboard::Drivers::IDriver* GetDriver() const = 0;
    virtual const DeviceConfig_t* GetDeviceConfig() const = 0;
};

}
}
