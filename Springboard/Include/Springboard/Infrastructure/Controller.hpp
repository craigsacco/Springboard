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

#include <chversion.h>
#include <Springboard/Infrastructure/Resource.hpp>
#include <Springboard/InternalHAL/PeripheralFactory.hpp>
#include <Springboard/Kernel/Systime.hpp>
#include <Springboard/Utilities/Dictionary.hpp>

using Springboard::Utilities::ByteArray;
using Springboard::Utilities::CharArray;

namespace Springboard {
namespace Infrastructure {

class BaseController : public Resource
{
protected:
    BaseController(const ResourceIdentifier identifier, const char* name);
};

class Controller : public BaseController
{
public:
    Controller(const ResourceIdentifier identifier, const char* name);

    virtual void Start();

    void AddResource(Resource* resource);
    Resource* FindResource(ResourceIdentifier identifier);

    PROPERTY_GET_HANDLER(Controller, Resource)
    PROPERTY_SET_HANDLER(Controller, Resource)

protected:
    Springboard::InternalHAL::PeripheralFactory mPeripheralFactory;

private:
    ResultCode GetRTOSNamePropertyRequest(CharArray value)
    {
        Springboard::Utilities::ArrayReferenceUtils::SafeStringCopy(
            value, Springboard::InternalHAL::GetRTOSName());
        return RC_OK;
    }

    ResultCode GetRTOSVersionPropertyRequest(CharArray value)
    {
        Springboard::Utilities::ArrayReferenceUtils::SafeStringCopy(
            value, Springboard::InternalHAL::GetRTOSVersion());
        return RC_OK;
    }

    ResultCode GetRTOSPortInfoPropertyRequest(CharArray value)
    {
        Springboard::Utilities::ArrayReferenceUtils::SafeStringCopy(
            value, Springboard::InternalHAL::GetRTOSPortInfo());
        return RC_OK;
    }

    ResultCode GetMCUArchitectureNamePropertyRequest(CharArray value)
    {
        Springboard::Utilities::ArrayReferenceUtils::SafeStringCopy(
            value, Springboard::InternalHAL::GetMCUArchitectureName());
        return RC_OK;
    }

    ResultCode GetMCUArchitectureRevisionPropertyRequest(CharArray value)
    {
        Springboard::Utilities::ArrayReferenceUtils::SafeStringCopy(
            value, Springboard::InternalHAL::GetMCUArchitectureRevision());
        return RC_OK;
    }

    ResultCode GetMCUCoreVariantNamePropertyRequest(CharArray value)
    {
        Springboard::Utilities::ArrayReferenceUtils::SafeStringCopy(
            value, Springboard::InternalHAL::GetMCUCoreVariantName());
        return RC_OK;
    }

    ResultCode GetMCUDeviceIdPropertyRequest(uint32_t* value)
    {
        *value = Springboard::InternalHAL::GetMCUDeviceId();
        return RC_OK;
    }

    ResultCode GetMCUDeviceIdPropertyRequest(ByteArray value)
    {
        if (!Springboard::InternalHAL::GetMCUUniqueId(value)) {
            return RC_RESOURCE_INVALID_PROPERTY_LENGTH;
        }

        return RC_OK;
    }

    ResultCode GetSystemTimePropertyRequest(systime_t* value)
    {
        *value = Springboard::Kernel::Systime::Now();
        return RC_OK;
    }

    ResultCode GetRTCTimePropertyRequest(uint64_t* value)
    {
        return mPeripheralFactory.GetRTC(1)->GetTime(value);
    }

    ResultCode SetRTCTimePropertyRequest(uint64_t value)
    {
        return mPeripheralFactory.GetRTC(1)->SetTime(value);
    }

    ResultCode GetRTCTimeStringPropertyRequest(CharArray value)
    {
        return mPeripheralFactory.GetRTC(1)->GetTimeAsString(value);
    }

    ResultCode GetMCUFamilyPropertyRequest(CharArray value)
    {
        Springboard::Utilities::ArrayReferenceUtils::SafeStringCopy(
            value, Springboard::InternalHAL::GetMCUFamilyName());
        return RC_OK;
    }

    ResultCode GetMCULinePropertyRequest(CharArray value)
    {
        Springboard::Utilities::ArrayReferenceUtils::SafeStringCopy(
            value, Springboard::InternalHAL::GetMCULineName());
        return RC_OK;
    }

    ResultCode GetMCUVariantPropertyRequest(CharArray value)
    {
        Springboard::Utilities::ArrayReferenceUtils::SafeStringCopy(
            value, Springboard::InternalHAL::GetMCUVariantName());
        return RC_OK;
    }

    PROPERTY_TABLE_START(Controller, 14)
    PROPERTY_ENTRY_STRING_RO(Controller, 10, "RTOSName",
                             GetRTOSNamePropertyRequest)
    PROPERTY_ENTRY_STRING_RO(Controller, 11, "RTOSVersion",
                             GetRTOSVersionPropertyRequest)
    PROPERTY_ENTRY_STRING_RO(Controller, 12, "RTOSPortInfo",
                             GetRTOSPortInfoPropertyRequest)
    PROPERTY_ENTRY_STRING_RO(Controller, 13, "MCUArchitectureName",
                             GetMCUArchitectureNamePropertyRequest)
    PROPERTY_ENTRY_STRING_RO(Controller, 14, "MCUArchitectureRevision",
                             GetMCUArchitectureRevisionPropertyRequest)
    PROPERTY_ENTRY_STRING_RO(Controller, 15, "MCUCoreVariantName",
                             GetMCUCoreVariantNamePropertyRequest)
    PROPERTY_ENTRY_UINT32_RO(Controller, 16, "MCUDeviceId",
                             GetMCUDeviceIdPropertyRequest)
    PROPERTY_ENTRY_BYTEARRAY_RO(Controller, 17, "MCUUniqueId",
                                MCU_UNIQUE_ID_LENGTH,
                                GetMCUDeviceIdPropertyRequest)
    PROPERTY_ENTRY_UINT32_RO(Controller, 18, "SystemTime",
                             GetSystemTimePropertyRequest)
    PROPERTY_ENTRY_UINT64_RW(Controller, 19, "RTCTime",
                             GetRTCTimePropertyRequest,
                             SetRTCTimePropertyRequest)
    PROPERTY_ENTRY_STRING_RO(Controller, 20, "RTCTimeString",
                             GetRTCTimeStringPropertyRequest)
    PROPERTY_ENTRY_STRING_RO(Controller, 21, "MCUFamily",
                             GetMCUFamilyPropertyRequest)
    PROPERTY_ENTRY_STRING_RO(Controller, 22, "MCULine",
                             GetMCULinePropertyRequest)
    PROPERTY_ENTRY_STRING_RO(Controller, 23, "MCUVariant",
                             GetMCUVariantPropertyRequest)
    PROPERTY_TABLE_END()

    Springboard::Utilities::Dictionary<ResourceIdentifier, Resource*>
        mResourceDictionary;
};

}  // namespace Infrastructure
}  // namespace Springboard
