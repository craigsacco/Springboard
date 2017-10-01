/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

//! \section using ChibiOS/RT
#define _CHIBIOS_RT_CONF_

//! \section mandatory timer settings
#define CH_CFG_ST_RESOLUTION                32
#define CH_CFG_ST_FREQUENCY                 1000
#define CH_CFG_ST_TIMEDELTA                 0

//! \section mandatory kernel settings
#define CH_CFG_TIME_QUANTUM                 0
#define CH_CFG_MEMCORE_SIZE                 0
#define CH_CFG_NO_IDLE_THREAD               FALSE

//! \section mandatory kernel features
#define CH_CFG_USE_TM                       TRUE
#define CH_CFG_USE_REGISTRY                 TRUE
#define CH_CFG_USE_WAITEXIT                 TRUE
#define CH_CFG_USE_SEMAPHORES               TRUE
#define CH_CFG_USE_SEMAPHORES_PRIORITY      FALSE
#define CH_CFG_USE_MUTEXES                  TRUE
#define CH_CFG_USE_MUTEXES_RECURSIVE        FALSE
#define CH_CFG_USE_CONDVARS                 TRUE
#define CH_CFG_USE_CONDVARS_TIMEOUT         TRUE
#define CH_CFG_USE_EVENTS                   TRUE
#define CH_CFG_USE_EVENTS_TIMEOUT           TRUE
#define CH_CFG_USE_MESSAGES                 TRUE
#define CH_CFG_USE_MESSAGES_PRIORITY        FALSE
#define CH_CFG_USE_MAILBOXES                TRUE
#define CH_CFG_USE_MEMCORE                  TRUE
#define CH_CFG_USE_HEAP                     TRUE
#define CH_CFG_USE_MEMPOOLS                 FALSE
#define CH_CFG_USE_DYNAMIC                  TRUE

//! \section mandatory debug options

#define CH_DBG_SYSTEM_STATE_CHECK           TRUE
#define CH_DBG_ENABLE_CHECKS                TRUE
#define CH_DBG_ENABLE_ASSERTS               TRUE
#define CH_DBG_ENABLE_STACK_CHECK           TRUE
#define CH_DBG_FILL_THREADS                 TRUE

//! \section extern declarations for kernel hooks
//! \note need to hide it from the assembler

#ifndef _FROM_ASM_
#ifdef __cplusplus
extern "C" {
#endif
extern void HandleCrashFA(const char* reason);
#ifdef __cplusplus
}
#endif
#endif

//! \section mandatory kernel hooks

#define CH_CFG_THREAD_EXTRA_FIELDS                                          \
    /* Add threads custom fields here.*/
#define CH_CFG_THREAD_INIT_HOOK(tp) {                                       \
    /* Add threads initialization code here.*/                              \
}
#define CH_CFG_THREAD_EXIT_HOOK(tp) {                                       \
    /* Add threads finalization code here.*/                                \
}
#define CH_CFG_CONTEXT_SWITCH_HOOK(ntp, otp) {                              \
    /* Context switch code here.*/                                          \
}
#define CH_CFG_IRQ_PROLOGUE_HOOK() {                                        \
    /* IRQ prologue code here.*/                                            \
}
#define CH_CFG_IRQ_EPILOGUE_HOOK() {                                        \
    /* IRQ epilogue code here.*/                                            \
}
#define CH_CFG_IDLE_ENTER_HOOK() {                                          \
    /* Idle-enter code here.*/                                              \
}
#define CH_CFG_IDLE_LEAVE_HOOK() {                                          \
    /* Idle-leave code here.*/                                              \
}
#define CH_CFG_IDLE_LOOP_HOOK() {                                           \
    /* Idle loop code here.*/                                               \
}
#define CH_CFG_SYSTEM_TICK_HOOK() {                                         \
    /* System tick event code here.*/                                       \
}
#define CH_CFG_SYSTEM_HALT_HOOK(reason) {                                   \
    HandleCrashFA(reason);                                                  \
}
#define CH_CFG_TRACE_HOOK(tep) {                                            \
    /* Trace code here.*/                                                   \
}

//! \section port options
#define PORT_ENABLE_GUARD_PAGES             TRUE
