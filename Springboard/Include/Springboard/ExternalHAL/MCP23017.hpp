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

#if SPRINGBOARD_HAL_ENABLE_I2C

namespace Springboard {
namespace ExternalHAL {

class MCP23017 : public Springboard::InternalHAL::I2CDevice
{
public:
    MCP23017(Springboard::InternalHAL::I2CBus* bus, const Address address,
             const Speed requestedSpeed);

    ResultCode ReadIODIRx(uint16_t* value);
    ResultCode ReadIPOLx(uint16_t* value);
    ResultCode ReadGPINTENx(uint16_t* value);
    ResultCode ReadDEFVALx(uint16_t* value);
    ResultCode ReadINTCONx(uint16_t* value);
    ResultCode ReadIOCON(uint8_t* value);
    ResultCode ReadGPPUx(uint16_t* value);
    ResultCode ReadINTFx(uint16_t* value);
    ResultCode ReadINTCAPx(uint16_t* value);
    ResultCode ReadPORTx(uint16_t* value);
    ResultCode ReadOLATx(uint16_t* value);
    ResultCode WriteIODIRx(const uint16_t value);
    ResultCode WriteIPOLx(const uint16_t value);
    ResultCode WriteGPINTENx(const uint16_t value);
    ResultCode WriteDEFVALx(const uint16_t value);
    ResultCode WriteINTCONx(const uint16_t value);
    ResultCode WriteIOCON(const uint8_t value);
    ResultCode WriteGPPUx(const uint16_t value);
    ResultCode WriteINTFx(const uint16_t value);
    ResultCode WriteINTCAPx(const uint16_t value);
    ResultCode WritePORTx(const uint16_t value);
    ResultCode WriteOLATx(const uint16_t value);

private:
    enum class Register : uint8_t
    {
        IODIRA = 0x00,
        IODIRB = 0x01,
        IPOLA = 0x02,
        IPOLB = 0x03,
        GPINTENA = 0x04,
        GPINTENB = 0x05,
        DEFVALA = 0x06,
        DEFVALB = 0x07,
        INTCONA = 0x08,
        INTCONB = 0x09,
        IOCON = 0x0A,
        GPPUA = 0x0C,
        GPPUB = 0x0D,
        INTFA = 0x0E,
        INTFB = 0x0F,
        INTCAPA = 0x10,
        INTCAPB = 0x11,
        PORTA = 0x12,
        PORTB = 0x13,
        OLATA = 0x14,
        OLATB = 0x15,
    };

    enum class IOCONBits : uint8_t
    {
        INTPOL = (1 << 1U),
        ODR = (1 << 2U),
        HAEN = (1 << 3U),
        DISSLW = (1 << 4U),
        SEQOP = (1 << 5U),
        MIRROR = (1 << 6U),
        BANK = (1 << 7U),
    };

    ResultCode ReadRegister(const Register reg, uint8_t* value);
    ResultCode ReadRegisterPair(const Register reg, uint16_t* value);
    ResultCode WriteRegister(const Register reg, const uint8_t value);
    ResultCode WriteRegisterPair(const Register reg, const uint16_t value);

    static constexpr Speed MAX_SPEED = 1700000U;
};

}  // namespace ExternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_I2C
