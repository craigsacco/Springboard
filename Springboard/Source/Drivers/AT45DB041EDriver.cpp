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

#include <Springboard/Drivers/AT45DB041EDriver.hpp>

#if SPRINGBOARD_HAL_ENABLE_SPI

using Springboard::ExternalHAL::AT45DB041E;
using Springboard::Utilities::ByteArray;

namespace Springboard {
namespace Drivers {

AT45DB041EDriver::AT45DB041EDriver(
    Springboard::Infrastructure::Controller* controller,
    const ResourceIdentifier identifier, const char* name,
    AT45DB041E* driver)
    : Resource(controller, identifier, ResourceType::ExternalFlash, name),
      mDriver(driver)
{
}

ResultCode AT45DB041EDriver::GetWriteProtectState(bool* state)
{
    return mDriver->GetWriteProtectState(state);
}

ResultCode AT45DB041EDriver::SetWriteProtectState(bool state)
{
    return mDriver->SetWriteProtectState(state);
}

ResultCode AT45DB041EDriver::GetResetState(bool* state)
{
    return mDriver->GetResetState(state);
}

ResultCode AT45DB041EDriver::SetResetState(bool state)
{
    return mDriver->SetResetState(state);
}

ResultCode AT45DB041EDriver::ReadJEDECInfo(ByteArray bytes)
{
    return mDriver->ReadJEDECInfo(bytes);
}

}  // namespace Drivers
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_SPI
