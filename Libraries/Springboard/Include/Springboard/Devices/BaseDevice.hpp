#pragma once

#include "Springboard/Devices/IDevice.hpp"

namespace Springboard {

namespace Devices {

template <Springboard::DeviceType_t DeviceType, typename TDriverInterfaceType, typename TDriverConfigType>
class BaseDevice : public IDevice
{
public:
    BaseDevice()
        : mDriver(nullptr)
        , mDeviceConfig(nullptr)
    {
    }

    Springboard::Error_t Configure(DeviceConfig_t& config) override final
    {
        if (config.type != DeviceType) {
            return RAISE_ERROR(Springboard::Error_t::InvalidDeviceType, "Attempted to configure device using wrong config");
        }

        mDeviceConfig = &config;

        return InitialiseDriver(reinterpret_cast<TDriverConfigType*>(config.driverConfig));
    }

    Springboard::Drivers::IDriver* GetDriver() const override final
    {
        return mDriver;
    }

    const DeviceConfig_t* GetDeviceConfig() const override final
    {
        return mDeviceConfig;
    }

protected:
    virtual Springboard::Error_t InitialiseDriver(TDriverConfigType* driverConfig) = 0;

protected:
    TDriverInterfaceType* mDriver;
    const DeviceConfig_t* mDeviceConfig;
};

}
}
