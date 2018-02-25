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

#include <Springboard/InternalHAL/UARTBus.hpp>
#include <Springboard/Utilities/StaticLookup.hpp>
#include <stm32f4xx_rcc.h>

namespace Springboard {
namespace InternalHAL {

UARTBus::UARTBus()
{
}

#pragma pack(1)
struct UARTPeripheralInfo
{
    USART_TypeDef* regs;
    uint8_t index;
    uint8_t apb;
    uint32_t rccbit;
};
#pragma pack

const UARTPeripheralInfo gUARTPeripherals[UARTBus::NUMBER_OF_UARTS] {
    { USART1, 0, 2, RCC_APB2Periph_USART1 },
    { USART2, 1, 1, RCC_APB1Periph_USART2 },
    { USART3, 2, 1, RCC_APB1Periph_USART3 },
    { UART4, 3, 1, RCC_APB1Periph_UART4 },
    { UART5, 4, 1, RCC_APB1Periph_UART5 },
    { USART6, 5, 2, RCC_APB2Periph_USART6 },
};

UARTBus* UARTBusInstances[UARTBus::NUMBER_OF_UARTS] { nullptr, nullptr, nullptr,
                                                      nullptr, nullptr, nullptr };

ResultCode UARTBus::ConfigureInternal(UARTBusConfiguration* config)
{
    ResultCode result = RC_CONFIGURATION_FAILED;
    for (const UARTPeripheralInfo& info : gUARTPeripherals) {
        if (config->regs == info.regs) {
            if (info.apb == 1) {
                RCC_APB1PeriphClockCmd(info.rccbit, ENABLE);
            } else {
                RCC_APB2PeriphClockCmd(info.rccbit, ENABLE);
            }
            UARTBusInstances[info.index] = this;
            result = RC_OK;
            break;
        }
    }
    if (result != RC_OK) {
        return result;
    }

    USART_InitTypeDef init;
    init.USART_BaudRate = config->speed;
    init.USART_WordLength = static_cast<uint16_t>(config->dataBits);
    init.USART_StopBits = static_cast<uint16_t>(config->stopBits);
    init.USART_Parity = static_cast<uint16_t>(config->parity);
    init.USART_HardwareFlowControl = static_cast<uint16_t>(config->flowControl);
    init.USART_Mode = (config->rxPin != nullptr ? USART_Mode_Rx : 0) |
                      (config->txPin != nullptr ? USART_Mode_Tx : 0);
    USART_Init(config->regs, &init);
}

uint8_t UARTBus::Read()
{
    return 0;
}

void UARTBus::Read(Springboard::Utilities::ByteArray buffer)
{

}

size_t UARTBus::ReadAsync(Springboard::Utilities::ByteArray buffer)
{
    return 0;
}

void UARTBus::Write(uint8_t b)
{

}

void UARTBus::Write(Springboard::Utilities::ConstByteArray buffer)
{

}

size_t UARTBus::ReadAsync(Springboard::Utilities::ConstByteArray buffer)
{
    return 0;
}

}  // namespace InternalHAL
}  // namespace Springboard
