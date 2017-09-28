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

#include <Springboard/InternalHAL/SPIDevice.hpp>

#if SPRINGBOARD_HAL_ENABLE_SPI

namespace Springboard {
namespace ExternalHAL {

class AT45DB041E : public Springboard::InternalHAL::SPIDevice
{
public:
    AT45DB041E(Springboard::InternalHAL::SPIBus* bus,
               Springboard::CommonHAL::IDigitalOutput* selectPin,
               const Speed requestedSpeed,
               Springboard::CommonHAL::IDigitalOutput* writeProtectPin,
               Springboard::CommonHAL::IDigitalOutput* resetPin);

    ResultCode GetWriteProtectState(bool* state);
    ResultCode SetWriteProtectState(bool state);
    ResultCode GetResetState(bool* state);
    ResultCode SetResetState(bool state);
    ResultCode ReadJEDECInfo(ByteArray bytes);

    static constexpr size_t JEDEC_INFO_LENGTH = 5;

private:
    enum class OpCodes : uint8_t {
        JedecInfo = 0x9F,
    };

    static constexpr Speed MAX_SPEED = 50000000U;

    Springboard::CommonHAL::IDigitalOutput* mWriteProtectPin;
    Springboard::CommonHAL::IDigitalOutput* mResetPin;
};

}  // namespace ExternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_SPI
