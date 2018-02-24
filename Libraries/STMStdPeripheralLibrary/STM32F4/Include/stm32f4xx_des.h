#pragma once

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

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
