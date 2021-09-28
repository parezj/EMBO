/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"

#include "app_data.h"
#include "main.h"

#include "FreeRTOS.h"
#include "semphr.h"


/* counter overflow bit - software extended counter resolution */
void EM_TIM_CNTR_UP_IRQh(void)
{
    traceISR_ENTER();

    if(LL_TIM_IsActiveFlag_UPDATE(EM_TIM_CNTR) == 1)
    {
        em_cntr.ovf++;
        EM_TIM_CNTR_OVF(LL_TIM_OC_SetCompare)(EM_TIM_CNTR, em_cntr.ovf);
    }
    LL_TIM_ClearFlag_UPDATE(EM_TIM_CNTR);

    traceISR_EXIT();
}
