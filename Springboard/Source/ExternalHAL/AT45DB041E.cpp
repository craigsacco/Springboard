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

#include <Springboard/ExternalHAL/AT45DB041E.hpp>
#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/CommonHAL/IDigitalOutput.hpp>

#if SPRINGBOARD_HAL_ENABLE_SPI

using Springboard::CommonHAL::IDigitalOutput;
using Springboard::InternalHAL::SPIBus;
using Springboard::Utilities::ByteArray;
using Springboard::Utilities::ConstByteArray;

namespace Springboard {
namespace ExternalHAL {

AT45DB041E::AT45DB041E(
    SPIBus* bus, IDigitalOutput* selectPin, const SPIBus::Speed requestedSpeed,
    IDigitalOutput* writeProtectPin, IDigitalOutput* resetPin)
    : Springboard::InternalHAL::SPIDevice(
        bus, selectPin,
        Springboard::InternalHAL::SPIClockConfig::Mode0_CPOL0_CPHA0,
        requestedSpeed, MAX_SPEED),
      mWriteProtectPin(writeProtectPin), mResetPin(resetPin)
{
    // enable write protection by default, and put the chip in reset
    if (mWriteProtectPin != nullptr) {
        mWriteProtectPin->Clear();
    }
    if (mResetPin != nullptr) {
        mResetPin->Clear();
    }
}

ResultCode AT45DB041E::GetWriteProtectState(bool* state)
{
    if (mWriteProtectPin == nullptr) {
        return RC_AT45DBXX_NO_nWP_PIN;
    }

    *state = !mWriteProtectPin->Get();  // invert
    return RC_OK;
}

ResultCode AT45DB041E::SetWriteProtectState(bool state)
{
    if (mWriteProtectPin == nullptr) {
        return RC_AT45DBXX_NO_nWP_PIN;
    }

    mWriteProtectPin->Set(!state);  // invert
    return RC_OK;
}

ResultCode AT45DB041E::GetResetState(bool* state)
{
    if (mWriteProtectPin == nullptr) {
        return RC_AT45DBXX_NO_nRST_PIN;
    }

    *state = !mResetPin->Get();  // invert
    return RC_OK;
}

ResultCode AT45DB041E::SetResetState(bool state)
{
    if (mWriteProtectPin == nullptr) {
        return RC_AT45DBXX_NO_nRST_PIN;
    }

    mResetPin->Set(!state);  // invert
    return RC_OK;
}

ResultCode AT45DB041E::ReadJEDECInfo(ByteArray bytes)
{
    if (bytes.GetSize() < JEDEC_INFO_LENGTH) {
        return RC_AT45DBXX_JEDEC_BUFFER_TOO_SMALL;
    }

    uint8_t opcode[1] = { static_cast<uint8_t>(OpCodes::JedecInfo) };
    return TransmitAndReceive(opcode, bytes.Left(5));
}

}  // namespace ExternalHAL
}  // namespace Springboard

#endif  // #if SPRINGBOARD_HAL_ENABLE_SPI
