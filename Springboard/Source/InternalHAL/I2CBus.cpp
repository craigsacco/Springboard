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

#include <Springboard/InternalHAL/I2CBus.hpp>
#include <Springboard/InternalHAL/I2CDevice.hpp>

#if SPRINGBOARD_HAL_ENABLE_I2C

namespace Springboard {
namespace InternalHAL {

I2CBus::I2CBus(Bus* bus, I2CMode mode, const char* name, Priority priority,
               size_t transactionDepth)
    : Thread(name, SPRINGBOARD_HAL_I2C_THREAD_SIZE, priority),
      mBus(bus), mConfig(), mTransactionQueue(transactionDepth)
{
    mConfig.op_mode = static_cast<i2copmode_t>(mode);
}

void I2CBus::Run()
{
    mConfig.clock_speed = 0;

    while (!ShouldTerminate()) {
        I2CTransaction& transaction = mTransactionQueue.Fetch<I2CTransaction>();

        I2CDevice::Speed speed = transaction.device->GetSpeed();
        if (mConfig.clock_speed != speed) {
            if (mConfig.clock_speed > 0) {
                i2cStop(mBus);
            }
            mConfig.clock_speed = speed;
            mConfig.duty_cycle =
                static_cast<i2cdutycycle_t>(speed <= 100000 ?
                                            I2CDutyCycle::Standard :
                                            I2CDutyCycle::Fast_16_9);
            i2cStart(mBus, &mConfig);
        }

        if (transaction.txlen == 0) {
            transaction.result =
                i2cMasterReceive(mBus, transaction.device->GetAddress(),
                                 transaction.rxbuf, transaction.rxlen);
        } else {
            transaction.result =
                i2cMasterTransmit(mBus, transaction.device->GetAddress(),
                                  transaction.txbuf, transaction.txlen,
                                  transaction.rxbuf, transaction.rxlen);
        }

        transaction.errors = mBus->errors;
        transaction.completion->Signal();
    }
}

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_I2C
