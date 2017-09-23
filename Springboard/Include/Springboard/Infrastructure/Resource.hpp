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

#include <Springboard/Common.h>
#include <functional>
#include <cstring>

namespace Springboard {
namespace Infrastructure {

class Resource
{
public:
    typedef uint16_t ResourceIdentifier;
    typedef uint16_t PropertyIdentifier;
    template <class TClass, typename TProp> using GetterFPtr =
        ResultCode(TClass::*)(TProp*);
    template <class TClass> using BoolGetterFPtr =
        GetterFPtr<TClass, bool>;
    template <class TClass> using UInt8GetterFPtr =
        GetterFPtr<TClass, uint8_t>;
    template <class TClass> using UInt16GetterFPtr =
        GetterFPtr<TClass, uint16_t>;
    template <class TClass> using UInt32GetterFPtr =
        GetterFPtr<TClass, uint32_t>;
    template <class TClass> using UInt64GetterFPtr =
        GetterFPtr<TClass, uint64_t>;
    template <class TClass> using Int8GetterFPtr =
        GetterFPtr<TClass, int8_t>;
    template <class TClass> using Int16GetterFPtr =
        GetterFPtr<TClass, int16_t>;
    template <class TClass> using Int32GetterFPtr =
        GetterFPtr<TClass, int32_t>;
    template <class TClass> using Int64GetterFPtr =
        GetterFPtr<TClass, int64_t>;
    template <class TClass> using FloatGetterFPtr =
        GetterFPtr<TClass, float>;
    template <class TClass> using DoubleGetterFPtr =
        GetterFPtr<TClass, double>;
    template <class TClass> using StringGetterFPtr =
        GetterFPtr<TClass, char>;
    template <class TClass> using ByteArrayGetterFPtr =
        GetterFPtr<TClass, uint8_t>;
    template <class TClass, typename TProp> using SetterFPtr =
        ResultCode(TClass::*)(const TProp);
    template <class TClass> using BoolSetterFPtr =
        SetterFPtr<TClass, bool>;
    template <class TClass> using UInt8SetterFPtr =
        SetterFPtr<TClass, uint8_t>;
    template <class TClass> using UInt16SetterFPtr =
        SetterFPtr<TClass, uint16_t>;
    template <class TClass> using UInt32SetterFPtr =
        SetterFPtr<TClass, uint32_t>;
    template <class TClass> using UInt64SetterFPtr =
        SetterFPtr<TClass, uint64_t>;
    template <class TClass> using Int8SetterFPtr =
        SetterFPtr<TClass, int8_t>;
    template <class TClass> using Int16SetterFPtr =
        SetterFPtr<TClass, int16_t>;
    template <class TClass> using Int32SetterFPtr =
        SetterFPtr<TClass, int32_t>;
    template <class TClass> using Int64SetterFPtr =
        SetterFPtr<TClass, int64_t>;
    template <class TClass> using FloatSetterFPtr =
        SetterFPtr<TClass, float>;
    template <class TClass> using DoubleSetterFPtr =
        SetterFPtr<TClass, double>;
    template <class TClass> using StringSetterFPtr =
        SetterFPtr<TClass, const char*>;
    template <class TClass> using ByteArraySetterFPtr =
        SetterFPtr<TClass, const uint8_t*>;

    enum class PropertyType : uint8_t
    {
        Boolean,
        UInt8,
        UInt16,
        UInt32,
        UInt64,
        Int8,
        Int16,
        Int32,
        Int64,
        Float,
        Double,
        String,
        ByteArray,
    };

    const size_t PropertyTypeLengths[13] = {
        sizeof(bool),
        sizeof(uint8_t),
        sizeof(uint16_t),
        sizeof(uint32_t),
        sizeof(uint64_t),
        sizeof(int8_t),
        sizeof(int16_t),
        sizeof(int32_t),
        sizeof(int64_t),
        sizeof(float),
        sizeof(double),
        0,
        0,
    };

