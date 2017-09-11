#pragma once

#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/InternalHAL/I2CDevice.hpp>
#include <Springboard/Kernel/Thread.hpp>
#include <Springboard/Kernel/Mailbox.hpp>

//#if SPRINGBOARD_HAL_ENABLE_I2C

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
    msg_t result;
    i2cflags_t errors;
    Springboard::Kernel::BinarySemaphore* completion;
};

class I2CBus : public Springboard::Kernel::StaticThread<SPRINGBOARD_I2C_THREAD_SIZE>
{
public:
    typedef I2CDriver Bus;
    typedef I2CConfig Config;

    I2CBus(Bus* bus, I2CMode mode);
    void Run();
    void Enqueue(I2CTransaction& transaction);

private:
    Bus* mBus;
    Config mConfig;
    Springboard::Kernel::Mailbox<I2CTransaction, SPRINGBOARD_I2C_MAILBOX_DEPTH> mTransactionQueue;
};

}
}

//#endif // SPRINGBOARD_HAL_ENABLE_I2C
