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
#include <Springboard/InternalHAL/I2CDevice.hpp>
#include <Springboard/Kernel/Thread.hpp>
#include <Springboard/Kernel/Mailbox.hpp>

#if SPRINGBOARD_HAL_ENABLE_I2C

#if !defined(SPRINGBOARD_HAL_I2C_THREAD_SIZE)
#define SPRINGBOARD_HAL_I2C_THREAD_SIZE     512
#endif

namespace Springboard {

namespace Kernel { class BinarySemaphore; }

namespace InternalHAL {

class I2CDevice;

struct I2CTransaction
{
    I2CDevice* device;
    const uint8_t* txbuf;
    size_t txlen;
    uint8_t* rxbuf;
    size_t rxlen;
    systime_t timeout;
    ResultCode result;
    Springboard::Kernel::BinarySemaphore* completion;
};

class I2CBus : public Springboard::Kernel::Thread
{
public:
    typedef I2CDriver Bus;
    typedef I2CConfig Config;

    I2CBus(Bus* bus, I2CMode mode, const char* name, Priority priority,
           size_t transactionDepth);
    void Run();

    inline void Enqueue(const I2CTransaction& transaction)
    {
        mTransactionQueue.Post(transaction);
    }

private:
    Bus* mBus;
    Config mConfig;
    Springboard::Kernel::Mailbox mTransactionQueue;
};

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_I2C
