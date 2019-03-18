#pragma once

#include "Springboard/Common/SpringboardCommon.hpp"

namespace Springboard {
namespace Devices {

struct DeviceConfig_t {
    Springboard::DeviceId_t id;
    Springboard::DeviceType_t type;
    const char* name;
    void* driverConfig;
};

}
}
