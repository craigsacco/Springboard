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

#include <stm32f4xx_gpio.h>
#include <Springboard/InternalHAL/DigitalOutput.hpp>

namespace Springboard {
namespace InternalHAL {

DigitalOutput::DigitalOutput()
{
}

ResultCode DigitalOutput::ConfigureInternal(DigitalOutputConfiguration* config)
{
    GPIO_InitTypeDef init;
    init.GPIO_Pin = (1UL << config->pad);
    init.GPIO_Mode = GPIO_Mode_OUT;
    init.GPIO_OType = static_cast<GPIOOType_TypeDef>(config->outputType);
    init.GPIO_Speed = static_cast<GPIOSpeed_TypeDef>(config->outputSpeed);
    init.GPIO_PuPd = static_cast<GPIOPuPd_TypeDef>(config->pullType);
    GPIO_Init(config->port->regs, &init);

    return RC_OK;
}

bool DigitalOutput::Get() const
{
    return mConfig->port->regs->ODR & (1UL << mConfig->pad);
}

void DigitalOutput::Set()
{
    mConfig->port->regs->BSRRL = (1UL << mConfig->pad);
}

void DigitalOutput::Set(bool state)
{
    mConfig->port->regs->ODR =
        (mConfig->port->regs->ODR & ~(1UL << mConfig->pad)) |
        ((state ? 1UL : 0UL) << mConfig->pad);
}

void DigitalOutput::Clear()
{
    mConfig->port->regs->BSRRH = (1UL << mConfig->pad);
}

void DigitalOutput::Toggle()
{
    mConfig->port->regs->ODR ^= (1UL << mConfig->pad);
}

}  // namespace InternalHAL
}  // namespace Springboard
