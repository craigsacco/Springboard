
set (CHIBIOS_BASE ../../Libraries/ChibiOS)
set (CHIBIOS_VERSION 17.6.x)

set (CHIBIOS_BASE_HAL ${CHIBIOS_BASE}/${CHIBIOS_VERSION}/os/hal)
set (CHIBIOS_BASE_OSAL ${CHIBIOS_BASE}/${CHIBIOS_VERSION}/os/hal/osal/rt)
set (CHIBIOS_BASE_STREAMS ${CHIBIOS_BASE}/${CHIBIOS_VERSION}/os/hal/lib/streams)
set (CHIBIOS_BASE_RT ${CHIBIOS_BASE}/${CHIBIOS_VERSION}/os/rt)
set (CHIBIOS_BASE_OSLIB ${CHIBIOS_BASE}/${CHIBIOS_VERSION}/os/common/oslib)
set (CHIBIOS_BASE_LICENSE ${CHIBIOS_BASE}/${CHIBIOS_VERSION}/os/license)
set (CHIBIOS_BASE_STARTUP ${CHIBIOS_BASE}/${CHIBIOS_VERSION}/os/common/startup/ARMCMx)
set (CHIBIOS_BASE_CMSIS ${CHIBIOS_BASE}/${CHIBIOS_VERSION}/os/common/ext/CMSIS)
set (CHIBIOS_BASE_PORTS ${CHIBIOS_BASE}/${CHIBIOS_VERSION}/os/hal/ports)
set (CHIBIOS_BASE_CORE ${CHIBIOS_BASE}/${CHIBIOS_VERSION}/os/common/ports/ARMCMx)

include_directories (${CHIBIOS_BASE_HAL}/include)
include_directories (${CHIBIOS_BASE_OSAL})
include_directories (${CHIBIOS_BASE_STREAMS})
include_directories (${CHIBIOS_BASE_RT}/include)
include_directories (${CHIBIOS_BASE_OSLIB}/include)
include_directories (${CHIBIOS_BASE_LICENSE})
include_directories (${CHIBIOS_BASE_STARTUP}/compilers/GCC)
include_directories (${CHIBIOS_BASE_STARTUP}/devices/STM32F4xx)
include_directories (${CHIBIOS_BASE_CMSIS}/include)
include_directories (${CHIBIOS_BASE_CMSIS}/ST/STM32F4xx)
include_directories (${CHIBIOS_BASE_PORTS}/common/ARMCMx)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/STM32F4xx)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/ADCv2)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/CANv1)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/DACv1)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/DMAv2)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/EXTIv1)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/GPIOv2)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/I2Cv1)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/MACv1)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/OTGv1)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/QUADSPIv1)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/RTCv2)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/SPIv1)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/SDIOv1)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/TIMv1)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/USARTv1)
include_directories (${CHIBIOS_BASE_PORTS}/STM32/LLD/xWDGv1)
include_directories (${CHIBIOS_BASE_CORE})
include_directories (${CHIBIOS_BASE_CORE}/compilers/GCC)

file (GLOB CHIBIOS_SOURCE_C ${CHIBIOS_BASE_HAL}/src/*.c
                            ${CHIBIOS_BASE_OSAL}/*.c
                            ${CHIBIOS_BASE_STREAMS}/*.c
                            ${CHIBIOS_BASE_RT}/src/*.c
                            ${CHIBIOS_BASE_OSLIB}/src/*.c
                            ${CHIBIOS_BASE_STARTUP}/compilers/GCC/crt1.c
                            ${CHIBIOS_BASE_STARTUP}/compilers/GCC/vectors.c
                            ${CHIBIOS_BASE_PORTS}/common/ARMCMx/nvic.c
                            ${CHIBIOS_BASE_PORTS}/STM32/STM32F4xx/hal_lld.c
                            ${CHIBIOS_BASE_PORTS}/STM32/STM32F4xx/hal_ext_lld_isr.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/ADCv2/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/CANv1/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/DACv1/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/DMAv2/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/EXTIv1/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/GPIOv2/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/I2Cv1/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/MACv1/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/OTGv1/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/QUADSPIv1/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/RTCv2/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/SPIv1/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/SDIOv1/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/TIMv1/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/USARTv1/*.c
                            ${CHIBIOS_BASE_PORTS}/STM32/LLD/xWDGv1/*.c
                            ${CHIBIOS_BASE_CORE}/chcore.c
                            ${CHIBIOS_BASE_CORE}/chcore_v7m.c)
file (GLOB CHIBIOS_SOURCE_ASM ${CHIBIOS_BASE_STARTUP}/compilers/GCC/crt0_v7m.S
                              ${CHIBIOS_BASE_CORE}/compilers/GCC/chcoreasm_v7m.S)

set (CHIBIOS_SOURCE ${CHIBIOS_SOURCE_C} ${CHIBIOS_SOURCE_ASM})
