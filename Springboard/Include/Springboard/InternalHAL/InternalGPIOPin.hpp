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

namespace Springboard {
namespace InternalHAL {

class InternalGPIOPin
{
public:
    typedef ioportid_t Port;

    struct Pad
    {
        const Port port;
        const uint8_t pin;
    };

    InternalGPIOPin(const Port port, const uint8_t pin,
                    const GPIOPullConfiguration pullConfiguration) :
        mPort(port), mPin(pin), mPullConfiguration(pullConfiguration)
    {
    }

    inline static void SetPinConfiguration(
        const Pad pad, const GPIOPinMode mode,
        const GPIOPullConfiguration pullConfiguration =
            GPIOPullConfiguration::Floating,
        const GPIOOutputConfiguration outputConfiguration =
            GPIOOutputConfiguration::PushPull,
        const GPIOOutputSpeed outputSpeed = GPIOOutputSpeed::Low_2MHz)
    {
        SetPinConfiguration(pad.port, pad.pin, mode, pullConfiguration,
                            outputConfiguration, outputSpeed);
    }

    inline static void SetPinConfiguration(
        const Port port, const uint8_t pin, const GPIOPinMode mode,
        const GPIOPullConfiguration pullConfiguration =
            GPIOPullConfiguration::Floating,
        const GPIOOutputConfiguration outputConfiguration =
            GPIOOutputConfiguration::PushPull,
        const GPIOOutputSpeed outputSpeed = GPIOOutputSpeed::Low_2MHz)
    {
        palSetPadMode(port, pin, static_cast<iomode_t>(mode) |
                                 static_cast<iomode_t>(pullConfiguration) |
                                 static_cast<iomode_t>(outputConfiguration) |
                                 static_cast<iomode_t>(outputSpeed));
    }

protected:
    const Port mPort;
    const uint8_t mPin;
    const GPIOPullConfiguration mPullConfiguration;
};

}  // namespace InternalHAL
}  // namespace Springboard
