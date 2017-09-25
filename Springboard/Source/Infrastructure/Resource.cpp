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

#include <Springboard/Infrastructure/Resource.hpp>
#include <Springboard/Infrastructure/IResourceOwner.hpp>

namespace Springboard {
namespace Infrastructure {

Resource::Resource(IResourceOwner* owner,
                   const ResourceIdentifier identifier,
                   const ResourceType type,
                   const char* name) :
    mIdentifier(identifier), mResourceType(type), mName(name)
{
    if (owner != nullptr) {
        owner->AddResource(this);
    }
}

ResultCode Resource::GetProperty(PropertyIdentifier identifier,
                                 void* data, size_t* len)
{
    return PROPERTY_GET_HANDLER_IMPL(Resource);
}

ResultCode Resource::SetProperty(PropertyIdentifier identifier,
                                 const void* data, size_t len)
{
    return PROPERTY_SET_HANDLER_IMPL(Resource);
}

}  // namespace Infrastructure
}  // namespace Springboard
