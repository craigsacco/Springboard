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
#include <Springboard/Kernel/Thread.hpp>
#include <Springboard/Kernel/Mailbox.hpp>
#include <Springboard/Utilities/ArrayReference.hpp>

#if SPRINGBOARD_HAL_ENABLE_SPI

#if !defined(SPRINGBOARD_HAL_SPI_THREAD_SIZE)
#define SPRINGBOARD_HAL_SPI_THREAD_SIZE     512
#endif

namespace Springboard {

namespace CommonHAL { class IDigitalOutput; }
namespace Kernel { class BinarySemaphore; }

namespace InternalHAL {

class SPIBus : public Springboard::Kernel::Thread
{
public:
    typedef SPIDriver Bus;
    typedef SPIConfig Config;
    typedef uint32_t Speed;
    typedef uint8_t Prescaler;

    struct Transaction
    {
        Prescaler clockPrescaler;
        SPIClockConfig clockConfig;
        Springboard::CommonHAL::IDigitalOutput* selectPin;
        Springboard::Utilities::ConstByteArray txbuf;
        Springboard::Utilities::ByteArray rxbuf;
        bool exchangeData;
        ResultCode result;
        Springboard::Kernel::BinarySemaphore* completion;
    };

    SPIBus(Bus* bus, const char* name, Priority priority,
           size_t transactionDepth);

    void Run() final;

    inline Speed GetMaximumSpeed() const
    {
        return mMaximumSpeed;
    }

    inline void Enqueue(const Transaction& transaction)
    {
        mTransactionQueue.Post(transaction);
    }

private:
    Bus* mBus;
    Config mConfig;
    Speed mMaximumSpeed;
    Springboard::Kernel::Mailbox mTransactionQueue;
};

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_SPI
