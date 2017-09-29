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
#include <Springboard/InternalHAL/SPIBus.hpp>
#include <Springboard/Kernel/BinarySemaphore.hpp>
#include <Springboard/Utilities/ArrayReference.hpp>

#if SPRINGBOARD_HAL_ENABLE_SPI

namespace Springboard {

namespace CommonHAL { class IDigitalOutput; }

namespace InternalHAL {

class SPIDevice
{
public:
    SPIDevice(SPIBus* bus, Springboard::CommonHAL::IDigitalOutput* selectPin,
              const SPIClockConfig clockConfig,
              const SPIBus::Speed requestedSpeed,
              const SPIBus::Speed maximumSpeed = DEFAULT_MAX_SPEED);

    inline Springboard::CommonHAL::IDigitalOutput* GetSelectPin() const
    {
        return mSelectPin;
    }

    inline SPIClockConfig GetClockConfig() const
    {
        return mClockConfig;
    }

    inline SPIBus::Speed GetRequestedSpeed() const
    {
        return mRequestedSpeed;
    }

    inline SPIBus::Speed GetActualSpeed() const
    {
        return mActualSpeed;
    }

    inline SPIBus::Prescaler GetActualClockPrescaler() const
    {
        return mActualClockPrescaler;
    }

    inline SPIBus::Speed GetMaximumSpeed() const
    {
        return mMaximumSpeed;
    }

    static constexpr SPIBus::Speed DEFAULT_MAX_SPEED = 100000U;

protected:
    inline ResultCode Receive(Springboard::Utilities::ByteArray rxbuf)
    {
        return PerformTransaction(nullptr, rxbuf, false);
    }

    inline ResultCode Transmit(Springboard::Utilities::ConstByteArray txbuf)
    {
        return PerformTransaction(txbuf, nullptr, false);
    }

    inline ResultCode TransmitAndReceive(
        Springboard::Utilities::ConstByteArray txbuf,
        Springboard::Utilities::ByteArray rxbuf)
    {
        return PerformTransaction(txbuf, rxbuf, false);
    }

    inline ResultCode Exchange(Springboard::Utilities::ConstByteArray txbuf,
                               Springboard::Utilities::ByteArray rxbuf)
    {
        ASSERT(txbuf.GetSize() == rxbuf.GetSize());
        return PerformTransaction(txbuf, rxbuf, true);
    }

private:
    ResultCode PerformTransaction(Springboard::Utilities::ConstByteArray txbuf,
                                  Springboard::Utilities::ByteArray rxbuf,
                                  bool exchangeData);

    SPIBus* mBus;
    Springboard::CommonHAL::IDigitalOutput* mSelectPin;
    const SPIClockConfig mClockConfig;
    const SPIBus::Speed mRequestedSpeed;
    SPIBus::Speed mActualSpeed;
    SPIBus::Prescaler mActualClockPrescaler;
    const SPIBus::Speed mMaximumSpeed;
    Springboard::Kernel::BinarySemaphore mCompletion;
};

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_SPI
