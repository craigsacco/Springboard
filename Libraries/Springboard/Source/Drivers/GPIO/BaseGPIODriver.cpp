#pragma once

#include "Springboard/Drivers/GPIO/BaseGPIODriver.hpp"

namespace Springboard {
namespace Drivers {
namespace GPIO {

BaseGPIODriver::BaseGPIODriver()
    : mConfig(nullptr)
{
}

const DriverConfig_t* BaseGPIODriver::GetDriverConfig() const
{
    return mConfig;
}

Springboard::DeviceType_t BaseGPIODriver::GetDeviceType() const
{
    return Springboard::DeviceType_t::GPIO;
}

Springboard::UnderlyingDriverType_t BaseGPIODriver::GetDriverType() const
{
    return static_cast<Springboard::UnderlyingDriverType_t>(mConfig->type);
}

Springboard::Error_t BaseGPIODriver::Configure(Springboard::Drivers::IDriverLookup* lookup,
                                               DriverConfig_t* config)
{
    Springboard::Error_t result = InitialiseDriver(lookup, config);
    if (result != Springboard::Error_t::Success) {
        return result;
    }

    mConfig = config;
    return Springboard::Error_t::Success;
}

}
}
}
