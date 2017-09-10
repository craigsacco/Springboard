#pragma once

#include <Springboard/Common.hpp>
#include <hal.h>

//#if SPRINGBOARD_HAL_ENABLE_I2C

namespace Springboard {
namespace InternalHAL {

class I2CBus
{
public:
    typedef I2CDriver Bus;
    typedef I2CConfig Config;

    I2CBus(const Bus* bus)
        : mBus(mBus)
    {
    }

    void Start()
    {
        // to be implemented
    }

    void Stop()
    {
        // to be implemented
    }

private:
    const Bus* mBus;
};

}
}

//#endif // SPRINGBOARD_HAL_ENABLE_I2C
