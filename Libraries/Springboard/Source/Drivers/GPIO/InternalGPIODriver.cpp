#include "Springboard/Drivers/GPIO/InternalGPIODriver.hpp"
#include "stm32f4xx.h"

namespace Springboard {
namespace Drivers {
namespace GPIO {

InternalGPIODriver::InternalGPIODriver()
    : BaseGPIODriver()
    , mGPIO(nullptr)
{
}

Springboard::Error_t InternalGPIODriver::ConfigureDriver(GPIODriverConfig_t& config, Springboard::Drivers::IDriverLookup& lookup)
{
    if (config.type != GPIODriverConfig_t::Type_t::InternalGPIO) {
        return RAISE_ERROR(Springboard::Error_t::InvalidDriverType, "Attempted to configure InternalGPIO using wrong config");
    }

    InternalGPIODriverConfig_t* driverSpecificConfig = reinterpret_cast<InternalGPIODriverConfig_t*>(config.driverSpecificConfig);

    static constexpr InternalGPIOStaticInfoRecord_t records[11] = {
        { InternalGPIODriverConfig_t::Port_t::A, GPIOA, RCC_AHB1Periph_GPIOA },
        { InternalGPIODriverConfig_t::Port_t::B, GPIOB, RCC_AHB1Periph_GPIOB },
        { InternalGPIODriverConfig_t::Port_t::C, GPIOC, RCC_AHB1Periph_GPIOC },
        { InternalGPIODriverConfig_t::Port_t::D, GPIOD, RCC_AHB1Periph_GPIOD },
        { InternalGPIODriverConfig_t::Port_t::E, GPIOE, RCC_AHB1Periph_GPIOE },
        { InternalGPIODriverConfig_t::Port_t::F, GPIOF, RCC_AHB1Periph_GPIOF },
        { InternalGPIODriverConfig_t::Port_t::G, GPIOG, RCC_AHB1Periph_GPIOG },
        { InternalGPIODriverConfig_t::Port_t::H, GPIOH, RCC_AHB1Periph_GPIOH },
        { InternalGPIODriverConfig_t::Port_t::I, GPIOI, RCC_AHB1Periph_GPIOI },
        { InternalGPIODriverConfig_t::Port_t::J, GPIOJ, RCC_AHB1Periph_GPIOJ },
        { InternalGPIODriverConfig_t::Port_t::K, GPIOK, RCC_AHB1Periph_GPIOK },
    };
    for (auto& record : records) {
        if (record.port == driverSpecificConfig->port) {
            RCC_AHB1PeriphClockCmd(record.rccEnable, ENABLE);
            mGPIO = record.gpio;
            return Springboard::Error_t::Success;
        }
    }

    // if it got here, the driver wasn't configured correctly
    return RAISE_ERROR(Springboard::Error_t::InvalidDriverConfig, "GPIO port was invalid");
}

GPIO_TypeDef* InternalGPIODriver::GetGPIO() const
{
    return mGPIO;
}

}
}
}
