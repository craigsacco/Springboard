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

#include <Springboard/ExternalHAL/AT24Cxx.hpp>

#if SPRINGBOARD_HAL_ENABLE_I2C

using Springboard::InternalHAL::I2CBus;
using Springboard::Utilities::ByteArray;
using Springboard::Utilities::ConstByteArray;

namespace Springboard {
namespace ExternalHAL {

AT24Cxx::AT24Cxx(I2CBus* bus, const I2CBus::Address address,
                 const I2CBus::Speed requestedSpeed,
                 Variant variant)
    : I2CDevice(bus, address, requestedSpeed, MAX_SPEED),
      mVariant(variant)
{
    ASSERT(address >= 0x50 && address <= 0x57);
}

ResultCode AT24Cxx::ReadChunks(size_t offset, ByteArray data,
                               size_t chunkSize)
{
    if (offset + data.GetSize() > GetSize()) {
        return RC_AT45DBXX_INVALID_OFFSET_OR_SIZE;
    }

    // TODO(craig.sacco): read in chunks

    return RC_OK;
}

ResultCode AT24Cxx::WriteChunks(size_t offset, ConstByteArray data,
                                size_t chunkSize)
{
    if (offset + data.GetSize() > GetSize()) {
        return RC_AT45DBXX_INVALID_OFFSET_OR_SIZE;
    }

    // TODO(craig.sacco): write in chunks

    return RC_OK;
}

AT24CxxType1::AT24CxxType1(I2CBus* bus, const I2CBus::Address address,
                           const I2CBus::Speed requestedSpeed,
                           Variant variant)
    : AT24Cxx(bus, address, requestedSpeed, variant)
{
    ASSERT(variant == Variant::AT24C01 || variant == Variant::AT24C02);
    ASSERT(address >= 0x50 && address <= 0x57);
}

ResultCode AT24CxxType1::Read(size_t offset, ByteArray data)
{
    return ReadChunks(offset, data, MAX_BYTES_PER_XACTION);
}

ResultCode AT24CxxType1::Write(size_t offset,  ConstByteArray data)
{
    return WriteChunks(offset, data, MAX_BYTES_PER_XACTION);
}

AT24CxxType2::AT24CxxType2(I2CBus* bus, const I2CBus::Address address,
                           const I2CBus::Speed requestedSpeed,
                           Variant variant)
    : AT24Cxx(bus, address, requestedSpeed, variant)
{
    ASSERT(variant == Variant::AT24C04 || variant == Variant::AT24C08 ||
           variant == Variant::AT24C16);
}

ResultCode AT24CxxType2::Read(size_t offset, ByteArray data)
{
    return ReadChunks(offset, data, MAX_BYTES_PER_XACTION);
}

ResultCode AT24CxxType2::Write(size_t offset,  ConstByteArray data)
{
    return WriteChunks(offset, data, MAX_BYTES_PER_XACTION);
}

AT24C01::AT24C01(I2CBus* bus, const I2CBus::Address address,
                 const I2CBus::Speed requestedSpeed) :
    AT24CxxType1(bus, address, requestedSpeed, Variant::AT24C01)
{
}

AT24C02::AT24C02(I2CBus* bus, const I2CBus::Address address,
                 const I2CBus::Speed requestedSpeed) :
    AT24CxxType1(bus, address, requestedSpeed, Variant::AT24C02)
{
}

AT24C04::AT24C04(I2CBus* bus, const I2CBus::Address address,
                 const I2CBus::Speed requestedSpeed) :
    AT24CxxType2(bus, address, requestedSpeed, Variant::AT24C04)
{
    ASSERT((address & 0x01) == 0);  // pin A0 not used
}

AT24C08::AT24C08(I2CBus* bus, const I2CBus::Address address,
                 const I2CBus::Speed requestedSpeed) :
    AT24CxxType2(bus, address, requestedSpeed, Variant::AT24C08)
{
    ASSERT((address & 0x03) == 0);  // pins A0+A1 not used
}

AT24C16::AT24C16(I2CBus* bus, const I2CBus::Address address,
                 const I2CBus::Speed requestedSpeed) :
    AT24CxxType2(bus, address, requestedSpeed, Variant::AT24C16)
{
    ASSERT((address & 0x07) == 0);  // pins A0+A1+A2 not used
}

}  // namespace ExternalHAL
}  // namespace Springboard

#endif  // #if SPRINGBOARD_HAL_ENABLE_I2C
