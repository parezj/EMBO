/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"
#include "daq.h"
#include "daq_trig.h"

#include "app_sync.h"
#include "comm.h"
#include "main.h"
#include "periph.h"
#include "utility.h"

#include "FreeRTOS.h"
#include "semphr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void daq_trig_init(daq_data_t* self)
{
    self->trig.ignore = EM_FALSE;
    self->trig.ready = EM_FALSE;
    self->trig.cntr = 0;
    self->trig.awd_trig = 0;
    self->trig.all_cntr = 0;
    self->trig.pos_frst = 0;
    self->trig.pos_trig = 0;
    self->trig.pos_last = 0;
    self->trig.pos_diff = 0;
    self->trig.uwtick_first = 0;
    self->trig.pretrig_cntr = 0;
    self->trig.is_post = EM_FALSE;
    self->trig.posttrig_size = 0;
    self->trig.auttrig_val = 0;
    self->trig.pretrig_val = 0;
    self->trig.fullmem_val = 0;
    self->trig.buff_trig = NULL;
    self->trig.dma_ch_trig = EM_DMA_CH_ADC1;
    self->trig.exti_trig = EM_LA_IRQ_EXTI1;
    self->trig.adc_trig = ADC1;
    self->trig.dma_trig = EM_DMA_ADC1;
    self->trig.order = 0;
    self->trig.ready_last = EM_FALSE;
    self->trig.post_start = EM_FALSE;
    self->trig.post_from = 0;
    self->trig.dma_pos_catched = 0;
    self->trig.forced = EM_FALSE;
    self->trig.respond = EM_FALSE;
}

void daq_trig_check(daq_data_t* self)
{
    char t_resp = '0';

    if (self->enabled == EM_TRUE) // check pre trigger
    {
        self->trig.pretrig_cntr = self->uwTick - self->trig.uwtick_first;
        if (self->trig.pretrig_cntr < 0)
            self->trig.pretrig_cntr += EM_UWTICK_MAX;

        if (self->trig.pretrig_cntr > self->trig.pretrig_val && self->trig.set.mode != DISABLED)
        {
            if (self->mode == SCOPE)
            {
                ASSERT(self->trig.awd_trig != 0);
                LL_ADC_SetAnalogWDMonitChannels(self->trig.adc_trig, EM_ADC_AWD self->trig.awd_trig);
            }
        }
    }
    else
    {
        self->trig.pretrig_cntr = 0;
    }

    if (self->mode != VM) // check auto trigger
    {
        if (self->enabled == EM_TRUE &&
            self->trig.set.mode == AUTO &&
            self->trig.is_post == EM_FALSE &&
            self->trig.ready == EM_FALSE &&
            self->trig.pretrig_cntr > self->trig.auttrig_val)
        {
            daq_enable(self, EM_FALSE);
            self->trig.pos_frst = EM_DMA_LAST_IDX(self->trig.buff_trig->len, self->trig.dma_ch_trig, self->trig.dma_trig);

            self->trig.ready = EM_TRUE;
            self->trig.is_post = EM_FALSE;

            t_resp = 'A';
            self->trig.respond = EM_TRUE; // init async respond ReadyX
        }
        else if (self->trig.set.mode == DISABLED &&  // trigger is disabled
                 self->trig.pretrig_cntr > self->trig.fullmem_val)
        {
            self->trig.ready = EM_TRUE;
            if (self->trig.ready_last == EM_FALSE)
            {
                daq_enable(self, EM_FALSE);
                self->trig.pos_frst = EM_DMA_LAST_IDX(self->trig.buff_trig->len, self->trig.dma_ch_trig, self->trig.dma_trig);

                t_resp = 'D';
                self->trig.respond = EM_TRUE; // init async respond ReadyX
            }
        }
    }
    self->trig.ready_last = self->trig.ready;

    if (self->trig.respond == EM_TRUE) // // check async respond ReadyX
    {
        const char* resp;

        if (t_resp == 'A')
            resp = EM_RESP_RDY_A;       // data ready - trig auto
        else if (t_resp == 'D')
            resp = EM_RESP_RDY_D;       // data ready - trig disabled
        else
        {
            if (self->trig.forced == EM_TRUE)
                resp = EM_RESP_RDY_F;   // data ready - trig forced
            else if (self->trig.set.mode == SINGLE)
                resp = EM_RESP_RDY_S;   // data ready - trig single
            else
                resp = EM_RESP_RDY_A;   // data ready - trig normal
        }

        comm_daq_ready(comm_ptr, resp, self->trig.pos_frst); // finally send the respond

        self->trig.respond = EM_FALSE;
        self->trig.forced = EM_FALSE;
    }
}

