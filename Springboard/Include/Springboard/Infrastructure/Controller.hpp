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
#include <Springboard/InternalHAL/PeripheralFactory.hpp>

namespace Springboard {
namespace Infrastructure {

class Controller : public Springboard::Infrastructure::Resource
{
public:
    Controller(const ResourceIdentifier identifier, const char* name);

    virtual void Start();

    PROPERTY_GET_HANDLER(Controller, Resource)
    PROPERTY_SET_HANDLER(Controller, Resource)

protected:
    Springboard::InternalHAL::PeripheralFactory mPeripheralFactory;

private:
    PROPERTY_TABLE_START(Controller, 0)
    /*
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
    */
    PROPERTY_TABLE_END()
};

}  // namespace Infrastructure
}  // namespace Springboard
