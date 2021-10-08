/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"
#include "daq.h"
#include "daq_trig.h"

#include "main.h"
#include "periph/periph_adc.h"
#include "periph/periph_dma.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


static void daq_enable_adc(daq_data_t* self, ADC_TypeDef* adc, uint8_t enable, uint32_t dma_ch);
static void daq_malloc(daq_data_t* self, daq_buff_t* buff, int mem, int reserve, int chans, uint32_t src, uint32_t dma_ch,
                       DMA_TypeDef* dma, enum daq_bits bits);
static void daq_clear_buff(daq_buff_t* buff);


void daq_init(daq_data_t* self)
{
    daq_trig_init(self);
    daq_settings_init(self, EM_TRUE, EM_TRUE);
    daq_settings_save(&self->save_s, &self->trig.save_s, &self->set, &self->trig.set);
    self->mode = SCOPE;

    daq_clear_buff(&self->buff1);
    daq_clear_buff(&self->buff2);
    daq_clear_buff(&self->buff3);
    daq_clear_buff(&self->buff4);
    memset(self->buff_raw, 0, EM_DAQ_MAX_MEM * sizeof(uint8_t));
    self->buff_raw_ptr = 0;

    self->trig.buff_trig = NULL;
    self->enabled = EM_FALSE;
    self->dis_hold = EM_FALSE;
    self->vref = 0;
    self->vcc_mv = 0;
    self->adc_max_val = 0;
    self->smpl_time = 0;
    self->interleaved = EM_FALSE;
    self->dualmode = EM_FALSE;
    self->uwTick = 0;
    self->uwTick_start = 0;
    self->vm_seq = -1;

    NVIC_DisableIRQ(EM_LA_IRQ_EXTI1);
    NVIC_DisableIRQ(EM_LA_IRQ_EXTI2);

    #ifdef EM_DAQ_4CH
        NVIC_DisableIRQ(EM_LA_IRQ_EXTI3);
        NVIC_DisableIRQ(EM_LA_IRQ_EXTI4);
    #endif

    NVIC_SetPriority(EM_LA_IRQ_EXTI1, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), EM_IT_PRI_EXTI, 0));
    NVIC_SetPriority(EM_LA_IRQ_EXTI2, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), EM_IT_PRI_EXTI, 0));

    #ifdef EM_DAQ_4CH
        NVIC_SetPriority(EM_LA_IRQ_EXTI3, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), EM_IT_PRI_EXTI, 0));
        NVIC_SetPriority(EM_LA_IRQ_EXTI4, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), EM_IT_PRI_EXTI, 0));
    #endif

    #if defined(EM_ADC1_USED)
        NVIC_SetPriority(EM_IRQN_ADC1, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), EM_IT_PRI_ADC, 0));
        NVIC_DisableIRQ(EM_IRQN_ADC1);
    #endif

    #if defined(EM_ADC2_USED)
        NVIC_SetPriority(EM_IRQN_ADC2, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), EM_IT_PRI_ADC, 0));
        NVIC_DisableIRQ(EM_IRQN_ADC2);
    #endif

    #if defined(EM_ADC3_USED)
        NVIC_SetPriority(EM_IRQN_ADC3, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), EM_IT_PRI_ADC, 0));
        NVIC_DisableIRQ(EM_IRQN_ADC3);
    #endif

    #if defined(EM_ADC4_USED)
        NVIC_SetPriority(EM_IRQN_ADC4, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), EM_IT_PRI_ADC, 0));
        NVIC_DisableIRQ(EM_IRQN_ADC4);
    #endif

    adc_init();
}

void daq_settings_save(daq_settings_t* src1, trig_settings_t* src2, daq_settings_t* dst1, trig_settings_t* dst2)
{
    dst1->fs = src1->fs;
    dst1->mem = src1->mem;
    dst1->bits = src1->bits;

    dst1->ch1_en = src1->ch1_en;
    dst1->ch2_en = src1->ch2_en;
    dst1->ch3_en = src1->ch3_en;
    dst1->ch4_en = src1->ch4_en;

    dst2->val_percent = src2->val_percent;
    dst2->val = src2->val;
    dst2->ch = src2->ch;
    dst2->edge = src2->edge;
    dst2->mode = src2->mode;
    dst2->pretrigger = src2->pretrigger;
}