void daq_trig_trigger_scope(daq_data_t* self)
{
    ASSERT(self->trig.buff_trig != NULL);
    ASSERT(self->trig.dma_ch_trig != 0);

    if (self->trig.ready == EM_TRUE || self->trig.post_start == EM_TRUE)
        goto invalid_trigger;

    int ch_cnt = self->set.ch1_en + self->set.ch2_en + self->set.ch3_en + self->set.ch4_en;
    int ch_pos_trig = self->trig.dma_pos_catched % ch_cnt;
    int ch_pos_want = ch_cnt - self->trig.order - 1;

    if (ch_pos_want < ch_pos_trig)
        self->trig.dma_pos_catched -= ch_pos_trig - ch_pos_want;
    else if (ch_pos_want > ch_pos_trig)
        self->trig.dma_pos_catched -= ch_cnt - (ch_pos_want - ch_pos_trig);

    if (self->trig.dma_pos_catched < 0)
        self->trig.dma_pos_catched += self->trig.buff_trig->len;

    int prev_last_idx = self->trig.dma_pos_catched - self->trig.buff_trig->chans;
    if (prev_last_idx < 0)
        prev_last_idx += self->trig.buff_trig->len;

    //uint16_t last_val = 0;
    uint16_t prev_last_val = 0;

    if (self->set.bits == B8)
    {
        prev_last_val = (uint16_t)(((uint8_t*)(self->trig.buff_trig->data))[prev_last_idx]);
    }
    else //(self->set.bits == B12)
    {
        prev_last_val = (*((uint16_t*)(((uint8_t*)self->trig.buff_trig->data)+(prev_last_idx * 2))));
    }

    self->trig.all_cntr++;
    uint8_t switch_awd = 0;
    if (self->trig.ignore == EM_TRUE)
    {
        self->trig.ignore = EM_FALSE;
        switch_awd = 1;
    }
    else
    {
        // trigger condition
        if ((self->trig.set.edge == RISING && prev_last_val <= self->trig.set.val) || // last_val > self->trig.set.val &&
            (self->trig.set.edge == FALLING && prev_last_val >= self->trig.set.val))  // last_val < self->trig.set.val &&
        {
            daq_trig_poststart(self, self->trig.dma_pos_catched); // VALID TRIG
            return;
        }
        else // false trig, switch edges and wait for another window
        {
            self->trig.ignore = EM_TRUE;
            switch_awd = 1;
        }
    }

    if (switch_awd)
    {
        uint32_t awd_h = LL_ADC_GetAnalogWDThresholds(self->trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_THRESHOLD_HIGH);
        uint32_t awd_l = LL_ADC_GetAnalogWDThresholds(self->trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_THRESHOLD_LOW);

        LL_ADC_SetAnalogWDThresholds(self->trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_THRESHOLD_HIGH, awd_l);
        LL_ADC_SetAnalogWDThresholds(self->trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_THRESHOLD_LOW, awd_h);
    }

    invalid_trigger:  // if any code gets here, means that trigger is invalid
    LL_ADC_SetAnalogWDMonitChannels(self->trig.adc_trig, EM_ADC_AWD self->trig.awd_trig); // reenable irq
}

void daq_trig_trigger_la(daq_data_t* self)
{
    ASSERT(self->trig.buff_trig != NULL);
    ASSERT(self->trig.dma_ch_trig != 0);

    if (self->trig.ready == EM_TRUE || self->trig.post_start == EM_TRUE)
        goto invalid_trigger;

    if (self->trig.pretrig_cntr > self->trig.pretrig_val)
    {
        daq_trig_poststart(self, self->trig.dma_pos_catched); // VALID TRIG
        //return; here fails
    }
    
    return; // why need to be here?

    invalid_trigger: // if any code gets here, means that trigger is invalid
    NVIC_ClearPendingIRQ(self->trig.exti_trig);
    NVIC_EnableIRQ(self->trig.exti_trig); // reenable irq
}

