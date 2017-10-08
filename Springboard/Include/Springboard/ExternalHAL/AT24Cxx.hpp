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

#include <Springboard/InternalHAL/I2CDevice.hpp>
#include <Springboard/Kernel/Mutex.hpp>
#include <Springboard/Utilities/ArrayReference.hpp>

#if SPRINGBOARD_HAL_ENABLE_I2C

namespace Springboard {
namespace ExternalHAL {

class AT24Cxx : public Springboard::InternalHAL::I2CDevice
{
protected:
    enum class Variant : uint32_t
    {
        AT24C01 = 128UL,
        AT24C02 = 256UL,
        AT24C04 = 512UL,
        AT24C08 = 1024UL,
        AT24C16 = 2048UL,
    };

    AT24Cxx(Springboard::InternalHAL::I2CBus* bus,
            const Springboard::InternalHAL::I2CBus::Address address,
            const Springboard::InternalHAL::I2CBus::Speed requestedSpeed,
            Variant variant);

public:
    inline size_t GetSize() const
    {
        return static_cast<size_t>(mVariant);
    }

    virtual size_t GetMaxChunkSize() const = 0;

    ResultCode Read(size_t offset, Springboard::Utilities::ByteArray data,
                    size_t* read);
    ResultCode Write(size_t offset, Springboard::Utilities::ConstByteArray data,
                     size_t* written);

protected:
    Variant mVariant;
    Springboard::Kernel::Mutex mMutex;

private:
    static constexpr Springboard::InternalHAL::I2CBus::Speed MAX_SPEED =
        400000U;
};

class AT24CxxType1 : public AT24Cxx
{
protected:
    AT24CxxType1(Springboard::InternalHAL::I2CBus* bus,
                 const Springboard::InternalHAL::I2CBus::Address address,
                 const Springboard::InternalHAL::I2CBus::Speed requestedSpeed,
                 Variant variant);

public:
    inline size_t GetMaxChunkSize() const final
    {
        return 7;
    }
};

class AT24CxxType2 : public AT24Cxx
{
protected:
    AT24CxxType2(Springboard::InternalHAL::I2CBus* bus,
                 const Springboard::InternalHAL::I2CBus::Address address,
                 const Springboard::InternalHAL::I2CBus::Speed requestedSpeed,
                 Variant variant);

public:
    inline size_t GetMaxChunkSize() const final
    {
        return 15;
    }
};

class AT24C01 : public AT24CxxType1
{
public:
    AT24C01(Springboard::InternalHAL::I2CBus* bus,
            const Springboard::InternalHAL::I2CBus::Address address,
            const Springboard::InternalHAL::I2CBus::Speed requestedSpeed);
};

class AT24C02 : public AT24CxxType1
{
public:
    AT24C02(Springboard::InternalHAL::I2CBus* bus,
            const Springboard::InternalHAL::I2CBus::Address address,
            const Springboard::InternalHAL::I2CBus::Speed requestedSpeed);
};

class AT24C04 : public AT24CxxType2
{
public:
    AT24C04(Springboard::InternalHAL::I2CBus* bus,
            const Springboard::InternalHAL::I2CBus::Address address,
            const Springboard::InternalHAL::I2CBus::Speed requestedSpeed);
};

class AT24C08 : public AT24CxxType2
{
public:
    AT24C08(Springboard::InternalHAL::I2CBus* bus,
            const Springboard::InternalHAL::I2CBus::Address address,
            const Springboard::InternalHAL::I2CBus::Speed requestedSpeed);
};

class AT24C16 : public AT24CxxType2
{
public:
    AT24C16(Springboard::InternalHAL::I2CBus* bus,
            const Springboard::InternalHAL::I2CBus::Address address,
            const Springboard::InternalHAL::I2CBus::Speed requestedSpeed);
};

}  // namespace ExternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_I2C
