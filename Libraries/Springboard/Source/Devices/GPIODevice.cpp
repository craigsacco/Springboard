#include "Springboard/Devices/GPIODevice.hpp"
#include "Springboard/Drivers/GPIO/IGPIODriver.hpp"
#include "Springboard/Drivers/GPIO/GPIODriverFactory.hpp"

namespace Springboard {
namespace Devices {

GPIODevice::GPIODevice(Springboard::Drivers::GPIO::IGPIODriverFactory& driverFactory)
    : IDevice()
    , mDriverFactory(driverFactory)
    , mDriver(nullptr)
    , mDeviceConfig(nullptr)
{
}

Springboard::Error_t GPIODevice::ConfigureDevice(DeviceConfig_t& config, Springboard::Drivers::IDriverLookup& lookup)
{
    if (config.type != Springboard::DeviceType_t::GPIO) {
        return RAISE_ERROR(Springboard::Error_t::InvalidDeviceType, "Attempted to configure the wrong device type");
    }

    Springboard::Drivers::GPIO::GPIODriverConfig_t* driverConfig = reinterpret_cast<Springboard::Drivers::GPIO::GPIODriverConfig_t*>(config.driverConfig);
    Springboard::Drivers::GPIO::IGPIODriver* driver = mDriverFactory.CreateDriver(*driverConfig);
    if (mDriver == nullptr) {
        return RAISE_ERROR(Springboard::Error_t::DriverNotCreated, "Could not create driver from device configuration");
    }

    Springboard::Error_t result = driver->ConfigureDriver(*driverConfig, lookup);
    if (result != Springboard::Error_t::Success) {
        return result;
    }

    mDeviceConfig = &config;
    mDriver = driver;
    return Springboard::Error_t::Success;
}

Springboard::Drivers::IDriver* GPIODevice::GetDriver() const
{
    return mDriver;
}

const DeviceConfig_t* GPIODevice::GetDeviceConfig() const
{
    return mDeviceConfig;
}

}
}
