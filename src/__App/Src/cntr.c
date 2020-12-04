/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"
#include "cntr.h"
#include "main.h"


void cntr_init(cntr_data_t* self)
{
    self->freq = 0;
    self->ovf = 0;
    self->enabled = 0;
    memset(self->data, 0, PS_CNTR_BUFF_SZ * sizeof(uint16_t));
    dma_set((uint32_t)&PS_TIM_CNTR->PS_TIM_CNTR_CCR, PS_DMA_CNTR, PS_DMA_CH_CNTR, (uint32_t)self->data, PS_CNTR_BUFF_SZ, LL_DMA_PDATAALIGN_HALFWORD);
}

void cntr_enable(cntr_data_t* self, uint8_t enable)
{
    if (enable)
    {
        LL_DMA_EnableChannel(PS_DMA_CNTR, PS_DMA_CH_CNTR);
        LL_TIM_EnableCounter(PS_TIM_CNTR);
        LL_TIM_CC_EnableChannel(PS_TIM_CNTR, PS_TIM_CNTR_CH);
    }
    else
    {
        LL_TIM_DisableCounter(PS_TIM_CNTR);
        LL_TIM_CC_DisableChannel(PS_TIM_CNTR, PS_TIM_CNTR_CH);
        //LL_DMA_DisableChannel(PS_DMA_CNTR, PS_DMA_CNTR);
    }
    self->enabled = enable;
}

float cntr_read(cntr_data_t* self)
{
    //cntr_enable(&self, 0);
    self->ovf = 0;
    int last1 = PS_DMA_LAST_IDX(PS_CNTR_BUFF_SZ, PS_DMA_CH_CNTR);
    cntr_enable(self, 1);
    int timeout = PS_FREQ_HCLK / 50; // TODO

    int diff = 0;
    int last2 = 0;
    uint32_t cc = 0;

    while (1)
    {
        cc = self->ovf;
        int last2 = PS_DMA_LAST_IDX(PS_CNTR_BUFF_SZ, PS_DMA_CH_CNTR);
        diff = last2 - last1;
        if (diff < 0)
            diff += PS_CNTR_BUFF_SZ;
        timeout--;
        if (diff >= 3 || timeout < 0)
            break;
    }

    cntr_enable(self, 0);

    if (diff >= 3)
    {
        int debug1 = self->data[last1];
        float total = (cc * PS_TIM_CNTR_MAX) + self->data[last2];
        if (diff > 3)
            total /= (((float)diff / 2.0) - 0.5); // too fast, 1 period normalize

        float f = total / (float)PS_TIM_CNTR_FREQ;
        return f;
    }
    else
    {
        return -1;
    }
}
