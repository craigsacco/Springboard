#include "Springboard/Drivers/GPIO/BaseGPIODriver.hpp"

namespace Springboard {
namespace Drivers {
namespace GPIO {

BaseGPIODriver::BaseGPIODriver()
    : mConfig(nullptr)
{
}

const GPIODriverConfig_t* BaseGPIODriver::GetDriverConfig() const
{
    return mConfig;
}

Springboard::DeviceType_t BaseGPIODriver::GetDeviceType() const
{
    return Springboard::DeviceType_t::GPIO;
}

Springboard::UnderlyingDriverType_t BaseGPIODriver::GetDriverType() const
{
    ASSERT(mConfig != nullptr, "mConfig is nullptr");
    return static_cast<Springboard::UnderlyingDriverType_t>(mConfig->type);
}

}
}
}
