#include <Springboard/InternalHAL/I2CBus.hpp>
#include <Springboard/InternalHAL/I2CDevice.hpp>

namespace Springboard {
namespace InternalHAL {

I2CBus::I2CBus(Bus* bus, I2CMode mode)
    : mBus(bus), mConfig()
{
    mConfig.op_mode = (i2copmode_t)mode;
}

void I2CBus::Start()
{
    // start the bus using a default configuration
    mConfig.clock_speed = DefaultSpeed_Hz;
    mConfig.duty_cycle = (i2cdutycycle_t)DefaultDutyCycle;
    i2cStart(mBus, &mConfig);

    while (true) {
        I2CTransaction& transaction = mTransactionQueue.Fetch();

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

        transaction.completion->Signal();
    }
}

void I2CBus::Enqueue(I2CTransaction& transaction)
{
    mTransactionQueue.Post(transaction);
}

}
}
