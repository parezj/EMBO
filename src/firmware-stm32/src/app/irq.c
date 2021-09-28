/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"

#include "app_data.h"
#include "app_sync.h"
#include "main.h"

#include "FreeRTOS.h"
#include "semphr.h"


void SysTick_Handler(void)
{
    if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
        xPortSysTickHandler();
    #ifdef EM_HAL_SYSTICK
        HAL_IncTick();
    #endif
    em_daq.uwTick++;
}

void SVC_Handler(void)
{
    vPortSVCHandler();
}

void PendSV_Handler(void)
{
    xPortPendSVHandler();
}

