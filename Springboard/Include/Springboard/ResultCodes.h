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

//! \section Success
#define RC_OK                               ((ResultCode)0)

//! \section Construction macros
#define RC_BASE_INFRASTRUCTURE              ((ResultCode)0x10000000)
#define RC_BASE_INFRASTRUCTURE_BLOCK(x)     (RC_BASE_INFRASTRUCTURE + (x << 16))
#define RC_BASE_DRIVERS                     ((ResultCode)0x20000000)
#define RC_BASE_DRIVERS_BLOCK(x)            (RC_BASE_INFRASTRUCTURE + (x << 16))
#define RC_BASE_HAL                         ((ResultCode)0x30000000)
#define RC_BASE_HAL_BLOCK(x)                (RC_BASE_HAL + (x << 16))
#define RC_BASE_EXTERNAL_HAL                ((ResultCode)0x40000000)
#define RC_BASE_EXTERNAL_HAL_BLOCK(x)       (RC_BASE_EXTERNAL_HAL + (x << 16))

//! \section Resource result codes
#define RC_RESOURCE_BASE                    (RC_BASE_INFRASTRUCTURE_BLOCK(0))
#define RC_RESOURCE_INVALID_TYPE            (RC_RESOURCE_BASE + 0)
#define RC_RESOURCE_INVALID_PROPERTY_ID     (RC_RESOURCE_BASE + 1)
#define RC_RESOURCE_PROPERTY_NOT_SETABLE    (RC_RESOURCE_BASE + 2)
#define RC_RESOURCE_INVALID_PROPERTY_LENGTH (RC_RESOURCE_BASE + 3)

//! \section Controller result codes
#define RC_CONTROLLER_BASE                  (RC_BASE_INFRASTRUCTURE_BLOCK(1))
#define RC_CONTROLLER_INVALID_RESOURCE_ID   (RC_CONTROLLER_BASE + 0)

//! \section I2C result codes
#define RC_I2C_BASE                         (RC_BASE_HAL_BLOCK(0))
#define RC_I2C_TIMED_OUT                    (RC_I2C_BASE + 0)
#define RC_I2C_HARDWARE_ERROR_BASE          (RC_I2C_BASE + 0x8000)

//! \section RTC result codes
#define RC_RTC_BASE                         (RC_BASE_HAL_BLOCK(1))
#define RC_RTC_YEAR_BEFORE_1980             (RC_RTC_BASE + 0)

//! \section SPI result codes
#define RC_SPI_BASE                         (RC_BASE_HAL_BLOCK(2))
#define RC_SPI_EXCHANGE_INVALID             (RC_SPI_BASE + 0)

//! \section NMEA0183 GPS device result codes
#define RC_NMEA0183_GPS_BASE                (RC_BASE_EXTERNAL_HAL_BLOCK(0))
#define RC_NMEA0183_NO_FIX_ACQUIRED         (RC_NMEA0183_GPS_BASE + 0)
