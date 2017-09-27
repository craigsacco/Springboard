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

#include <cstring>
#include <Springboard/ExternalHAL/NMEA0183GPSDevice.hpp>

using Springboard::Kernel::ScopedMutex;

namespace Springboard {
namespace ExternalHAL {

NMEA0183GPSDevice::NMEA0183GPSDevice(Springboard::InternalHAL::UARTBus* bus,
                                     const char* name, Priority priority) :
    NMEA0183Device(bus, name, priority),
    mMutex(), mLastFixReceived(false)
{
}

ResultCode NMEA0183GPSDevice::GetLastFixTimeUTC(uint32_t* time)
{
    ScopedMutex mutex(&mMutex);

    if (!mLastFixReceived) {
        return RC_NMEA0183_NO_FIX_ACQUIRED;
    }

    *time = mLastFixTimeUTC;
    return RC_OK;
}

ResultCode NMEA0183GPSDevice::GetLastFixLatitude(float* latitude)
{
    ScopedMutex mutex(&mMutex);

    if (!mLastFixReceived) {
        return RC_NMEA0183_NO_FIX_ACQUIRED;
    }

    *latitude = mLastFixLatitude;
    return RC_OK;
}

ResultCode NMEA0183GPSDevice::GetLastFixLongitude(float* longitude)
{
    ScopedMutex mutex(&mMutex);

    if (!mLastFixReceived) {
        return RC_NMEA0183_NO_FIX_ACQUIRED;
    }

    *longitude = mLastFixLongitude;
    return RC_OK;
}

ResultCode NMEA0183GPSDevice::GetLastFixQuality(uint32_t* quality)
{
    ScopedMutex mutex(&mMutex);

    if (!mLastFixReceived) {
        return RC_NMEA0183_NO_FIX_ACQUIRED;
    }

    *quality = mLastFixQuality;
    return RC_OK;
}

ResultCode NMEA0183GPSDevice::GetLastFixSatellitesTracked(uint32_t* satellites)
{
    ScopedMutex mutex(&mMutex);

    if (!mLastFixReceived) {
        return RC_NMEA0183_NO_FIX_ACQUIRED;
    }

    *satellites = mLastFixSatellitesTracked;
    return RC_OK;
}

ResultCode NMEA0183GPSDevice::GetLastFixHorizontalDilution(float* dilution)
{
    ScopedMutex mutex(&mMutex);

    if (!mLastFixReceived) {
        return RC_NMEA0183_NO_FIX_ACQUIRED;
    }

    *dilution = mLastFixHorizontalDilution;
    return RC_OK;
}

ResultCode NMEA0183GPSDevice::GetLastFixAltitude(float* altitude)
{
    ScopedMutex mutex(&mMutex);

    if (!mLastFixReceived) {
        return RC_NMEA0183_NO_FIX_ACQUIRED;
    }

    *altitude = mLastFixAltitude;
    return RC_OK;
}

ResultCode NMEA0183GPSDevice::GetLastFixHeightOfGeoid(float* height)
{
    ScopedMutex mutex(&mMutex);

    if (!mLastFixReceived) {
        return RC_NMEA0183_NO_FIX_ACQUIRED;
    }

    *height = mLastFixHeightOfGeoid;
    return RC_OK;
}

void NMEA0183GPSDevice::ReceivedMessage(ConstCharArray message)
{
    StringSplitter splitter(message, ',');
    ConstCharArray type = splitter.GetNext();

    if (strncmp(type.GetData(), "GPGGA", 5) == 0) {
        ReceivedGPSFixInformation(splitter.GetRemainder());
    }
}

void NMEA0183GPSDevice::ReceivedGPSFixInformation(StringSplitter splitter)
{
    ScopedMutex mutex(&mMutex);

    mLastFixReceived = true;
    uint32_t lastFixTimeUTC = splitter.GetNextAsUInt32();
    mLastFixTimeUTC = (lastFixTimeUTC % 100) +
                      (((lastFixTimeUTC / 100) % 100) * 60) +
                      ((lastFixTimeUTC / 10000) * 60 * 60);
    mLastFixLatitude = splitter.GetNextAsFloat() / 100.0f;
    if (splitter.GetNext().At(0) == 'S') {
        mLastFixLatitude = 0.0f - mLastFixLatitude;
    }
    mLastFixLongitude = splitter.GetNextAsFloat() / 100.0f;
    if (splitter.GetNext().At(0) == 'W') {
        mLastFixLongitude = 0.0f - mLastFixLongitude;
    }
    mLastFixQuality = splitter.GetNextAsUInt32();
    mLastFixSatellitesTracked = splitter.GetNextAsUInt32();
    mLastFixHorizontalDilution = splitter.GetNextAsFloat();
    mLastFixAltitude = splitter.GetNextAsFloat();
    splitter.SkipNext();  // altitude units
    mLastFixHeightOfGeoid = splitter.GetNextAsFloat();
    splitter.SkipNext();  // height of geoid units
}

}  // namespace ExternalHAL
}  // namespace Springboard
