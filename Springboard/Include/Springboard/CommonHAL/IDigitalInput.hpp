#pragma once

#include <Springboard/Common.hpp>

namespace Springboard {
namespace CommonHAL {

class IDigitalInput
{
public:
    virtual bool Get() const = 0;
};

}
}
