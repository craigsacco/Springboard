#include "Springboard/Devices/DeviceFactory.hpp"
#include "Springboard/Devices/GPIODevice.hpp"

namespace Springboard {
namespace Devices {

DeviceFactory::DeviceFactory(Springboard::Drivers::GPIO::IGPIODriverFactory& gpioDriverFactory)
    : mGPIODriverFactory(gpioDriverFactory)
{
}

IDevice* DeviceFactory::CreateDevice(DeviceConfig_t& config) const
{
    switch (config.type) {
        case Springboard::DeviceType_t::GPIO:
            return new Springboard::Devices::GPIODevice(mGPIODriverFactory);
        default:
            return nullptr;
    }
}

}
}
