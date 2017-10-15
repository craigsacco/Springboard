/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#include <board-common.h>

//! \section Voltage and external oscillator config
#define STM32_LSECLK                32768U
#define STM32_HSECLK                8000000U
#define STM32_VDD                   330U
#if MCU_FAMILY == MCU_FAMILY_STM32F7
#define STM32_LSEDRV                (3U << 3U)
#endif
