
PROJECT_NAME = STMApp

STM32F4_ROOT = ../../Libraries/STMStdPeripheralLibrary/STM32F4/1.8.0
STM32F4_INC = $(STM32F4_ROOT)/Libraries/STM32F4xx_StdPeriph_Driver/inc
STM32F4_SRC = $(STM32F4_ROOT)/Libraries/STM32F4xx_StdPeriph_Driver/src
STM32F4_CMSIS = $(STM32F4_ROOT)/Libraries/CMSIS/Include
STM32F4_CMSIS_STM32F4 = $(STM32F4_ROOT)/Libraries/CMSIS/Device/ST/STM32F4xx/Include
STM32F4_CMSIS_STARTUP = $(STM32F4_ROOT)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/SW4STM32
STM32F4_OTHER = $(STM32F4_ROOT)/../Include

FREERTOS_ROOT = ../../Libraries/FreeRTOS/10.0.1
FREERTOS_INC = $(FREERTOS_ROOT)/FreeRTOS/Source/include
FREERTOS_SRC = $(FREERTOS_ROOT)/FreeRTOS/Source
FREERTOS_PORT = $(FREERTOS_SRC)/portable/GCC/ARM_CM4F
FREERTOS_PORT_MEMMANG = $(FREERTOS_SRC)/portable/MemMang

SPRINGBOARD_ROOT = ../../Springboard
SPRINGBOARD_INC = $(SPRINGBOARD_ROOT)/Include
SPRINGBOARD_SRC = $(SPRINGBOARD_ROOT)/Source
SPRINGBOARD_MODULES = CommonHAL Configuration InternalHAL Utilities

INCDIR = ./Include $(STM32F4_INC) $(STM32F4_CMSIS) $(STM32F4_CMSIS_STM32F4) $(STM32F4_OTHER) $(FREERTOS_INC) \
         $(FREERTOS_PORT) $(SPRINGBOARD_INC)
SRCDIR = ./Source $(STM32F4_SRC) $(STM32F4_CMSIS_STARTUP) $(FREERTOS_SRC) $(FREERTOS_PORT) $(FREERTOS_PORT_MEMMANG) \
         $(foreach module,$(SPRINGBOARD_MODULES),$(SPRINGBOARD_SRC)/$(module))

STM32F4_SOURCE_ASM = $(STM32F4_CMSIS_STARTUP)/startup_stm32f40_41xxx.s
STM32F4_SOURCE_C = $(addprefix $(STM32F4_SRC)/, stm32f4xx_adc.c \
                                                stm32f4xx_crc.c \
                                                stm32f4xx_dbgmcu.c \
                                                stm32f4xx_dma.c \
                                                stm32f4xx_exti.c \
                                                stm32f4xx_flash.c \
                                                stm32f4xx_gpio.c \
                                                stm32f4xx_i2c.c \
                                                stm32f4xx_iwdg.c \
                                                stm32f4xx_pwr.c \
                                                stm32f4xx_rcc.c \
                                                stm32f4xx_rtc.c \
                                                stm32f4xx_sdio.c \
                                                stm32f4xx_spi.c \
                                                stm32f4xx_syscfg.c \
                                                stm32f4xx_tim.c \
                                                stm32f4xx_usart.c \
                                                stm32f4xx_wwdg.c \
                                                stm32f4xx_cryp.c \
                                                stm32f4xx_hash.c \
                                                stm32f4xx_rng.c \
                                                stm32f4xx_can.c \
                                                stm32f4xx_dac.c \
                                                stm32f4xx_dcmi.c \
                                                stm32f4xx_fsmc.c)

FREERTOS_SOURCE_C = $(addprefix $(FREERTOS_SRC)/, croutine.c \
                                                  event_groups.c \
                                                  list.c \
                                                  queue.c \
                                                  stream_buffer.c \
                                                  tasks.c \
                                                  timers.c) \
                    $(FREERTOS_PORT)/port.c \
                    $(FREERTOS_PORT_MEMMANG)/heap_1.c

