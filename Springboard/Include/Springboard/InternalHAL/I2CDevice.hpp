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
#include <Springboard/InternalHAL/I2CBus.hpp>
#include <Springboard/Kernel/BinarySemaphore.hpp>
#include <Springboard/Utilities/ArrayReference.hpp>

#if SPRINGBOARD_HAL_ENABLE_I2C

namespace Springboard {
namespace InternalHAL {

class I2CBus;

class I2CDevice
{
public:
    I2CDevice(I2CBus* bus,
              const I2CBus::Address address,
              const I2CBus::Speed requestedSpeed,
              const I2CBus::Speed maximumSpeed = DEFAULT_MAX_SPEED);

    inline I2CBus::Address GetAddress() const
    {
        return mAddress;
    }

    inline I2CBus::Speed GetRequestedSpeed() const
    {
        return mRequestedSpeed;
    }

    inline I2CBus::Speed GetMaximumSpeed() const
    {
        return mMaximumSpeed;
    }

    static constexpr I2CBus::Speed DEFAULT_MAX_SPEED = 100000U;

protected:
    inline ResultCode Receive(Springboard::Utilities::ByteArray rxbuf,
                              systime_t timeout = TIME_INFINITE)
    {
        return ReceiveEx(mAddress, rxbuf, timeout);
    }

    inline ResultCode Transmit(Springboard::Utilities::ConstByteArray txbuf,
                               systime_t timeout = TIME_INFINITE)
    {
        return TransmitEx(mAddress, txbuf, timeout);
    }

    inline ResultCode TransmitAndReceive(
        Springboard::Utilities::ConstByteArray txbuf,
        Springboard::Utilities::ByteArray rxbuf,
        systime_t timeout = TIME_INFINITE)
    {
        return TransmitAndReceiveEx(mAddress, txbuf, rxbuf, timeout);
    }

    inline ResultCode ReceiveEx(I2CBus::Address address,
                                Springboard::Utilities::ByteArray rxbuf,
                                systime_t timeout = TIME_INFINITE)
    {
        return PerformTransaction(address, nullptr, rxbuf, timeout);
    }

    inline ResultCode TransmitEx(I2CBus::Address address,
                                 Springboard::Utilities::ConstByteArray txbuf,
                                 systime_t timeout = TIME_INFINITE)
    {
        return PerformTransaction(address, txbuf, nullptr, timeout);
    }

    inline ResultCode TransmitAndReceiveEx(
        I2CBus::Address address, Springboard::Utilities::ConstByteArray txbuf,
        Springboard::Utilities::ByteArray rxbuf,
        systime_t timeout = TIME_INFINITE)
    {
        return PerformTransaction(address, txbuf, rxbuf, timeout);
    }

private:
    ResultCode PerformTransaction(I2CBus::Address address,
                                  Springboard::Utilities::ConstByteArray txbuf,
                                  Springboard::Utilities::ByteArray rxbuf,
                                  systime_t timeout);

    I2CBus* mBus;
    const I2CBus::Address mAddress;
    const I2CBus::Speed mRequestedSpeed;
    const I2CBus::Speed mMaximumSpeed;
    Springboard::Kernel::BinarySemaphore mCompletion;
};

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_I2C
