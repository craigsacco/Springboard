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

#include <Springboard/InternalHAL/GPIOPort.hpp>
#include <Springboard/Configuration/IConfiguration.hpp>
#include <stm32f4xx_gpio.h>

namespace Springboard {
namespace InternalHAL {

struct GPIOPortPinConfiguration : public Springboard::Configuration::IConfiguration
{
    enum class PullType : uint8_t
    {
        None = GPIO_PuPd_NOPULL,
        PullUp = GPIO_PuPd_UP,
        PullDown = GPIO_PuPd_DOWN,
    };

    GPIOPortConfiguration* port;
    uint8_t pad;
    PullType pullType = PullType::None;
};

struct DigitalInputConfiguration : public GPIOPortPinConfiguration
{
};

struct DigitalOutputConfiguration : public GPIOPortPinConfiguration
{
    enum class OutputType : uint8_t {
        PushPull = GPIO_OType_PP,
        OpenDrain = GPIO_OType_OD,
    };

    enum class OutputSpeedType : uint8_t {
        LowSpeed = GPIO_Low_Speed,
        MediumSpeed = GPIO_Medium_Speed,
        FastSpeed = GPIO_Fast_Speed,
        HighSpeed = GPIO_High_Speed,
    };

    OutputType outputType = OutputType::PushPull;
    OutputSpeedType outputSpeed = OutputSpeedType::LowSpeed;
};

struct AlternateFunctionPinConfiguration : public DigitalOutputConfiguration
{
    uint8_t alternateFunction;
};

}  // namespace InternalHAL
}  // namespace Springboard
