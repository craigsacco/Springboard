SET(hal_driver_libroot ${stm32l4xx_hal_driver_libroot})
SET(cmsis_device_libroot ${cmsis_stm32l4xx_libroot})
SET(freertos_port ARM_CM4F)
SET(mcu_family STM32L4)
SET(flags_common_mcu "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MCU_FAMILY__=${mcu_family}")

IF(${project_mcu} STREQUAL "STM32L432xC")
    # chip is an L432xC
    SET(ldscript_file ${ldscript_root}/STM32L432xC_FLASH.ld)
    SET(mcu_subfamily STM32L432xx)
    SET(springboard_startup_source ${springboard_root}/Startup/startup_stm32l432xx.s)
ELSE()
    MESSAGE(FATAL_ERROR "Unsupported MCU type: ${project_mcu}")
ENDIF()

SET(flags_common_mcu "${flags_common_mcu} -D${mcu_subfamily} -D__MCU_SUBFAMILY__=${mcu_subfamily}")
