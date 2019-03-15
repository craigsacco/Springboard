SET(hal_driver_libroot ${stm32f4xx_stdperiph_library_libroot})
SET(cmsis_device_libroot ${cmsis_stm32f4xx_libroot})
SET(freertos_port ARM_CM4F)
SET(mcu_family STM32F4)
SET(flags_common_mcu "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -DUSE_STDPERIPH_DRIVER -D__MCU_FAMILY__=${mcu_family}")

IF(${project_mcu} MATCHES "^STM32F4[01]7xG$")
    # chip is an F407xG or F417xG
    SET(ldscript_file ${ldscript_root}/STM32F407xG_FLASH.ld)
    SET(mcu_subfamily STM32F40_41xxx)
    SET(springboard_startup_source ${springboard_root}/Startup/startup_stm32f40_41xxx.s)
ELSEIF(${project_mcu} MATCHES "^STM32F4[23]9xI$")
    # chip is an F429xI or F439xG
    SET(ldscript_file ${ldscript_root}/STM32F429xI_FLASH.ld)
    SET(mcu_subfamily STM32F429_439xx)
    SET(springboard_startup_source ${springboard_root}/Startup/startup_stm32f429_439xx.s)
ELSE()
    MESSAGE(FATAL_ERROR "Unsupported MCU type: ${project_mcu}")
ENDIF()

SET(flags_common_mcu "${flags_common_mcu} -D${mcu_subfamily} -D__MCU_SUBFAMILY__=${mcu_subfamily}")