void daq_trig_poststart(daq_data_t* self, int pos)
{
    self->trig.post_start = EM_TRUE;
    self->trig.post_from = pos;
    self->trig.pretrig_cntr = 0;

    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    ASSERT(xSemaphoreGiveFromISR(sem2_trig, &xHigherPriorityTaskWoken) == pdPASS);
    if (xHigherPriorityTaskWoken != pdFALSE)
        portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

void daq_trig_postcount(daq_data_t* self) // TODO slow start ??!! 600 samples (800 ksps)
{
    int last_idx = self->trig.post_from;

    ASSERT(self->trig.buff_trig != NULL);

    self->trig.is_post = EM_TRUE;
    self->trig.cntr++;

    if (self->mode == SCOPE)
    {
        self->trig.pos_trig = last_idx + self->trig.order;
        if (self->trig.pos_trig >= self->trig.buff_trig->len)
            self->trig.pos_trig -= self->trig.buff_trig->len;

        int post = (int)((double)self->set.mem * ((double)(100 - self->trig.set.pretrigger) / 100.0));
        self->trig.posttrig_size = post * self->trig.buff_trig->chans;

        self->trig.pos_last = self->trig.pos_trig + self->trig.posttrig_size;
        if (self->trig.pos_last >= self->trig.buff_trig->len)
            self->trig.pos_last -= self->trig.buff_trig->len;

        self->trig.pos_frst = self->trig.pos_trig - ((self->set.mem - post + 1) * self->trig.buff_trig->chans) + 1;

        if (self->trig.pos_frst < 0)
            self->trig.pos_frst += self->trig.buff_trig->len;
    }
    else // mode == LA
    {
        self->trig.pos_trig = last_idx;
        self->trig.posttrig_size = (int)((double)self->set.mem * ((double)(100 - self->trig.set.pretrigger) / 100.0));

        self->trig.pos_last = self->trig.pos_trig + self->trig.posttrig_size;
        if (self->trig.pos_last >= self->trig.buff_trig->len)
            self->trig.pos_last -= self->trig.buff_trig->len;

        self->trig.pos_frst = self->trig.pos_trig - (self->set.mem - self->trig.posttrig_size) + 1; // +1 ??
        if (self->trig.pos_frst < 0)
            self->trig.pos_frst += self->trig.buff_trig->len;
    }

    //int pos_last_len = self->trig.buff_trig->len - self->trig.pos_last;  // DMA len of last valid point to compare
    int target_prev = self->trig.buff_trig->len - self->trig.post_from;
    int target_sum = 0;

    while(1)
    {
        iwdg_feed(); // 1

        // 15 instructions worst case
        // Cortex M3 - 1.25 IPC per core -> 72/(15/1.25) = 6 MHz max
        int target = LL_DMA_GetDataLength(self->trig.dma_trig, self->trig.dma_ch_trig); // 6

        int target_diff = target_prev - target;
        if (target_diff >= 0)
            target_sum += target_diff;
        else
            target_sum += target_diff + self->trig.buff_trig->len;

        target_prev = target;

        if (target_sum >= self->trig.posttrig_size) // pos_last_len == target
        {
            LL_TIM_DisableCounter(EM_TIM_DAQ);

            daq_enable(self, EM_FALSE);
            self->trig.ready = EM_TRUE;
            self->trig.is_post = EM_FALSE;

            self->trig.pos_diff = self->trig.pos_last - self->trig.pos_trig;
            if (self->trig.pos_diff < 0)
                self->trig.pos_diff += self->trig.buff_trig->len;

            self->trig.respond = EM_TRUE; // init async respond ReadyX
            break;
        }
    }
    self->trig.post_start = EM_FALSE;
}

void daq_trig_update(daq_data_t* self)
{
    daq_trig_set(self, self->trig.set.ch, self->trig.set.val_percent,
                 self->trig.set.edge, self->trig.set.mode, self->trig.set.pretrigger);
}

void daq_trig_disable(daq_data_t* self)
{
    daq_trig_set(self, 0, self->trig.set.val_percent, self->trig.set.edge, DISABLED, self->trig.set.pretrigger);
}

int daq_trig_set(daq_data_t* self, uint32_t ch, uint8_t level, enum trig_edge edge, enum trig_mode mode, int pretrigger)
{
    if((level < 0 || level > 100) ||
       (ch < 1 || ch > 4) ||
       (pretrigger > 99 || pretrigger < 1))
    {
        return -1;
    }

    daq_enable(self, EM_FALSE);
    daq_reset(self);
    ADC_TypeDef* adc = ADC1;

    if (self->mode == LA)
    {
        self->trig.buff_trig = &self->buff1;
        self->trig.dma_ch_trig = EM_DMA_CH_LA;
        self->trig.dma_trig = EM_DMA_LA;
    }
    else
    {
        int ch2 = ch;
        if (mode == DISABLED)
        {
            if (self->set.ch1_en) ch2 = 1;
            else if (self->set.ch2_en) ch2 = 2;
            else if (self->set.ch3_en) ch2 = 3;
            else if (self->set.ch4_en) ch2 = 4;
        }

#if defined(EM_ADC_MODE_ADC1)

        self->trig.buff_trig = &self->buff1;
        self->trig.dma_ch_trig = EM_DMA_CH_ADC1;
        self->trig.dma_trig = EM_DMA_ADC1;
        int ch_cnt = self->set.ch1_en + self->set.ch2_en + self->set.ch3_en + self->set.ch4_en + 0;
        int it = 0;
        if (self->set.ch1_en){
            it++;
            if (ch2 == 1) self->trig.order = ch_cnt - it;
        }
        if (self->set.ch2_en){
            it++;
            if (ch2 == 2) self->trig.order = ch_cnt - it;
        }
        if (self->set.ch3_en){
            it++;
            if (ch2 == 3) self->trig.order = ch_cnt - it;
        }
        if (self->set.ch4_en){
            it++;
            if (ch2 == 4) self->trig.order = ch_cnt - it;
        }

#elif defined(EM_ADC_MODE_ADC12)

        if (ch2 == 1 || ch2 == 2)
        {
            adc = ADC1;
            self->trig.buff_trig = &self->buff1;
            self->trig.dma_ch_trig = EM_DMA_CH_ADC1;
            self->trig.dma_trig = EM_DMA_ADC1;

            int ch_cnt = self->set.ch1_en + self->set.ch2_en + 0;
            int it = 0;
            if (self->set.ch1_en){
                it++;
                if (ch2 == 1) self->trig.order = ch_cnt - it;
            }
            if (self->set.ch2_en){
                it++;
                if (ch2 == 2) self->trig.order = ch_cnt - it;
            }
        }
        else // if (ch == 3 || ch == 4)
        {
            adc = ADC2;
            self->trig.buff_trig = &self->buff2;
            self->trig.dma_ch_trig = EM_DMA_CH_ADC2;
            self->trig.dma_trig = EM_DMA_ADC2;

            int ch_cnt = self->set.ch3_en + self->set.ch4_en;
            int it = 0;
            if (self->set.ch3_en){
                it++;
                if (ch2 == 3) self->trig.order = ch_cnt - it;
            }
            if (self->set.ch4_en){
                it++;
                if (ch2 == 4) self->trig.order = ch_cnt - it;
        }

#elif defined(EM_ADC_MODE_ADC1234)

        self->trig.order = 0;
        if (ch2 == 1)
        {
            adc = ADC1;
            self->trig.buff_trig = &self->buff1;
            self->trig.dma_ch_trig = EM_DMA_CH_ADC1;
            self->trig.dma_trig = EM_DMA_ADC1;
        }
        if (ch2 == 2)
        {
            adc = ADC2;
            self->trig.buff_trig = &self->buff2;
            self->trig.dma_ch_trig = EM_DMA_CH_ADC2;
            self->trig.dma_trig = EM_DMA_ADC2;
        }
        else if (ch2 == 3)
        {
            adc = ADC3;
            self->trig.buff_trig = &self->buff3;
            self->trig.dma_ch_trig = EM_DMA_CH_ADC3;
            self->trig.dma_trig = EM_DMA_ADC3;
        }
        else // if (ch2 == 4)
        {
            adc = ADC4;
            self->trig.buff_trig = &self->buff4;
            self->trig.dma_ch_trig = EM_DMA_CH_ADC4;
            self->trig.dma_trig = EM_DMA_ADC4;
        }

#endif
    }

    self->trig.fullmem_val = (int)(((1.0 / (double)self->set.fs) * (double)self->set.mem) * (double)EM_SYSTICK_FREQ) + 1;
    self->trig.auttrig_val = EM_AUTRIG_MIN_MS + (int)((double)self->trig.fullmem_val * 1.0);
    self->trig.adc_trig = adc;

    if (mode == DISABLED)
    {
        ASSERT(self->trig.exti_trig != 0);

        NVIC_DisableIRQ(self->trig.exti_trig);
        LL_ADC_SetAnalogWDMonitChannels(adc, EM_ADC_AWD LL_ADC_AWD_DISABLE);

        self->trig.set.mode = DISABLED;

        daq_enable(self, EM_TRUE);
        return 0;
    }

    if (self->mode == LA)
    {
        LL_ADC_SetAnalogWDMonitChannels(adc, EM_ADC_AWD LL_ADC_AWD_DISABLE);

        LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
        uint32_t extiline = 0;
        uint32_t exti = 0;

        if (ch == 1)
        {
            self->trig.exti_trig = EM_LA_IRQ_EXTI1;
            extiline = EM_LA_EXTILINE1;
            exti = EM_LA_EXTI1;
        }
        else if (ch == 2)
        {
            self->trig.exti_trig = EM_LA_IRQ_EXTI2;
            extiline = EM_LA_EXTILINE2;
            exti = EM_LA_EXTI2;
        }
        else if (ch == 3)
        {
            self->trig.exti_trig = EM_LA_IRQ_EXTI3;
            extiline = EM_LA_EXTILINE3;
            exti = EM_LA_EXTI3;
        }
        else // if (ch == 4)
        {
            self->trig.exti_trig = EM_LA_IRQ_EXTI4;
            extiline = EM_LA_EXTILINE4;
            exti = EM_LA_EXTI4;
        }

        LL_EXTI_DisableIT_0_31(EM_LA_EXTI1);
        LL_EXTI_DisableIT_0_31(EM_LA_EXTI2);
        LL_EXTI_DisableIT_0_31(EM_LA_EXTI3);
        LL_EXTI_DisableIT_0_31(EM_LA_EXTI4);

        EM_GPIO_EXTI_SRC(EM_LA_EXTI_PORT, extiline);

        EXTI_InitStruct.Line_0_31 = exti;
        EXTI_InitStruct.LineCommand = ENABLE;
        EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
        EXTI_InitStruct.Trigger = (edge == RISING ? LL_EXTI_TRIGGER_RISING : LL_EXTI_TRIGGER_FALLING);
        LL_EXTI_Init(&EXTI_InitStruct);
        LL_EXTI_EnableIT_0_31(exti);

        NVIC_SetPriority(self->trig.exti_trig, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), EM_IT_PRI_EXTI, 0));
        NVIC_DisableIRQ(self->trig.exti_trig);

        self->trig.set.val = 0;
        self->trig.set.val_percent = 0;
    }
    else // SCOPE
    {
        ASSERT(self->trig.exti_trig != 0);
        NVIC_DisableIRQ(self->trig.exti_trig);

        if ((ch == 1 && self->set.ch1_en) ||
            (ch == 2 && self->set.ch2_en) ||
            (ch == 3 && self->set.ch3_en) ||
            (ch == 4 && self->set.ch4_en))
        {
            if (ch == 1)
                self->trig.awd_trig = EM_ADC_AWD1;
            else if (ch == 2)
                self->trig.awd_trig = EM_ADC_AWD2;
            else if (ch == 3)
                self->trig.awd_trig = EM_ADC_AWD3;
            else if (ch == 4)
                self->trig.awd_trig = EM_ADC_AWD4;

            uint32_t level_raw = (int)(self->adc_max_val / 100.0 * (double)level);

            if (edge == RISING)
            {
                memset(self->trig.buff_trig->data, (int)self->adc_max_val,
                       self->trig.buff_trig->len * (self->set.bits == B12 ? sizeof(uint16_t) : sizeof(uint8_t)));

                LL_ADC_SetAnalogWDThresholds(adc, EM_ADC_AWD LL_ADC_AWD_THRESHOLD_HIGH, level_raw);
                LL_ADC_SetAnalogWDThresholds(adc, EM_ADC_AWD LL_ADC_AWD_THRESHOLD_LOW, 0);
            }
            else // (edge == FALLING)
            {
                memset(self->trig.buff_trig->data, 0,
                       self->trig.buff_trig->len * (self->set.bits == B12 ? sizeof(uint16_t) : sizeof(uint8_t)));

                LL_ADC_SetAnalogWDThresholds(adc, EM_ADC_AWD LL_ADC_AWD_THRESHOLD_HIGH, (int)self->adc_max_val);
                LL_ADC_SetAnalogWDThresholds(adc, EM_ADC_AWD LL_ADC_AWD_THRESHOLD_LOW, level_raw);
            }

            self->trig.set.val = level_raw;
            self->trig.set.val_percent = level;
        }
        else return -1;
    }

    self->trig.pretrig_val = (int)((double)self->trig.fullmem_val * ((double)pretrigger / 100.0)) + 1;
    self->trig.set.pretrigger = pretrigger;
    self->trig.set.mode = mode;
    self->trig.set.edge = edge;
    self->trig.set.ch = ch;

    if (self->trig.pretrig_val < EM_PRETRIG_MIN_MS)
        self->trig.pretrig_val = EM_PRETRIG_MIN_MS;

    daq_enable(self, EM_TRUE);
    return 0;
}
