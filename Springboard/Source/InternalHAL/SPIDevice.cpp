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

#include <Springboard/InternalHAL/SPIDevice.hpp>
#include <Springboard/InternalHAL/SPIBus.hpp>
#include <Springboard/CommonHAL/IDigitalOutput.hpp>

#if SPRINGBOARD_HAL_ENABLE_SPI

namespace Springboard {
namespace InternalHAL {

SPIDevice::SPIDevice(SPIBus* bus,
                     Springboard::CommonHAL::IDigitalOutput* selectPin,
                     const SPIClockConfig clockConfig, const Speed speed,
                     const Speed maximumSpeed)
    : mBus(bus), mSelectPin(selectPin), mClockConfig(clockConfig),
      mSpeed(speed), mMaximumSpeed(maximumSpeed), mCompletion(true)
{
    ASSERT(bus != nullptr);
    ASSERT(speed > 0 && speed <= GetMaximumSpeed());

    // set the select pin to inhibit selection
    mSelectPin->Set();
}

ResultCode SPIDevice::PerformTransaction(ConstByteArray txbuf, ByteArray rxbuf,
                                         bool exchangeData)
{
    SPITransaction transaction {
        .device = this, .txbuf = txbuf,
        .rxbuf = rxbuf, .exchangeData = exchangeData,
        .result = RC_OK, .completion = &mCompletion
    };
    mBus->Enqueue(transaction);
    mCompletion.Wait();

    return RC_OK;
}

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_I2C
