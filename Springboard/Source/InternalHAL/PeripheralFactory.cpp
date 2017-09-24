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

#include <Springboard/InternalHAL/PeripheralFactory.hpp>

namespace Springboard {
namespace InternalHAL {

PeripheralFactory::PeripheralFactory()
{
}

void PeripheralFactory::Start()
{
#if SPRINGBOARD_HAL_ENABLE_I2C
    for (I2CBus* bus : mI2CBuses) {
        if (bus != nullptr) {
            bus->Start();
        }
    }
#endif

#if SPRINGBOARD_HAL_ENABLE_UART
    for (UARTBus* bus : mUARTBuses) {
        if (bus != nullptr) {
            bus->Start();
        }
    }
#endif
}

I2CBus* PeripheralFactory::GetI2CBus(size_t index)
{
#if SPRINGBOARD_HAL_ENABLE_I2C
    ASSERT(index > 0 && index <= SPRINGBOARD_HAL_I2C_COUNT);
    return mI2CBuses[index-1];
#else
    return nullptr;
#endif
}

UARTBus* PeripheralFactory::GetUARTBus(size_t index)
{
#if SPRINGBOARD_HAL_ENABLE_UART
    ASSERT(index > 0 && index <= SPRINGBOARD_HAL_UART_COUNT);
    return mUARTBuses[index-1];
#else
    return nullptr;
#endif
}

}  // namespace InternalHAL
}  // namespace Springboard
