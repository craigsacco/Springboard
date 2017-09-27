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

#include <Springboard/Infrastructure/Resource.hpp>

namespace Springboard {

namespace ExternalHAL { class NMEA0183GPSDevice; }

namespace Drivers {

class NMEA0183GPSDriver : public Springboard::Infrastructure::Resource
{
public:
    NMEA0183GPSDriver(Springboard::Infrastructure::Controller* controller,
                      const ResourceIdentifier identifier,
                      const char* name,
                      Springboard::ExternalHAL::NMEA0183GPSDevice* driver);

    ResultCode ReadLastFixTimeUTC(uint32_t* time);
    ResultCode ReadLastFixLatitude(float* latitude);
    ResultCode ReadLastFixLongitude(float* longitude);
    ResultCode ReadLastFixQuality(uint32_t* quality);
    ResultCode ReadLastFixSatellitesTracked(uint32_t* satellites);
    ResultCode ReadLastFixHorizontalDilution(float* dilution);
    ResultCode ReadLastFixAltitude(float* altitude);
    ResultCode ReadLastFixHeightOfGeoid(float* height);

    PROPERTY_GET_HANDLER(NMEA0183GPSDriver,
                         Springboard::Infrastructure::Resource)
    PROPERTY_SET_HANDLER(NMEA0183GPSDriver,
                         Springboard::Infrastructure::Resource)

private:
    Springboard::ExternalHAL::NMEA0183GPSDevice* mDriver;

    PROPERTY_TABLE_START(NMEA0183GPSDriver, 8)
    PROPERTY_ENTRY_UINT32_RO(NMEA0183GPSDriver, 100, "LastFixTimeUTC",
                             ReadLastFixTimeUTC)
    PROPERTY_ENTRY_FLOAT_RO(NMEA0183GPSDriver, 101, "LastFixLatitude",
                            ReadLastFixLatitude)
    PROPERTY_ENTRY_FLOAT_RO(NMEA0183GPSDriver, 102, "LastFixLongitude",
                            ReadLastFixLongitude)
    PROPERTY_ENTRY_UINT32_RO(NMEA0183GPSDriver, 103, "LastFixQuality",
                             ReadLastFixQuality)
    PROPERTY_ENTRY_UINT32_RO(NMEA0183GPSDriver, 104, "LastFixSatellitesTracked",
                             ReadLastFixSatellitesTracked)
    PROPERTY_ENTRY_FLOAT_RO(NMEA0183GPSDriver, 105, "LastFixHorizontalDilution",
                            ReadLastFixHorizontalDilution)
    PROPERTY_ENTRY_FLOAT_RO(NMEA0183GPSDriver, 106, "LastFixAltitude",
                            ReadLastFixAltitude)
    PROPERTY_ENTRY_FLOAT_RO(NMEA0183GPSDriver, 107, "LastFixHeightOfGeoid",
                            ReadLastFixHeightOfGeoid)
    PROPERTY_TABLE_END()
};

}  // namespace Drivers
}  // namespace Springboard
