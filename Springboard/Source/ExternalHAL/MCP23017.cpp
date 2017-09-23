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
    : Springboard::InternalHAL::I2CDevice(bus, address, speed)
{
    ASSERT(address >= 0x20 && address <= 0x27);
}

uint16_t MCP23017::ReadIODIRx()
{
    return ReadRegisterPair(Register::IODIRA);
}

uint16_t MCP23017::ReadIPOLx()
{
    return ReadRegisterPair(Register::IPOLA);
}

uint16_t MCP23017::ReadGPINTENx()
{
    return ReadRegisterPair(Register::GPINTENA);
}

uint16_t MCP23017::ReadDEFVALx()
{
    return ReadRegisterPair(Register::DEFVALA);
}

uint16_t MCP23017::ReadINTCONx()
{
    return ReadRegisterPair(Register::INTCONA);
}

uint8_t MCP23017::ReadIOCON()
{
    return ReadRegister(Register::IOCON);
}

uint16_t MCP23017::ReadGPPUx()
{
    return ReadRegisterPair(Register::GPPUA);
}

uint16_t MCP23017::ReadINTFx()
{
    return ReadRegisterPair(Register::INTFA);
}

uint16_t MCP23017::ReadINTCAPx()
{
    return ReadRegisterPair(Register::INTCAPA);
}

uint16_t MCP23017::ReadPORTx()
{
    return ReadRegisterPair(Register::PORTA);
}

uint16_t MCP23017::ReadOLATx()
{
    return ReadRegisterPair(Register::OLATA);
}

void MCP23017::WriteIODIRx(const uint16_t value)
{
    return WriteRegisterPair(Register::IODIRA, value);
}

void MCP23017::WriteIPOLx(const uint16_t value)
{
    return WriteRegisterPair(Register::IPOLA, value);
}

void MCP23017::WriteGPINTENx(const uint16_t value)
{
    return WriteRegisterPair(Register::GPINTENA, value);
}

void MCP23017::WriteDEFVALx(const uint16_t value)
{
    return WriteRegisterPair(Register::DEFVALA, value);
}

void MCP23017::WriteINTCONx(const uint16_t value)
{
    return WriteRegisterPair(Register::INTCONA, value);
}

void MCP23017::WriteIOCON(const uint8_t value)
{
    // only INTPOL, ODR and MIRROR pins are settable
    static const uint8_t mask = (static_cast<uint8_t>(IOCONBits::INTPOL) |
                                 static_cast<uint8_t>(IOCONBits::ODR) |
                                 static_cast<uint8_t>(IOCONBits::MIRROR));
    return WriteRegister(Register::IOCON, value & mask);
}

void MCP23017::WriteGPPUx(const uint16_t value)
{
    return WriteRegisterPair(Register::GPPUA, value);
}

void MCP23017::WriteINTFx(const uint16_t value)
{
    return WriteRegisterPair(Register::INTFA, value);
}

void MCP23017::WriteINTCAPx(const uint16_t value)
{
    return WriteRegisterPair(Register::INTCAPA, value);
}

void MCP23017::WritePORTx(const uint16_t value)
{
    return WriteRegisterPair(Register::PORTA, value);
}

void MCP23017::WriteOLATx(const uint16_t value)
{
    return WriteRegisterPair(Register::OLATA, value);
}

uint8_t MCP23017::ReadRegister(const Register reg)
{
    const uint8_t input = static_cast<uint8_t>(reg);
    uint8_t output;
    TransmitAndReceive(&input, 1, &output, 1);
    return output;
}

uint16_t MCP23017::ReadRegisterPair(const Register reg)
{
    const uint8_t input = static_cast<uint8_t>(reg);
    uint8_t output[2];
    TransmitAndReceive(&input, 1, output, 2);
    return output[0] | (static_cast<uint16_t>(output[1]) << 8U);
}

void MCP23017::WriteRegister(const Register reg, uint8_t value)
{
    const uint8_t input[2] = { static_cast<uint8_t>(reg), value };
    Transmit(input, 2);
}

void MCP23017::WriteRegisterPair(const Register reg, uint16_t value)
{
    const uint8_t input[3] = { static_cast<uint8_t>(reg),
                               static_cast<uint8_t>(value & 0xff),
                               static_cast<uint8_t>((value >> 8U) & 0xff) };
    Transmit(input, 3);
}

}  // namespace ExternalHAL
}  // namespace Springboard

#endif  // #if SPRINGBOARD_HAL_ENABLE_I2C
