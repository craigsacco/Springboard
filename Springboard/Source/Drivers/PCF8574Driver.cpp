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

#include <Springboard/Drivers/PCF8574Driver.hpp>
#include <Springboard/ExternalHAL/PCF8574.hpp>

namespace Springboard {
namespace Drivers {

PROPERTY_TABLE_START(PCF8574Driver)
PROPERTY_ENTRY_UINT8(PCF8574Driver, 100, "ReadPort", ReadPort)
PROPERTY_TABLE_END()

PCF8574Driver::PCF8574Driver(const PCF8574Driver::ResourceIdentifier identifier,
                             Springboard::ExternalHAL::PCF8574* driver) :
    Resource(identifier),
    mDriver(driver)
{
}

uint8_t PCF8574Driver::ReadPort() const
{
    return mDriver->ReadPort();
}

}  // namespace Drivers
}  // namespace Springboard
