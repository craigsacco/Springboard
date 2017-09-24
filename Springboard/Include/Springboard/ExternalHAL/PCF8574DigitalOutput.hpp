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

#include <Springboard/CommonHAL/IDigitalOutput.hpp>
#include <Springboard/ExternalHAL/PCF8574GPIOPin.hpp>

namespace Springboard {
namespace ExternalHAL {

class PCF8574DigitalOutput : public PCF8574GPIOPin,
                             public Springboard::CommonHAL::IDigitalOutput
{
public:
    PCF8574DigitalOutput(PCF8574* driver, const uint8_t pin)
        : PCF8574GPIOPin(driver, pin)
    {
    }

    inline bool Get() const final
    {
        uint8_t value;
        mDriver->ReadPort(&value);
        return (value & (1UL << mPin));
    }

    inline void Set(bool state = true) final
    {
        uint8_t value;
        mDriver->ReadPort(&value);
        mDriver->WritePort(value | (1UL << mPin));
    }

    inline void Clear() final
    {
        uint8_t value;
        mDriver->ReadPort(&value);
        mDriver->WritePort(value & (uint8_t)(~(1UL << mPin)));
    }

    inline void Toggle() final
    {
        uint8_t value;
        mDriver->ReadPort(&value);
        mDriver->WritePort(value ^ (1UL << mPin));
    }
};

}  // namespace ExternalHAL
}  // namespace Springboard