void daq_settings_init(daq_data_t* self, uint8_t scope, uint8_t la)
{
    if (scope == EM_TRUE)
    {
        self->save_s.fs = 100000;
        self->save_s.mem = 1000;
        self->save_s.bits = B12;

        self->save_s.ch1_en = 1;
        self->save_s.ch2_en = 1;
        self->save_s.ch3_en = 0;
        self->save_s.ch4_en = 0;

        self->trig.save_s.val_percent = 50;
        self->trig.save_s.val = 2047;
        self->trig.save_s.ch = 1;
        self->trig.save_s.edge = RISING;
        self->trig.save_s.mode = AUTO;
        self->trig.save_s.pretrigger = 50;
    }

    if (la == EM_TRUE)
    {
        self->save_l.fs = 100000;
        self->save_l.mem = 2000;
        self->save_l.bits = B1;

        self->save_l.ch1_en = 1;
        self->save_l.ch2_en = 1;
        self->save_l.ch3_en = 1;
        self->save_l.ch4_en = 1;

        self->trig.save_l.val_percent = 0;
        self->trig.save_l.val = 0;
        self->trig.save_l.ch = 1;
        self->trig.save_l.edge = RISING;
        self->trig.save_l.mode = AUTO;
        self->trig.save_l.pretrigger = 50;
    }
}

int daq_mem_set(daq_data_t* self, uint16_t mem_per_ch)
{
    daq_enable(self, EM_FALSE);
    daq_reset(self);

    daq_clear_buff(&self->buff1);
    daq_clear_buff(&self->buff2);
    daq_clear_buff(&self->buff3);
    daq_clear_buff(&self->buff4);
    self->buff_raw_ptr = 0;
    memset(self->buff_raw, 0, EM_DAQ_MAX_MEM * sizeof(uint8_t));

    int max_len = EM_DAQ_MAX_MEM;
    if (self->set.bits == B12)
        max_len /= 2;

    if (self->mode != LA)
    {
        uint8_t is_vcc = (self->mode == VM ? 1 : 0);

        #if defined(EM_ADC_MODE_ADC1)

            int len1 = self->set.ch1_en + self->set.ch2_en + self->set.ch3_en + self->set.ch4_en + is_vcc;

            if (mem_per_ch < 1 || (mem_per_ch * len1) > max_len)
                return -2;

            daq_malloc(self, &self->buff1, mem_per_ch * len1, EM_MEM_RESERVE, len1, EM_ADC_ADDR(EM_ADC1), EM_DMA_CH_ADC1, EM_DMA_ADC1, self->set.bits);

        #elif defined(EM_ADC_MODE_ADC12)

            int len1 = self->set.ch1_en + self->set.ch2_en + is_vcc;
            int len2 = self->set.ch3_en + self->set.ch4_en;
            int total = len1 + len2;

            #if defined(EM_ADC_INTERLEAVED)
                if (chans == 1)
                {
                    len1 = 1;
                    len2 = 0;
                    total = 1;
                }
            #endif

            if (mem_per_ch < 1 || (mem_per_ch * total) > max_len)
                return -2;

            if (len1 > 0)
                daq_malloc(self, &self->buff1, mem_per_ch * len1, EM_MEM_RESERVE, len1, EM_ADC_ADDR(EM_ADC1), EM_DMA_CH_ADC1, EM_DMA_ADC1, self->set.bits);
            if (len2 > 0)
                daq_malloc(self, &self->buff2, mem_per_ch * len2, EM_MEM_RESERVE, len2, EM_ADC_ADDR(EM_ADC2), EM_DMA_CH_ADC2, EM_DMA_ADC2, self->set.bits);

        #elif defined(EM_ADC_MODE_ADC1234)

            int len1 = self->set.ch1_en + is_vcc;
            int len2 = self->set.ch2_en;
            int len3 = self->set.ch3_en;
            int len4 = self->set.ch4_en;
            int total = len1 + len2 + len3 + len4;

            #if defined(EM_ADC_INTERLEAVED)
                if (chans == 1)
                {
                    len1 = 1;
                    len2 = 0;
                    len3 = 1;
                    len4 = 0;
                    total = 2; // TODO size??
                }
            #endif

            if (mem_per_ch < 1 || (mem_per_ch * total) > max_len)
                return -2;

            if (len1 > 0)
                daq_malloc(self, &self->buff1, mem_per_ch * len1, EM_MEM_RESERVE, len1, EM_ADC_ADDR(EM_ADC1), EM_DMA_CH_ADC1, EM_DMA_ADC1, self->set.bits);
            if (len2 > 0)
                daq_malloc(self, &self->buff2, mem_per_ch * len2, EM_MEM_RESERVE, len2, EM_ADC_ADDR(EM_ADC2), EM_DMA_CH_ADC2, EM_DMA_ADC2, self->set.bits);
            if (len3 > 0)
                daq_malloc(self, &self->buff3, mem_per_ch * len3, EM_MEM_RESERVE, len3, EM_ADC_ADDR(EM_ADC3), EM_DMA_CH_ADC3, EM_DMA_ADC3, self->set.bits);
            if (len4 > 0)
                daq_malloc(self, &self->buff4, mem_per_ch * len4, EM_MEM_RESERVE, len4, EM_ADC_ADDR(EM_ADC4), EM_DMA_CH_ADC4, EM_DMA_ADC4, self->set.bits);

        #endif
    }
    else // mode == LA
    {
        if (mem_per_ch < 1 || mem_per_ch > EM_DAQ_MAX_MEM)
            return -2;

        daq_malloc(self, &self->buff1, mem_per_ch, EM_MEM_RESERVE, 4, (uint32_t)&EM_GPIO_LA_PORT->IDR+EM_GPIO_LA_OFFSET,
                   EM_DMA_CH_LA, EM_DMA_LA, self->set.bits);
    }

    self->set.mem = mem_per_ch;

    daq_trig_update(self);
    daq_enable(self, EM_TRUE);
    return 0;
}

