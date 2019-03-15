SET(freertos_root ${freertos_libroot}/10.2.0)
SET(freertos_portdir ${freertos_root}/portable/GCC/${freertos_port})
SET(freertos_heapdir ${freertos_root}/portable/MemMang)

SET(freertos_includes
    ${freertos_root}/include
    ${freertos_portdir}
)

FILE(GLOB freertos_sources_rtos ${freertos_root}/*.c)

SET(freertos_sources
    ${freertos_sources_rtos}
    ${freertos_portdir}/port.c
    ${freertos_heapdir}/heap_1.c
)
