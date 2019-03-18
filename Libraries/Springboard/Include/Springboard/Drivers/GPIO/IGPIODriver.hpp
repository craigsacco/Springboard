#pragma once

#include "Springboard/Drivers/IDriver.hpp"

namespace Springboard {
namespace Drivers {

class IDriverLookup;

namespace GPIO {

enum class DriverType_t : uint32_t {
    InternalGPIO,
};

struct DriverConfig_t {
    DriverType_t type;
    void* driverSpecificConfig;
};

class IGPIODriver : public IDriver
{
public:
    virtual Springboard::Error_t ConfigureDriver(DriverConfig_t* config) = 0;
    virtual const DriverConfig_t* GetDriverConfig() const = 0;
};

}
}
}
