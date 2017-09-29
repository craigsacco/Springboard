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

using Springboard::Utilities::ByteArray;
using Springboard::Utilities::ConstByteArray;

namespace Springboard {
namespace InternalHAL {

SPIBus::SPIBus(Bus* bus, const char* name, Priority priority,
               size_t transactionDepth)
    : Thread(name, SPRINGBOARD_HAL_SPI_THREAD_SIZE, priority),
      mBus(bus), mConfig(), mMaximumSpeed(0),
      mTransactionQueue(transactionDepth)
{
    // determine maximum bus speed - it is half of the APB clock speed
    // of the bus it is running on
    if (false) {  // NOLINT
#if SPRINGBOARD_HAL_USE_SPI1
    } else if (mBus == &SPID1) {
        mMaximumSpeed = STM32_PCLK2_MAX >> 1;
#endif
#if SPRINGBOARD_HAL_USE_SPI2
    } else if (mBus == &SPID2) {
        mMaximumSpeed = STM32_PCLK1_MAX >> 1;
#endif
#if SPRINGBOARD_HAL_USE_SPI3
    } else if (mBus == &SPID3) {
        mMaximumSpeed = STM32_PCLK1_MAX >> 1;
#endif
#if SPRINGBOARD_HAL_USE_SPI4
    } else if (mBus == &SPID4) {
        mMaximumSpeed = STM32_PCLK2_MAX >> 1;
#endif
#if SPRINGBOARD_HAL_USE_SPI5
    } else if (mBus == &SPID5) {
        mMaximumSpeed = STM32_PCLK2_MAX >> 1;
#endif
#if SPRINGBOARD_HAL_USE_SPI5
    } else if (mBus == &SPID6) {
        mMaximumSpeed = STM32_PCLK2_MAX >> 1;
#endif
    } else {
        ASSERT_FAIL_MSG("Unknown SPI peripheral");
    }
}

void SPIBus::Run()
{
    // start running with unconfigured values
    mConfig.cr1 = 0;
    mConfig.cr2 = 0;
    spiStart(mBus, &mConfig);

    while (!ShouldTerminate()) {
        Transaction& transaction = mTransactionQueue.Fetch<Transaction>();

        // (re-)configure the peripheral where necessary
        uint32_t cr1 =
            (static_cast<uint32_t>(transaction.clockPrescaler) << 3) |
            static_cast<uint32_t>(transaction.clockConfig);
        uint32_t cr2 = 0;
        if (mConfig.cr1 != cr1 || mConfig.cr2 != cr2) {
            mConfig.cr1 = cr1;
            mConfig.cr2 = cr2;
            spiStart(mBus, &mConfig);
        }

        // select the device by asserting the /CS line
        if (transaction.selectPin != nullptr) {
            transaction.selectPin->Clear();
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

        // unselect the device by de-asserting the /CS line
        if (transaction.selectPin != nullptr) {
            transaction.selectPin->Set();
        }

        // signal caller
        transaction.completion->Signal();
    }
}

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_SPI
