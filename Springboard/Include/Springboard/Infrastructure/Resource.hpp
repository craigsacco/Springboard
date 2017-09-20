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

namespace Springboard {
namespace Infrastructure {

class Resource
{
public:
    typedef uint16_t ResourceIdentifier;
    typedef uint16_t PropertyIdentifier;

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

    template <typename T>
    struct PropertyEntry
    {
        PropertyEntry() = delete;

        union PropertyCallee
        {
            ~PropertyCallee()
            {
            }

            std::function<bool(const T&)> bool_fn;
            std::function<uint8_t(const T&)> uint8_fn;
            std::function<uint16_t(const T&)> uint16_fn;
            std::function<uint32_t(const T&)> uint32_fn;
            std::function<uint64_t(const T&)> uint64_fn;
            std::function<int8_t(const T&)> int8_fn;
            std::function<int16_t(const T&)> int16_fn;
            std::function<int32_t(const T&)> int32_fn;
            std::function<int64_t(const T&)> int64_fn;
            std::function<float(const T&)> float_fn;
            std::function<double(const T&)> double_fn;
            std::function<const char*(const T&)> string_fn;
            std::function<const uint8_t*(const T&)> bytearray_fn;
        };

        PropertyIdentifier identifier;
        const char* name;
        PropertyType type;
        uint8_t length;
        PropertyCallee callee;
    };

#define PROPERTY_TABLE_DECL(owner)                                      \
    static const PropertyEntry<owner> sPropertyTable[]
#define PROPERTY_TABLE_START(owner)                                     \
    const owner::PropertyEntry<owner> owner::sPropertyTable[] = {
#define PROPERTY_ENTRY_BASE(id, name, type, length, callee)             \
    { id, #name, type, length, { callee } },
#define PROPERTY_ENTRY_BOOL(owner, id, name, callee)                    \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Bool, 0,                \
        .bool_fn = &owner::callee)
#define PROPERTY_ENTRY_UINT8(owner, id, name, callee)                   \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::UInt8, 0,               \
        .uint8_fn = &owner::callee)
#define PROPERTY_ENTRY_UINT16(owner, id, name, callee)                  \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::UInt16, 0,              \
        .uint16_fn = &owner::callee)
#define PROPERTY_ENTRY_UINT32(owner, id, name, callee)                  \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::UInt32, 0,              \
        .uint32_fn = &owner::callee)
#define PROPERTY_ENTRY_UINT64(owner, id, name, callee)                  \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::UInt64, 0,              \
        .uint64_fn = &owner::callee)
#define PROPERTY_ENTRY_INT8(owner, id, name, callee)                    \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Int8, 0,                \
        .int8_fn = &owner::callee)
#define PROPERTY_ENTRY_INT16(owner, id, name, callee)                   \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Int16, 0,               \
        .int16_fn = &owner::callee)
#define PROPERTY_ENTRY_INT32(owner, id, name, callee)                   \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Int32, 0,               \
        .int32_fn = &owner::callee)
#define PROPERTY_ENTRY_INT64(owner, id, name, callee)                   \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Int64, 0,               \
        .int64_fn = &owner::callee)
#define PROPERTY_ENTRY_FLOAT(owner, id, name, callee)                   \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Float, 0,               \
        .float_fn = &owner::callee)
#define PROPERTY_ENTRY_DOUBLE(owner, id, name, callee)                  \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::Double, 0,              \
        .double_fn = &owner::callee)
#define PROPERTY_ENTRY_STRING(owner, id, name, callee)                  \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::String, 0,              \
        .string_fn = &owner::callee)
#define PROPERTY_ENTRY_BYTEARRAY(owner, id, name, length, callee)       \
    PROPERTY_ENTRY_BASE(id, name, PropertyType::ByteArray, length,      \
        .bytearray_fn = &owner::callee)
#define PROPERTY_TABLE_END()                                            \
    };

    explicit Resource(const ResourceIdentifier identifier);

    inline ResourceIdentifier GetID() const
    {
        return mIdentifier;
    }

protected:
    ResourceIdentifier mIdentifier;
};

}  // namespace Infrastructure
}  // namespace Springboard
