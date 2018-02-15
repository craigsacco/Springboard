
project(${PROJECT_NAME} C CXX ASM)

include (../../Libraries/ChibiOS/ChibiOS.cmake)

set (CMAKE_C_COMPILER "arm-none-eabi-gcc")
set (CMAKE_CXX_COMPILER "arm-none-eabi-g++")
set (CMAKE_ASM_COMPILER "arm-none-eabi-gcc")
set (CMAKE_LINKER "arm-none-eabi-gcc")

set (CMAKE_COMMON_FLAGS "-DTHUMB -mno-thumb-interwork -DTHUMB_NO_INTERWORKING -mcpu=cortex-m4")
set (CMAKE_COMMON_C_FLAGS "${CMAKE_COMMON_FLAGS} -Wall -Wextra -Wundef -ffunction-sections -fdata-sections -fno-common")

set (CMAKE_C_FLAGS "${CMAKE_COMMON_C_FLAGS} -Wstrict-prototypes")
set (CMAKE_CXX_FLAGS "${CMAKE_COMMON_C_FLAGS}")
set (CMAKE_C_LINK_FLAGS "-nostartfiles -Wl,--cref,--no-warn-mismatch,--gc-sections,--library-path=${CHIBIOS_BASE_STARTUP}/compilers/GCC/ld,--script=${CHIBIOS_BASE_STARTUP}/compilers/GCC/ld/STM32F407xG.ld,--defsym=__process_stack_size__=0x400,--defsym=__main_stack_size__=0x400")
set (CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
set (CMAKE_ASM_FLAGS "-x assembler-with-cpp ${CMAKE_COMMON_FLAGS} -mthumb")

include_directories (.)

file (GLOB PROJECT_SOURCE_C ./*.c)

set (PROJECT_SOURCE ${PROJECT_SOURCE_C})

add_executable (${PROJECT_NAME}.elf ${CHIBIOS_SOURCE} ${PROJECT_SOURCE})
