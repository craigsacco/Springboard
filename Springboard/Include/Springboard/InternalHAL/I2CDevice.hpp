#pragma once

#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/Kernel/BinarySemaphore.hpp>

#if SPRINGBOARD_HAL_ENABLE_I2C

namespace Springboard {

namespace InternalHAL {

class I2CBusBase;

class I2CDevice
{
public:
    typedef i2caddr_t Address;
    typedef uint32_t Speed;

    I2CDevice(I2CBusBase* bus, const Address address, const Speed speed);

    inline Address GetAddress() const
    {
        return mAddress;
    }

    inline Speed GetSpeed() const
    {
        return mSpeed;
    }

protected:
    inline void Receive(uint8_t* rxbuf, size_t len)
    {
        PerformTransaction(nullptr, 0, rxbuf, len);
    }

    inline void Transmit(const uint8_t* txbuf, size_t len)
    {
        PerformTransaction(txbuf, len, nullptr, 0);
    }

    inline void TransmitAndReceive(const uint8_t* txbuf, size_t txlen,
                                   uint8_t* rxbuf, size_t rxlen)
    {
        PerformTransaction(txbuf, txlen, rxbuf, rxlen);
    }

private:
    void PerformTransaction(const uint8_t* txbuf, size_t txlen, uint8_t* rxbuf,
                            size_t rxlen);

    I2CBusBase* mBus;
    Address mAddress;
    Speed mSpeed;
    Springboard::Kernel::BinarySemaphore mCompletion;
};

}
}

#endif // SPRINGBOARD_HAL_ENABLE_I2C
