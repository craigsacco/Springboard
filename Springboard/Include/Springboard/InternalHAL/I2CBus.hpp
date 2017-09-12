/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

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
    msg_t result;
    i2cflags_t errors;
    Springboard::Kernel::BinarySemaphore* completion;
};

class I2CBusBase : public Springboard::Kernel::Thread
{
public:
    typedef I2CDriver Bus;
    typedef I2CConfig Config;

    I2CBusBase(Bus* bus, I2CMode mode, const char* name, Priority priority);
    void Run();
    virtual void Enqueue(const I2CTransaction& transaction) = 0;

protected:
    virtual I2CTransaction& Dequeue() = 0;

private:
    Bus* mBus;
    Config mConfig;
};

template <int TransactionDepth>
class I2CBus : public I2CBusBase
{
public:
    I2CBus(Bus* bus, I2CMode mode, const char* name, Priority priority) :
        I2CBusBase(bus, mode, name, priority)
    {
    }

    inline void Enqueue(const I2CTransaction& transaction) final
    {
        mTransactionQueue.Post(transaction);
    }

private:
    inline I2CTransaction& Dequeue() final
    {
        return mTransactionQueue.Fetch();
    }

    Springboard::Kernel::Mailbox<I2CTransaction, TransactionDepth>
        mTransactionQueue;
};

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_I2C
