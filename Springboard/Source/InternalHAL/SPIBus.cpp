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

#include <Springboard/InternalHAL/SPIBus.hpp>
#include <Springboard/InternalHAL/SPIDevice.hpp>
#include <Springboard/CommonHAL/IDigitalOutput.hpp>

#if SPRINGBOARD_HAL_ENABLE_SPI

namespace Springboard {
namespace InternalHAL {

SPIBus::SPIBus(Bus* bus, const char* name, Priority priority,
               size_t transactionDepth)
    : Thread(name, SPRINGBOARD_HAL_SPI_THREAD_SIZE, priority),
      mBus(bus), mConfig(), mTransactionQueue(transactionDepth)
{
}

void SPIBus::Run()
{
    while (!ShouldTerminate()) {
        SPITransaction& transaction = mTransactionQueue.Fetch<SPITransaction>();

        /*
        I2CDevice::Speed speed = transaction.device->GetSpeed();
        if (mConfig.clock_speed != speed) {
            if (mConfig.clock_speed > 0) {
                i2cStop(mBus);
            }
            mConfig.clock_speed = speed;
            mConfig.duty_cycle =
                static_cast<i2cdutycycle_t>(speed <= 100000 ?
                                            I2CDutyCycle::Standard :
                                            I2CDutyCycle::Fast_2);
            i2cStart(mBus, &mConfig);
        }
        */

        // select the device
        Springboard::CommonHAL::IDigitalOutput* selectPin =
            transaction.device->GetSelectPin();
        if (selectPin != nullptr) {
            selectPin->Clear();
        }

        // perform transaction
        transaction.result = RC_OK;
        if (transaction.exchangeData) {
            if (transaction.txbuf.GetSize() == transaction.rxbuf.GetSize()) {
                spiExchange(mBus, transaction.txbuf.GetSize(),
                            transaction.txbuf.GetData(),
                            transaction.rxbuf.GetData());
            } else {
                transaction.result = RC_SPI_EXCHANGE_INVALID;
            }
        } else {
            if (transaction.txbuf.GetSize() != 0) {
                spiSend(mBus, transaction.txbuf.GetSize(),
                        transaction.txbuf.GetData());
            }
            if (transaction.rxbuf.GetSize() != 0) {
                spiReceive(mBus, transaction.rxbuf.GetSize(),
                           transaction.rxbuf.GetData());
            }
        }

        // unselect the device
        if (selectPin != nullptr) {
            selectPin->Set();
        }

        // signal caller
        transaction.completion->Signal();
    }
}

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_I2C
