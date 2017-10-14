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

#if SPRINGBOARD_HAL_ENABLE_I2C

using Springboard::ExternalHAL::MCP23017;

namespace Springboard {
namespace Drivers {

MCP23017Driver::MCP23017Driver(
    Springboard::Infrastructure::Controller* controller,
    const ResourceIdentifier identifier, const char* name, MCP23017* driver)
    : Resource(controller, identifier, ResourceType::IOExpander, name),
      mDriver(driver)
{
}

ResultCode MCP23017Driver::ReadIODIRx(uint16_t* value)
{
    return mDriver->ReadIODIRx(value);
}

ResultCode MCP23017Driver::ReadIPOLx(uint16_t* value)
{
    return mDriver->ReadIPOLx(value);
}

ResultCode MCP23017Driver::ReadGPINTENx(uint16_t* value)
{
    return mDriver->ReadGPINTENx(value);
}

ResultCode MCP23017Driver::ReadDEFVALx(uint16_t* value)
{
    return mDriver->ReadDEFVALx(value);
}

ResultCode MCP23017Driver::ReadINTCONx(uint16_t* value)
{
    return mDriver->ReadINTCONx(value);
}

ResultCode MCP23017Driver::ReadIOCON(uint8_t* value)
{
    return mDriver->ReadIOCON(value);
}

ResultCode MCP23017Driver::ReadGPPUx(uint16_t* value)
{
    return mDriver->ReadGPPUx(value);
}

ResultCode MCP23017Driver::ReadINTFx(uint16_t* value)
{
    return mDriver->ReadINTFx(value);
}

ResultCode MCP23017Driver::ReadINTCAPx(uint16_t* value)
{
    return mDriver->ReadINTCAPx(value);
}

ResultCode MCP23017Driver::ReadPORTx(uint16_t* value)
{
    return mDriver->ReadPORTx(value);
}

ResultCode MCP23017Driver::ReadOLATx(uint16_t* value)
{
    return mDriver->ReadOLATx(value);
}

ResultCode MCP23017Driver::WriteIODIRx(const uint16_t value)
{
    return mDriver->WriteIODIRx(value);
}

ResultCode MCP23017Driver::WriteIPOLx(const uint16_t value)
{
    return mDriver->WriteIPOLx(value);
}

ResultCode MCP23017Driver::WriteGPINTENx(const uint16_t value)
{
    return mDriver->WriteGPINTENx(value);
}

ResultCode MCP23017Driver::WriteDEFVALx(const uint16_t value)
{
    return mDriver->WriteDEFVALx(value);
}

ResultCode MCP23017Driver::WriteINTCONx(const uint16_t value)
{
    return mDriver->WriteINTCONx(value);
}

ResultCode MCP23017Driver::WriteIOCON(const uint8_t value)
{
    return mDriver->WriteIOCON(value);
}

ResultCode MCP23017Driver::WriteGPPUx(const uint16_t value)
{
    return mDriver->WriteGPPUx(value);
}

ResultCode MCP23017Driver::WriteINTFx(const uint16_t value)
{
    return mDriver->WriteINTFx(value);
}

ResultCode MCP23017Driver::WriteINTCAPx(const uint16_t value)
{
    return mDriver->WriteINTCAPx(value);
}

ResultCode MCP23017Driver::WritePORTx(const uint16_t value)
{
    return mDriver->WritePORTx(value);
}

ResultCode MCP23017Driver::WriteOLATx(const uint16_t value)
{
    return mDriver->WriteOLATx(value);
}

}  // namespace Drivers
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_I2C
