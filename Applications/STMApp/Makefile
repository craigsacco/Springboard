


STM32F4_ROOT = ../../Libraries/STMStdPeripheralLibrary/STM32F4/1.8.0
STM32F4_INC = $(STM32F4_ROOT)/Libraries/STM32F4xx_StdPeriph_Driver/inc
STM32F4_CMSIS = $(STM32F4_ROOT)/Libraries/CMSIS/Include
STM32F4_CMSIS_STM32F4 = $(STM32F4_ROOT)/Libraries/CMSIS/Device/ST/STM32F4xx/Include
STM32F4_SRC = $(STM32F4_ROOT)/Libraries/STM32F4xx_StdPeriph_Driver/src

INCDIR = ./Include $(STM32F4_INC) $(STM32F4_CMSIS) $(STM32F4_CMSIS_STM32F4)
SRCDIR = ./Source $(STM32F4_SRC)

SOURCE_ASM = $(wildcard ./Source/*.S) $(wildcard $(STM32F4_SRC)/*.S)
SOURCE_C = $(wildcard ./Source/*.c) $(wildcard $(STM32F4_SRC)/*.c)
SOURCE_CPP = $(wildcard ./Source/*.cpp) $(wildcard $(STM32F4_SRC)/*.cpp)

OBJDIR = ./build/objs
OBJECTS_ASM = $(addprefix $(OBJDIR)/, $(notdir $(SOURCE_ASM:.S=.o)))
OBJECTS_C = $(addprefix $(OBJDIR)/, $(notdir $(SOURCE_C:.c=.o)))
OBJECTS_CPP = $(addprefix $(OBJDIR)/, $(notdir $(SOURCE_CPP:.cpp=.o)))

OUTDIR = ./build/output
ELFOUT = $(OUTDIR)/program.elf

CC = arm-none-eabi-gcc
CPP = arm-none-eabi-g++
LD = arm-none-eabi-gcc
AS = arm-none-eabi-gcc -x assembler-with-cpp

OPT = -mcpu=cortex-m4 -DTHUMB_PRESENT -mno-thumb-interwork -DTHUMB_NO_INTERWORKING -ffunction-sections -fdata-sections -fno-common -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -DCORTEX_USE_FPU=TRUE -O2 -ggdb -fomit-frame-pointer -falign-functions=16 $(addprefix -I, $(INCDIR))
OPT += -DSTM32F40_41xxx
ASMOPT = $(OPT) -mthumb
CXXOPT = $(OPT) -Wall -Wextra -Wundef -c
COPT = $(CXXOPT) -Wstrict-prototypes
CPPOPT = $(CXXOPT) -fno-rtti
LDOPT = -nostartfiles -Wl,--cref,--no-warn-mismatch,--gc-sections

VPATH = $(SRCDIR)

all : $(ELFOUT)

$(OBJECTS_ASM) : $(OBJDIR)/%.o : %.S Makefile
	@mkdir -p $(OBJDIR)
	$(AS) $(ASMOPT) -o $@ $<

$(OBJECTS_C) : $(OBJDIR)/%.o : %.c Makefile
	@mkdir -p $(OBJDIR)
	$(CC) $(COPT) -o $@ $<

$(OBJECTS_CPP) : $(OBJDIR)/%.o : %.cpp Makefile
	@mkdir -p $(OBJDIR)
	$(CPP) $(CPPOPT) -o $@ $<

$(ELFOUT) : $(OBJECTS_ASM) $(OBJECTS_C) $(OBJECTS_CPP)
	@mkdir -p $(OUTDIR)
	$(LD) $(LDOPT) -o $@ $<

clean:
	rm -rf $(OBJDIR)
	rm -rf $(OUTDIR)
