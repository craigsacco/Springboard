#pragma once

#include "Springboard/Drivers/GPIO/BaseGPIODriver.hpp"
#include "Springboard/Drivers/GPIO/InternalGPIODriverConfig.hpp"
#include "stm32f4xx_gpio.h"

namespace Springboard {
namespace Drivers {
namespace GPIO {

class InternalGPIODriver : public BaseGPIODriver
{
public:
    InternalGPIODriver();
    Springboard::Error_t ConfigureDriver(GPIODriverConfig_t& config, Springboard::Drivers::IDriverLookup& lookup) override final;
    GPIO_TypeDef* GetGPIO() const;

private:
    GPIO_TypeDef* mGPIO;

private:
    struct InternalGPIOStaticInfoRecord_t {
        InternalGPIODriverConfig_t::Port_t port;
        GPIO_TypeDef* gpio;
        uint32_t rccEnable;
    };
};

}
}
}
