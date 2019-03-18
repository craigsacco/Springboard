#include "Springboard/Devices/GPIODevice.hpp"
#include "Springboard/Drivers/GPIO/IGPIODriver.hpp"

namespace Springboard {
namespace Devices {

GPIODevice::GPIODevice()
    : IDevice()
    , mDriver(nullptr)
    , mDeviceConfig(nullptr)
{
}

Springboard::Error_t GPIODevice::ConfigureDevice(DeviceConfig_t& config)
{
    if (config.type != Springboard::DeviceType_t::GPIO) {
        return RAISE_ERROR(Springboard::Error_t::InvalidDeviceType, "Attempted to configure the wrong device type");
    }

    // TODO: create driver

    // Springboard::Drivers::GPIO::DriverConfig* driverConfig = reinterpret_cast<Springboard::Drivers::GPIO::DriverConfig*>(config.driverConfig);
    // Springboard::Drivers::GPIO::IGPIODriver* driver = 

    // mDriver = Springboard::Drivers::GPIO::GPIODriverFactory::CreateDriver(driverConfig);
    // if (mDriver == nullptr) {
    //     return RAISE_ERROR(Springboard::Error_t::DriverNotCreated, "Could not create driver from device configuration");
    // }

    
    // return mDriver->Configure(driverConfig);

    mDeviceConfig = &config;
    mDriver = nullptr;  // TODO: use real driver ptr
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
