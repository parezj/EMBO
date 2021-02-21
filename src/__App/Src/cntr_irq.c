/*
 * CTU/EMBO - Embedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"

#include "FreeRTOS.h"
#include "semphr.h"

#include "app_data.h"
#include "main.h"


void EM_TIM_CNTR_UP_IRQh(void)
{
    if(LL_TIM_IsActiveFlag_UPDATE(EM_TIM_CNTR) == 1)
    {
        cntr.ovf++;
        EM_TIM_CNTR_OVF(LL_TIM_OC_SetCompare)(EM_TIM_CNTR, cntr.ovf);
    }
    LL_TIM_ClearFlag_UPDATE(EM_TIM_CNTR);
}
