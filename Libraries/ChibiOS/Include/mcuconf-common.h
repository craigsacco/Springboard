/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

//! \section MCU configuration declaration
#define STM32F4xx_MCUCONF

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
#define __CM4_REV_STR           __CM4_ARCH_REV_STR __CM4_ARCH_PATCH_STR
#endif  // CORTEX_MODEL == 4

//! \section device electronic signature
#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || \
    defined(STM32F429_439xx)
#define MCU_UNIQUE_ID_LENGTH    12
typedef struct
{
    uint32_t                    low;
    uint32_t                    middle;
    uint32_t                    high;
} DES_UID_Regs_TypeDef;

typedef union
{
    DES_UID_Regs_TypeDef        regs;
    uint8_t                     data[MCU_UNIQUE_ID_LENGTH];
} DES_UID_TypeDef;

typedef struct
{
    DES_UID_TypeDef             UID;            /*!< Unique device ID */
    uint8_t                     RESERVED0[2];
    uint16_t                    FLASH_SIZE;     /*!< flash size (in kB) */
} DES_TypeDef;

#define DES_BASE                (0x1FFF7A10)
#define DES                     ((DES_TypeDef *) DES_BASE)
#endif  // defined(STM32F40_41xxx) || defined(STM32F427_437xx) || ...

//! \section mandatory driver features
#define STM32_WDG_USE_IWDG                  TRUE
#define STM32_I2C_DMA_ERROR_HOOK(i2cp)      osalSysHalt("DMA failure")
