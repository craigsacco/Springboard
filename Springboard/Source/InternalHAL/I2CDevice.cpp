///******************************************************************************
// * MIT License
// *
// * PROJECT SPRINGBOARD
// * -------------------
// * Copyright (c) 2017 <craig.sacco@gmail.com>
// *
// * Permission is hereby granted, free of charge, to any person obtaining a
// * copy of this software and associated documentation files (the "Software"),
// * to deal in the Software without restriction, including without limitation
// * the rights to use, copy, modify, merge, publish, distribute, sublicense,
// * and/or sell copies of the Software, and to permit persons to whom the
// * Software is furnished to do so, subject to the following conditions:
// *
// * The above copyright notice and this permission notice shall be included in
// * all copies or substantial portions of the Software.
// *
// * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// * IN THE SOFTWARE.
// *****************************************************************************/

//#include <Springboard/InternalHAL/I2CDevice.hpp>
//#include <Springboard/InternalHAL/I2CBus.hpp>

//#if SPRINGBOARD_HAL_ENABLE_I2C

//using Springboard::Utilities::ByteArray;
//using Springboard::Utilities::ConstByteArray;

//namespace Springboard {
//namespace InternalHAL {

//I2CDevice::I2CDevice(I2CBus* bus, const I2CBus::Address address,
//                     const I2CBus::Speed requestedSpeed,
//                     const I2CBus::Speed maximumSpeed)
//    : mBus(bus), mAddress(address), mRequestedSpeed(requestedSpeed),
//      mMaximumSpeed(maximumSpeed), mCompletion(true)
//{
//    ASSERT(bus != nullptr);
//    ASSERT(requestedSpeed > 0 && requestedSpeed <= GetMaximumSpeed());
//}

//ResultCode I2CDevice::PerformTransaction(I2CBus::Address address,
//                                         ConstByteArray txbuf,
//                                         ByteArray rxbuf, systime_t timeout)
//{
//    I2CBus::Transaction transaction {
//        .address = address, .speed = mRequestedSpeed, .txbuf = txbuf,
//        .rxbuf = rxbuf, .timeout = timeout, .result = RC_OK,
//        .completion = &mCompletion
//    };
//    mBus->Enqueue(transaction);
//    mCompletion.Wait();

//    return transaction.result;
//}

//}  // namespace InternalHAL
//}  // namespace Springboard

//#endif  // SPRINGBOARD_HAL_ENABLE_I2C
