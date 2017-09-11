#pragma once

#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/Kernel/BinarySemaphore.hpp>

//#if SPRINGBOARD_HAL_ENABLE_I2C

namespace Springboard {

namespace InternalHAL {

class I2CBus;

class I2CDevice
{
public:
    typedef i2caddr_t Address;
    typedef uint32_t Speed;

    I2CDevice(I2CBus* bus, const Address address);

    inline Address GetAddress() const
    {
        return mAddress;
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

    I2CBus* mBus;
    Address mAddress;
    Springboard::Kernel::BinarySemaphore mCompletion;
};

}
}

//#endif // SPRINGBOARD_HAL_ENABLE_I2C
