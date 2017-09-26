/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#include <board-common.h>

//! \section Voltage and external oscillator config
#define STM32_LSECLK                32768U
#define STM32_HSECLK                8000000U
#define STM32_VDD                   330U

//! \section Micro is an STM32F407xx
#define STM32F407xx
#define STM32F40_41xxx

//! \section Debug port/pad definitions
#define DEBUG_SWDIO_PORT            GPIOA
#define DEBUG_SWDIO_PAD             13
#define DEBUG_SWDIO_AF              0
#define DEBUG_SWCLK_PORT            GPIOA
#define DEBUG_SWCLK_PAD             14
#define DEBUG_SWCLK_AF              0
#define DEBUG_SWO_PORT              GPIOB
#define DEBUG_SWO_PAD               3
#define DEBUG_SWO_AF                0

//! \section GPIOA configuration
#define VAL_GPIOA_MODER             (PIN_MODE_ALTERNATE(DEBUG_SWDIO_PAD) | \
                                     PIN_MODE_ALTERNATE(DEBUG_SWCLK_PAD))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(DEBUG_SWDIO_PAD) | \
                                     PIN_OTYPE_PUSHPULL(DEBUG_SWCLK_PAD))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(DEBUG_SWDIO_PAD) | \
                                     PIN_OSPEED_HIGH(DEBUG_SWCLK_PAD))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(DEBUG_SWDIO_PAD) | \
                                     PIN_PUPDR_FLOATING(DEBUG_SWCLK_PAD))
#define VAL_GPIOA_ODR               (0U)
#define VAL_GPIOA_AFRL              (0U)
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(DEBUG_SWDIO_PAD, \
                                                 DEBUG_SWDIO_AF) | \
                                     PIN_AFIO_AF(DEBUG_SWCLK_PAD, \
                                                 DEBUG_SWCLK_AF))

//! \section GPIOB configuration
#define VAL_GPIOB_MODER             (PIN_MODE_ALTERNATE(DEBUG_SWO_PAD))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(DEBUG_SWO_PAD))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(DEBUG_SWO_PAD))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(DEBUG_SWO_PAD))
#define VAL_GPIOB_ODR               (0U)
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(DEBUG_SWO_PAD, DEBUG_SWO_AF))
#define VAL_GPIOB_AFRH              (0U)

//! \section GPIOC configuration
#define VAL_GPIOC_MODER             (0U)
#define VAL_GPIOC_OTYPER            (0U)
#define VAL_GPIOC_OSPEEDR           (0U)
#define VAL_GPIOC_PUPDR             (0U)
#define VAL_GPIOC_ODR               (0U)
#define VAL_GPIOC_AFRL              (0U)
#define VAL_GPIOC_AFRH              (0U)

//! \section GPIOD configuration
#define VAL_GPIOD_MODER             (0U)
#define VAL_GPIOD_OTYPER            (0U)
#define VAL_GPIOD_OSPEEDR           (0U)
#define VAL_GPIOD_PUPDR             (0U)
#define VAL_GPIOD_ODR               (0U)
#define VAL_GPIOD_AFRL              (0U)
#define VAL_GPIOD_AFRH              (0U)

//! \section GPIOE configuration
#define VAL_GPIOE_MODER             (0U)
#define VAL_GPIOE_OTYPER            (0U)
#define VAL_GPIOE_OSPEEDR           (0U)
#define VAL_GPIOE_PUPDR             (0U)
#define VAL_GPIOE_ODR               (0U)
#define VAL_GPIOE_AFRL              (0U)
#define VAL_GPIOE_AFRH              (0U)

//! \section GPIOF configuration
#define VAL_GPIOF_MODER             (0U)
#define VAL_GPIOF_OTYPER            (0U)
#define VAL_GPIOF_OSPEEDR           (0U)
#define VAL_GPIOF_PUPDR             (0U)
#define VAL_GPIOF_ODR               (0U)
#define VAL_GPIOF_AFRL              (0U)
#define VAL_GPIOF_AFRH              (0U)

//! \section GPIOG configuration
#define VAL_GPIOG_MODER             (0U)
#define VAL_GPIOG_OTYPER            (0U)
#define VAL_GPIOG_OSPEEDR           (0U)
#define VAL_GPIOG_PUPDR             (0U)
#define VAL_GPIOG_ODR               (0U)
#define VAL_GPIOG_AFRL              (0U)
#define VAL_GPIOG_AFRH              (0U)

//! \section GPIOH configuration
#define VAL_GPIOH_MODER             (0U)
#define VAL_GPIOH_OTYPER            (0U)
#define VAL_GPIOH_OSPEEDR           (0U)
#define VAL_GPIOH_PUPDR             (0U)
#define VAL_GPIOH_ODR               (0U)
#define VAL_GPIOH_AFRL              (0U)
#define VAL_GPIOH_AFRH              (0U)

//! \section GPIOI configuration
#define VAL_GPIOI_MODER             (0U)
#define VAL_GPIOI_OTYPER            (0U)
#define VAL_GPIOI_OSPEEDR           (0U)
#define VAL_GPIOI_PUPDR             (0U)
#define VAL_GPIOI_ODR               (0U)
#define VAL_GPIOI_AFRL              (0U)
#define VAL_GPIOI_AFRH              (0U)

#ifdef __cplusplus
extern "C" {
#endif
void boardInit(void);
#ifdef __cplusplus
}
#endif
