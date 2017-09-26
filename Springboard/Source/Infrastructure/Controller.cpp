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

#include <Springboard/Infrastructure/Controller.hpp>
#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/Kernel/Kernel.hpp>

namespace Springboard {
namespace Infrastructure {

Controller::Controller(const ResourceIdentifier identifier, const char* name) :
    Resource(nullptr, identifier, ResourceType::Controller, name),
    mPeripheralFactory(), mResourceDictionary()
{
    AddResource(this);
}

void Controller::Start()
{
    mPeripheralFactory.Start();
}

void Controller::AddResource(Resource* resource)
{
    mResourceDictionary.Add(resource->GetIdentifier(), resource);
}

Resource* Controller::FindResource(ResourceIdentifier identifier)
{
    Resource* resource = nullptr;
    if (mResourceDictionary.Find(identifier, &resource)) {
        return resource;
    } else {
        return nullptr;
    }
}

}  // namespace Infrastructure
}  // namespace Springboard
