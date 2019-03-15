#pragma once

#include "Springboard/Devices/IDeviceRegistry.hpp"
#include "Springboard/Drivers/IDriverLookup.hpp"
#include "Springboard/Drivers/GPIO/IGPIODriverFactory.hpp"

namespace Springboard {
namespace Devices {

class IDeviceFactory;

class DeviceRegistry : public IDeviceRegistry, public Springboard::Drivers::IDriverLookup
{
public:
    DeviceRegistry(IDeviceFactory& deviceFactory,
                   Springboard::Drivers::GPIO::IGPIODriverFactory& gpioDriverFactory);
    Springboard::Error_t CreateDevices(DeviceConfig_t configs[], size_t deviceCount) override final;
    IDevice* GetDeviceById(DeviceId_t id) const override final;
    Springboard::Drivers::IDriver* GetDriverByDeviceId(Springboard::DeviceId_t id) const override final;

private:
    IDeviceFactory* mDeviceFactory;
    Springboard::Drivers::GPIO::IGPIODriverFactory* mGPIODriverFactory;
    IDevice** mDevices;
    size_t mDeviceCount;
};

}
}
