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

#include <Springboard/Comms/IStream.hpp>
#include <Springboard/InternalHAL/InternalHAL.hpp>

#if SPRINGBOARD_HAL_ENABLE_UART

namespace Springboard {

namespace Kernel { class BinarySemaphore; }

namespace InternalHAL {

class UARTBus : public Springboard::Comms::IStream
{
public:
    typedef SerialDriver Bus;
    typedef SerialConfig Config;
    typedef uint32_t Speed;

    explicit UARTBus(Bus* bus);

    void Start();
    void Stop();
    void SetConfig(Speed speed,
                   UARTDataBits databits = UARTDataBits::Eight,
                   UARTParity parity = UARTParity::None,
                   UARTStopBits stopbits = UARTStopBits::One);

    inline bool IsStarted()
    {
        return (mBus->state == SD_READY);
    }

    inline uint8_t Read() final
    {
        return sdGet(mBus);
    }

    inline void Read(Springboard::Utilities::ByteArray buffer) final
    {
        sdRead(mBus, buffer.GetData(), buffer.GetSize());
    }

    inline size_t ReadAsync(Springboard::Utilities::ByteArray buffer) final
    {
        return sdAsynchronousRead(mBus, buffer.GetData(), buffer.GetSize());
    }

    inline void Write(uint8_t b) final
    {
        sdPut(mBus, b);
    }

    inline void Write(Springboard::Utilities::ConstByteArray buffer) final
    {
        sdWrite(mBus, buffer.GetData(), buffer.GetSize());
    }

    inline size_t ReadAsync(Springboard::Utilities::ConstByteArray buffer) final
    {
        return sdAsynchronousWrite(mBus, buffer.GetData(), buffer.GetSize());
    }

private:
    Bus* mBus;
    Config mConfig;
};

}  // namespace InternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_UART
