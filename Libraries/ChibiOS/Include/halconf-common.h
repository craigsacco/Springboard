/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#include <mcuconf.h>

//! \section mandatory HAL features
#define HAL_USE_PAL                 TRUE
#define HAL_USE_RTC                 TRUE
#define HAL_USE_WDG                 TRUE

//! \section mandatory peripheral features
#define I2C_USE_MUTUAL_EXCLUSION    FALSE
#define SPI_USE_WAIT                TRUE
#define SPI_USE_MUTUAL_EXCLUSION    FALSE

// TODO: common halconf.h definitions here
