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
#define RC_OK                               ((ResultCode)0UL)

//! \section Infrastructure result code macros and block ids
#define RC_BASE_INFRASTRUCTURE              ((ResultCode)0x10000000UL)
#define RC_BASE_INFRASTRUCTURE_BLOCK(x)     (RC_BASE_INFRASTRUCTURE + (x << 16))
#define RCBLK_INFRASTRUCTURE_RESOURCE       (0UL)
#define RCBLK_INFRASTRUCTURE_CONTROLLER     (1UL)
#define RCBLK_INFRASTRUCTURE_CONFIGURATION  (2UL)

//! \section Driver result code macros and block ids
#define RC_BASE_DRIVERS                     ((ResultCode)0x20000000UL)
#define RC_BASE_DRIVERS_BLOCK(x)            (RC_BASE_INFRASTRUCTURE + (x << 16))

//! \section HAL result code macros and block ids
#define RC_BASE_HAL                         ((ResultCode)0x30000000UL)
#define RC_BASE_HAL_BLOCK(x)                (RC_BASE_HAL + (x << 16))
#define RCBLK_HAL_I2C                       (0UL)
#define RCBLK_HAL_RTC                       (1UL)
#define RCBLK_HAL_SPI                       (2UL)

//! \section External HAL result code macros and block ids
#define RC_BASE_EXTERNAL_HAL                ((ResultCode)0x40000000)
#define RC_BASE_EXTERNAL_HAL_BLOCK(x)       (RC_BASE_EXTERNAL_HAL + (x << 16))
#define RCBLK_EXTERNAL_HAL_NMEA0183_GPS     (0UL)
#define RCBLK_EXTERNAL_HAL_MCP23017         (1UL)
#define RCBLK_EXTERNAL_HAL_AT45DBXX         (2UL)
#define RCBLK_EXTERNAL_HAL_AT24CXX          (3UL)

//! \section Resource result codes
#define RC_RESOURCE_BASE                    (RC_BASE_INFRASTRUCTURE_BLOCK(  \
                                             RCBLK_INFRASTRUCTURE_RESOURCE))
#define RC_RESOURCE_INVALID_TYPE            (RC_RESOURCE_BASE + 0UL)
#define RC_RESOURCE_INVALID_PROPERTY_ID     (RC_RESOURCE_BASE + 1UL)
#define RC_RESOURCE_PROPERTY_NOT_SETABLE    (RC_RESOURCE_BASE + 2UL)
#define RC_RESOURCE_INVALID_PROPERTY_LENGTH (RC_RESOURCE_BASE + 3UL)

//! \section Controller result codes
#define RC_CONTROLLER_BASE                  (RC_BASE_INFRASTRUCTURE_BLOCK(  \
                                             RCBLK_INFRASTRUCTURE_CONTROLLER))
#define RC_CONTROLLER_INVALID_RESOURCE_ID   (RC_CONTROLLER_BASE + 0UL)

//! \section Configuration result codes
#define RC_CONFIGURATION_BASE               (RC_BASE_INFRASTRUCTURE_BLOCK(  \
                                             RCBLK_INFRASTRUCTURE_CONFIGURATION))
#define RC_CONFIGURATION_FAILED             (RC_CONTROLLER_BASE + 0UL)

//! \section I2C result codes
#define RC_I2C_BASE                         (RC_BASE_HAL_BLOCK(RCBLK_HAL_I2C))
#define RC_I2C_TIMED_OUT                    (RC_I2C_BASE + 0UL)
#define RC_I2C_HARDWARE_ERROR_BASE          (RC_I2C_BASE + 0x8000UL)

//! \section RTC result codes
#define RC_RTC_BASE                         (RC_BASE_HAL_BLOCK(RCBLK_HAL_RTC))
#define RC_RTC_YEAR_BEFORE_1980             (RC_RTC_BASE + 0UL)

//! \section SPI result codes
#define RC_SPI_BASE                         (RC_BASE_HAL_BLOCK(RCBLK_HAL_SPI))
#define RC_SPI_EXCHANGE_INVALID             (RC_SPI_BASE + 0UL)

//! \section NMEA0183 GPS device result codes
#define RC_NMEA0183_GPS_BASE                (RC_BASE_EXTERNAL_HAL_BLOCK(    \
                                             RCBLK_EXTERNAL_HAL_NMEA0183_GPS))
#define RC_NMEA0183_NO_FIX_ACQUIRED         (RC_NMEA0183_GPS_BASE + 0UL)

//! \section MCP23017 expander device result codes
#define RC_MCP23017_BASE                    (RC_BASE_EXTERNAL_HAL_BLOCK(    \
                                             RCBLK_EXTERNAL_HAL_MCP23017))
#define RC_MCP23017_IOCON_INVALID           (RC_MCP23017_BASE + 0UL)

//! \section AT45DBxx flash device result codes
#define RC_AT45DBXX_BASE                    (RC_BASE_EXTERNAL_HAL_BLOCK(    \
                                             RCBLK_EXTERNAL_HAL_AT45DBXX))
#define RC_AT45DBXX_NO_nWP_PIN              (RC_AT45DBXX_BASE + 0UL)
#define RC_AT45DBXX_NO_nRST_PIN             (RC_AT45DBXX_BASE + 1UL)
#define RC_AT45DBXX_JEDEC_BUFFER_TOO_SMALL  (RC_AT45DBXX_BASE + 2UL)

//! \section AT24Cxx EEPROM device result codes
#define RC_AT24CXX_BASE                     (RC_BASE_EXTERNAL_HAL_BLOCK(    \
                                             RCBLK_EXTERNAL_HAL_AT24CXX))
#define RC_AT45DBXX_INVALID_OFFSET_OR_SIZE  (RC_AT24CXX_BASE + 0UL)
