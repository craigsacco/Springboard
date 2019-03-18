#include "Springboard/Devices/DeviceRegistry.hpp"
#include "Springboard/Devices/IDeviceFactory.hpp"

namespace Springboard {
namespace Devices {

DeviceRegistry::DeviceRegistry(IDeviceFactory& deviceFactory)
    : mDeviceFactory(&deviceFactory)
    , mDevices(nullptr)
    , mDeviceCount(0)
{
}

Springboard::Error_t  DeviceRegistry::CreateDevices(DeviceConfig_t configs[], size_t deviceCount)
{
    mDevices = new IDevice*[deviceCount];

    Springboard::Error_t result;

    for (size_t i = 0; i < deviceCount; i++) {
        DeviceConfig_t& config = configs[i];
        if (GetDeviceById(config.id) != nullptr) {
            return RAISE_ERROR(Springboard::Error_t::DuplicateDeviceId, "Device ID %u is a duplicate", config.id);
        }
        mDevices[i] = mDeviceFactory->CreateDevice(config);
        if (mDevices[i] == nullptr) {
            return RAISE_ERROR(Springboard::Error_t::DeviceNotCreated, "Could not create device from configuration");
        }
        result = mDevices[i]->ConfigureDevice(config);
        if (result != Springboard::Error_t::Success) {
            return result;
        }
        mDeviceCount++;
    }

    return Springboard::Error_t::Success;
}

IDevice* DeviceRegistry::GetDeviceById(DeviceId_t id) const
{
    for (size_t i = 0; i < mDeviceCount; i++) {
        if (mDevices[i]->GetDeviceConfig()->id == id) {
            return mDevices[i];
        }
    }

    return nullptr;
}

// Springboard::Drivers::IDriver* DeviceRegistry::GetDriverByDeviceId(Springboard::DeviceId_t id) const
// {
//     IDevice* device = GetDeviceById(id);
//     if (device == nullptr) {
//         return nullptr;
//     }

//     return device->GetDriver();
// }

}
}
