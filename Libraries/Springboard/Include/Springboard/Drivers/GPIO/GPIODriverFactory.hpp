#pragma once

#include "Springboard/Drivers/GPIO/IGPIODriverFactory.hpp"

namespace Springboard {
namespace Drivers {
namespace GPIO {

class GPIODriverFactory : public IGPIODriverFactory
{
public:
    GPIODriverFactory();
    IGPIODriver* CreateDriver(GPIODriverConfig_t& config) override final;
};

}
}
}
