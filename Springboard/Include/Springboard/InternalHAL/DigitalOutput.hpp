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
#include <Springboard/InternalHAL/InternalGPIOPin.hpp>

namespace Springboard {
namespace InternalHAL {

class DigitalOutput : public InternalGPIOPin,
                      public Springboard::CommonHAL::IDigitalOutput
{
public:
    DigitalOutput(const Pad pad,
                  const GPIOPullConfiguration pullConfiguration,
                  const GPIOOutputConfiguration outputConfiguration,
                  const GPIOOutputSpeed outputSpeed) :
        DigitalOutput(pad.port, pad.pin, pullConfiguration, outputConfiguration,
                      outputSpeed)
    {
    }

    DigitalOutput(const Port port, const uint8_t pin,
                  const GPIOPullConfiguration pullConfiguration,
                  const GPIOOutputConfiguration outputConfiguration,
                  const GPIOOutputSpeed outputSpeed) :
        InternalGPIOPin(port, pin, pullConfiguration),
        mOutputConfiguration(outputConfiguration),
        mOutputSpeed(outputSpeed)
    {
        SetPinConfiguration(mPort, mPin, GPIOPinMode::Output,
                            mPullConfiguration, mOutputConfiguration,
                            mOutputSpeed);
    }

    inline bool Get() const final
    {
        return palReadLatch(mPort) & (1UL << mPin);
    }

    inline void Set(bool state = true) final
    {
        palWritePad(mPort, mPin, state);
    }

    inline void Clear() final
    {
        palClearPad(mPort, mPin);
    }

    inline void Toggle() final
    {
        palTogglePad(mPort, mPin);
    }

private:
    const GPIOOutputConfiguration mOutputConfiguration;
    const GPIOOutputSpeed mOutputSpeed;
};

}  // namespace InternalHAL
}  // namespace Springboard
