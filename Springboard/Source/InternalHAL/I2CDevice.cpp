#include <Springboard/InternalHAL/I2CDevice.hpp>
#include <Springboard/InternalHAL/I2CBus.hpp>

#if SPRINGBOARD_HAL_ENABLE_I2C

namespace Springboard {
namespace InternalHAL {

I2CDevice::I2CDevice(I2CBusBase* bus, const Address address,
                     const Speed speed)
    : mBus(bus), mAddress(address), mSpeed(speed),
      mCompletion(true)
{
    ASSERT(bus != nullptr);
    ASSERT(speed > 0);
}

void I2CDevice::PerformTransaction(const uint8_t* txbuf, size_t txlen,
                                   uint8_t* rxbuf, size_t rxlen)
{
    I2CTransaction transaction {
        .device = this, .txbuf = txbuf,
        .txlen = txlen, .rxbuf = rxbuf,
        .rxlen = rxlen, .result = 0,
        .errors = 0, .completion = &mCompletion
    };
    mBus->Enqueue(transaction);
    mCompletion.Wait();
}

}
}

#endif // SPRINGBOARD_HAL_ENABLE_I2C
