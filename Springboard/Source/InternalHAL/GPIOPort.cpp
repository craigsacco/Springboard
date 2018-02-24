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
#include <Springboard/Utilities/StaticLookup.hpp>
#include <stm32f4xx_rcc.h>

namespace Springboard {
namespace InternalHAL {

GPIOPort::GPIOPort()
{
}

const Springboard::Utilities::StaticLookup<GPIO_TypeDef*, uint32_t, 9>
    GPIOToAHB1PeripheralEnable {
    {
        { GPIOA, RCC_AHB1Periph_GPIOA },
        { GPIOB, RCC_AHB1Periph_GPIOB },
        { GPIOC, RCC_AHB1Periph_GPIOC },
        { GPIOD, RCC_AHB1Periph_GPIOD },
        { GPIOE, RCC_AHB1Periph_GPIOE },
        { GPIOF, RCC_AHB1Periph_GPIOF },
        { GPIOG, RCC_AHB1Periph_GPIOG },
        { GPIOH, RCC_AHB1Periph_GPIOH },
        { GPIOI, RCC_AHB1Periph_GPIOI },
    }
};

ResultCode GPIOPort::ConfigureInternal(GPIOPortConfiguration* config)
{
    uint32_t peripheral;
    if (GPIOToAHB1PeripheralEnable.Find(config->regs, &peripheral)) {
        RCC_AHB1PeriphClockCmd(peripheral, ENABLE);
        return RC_OK;
    }

    return RC_CONFIGURATION_FAILED;
}

}  // namespace InternalHAL
}  // namespace Springboard
