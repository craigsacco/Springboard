# Architecture setting
MCU = cortex-m4

# Project folders, includes and source
PROJECTINC = ./Include
PROJECTCSRC = $(wildcard ./Source/*.c)
PROJECTCPPSRC = $(wildcard ./Source/*.cpp)
PROJECTASMSRC = $(wildcard ./Source/*.s)
PROJECTASMXSRC = $(wildcard ./Source/*.S)
PROJECTHEADERS = $(wildcard $(PROJECTINC)/*.h) $(wildcard $(PROJECTINC)/*.hpp)

# Springboard folders, includes and source
SPRINGBOARDDIRS = . Kernel CommonHAL InternalHAL ExternalHAL
SPRINGBOARDINC = $(SPRINGBOARD)/Include
SPRINGBOARDCSRC = $(foreach dir,$(addprefix $(SPRINGBOARD)/Source/,$(SPRINGBOARDDIRS)),$(wildcard $(dir)/*.c))
SPRINGBOARDCPPSRC = $(foreach dir,$(addprefix $(SPRINGBOARD)/Source/,$(SPRINGBOARDDIRS)),$(wildcard $(dir)/*.cpp))
SPRINGBOARDASMSRC = $(foreach dir,$(addprefix $(SPRINGBOARD)/Source/,$(SPRINGBOARDDIRS)),$(wildcard $(dir)/*.s))
SPRINGBOARDASMXSRC = $(foreach dir,$(addprefix $(SPRINGBOARD)/Source/,$(SPRINGBOARDDIRS)),$(wildcard $(dir)/*.S))
SPRINGBOARDHEADERS = $(foreach dir,$(addprefix $(SPRINGBOARD)/Include/Springboard/,$(SPRINGBOARDDIRS)),$(wildcard $(dir)/*.h)) \
                     $(foreach dir,$(addprefix $(SPRINGBOARD)/Include/Springboard/,$(SPRINGBOARDDIRS)),$(wildcard $(dir)/*.hpp))

# ChibiOS version and location
CHIBIOSVERSION = 17.6.x
ifeq ($(filter $(CHIBIOSVERSION),16.1.x 17.6.x),)
	$(error Unknown ChibiOS version - only 16.1.x and 17.6.x are supported)
endif
ifeq ($(CHIBIOSVERSION),17.6.x)
	CHIBIOSVERSIONDEF = 1706
else
	CHIBIOSVERSIONDEF = 1601
endif
CHIBIOS = $(SPRINGBOARD)/../Libraries/ChibiOS/$(CHIBIOSVERSION)

# ChibiOS make options
USE_OPT = -Og -ggdb -fomit-frame-pointer -falign-functions=16 -mthumb \
          -DTHUMB -DCH_VERSION=$(CHIBIOSVERSIONDEF)
USE_COPT = -Wall -Wextra -Wundef -Wstrict-prototypes
USE_CPPOPT = -fno-rtti -Wall -Wextra -Wundef
USE_LINK_GC = yes
USE_LDOPT =
USE_LTO = no
USE_THUMB = yes
USE_VERBOSE_COMPILE = no
USE_SMART_BUILD = no
USE_PROCESS_STACKSIZE = 0x400
USE_EXCEPTIONS_STACKSIZE = 0x400
USE_FPU = hard

# ChibiOS make includes
CHIBIOSMKHAL = $(CHIBIOS)/os/hal/hal.mk
CHIBIOSMKPLATFORM = $(CHIBIOS)/os/hal/ports/STM32/STM32F4xx/platform.mk
CHIBIOSMKOSAL = $(CHIBIOS)/os/hal/osal/rt/osal.mk
CHIBIOSMKRT = $(CHIBIOS)/os/rt/rt.mk
ifeq ($(CHIBIOSVERSION),17.6.x)
	CHIBIOSMKSTARTUP = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_stm32f4xx.mk
	CHIBIOSMKPORT = $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/port_v7m.mk
else
	CHIBIOSMKSTARTUP = $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/startup_stm32f4xx.mk
	CHIBIOSMKPORT = $(CHIBIOS)/os/rt/ports/ARMCMx/compilers/GCC/mk/port_v7m.mk
endif
include $(CHIBIOSMKSTARTUP)
include $(CHIBIOSMKHAL)
include $(CHIBIOSMKPLATFORM)
include $(CHIBIOSMKOSAL)
include $(CHIBIOSMKRT)
include $(CHIBIOSMKPORT)

# Define linker script file here
LDSCRIPT = $(STARTUPLD)/STM32F407xG.ld

# Optional sources provided by ChibiOS
VARIOUSINC = $(CHIBIOS)/os/various
VARIOUSCSRC = $(VARIOUSINC)/syscalls.c
VARIOUSCPPSRC = $(VARIOUSINC)/cpp_wrappers/syscalls_cpp.cpp

# C sources
CSRC = $(STARTUPSRC) $(KERNSRC) $(PORTSRC) $(OSALSRC) $(HALSRC) \
       $(PLATFORMSRC) $(VARIOUSCSRC) $(SPRINGBOARDCSRC) \
       $(PROJECTCSRC)

# C++ sources
CPPSRC = $(VARIOUSCPPSRC) $(SPRINGBOARDCPPSRC) $(PROJECTCPPSRC)

# ASM sources
ifeq ($(CHIBIOSVERSION),17.6.x)
	ASMSRC = $(SPRINGBOARDASMSRC) $(PROJECTASMSRC)
	ASMXSRC = $(STARTUPASM) $(PORTASM) $(OSALASM) $(SPRINGBOARDASMXSRC) \
	          $(PROJECTASMXSRC)
else
	ASMSRC = $(STARTUPASM) $(PORTASM) $(OSALASM) $(SPRINGBOARDASMSRC) \
	         $(PROJECTASMSRC)
	ASMXSRC = $(SPRINGBOARDASMXSRC) $(PROJECTASMXSRC)
endif

# Includes folders
INCDIR = $(CHIBIOS)/os/license $(STARTUPINC) $(KERNINC) $(PORTINC) \
         $(OSALINC) $(HALINC) $(PLATFORMINC) $(VARIOUSINC) \
         $(SPRINGBOARDINC) $(PROJECTINC)

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
ifeq ($(CHIBIOSVERSION),17.6.x)
	RULESPATH = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC
else
	RULESPATH = $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC
endif
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
