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
#include <Springboard/InternalHAL/SPIDevice.hpp>

#if SPRINGBOARD_HAL_ENABLE_SPI

#if !defined(SPRINGBOARD_HAL_SPI_THREAD_SIZE)
#define SPRINGBOARD_HAL_SPI_THREAD_SIZE     512
#endif

using Springboard::Utilities::ByteArray;
using Springboard::Utilities::ConstByteArray;

namespace Springboard {

namespace Kernel { class BinarySemaphore; }

namespace InternalHAL {

struct SPITransaction
{
    SPIDevice* device;
    ConstByteArray txbuf;
    ByteArray rxbuf;
    bool exchangeData;
    ResultCode result;
    Springboard::Kernel::BinarySemaphore* completion;
};

class SPIBus : public Springboard::Kernel::Thread
{
public:
    typedef SPIDriver Bus;
    typedef SPIConfig Config;

    SPIBus(Bus* bus, const char* name, Priority priority,
           size_t transactionDepth);

    void Run() final;

    inline SPIDevice::Speed GetMaximumSpeed() const
    {
        return mMaximumSpeed;
    }

    inline void Enqueue(const SPITransaction& transaction)
    {
        mTransactionQueue.Post(transaction);
    }

private:
    Bus* mBus;
    Config mConfig;
    SPIDevice::Speed mMaximumSpeed;
    Springboard::Kernel::Mailbox mTransactionQueue;
};

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_SPI
