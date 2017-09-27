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

#if SPRINGBOARD_HAL_ENABLE_SPI

using Springboard::Utilities::ByteArray;
using Springboard::Utilities::ConstByteArray;

namespace Springboard {

namespace CommonHAL { class IDigitalOutput; }

namespace InternalHAL {

class SPIBus;

class SPIDevice
{
public:
    typedef i2caddr_t Address;
    typedef uint32_t Speed;

    SPIDevice(SPIBus* bus, Springboard::CommonHAL::IDigitalOutput* selectPin,
              const SPIClockConfig clockConfig, const Speed speed,
              const Speed maximumSpeed = DEFAULT_MAX_SPEED);

    inline Springboard::CommonHAL::IDigitalOutput* GetSelectPin() const
    {
        return mSelectPin;
    }

    inline SPIClockConfig GetClockConfig() const
    {
        return mClockConfig;
    }

    inline Speed GetSpeed() const
    {
        return mSpeed;
    }

    inline Speed GetMaximumSpeed() const
    {
        return mMaximumSpeed;
    }

    static constexpr Speed DEFAULT_MAX_SPEED = 100000U;

protected:
    inline ResultCode Receive(ByteArray rxbuf)
    {
        return PerformTransaction(nullptr, rxbuf, false);
    }

    inline ResultCode Transmit(ConstByteArray txbuf)
    {
        return PerformTransaction(txbuf, nullptr, false);
    }

    inline ResultCode TransmitAndReceive(ConstByteArray txbuf, ByteArray rxbuf)
    {
        return PerformTransaction(txbuf, rxbuf, false);
    }

    inline ResultCode Exchange(ConstByteArray txbuf, ByteArray rxbuf)
    {
        ASSERT(txbuf.GetSize() == rxbuf.GetSize());
        return PerformTransaction(txbuf, rxbuf, true);
    }

private:
    ResultCode PerformTransaction(ConstByteArray txbuf, ByteArray rxbuf,
                                  bool exchangeData);

    SPIBus* mBus;
    Springboard::CommonHAL::IDigitalOutput* mSelectPin;
    const SPIClockConfig mClockConfig;
    const Speed mSpeed;
    const Speed mMaximumSpeed;
    Springboard::Kernel::BinarySemaphore mCompletion;
};

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_SPI
