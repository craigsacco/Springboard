#pragma once

#include "Springboard/Devices/IDevice.hpp"
#include <cstddef>

namespace Springboard {
namespace Devices {

class IDeviceRegistry
{
public:
    virtual Springboard::Error_t CreateDevices(DeviceConfig_t configs[], size_t size) = 0;
    virtual IDevice* GetDeviceById(DeviceId_t id) const = 0;
};

}
}
