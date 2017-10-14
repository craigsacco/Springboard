/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#include <Springboard/MCUTypes.h>

#if MCU_FAMILY == MCU_FAMILY_STM32F4
#if MCU_LINE == MCU_LINE_STM32F405_F415 || \
    MCU_LINE == MCU_LINE_STM32F407_F417 || \
    MCU_LINE == MCU_LINE_STM32F427_F437 || \
    MCU_LINE == MCU_LINE_STM32F429_F439

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

#endif  // MCU_LINE == MCU_LINE_STM32F405_F415 || ...
#endif  // MCU_FAMILY == MCU_FAMILY_STM32F4

//! \section boardInit() declaration
#ifdef __cplusplus
extern "C" {
#endif
void boardInit(void);
#ifdef __cplusplus
}
#endif

//! \section Overriding default _unhandled_exception behaviour
#define _unhandled_exception                                \
    /* void */ _unhandled_exception(void) {                 \
        __asm volatile (                                    \
            " tst lr, #4                                \n" \
            " ite eq                                    \n" \
            " mrseq r0, msp                             \n" \
            " mrsne r0, psp                             \n" \
            " ldr r1, [r0, #24]                         \n" \
            " ldr r2, handler_addr                      \n" \
            " bx r2                                     \n" \
            " handler_addr: .word UnhandledException    \n" \
        );                                                  \
    }                                                       \
    void _old_unhandled_exception

//! \section Macros for pin/port definition
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

//! \section Microcontroller declaration
#if MCU_FAMILY == MCU_FAMILY_STM32F4
#if MCU_LINE == MCU_LINE_STM32F405_F415 || \
    MCU_LINE == MCU_LINE_STM32F407_F417
#define STM32F40_41xxx
#if MCU_VARIANT_STM32_IN_GROUP(MCU_VARIANT_STM32F405xx)
#define STM32F405xx
#elif MCU_VARIANT_STM32_IN_GROUP(MCU_VARIANT_STM32F407xx)
#define STM32F407xx
#elif MCU_VARIANT_STM32_IN_GROUP(MCU_VARIANT_STM32F415xx)
#define STM32F415xx
#elif MCU_VARIANT_STM32_IN_GROUP(MCU_VARIANT_STM32F417xx)
#define STM32F417xx
#endif
#elif MCU_LINE == MCU_LINE_STM32F427_F437
#define STM32F427_437xx
#if MCU_VARIANT_STM32_IN_GROUP(MCU_VARIANT_STM32F427xx)
#define STM32F427xx
#elif MCU_VARIANT_STM32_IN_GROUP(MCU_VARIANT_STM32F437xx)
#define STM32F437xx
#endif
#elif MCU_LINE == MCU_LINE_STM32F429_F439
#define STM32F429_439xx
#if MCU_VARIANT_STM32_IN_GROUP(MCU_VARIANT_STM32F429xx)
#define STM32F429xx
#elif MCU_VARIANT_STM32_IN_GROUP(MCU_VARIANT_STM32F439xx)
#define STM32F439xx
#endif
#else
#error "Unsupported microcontroller line"
#endif
#else
#error "Unsupported microcontroller family"
#endif
