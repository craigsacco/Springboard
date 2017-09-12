/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#include <Springboard/Common.hpp>

namespace Springboard {
namespace CommonHAL {

class IDigitalInput
{
public:
    virtual bool Get() const = 0;
};

}  // namespace CommonHAL
}  // namespace Springboard
