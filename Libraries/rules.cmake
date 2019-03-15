INCLUDE(${project_path}/project.cmake)

PROJECT(${project_name} LANGUAGES C CXX ASM)

SET(stm32f4xx_stdperiph_library_libroot ./Libraries/STM32F4xx_StdPeriph_Library)
SET(stm32l4xx_hal_driver_libroot ./Libraries/STM32L4xx_HAL_Driver)
SET(cmsis_libroot ./Libraries/CMSIS)
SET(cmsis_stm32f4xx_libroot ./Libraries/CMSIS_STM32F4xx)
SET(cmsis_stm32l4xx_libroot ./Libraries/CMSIS_STM32L4xx)

GET_FILENAME_COMPONENT(ldscript_root ./Libraries/LinkerScripts ABSOLUTE .)

IF(${project_mcu} MATCHES "^STM32F4")
    INCLUDE(./Libraries/rules_stm32f4xx.cmake)
ELSEIF(${project_mcu} MATCHES "^STM32L4")
    INCLUDE(./Libraries/rules_stm32l4xx.cmake)
ELSE()
    MESSAGE(FATAL_ERROR "Unsupported MCU type: ${project_mcu}")
ENDIF()

SET(freertos_libroot ./Libraries/FreeRTOS)

INCLUDE(${freertos_libroot}/rules.cmake)
INCLUDE(${hal_driver_libroot}/rules.cmake)
INCLUDE(${cmsis_libroot}/rules.cmake)
INCLUDE(${cmsis_device_libroot}/rules.cmake)

SET(flags_common "-O0 -ggdb -fomit-frame-pointer -falign-functions=16 -ffunction-sections -fdata-sections -fno-common -flto ${flags_common_mcu}")
SET(flags_asm "-x assembler-with-cpp ${flags_common}")
SET(flags_c "${flags_common} -std=c11 -Wall -Wextra -Wundef -Wstrict-prototypes")
SET(flags_cpp "${flags_common} -std=c++17 -fno-rtti -Wall -Wextra -Wundef")
SET(flags_link "--specs=nosys.specs -Wl,--no-warn-mismatch,--library-path=${ldscript_root},--Map=${CMAKE_BINARY_DIR}/${project_name}.map,--script=${ldscript_file},--gc-sections")

SET(CMAKE_ASM_FLAGS ${flags_asm})
SET(CMAKE_C_FLAGS ${flags_c})
SET(CMAKE_CXX_FLAGS ${flags_cpp})
SET(CMAKE_EXE_LINKER_FLAGS ${flags_link})

SET(arm_toolchain_path /home/craig/Applications/gcc-arm-embedded/7-2018-q2-update)
SET(CMAKE_ASM_COMPILER ${arm_toolchain_path}/bin/arm-none-eabi-gcc)
SET(CMAKE_C_COMPILER ${arm_toolchain_path}/bin/arm-none-eabi-gcc)
SET(CMAKE_CXX_COMPILER ${arm_toolchain_path}/bin/arm-none-eabi-g++)
SET(CMAKE_C_LINK_EXECUTABLE ${arm_toolchain_path}/bin/arm-none-eabi-gcc)

FILE(GLOB project_sources_asm ${project_path}/*.s)
FILE(GLOB project_sources_c ${project_path}/*.c)
FILE(GLOB project_sources_cpp ${project_path}/*.cpp)
SET(project_sources ${project_sources_asm} ${project_sources_c} ${project_sources_cpp})
SET(project_includes ${project_path})

SET(springboard_root ./Libraries/Springboard)
SET(springboard_includes ${springboard_root}/Include)
FILE(GLOB_RECURSE springboard_sources ${springboard_root}/Source/*.cpp)

INCLUDE_DIRECTORIES(
    ${project_includes}
    ${freertos_includes}
    ${hal_includes}
    ${cmsis_includes}
    ${cmsis_device_includes}
    ${springboard_includes})

ADD_EXECUTABLE(${project_name}.elf
    ${project_sources}
    ${freertos_sources}
    ${hal_sources}
    ${cmsis_sources}
    ${cmsis_device_sources}
    ${springboard_sources})

ADD_CUSTOM_COMMAND(
    TARGET ${project_name}.elf
    POST_BUILD
    BYPRODUCTS ${project_name}.bin
    COMMAND ${arm_toolchain_path}/bin/arm-none-eabi-objcopy -O binary ${project_name}.elf ${project_name}.bin
    COMMENT "Generating firmware binary ${project_name}.bin")

ADD_CUSTOM_COMMAND(
    TARGET ${project_name}.elf
    POST_BUILD
    BYPRODUCTS ${project_name}.lst
    COMMAND ${arm_toolchain_path}/bin/arm-none-eabi-objdump -S ${project_name}.elf > ${project_name}.lst
    COMMENT "Generating assembly listing ${project_name}.lst")

SET_PROPERTY(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${project_name}.bin ${project_name}.lst ${project_name}.map)

ADD_CUSTOM_TARGET(flash_write COMMAND st-flash write ${project_name}.bin 0x08000000)
ADD_CUSTOM_TARGET(flash_erase COMMAND st-flash erase)
