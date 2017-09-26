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

#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <board.h>
#include <hal.h>
#include <chprintf.h>
#include <chversion.h>
#include <cstring>

namespace Springboard {
namespace InternalHAL {

void Initialise()
{
    halInit();
}

const char* GetRTOSName()
{
    return "ChibiOS/RT";
}

const char* GetRTOSVersion()
{
    return CH_VERSION;
}

const char* GetRTOSPortInfo()
{
    return PORT_INFO;
}

const char* GetMCUArchitectureName()
{
    return PORT_ARCHITECTURE_NAME;
}

const char* GetMCUArchitectureRevision()
{
    return __CM4_REV_STR;
}

const char* GetMCUCoreVariantName()
{
    return PORT_CORE_VARIANT_NAME;
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

}  // namespace InternalHAL
}  // namespace Springboard
