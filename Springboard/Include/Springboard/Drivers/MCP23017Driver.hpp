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

#include <Springboard/Infrastructure/Resource.hpp>

namespace Springboard {

namespace ExternalHAL { class MCP23017; }

namespace Drivers {

class MCP23017Driver : public Springboard::Infrastructure::Resource
{
public:
    MCP23017Driver(Springboard::Infrastructure::Controller* controller,
                   const ResourceIdentifier identifier,
                   const char* name,
                   Springboard::ExternalHAL::MCP23017* driver);

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

    PROPERTY_GET_HANDLER(MCP23017Driver, Springboard::Infrastructure::Resource)
    PROPERTY_SET_HANDLER(MCP23017Driver, Springboard::Infrastructure::Resource)

private:
    Springboard::ExternalHAL::MCP23017* mDriver;

    PROPERTY_TABLE_START(MCP23017Driver, 11)
    PROPERTY_ENTRY_UINT16_RW(MCP23017Driver, 100, "IODIR", ReadIODIRx,
                             WriteIODIRx)
    PROPERTY_ENTRY_UINT16_RW(MCP23017Driver, 101, "IPOL", ReadIPOLx, WriteIPOLx)
    PROPERTY_ENTRY_UINT16_RW(MCP23017Driver, 102, "GPINTEN", ReadGPINTENx,
                             WriteGPINTENx)
    PROPERTY_ENTRY_UINT16_RW(MCP23017Driver, 103, "DEFVAL", ReadDEFVALx,
                             WriteDEFVALx)
    PROPERTY_ENTRY_UINT16_RW(MCP23017Driver, 104, "INTCON", ReadINTCONx,
                             WriteINTCONx)
    PROPERTY_ENTRY_UINT8_RW(MCP23017Driver, 105, "IOCON", ReadIOCON, WriteIOCON)
    PROPERTY_ENTRY_UINT16_RW(MCP23017Driver, 106, "GPPU", ReadGPPUx, WriteGPPUx)
    PROPERTY_ENTRY_UINT16_RW(MCP23017Driver, 107, "INTF", ReadINTFx, WriteINTFx)
    PROPERTY_ENTRY_UINT16_RW(MCP23017Driver, 108, "INTCAP", ReadINTCAPx,
                             WriteINTCAPx)
    PROPERTY_ENTRY_UINT16_RW(MCP23017Driver, 109, "PORT", ReadPORTx, WritePORTx)
    PROPERTY_ENTRY_UINT16_RW(MCP23017Driver, 110, "OLAT", ReadOLATx, WriteOLATx)
    PROPERTY_TABLE_END()
};

}  // namespace Drivers
}  // namespace Springboard
