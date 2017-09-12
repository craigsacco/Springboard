/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#include <Springboard/Common.hpp>

namespace Springboard {
namespace CommonHAL {

class IDigitalOutput
{
public:
    virtual bool Get() const = 0;
    virtual void Set(bool state = true) = 0;
    virtual void Clear() = 0;
    virtual void Toggle() = 0;
};

}  // namespace CommonHAL
}  // namespace Springboard