    template <class TClass>
    union GetPropertyCallee
    {
        BoolGetterFPtr<TClass> bool_fn;
        UInt8GetterFPtr<TClass> uint8_fn;
        UInt16GetterFPtr<TClass> uint16_fn;
        UInt32GetterFPtr<TClass> uint32_fn;
        UInt64GetterFPtr<TClass> uint64_fn;
        Int8GetterFPtr<TClass> int8_fn;
        Int16GetterFPtr<TClass> int16_fn;
        Int32GetterFPtr<TClass> int32_fn;
        Int64GetterFPtr<TClass> int64_fn;
        FloatGetterFPtr<TClass> float_fn;
        DoubleGetterFPtr<TClass> double_fn;
        StringGetterFPtr<TClass> string_fn;
        ByteArrayGetterFPtr<TClass> bytearray_fn;
    };

    template <class TClass>
    union SetPropertyCallee
    {
        BoolSetterFPtr<TClass> bool_fn;
        UInt8SetterFPtr<TClass> uint8_fn;
        UInt16SetterFPtr<TClass> uint16_fn;
        UInt32SetterFPtr<TClass> uint32_fn;
        UInt64SetterFPtr<TClass> uint64_fn;
        Int8SetterFPtr<TClass> int8_fn;
        Int16SetterFPtr<TClass> int16_fn;
        Int32SetterFPtr<TClass> int32_fn;
        Int64SetterFPtr<TClass> int64_fn;
        FloatSetterFPtr<TClass> float_fn;
        DoubleSetterFPtr<TClass> double_fn;
        StringSetterFPtr<TClass> string_fn;
        ByteArraySetterFPtr<TClass> bytearray_fn;
    };

    template <class TClass>
    struct PropertyEntry
    {
        const PropertyIdentifier identifier;
        const char* name;
        const PropertyType type;
        const uint8_t length;
        const GetPropertyCallee<TClass> getter;
        const SetPropertyCallee<TClass> setter;
    };

#define PROPERTY_TABLE_START(owner, count)                                  \
    const owner::PropertyEntry<owner> sPropertyTable[count] {
#define PROPERTY_ENTRY_BASE(id, name, type, length, getter, setter)         \
    { id, #name, type, length, { getter }, { setter } },
#define PROPERTY_ENTRY_BOOL_RO(owner, id, name, getter)                     \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Bool, sizeof(bool),         \
        .bool_fn = &owner::getter, .bool_fn = nullptr)
#define PROPERTY_ENTRY_UINT8_RO(owner, id, name, getter)                    \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::UInt8, sizeof(uint8_t),     \
        .uint8_fn = &owner::getter, .uint8_fn = nullptr)
#define PROPERTY_ENTRY_UINT16_RO(owner, id, name, getter)                   \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::UInt16, sizeof(uint16_t),   \
        .uint16_fn = &owner::getter, .uint16_fn = nullptr)
#define PROPERTY_ENTRY_UINT32_RO(owner, id, name, getter)                   \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::UInt32, sizeof(uint32_t),   \
        .uint32_fn = &owner::getter, .uint32_fn = nullptr)
#define PROPERTY_ENTRY_UINT64_RO(owner, id, name, getter)                   \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::UInt64, sizeof(uint64_t),   \
        .uint64_fn = &owner::getter, .uint64_fn = nullptr)
#define PROPERTY_ENTRY_INT8_RO(owner, id, name, getter)                     \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Int8, sizeof(int8_t),       \
        .int8_fn = &owner::getter, .int8_fn = nullptr)
#define PROPERTY_ENTRY_INT16_RO(owner, id, name, getter)                    \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Int16, sizeof(int16_t),     \
        .int16_fn = &owner::getter, .int16_fn = nullptr)
#define PROPERTY_ENTRY_INT32_RO(owner, id, name, getter)                    \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Int32, sizeof(int32_t),     \
        .int32_fn = &owner::getter, .int32_fn = nullptr)
#define PROPERTY_ENTRY_INT64_RO(owner, id, name, getter)                    \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Int64, sizeof(int64_t),     \
        .int64_fn = &owner::getter, .int64_fn = nullptr)
