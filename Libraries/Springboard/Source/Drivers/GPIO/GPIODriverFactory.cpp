#include "Springboard/Drivers/GPIO/GPIODriverFactory.hpp"
#include "Springboard/Drivers/GPIO/InternalGPIODriver.hpp"

namespace Springboard {
namespace Drivers {
namespace GPIO {

GPIODriverFactory::GPIODriverFactory()
{
}

IGPIODriver* GPIODriverFactory::CreateDriver(GPIODriverConfig_t& config)
{
    switch (config.type) {
        case GPIODriverConfig_t::Type_t::InternalGPIO:
            return new InternalGPIODriver();
        default:
            return nullptr;
    }
}

}
}
}
