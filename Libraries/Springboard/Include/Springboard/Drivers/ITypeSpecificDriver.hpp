#pragma once

#include "Springboard/Drivers/IDriver.hpp"

namespace Springboard {
namespace Drivers {

template <typename TDriverConfigType, typename TDriverFactoryType>
class ITypeSpecificDriver : public IDriver
{
public:
    virtual const TDriverConfigType* GetDriverConfig(TDriverFactoryType* factory) const = 0;
};

}
}
