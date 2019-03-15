#pragma once

#include "Springboard/Common/SpringboardCommon.hpp"

namespace Springboard {
namespace Drivers {

class IDriver
{
public:
    virtual Springboard::DeviceType_t GetDeviceType() const = 0;
    virtual Springboard::UnderlyingDriverType_t GetDriverType() const = 0;
};

}
}
