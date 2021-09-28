/*
    FreeRTOS Kernel V10.4.3 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <cfg.h>

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, and not the assembler. */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif


#define configUSE_PREEMPTION                     1
#define configSUPPORT_STATIC_ALLOCATION          1
#define configSUPPORT_DYNAMIC_ALLOCATION         0
#define configCPU_CLOCK_HZ                       SystemCoreClock
#define configTICK_RATE_HZ                       ((TickType_t)1000)
#define configMAX_PRIORITIES                     ( 7 )
#define configMINIMAL_STACK_SIZE                 ((uint16_t)EM_STACK_MIN)
#define configTOTAL_HEAP_SIZE                    ((size_t)0)
#define configMAX_TASK_NAME_LEN                  ( 20 )
#define configUSE_16_BIT_TICKS                   0
#define configUSE_MUTEXES                        1
#define configQUEUE_REGISTRY_SIZE                8
#ifdef EM_CORTEX_M0
#define configUSE_PORT_OPTIMISED_TASK_SELECTION  0
#else
#define configUSE_PORT_OPTIMISED_TASK_SELECTION  1
#endif
#define configUSE_TIMERS                         0
#define configUSE_COUNTING_SEMAPHORES            0
#define configUSE_RECURSIVE_MUTEXES              0

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                    0
#define configMAX_CO_ROUTINE_PRIORITIES          ( 1 )

/* Hook function related definitions. */
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configCHECK_FOR_STACK_OVERFLOW          2
#define configUSE_MALLOC_FAILED_HOOK            0
#define configUSE_DAEMON_TASK_STARTUP_HOOK      0

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet            0
#define INCLUDE_uxTaskPriorityGet           0
#define INCLUDE_vTaskDelete                 0
#define INCLUDE_vTaskCleanUpResources       0
#define INCLUDE_vTaskSuspend                0
#define INCLUDE_vTaskDelayUntil             0
#define INCLUDE_vTaskDelay                  1
#define INCLUDE_xTaskGetSchedulerState      1
#define INCLUDE_xTaskGetIdleTaskHandle      1  /* System View */
#define INCLUDE_pxTaskGetStackStart         1  /* System View */

#ifdef EM_DEBUG
#define INCLUDE_uxTaskGetStackHighWaterMark 1
#endif

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if ((x) == 0) {taskDISABLE_INTERRUPTS(); for( ;; );}


#if defined(EM_CORTEX_M3) || defined(EM_CORTEX_M4F) || defined(EM_CORTEX_M7)

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
 /* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
 #define configPRIO_BITS         __NVIC_PRIO_BITS
#else
 #define configPRIO_BITS         4
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         15

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY         ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

#endif


/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
//#define vPortSVCHandler    SVC_Handler
//#define xPortPendSVHandler PendSV_Handler

/* IMPORTANT: This define MUST be commented when used with STM32Cube firmware, 
              to prevent overwriting SysTick_Handler defined within STM32Cube HAL */
/* #define xPortSysTickHandler SysTick_Handler */

/* USER CODE BEGIN Defines */   	      
/* Section where parameter definitions can be added (for instance, to override default ones in FreeRTOS.h) */
/* USER CODE END Defines */ 

#ifdef EM_SYSVIEW
#include "SEGGER_SYSVIEW_FreeRTOS.h"
#endif

#endif /* FREERTOS_CONFIG_H */
