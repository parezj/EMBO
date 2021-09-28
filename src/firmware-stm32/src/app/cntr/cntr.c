/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cntr.h"

#include "app_sync.h"
#include "main.h"
#include "periph/periph_dma.h"

#include "FreeRTOS.h"

#include <string.h>

#ifndef EMBO
    #define EM_TRUE                1
    #define EM_FALSE               0
    #define EM_IT_PRI_CNTR         4   // overflow bit
    #define EM_CNTR_IRQ            TIM1_UP_TIM16_IRQn
    #define EM_TIM_CNTR            TIM1
    #define EM_TIM_CNTR_FREQ       EM_FREQ_PCLK2
    #define EM_TIM_CNTR_UP_IRQh    TIM1_UP_TIM16_IRQHandler
    #define EM_TIM_CNTR_MAX        65535
    #define EM_TIM_CNTR_CH         LL_TIM_CHANNEL_CH1 // direct input capture - channel
    #define EM_TIM_CNTR_CH2        LL_TIM_CHANNEL_CH2 // indirect input capture - channel
    #define EM_TIM_CNTR_CCR        CCR1   // direct input capture - ccr register
    #define EM_TIM_CNTR_CCR2       CCR3   // ovf store - ccr register
    #define EM_TIM_CNTR_CC(a)      a##CC1 // direct input capture - cc name
    #define EM_TIM_CNTR_CC2(a)     a##CC2 // indirect input capture - cc name
    #define EM_TIM_CNTR_OVF(a)     a##CH3 // ovf store
    #define EM_TIM_CNTR_PSC_FAST   8      // prescaler for fast mode
    #define EM_DMA_CNTR            DMA1
    #define EM_DMA_CNTR2           DMA1
    #define EM_DMA_CH_CNTR         LL_DMA_CHANNEL_2
    #define EM_DMA_CH_CNTR2        LL_DMA_CHANNEL_3
#endif

static void cntr_reset(cntr_data_t* self);


void cntr_init(cntr_data_t* self)
{
    self->freq = -1;
    self->enabled = EM_FALSE;
    self->fast_mode = EM_FALSE;
    self->fast_mode_now = 0;

    NVIC_SetPriority(EM_CNTR_IRQ, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), EM_IT_PRI_CNTR, 0));
    //cntr_reset(self); REMOVED 29.5.21
}

