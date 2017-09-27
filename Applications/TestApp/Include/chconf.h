/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    templates/chconf.h
 * @brief   Configuration file template.
 * @details A copy of this file must be placed in each project directory, it
 *          contains the application specific kernel settings.
 *
 * @addtogroup config
 * @details Kernel related settings and hooks.
 * @{
 */

#pragma once

#include <chconf-common.h>

/*===========================================================================*/
/**
 * @name Performance options
 * @{
 */
/*===========================================================================*/

/**
 * @brief   OS optimization.
 * @details If enabled then time efficient rather than space efficient code
 *          is used when two possible implementations exist.
 *
 * @note    This is not related to the compiler optimization options.
 * @note    The default is @p TRUE.
 */
#define CH_CFG_OPTIMIZE_SPEED               TRUE

/** @} */

/*===========================================================================*/
/**
 * @name Debug options
 * @{
 */
/*===========================================================================*/

/**
 * @brief   Debug option, kernel statistics.
 *
 * @note    The default is @p FALSE.
 */
#define CH_DBG_STATISTICS                   FALSE

/**
 * @brief   Debug option, system state check.
 * @details If enabled the correct call protocol for system APIs is checked
 *          at runtime.
 *
 * @note    The default is @p FALSE.
 */
#define CH_DBG_SYSTEM_STATE_CHECK           FALSE

/**
 * @brief   Debug option, parameters checks.
 * @details If enabled then the checks on the API functions input
 *          parameters are activated.
 *
 * @note    The default is @p FALSE.
 */
#define CH_DBG_ENABLE_CHECKS                FALSE

/**
 * @brief   Debug option, consistency checks.
 * @details If enabled then all the assertions in the kernel code are
 *          activated. This includes consistency checks inside the kernel,
 *          runtime anomalies and port-defined checks.
 *
 * @note    The default is @p FALSE.
 */
#define CH_DBG_ENABLE_ASSERTS               TRUE

/**
 * @brief   Debug option, trace buffer.
 * @details If enabled then the trace buffer is activated.
 *
 * @note    The default is @p CH_DBG_TRACE_MASK_DISABLED.
 */
#define CH_DBG_TRACE_MASK                   CH_DBG_TRACE_MASK_DISABLED

/**
 * @brief   Trace buffer entries.
 * @note    The trace buffer is only allocated if @p CH_DBG_TRACE_MASK is
 *          different from @p CH_DBG_TRACE_MASK_DISABLED.
 */
#define CH_DBG_TRACE_BUFFER_SIZE            128

/**
 * @brief   Debug option, stack checks.
 * @details If enabled then a runtime stack check is performed.
 *
 * @note    The default is @p FALSE.
 * @note    The stack check is performed in a architecture/port dependent way.
 *          It may not be implemented or some ports.
 * @note    The default failure mode is to halt the system with the global
 *          @p panic_msg variable set to @p NULL.
 */
#define CH_DBG_ENABLE_STACK_CHECK           TRUE

/**
 * @brief   Debug option, stacks initialization.
 * @details If enabled then the threads working area is filled with a byte
 *          value when a thread is created. This can be useful for the
 *          runtime measurement of the used stack.
 *
 * @note    The default is @p FALSE.
 */
#define CH_DBG_FILL_THREADS                 FALSE

/**
 * @brief   Debug option, threads profiling.
 * @details If enabled then a field is added to the @p thread_t structure that
 *          counts the system ticks occurred while executing the thread.
 *
 * @note    The default is @p FALSE.
 * @note    This debug option is not currently compatible with the
 *          tickless mode.
 */
#define CH_DBG_THREADS_PROFILING            FALSE

/** @} */
