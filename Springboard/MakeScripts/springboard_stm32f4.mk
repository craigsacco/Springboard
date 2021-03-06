# Supported microcontrollers in the STM32F4 family
#  * STM32F405 - xE (512kB) and xG (1MB)
#  * STM32F407 - xE (512kB) and xG (1MB)
#  * STM32F415 - xG (1MB)
#  * STM32F417 - xE (512kB) and xG (1MB)
#  * STM32F427 - xG (1MB) and xI (2MB)
#  * STM32F429 - xE (512kB), xG (1MB) and xI (2MB)
#  * STM32F437 - xG (1MB) and xI (2MB)
#  * STM32F439 - xG (1MB) and xI (2MB)

# Architecture setting
MCU = cortex-m4

# ChibiOS make includes - specific to this port
include $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_stm32f4xx.mk
include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/port_v7m.mk

# Microprocessor options for GCC
MCUOPT = -mthumb -DTHUMB -DMCU_FAMILY_NAME=\"STM32F4\" -DMCU_NAME=\"$(PROJECT_MCU)\"

# ChibiOS linker script and definitions - STM32F405/F415 line
ifeq ($(PROJECT_MCU), STM32F405xE)
LDSCRIPT = $(LDSCRIPTDIR_SPRINGBOARD)/STM32F405xE.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F405_F415\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F405_F415,STM32F405xE\)

else ifeq ($(PROJECT_MCU), STM32F405xG)
LDSCRIPT = $(LDSCRIPTDIR_CHIBIOS)/STM32F405xG.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F405_F415\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F405_F415,STM32F405xG\)

else ifeq ($(PROJECT_MCU), STM32F415xG)
LDSCRIPT = $(LDSCRIPTDIR_CHIBIOS)/STM32F405xG.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F405_F415\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F405_F415,STM32F415xG\)

# ChibiOS linker script and definitions - STM32F407/F417 line
else ifeq ($(PROJECT_MCU), STM32F407xE)
LDSCRIPT = $(LDSCRIPTDIR_CHIBIOS)/STM32F407xE.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F407_F417\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F407_F417,STM32F407xE\)

else ifeq ($(PROJECT_MCU), STM32F407xG)
LDSCRIPT = $(LDSCRIPTDIR_CHIBIOS)/STM32F407xG.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F407_F417\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F407_F417,STM32F407xG\)

else ifeq ($(PROJECT_MCU), STM32F417xE)
LDSCRIPT = $(LDSCRIPTDIR_CHIBIOS)/STM32F407xE.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F407_F417\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F407_F417,STM32F417xE\)

else ifeq ($(PROJECT_MCU), STM32F417xG)
LDSCRIPT = $(LDSCRIPTDIR_CHIBIOS)/STM32F407xG.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F407_F417\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F407_F417,STM32F417xG\)

# ChibiOS linker script and definitions - STM32F427/F437 line
else ifeq ($(PROJECT_MCU), STM32F427xG)
LDSCRIPT = $(LDSCRIPTDIR_SPRINGBOARD)/STM32F427xG.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F427_F437\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F427_F437,STM32F427xG\)

else ifeq ($(PROJECT_MCU), STM32F427xI)
LDSCRIPT = $(LDSCRIPTDIR_SPRINGBOARD)/STM32F427xI.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F427_F437\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F427_F437,STM32F427xI\)

else ifeq ($(PROJECT_MCU), STM32F437xG)
LDSCRIPT = $(LDSCRIPTDIR_SPRINGBOARD)/STM32F427xG.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F427_F437\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F427_F437,STM32F437xG\)

else ifeq ($(PROJECT_MCU), STM32F427xI)
LDSCRIPT = $(LDSCRIPTDIR_SPRINGBOARD)/STM32F427xI.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F427_F437\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F427_F437,STM32F437xI\)

# ChibiOS linker script and definitions - STM32F429/F439 line
else ifeq ($(PROJECT_MCU), STM32F429xE)
LDSCRIPT = $(LDSCRIPTDIR_SPRINGBOARD)/STM32F429xE.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F429_F439\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F429_F439,STM32F429xE\)

else ifeq ($(PROJECT_MCU), STM32F429xG)
LDSCRIPT = $(LDSCRIPTDIR_SPRINGBOARD)/STM32F429xG.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F429_F439\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F429_F439,STM32F429xG\)

else ifeq ($(PROJECT_MCU), STM32F427xI)
LDSCRIPT = $(LDSCRIPTDIR_SPRINGBOARD)/STM32F427xI.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F429_F439\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F429_F439,STM32F429xI\)

else ifeq ($(PROJECT_MCU), STM32F437xG)
LDSCRIPT = $(LDSCRIPTDIR_SPRINGBOARD)/STM32F427xG.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F429_F439\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F429_F439,STM32F439xG\)

else ifeq ($(PROJECT_MCU), STM32F427xI)
LDSCRIPT = $(LDSCRIPTDIR_SPRINGBOARD)/STM32F427xI.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F429_F439\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F4,STM32F429_F439,STM32F439xI\)

else
$(error Microcontroller not supported)
endif
