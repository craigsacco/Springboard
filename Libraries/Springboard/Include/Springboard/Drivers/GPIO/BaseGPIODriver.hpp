#pragma once

#include "Springboard/Drivers/GPIO/IGPIODriver.hpp"

namespace Springboard {
namespace Drivers {
namespace GPIO {

class BaseGPIODriver : public IGPIODriver
{
public:
    BaseGPIODriver();
    const DriverConfig_t* GetDriverConfig() const override final;
    Springboard::DeviceType_t GetDeviceType() const override final;
    Springboard::UnderlyingDriverType_t GetDriverType() const override final;

protected:
    const DriverConfig_t* mConfig;
};

}
}
}
