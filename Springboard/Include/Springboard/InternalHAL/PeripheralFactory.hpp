#pragma once

#include <Springboard/Common.hpp>
#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/InternalHAL/I2CBus.hpp>
#include <hal.h>
#include <sbconf.h>

#if SPRINGBOARD_HAL_USE_I2C1
#if !defined(SPRINGBOARD_HAL_I2C1_THREAD_PRIORITY)
#error "SPRINGBOARD_HAL_I2C1_THREAD_PRIORITY must be defined when SPRINGBOARD_HAL_USE_I2C1 is set"
#endif
#if !defined(SPRINGBOARD_HAL_I2C1_XACTION_DEPTH)
#error "SPRINGBOARD_HAL_I2C1_XACTION_DEPTH must be defined when SPRINGBOARD_HAL_USE_I2C1 is set"
#endif
#endif

#if SPRINGBOARD_HAL_USE_I2C2
#if !defined(SPRINGBOARD_HAL_I2C2_THREAD_PRIORITY)
#error "SPRINGBOARD_HAL_I2C2_THREAD_PRIORITY must be defined when SPRINGBOARD_HAL_USE_I2C2 is set"
#endif
#if !defined(SPRINGBOARD_HAL_I2C2_XACTION_DEPTH)
#error "SPRINGBOARD_HAL_I2C2_XACTION_DEPTH must be defined when SPRINGBOARD_HAL_USE_I2C2 is set"
#endif
#endif

#if SPRINGBOARD_HAL_USE_I2C3
#if !defined(SPRINGBOARD_HAL_I2C3_THREAD_PRIORITY)
#error "SPRINGBOARD_HAL_I2C3_THREAD_PRIORITY must be defined when SPRINGBOARD_HAL_USE_I2C3 is set"
#endif
#if !defined(SPRINGBOARD_HAL_I2C3_XACTION_DEPTH)
#error "SPRINGBOARD_HAL_I2C3_XACTION_DEPTH must be defined when SPRINGBOARD_HAL_USE_I2C3 is set"
#endif
#endif

#define SPRINGBOARD_HAL_I2C_COUNT           3

namespace Springboard {
namespace InternalHAL {

class PeripheralFactory
{
public:
    PeripheralFactory();

    void Start();

#if SPRINGBOARD_HAL_ENABLE_I2C
    I2CBusBase* GetI2CBus(size_t index);
#endif

private:
#if SPRINGBOARD_HAL_ENABLE_I2C
#define SPRINGBOARD_HAL_PF_I2C_DECL(n)                              \
    I2CBus<SPRINGBOARD_HAL_I2C##n##_XACTION_DEPTH> mI2C##n##Bus     \
        { &I2CD##n, I2CMode::I2C, "I2C" #n "Bus",                   \
          SPRINGBOARD_HAL_I2C##n##_THREAD_PRIORITY }
#if SPRINGBOARD_HAL_USE_I2C1
    SPRINGBOARD_HAL_PF_I2C_DECL(1);
#endif
#if SPRINGBOARD_HAL_USE_I2C2
    SPRINGBOARD_HAL_PF_I2C_DECL(2);
#endif
#if SPRINGBOARD_HAL_USE_I2C3
    SPRINGBOARD_HAL_PF_I2C_DECL(3);
#endif
    I2CBusBase* mI2CBuses[SPRINGBOARD_HAL_I2C_COUNT] = {
#if SPRINGBOARD_HAL_USE_I2C1
        &mI2C1Bus,
#else
        nullptr,
#endif
#if SPRINGBOARD_HAL_USE_I2C2
        &mI2C2Bus,
#else
        nullptr,
#endif
#if SPRINGBOARD_HAL_USE_I2C3
        &mI2C3Bus,
#else
        nullptr,
#endif
    };
#endif // SPRINGBOARD_HAL_ENABLE_I2C
};

}
}
