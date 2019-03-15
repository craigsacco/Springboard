#pragma once

#include "Springboard/Drivers/GPIO/IGPIODriver.hpp"

namespace Springboard {
namespace Drivers {
namespace GPIO {

class IGPIODriverFactory
{
public:
    virtual IGPIODriver* CreateDriver(DriverConfig_t* config) = 0;
};

}
}
}
