#include <Springboard/InternalHAL/I2CBus.hpp>
#include <Springboard/InternalHAL/I2CDevice.hpp>

namespace Springboard {
namespace InternalHAL {

I2CBus::I2CBus(Bus* bus, I2CMode mode)
    : StaticThread<SPRINGBOARD_I2C_THREAD_SIZE>("I2CBus", SPRINGBOARD_I2C_THREAD_PRIORITY),
      mBus(bus), mConfig()
{
    mConfig.op_mode = (i2copmode_t)mode;
}

void I2CBus::Run()
{
    mConfig.clock_speed = 0;

    while (true) {
        I2CTransaction& transaction = mTransactionQueue.Fetch();

        I2CDevice::Speed speed = transaction.device->GetSpeed();
        if (mConfig.clock_speed != speed) {
            if (mConfig.clock_speed > 0) {
                i2cStop(mBus);
            }
            ASSERT(speed > 0, "I2C device speed cannot be zero");
            mConfig.clock_speed = speed;
            mConfig.duty_cycle = (i2cdutycycle_t)(speed <= 100000 ?
                                                      I2CDutyCycle::Standard :
                                                      I2CDutyCycle::Fast_16_9);
            i2cStart(mBus, &mConfig);
        }

        if (transaction.txlen == 0) {
            transaction.result = i2cMasterReceive(mBus,
                                                  transaction.device->GetAddress(),
                                                  transaction.rxbuf,
                                                  transaction.rxlen);
        } else {
            transaction.result = i2cMasterTransmit(mBus,
                                                   transaction.device->GetAddress(),
                                                   transaction.txbuf,
                                                   transaction.txlen,
                                                   transaction.rxbuf,
                                                   transaction.rxlen);
        }

        transaction.errors = mBus->errors;
        transaction.completion->Signal();
    }
}

void I2CBus::Enqueue(I2CTransaction& transaction)
{
    mTransactionQueue.Post(transaction);
}

}
}