#define PROPERTY_ENTRY_FLOAT_RO(owner, id, name, getter)                    \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Float, sizeof(float),       \
        .float_fn = &owner::getter, .float_fn = nullptr)
#define PROPERTY_ENTRY_DOUBLE_RO(owner, id, name, getter)                   \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Double, sizeof(double),     \
        .double_fn = &owner::getter, .double_fn = nullptr)
#define PROPERTY_ENTRY_STRING_RO(owner, id, name, getter)                   \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::String, 0,                  \
        .string_fn = &owner::getter, .string_fn = nullptr)
#define PROPERTY_ENTRY_BYTEARRAY_RO(owner, id, name, length, getter)        \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::ByteArray, length,          \
        .bytearray_fn = &owner::getter, .bytearray_fn = nullptr)
#define PROPERTY_ENTRY_BOOL_RW(owner, id, name, getter, setter)             \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Bool, sizeof(bool),         \
        .bool_fn = &owner::getter, .bool_fn = &owner::setter)
#define PROPERTY_ENTRY_UINT8_RW(owner, id, name, getter, setter)            \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::UInt8, sizeof(uint8_t),     \
        .uint8_fn = &owner::getter, .uint8_fn = &owner::setter)
#define PROPERTY_ENTRY_UINT16_RW(owner, id, name, getter, setter)           \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::UInt16, sizeof(uint16_t),   \
        .uint16_fn = &owner::getter, .uint16_fn = &owner::setter)
#define PROPERTY_ENTRY_UINT32_RW(owner, id, name, getter, setter)           \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::UInt32, sizeof(uint32_t),   \
        .uint32_fn = &owner::getter, .uint32_fn = &owner::setter)
#define PROPERTY_ENTRY_UINT64_RW(owner, id, name, getter, setter)           \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::UInt64, sizeof(uint64_t),   \
        .uint64_fn = &owner::getter, .uint64_fn = &owner::setter)
#define PROPERTY_ENTRY_INT8_RW(owner, id, name, getter, setter)             \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Int8, sizeof(int8_t),       \
        .int8_fn = &owner::getter, .int8_fn = &owner::setter)
#define PROPERTY_ENTRY_INT16_RW(owner, id, name, getter, setter)            \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Int16, sizeof(int16_t),     \
        .int16_fn = &owner::getter, .int16_fn = &owner::setter)
#define PROPERTY_ENTRY_INT32_RW(owner, id, name, getter, setter)            \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Int32, sizeof(int32_t),     \
        .int32_fn = &owner::getter, .int32_fn = &owner::setter)
#define PROPERTY_ENTRY_INT64_RW(owner, id, name, getter, setter)            \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Int64, sizeof(int64_t),     \
        .int64_fn = &owner::getter, .int64_fn = &owner::setter)
#define PROPERTY_ENTRY_FLOAT_RW(owner, id, name, getter, setter)            \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Float, sizeof(float),       \
        .float_fn = &owner::getter, .float_fn = &owner::setter)
#define PROPERTY_ENTRY_DOUBLE_RW(owner, id, name, getter, setter)           \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Double, sizeof(double),     \
        .double_fn = &owner::getter, .double_fn = &owner::setter)
#define PROPERTY_ENTRY_STRING_RW(owner, id, name, getter, setter)           \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::String, 0,                  \
        .string_fn = &owner::getter, .string_fn = &owner::setter)
#define PROPERTY_ENTRY_BYTEARRAY_RW(owner, id, name, getter, setter,        \
                                    length)                                 \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::ByteArray, length,          \
        .bytearray_fn = &owner::getter, .bytearray_fn = &owner::setter)
#define PROPERTY_TABLE_END()                                                \
    };

    explicit Resource(const ResourceIdentifier identifier);

    inline ResourceIdentifier GetID() const
    {
        return mIdentifier;
    }

    virtual ResultCode GetProperty(PropertyIdentifier identifier,
                                   void* data, size_t* len) = 0;
    virtual ResultCode SetProperty(PropertyIdentifier identifier,
                                   const void* data, size_t len) = 0;

