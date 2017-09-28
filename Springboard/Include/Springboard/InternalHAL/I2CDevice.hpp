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
#include <Springboard/Utilities/ArrayReference.hpp>

#if SPRINGBOARD_HAL_ENABLE_I2C

using Springboard::Utilities::ByteArray;
using Springboard::Utilities::ConstByteArray;

namespace Springboard {
namespace InternalHAL {

class I2CBus;

class I2CDevice
{
public:
    typedef i2caddr_t Address;
    typedef uint32_t Speed;

    I2CDevice(I2CBus* bus, const Address address, const Speed requestedSpeed,
              const Speed maximumSpeed = DEFAULT_MAX_SPEED);

    inline Address GetAddress() const
    {
        return mAddress;
    }

    inline Speed GetRequestedSpeed() const
    {
        return mRequestedSpeed;
    }

    inline Speed GetMaximumSpeed() const
    {
        return mMaximumSpeed;
    }

    static constexpr Speed DEFAULT_MAX_SPEED = 100000U;

protected:
    inline ResultCode Receive(ByteArray rxbuf,
                              systime_t timeout = TIME_INFINITE)
    {
        return PerformTransaction(nullptr, rxbuf, timeout);
    }

    inline ResultCode Transmit(ConstByteArray txbuf,
                               systime_t timeout = TIME_INFINITE)
    {
        return PerformTransaction(txbuf, nullptr, timeout);
    }

    inline ResultCode TransmitAndReceive(ConstByteArray txbuf, ByteArray rxbuf,
                                         systime_t timeout = TIME_INFINITE)
    {
        return PerformTransaction(txbuf, rxbuf, timeout);
    }

private:
    ResultCode PerformTransaction(ConstByteArray txbuf, ByteArray rxbuf,
                                  systime_t timeout);

    I2CBus* mBus;
    const Address mAddress;
    const Speed mRequestedSpeed;
    const Speed mMaximumSpeed;
    Springboard::Kernel::BinarySemaphore mCompletion;
};

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_I2C
