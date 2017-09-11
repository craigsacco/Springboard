#include <Springboard/InternalHAL/I2CDevice.hpp>
#include <Springboard/InternalHAL/I2CBus.hpp>

namespace Springboard {
namespace InternalHAL {

I2CDevice::I2CDevice(I2CBus* bus, const Address address,
                     const Speed speed)
    : mBus(bus), mAddress(address), mSpeed(speed),
      mCompletion(true)
{
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
