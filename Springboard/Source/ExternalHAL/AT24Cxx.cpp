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
using Springboard::Kernel::ScopedMutex;
using Springboard::Utilities::ByteArray;
using Springboard::Utilities::ConstByteArray;

namespace Springboard {
namespace ExternalHAL {

AT24Cxx::AT24Cxx(I2CBus* bus, const I2CBus::Address address,
                 const I2CBus::Speed requestedSpeed,
                 Variant variant)
    : I2CDevice(bus, address, requestedSpeed, MAX_SPEED),
      mVariant(variant), mMutex()
{
    ASSERT(address >= 0x50 && address <= 0x57);
}

ResultCode AT24Cxx::Read(size_t offset, ByteArray data, size_t* read)
{
    if (offset >= GetSize() ||
        offset + data.GetSize() >= GetSize()) {
        return RC_AT45DBXX_INVALID_OFFSET_OR_SIZE;
    }

    if (read != nullptr) {
        *read = 0;
    }

    ScopedMutex mutex(&mMutex);

    size_t bytesRemaining = data.GetSize();
    size_t dataOffset = 0;
    while (bytesRemaining > 0) {
        uint8_t page = static_cast<uint8_t>(offset >> 8);
        uint8_t pageOffset = static_cast<uint8_t>(offset & 0xff);
        uint16_t pageBytesRemaining = 256U - pageOffset;
        uint8_t chunkSize = (bytesRemaining < GetMaxChunkSize() ?
                             bytesRemaining :
                             (pageBytesRemaining < GetMaxChunkSize() ?
                              pageBytesRemaining : GetMaxChunkSize()));

        // write page/offset
        ResultCode result = TransmitEx(
            GetAddress() + page, ConstByteArray::FromSingleRef(pageOffset));
        if (result != RC_OK) {
            return result;
        }

        // read chunk
        result = ReceiveEx(GetAddress() + page, data.Mid(dataOffset, chunkSize));
        if (result != RC_OK) {
            return result;
        }

        if (read != nullptr) {
            *read += chunkSize;
        }

        bytesRemaining -= chunkSize;
        offset += chunkSize;
        dataOffset += chunkSize;
    }

    return RC_OK;
}

ResultCode AT24Cxx::Write(size_t offset,  ConstByteArray data, size_t* write)
{
    if (offset >= GetSize() ||
        offset + data.GetSize() >= GetSize()) {
        return RC_AT45DBXX_INVALID_OFFSET_OR_SIZE;
    }

    ASSERT(GetMaxChunkSize() < 16);

    uint8_t writeData[16] = { 0x00 };
    ByteArray writeArray(writeData);

    if (write != nullptr) {
        *write = 0;
    }

    ScopedMutex mutex(&mMutex);

    size_t bytesRemaining = data.GetSize();
    size_t dataOffset = 0;
    while (bytesRemaining > 0) {
        uint8_t page = static_cast<uint8_t>(offset >> 8);
        uint8_t pageOffset = static_cast<uint8_t>(offset & 0xff);
        uint16_t pageBytesRemaining = 256U - pageOffset;
        uint8_t chunkSize = (bytesRemaining < GetMaxChunkSize() ?
                             bytesRemaining :
                             (pageBytesRemaining < GetMaxChunkSize() ?
                              pageBytesRemaining : GetMaxChunkSize()));

        // construct write buffer
        writeArray[0] = pageOffset;
        data.Mid(dataOffset, chunkSize).CopyTo(writeArray.From(1));

        // write data
        ResultCode result = TransmitEx(GetAddress() + page,
                                       writeArray.ToConst());
        if (result != RC_OK) {
            return result;
        }

        if (write != nullptr) {
            *write += chunkSize;
        }

        bytesRemaining -= chunkSize;
        offset += chunkSize;
        dataOffset += chunkSize;
    }

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

AT24CxxType2::AT24CxxType2(I2CBus* bus, const I2CBus::Address address,
                           const I2CBus::Speed requestedSpeed,
                           Variant variant)
    : AT24Cxx(bus, address, requestedSpeed, variant)
{
    ASSERT(variant == Variant::AT24C04 || variant == Variant::AT24C08 ||
           variant == Variant::AT24C16);
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
