# Project folders, includes and source
PROJECTINC = ./Include
PROJECTCSRC = $(wildcard ./Source/*.c)
PROJECTCPPSRC = $(wildcard ./Source/*.cpp)
PROJECTASMSRC = $(wildcard ./Source/*.s)
PROJECTASMXSRC = $(wildcard ./Source/*.S)
PROJECTHEADERS = $(wildcard $(PROJECTINC)/*.h) $(wildcard $(PROJECTINC)/*.hpp)

# Springboard folders, includes and source
SPRINGBOARDDIRS = . Kernel CommonHAL InternalHAL ExternalHAL Core Drivers Infrastructure Comms Utilities
SPRINGBOARDINC = $(SPRINGBOARD)/Include
SPRINGBOARDCSRC = $(foreach dir,$(addprefix $(SPRINGBOARD)/Source/,$(SPRINGBOARDDIRS)),$(wildcard $(dir)/*.c))
SPRINGBOARDCPPSRC = $(foreach dir,$(addprefix $(SPRINGBOARD)/Source/,$(SPRINGBOARDDIRS)),$(wildcard $(dir)/*.cpp))
SPRINGBOARDASMSRC = $(foreach dir,$(addprefix $(SPRINGBOARD)/Source/,$(SPRINGBOARDDIRS)),$(wildcard $(dir)/*.s))
SPRINGBOARDASMXSRC = $(foreach dir,$(addprefix $(SPRINGBOARD)/Source/,$(SPRINGBOARDDIRS)),$(wildcard $(dir)/*.S))
SPRINGBOARDHEADERS = $(foreach dir,$(addprefix $(SPRINGBOARD)/Include/Springboard/,$(SPRINGBOARDDIRS)),$(wildcard $(dir)/*.h)) \
                     $(foreach dir,$(addprefix $(SPRINGBOARD)/Include/Springboard/,$(SPRINGBOARDDIRS)),$(wildcard $(dir)/*.hpp))

# ChibiOS location
CHIBIOS = $(SPRINGBOARD)/../Libraries/ChibiOS/17.6.x

# ChibiOS make includes
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/hal/ports/STM32/STM32F4xx/platform.mk
include $(CHIBIOS)/os/hal/osal/rt/osal.mk
include $(CHIBIOS)/os/hal/lib/streams/streams.mk
include $(CHIBIOS)/os/rt/rt.mk

# Linker script locations
LDSCRIPTDIR_CHIBIOS = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/ld
LDSCRIPTDIR_SPRINGBOARD = $(SPRINGBOARD)/LinkerScripts

# Architecture settings
ifeq ($(findstring STM32F4,$(PROJECT_MCU)), STM32F4)
include $(SPRINGBOARD)/MakeScripts/springboard_stm32f4.mk
else
$(error Architecture is not defined, or is not supported)
endif

# ChibiOS make options
USE_OPT = -Og -ggdb -fomit-frame-pointer -falign-functions=16 --specs=nano.specs $(MCUOPT)
USE_COPT = -std=c11 -Wall -Wextra -Wundef -Wstrict-prototypes
USE_CPPOPT = -std=c++14 -fno-rtti -Wall -Wextra -Wundef -fno-exceptions
USE_LINK_GC = yes
USE_LDOPT =
USE_LTO = no
USE_THUMB = yes
USE_VERBOSE_COMPILE = no
USE_SMART_BUILD = no
USE_PROCESS_STACKSIZE = 0x1000
USE_EXCEPTIONS_STACKSIZE = 0x400
USE_FPU = hard

# Optional sources provided by ChibiOS
VARIOUSINC = $(CHIBIOS)/os/various
VARIOUSCSRC = $(VARIOUSINC)/syscalls.c
VARIOUSCPPSRC = $(VARIOUSINC)/cpp_wrappers/syscalls_cpp.cpp

# C sources
CSRC = $(STARTUPSRC) $(KERNSRC) $(PORTSRC) $(OSALSRC) $(HALSRC) \
       $(PLATFORMSRC) $(VARIOUSCSRC) $(STREAMSSRC) $(SPRINGBOARDCSRC) \
       $(PROJECTCSRC)

# C++ sources
CPPSRC = $(VARIOUSCPPSRC) $(SPRINGBOARDCPPSRC) $(PROJECTCPPSRC)

# ASM sources
ASMSRC = $(SPRINGBOARDASMSRC) $(PROJECTASMSRC)
ASMXSRC = $(STARTUPASM) $(PORTASM) $(OSALASM) $(SPRINGBOARDASMXSRC) \
          $(PROJECTASMXSRC)

# Includes folders
INCDIR = $(CHIBIOS)/os/license $(CHIBIOS)/../Include $(STARTUPINC) $(KERNINC) \
         $(PORTINC) $(OSALINC) $(HALINC) $(PLATFORMINC) $(VARIOUSINC) \
         $(STREAMSINC) $(SPRINGBOARDINC) $(PROJECTINC)

# Tools
CC   = arm-none-eabi-gcc
CPPC = arm-none-eabi-g++
LD   = arm-none-eabi-g++
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
QTGENPRJ_FILES_LIST = $(sort $(CSRC) $(CPPSRC) $(ASMXSRC) $(LDSCRIPT) $(SPRINGBOARDHEADERS) \
                             $(foreach dir,$(QTGENPRJ_INCLUDES_LIST),$(wildcard $(dir)/*.h)) \
                             $(foreach dir,$(QTGENPRJ_INCLUDES_LIST),$(wildcard $(dir)/*.hpp)) \
                             Makefile)
define update_qt_creator_project
	@rm -f $(QTGENPRJ_FILES) $(QTGENPRJ_INCLUDES)
	@$(foreach file,$(QTGENPRJ_FILES_LIST),echo `realpath --relative-to=. $(file)` >> $(QTGENPRJ_FILES);)
	@$(foreach dir,$(QTGENPRJ_INCLUDES_LIST),echo `realpath --relative-to=. $(dir)` >> $(QTGENPRJ_INCLUDES);)
endef

define generate_cpplint_report
	@cpplint --filter=-whitespace/braces,-whitespace/indent \
             $(PROJECTCSRC) $(PROJECTCPPSRC) $(PROJECTHEADERS) \
		     $(SPRINGBOARDCSRC) $(SPRINGBOARDCPPSRC) $(SPRINGBOARDHEADERS) || true
endef

# ChibiOS pre/post make hooks
PRE_MAKE_ALL_RULE_HOOK:
	$(call update_qt_creator_project)

POST_MAKE_ALL_RULE_HOOK:
	$(call generate_cpplint_report)
