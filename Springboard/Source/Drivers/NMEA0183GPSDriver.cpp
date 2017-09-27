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

#include <Springboard/Drivers/NMEA0183GPSDriver.hpp>
#include <Springboard/ExternalHAL/NMEA0183GPSDevice.hpp>

using Springboard::ExternalHAL::NMEA0183GPSDevice;

namespace Springboard {
namespace Drivers {

NMEA0183GPSDriver::NMEA0183GPSDriver(
    Springboard::Infrastructure::Controller* controller,
    const ResourceIdentifier identifier, const char* name,
    NMEA0183GPSDevice* driver)
    : Resource(controller, identifier, ResourceType::GPSReceiver, name),
      mDriver(driver)
{
}

ResultCode NMEA0183GPSDriver::ReadLastFixTimeUTC(uint32_t* time)
{
    return mDriver->GetLastFixTimeUTC(time);
}

ResultCode NMEA0183GPSDriver::ReadLastFixLatitude(float* latitude)
{
    return mDriver->GetLastFixLatitude(latitude);
}

ResultCode NMEA0183GPSDriver::ReadLastFixLongitude(float* longitude)
{
    return mDriver->GetLastFixLongitude(longitude);
}

ResultCode NMEA0183GPSDriver::ReadLastFixQuality(uint32_t* quality)
{
    return mDriver->GetLastFixQuality(quality);
}

ResultCode NMEA0183GPSDriver::ReadLastFixSatellitesTracked(uint32_t* satellites)
{
    return mDriver->GetLastFixSatellitesTracked(satellites);
}

ResultCode NMEA0183GPSDriver::ReadLastFixHorizontalDilution(float* dilution)
{
    return mDriver->GetLastFixHorizontalDilution(dilution);
}

ResultCode NMEA0183GPSDriver::ReadLastFixAltitude(float* altitude)
{
    return mDriver->GetLastFixAltitude(altitude);
}

ResultCode NMEA0183GPSDriver::ReadLastFixHeightOfGeoid(float* height)
{
    return mDriver->GetLastFixHeightOfGeoid(height);
}

}  // namespace Drivers
}  // namespace Springboard