#define PROPERTY_GET_HANDLER_IMPL(owner)                                    \
    ResultCode result = GetPropertyInternal<owner>(                         \
        this, sPropertyTable,                                               \
        sizeof(sPropertyTable) / sizeof(PropertyEntry<owner>),              \
        identifier, data, len);
#define PROPERTY_SET_HANDLER_IMPL(owner)                                    \
    ResultCode result = SetPropertyInternal<owner>(                         \
        this, sPropertyTable,                                               \
        sizeof(sPropertyTable) / sizeof(PropertyEntry<owner>),              \
        identifier, data, len);
#define PROPERTY_GET_HANDLER(owner)                                         \
    ResultCode GetProperty(PropertyIdentifier identifier,                   \
                           void* data, size_t* len) final                   \
    {                                                                       \
        PROPERTY_GET_HANDLER_IMPL(owner)                                    \
        return result;                                                      \
    }
#define PROPERTY_SET_HANDLER(owner)                                         \
    ResultCode SetProperty(PropertyIdentifier identifier,                   \
                           const void* data, size_t len) final              \
    {                                                                       \
        PROPERTY_SET_HANDLER_IMPL(owner)                                    \
        return result;                                                      \
    }
#define PROPERTY_GET_HANDLER_EX(owner, base)                                \
    ResultCode GetProperty(PropertyIdentifier identifier,                   \
                           void* data, size_t* len) final                   \
    {                                                                       \
        PROPERTY_GET_HANDLER_IMPL(owner)                                    \
        if (result == RC_RESOURCE_INVALID_PROPERTY_ID) {                    \
            result = base::GetProperty(identifier, data, len);              \
        }                                                                   \
        return result;                                                      \
    }
#define PROPERTY_SET_HANDLER_EX(owner, base)                                \
    ResultCode SetProperty(PropertyIdentifier identifier,                   \
                           const void* data, size_t len) final              \
    {                                                                       \
        PROPERTY_SET_HANDLER_IMPL(owner)                                    \
        if (result == RC_RESOURCE_INVALID_PROPERTY_ID) {                    \
            result = base::SetProperty(identifier, data, len);              \
        }                                                                   \
        return result;                                                      \
    }

