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

#include <Springboard/ExternalHAL/NMEA0183Device.hpp>
#include <Springboard/Kernel/Mutex.hpp>
#include <Springboard/Utilities/StringSplitter.hpp>

#if SPRINGBOARD_HAL_ENABLE_UART

using Springboard::Utilities::StringSplitter;

namespace Springboard {
namespace ExternalHAL {

class NMEA0183GPSDevice : public NMEA0183Device
{
public:
    NMEA0183GPSDevice(Springboard::InternalHAL::UARTBus* bus,
                      const char* name, Priority priority);

    ResultCode GetLastFixTimeUTC(uint32_t* time);
    ResultCode GetLastFixLatitude(float* latitude);
    ResultCode GetLastFixLongitude(float* longitude);
    ResultCode GetLastFixQuality(uint32_t* quality);
    ResultCode GetLastFixSatellitesTracked(uint32_t* satellites);
    ResultCode GetLastFixHorizontalDilution(float* dilution);
    ResultCode GetLastFixAltitude(float* altitude);
    ResultCode GetLastFixHeightOfGeoid(float* height);

private:
    void ReceivedMessage(ConstCharArray message) final;
    void ReceivedGPSFixInformation(StringSplitter splitter);

    Springboard::Kernel::Mutex mMutex;

    bool mLastFixReceived;
    uint32_t mLastFixTimeUTC;
    float mLastFixLatitude;
    float mLastFixLongitude;
    uint32_t mLastFixQuality;
    uint32_t mLastFixSatellitesTracked;
    float mLastFixHorizontalDilution;
    float mLastFixAltitude;
    float mLastFixHeightOfGeoid;
};

}  // namespace ExternalHAL
}  // namespace Springboard

#endif  // SPRINGBOARD_HAL_ENABLE_UART
