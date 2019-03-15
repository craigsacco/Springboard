#include "Springboard/Devices/DeviceFactory.hpp"
#include "Springboard/Devices/GPIODevice.hpp"

namespace Springboard {
namespace Devices {

DeviceFactory::DeviceFactory()
{
}

IDevice* DeviceFactory::CreateDevice(DeviceConfig_t& config)
{
    switch (config.type) {
        case Springboard::DeviceType_t::GPIO:
            return new GPIODevice();
        default:
            return nullptr;
    }
}

}
}
