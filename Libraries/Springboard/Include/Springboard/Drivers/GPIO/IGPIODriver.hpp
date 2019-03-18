#pragma once

#include "Springboard/Drivers/ITypeSpecificDriver.hpp"

namespace Springboard {
namespace Drivers {

class IDriverLookup;

namespace GPIO {

class IGPIODriverFactory;

enum class DriverType_t : uint32_t {
    InternalGPIO,
};

struct DriverConfig_t {
    DriverType_t type;
    void* driverSpecificConfig;
};

class IGPIODriver : public ITypeSpecificDriver<DriverConfig_t, IGPIODriverFactory>
{
public:
    virtual Springboard::Error_t ConfigureDriver(DriverConfig_t* config,
                                                 IGPIODriverFactory* factory) = 0;
};

}
}
}
