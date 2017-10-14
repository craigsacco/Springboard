/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#include <Springboard/MCUTypes.h>

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
