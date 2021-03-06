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

#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/Infrastructure/Resource.hpp>

#if SPRINGBOARD_HAL_ENABLE_I2C

namespace Springboard {

namespace ExternalHAL { class PCF8574; }

namespace Drivers {

class PCF8574Driver : public Springboard::Infrastructure::Resource
{
public:
    PCF8574Driver(Springboard::Infrastructure::Controller* controller,
                  const ResourceIdentifier identifier,
                  const char* name,
                  Springboard::ExternalHAL::PCF8574* driver);

    ResultCode ReadPort(uint8_t* value);
    ResultCode WritePort(const uint8_t value);

    PROPERTY_GET_HANDLER(PCF8574Driver, Springboard::Infrastructure::Resource)
    PROPERTY_SET_HANDLER(PCF8574Driver, Springboard::Infrastructure::Resource)

private:
    Springboard::ExternalHAL::PCF8574* mDriver;

    PROPERTY_TABLE_START(PCF8574Driver, 1)
    PROPERTY_ENTRY_UINT8_RW(PCF8574Driver, 100, "PORT", ReadPort, WritePort)
    PROPERTY_TABLE_END()
};

}  // namespace Drivers
}  // namespace Springboard

#endif  // #if SPRINGBOARD_HAL_ENABLE_I2C
