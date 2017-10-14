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

#if SPRINGBOARD_HAL_ENABLE_I2C

using Springboard::ExternalHAL::PCF8574;

namespace Springboard {
namespace Drivers {

PCF8574Driver::PCF8574Driver(
    Springboard::Infrastructure::Controller* controller,
    const ResourceIdentifier identifier, const char* name, PCF8574* driver)
    : Resource(controller, identifier, ResourceType::IOExpander, name),
      mDriver(driver)
{
}

ResultCode PCF8574Driver::ReadPort(uint8_t* value)
{
    return mDriver->ReadPort(value);
}

ResultCode PCF8574Driver::WritePort(const uint8_t value)
{
    return mDriver->WritePort(value);
}

}  // namespace Drivers
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_I2C