SPRINGBOARD_SOURCE_CPP = $(foreach module,$(SPRINGBOARD_MODULES),$(wildcard $(SPRINGBOARD_SRC)/$(module)/*.cpp))

SOURCE_ASM = $(wildcard ./Source/*.s) $(STM32F4_SOURCE_ASM)
SOURCE_C = $(wildcard ./Source/*.c) $(STM32F4_SOURCE_C) $(FREERTOS_SOURCE_C)
SOURCE_CPP = $(wildcard ./Source/*.cpp) $(SPRINGBOARD_SOURCE_CPP)

OBJDIR = ./build/objs
OBJECTS_ASM = $(addprefix $(OBJDIR)/, $(notdir $(SOURCE_ASM:.s=.o)))
OBJECTS_C = $(addprefix $(OBJDIR)/, $(notdir $(SOURCE_C:.c=.o)))
OBJECTS_CPP = $(addprefix $(OBJDIR)/, $(notdir $(SOURCE_CPP:.cpp=.o)))

OUTDIR = ./build/output
ELFOUT = $(OUTDIR)/$(PROJECT_NAME).elf
BINOUT = $(OUTDIR)/$(PROJECT_NAME).bin
LSTOUT = $(OUTDIR)/$(PROJECT_NAME).lst

QTPRJCONFIG = ./$(PROJECT_NAME).config
QTPRJFILES = ./$(PROJECT_NAME).files
QTPRJINCLUDES = ./$(PROJECT_NAME).includes
QTPRJOUT = ./$(PROJECT_NAME).creator

DEPDIR = ./build/deps

MCU_FAMILY_NAME = STM32F4
MCU_LINE_NAME = STM32F407_F417
MCU_NAME = STM32F407xG

LDSCRIPT = ./$(MCU_NAME).ld

CC = arm-none-eabi-gcc
CPP = arm-none-eabi-g++
LD = arm-none-eabi-g++
AS = arm-none-eabi-gcc -x assembler-with-cpp
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size

DEFS = -DTHUMB_PRESENT -DUSE_STDPERIPH_DRIVER -DTHUMB_NO_INTERWORKING -DCORTEX_USE_FPU=TRUE
DEFS += -DMCU_FAMILY_NAME=\"$(MCU_FAMILY_NAME)\" -DMCU_NAME=\"$(MCU_NAME)\"
DEFS += -DMCU_LINE_NAME=\"$(MCU_LINE_NAME)\" -DMCU_TYPE_VALUE=MCU_TYPE\($(MCU_FAMILY_NAME),$(MCU_LINE_NAME),$(MCU_NAME)\)
OPT = $(DEFS) -c -mcpu=cortex-m4 -O2 -ggdb -fomit-frame-pointer -falign-functions=16 -mno-thumb-interwork
OPT += -ffunction-sections -fdata-sections -fno-common -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant
OPT += $(addprefix -I, $(INCDIR)) -MD -MP -MF $(DEPDIR)/$(@F).d
OPT += -DSTM32F40_41xxx
ASMOPT = $(OPT) -mthumb
CXXOPT = $(OPT) -Wall -Wextra -Wundef
COPT = $(CXXOPT) -Wstrict-prototypes -std=c11
CPPOPT = $(CXXOPT) -fno-rtti -std=c++17
LDOPT = -mno-thumb-interwork -mthumb --specs=nosys.specs -Wl,-Map=$(OUTDIR)/$(PROJECT_NAME).map,--no-warn-mismatch,--gc-sections,--script=$(LDSCRIPT)
BINOPT = -x --syms

VPATH = $(SRCDIR)

all : PRE_MAKE_ALL_RULE_HOOK $(ELFOUT) $(BINOUT) $(LSTOUT)

PRE_MAKE_ALL_RULE_HOOK : $(QTPRJOUT)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(DEPDIR):
	@mkdir -p $(DEPDIR)

$(OUTDIR):
	@mkdir -p $(OUTDIR)

$(OBJECTS_ASM) : $(OBJDIR)/%.o : %.s $(OBJDIR) $(DEPDIR)
	$(AS) $(ASMOPT) -o $@ $<

$(OBJECTS_C) : $(OBJDIR)/%.o : %.c $(OBJDIR) $(DEPDIR)
	$(CC) $(COPT) -o $@ $<

$(OBJECTS_CPP) : $(OBJDIR)/%.o : %.cpp $(OBJDIR) $(DEPDIR)
	$(CPP) $(CPPOPT) -o $@ $<

$(ELFOUT) : $(OBJECTS_ASM) $(OBJECTS_C) $(OBJECTS_CPP) $(OUTDIR)
	$(LD) $(LDOPT) -o $@ $(OBJECTS_ASM) $(OBJECTS_C) $(OBJECTS_CPP)

$(BINOUT): $(ELFOUT)
	$(OBJDUMP) $(BINOPT) $< > $@
	$(SIZE) $<

$(LSTOUT): $(ELFOUT)
	$(OBJDUMP) -S $< > $@

$(QTPRJOUT): Makefile
	@touch $(QTPRJOUT)
	@touch $(QTPRJCONFIG)
	@rm -f $(QTPRJFILES) $(QTPRJINCLUDES)
	@$(foreach file,$(SOURCE_ASM),echo `realpath --relative-to=. $(file)` >> $(QTPRJFILES);)
	@$(foreach file,$(SOURCE_C),echo `realpath --relative-to=. $(file)` >> $(QTPRJFILES);)
	@$(foreach file,$(SOURCE_CPP),echo `realpath --relative-to=. $(file)` >> $(QTPRJFILES);)
	@$(foreach file,$(foreach dir,$(INCDIR),$(shell find $(dir) -type f -name '*.h')),echo `realpath --relative-to=. $(file)` >> $(QTPRJFILES);)
	@$(foreach file,$(foreach dir,$(INCDIR),$(shell find $(dir) -type f -name '*.hpp')),echo `realpath --relative-to=. $(file)` >> $(QTPRJFILES);)
	@echo $(LDSCRIPT) >>  $(QTPRJFILES)
	@echo Makefile >>  $(QTPRJFILES)
	@$(foreach dir,$(INCDIR),echo `realpath --relative-to=. $(dir)` >> $(QTPRJINCLUDES);)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(OUTDIR)
	rm -rf $(DEPDIR)
