#pragma once

#include "Springboard/Drivers/ITypeSpecificDriver.hpp"

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

class IGPIODriver : public ITypeSpecificDriver<DriverConfig_t>
{
public:
    virtual Springboard::Error_t Configure(Springboard::Drivers::IDriverLookup* lookup,
                                           DriverConfig_t* config) = 0;
};

}
}
}
