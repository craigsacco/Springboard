# Architecture setting
MCU = cortex-m4

# ChibiOS location
CHIBIOS = $(SPRINGBOARD)/../Libraries/ChibiOS/17.6.x

# ChibiOS make options
USE_OPT = -O2 -ggdb -fomit-frame-pointer -falign-functions=16 -mthumb \
          -DTHUMB
USE_COPT = -Wall -Wextra -Wundef -Wstrict-prototypes
USE_CPPOPT = -fno-rtti -Wall -Wextra -Wundef
USE_LINK_GC = yes
USE_LDOPT =
USE_LTO = yes
USE_THUMB = yes
USE_VERBOSE_COMPILE = no
USE_SMART_BUILD = no
USE_PROCESS_STACKSIZE = 0x400
USE_EXCEPTIONS_STACKSIZE = 0x400
USE_FPU = hard

# ChibiOS make includes
include $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_stm32f4xx.mk
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/hal/ports/STM32/STM32F4xx/platform.mk
include $(CHIBIOS)/os/hal/boards/ST_STM32F4_DISCOVERY/board.mk
include $(CHIBIOS)/os/hal/osal/rt/osal.mk
include $(CHIBIOS)/os/rt/rt.mk
include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/port_v7m.mk

# Define linker script file here
LDSCRIPT = $(STARTUPLD)/STM32F407xG.ld

# C sources
CSRC = $(STARTUPSRC) $(KERNSRC) $(PORTSRC) $(OSALSRC) $(HALSRC) \
       $(PLATFORMSRC) $(BOARDSRC) $(TESTSRC) \
       $(wildcard Source/*.c)

# C++ sources
CPPSRC = $(wildcard Source/*.cpp)

# ASM sources
ASMXSRC = $(STARTUPASM) $(PORTASM) $(OSALASM) \
          $(wildcard Source/*.S)

INCDIR = $(CHIBIOS)/os/license $(STARTUPINC) $(KERNINC) $(PORTINC) \
         $(OSALINC) $(HALINC) $(PLATFORMINC) $(BOARDINC) $(TESTINC) \
         $(CHIBIOS)/os/various Include

# Project files
OUTFILES = $(PROJECT).config $(PROJECT).creator $(PROJECT).files \
           $(PROJECT).includes

# Tools
CC   = arm-none-eabi-gcc
CPPC = arm-none-eabi-g++
LD   = arm-none-eabi-gcc
CP   = arm-none-eabi-objcopy
AS   = $(CC) -x assembler-with-cpp
AR   = arm-none-eabi-ar
OD   = arm-none-eabi-objdump
SZ   = arm-none-eabi-size
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary

# ChibiOS build rules
RULESPATH = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC
include $(RULESPATH)/rules.mk

# Qt Generic project file generation
QTGENPRJ_CONFIG = $(PROJECT).config
QTGENPRJ_CREATOR = $(PROJECT).creator
QTGENPRJ_FILES = $(PROJECT).files
QTGENPRJ_INCLUDES = $(PROJECT).includes
QTGENPRJ_INCLUDES_LIST = $(sort $(INCDIR))
QTGENPRJ_FILES_LIST = $(sort $(CSRC) $(CPPSRC) $(ASMXSRC) $(LDSCRIPT) \
                        	 $(foreach dir,$(QTGENPRJ_INCLUDES_LIST),$(wildcard $(dir)/*.h)) \
                             Makefile)
define update_qt_creator_project
	@rm -f $(QTGENPRJ_FILES) $(QTGENPRJ_INCLUDES)
	@$(foreach file,$(QTGENPRJ_FILES_LIST),echo `realpath --relative-to=. $(file)` >> $(QTGENPRJ_FILES);)
	@$(foreach dir,$(QTGENPRJ_INCLUDES_LIST),echo `realpath --relative-to=. $(dir)` >> $(QTGENPRJ_INCLUDES);)
endef

# ChibiOS pre/post make hooks
PRE_MAKE_ALL_RULE_HOOK:
	$(call update_qt_creator_project)

