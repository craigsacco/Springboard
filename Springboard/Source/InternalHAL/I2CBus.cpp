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

I2CBus::I2CBus(Bus* bus, const char* name, Priority priority,
               size_t transactionDepth)
    : Thread(name, SPRINGBOARD_HAL_I2C_THREAD_SIZE, priority),
      mBus(bus), mConfig(), mTransactionQueue(transactionDepth)
{
#if MCU_FAMILY == MCU_FAMILY_STM32F4
    mConfig.op_mode = OPMODE_I2C;
#endif

    // determine peripheral and maximum speed - it is half of the APB clock
    // speed of the bus it is running on
#if MCU_FAMILY == MCU_FAMILY_STM32F4 && \
    (MCU_LINE == MCU_LINE_STM32F405_F415 || \
     MCU_LINE == MCU_LINE_STM32F407_F417 || \
     MCU_LINE == MCU_LINE_STM32F427_F437 || \
     MCU_LINE == MCU_LINE_STM32F429_F439)
    mMaximumSpeed = FAST_MODE_SPEED_MAX;
    if (false) {  // NOLINT
#if SPRINGBOARD_HAL_USE_I2C1
    } else if (mBus == &I2CD1) {
        mPeripheralSpeed = STM32_PCLK1_MAX;
#endif
#if SPRINGBOARD_HAL_USE_I2C2
    } else if (mBus == &I2CD2) {
        mPeripheralSpeed = STM32_PCLK1_MAX;
#endif
#if SPRINGBOARD_HAL_USE_I2C3
    } else if (mBus == &I2CD3) {
        mPeripheralSpeed = STM32_PCLK1_MAX;
#endif
    } else {
        ASSERT_FAIL_MSG("Unknown SPI peripheral");
    }
#elif MCU_FAMILY == MCU_FAMILY_STM32F7 && (MCU_LINE == MCU_LINE_STM32F746_F756)
    mMaximumSpeed = FAST_MODE_PLUS_SPEED_MAX;
    if (false) {  // NOLINT
#if SPRINGBOARD_HAL_USE_I2C1
    } else if (mBus == &I2CD1) {
        mPeripheralSpeed = STM32_I2C1CLK;
#endif
#if SPRINGBOARD_HAL_USE_I2C2
    } else if (mBus == &I2CD2) {
        mPeripheralSpeed = STM32_I2C2CLK;
#endif
#if SPRINGBOARD_HAL_USE_I2C3
    } else if (mBus == &I2CD3) {
        mPeripheralSpeed = STM32_I2C3CLK;
#endif
#if SPRINGBOARD_HAL_USE_I2C4
    } else if (mBus == &I2CD4) {
        mPeripheralSpeed = STM32_I2C4CLK;
#endif
    } else {
        ASSERT_FAIL_MSG("Unknown SPI peripheral");
    }
#else
#error "Cannot determine maximum SPI interface speed"
#endif
}

void I2CBus::Run()
{
    uint32_t currentSpeed = 0;

    while (!ShouldTerminate()) {
        Transaction& transaction = mTransactionQueue.Fetch<Transaction>();
        transaction.result = RC_OK;

        if (currentSpeed != transaction.speed) {
            if (currentSpeed > 0) {
                i2cStop(mBus);
            }
            Speed actualSpeed = (transaction.speed <= GetMaximumSpeed() ?
                                 transaction.speed : GetMaximumSpeed());
#if MCU_FAMILY == MCU_FAMILY_STM32F4
            mConfig.clock_speed = actualSpeed;
            mConfig.duty_cycle = (actualSpeed <= STANDARD_MODE_SPEED_MAX ?
                                  STD_DUTY_CYCLE : FAST_DUTY_CYCLE_2);
#elif MCU_FAMILY == MCU_FAMILY_STM32F7
            transaction.result = RC_I2C_NOT_SUPPORTED;
            // TODO(craig.sacco): calculate mConfig.timingr
#endif
            i2cStart(mBus, &mConfig);
            currentSpeed = transaction.speed;
        }

        if (transaction.result == RC_OK) {
            msg_t result = MSG_OK;
            if (transaction.txbuf.GetSize() == 0) {
                result = i2cMasterReceiveTimeout(mBus,
                                                 transaction.address,
                                                 transaction.rxbuf.GetData(),
                                                 transaction.rxbuf.GetSize(),
                                                 transaction.timeout);
            } else {
                result = i2cMasterTransmitTimeout(mBus,
                                                  transaction.address,
                                                  transaction.txbuf.GetData(),
                                                  transaction.txbuf.GetSize(),
                                                  transaction.rxbuf.GetData(),
                                                  transaction.rxbuf.GetSize(),
                                                  transaction.timeout);
            }

            if (result != MSG_OK) {
                transaction.result = RC_I2C_TIMED_OUT;
                currentSpeed = 0;  // bus is locked - force bus restart
            } else if (mBus->errors != I2C_NO_ERROR) {
                transaction.result = RC_I2C_HARDWARE_ERROR_BASE + mBus->errors;
            }
        }

        transaction.completion->Signal();
    }
}

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_I2C
