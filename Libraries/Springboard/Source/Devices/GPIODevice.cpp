#include "Springboard/Devices/GPIODevice.hpp"
#include "Springboard/Drivers/GPIO/GPIODriverFactory.hpp"

namespace Springboard {
namespace Devices {

GPIODevice::GPIODevice()
    : BaseDevice<Springboard::DeviceType_t::GPIO,
                 Springboard::Drivers::GPIO::IGPIODriver,
                 Springboard::Drivers::GPIO::DriverConfig_t>()
{
}

Springboard::Error_t GPIODevice::InitialiseDriver(Springboard::Drivers::GPIO::DriverConfig_t* driverConfig)
{
    mDriver = Springboard::Drivers::GPIO::GPIODriverFactory::CreateDriver(driverConfig);
    if (mDriver == nullptr) {
        return RAISE_ERROR(Springboard::Error_t::DriverNotCreated, "Could not create driver from device configuration");
    }

    return mDriver->Configure(driverConfig);
}

}
}
