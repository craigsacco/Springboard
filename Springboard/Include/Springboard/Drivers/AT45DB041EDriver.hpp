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
#include <Springboard/ExternalHAL/AT45DB041E.hpp>

namespace Springboard {

namespace Drivers {

class AT45DB041EDriver : public Springboard::Infrastructure::Resource
{
public:
    AT45DB041EDriver(Springboard::Infrastructure::Controller* controller,
                     const ResourceIdentifier identifier,
                     const char* name,
                     Springboard::ExternalHAL::AT45DB041E* driver);

    ResultCode GetWriteProtectState(bool* state);
    ResultCode SetWriteProtectState(bool state);
    ResultCode GetResetState(bool* state);
    ResultCode SetResetState(bool state);
    ResultCode ReadJEDECInfo(ByteArray bytes);

    PROPERTY_GET_HANDLER(AT45DB041EDriver,
                         Springboard::Infrastructure::Resource)
    PROPERTY_SET_HANDLER(AT45DB041EDriver,
                         Springboard::Infrastructure::Resource)

private:
    Springboard::ExternalHAL::AT45DB041E* mDriver;

    PROPERTY_TABLE_START(AT45DB041EDriver, 3)
    PROPERTY_ENTRY_BOOL_RW(AT45DB041EDriver, 100, "WriteProtectState",
                           GetWriteProtectState, SetWriteProtectState)
    PROPERTY_ENTRY_BOOL_RW(AT45DB041EDriver, 101, "ResetState",
                            GetResetState, SetResetState)
    PROPERTY_ENTRY_BYTEARRAY_RO(
        AT45DB041EDriver, 102, "JEDECInfo",
        Springboard::ExternalHAL::AT45DB041E::JEDEC_INFO_LENGTH, ReadJEDECInfo)
    PROPERTY_TABLE_END()
};

}  // namespace Drivers
}  // namespace Springboard
