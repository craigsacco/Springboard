#pragma once

#include "Springboard/Drivers/IDriver.hpp"

namespace Springboard {
namespace Drivers {

template <typename TDriverConfigType>
class ITypeSpecificDriver : public IDriver
{
public:
    virtual const TDriverConfigType* GetDriverConfig() const = 0;
};

}
}
