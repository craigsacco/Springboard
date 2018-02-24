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

#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/InternalHAL/GPIOPort.hpp>
#include <Springboard/CommonHAL/IDigitalOutput.hpp>
#include <Springboard/Configuration/IConfigurable.hpp>

namespace Springboard {
namespace InternalHAL {

struct DigitalOutputConfiguration : public Springboard::Configuration::IConfiguration
{
public:
    GPIOPortConfiguration* port;
    uint8_t pad;
};

class DigitalOutput : public Springboard::CommonHAL::IDigitalOutput,
                      public Springboard::Configuration::IConfigurable<DigitalOutputConfiguration>
{
public:
    DigitalOutput();
    ResultCode ConfigureInternal(DigitalOutputConfiguration* config) override final;
    bool Get() const override final;
    void Set() override final;
    void Set(bool state) override final;
    void Clear() override final;
    void Toggle() override final;
};

}  // namespace InternalHAL
}  // namespace Springboard
