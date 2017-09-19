/******************************************************************************
 * MIT License
 *
 * PROJECT SPRINGBOARD
 * -------------------
 * Copyright (c) 2017 <craig.sacco@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *****************************************************************************/

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

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_I2C
