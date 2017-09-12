/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#include <Springboard/InternalHAL/I2CBus.hpp>
#include <Springboard/InternalHAL/I2CDevice.hpp>

#if SPRINGBOARD_HAL_ENABLE_I2C

namespace Springboard {
namespace InternalHAL {

I2CBusBase::I2CBusBase(Bus* bus, I2CMode mode, const char* name,
                       Priority priority)
    : Thread(name, SPRINGBOARD_HAL_I2C_THREAD_SIZE, priority),
      mBus(bus), mConfig()
{
    mConfig.op_mode = (i2copmode_t)mode;
}

void I2CBusBase::Run()
{
    mConfig.clock_speed = 0;

    while (true) {
        I2CTransaction& transaction = Dequeue();

        I2CDevice::Speed speed = transaction.device->GetSpeed();
        if (mConfig.clock_speed != speed) {
            if (mConfig.clock_speed > 0) {
                i2cStop(mBus);
            }
            ASSERT(speed > 0);
            mConfig.clock_speed = speed;
            mConfig.duty_cycle = (i2cdutycycle_t)(speed <= 100000 ?
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