protected:
    template <class TClass>
    ResultCode GetPropertyInternal(TClass* owner,
                                   const PropertyEntry<TClass> entries[],
                                   size_t size,
                                   PropertyIdentifier identifier,
                                   void* data, size_t* len)
    {
        for (size_t i = 0; i < size; i++)
        {
            const PropertyEntry<TClass>& entry = entries[i];

            if (entry.identifier == identifier)
            {
                ResultCode result = RC_OK;
                switch (entry.type)
                {
                case PropertyType::Boolean:
                    result = (owner->*(entry.getter.bool_fn))
                        (static_cast<bool*>(data));
                    break;
                case PropertyType::UInt8:
                    result = (owner->*(entry.getter.uint8_fn))
                        (static_cast<uint8_t*>(data));
                    break;
                case PropertyType::UInt16:
                    result = (owner->*(entry.getter.uint16_fn))
                        (static_cast<uint16_t*>(data));
                    break;
                case PropertyType::UInt32:
                    result = (owner->*(entry.getter.uint32_fn))
                        (static_cast<uint32_t*>(data));
                    break;
                case PropertyType::UInt64:
                    result = (owner->*(entry.getter.uint64_fn))
                        (static_cast<uint64_t*>(data));
                    break;
                case PropertyType::Int8:
                    result = (owner->*(entry.getter.int8_fn))
                        (static_cast<int8_t*>(data));
                    break;
                case PropertyType::Int16:
                    result = (owner->*(entry.getter.int16_fn))
                        (static_cast<int16_t*>(data));
                    break;
                case PropertyType::Int32:
                    result = (owner->*(entry.getter.int32_fn))
                        (static_cast<int32_t*>(data));
                    break;
                case PropertyType::Int64:
                    result = (owner->*(entry.getter.int64_fn))
                        (static_cast<int64_t*>(data));
                    break;
                case PropertyType::Float:
                {
                    float f = 0.0f;
                    result = (owner->*(entry.getter.float_fn))(&f);
                    memcpy(data, &f, sizeof(float));
                    break;
                }
                case PropertyType::Double:
                {
                    double d = 0.0;
                    result = (owner->*(entry.getter.double_fn))(&d);
                    memcpy(data, &d, sizeof(double));
                    break;
                }
                case PropertyType::String:
                    result = (owner->*(entry.getter.string_fn))
                        (static_cast<char*>(data));
                    break;
                case PropertyType::ByteArray:
                    result = (owner->*(entry.getter.bytearray_fn))
                        (static_cast<uint8_t*>(data));
                    break;
                default:
                    return RC_RESOURCE_INVALID_TYPE;
                }

                if (result != RC_OK) {
                    return result;
                }

                if (entry.type == PropertyType::String) {
                    *len = strlen(static_cast<char*>(data));
                } else {
                    *len = entry.length;
                }

                return RC_OK;
            }
        }

        return RC_RESOURCE_INVALID_PROPERTY_ID;
    }

    template <class TClass>
    ResultCode SetPropertyInternal(TClass* owner,
                                   const PropertyEntry<TClass> entries[],
                                   size_t size,
                                   PropertyIdentifier identifier,
                                   const void* data, size_t len)
    {
        for (size_t i = 0; i < size; i++)
        {
            const PropertyEntry<TClass>& entry = entries[i];

            if (entry.identifier == identifier)
            {
                if (PropertyTypeLengths[static_cast<size_t>(entry.type)] > 0 &&
                    PropertyTypeLengths[static_cast<size_t>(entry.type)] != len)
                {
                    return RC_RESOURCE_INVALID_PROPERTY_LENGTH;
                }

                switch (entry.type)
                {
                case PropertyType::Boolean:
                    return (owner->*(entry.setter.bool_fn))
                        (*reinterpret_cast<const bool*>(data));
                case PropertyType::UInt8:
                    return (owner->*(entry.setter.uint8_fn))
                        (*reinterpret_cast<const uint8_t*>(data));
                case PropertyType::UInt16:
                    return (owner->*(entry.setter.uint16_fn))
                        (*reinterpret_cast<const uint16_t*>(data));
                case PropertyType::UInt32:
                    return (owner->*(entry.setter.uint32_fn))
                        (*reinterpret_cast<const uint32_t*>(data));
                case PropertyType::UInt64:
                    return (owner->*(entry.setter.uint64_fn))
                        (*reinterpret_cast<const uint64_t*>(data));
                case PropertyType::Int8:
                    return (owner->*(entry.setter.int8_fn))
                        (*reinterpret_cast<const int8_t*>(data));
                case PropertyType::Int16:
                    return (owner->*(entry.setter.int16_fn))
                        (*reinterpret_cast<const int16_t*>(data));
                case PropertyType::Int32:
                    return (owner->*(entry.setter.int32_fn))
                        (*reinterpret_cast<const int32_t*>(data));
                case PropertyType::Int64:
                    return (owner->*(entry.setter.int64_fn))
                        (*reinterpret_cast<const int64_t*>(data));
                case PropertyType::Float:
                {
                    float f = 0.0f;
                    memcpy(&f, data, sizeof(float));
                    return (owner->*(entry.setter.float_fn))(f);
                }
                case PropertyType::Double:
                {
                    double d = 0.0;
                    memcpy(&d, data, sizeof(float));
                    return (owner->*(entry.setter.double_fn))(d);
                }
                case PropertyType::String:
                    return (owner->*(entry.setter.string_fn))
                        (reinterpret_cast<const char*>(data));
                case PropertyType::ByteArray:
                    return (owner->*(entry.setter.bytearray_fn))
                        (reinterpret_cast<const uint8_t*>(data));
                default:
                    return RC_RESOURCE_INVALID_TYPE;
                }
            }
        }

        return RC_RESOURCE_INVALID_PROPERTY_ID;
    }

    ResourceIdentifier mIdentifier;
};

}  // namespace Infrastructure
}  // namespace Springboard