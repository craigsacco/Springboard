#pragma once

#include "Springboard/Common/SpringboardCommon.hpp"

namespace Springboard {
namespace Drivers {
namespace GPIO {

struct InternalGPIODriverConfig_t {

    enum class Port_t : uint32_t {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
    };

    Port_t port;
};

}
}
}
