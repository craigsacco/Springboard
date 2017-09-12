#include <Springboard/InternalHAL/PeripheralFactory.hpp>

namespace Springboard {
namespace InternalHAL {

PeripheralFactory::PeripheralFactory()
{
}

void PeripheralFactory::Start()
{
#if SPRINGBOARD_HAL_ENABLE_I2C
    for (I2CBusBase* bus : mI2CBuses) {
        if (bus != nullptr) {
            bus->Start();
        }
    }
#endif
}

#if SPRINGBOARD_HAL_ENABLE_I2C
I2CBusBase* PeripheralFactory::GetI2CBus(size_t index)
{
    ASSERT(index > 0 && index <= SPRINGBOARD_HAL_I2C_COUNT);
    return mI2CBuses[index-1];
}
#endif

}
}
