#pragma once

#include "Springboard/Devices/IDeviceRegistry.hpp"
//#include "Springboard/Drivers/IDriverLookup.hpp"

namespace Springboard {
namespace Devices {

class IDeviceFactory;

class DeviceRegistry : public IDeviceRegistry
{
public:
    DeviceRegistry(IDeviceFactory& deviceFactory);
    Springboard::Error_t CreateDevices(DeviceConfig_t configs[], size_t deviceCount) override final;
    IDevice* GetDeviceById(DeviceId_t id) const override final;

private:
    IDeviceFactory* mDeviceFactory;
    IDevice** mDevices;
    size_t mDeviceCount;
};

}
}
