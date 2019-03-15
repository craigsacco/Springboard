SET(stm32f4xx_stdperiph_library_root ${stm32f4xx_stdperiph_library_libroot}/1.8.0)

SET(hal_includes
    ${stm32f4xx_stdperiph_library_root}/inc
)

# common peripherals for all F4xx micros
SET(stm32f4xx_stdperiph_library_sources_hal
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_adc.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_crc.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_dbgmcu.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_dma.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_exti.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_flash.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_flash_ramfunc.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_gpio.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_i2c.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_iwdg.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_pwr.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_rcc.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_rtc.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_sdio.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_spi.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_syscfg.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_tim.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_usart.c
    ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_wwdg.c
    ${stm32f4xx_stdperiph_library_root}/src/misc.c
)

IF(${mcu_subfamily} STREQUAL "STM32F429_439xx")
    SET(stm32f4xx_stdperiph_library_sources_hal
        ${stm32f4xx_stdperiph_library_sources_hal}
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_can.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_cryp_aes.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_cryp.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_cryp_des.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_cryp_tdes.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_dac.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_dcmi.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_dma2d.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_fmc.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_hash.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_hash_md5.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_hash_sha1.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_ltdc.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_rng.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_sai.c
    )
ENDIF()

IF(${mcu_subfamily} STREQUAL "STM32F427_437xx")
    SET(stm32f4xx_stdperiph_library_sources_hal
        ${stm32f4xx_stdperiph_library_sources_hal}
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_can.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_cryp_aes.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_cryp.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_cryp_des.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_cryp_tdes.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_dac.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_dcmi.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_dma2d.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_fmc.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_hash.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_hash_md5.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_hash_sha1.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_rng.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_sai.c
    )
ENDIF()

IF(${mcu_subfamily} STREQUAL "STM32F427_437xx")
    SET(stm32f4xx_stdperiph_library_sources_hal
        ${stm32f4xx_stdperiph_library_sources_hal}
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_can.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_cryp_aes.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_cryp.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_cryp_des.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_cryp_tdes.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_dac.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_dcmi.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_fsmc.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_hash.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_hash_md5.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_hash_sha1.c
        ${stm32f4xx_stdperiph_library_root}/src/stm32f4xx_rng.c
    )
ENDIF()

SET(hal_sources
    ${stm32f4xx_stdperiph_library_sources_hal}
)
