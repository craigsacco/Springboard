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

#include <Springboard/ExternalHAL/MCP23017.hpp>

#if SPRINGBOARD_HAL_ENABLE_I2C

namespace Springboard {
namespace ExternalHAL {

MCP23017::MCP23017(Springboard::InternalHAL::I2CBus* bus,
                   const Address address, const Speed speed)
    : Springboard::InternalHAL::I2CDevice(bus, address, speed, MAX_SPEED)
{
    ASSERT(address >= 0x20 && address <= 0x27);
}

ResultCode MCP23017::ReadRegister(const Register reg, uint8_t* value)
{
    const uint8_t input = static_cast<uint8_t>(reg);
    return TransmitAndReceive(ConstByteArray::FromSingleRef(input),
                              ByteArray::FromSinglePtr(value));
}

ResultCode MCP23017::ReadRegisterPair(const Register reg, uint16_t* value)
{
    const uint8_t input = static_cast<uint8_t>(reg);
    ASSERT((input & 0x01) == 0x00);
    uint8_t output[2];
    ResultCode result = TransmitAndReceive(ConstByteArray::FromSingleRef(input),
                                           output);
    *value = (output[0] | (static_cast<uint16_t>(output[1]) << 8U));
    return result;
}

ResultCode MCP23017::WriteRegister(const Register reg, const uint8_t value)
{
    const uint8_t input[2] = { static_cast<uint8_t>(reg), value };
    ASSERT((input[0] & 0x01) == 0x00);
    return Transmit(input);
}

ResultCode MCP23017::WriteRegisterPair(const Register reg, const uint16_t value)
{
    const uint8_t input[3] = { static_cast<uint8_t>(reg),
                               static_cast<uint8_t>(value & 0xff),
                               static_cast<uint8_t>((value >> 8U) & 0xff) };
    return Transmit(input);
}

}  // namespace ExternalHAL
}  // namespace Springboard

#endif  // #if SPRINGBOARD_HAL_ENABLE_I2C
