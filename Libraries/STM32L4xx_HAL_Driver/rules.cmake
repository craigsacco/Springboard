SET(stm32l4xx_hal_driver_root ${stm32l4xx_hal_driver_libroot}/1.9.0)

SET(hal_includes
    ${stm32l4xx_hal_driver_root}/Inc
)

FILE(GLOB stm32l4xx_hal_driver_sources_hal ${stm32l4xx_hal_driver_root}/Src/stm32l4xx_hal*.c)
FILE(GLOB stm32l4xx_hal_driver_sources_lld ${stm32l4xx_hal_driver_root}/Src/stm32l4xx_ll*.c)

SET(hal_sources
    ${stm32l4xx_hal_driver_sources_hal}
    ${stm32l4xx_hal_driver_sources_lld}
)