static void daq_malloc(daq_data_t* self, daq_buff_t* buff, int mem, int reserve, int chans, uint32_t src,
                       uint32_t dma_ch, DMA_TypeDef* dma, enum daq_bits bits)
{
    if (bits == B12)
    {
        mem += reserve * chans;
        buff->reserve = reserve * chans;

        size_t ln = mem * sizeof(uint16_t);
        buff->data = (uint16_t*)(((uint8_t*)self->buff_raw)+(self->buff_raw_ptr));
        self->buff_raw_ptr += mem * 2;
        buff->chans = chans;
        buff->len = mem;
        memset(buff->data, 0, ln);
        uint32_t dma_p_sz = LL_DMA_PDATAALIGN_HALFWORD;
        uint32_t dma_m_sz = LL_DMA_MDATAALIGN_HALFWORD;

        #if defined(EM_ADC_DUALMODE)
            if (chans == 2 || chans == 4)
            {
                dma_p_sz = LL_DMA_PDATAALIGN_WORD;
                dma_m_sz = LL_DMA_MDATAALIGN_WORD;
            }
        #endif

        #if defined(EM_ADC_INTERLEAVED)
            if (chans == 1)
            {
                dma_p_sz = LL_DMA_PDATAALIGN_WORD;
                dma_m_sz = LL_DMA_MDATAALIGN_WORD;
            }
        #endif

        dma_set(src, dma, dma_ch, (uint32_t)((uint16_t*)((uint8_t*)buff->data)), mem,
                dma_p_sz, dma_m_sz, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    }
    else if (bits == B8)
    {
        mem += reserve * chans;
        buff->reserve = reserve * chans;

        size_t ln = mem * sizeof(uint8_t);
        buff->data = (uint8_t*)(((uint8_t*)self->buff_raw)+(self->buff_raw_ptr));
        self->buff_raw_ptr += mem;
        buff->chans = chans;
        buff->len = mem;
        memset(buff->data, 0, ln);
        uint32_t dma_p_sz = LL_DMA_PDATAALIGN_BYTE;
        uint32_t dma_m_sz = LL_DMA_MDATAALIGN_BYTE;

        #if defined(EM_ADC_DUALMODE)
            if (chans == 2 || chans == 4)
            {
                dma_p_sz = LL_DMA_PDATAALIGN_HALFWORD;
                dma_m_sz = LL_DMA_MDATAALIGN_HALFWORD;
            }
        #endif

        #if defined(EM_ADC_INTERLEAVED)
            if (chans == 1)
            {
                dma_p_sz = LL_DMA_PDATAALIGN_HALFWORD;
                dma_m_sz = LL_DMA_PDATAALIGN_HALFWORD;
            }
        #endif

        dma_set(src, dma, dma_ch, (uint32_t)((uint8_t*)buff->data), mem,
                dma_p_sz, dma_m_sz, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    }
    else // if (bits == B1)
    {
        mem += reserve * 1;
        buff->reserve = reserve * 1;

        size_t ln = mem * sizeof(uint8_t);
        buff->data = (uint8_t*)(((uint8_t*)self->buff_raw)+(self->buff_raw_ptr));
        self->buff_raw_ptr += mem;
        buff->chans = chans;
        buff->len = mem;
        memset(buff->data, 0, ln);
        dma_set(src, dma, EM_DMA_CH_LA, (uint32_t)((uint8_t*)buff->data), mem,
                LL_DMA_PDATAALIGN_BYTE, LL_DMA_MDATAALIGN_BYTE, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    }
}

static void daq_clear_buff(daq_buff_t* buff)
{
    buff->data = NULL;
    buff->chans = 0;
    buff->len = 0;
    buff->reserve = 0;
}

int daq_bit_set(daq_data_t* self, enum daq_bits bits)
{
    if (bits != B12 && bits != B8 && bits != B1)
        return -1;

    self->set.bits = bits;
    if (bits == B12)
        self->adc_max_val = 4095;
    else if (bits == B8)
        self->adc_max_val = 255;
    else
        self->adc_max_val = 1;

    if (self->mode == SCOPE || self->mode == VM)
    {
        daq_enable(self, EM_FALSE);
        daq_reset(self);

        if (bits == B8)
        {
            #ifndef EM_ADC_BIT8
                return -2;
            #endif
        }

        uint32_t bits_raw = LL_ADC_RESOLUTION_12B;

        #ifdef EM_ADC_BIT8
            if (bits == B8)
                bits_raw = LL_ADC_RESOLUTION_8B;
        #endif

        #if defined(EM_ADC_MODE_ADC1) || defined(EM_ADC_MODE_ADC12) || defined(EM_ADC_MODE_ADC1234)
            adc_set_res(EM_ADC1, bits_raw);
        #endif

        #if defined(EM_ADC_MODE_ADC12) || defined(EM_ADC_MODE_ADC1234)
            adc_set_res(EM_ADC2, bits_raw);
        #endif

        #if defined(EM_ADC_MODE_ADC1234)
            adc_set_res(EM_ADC3, bits_raw);
            adc_set_res(EM_ADC4, bits_raw);
        #endif

        int ret = daq_mem_set(self, self->set.mem);

        daq_enable(self, EM_TRUE);

        return ret;
    }
    return 0;
}

int daq_fs_set(daq_data_t* self, int fs)
{
    uint8_t is_vcc = (self->mode == VM ? 1 : 0);
    int fs2 = fs;

    #if defined(EM_ADC_MODE_ADC1)
        int channs = self->set.ch1_en + self->set.ch2_en + self->set.ch3_en + self->set.ch4_en + is_vcc;
        //double scope_max_fs = 1.0 / (EM_ADC_1CH_SMPL_TM(EM_ADC_SMPLT_MAX_N, (self->set.bits == B12 ? EM_ADC_TCONV12 : EM_ADC_TCONV8)) * (float)(channs));
        double scope_max_fs = (self->set.bits == B12 ? EM_DAQ_MAX_B12_FS : EM_DAQ_MAX_B8_FS) / (double)(channs);

        #if defined(EM_ADC_DUALMODE)
            if (channs == 2 || channs == 4)
                scope_max_fs *= 2.0;
        #endif

        #if defined(EM_ADC_INTERLEAVED)
            if (channs == 1)
                fs2 /= 2.0;
        #endif

    #elif defined(EM_ADC_MODE_ADC12)
        int adc1 = self->set.ch1_en + self->set.ch2_en + is_vcc;
        int adc2 = self->set.ch3_en + self->set.ch4_en;
        double scope_max_fs = (self->set.bits == B12 ? EM_DAQ_MAX_B12_FS : EM_DAQ_MAX_B8_FS) / (double)(adc1 > adc2 ? adc1 : adc2);

        #if defined(EM_ADC_INTERLEAVED)
            if (channs == 1)
                fs2 /= 2.0;
        #endif

    #elif defined(EM_ADC_MODE_ADC1234)
        double scope_max_fs = (self->set.bits == B12 ? EM_DAQ_MAX_B12_FS : EM_DAQ_MAX_B8_FS) / (double)(self->set.ch1_en ? 1 + is_vcc : 1);

        #if defined(EM_ADC_INTERLEAVED)
            if (channs == 1)
                fs2 /= 4.0;
        #endif

    #endif

    if (fs2 < 1 || fs2 > (self->mode == LA ? EM_LA_MAX_FS : scope_max_fs))
        return -1;

    self->set.fs = fs;

    daq_enable(self, EM_FALSE);
    daq_reset(self);

    int prescaler = 1;
    int reload = 1;
    self->set.fs_real = get_freq(&prescaler, &reload, EM_TIM_DAQ_MAX, EM_TIM_DAQ_FREQ, fs2);

    LL_TIM_SetPrescaler(EM_TIM_DAQ, prescaler);
    LL_TIM_SetAutoReload(EM_TIM_DAQ, reload);

    daq_trig_update(self);
    daq_enable(self, EM_TRUE);
    return 0;
}

int daq_ch_set(daq_data_t* self, uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, int fs)
{
    #ifndef EM_DAQ_4CH
        if (ch3 == EM_TRUE || ch4 == EM_TRUE)
            return -1;
    #endif

    self->set.ch1_en = ch1;
    self->set.ch2_en = ch2;
    self->set.ch3_en = ch3;
    self->set.ch4_en = ch4;

    if (self->set.ch1_en + self->set.ch2_en + self->set.ch3_en + self->set.ch4_en <= 0)
        return -1;

    int reen = 0;
    if (self->enabled == EM_TRUE)
    {
        reen = 1;
        daq_enable(self, EM_FALSE);
        daq_reset(self);
    }

    if (self->mode != LA)
    {
        if (fs <= 0)
            return -1;

        uint8_t is_vcc = (self->mode == VM ? 1 : 0);
        uint32_t smpl_time = EM_ADC_SMPLT[0];
        float smpl_time_n = EM_ADC_SMPLT_N[0];
        int channs = 0;

        #if defined(EM_ADC_MODE_ADC1)
            channs = self->set.ch1_en + self->set.ch2_en + self->set.ch3_en + self->set.ch4_en + is_vcc;

            #if defined(EM_ADC_DUALMODE)
                    if (channs == 2 || channs == 4)
                        channs /= 2;
            #endif

        #elif defined(EM_ADC_MODE_ADC12)
            int len1 = self->set.ch1_en + self->set.ch2_en + is_vcc;
            int len2 = self->set.ch3_en + self->set.ch4_en;
            channs = len1 > len2 ? len1 : len2;

        #elif defined(EM_ADC_MODE_ADC1234)
                channs = is_vcc ? 2 : 1;
        #endif

        double T = 1.0 / fs;
        for (int i = 0; i < EM_ADC_SMPLT_CNT; i++) // find best sample time
        {
            if (((double)channs * EM_ADC_1CH_SMPL_TM(EM_ADC_SMPLT_N[i] + 0.5, (self->set.bits == B12 ? EM_ADC_TCONV12 : EM_ADC_TCONV8))) < T)
            {
                smpl_time = EM_ADC_SMPLT[i];
                smpl_time_n = EM_ADC_SMPLT_N[i];
            }
            else
            {
                break;
            }
        }
        self->smpl_time = smpl_time_n;

        #if defined(EM_ADC_MODE_ADC1) /* --------------------------------------------------------------------------*/
            adc_set_ch(EM_ADC1, ch1, ch2, ch3, ch4, smpl_time, is_vcc);

            #if defined(EM_ADC_DUALMODE)
                    if (channs == 2)
                    {
                        if (ch1 && ch2) {
                            adc_set_ch(EM_ADC1, ch1, 0, 0, 0, smpl_time, 0);
                            adc_set_ch(EM_ADC2, 0, ch2, 0, 0, smpl_time, 0);
                        }
                        else if (ch1 && ch3) {
                            adc_set_ch(EM_ADC1, ch1, 0, 0, 0, smpl_time, 0);
                            adc_set_ch(EM_ADC2, 0, 0, ch3, 0, smpl_time, 0);
                        }
                        else if (ch1 && ch4) {
                            adc_set_ch(EM_ADC1, ch1, 0, 0, 0, smpl_time, 0);
                            adc_set_ch(EM_ADC2, 0, 0, 0, ch4, smpl_time, 0);
                        }
                        else if (ch2 && ch3) {
                            adc_set_ch(EM_ADC1, 0, ch2, 0, 0, smpl_time, 0);
                            adc_set_ch(EM_ADC2, 0, 0, ch3, 0, smpl_time, 0);
                        }
                        else if (ch2 && ch4) {
                            adc_set_ch(EM_ADC1, 0, ch2, 0, 0, smpl_time, 0);
                            adc_set_ch(EM_ADC2, 0, 0, 0, ch4, smpl_time, 0);
                        }
                        else if (ch3 && ch4) {
                            adc_set_ch(EM_ADC1, 0, 0, ch3, 0, smpl_time, 0);
                            adc_set_ch(EM_ADC2, 0, 0, 0, ch4, smpl_time, 0);
                        }
                        else ASSERT(0);
                    }
                    else if (channs == 4)
                    {
                        adc_set_ch(EM_ADC1, ch1, ch2, 0, 0, smpl_time, 0);
                        adc_set_ch(EM_ADC2, 0, 0, ch3, ch4, smpl_time, 0);
                    }

                    if (channs == 2 || channs == 4)
                    {
                        LL_ADC_SetMultimode(__LL_ADC_COMMON_INSTANCE(EM_ADC1), LL_ADC_MULTI_DUAL_REG_SIMULT);
                        LL_ADC_REG_SetTriggerSource(EM_ADC2, LL_ADC_REG_TRIG_SOFTWARE);
                        LL_ADC_REG_SetDMATransfer(EM_ADC2, LL_ADC_REG_DMA_TRANSFER_NONE);

                        self->dualmode = EM_TRUE;
                    }
                    else
                        self->dualmode = EM_FALSE;

            #endif

            #if defined(EM_ADC_INTERLEAVED)
                    if (channs == 1)
                    {
                        adc_set_ch(EM_ADC1, ch1, ch2, ch3, ch4, smpl_time, 0);
                        adc_set_ch(EM_ADC2, ch1, ch2, ch3, ch4, smpl_time, 0);

                        LL_ADC_SetMultimode(__LL_ADC_COMMON_INSTANCE(EM_ADC1), LL_ADC_MULTI_DUAL_REG_INTERL_FAST);
                        LL_ADC_REG_SetTriggerSource(EM_ADC2, LL_ADC_REG_TRIG_SOFTWARE);
                        LL_ADC_REG_SetDMATransfer(EM_ADC2, LL_ADC_REG_DMA_TRANSFER_NONE);

                        self->interleaved = EM_TRUE;
                    }
                    else
                        self->interleaved = EM_FALSE;
            #endif

        #elif defined(EM_ADC_MODE_ADC12) /* --------------------------------------------------------------------------*/
            adc_set_ch(EM_ADC1, ch1, ch2, 0, 0, smpl_time, is_vcc);
            adc_set_ch(EM_ADC2, 0, 0, ch3, ch4, smpl_time, 0);

            #if defined(EM_ADC_INTERLEAVED)
                if (channs == 1)
                {
                    adc_set_ch(EM_ADC1, ch1, ch2, ch3, ch4, smpl_time, 0);
                    adc_set_ch(EM_ADC2, ch1, ch2, ch3, ch4, smpl_time, 0);

                    LL_ADC_SetMultimode(__LL_ADC_COMMON_INSTANCE(EM_ADC1), LL_ADC_MULTI_DUAL_REG_INTERL_FAST);
                    LL_ADC_REG_SetTriggerSource(EM_ADC2, LL_ADC_REG_TRIG_SOFTWARE);
                    LL_ADC_REG_SetDMATransfer(EM_ADC2, LL_ADC_REG_DMA_TRANSFER_NONE);

                    self->interleaved = EM_TRUE;
                }
                else
                    self->interleaved = EM_FALSE;
            #endif

        #elif defined(EM_ADC_MODE_ADC1234) /* --------------------------------------------------------------------------*/
            adc_set_ch(EM_ADC1, ch1, 0, 0, 0, smpl_time, is_vcc);
            adc_set_ch(EM_ADC2, 0, ch2, 0, 0, smpl_time, 0);
            adc_set_ch(EM_ADC3, 0, 0, ch3, 0, smpl_time, 0);
            adc_set_ch(EM_ADC4, 0, 0, 0, ch4, smpl_time, 0);

            #if defined(EM_ADC_INTERLEAVED)
                if (channs == 1)
                {
                    adc_set_ch(EM_ADC1, ch1, ch2, ch3, ch4, smpl_time, 0);
                    adc_set_ch(EM_ADC2, ch1, ch2, ch3, ch4, smpl_time, 0);
                    adc_set_ch(EM_ADC3, ch1, ch2, ch3, ch4, smpl_time, 0);
                    adc_set_ch(EM_ADC4, ch1, ch2, ch3, ch4, smpl_time, 0);

                    LL_ADC_SetMultimode(__LL_ADC_COMMON_INSTANCE(EM_ADC1), LL_ADC_MULTI_DUAL_REG_INTERL_FAST);
                    LL_ADC_REG_SetTriggerSource(EM_ADC2, LL_ADC_REG_TRIG_SOFTWARE);
                    LL_ADC_REG_SetDMATransfer(EM_ADC2, LL_ADC_REG_DMA_TRANSFER_NONE);
                    LL_ADC_REG_SetTriggerSource(EM_ADC3, LL_ADC_REG_TRIG_SOFTWARE);
                    LL_ADC_REG_SetDMATransfer(EM_ADC3, LL_ADC_REG_DMA_TRANSFER_NONE);
                    LL_ADC_REG_SetTriggerSource(EM_ADC4, LL_ADC_REG_TRIG_SOFTWARE);
                    LL_ADC_REG_SetDMATransfer(EM_ADC4, LL_ADC_REG_DMA_TRANSFER_NONE);

                    self->interleaved = EM_TRUE;
                }
                else
                    self->interleaved = EM_FALSE;
            #endif

        #endif
    }

    //int ret = daq_mem_set(self, self->set.mem);

    if (reen)
        daq_enable(self, EM_TRUE);

    return 0;
}

void daq_reset(daq_data_t* self)
{
    self->trig.uwtick_first = 0;
    self->trig.pretrig_cntr = 0;
    self->trig.posttrig_size = 0;
    self->trig.ready_last = EM_FALSE;
    self->trig.ready = EM_FALSE;
    self->trig.cntr = 0;
    self->trig.all_cntr = 0;
    //self->trig.pos_frst = 0;
    //self->trig.pos_trig = 0;
    //self->trig.pos_last = 0;
    //self->trig.pos_diff = 0;
    self->trig.pretrig_cntr = 0;
    self->trig.is_post = EM_FALSE;

    if (self->buff1.len > 0)
        memset(self->buff1.data, 0, self->buff1.len);
    if (self->buff2.len > 0)
        memset(self->buff2.data, 0, self->buff2.len);
    if (self->buff3.len > 0)
        memset(self->buff3.data, 0, self->buff3.len);
    if (self->buff4.len > 0)
        memset(self->buff4.data, 0, self->buff4.len);
}

void daq_enable(daq_data_t* self, uint8_t enable)
{
    if (enable == EM_FALSE)
    {
        LL_TIM_DisableCounter(EM_TIM_DAQ);
        for (int i = 0; i < 10000; i++) __asm("nop"); // wait for all conversions finish (crucial!)
    }

    if (self->enabled == EM_TRUE && self->dis_hold == EM_TRUE)
        return;

    self->trig.pretrig_cntr = 0;
    self->trig.all_cntr = 0;
    self->trig.cntr = 0;
    self->trig.ignore = EM_FALSE;
    self->trig.irq_en = EM_FALSE;
    self->trig.force_single = EM_FALSE;

    if (self->mode == SCOPE || self->mode == VM)
    {
        #if defined(EM_ADC_MODE_ADC1)
            daq_enable_adc(self, EM_ADC1, enable, EM_DMA_CH_ADC1);
        #elif defined(EM_ADC_MODE_ADC12)
            daq_enable_adc(self, EM_ADC1, (enable && (self->set.ch1_en == EM_TRUE || self->set.ch2_en == EM_TRUE)), EM_DMA_CH_ADC1);
            daq_enable_adc(self, EM_ADC2, (enable && (self->set.ch3_en == EM_TRUE || self->set.ch4_en == EM_TRUE) &&
                    (self->interleaved == EM_FALSE)), EM_DMA_CH_ADC2);
        #elif defined(EM_ADC_MODE_ADC1234)
            daq_enable_adc(self, EM_ADC1, (enable && (self->set.ch1_en == EM_TRUE)), EM_DMA_CH_ADC1);
            daq_enable_adc(self, EM_ADC2, (enable && (self->set.ch2_en == EM_TRUE) && (self->interleaved == EM_FALSE)), EM_DMA_CH_ADC2);
            daq_enable_adc(self, EM_ADC3, (enable && (self->set.ch3_en == EM_TRUE) && (self->interleaved == EM_FALSE)), EM_DMA_CH_ADC3);
            daq_enable_adc(self, EM_ADC4, (enable && (self->set.ch4_en == EM_TRUE) && (self->interleaved == EM_FALSE)), EM_DMA_CH_ADC4);
        #endif
    }
    else //if(self->mode == LA)
    {
        ASSERT(self->trig.exti_trig != 0);

        if (enable == EM_TRUE)
        {
            EM_TIM_DAQ_CC(LL_TIM_EnableDMAReq_)(EM_TIM_DAQ);

            //NVIC_ClearPendingIRQ(self->trig.exti_trig);
            //if (self->trig.set.mode != DISABLED)
            //    NVIC_EnableIRQ(self->trig.exti_trig);
        }
        else
        {
            EM_TIM_DAQ_CC(LL_TIM_DisableDMAReq_)(EM_TIM_DAQ);
            NVIC_DisableIRQ(self->trig.exti_trig);
        }
    }

    //for (int i = 0; i < 10000; i++) __asm("nop");  // let DMA and ADC finish their jobs

    if (enable == EM_TRUE) // start the timer
    {
        LL_TIM_EnableCounter(EM_TIM_DAQ);
    }

    self->trig.uwtick_first = self->uwTick;
    self->enabled = enable;
}

static void daq_enable_adc(daq_data_t* self, ADC_TypeDef* adc, uint8_t enable, uint32_t dma_ch)
{
    if (enable == EM_TRUE)
    {
        #ifdef LL_ADC_SPEC_START
            LL_ADC_REG_StartConversionExtTrig(adc, LL_ADC_REG_TRIG_EXT_RISING);
        #else
            LL_ADC_REG_StartConversion(adc);
        #endif
    }
    else
    {
        #ifdef LL_ADC_SPEC_START
            LL_ADC_REG_StopConversionExtTrig(adc);
        #else
            LL_ADC_REG_StopConversion(adc); // if stopped anytime (not synced with timer) it could break order of channels!
        #endif

        LL_ADC_SetAnalogWDMonitChannels(adc, EM_ADC_AWD LL_ADC_AWD_DISABLE);
    }
}

void daq_mode_set(daq_data_t* self, enum daq_mode mode)
{
    if (self->mode == SCOPE)
        daq_settings_save(&self->set, &self->trig.set, &self->save_s, &self->trig.save_s);
    else if (self->mode == LA)
        daq_settings_save(&self->set, &self->trig.set, &self->save_l, &self->trig.save_l);

    daq_enable(self, EM_FALSE);
    daq_reset(self);
    self->dis_hold = EM_TRUE;
    self->mode = mode;

    // GPIO init
    if (mode == SCOPE || mode == VM)
    {
        LL_GPIO_InitTypeDef GPIO_InitStruct =
        {
            .Pin = EM_GPIO_ADC_CH1,
            .Speed = LL_GPIO_SPEED_FREQ_HIGH,
            .Mode = LL_GPIO_MODE_ANALOG
        };
        LL_GPIO_Init(EM_GPIO_ADC_PORT1, &GPIO_InitStruct);
        GPIO_InitStruct.Pin = EM_GPIO_ADC_CH2;
        LL_GPIO_Init(EM_GPIO_ADC_PORT2, &GPIO_InitStruct);

        #ifdef EM_DAQ_4CH
            GPIO_InitStruct.Pin = EM_GPIO_ADC_CH3;
            LL_GPIO_Init(EM_GPIO_ADC_PORT3, &GPIO_InitStruct);
            GPIO_InitStruct.Pin = EM_GPIO_ADC_CH4;
            LL_GPIO_Init(EM_GPIO_ADC_PORT4, &GPIO_InitStruct);
        #endif
    }
    else // if (mode == LA)
    {
        LL_GPIO_InitTypeDef GPIO_InitStruct =
        {
            #ifdef EM_DAQ_4CH
                .Pin = EM_GPIO_LA_CH1 | EM_GPIO_LA_CH2 | EM_GPIO_LA_CH3 | EM_GPIO_LA_CH4,
            #else
                .Pin = EM_GPIO_LA_CH1 | EM_GPIO_LA_CH2,
            #endif

            .Speed = LL_GPIO_SPEED_FREQ_HIGH,
            .Mode = LL_GPIO_MODE_INPUT //LL_GPIO_MODE_FLOATING;
        };
        LL_GPIO_Init(EM_GPIO_LA_PORT, &GPIO_InitStruct);
    }

    // DAQ init
    if (mode == SCOPE)
    {
        daq_mem_set(self, 3); // safety guard
        daq_bit_set(self, self->save_s.bits);

        #ifdef EM_DAQ_4CH
            daq_ch_set(self, self->save_s.ch1_en, self->save_s.ch2_en, self->save_s.ch3_en, self->save_s.ch4_en, self->save_s.fs);
        #else
            daq_ch_set(self, self->save_s.ch1_en, self->save_s.ch2_en, EM_FALSE, EM_FALSE, self->save_s.fs);
        #endif

        daq_fs_set(self, self->save_s.fs);
        daq_mem_set(self, self->save_s.mem);
        daq_trig_set(self, self->trig.save_s.ch, self->trig.save_s.val_percent, self->trig.save_s.edge,
                     self->trig.save_s.mode, self->trig.save_s.pretrigger);
    }
    else if (mode == VM)
    {
        daq_mem_set(self, 3); // safety guard
        daq_bit_set(self, B12);

        #ifdef EM_DAQ_4CH
            daq_ch_set(self, EM_TRUE, EM_TRUE, EM_TRUE, EM_TRUE, EM_VM_FS);
        #else
            daq_ch_set(self, EM_TRUE, EM_TRUE, EM_FALSE, EM_FALSE, EM_VM_FS);
        #endif

        daq_mem_set(self, EM_VM_MEM);
        daq_fs_set(self, EM_VM_FS);
        daq_trig_set(self, 1, 0, RISING, DISABLED, 50);
        self->vm_seq = -1;
    }
    else // if (mode == LA)
    {
        daq_mem_set(self, 3); // safety guard
        daq_bit_set(self, self->save_l.bits);

        #ifdef EM_DAQ_4CH
            daq_ch_set(self, self->save_l.ch1_en, self->save_l.ch2_en, self->save_l.ch3_en, self->save_l.ch4_en, self->save_l.fs);
        #else
            daq_ch_set(self, self->save_l.ch1_en, self->save_l.ch2_en, EM_FALSE, EM_FALSE, self->save_l.fs);
        #endif

        daq_fs_set(self, self->save_l.fs);
        daq_mem_set(self, self->save_l.mem);
        daq_trig_set(self, self->trig.save_l.ch, self->trig.save_l.val_percent, self->trig.save_l.edge,
                     self->trig.save_l.mode, self->trig.save_l.pretrigger);
    }

    self->dis_hold = EM_FALSE;
    daq_enable(self, EM_TRUE);
    self->uwTick_start = self->uwTick;
}
