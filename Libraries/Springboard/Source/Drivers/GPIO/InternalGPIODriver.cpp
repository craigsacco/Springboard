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

Springboard::Error_t InternalGPIODriver::InitialiseDriver(Springboard::Drivers::IDriverLookup* lookup,
                                                          DriverConfig_t* config)
{
    if (config->type != DriverType_t::InternalGPIO) {
        return RAISE_ERROR(Springboard::Error_t::InvalidDriverType, "Attempted to configure InternalGPIO using wrong config");
    }

    DriverSpecificConfig_t* driverConfig = reinterpret_cast<DriverSpecificConfig_t*>(config->driverSpecificConfig);

    static constexpr InternalGPIOStaticInfoRecord_t records[11] = {
        { InternalGPIODriver::GPIOPort_t::A, GPIOA, RCC_AHB1Periph_GPIOA },
        { InternalGPIODriver::GPIOPort_t::B, GPIOB, RCC_AHB1Periph_GPIOB },
        { InternalGPIODriver::GPIOPort_t::C, GPIOC, RCC_AHB1Periph_GPIOC },
        { InternalGPIODriver::GPIOPort_t::D, GPIOD, RCC_AHB1Periph_GPIOD },
        { InternalGPIODriver::GPIOPort_t::E, GPIOE, RCC_AHB1Periph_GPIOE },
        { InternalGPIODriver::GPIOPort_t::F, GPIOF, RCC_AHB1Periph_GPIOF },
        { InternalGPIODriver::GPIOPort_t::G, GPIOG, RCC_AHB1Periph_GPIOG },
        { InternalGPIODriver::GPIOPort_t::H, GPIOH, RCC_AHB1Periph_GPIOH },
        { InternalGPIODriver::GPIOPort_t::I, GPIOI, RCC_AHB1Periph_GPIOI },
        { InternalGPIODriver::GPIOPort_t::J, GPIOJ, RCC_AHB1Periph_GPIOJ },
        { InternalGPIODriver::GPIOPort_t::K, GPIOK, RCC_AHB1Periph_GPIOK },
    };
    for (auto& record : records) {
        if (record.port == driverConfig->port) {
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
