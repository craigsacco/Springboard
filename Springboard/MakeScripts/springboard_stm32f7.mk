# Supported microcontrollers in the STM32F4 family
#  * STM32F746 - xG (1MB)

# Architecture setting
MCU = cortex-m7
USE_FPU = hard
USE_FPU_OPT = -mfloat-abi=hard -mfpu=fpv5-sp-d16 -fsingle-precision-constant

# ChibiOS make includes - specific to this port
include $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_stm32f7xx.mk
include $(CHIBIOS)/os/hal/ports/STM32/STM32F7xx/platform.mk
include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/port_v7m.mk

# Microprocessor options for GCC
MCUOPT = -mthumb -DTHUMB -DMCU_FAMILY_NAME=\"STM32F7\" -DMCU_NAME=\"$(TARGET)\"

# ChibiOS linker script and definitions - STM32F746/F756 line
ifeq ($(TARGET), STM32F746xG)
LDSCRIPT = $(LDSCRIPTDIR_CHIBIOS)/STM32F746xG.ld
MCUOPT += -DMCU_LINE_NAME=\"STM32F746_F756\" -DMCU_TYPE_VALUE=MCU_TYPE\(STM32F7,STM32F746_F756,STM32F746xG\)

else
$(error Microcontroller not supported)
endif
