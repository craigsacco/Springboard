#include <Springboard/InternalHAL/I2CDevice.hpp>
#include <Springboard/InternalHAL/I2CBus.hpp>

namespace Springboard {
namespace InternalHAL {

I2CDevice::I2CDevice(I2CBus* bus, const Address address)
    : mBus(bus), mAddress(address)
{
}

void I2CDevice::PerformTransaction(const uint8_t* txbuf, size_t txlen,
                                   uint8_t* rxbuf, size_t rxlen)
{
    I2CTransaction transaction {
        this, txbuf, txlen, rxbuf, rxlen, 0, &mCompletion
    };
    mBus->Enqueue(transaction);
    mCompletion.Wait();
}

}
}
