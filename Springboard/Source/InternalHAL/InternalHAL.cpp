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

#include <cstring>
#include <stm32f4xx_des.h>
#include <Springboard/InternalHAL/InternalHAL.hpp>

namespace Springboard {
namespace InternalHAL {

const char* GetRTOSName()
{
    return "FreeRTOS";
}

const char* GetRTOSVersion()
{
    return tskKERNEL_VERSION_NUMBER;
}

const char* GetRTOSPortInfo()
{
    return "";
}

const char* GetMCUArchitectureName()
{
    return "";
}

const char* GetMCUArchitectureRevision()
{
    return "";
}

const char* GetMCUCoreVariantName()
{
    return "";
}

uint32_t GetMCUDeviceId()
{
    return DBGMCU->IDCODE;
}

bool GetMCUUniqueId(Springboard::Utilities::ByteArray buffer)
{
    // ensure that the provided buffer can accomodate the identifier
    if (buffer.GetSize() < MCU_UNIQUE_ID_LENGTH) {
        return false;
    }

    memcpy(buffer.GetData(), DES->UID.data, MCU_UNIQUE_ID_LENGTH);
    return true;
}

const char* GetMCUFamilyName()
{
    return MCU_FAMILY_NAME;
}

const char* GetMCULineName()
{
    return MCU_LINE_NAME;
}

const char* GetMCUVariantName()
{
    return MCU_NAME;
}

}  // namespace InternalHAL
}  // namespace Springboard
