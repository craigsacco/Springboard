/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#include <Springboard/MCUTypes.h>

//! \section MCU configuration declaration
#if MCU_FAMILY == MCU_FAMILY_STM32F4
#define STM32F4xx_MCUCONF
#endif
#if MCU_FAMILY == MCU_FAMILY_STM32F7
#define STM32F7xx_MCUCONF
#endif

//! \section ARM architecture version
#if CORTEX_MODEL == 4
#define __CM4_ARCH_REV          ((__CM4_REV >> 8) & 0xff)
#define __CM4_ARCH_PATCH        (__CM4_REV & 0xff)
#if __CM4_ARCH_REV == 0
#define __CM4_ARCH_REV_STR      "r0"
#elif __CM4_ARCH_REV == 1
#define __CM4_ARCH_REV_STR      "r1"
#elif __CM4_ARCH_REV == 2
#define __CM4_ARCH_REV_STR      "r2"
#elif __CM4_ARCH_REV == 3
#define __CM4_ARCH_REV_STR      "r3"
#elif __CM4_ARCH_REV == 4
#define __CM4_ARCH_REV_STR      "r4"
#elif __CM4_ARCH_REV == 5
#define __CM4_ARCH_REV_STR      "r5"
#else
#error "Need more conditions here"
#endif
#if __CM4_ARCH_PATCH == 0
#define __CM4_ARCH_PATCH_STR    "p0"
#elif __CM4_ARCH_PATCH == 1
#define __CM4_ARCH_PATCH_STR    "p1"
#elif __CM4_ARCH_PATCH == 2
#define __CM4_ARCH_PATCH_STR    "p2"
#elif __CM4_ARCH_PATCH == 3
#define __CM4_ARCH_PATCH_STR    "p3"
#elif __CM4_ARCH_PATCH == 4
#define __CM4_ARCH_PATCH_STR    "p4"
#elif __CM4_ARCH_PATCH == 5
#define __CM4_ARCH_PATCH_STR    "p5"
#else
#error "Need more conditions here"
#endif
#define PORT_ARCHITECTURE_REVISION  __CM4_ARCH_REV_STR __CM4_ARCH_PATCH_STR
#else
#define PORT_ARCHITECTURE_REVISION  "Unknown"
#endif  // CORTEX_MODEL == 4

//! \section device electronic signature
#if (MCU_FAMILY == MCU_FAMILY_STM32F4 && \
     (MCU_LINE == MCU_LINE_STM32F405_F415 || \
      MCU_LINE == MCU_LINE_STM32F407_F417 || \
      MCU_LINE == MCU_LINE_STM32F427_F437 || \
      MCU_LINE == MCU_LINE_STM32F429_F439)) || \
    (MCU_FAMILY == MCU_FAMILY_STM32F7 && \
     (MCU_LINE == MCU_LINE_STM32F746_F756))
#define MCU_DES_UID_LENGTH      12
typedef struct
{
    uint32_t                    low;
    uint32_t                    middle;
    uint32_t                    high;
} DES_UID_Regs_TypeDef;

typedef union
{
    DES_UID_Regs_TypeDef        regs;
    uint8_t                     data[MCU_DES_UID_LENGTH];
} DES_UID_TypeDef;

typedef struct
{
    DES_UID_TypeDef             UID;            /*!< Unique device ID */
    uint8_t                     RESERVED0[2];
    uint16_t                    FLASH_SIZE;     /*!< flash size (in kB) */
} DES_TypeDef;

#if MCU_FAMILY == MCU_FAMILY_STM32F4
#define DES_BASE                (0x1FFF7A10)
#elif MCU_FAMILY == MCU_FAMILY_STM32F7
#define DES_BASE                (0x1FF0F420)
#endif
#define DES                     ((DES_TypeDef *) DES_BASE)
#endif  // MCU_FAMILY == MCU_FAMILY_STM32F4 && ( ...

//! \section mandatory driver features
#define STM32_WDG_USE_IWDG                  TRUE
#define STM32_I2C_DMA_ERROR_HOOK(i2cp)      osalSysHalt("DMA failure")
#define STM32_SPI_DMA_ERROR_HOOK(spip)      osalSysHalt("DMA failure")
#define STM32_ST_IRQ_PRIORITY               8
#define STM32_ST_USE_TIMER                  2
