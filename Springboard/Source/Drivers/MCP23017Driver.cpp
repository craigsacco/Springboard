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

#include <Springboard/Drivers/MCP23017Driver.hpp>
#include <Springboard/ExternalHAL/MCP23017.hpp>

using Springboard::ExternalHAL::MCP23017;

namespace Springboard {
namespace Drivers {

MCP23017Driver::MCP23017Driver(
    Springboard::Infrastructure::IResourceOwner* owner,
    const ResourceIdentifier identifier, const char* name, MCP23017* driver)
    : Resource(owner, identifier, ResourceType::IOExpander, name),
      mDriver(driver)
{
}

ResultCode MCP23017Driver::ReadIODIRx(uint16_t* value)
{
    return mDriver->ReadRegisterPair(MCP23017::Register::IODIRA, value);
}

ResultCode MCP23017Driver::ReadIPOLx(uint16_t* value)
{
    return mDriver->ReadRegisterPair(MCP23017::Register::IPOLA, value);
}

ResultCode MCP23017Driver::ReadGPINTENx(uint16_t* value)
{
    return mDriver->ReadRegisterPair(MCP23017::Register::GPINTENA, value);
}

ResultCode MCP23017Driver::ReadDEFVALx(uint16_t* value)
{
    return mDriver->ReadRegisterPair(MCP23017::Register::DEFVALA, value);
}

ResultCode MCP23017Driver::ReadINTCONx(uint16_t* value)
{
    return mDriver->ReadRegisterPair(MCP23017::Register::INTCONA, value);
}

ResultCode MCP23017Driver::ReadIOCON(uint8_t* value)
{
    return mDriver->ReadRegister(MCP23017::Register::IOCON, value);
}

ResultCode MCP23017Driver::ReadGPPUx(uint16_t* value)
{
    return mDriver->ReadRegisterPair(MCP23017::Register::GPPUA, value);
}

ResultCode MCP23017Driver::ReadINTFx(uint16_t* value)
{
    return mDriver->ReadRegisterPair(MCP23017::Register::INTFA, value);
}

ResultCode MCP23017Driver::ReadINTCAPx(uint16_t* value)
{
    return mDriver->ReadRegisterPair(MCP23017::Register::INTCAPA, value);
}

ResultCode MCP23017Driver::ReadPORTx(uint16_t* value)
{
    return mDriver->ReadRegisterPair(MCP23017::Register::PORTA, value);
}

ResultCode MCP23017Driver::ReadOLATx(uint16_t* value)
{
    return mDriver->ReadRegisterPair(MCP23017::Register::OLATA, value);
}

ResultCode MCP23017Driver::WriteIODIRx(const uint16_t value)
{
    return mDriver->WriteRegisterPair(MCP23017::Register::IODIRA, value);
}

ResultCode MCP23017Driver::WriteIPOLx(const uint16_t value)
{
    return mDriver->WriteRegisterPair(MCP23017::Register::IPOLA, value);
}

ResultCode MCP23017Driver::WriteGPINTENx(const uint16_t value)
{
    return mDriver->WriteRegisterPair(MCP23017::Register::GPINTENA, value);
}

ResultCode MCP23017Driver::WriteDEFVALx(const uint16_t value)
{
    return mDriver->WriteRegisterPair(MCP23017::Register::DEFVALA, value);
}

ResultCode MCP23017Driver::WriteINTCONx(const uint16_t value)
{
    return mDriver->WriteRegisterPair(MCP23017::Register::INTCONA, value);
}

ResultCode MCP23017Driver::WriteIOCON(const uint8_t value)
{
    // only INTPOL, ODR and MIRROR bits are settable - setting any other
    // bits in this register will cause this driver to malfunction
    static const uint8_t mask = (
        static_cast<uint8_t>(MCP23017::IOCONBits::INTPOL) |
        static_cast<uint8_t>(MCP23017::IOCONBits::ODR) |
        static_cast<uint8_t>(MCP23017::IOCONBits::MIRROR));
    return mDriver->WriteRegister(MCP23017::Register::IOCON, value & mask);
}

ResultCode MCP23017Driver::WriteGPPUx(const uint16_t value)
{
    return mDriver->WriteRegister(MCP23017::Register::GPPUA, value);
}

ResultCode MCP23017Driver::WriteINTFx(const uint16_t value)
{
    return mDriver->WriteRegister(MCP23017::Register::INTFA, value);
}

ResultCode MCP23017Driver::WriteINTCAPx(const uint16_t value)
{
    return mDriver->WriteRegister(MCP23017::Register::INTCAPA, value);
}

ResultCode MCP23017Driver::WritePORTx(const uint16_t value)
{
    return mDriver->WriteRegister(MCP23017::Register::PORTA, value);
}

ResultCode MCP23017Driver::WriteOLATx(const uint16_t value)
{
    return mDriver->WriteRegister(MCP23017::Register::OLATA, value);
}

}  // namespace Drivers
}  // namespace Springboard
