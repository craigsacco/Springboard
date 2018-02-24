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

//#include <hal.h>
//#include <chprintf.h>
//#include <ctime>
//#include <Springboard/InternalHAL/RealTimeClock.hpp>

//namespace Springboard {
//namespace InternalHAL {

//RealTimeClock::RealTimeClock(Driver* driver)
//    : mDriver(driver)
//{
//}

//ResultCode RealTimeClock::SetTime(uint64_t milliseconds)
//{
//    time_t seconds = static_cast<time_t>(milliseconds / 1000ULL);
//    tm time;
//    localtime_r(&seconds, &time);
//    if (time.tm_year < 80) {
//        return RC_RTC_YEAR_BEFORE_1980;
//    }

//    RTCDateTime dt;
//    uint32_t ms = static_cast<uint32_t>(milliseconds % 1000ULL);
//    rtcConvertStructTmToDateTime(&time, ms, &dt);
//    rtcSetTime(mDriver, &dt);

//    return RC_OK;
//}

//ResultCode RealTimeClock::GetTime(uint64_t* milliseconds)
//{
//    RTCDateTime dt;
//    rtcGetTime(mDriver, &dt);

//    tm time;
//    uint32_t ms = 0;
//    rtcConvertDateTimeToStructTm(&dt, &time, &ms);

//    time_t seconds = mktime(&time);
//    *milliseconds = (static_cast<uint64_t>(seconds) * 1000ULL) + ms;

//    return RC_OK;
//}

//ResultCode RealTimeClock::GetTimeAsString(
//    Springboard::Utilities::CharArray value)
//{
//    RTCDateTime dt;
//    rtcGetTime(mDriver, &dt);

//    uint32_t milliseconds = dt.millisecond;
//    uint32_t hours = milliseconds / (60UL * 60UL * 1000UL);
//    milliseconds -= (hours * (60UL * 60UL * 1000UL));
//    uint32_t minutes = milliseconds / (60UL * 1000UL);
//    milliseconds -= (minutes * (60UL * 1000UL));
//    uint32_t seconds = milliseconds / 1000UL;
//    milliseconds -= (seconds * 1000UL);
//    chsnprintf(value.GetData(), value.GetSize() - 1,
//               "%04u-%02u-%02u %02u:%02u:%02u.%03u",
//               dt.year + RTC_BASE_YEAR, dt.month, dt.day, hours, minutes,
//               seconds, milliseconds);

//    return RC_OK;
//}

//}  // namespace InternalHAL
//}  // namespace Springboard
