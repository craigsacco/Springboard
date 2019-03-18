#pragma once

#include "Springboard/Devices/IDeviceFactory.hpp"

namespace Springboard {
namespace Devices {

class DeviceFactory : public IDeviceFactory
{
public:
    DeviceFactory();
    IDevice* CreateDevice(DeviceConfig_t& config) const override final;
};

}
}
