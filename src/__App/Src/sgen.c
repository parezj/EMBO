/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include <string.h>

#include "cfg.h"
#include "sgen.h"
#include "main.h"
#include "periph.h"


#ifdef PS_DAC

void sgen_init(sgen_data_t* self)
{
    self->enabled = 0;
    memset(self->data, 0xFF, PS_DAC_BUFF_LEN * sizeof(uint16_t));
    dma_set((uint32_t)&self->data, PS_DMA_SGEN, PS_DMA_CH_SGEN,
            LL_DAC_DMA_GetRegAddr(PS_DAC, PS_DAC_CH, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED), PS_DAC_BUFF_LEN, // TODO LEN
            LL_DMA_PDATAALIGN_HALFWORD, LL_DMA_MDATAALIGN_HALFWORD, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
}

void sgen_enable(sgen_data_t* self, uint8_t enable)
{
    if (enable)
    {
        sgen_init(self);

        LL_DAC_EnableDMAReq(PS_DAC, PS_DAC_CH);
        LL_DAC_EnableTrigger(PS_DAC, PS_DAC_CH);
        LL_TIM_EnableCounter(PS_TIM_SGEN);
    }
    else
    {
        LL_TIM_DisableCounter(PS_TIM_SGEN);
        LL_DAC_DisableDMAReq(PS_DAC, PS_DAC_CH);
        LL_DAC_DisableTrigger(PS_DAC, PS_DAC_CH);
    }
    self->enabled = enable;
}

#endif
