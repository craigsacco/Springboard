#include "Springboard/Drivers/GPIO/GPIODriverFactory.hpp"
#include "Springboard/Drivers/GPIO/InternalGPIODriver.hpp"

namespace Springboard {
namespace Drivers {
namespace GPIO {

GPIODriverFactory::GPIODriverFactory()
{
}

IGPIODriver* GPIODriverFactory::CreateDriver(DriverConfig_t* config)
{
    switch (config->type) {
        // case DriverType_t::InternalGPIO:
        //     return new InternalGPIODriver();
        default:
            return nullptr;
    }
}

}
}
}
