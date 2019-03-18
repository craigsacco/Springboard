#pragma once

#include "Springboard/Drivers/IDriver.hpp"
#include "Springboard/Drivers/GPIO/GPIODriverConfig.hpp"

namespace Springboard {
namespace Drivers {

class IDriverLookup;

namespace GPIO {

class IGPIODriver : public IDriver
{
public:
    virtual Springboard::Error_t ConfigureDriver(GPIODriverConfig_t& config, Springboard::Drivers::IDriverLookup& lookup) = 0;
    virtual const GPIODriverConfig_t* GetDriverConfig() const = 0;
};

}
}
}
