/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif
void boardInit(void);
#ifdef __cplusplus
}
#endif

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

//! \section macros for pin/port definition
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

// TODO: common board.h definitions here

#include <board.h>
