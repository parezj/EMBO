/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include <string.h>

#include "cfg.h"
#include "cntr.h"
#include "main.h"
#include "periph.h"


void cntr_init(cntr_data_t* self)
{
    self->freq = 0;
    self->ovf = 0;
    self->enabled = 0;
    self->data_ovf_it = 0;
    memset(self->data_ccr, 0, PS_CNTR_BUFF_SZ * sizeof(uint16_t));
    memset(self->data_ovf, 0, PS_CNTR_BUFF_SZ * sizeof(uint16_t));
    dma_set((uint32_t)&PS_TIM_CNTR->PS_TIM_CNTR_CCR, PS_DMA_CNTR, PS_DMA_CH_CNTR, (uint32_t)&self->data_ccr, PS_CNTR_BUFF_SZ,
            LL_DMA_PDATAALIGN_HALFWORD, LL_DMA_MDATAALIGN_HALFWORD, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

    NVIC_SetPriority(TIM1_UP_TIM16_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1, 0));
    NVIC_SetPriority(TIM1_CC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1, 0));
    PS_TIM_CNTR_CC(LL_TIM_EnableIT_)(PS_TIM_CNTR);
    LL_TIM_EnableIT_UPDATE(PS_TIM_CNTR);
}

void cntr_enable(cntr_data_t* self, uint8_t enable)
{
    if (enable)
    {
        cntr_init(self);

        PS_TIM_CNTR_CC(LL_TIM_EnableDMAReq_)(PS_TIM_CNTR);
        NVIC_EnableIRQ(TIM1_CC_IRQn);
        NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
        LL_TIM_EnableCounter(PS_TIM_CNTR);
        LL_TIM_CC_EnableChannel(PS_TIM_CNTR, PS_TIM_CNTR_CH);
    }
    else
    {
        LL_TIM_DisableCounter(PS_TIM_CNTR);
        LL_TIM_CC_DisableChannel(PS_TIM_CNTR, PS_TIM_CNTR_CH);
        NVIC_DisableIRQ(TIM1_CC_IRQn);
        NVIC_DisableIRQ(TIM1_UP_TIM16_IRQn);
        PS_TIM_CNTR_CC(LL_TIM_DisableDMAReq_)(PS_TIM_CNTR);
    }
    self->enabled = enable;
}

float cntr_read(cntr_data_t* self, daq_data_t* daq)
{
    int uwTick_start = daq->uwTick;
    int sz = 0;

    cntr_enable(self, 1);

    while (1)
    {
        sz = LL_DMA_GetDataLength(PS_DMA_CNTR, PS_DMA_CH_CNTR);

        uint32_t timeout = daq->uwTick - uwTick_start;
        if (timeout < 0)
            timeout += PS_UWTICK_MAX;

        if (timeout > PS_CNTR_MEAS_MS || sz == 0)
            break;
    }

    cntr_enable(self, 0);

    sz = PS_CNTR_BUFF_SZ - sz;

    if (sz >= 2)
    {
        uint32_t ovf = 0;
        uint32_t ccr_sum = 0;

        if (self->data_ovf_it > 1)
            ovf = self->data_ovf[self->data_ovf_it - 1] - self->data_ovf[0] - 1;

        if (self->data_ovf_it > 0)
            ccr_sum += (PS_TIM_CNTR_MAX - self->data_ccr[0]) + self->data_ccr[sz - 1];
        else
            ccr_sum += self->data_ccr[sz - 1] - self->data_ccr[0];

        float total = (ovf * PS_TIM_CNTR_MAX) + ccr_sum;
        total /= (float)(sz - 1);
        float f = (float)PS_TIM_CNTR_FREQ / total;
        self->freq = f;
        return f;
    }
    else
    {
        return -1; // timeout
    }
}