static void cntr_reset(cntr_data_t* self)
{
    self->ovf = 0;
    self->fast_mode_now = self->fast_mode == EM_TRUE;

    memset(self->data_ccr, 0, EM_CNTR_BUFF_SZ * sizeof(uint16_t));
    memset(self->data_ovf, 0, EM_CNTR_BUFF_SZ * sizeof(uint16_t));

    dma_set((uint32_t)&EM_TIM_CNTR->EM_TIM_CNTR_CCR, EM_DMA_CNTR, EM_DMA_CH_CNTR, (uint32_t)&self->data_ccr,
            self->fast_mode_now ? EM_CNTR_BUFF_SZ : EM_CNTR_BUFF_SZ2,
            LL_DMA_PDATAALIGN_HALFWORD, LL_DMA_MDATAALIGN_HALFWORD, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

    dma_set((uint32_t)&EM_TIM_CNTR->EM_TIM_CNTR_CCR2, EM_DMA_CNTR2, EM_DMA_CH_CNTR2, (uint32_t)&self->data_ovf,
            self->fast_mode_now ? EM_CNTR_BUFF_SZ : EM_CNTR_BUFF_SZ2,
            LL_DMA_PDATAALIGN_HALFWORD, LL_DMA_MDATAALIGN_HALFWORD, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

    LL_TIM_EnableIT_UPDATE(EM_TIM_CNTR);
    EM_TIM_CNTR_OVF(LL_TIM_OC_SetCompare)(EM_TIM_CNTR, 0);
    LL_TIM_SetCounter(EM_TIM_CNTR, 0);

    LL_TIM_IC_SetPrescaler(EM_TIM_CNTR, EM_TIM_CNTR_CH, self->fast_mode_now ? LL_TIM_ICPSC_DIV8 : LL_TIM_ICPSC_DIV1);
    LL_TIM_IC_SetPrescaler(EM_TIM_CNTR, EM_TIM_CNTR_CH2, self->fast_mode_now ? LL_TIM_ICPSC_DIV8 : LL_TIM_ICPSC_DIV1);
}

void cntr_enable(cntr_data_t* self, uint8_t enable, uint8_t fast_mode)
{
    uint8_t en = self->enabled;
    self->enabled = enable;
    self->fast_mode = fast_mode;

    if (en == EM_FALSE && enable == EM_TRUE)
        self->freq = -1;

    if (enable == EM_TRUE && en == EM_FALSE)
        xSemaphoreGive(sem3_cntr);
    else if (enable == EM_FALSE && en == EM_TRUE)
        xSemaphoreTake(sem3_cntr, 0);

    if (enable == EM_FALSE) // ADDED 29.5.21
    {
        LL_DMA_DisableChannel(EM_DMA_CNTR, EM_DMA_CH_CNTR);
        LL_DMA_DisableChannel(EM_DMA_CNTR, EM_DMA_CH_CNTR2);
    }
}

void cntr_start(cntr_data_t* self, uint8_t start)
{
    if (start) // start counter
    {
        cntr_reset(self);

        EM_TIM_CNTR_CC(LL_TIM_EnableDMAReq_)(EM_TIM_CNTR);
        EM_TIM_CNTR_CC2(LL_TIM_EnableDMAReq_)(EM_TIM_CNTR);
        NVIC_EnableIRQ(EM_CNTR_IRQ);
        LL_TIM_CC_EnableChannel(EM_TIM_CNTR, EM_TIM_CNTR_CH);
        LL_TIM_CC_EnableChannel(EM_TIM_CNTR, EM_TIM_CNTR_CH2);
        LL_TIM_EnableCounter(EM_TIM_CNTR);
    }
    else // stop counter
    {
        LL_TIM_DisableCounter(EM_TIM_CNTR);
        LL_TIM_CC_DisableChannel(EM_TIM_CNTR, EM_TIM_CNTR_CH);
        LL_TIM_CC_DisableChannel(EM_TIM_CNTR, EM_TIM_CNTR_CH2);
        NVIC_DisableIRQ(EM_CNTR_IRQ);
        EM_TIM_CNTR_CC(LL_TIM_DisableDMAReq_)(EM_TIM_CNTR);
        EM_TIM_CNTR_CC2(LL_TIM_DisableDMAReq_)(EM_TIM_CNTR);
    }
}

void cntr_meas(cntr_data_t* self)
{
    int pre_timeout = 0;
    int cntr_timeout = 0;
    uint32_t sz = 0;

    cntr_start(self, 1); // start

    while (1) // wait DMA fill buffer or timeout
    {
        sz = LL_DMA_GetDataLength(EM_DMA_CNTR, EM_DMA_CH_CNTR);

        if (pre_timeout > 1000)
        {
            vTaskDelay(EM_CNTR_INT_DELAY);
            cntr_timeout += EM_CNTR_INT_DELAY;
        }

        pre_timeout++;

        if (cntr_timeout > EM_CNTR_MEAS_MS || sz == 0)
            break;
    }

    cntr_start(self, 0); // stop

    sz = (self->fast_mode_now ? EM_CNTR_BUFF_SZ : EM_CNTR_BUFF_SZ2) - sz; // get data size

    if (sz >= 2)
    {
        uint16_t ovf = 0;
        uint32_t ccr_sum = 0;

        ovf = self->data_ovf[sz - 1] - self->data_ovf[0];

        if (ovf > 0) // prepare overflow bit values
        {
            ccr_sum += (EM_TIM_CNTR_MAX - self->data_ccr[0]) + self->data_ccr[sz - 1];
            ovf -= 1;
        }
        else
        {
            if (self->data_ccr[sz - 1] > self->data_ccr[0])
                ccr_sum += self->data_ccr[sz - 1] - self->data_ccr[0];
            else
                return;
        }

        /* finally calc freq */
        double total = (ovf * EM_TIM_CNTR_MAX) + ccr_sum;
        total /= (double)(sz - 1);
        self->freq = ((double)EM_TIM_CNTR_FREQ / total) * (double)(self->fast_mode_now ? 8 : 1);
    }
    else
    {
        self->freq = -1; // timeout
    }
}
