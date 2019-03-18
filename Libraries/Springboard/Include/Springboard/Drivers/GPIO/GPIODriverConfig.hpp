#pragma once

#include "Springboard/Common/SpringboardCommon.hpp"

namespace Springboard {
namespace Drivers {
namespace GPIO {

struct GPIODriverConfig_t {

    enum class Type_t : uint32_t {
        InternalGPIO,
    };

    Type_t type;
    void* driverSpecificConfig;
};

}
}
}
