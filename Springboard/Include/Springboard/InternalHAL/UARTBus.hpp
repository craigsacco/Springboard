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

#include <Springboard/Common.h>
#include <Springboard/InternalHAL/AlternateFunctionPin.hpp>
#include <Springboard/Comms/IStream.hpp>
#include <Springboard/Configuration/Configurable.hpp>
#include <stm32f4xx_usart.h>

namespace Springboard {
namespace InternalHAL {

struct UARTBusConfiguration : public Springboard::Configuration::IConfiguration
{
    enum class DataBitsType : uint16_t
    {
        Eight = USART_WordLength_8b,
        Nine = USART_WordLength_9b,
    };

    enum class ParityType : uint16_t
    {
        None = USART_Parity_No,
        Even = USART_Parity_Even,
        Odd = USART_Parity_Odd,
    };

    enum class StopBitsType : uint16_t
    {
        ZeroPointFive = USART_StopBits_0_5,
        One = USART_StopBits_1,
        OnePointFive = USART_StopBits_1_5,
        Two = USART_StopBits_2,
    };

    enum class FlowControlType : uint16_t
    {
        None = USART_HardwareFlowControl_None,
        RTSOnly = USART_HardwareFlowControl_RTS,
        CTSOnly = USART_HardwareFlowControl_CTS,
        Full = USART_HardwareFlowControl_RTS_CTS,
    };

    USART_TypeDef* regs;
    AlternateFunctionPinConfiguration* txPin;
    AlternateFunctionPinConfiguration* rxPin;
    uint32_t speed;
    DataBitsType dataBits;
    ParityType parity;
    StopBitsType stopBits;
    FlowControlType flowControl;
};

class UARTBus : public Springboard::Configuration::Configurable<UARTBusConfiguration>,
                public Springboard::Comms::IStream
{
public:
    explicit UARTBus();
    ResultCode ConfigureInternal(UARTBusConfiguration* config) override final;

    uint8_t Read() override final;
    void Read(Springboard::Utilities::ByteArray buffer) override final;
    size_t ReadAsync(Springboard::Utilities::ByteArray buffer) override final;
    void Write(uint8_t b) override final;
    void Write(Springboard::Utilities::ConstByteArray buffer) override final;
    size_t ReadAsync(Springboard::Utilities::ConstByteArray buffer) override final;

    static constexpr size_t NUMBER_OF_UARTS = 6;
};

}  // namespace InternalHAL
}  // namespace Springboard
