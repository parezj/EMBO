/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utility.h"
#include "cfg.h"
#include "periph.h"
#include "main.h"


static void dma_set(uint32_t src, DMA_TypeDef* dma, uint32_t dma_ch, uint16_t* buff, uint32_t buff_size, uint32_t sz);

static void adc_init();
static void adc_init_calib(ADC_TypeDef* adc);
static uint32_t adc_get_next_rank(uint32_t rank);
static void adc_set_ch(ADC_TypeDef* adc, uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint32_t smpl_time, uint8_t vrefint);
static void adc_set_res(ADC_TypeDef* adc, uint32_t resolution);
//static uint16_t adc_read(uint32_t ch);

static void daq_settings_save(daq_settings_t* src1, trig_settings_t* src2, daq_settings_t* dst1, trig_settings_t* dst2);
static void daq_settings_init(daq_data_t* self);
static void daq_enable_adc(daq_data_t* self, ADC_TypeDef* adc, uint8_t enable);
static void daq_malloc(daq_buff_t* buff, int mem, int chans, uint32_t src, uint32_t dma_ch, enum daq_bits bits);
static void daq_clear_buff(daq_buff_t* buff);
static void daq_enable_adc(daq_data_t* self, ADC_TypeDef* adc, uint8_t enable);


/************************* DMA  *************************/


static void dma_set(uint32_t src, DMA_TypeDef* dma, uint32_t dma_ch, uint16_t* buff, uint32_t buff_size, uint32_t sz)
{
    LL_DMA_DisableChannel(dma, dma_ch);
    // Select ADC as DMA transfer request.
    //LL_DMAMUX_SetRequestID(DMAMUX1, LL_DMAMUX_CHANNEL_0, LL_DMAMUX_REQ_ADC1);

    // DMA transfer addresses and size.
    LL_DMA_ConfigAddresses(dma, dma_ch, src,
                           (uint32_t)buff,
                           LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    LL_DMA_SetPeriphSize(dma, dma_ch, sz);
    LL_DMA_SetDataLength(dma, dma_ch, buff_size);

    //LL_DMA_EnableIT_TC(dma, dma_ch); // Enable transfer complete interrupt.
    //LL_DMA_EnableIT_HT(dma, dma_ch); // Enable half transfer interrupt.
    //LL_DMA_EnableIT_TE(dma, dma_ch); // Enable transfer error interrupt.

    // Enable
    LL_DMA_EnableChannel(dma, dma_ch);
}

/************************* ADC  *************************/

/*
static uint16_t adc_read(uint32_t ch)
{
    LL_ADC_REG_StartConversionSWStart(ADC2);

    while(LL_ADC_IsActiveFlag_EOS(ADC2) == 0);
    if( LL_ADC_IsActiveFlag_EOS(ADC2) )
        LL_ADC_ClearFlag_EOS(ADC2);

    return LL_ADC_REG_ReadConversionData12(ADC2);
}
*/

static void adc_init()
{
#ifdef PS_ADC_MODE_ADC1
    adc_init_calib(ADC1);
#endif

#ifdef PS_ADC_MODE_ADC12
    adc_init_calib(ADC2);
#endif

#ifdef PS_ADC_MODE_ADC1234
    adc_init_calib(ADC3);
    adc_init_calib(ADC4);
#endif
}

static void adc_init_calib(ADC_TypeDef* adc)
{
    LL_ADC_Enable(adc);
    adc->CR2 |= ADC_CR2_TSVREFE;

    uint32_t  wait_loop_index = ((LL_ADC_DELAY_ENABLE_CALIB_ADC_CYCLES * 32) >> 1);
    while(wait_loop_index != 0)
    {
      wait_loop_index--;
    }

    //LL_ADC_EnableInternalRegulator(adc);
    //LL_ADC_DisableDeepPowerDown(adc);
    //for (int i = 0; i <  1000; ++i) asm("nop");

    //LL_ADC_Disable(adc);
    const uint32_t dma_tx_mode = LL_ADC_REG_GetDMATransfer(adc);
    LL_ADC_REG_SetDMATransfer(adc, LL_ADC_REG_DMA_TRANSFER_NONE);

    LL_ADC_StartCalibration(adc);
    while (LL_ADC_IsCalibrationOnGoing(adc) != 0);

    for (int i = 0; i <  1000; ++i) asm("nop");

    LL_ADC_REG_SetDMATransfer(adc, dma_tx_mode);
    //LL_ADC_Enable(adc);
}

static void adc_set_ch(ADC_TypeDef* adc, uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint32_t smpl_time, uint8_t vrefint)
{
    //LL_ADC_Disable(adc);
    int len = ch1 + ch2 + ch3 + ch4 + vrefint;

    uint32_t len_raw = LL_ADC_REG_SEQ_SCAN_DISABLE;
    if (len == 2)
        len_raw = LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS;
    if (len == 3)
        len_raw = LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS;
    else if (len == 4)
        len_raw = LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS;
    else if (len == 5)
        len_raw = LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS;

    LL_ADC_REG_SetSequencerLength(adc, len_raw);

    uint32_t next_rank = LL_ADC_REG_RANK_1;

    if (vrefint)
    {
        LL_ADC_REG_SetSequencerRanks(adc, next_rank, LL_ADC_CHANNEL_VREFINT);
        LL_ADC_SetChannelSamplingTime(adc, LL_ADC_CHANNEL_VREFINT, PS_ADC_SMPL_TIME);
        next_rank = adc_get_next_rank(next_rank);
    }
    if (ch1) {
        LL_ADC_REG_SetSequencerRanks(adc, next_rank, PS_ADC_CH1);
        LL_ADC_SetChannelSamplingTime(adc, PS_ADC_CH1, PS_ADC_SMPL_TIME);
        next_rank = adc_get_next_rank(next_rank);
    }
    if (ch2) {
        LL_ADC_REG_SetSequencerRanks(adc, next_rank, PS_ADC_CH2);
        LL_ADC_SetChannelSamplingTime(adc, PS_ADC_CH2, PS_ADC_SMPL_TIME);
        next_rank = adc_get_next_rank(next_rank);
    }
    if (ch3) {
        LL_ADC_REG_SetSequencerRanks(adc, next_rank, PS_ADC_CH3);
        LL_ADC_SetChannelSamplingTime(adc, PS_ADC_CH3, PS_ADC_SMPL_TIME);
        next_rank = adc_get_next_rank(next_rank);
    }
    if (ch4) {
        LL_ADC_REG_SetSequencerRanks(adc, next_rank, PS_ADC_CH4);
        LL_ADC_SetChannelSamplingTime(adc, PS_ADC_CH4, PS_ADC_SMPL_TIME);
        next_rank = adc_get_next_rank(next_rank);
    }

    //LL_ADC_Enable(adc);
}

static uint32_t adc_get_next_rank(uint32_t rank)
{
    if (rank == LL_ADC_REG_RANK_2)
        return LL_ADC_REG_RANK_3;
    else if (rank == LL_ADC_REG_RANK_3)
        return LL_ADC_REG_RANK_4;
    else if (rank == LL_ADC_REG_RANK_4)
        return LL_ADC_REG_RANK_5;
    else
        return LL_ADC_REG_RANK_6;
}

static void adc_set_res(ADC_TypeDef* adc, uint32_t resolution) // LL_ADC_RESOLUTION_12B, LL_ADC_RESOLUTION_8B
{
    //LL_ADC_Disable(adc);
#ifdef PS_ADC_BIT8
    LL_ADC_SetResolution(adc, resolution);
#endif
    //LL_ADC_Enable(adc);
}

// ************************** LED *********************************

void led_init(led_data_t* self)
{
    self->blink_cntr = 0;
    self->blink_len = 0;
    self->blink_cntr = 0;
    self->enabled = 0;
}

void led_set(led_data_t* self, uint8_t enable)
{
    self->enabled = enable;
    if (!self->enabled)
        PS_LED_PORT->BSRR |= (1 << PS_LED_PIN);  // 1
    else
        PS_LED_PORT->BRR |= (1 << PS_LED_PIN);   // 0
}

void led_toggle(led_data_t* self)
{
    if (self->enabled)
        PS_LED_PORT->BSRR |= (1 << PS_LED_PIN);  // 1
    else
        PS_LED_PORT->BRR |= (1 << PS_LED_PIN);   // 0
    self->enabled = !self->enabled;
}

void led_blink_set(led_data_t* self, int num, int len)
{
    self->blink_num = (num * 2) - 1;
    self->blink_len = len;
    self->blink_cntr = len;
    led_set(self, 1);
}

void led_blink_do(led_data_t* self)
{
    if (self->blink_num > 0)
    {
        if (self->blink_cntr > 0)
            self->blink_cntr--;
        else
        {
            self->blink_cntr = self->blink_len;
            self->blink_num--;
            led_toggle(self);
        }
    }
}

/************************** cntr *********************************/

void cntr_init(cntr_data_t* self)
{
    size_t ln = PS_CNTR_BUFF_SZ * sizeof(uint16_t);
    self->data = (uint16_t*) malloc(ln);
    self->data_len = PS_CNTR_BUFF_SZ;
    self->freq = 0;
    self->ovf = 0;
    self->enabled = 0;
    memset(self->data, 0, ln);
    dma_set((uint32_t)&PS_TIM_CNTR->CCR1, DMA1, PS_DMA_CNTR, self->data, PS_CNTR_BUFF_SZ, LL_DMA_PDATAALIGN_HALFWORD);
}

void cntr_enable(cntr_data_t* self, uint8_t enable)
{
    if (enable)
    {
        LL_TIM_EnableCounter(PS_TIM_CNTR);
        LL_TIM_CC_EnableChannel(PS_TIM_CNTR, LL_TIM_CHANNEL_CH1);
    }
    else
    {
        LL_TIM_DisableCounter(PS_TIM_CNTR);
        LL_TIM_CC_DisableChannel(PS_TIM_CNTR, LL_TIM_CHANNEL_CH1);
    }
    self->enabled = enable;
}

/************************** PWM *********************************/

void pwm_init(pwm_data_t* self)
{
    self->enabled_ch1 = 0;
    self->enabled_ch2 = 0;
}

void pwm_set(pwm_data_t* self, int ch, float freq, float duty) // TODO NEMENIT FREKVENCI pro ruzne kanaly, omezit PRESCALER!!!!!!!!!!!!§
{
    ASSERT(ch >= 1 && ch <= 2);

    // TODO Disable Counter ??
    LL_TIM_CC_DisableChannel(PS_TIM_PWM, (ch == 1 ? LL_TIM_CHANNEL_CH1 : LL_TIM_CHANNEL_CH2));

    int prescaler = 1;
    int reload = 0;
    self->freq = get_freq(&prescaler, &reload, PS_TIM_PWM_MAX, PS_TIM_PWM_FREQ, freq);

    LL_TIM_SetAutoReload(PS_TIM_PWM, reload);
    if (prescaler > 1)
        LL_TIM_SetPrescaler(PS_TIM_PWM, prescaler);

    int compare = (duty / (float)100) * reload;
    float real_duty = ((float)compare / (float)reload) * (float)100;
    if (ch == 1)
    {
        self->duty_ch1 = real_duty;
        LL_TIM_OC_SetCompareCH1(PS_TIM_PWM, compare);
        if (self->enabled_ch1)
            LL_TIM_CC_EnableChannel(PS_TIM_PWM, LL_TIM_CHANNEL_CH1);
    }
    else // if (param1 == 2)
    {
        self->duty_ch2 = real_duty;
        LL_TIM_OC_SetCompareCH2(PS_TIM_PWM, compare);
        if (self->enabled_ch2)
            LL_TIM_CC_EnableChannel(PS_TIM_PWM, LL_TIM_CHANNEL_CH2);
    }

    // TODO EnableCounter ??
}

void pwm_enable(pwm_data_t* self, uint8_t ch, uint8_t enable)
{
    // TODO
}

/************************** trigger *********************************/

void daq_trig_init(daq_data_t* self)
{
    self->trig.ignore = 0;
    self->trig.ready = 0;
    self->trig.cntr = 0;
    self->trig.ch_reg = 0;
    self->trig.all_cntr = 0;
    self->trig.pos_frst = 0;
    self->trig.pos_trig = 0;
    self->trig.pos_last = 0;
    self->trig.pos_diff = 0;
    self->trig.uwtick_last = 0;
    self->trig.pretrig_cntr = 0;
    self->trig.is_post = 0;
    self->trig.posttrig_size = 0;
    self->trig.pretrig_val = 0;
    self->trig.fullmem_val = 0;
    self->trig.buff_trig = NULL;
    self->trig.dma_trig = PS_DMA_ADC1;
    self->trig.exti_trig = PS_LA_IRQ_EXTI1;
}

void daq_trig_check(daq_data_t* self)
{
    //NVIC_DisableIRQ(ADC1_2_IRQn); // TODO disable all ADCs / DMA ?

    if (uwTick >= self->trig.uwtick_last)
        self->trig.pretrig_cntr += uwTick - self->trig.uwtick_last;
    else
        self->trig.pretrig_cntr += (uwTick - self->trig.uwtick_last) + 4294967295;

    self->trig.uwtick_last = uwTick;

    if (self->trig.set.mode == AUTO &&
        self->trig.is_post == 0 &&
        self->trig.ready == 0 &&
        self->trig.pretrig_cntr >= self->trig.pretrig_val + PS_AUTRIG_SYSTCKS)
    {
        daq_trig_trigger(self, -1, -1);
    }
    else if (self->trig.set.mode == DISABLED &&
             self->trig.pretrig_cntr >= self->trig.fullmem_val)
    {
        //daq_enable(self, 0);
        //self->trig.pretrig_cntr = 0;
        self->trig.ready = 1;
    }
    //NVIC_EnableIRQ(ADC1_2_IRQn);
}

void daq_trig_trigger_scope(daq_data_t* self)
{
    ASSERT(self->trig.buff_trig != NULL);
    ASSERT(self->trig.dma_trig != 0);

    int last_idx = PS_DMA_LAST_IDX(self->trig.buff_trig->len, self->trig.dma_trig);

    if (self->trig.ready)
        return;

    int prev_last_idx = last_idx - self->trig.buff_trig->chans;
    if (prev_last_idx < 0)
        prev_last_idx += self->trig.buff_trig->len;

    uint16_t last_val = 0;
    uint16_t prev_last_val = 0;

    if (self->set.bits == B8)
    {
        last_val = (uint16_t)(((uint8_t*)(self->trig.buff_trig->data))[last_idx]);
        prev_last_val = (uint16_t)(((uint8_t*)(self->trig.buff_trig->data))[prev_last_idx]);
    }
    else
    {
        last_val = ((uint16_t*)(self->trig.buff_trig->data))[last_idx];
        prev_last_val = ((uint16_t*)(self->trig.buff_trig->data))[prev_last_idx];
    }

    /*
    if (tignore)
    {
        tignore = 0;

        uint32_t h = LL_ADC_GetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_HIGH);
        uint32_t l = LL_ADC_GetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_LOW);

        LL_ADC_SetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_HIGH, l);
        LL_ADC_SetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_LOW, h);
    }
    else
    {
    */
        // trigger condition
        if ((self->trig.set.edge == RISING && last_val > self->trig.set.val && prev_last_val <= self->trig.set.val) ||
            (self->trig.set.edge == FALLING && last_val < self->trig.set.val && prev_last_val >= self->trig.set.val))
        {
            if (self->trig.pretrig_cntr > self->trig.pretrig_val) // pretrigger counter
            {
                self->trig.pretrig_cntr = 0;
                daq_trig_trigger(self, last_idx, last_idx);
            }
        }
        self->trig.all_cntr++;

        /*
        //else // false trig, switch edges and wait for another window
        //{
            tignore = 1;

            uint32_t h = LL_ADC_GetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_HIGH);
            uint32_t l = LL_ADC_GetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_LOW);

            LL_ADC_SetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_HIGH, l);
            LL_ADC_SetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_LOW, h);
            trig_false_cntr++;
        //}
         */
    //}
}

void daq_trig_trigger_la(daq_data_t* self)
{
    ASSERT(self->trig.buff_trig != NULL);
    ASSERT(self->trig.dma_trig != 0);

    int last_idx = PS_DMA_LAST_IDX(self->trig.buff_trig->len, self->trig.dma_trig);

    if (self->trig.ready)
        return;

    if (self->trig.pretrig_cntr > self->trig.pretrig_val)
    {
        self->trig.pretrig_cntr = 0;
        daq_trig_trigger(self, last_idx, last_idx);
    }
}

void daq_trig_trigger(daq_data_t* self, int pos, int last_idx)
{
    ASSERT(self->trig.buff_trig != NULL);

    if (pos == -1)
    {
        last_idx = PS_DMA_LAST_IDX(self->trig.buff_trig->len, self->trig.dma_trig);
    }

    self->trig.is_post = 1;
    self->trig.cntr++;
    self->trig.pos_trig = last_idx;
    self->trig.posttrig_size = (int)((float)self->trig.buff_trig->len * ((float)(100 - self->trig.set.pretrigger) / 100.0));
    self->trig.pos_frst = last_idx - (int)((float)self->trig.buff_trig->len * ((float)self->trig.set.pretrigger / 100.0));

    if (self->trig.pos_frst < 0)
        self->trig.pos_frst += self->trig.buff_trig->len;

    if (self->mode != LA)
    {
#ifdef PS_ADC_MODE_ADC1
        LL_ADC_SetAnalogWDMonitChannels(ADC1, LL_ADC_AWD_DISABLE);
#endif

#ifdef PS_ADC_MODE_ADC12
        LL_ADC_SetAnalogWDMonitChannels(ADC2, LL_ADC_AWD_DISABLE);
#endif

#ifdef PS_ADC_MODE_ADC1234
        LL_ADC_SetAnalogWDMonitChannels(ADC3, LL_ADC_AWD_DISABLE);
        LL_ADC_SetAnalogWDMonitChannels(ADC4, LL_ADC_AWD_DISABLE);
#endif
    }
    else
    {
        NVIC_DisableIRQ(self->trig.exti_trig);
    }

    // start timer - count posttriger (half buffer)

    //LL_TIM_EnableCounter(PS_TIM_TRIG);
    //LL_TIM_CC_EnableChannel(PS_TIM_TRIG, LL_TIM_CHANNEL_CH1);
    LL_TIM_EnableIT_CC1(PS_TIM_ADC);
    self->trig.pretrig_cntr = 0;
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
       (ch < 0 || ch > 4) ||
       (pretrigger > 99 || pretrigger < 1))
    {
        return -1;
    }

    //int reen = 0;
    //if (self->enabled)
    //{
    //    reen = 1;
        daq_enable(self, 0);
        daq_reset(self);
    //}

#if defined(PS_ADC_MODE_ADC1)

    ADC_TypeDef* adc = ADC1;
    self->trig.buff_trig = &self->buff1;
    self->trig.dma_trig = PS_DMA_ADC1;

#elif defined(PS_ADC_MODE_ADC12)

    uint32_t adc = ADC1;
    self->trig.buff_trig = &self->buff1;
    self->trig.dma_trig = PS_DMA_ADC1;
    if (ch == 3 || ch == 4)
    {
        adc = ADC2;
        self->trig.buff_trig = &self->buff2;
        self->trig.dma_trig = PS_DMA_ADC2;
    }

#elif defined(PS_ADC_MODE_ADC1234)

    uint32_t adc = ADC1;
    self->trig.buff_trig = &self->buff1;
    self->trig.dma_trig = PS_DMA_ADC1;
    if (ch == 2)
    {
        adc = ADC2;
        self->trig.buff_trig = &self->buff2;
        self->trig.dma_trig = PS_DMA_ADC2;
    }
    else if (ch == 3)
    {
        adc = ADC3;
        self->trig.buff_trig = &self->buff3;
        self->trig.dma_trig = PS_DMA_ADC3;
    }
    else // if (ch == 4)
    {
        adc = ADC4;
        self->trig.buff_trig = &self->buff4;
        self->trig.dma_trig = PS_DMA_ADC4;
    }

#endif

    self->trig.fullmem_val = (int)(((1.0 / (float)self->set.fs) * (float)self->set.mem) * (float)PS_SYSTICK_FREQ); // ?

    if (ch == 0 || mode == DISABLED)
    {
        ASSERT(self->trig.exti_trig != 0);

        NVIC_DisableIRQ(self->trig.exti_trig);
        LL_ADC_SetAnalogWDMonitChannels(adc, LL_ADC_AWD_DISABLE);

        self->trig.set.ch = 0;
        self->trig.set.mode = DISABLED;
        return 0;
    }

    if (self->mode == LA)
    {
        self->trig.buff_trig = &self->buff1;
        self->trig.dma_trig = PS_DMA_LA;

        LL_ADC_SetAnalogWDMonitChannels(adc, LL_ADC_AWD_DISABLE);

        LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
        uint32_t extiline = 0;
        uint32_t exti = 0;

        if (self->set.ch1_en)
        {
            self->trig.exti_trig = PS_LA_IRQ_EXTI1;
            extiline = PS_LA_EXTILINE1;
            exti = PS_LA_EXTI1;
        }
        else if (self->set.ch2_en)
        {
            self->trig.exti_trig = PS_LA_IRQ_EXTI2;
            extiline = PS_LA_EXTILINE2;
            exti = PS_LA_EXTI2;
        }
        else if (self->set.ch3_en)
        {
            self->trig.exti_trig = PS_LA_IRQ_EXTI3;
            extiline = PS_LA_EXTILINE3;
            exti = PS_LA_EXTI3;
        }
        else // if (self->set.ch4_en)
        {
            self->trig.exti_trig = PS_LA_IRQ_EXTI4;
            extiline = PS_LA_EXTILINE4;
            exti = PS_LA_EXTI4;
        }

        LL_GPIO_AF_SetEXTISource(PS_LA_EXTI_PORT, extiline);

        EXTI_InitStruct.Line_0_31 = exti;
        EXTI_InitStruct.LineCommand = ENABLE;
        EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
        EXTI_InitStruct.Trigger = (self->trig.set.edge == RISING ? LL_EXTI_TRIGGER_RISING : LL_EXTI_TRIGGER_FALLING);
        LL_EXTI_Init(&EXTI_InitStruct);

        NVIC_SetPriority(self->trig.exti_trig, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
        NVIC_EnableIRQ(self->trig.exti_trig);

        self->trig.set.val = 0;
        self->trig.set.val_percent = 0;
    }
    else
    {
        ASSERT(self->trig.exti_trig != 0);
        NVIC_DisableIRQ(self->trig.exti_trig);

        if ((ch == 1 && self->set.ch1_en) ||
            (ch == 2 && self->set.ch2_en) ||
            (ch == 3 && self->set.ch3_en) ||
            (ch == 4 && self->set.ch4_en))
        {
            if (ch == 1)
                self->trig.ch_reg = PS_ADC_AWD1;
            else if (ch == 2)
                self->trig.ch_reg = PS_ADC_AWD2;
            else if (ch == 3)
                self->trig.ch_reg = PS_ADC_AWD3;
            else if (ch == 4)
                self->trig.ch_reg = PS_ADC_AWD4;

            LL_ADC_SetAnalogWDMonitChannels(adc, self->trig.ch_reg);

            uint32_t level_raw;
            uint32_t level_max;
            if (self->set.bits == B12)
                level_max = 4095;
            else // B8
                level_max = 255;

            level_raw = (int)((float)level_max / 100.0 * (float)level);

            if (edge == RISING)
            {
                LL_ADC_SetAnalogWDThresholds(adc, LL_ADC_AWD_THRESHOLD_HIGH, level);
                LL_ADC_SetAnalogWDThresholds(adc, LL_ADC_AWD_THRESHOLD_LOW, 0);
            }
            else // (edge == FALLING)
            {
                LL_ADC_SetAnalogWDThresholds(adc, LL_ADC_AWD_THRESHOLD_HIGH, level_max);
                LL_ADC_SetAnalogWDThresholds(adc, LL_ADC_AWD_THRESHOLD_LOW, level);
            }

            self->trig.set.val = level_raw;
            self->trig.set.val_percent = level;
        }
        else return -1;

        self->trig.pretrig_val = (int)((float)self->trig.fullmem_val * ((float)pretrigger / 100.0));
        self->trig.set.pretrigger = pretrigger;
        self->trig.set.mode = mode;
        self->trig.set.edge = edge;
        self->trig.set.ch = ch;
    }


    daq_enable(self, 1);
    return 0;
}

/************************** DAQ *********************************/

void daq_init(daq_data_t* self)
{
    daq_trig_init(self);
    daq_settings_init(self);
    daq_settings_save(&self->save_s, &self->trig.save_s, &self->set, &self->trig.set);
    self->mode = SCOPE;

    daq_clear_buff(&self->buff1);
    daq_clear_buff(&self->buff2);
    daq_clear_buff(&self->buff3);
    daq_clear_buff(&self->buff4);
    daq_clear_buff(&self->buff_out);
    self->trig.buff_trig = NULL;

    self->enabled = 0;
    self->dis_hold = 0;

    adc_init();
}

static void daq_settings_save(daq_settings_t* src1, trig_settings_t* src2, daq_settings_t* dst1, trig_settings_t* dst2)
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

static void daq_settings_init(daq_data_t* self)
{
    // SCOPE
    self->save_s.fs = 1000;
    self->save_s.mem = 500;
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

    // LA
    self->save_l.fs = 100000;
    self->save_l.mem = 1000;
    self->save_l.bits = B1;

    self->save_l.ch1_en = 1;
    self->save_l.ch2_en = 1;
    self->save_l.ch3_en = 1;
    self->save_l.ch4_en = 1;

    self->trig.save_s.val_percent = 0;
    self->trig.save_l.val = 0;
    self->trig.save_l.ch = 1;
    self->trig.save_l.edge = RISING;
    self->trig.save_l.mode = AUTO;
    self->trig.save_l.pretrigger = 50;
}

int daq_mem_set(daq_data_t* self, uint16_t mem_per_ch)
{
    //int reen = 0;
    //if (self->enabled)
    //{
    //    reen = 1;
        daq_enable(self, 0);
        daq_reset(self);
    //}

    daq_clear_buff(&self->buff1);
    daq_clear_buff(&self->buff2);
    daq_clear_buff(&self->buff3);
    daq_clear_buff(&self->buff4);
    daq_clear_buff(&self->buff_out);

    int max_len = PS_DAQ_MAX_MEM;
    int out_per_ch = mem_per_ch;
    if (self->set.bits == B12)
    {
        max_len /= 2;
        out_per_ch *= 2;
    }

    if (self->mode != LA)
    {
#if defined(PS_ADC_MODE_ADC1)

        int len1 = self->set.ch1_en + self->set.ch2_en + self->set.ch3_en + self->set.ch4_en + 1;

        //                            DMA ADC            UART / USB OUT
        if (mem_per_ch < 0 || (mem_per_ch * len1) + (mem_per_ch * len1 - 1) > max_len)
            return -2;

        self->buff_out.chans = len1 - 1;
        self->buff_out.len = out_per_ch * (len1 - 1);
        self->buff_out.data = malloc(self->buff_out.len * sizeof(uint8_t));

        daq_malloc(&self->buff1, mem_per_ch * len1, len1, PS_ADC_ADDR(ADC1), PS_DMA_ADC1, self->set.bits);

#elif defined(PS_ADC_MODE_ADC12)

        int len1 = self->set.ch1_en + self->set.ch2_en + 1;
        int len2 = self->set.ch3_en + self->set.ch4_en;
        int total = len1 + len2;

        if (mem_per_ch < 0 || (mem_per_ch * total) + (mem_per_ch * total - 1) > max_len)
            return -2;

        self->buff_out.chans = total - 1;
        self->buff_out.len = out_per_ch * (total - 1);
        self->buff_out.data = malloc(self->buff_out.len * sizeof(uint8_t));

        daq_malloc(&self->buff1, mem_per_ch * len1, len1, PS_ADC_ADDR(ADC1), PS_DMA_ADC1, self->set.bits);
        daq_malloc(&self->buff2, mem_per_ch * len2, len2, PS_ADC_ADDR(ADC2), PS_DMA_ADC2, self->set.bits);

#elif defined(PS_ADC_MODE_ADC1234)

        int len1 = self->set.ch1_en + 1;
        int len2 = self->set.ch3_en;
        int len3 = self->set.ch3_en;
        int len4 = self->set.ch3_en;
        int total = len1 + len2 + len3 + len4;

        if (mem_per_ch < 0 || (mem_per_ch * total) + (mem_per_ch * total - 1) > max_len)
            return -2;

        self->buff_out.chans = total - 1;
        self->buff_out.len = out_per_ch * (total - 1);
        self->buff_out.data = malloc(self->buff_out.len * sizeof(uint8_t));

        daq_malloc(&self->buff1, mem_per_ch * len1, len1, PS_ADC_ADDR(ADC1), PS_DMA_ADC1, self->set.bits);
        daq_malloc(&self->buff2, mem_per_ch * len2, len2, PS_ADC_ADDR(ADC2), PS_DMA_ADC2, self->set.bits);
        daq_malloc(&self->buff3, mem_per_ch * len3, len3, PS_ADC_ADDR(ADC3), PS_DMA_ADC3, self->set.bits);
        daq_malloc(&self->buff4, mem_per_ch * len4, len4, PS_ADC_ADDR(ADC4), PS_DMA_ADC4, self->set.bits);

#endif
    }
    else
    {
        if (mem_per_ch < 0 || mem_per_ch > max_len)
            return -2;

        self->buff_out.chans = 4;
        self->buff_out.len = mem_per_ch;
        self->buff_out.data = malloc(mem_per_ch * sizeof(uint8_t));

        daq_malloc(&self->buff1, mem_per_ch, 4, PS_DAQ_PORT->ODR, PS_DMA_LA, self->set.bits);
    }

    self->set.mem = mem_per_ch;

    daq_trig_update(self);

    //if (reen)
        daq_enable(self, 1);
    return 0;
}

static void daq_malloc(daq_buff_t* buff, int mem, int chans, uint32_t src, uint32_t dma_ch, enum daq_bits bits)
{
    if (bits == B12)
    {
        size_t ln = mem * sizeof(uint16_t);
        buff->data = (uint16_t*) malloc(ln);
        buff->chans = chans;
        buff->len = mem;
        memset(buff->data, 0, ln);
        dma_set(src, DMA1, dma_ch, buff->data, mem, LL_DMA_PDATAALIGN_HALFWORD);
    }
    else if (bits == B8)
    {
        size_t ln = mem * sizeof(uint8_t);
        buff->data = (uint8_t*) malloc(ln);
        buff->chans = chans;
        buff->len = mem;
        memset(buff->data, 0, ln);
        dma_set(src, DMA1, dma_ch, buff->data, mem, LL_DMA_PDATAALIGN_BYTE);
    }
    else // if (bits == B1)
    {
        size_t ln = mem * sizeof(uint8_t);
        buff->data = (uint8_t*) malloc(ln);
        buff->chans = chans;
        buff->len = mem;
        memset(buff->data, 0, ln);
        dma_set(src, DMA1, PS_DMA_LA, buff->data, mem, LL_DMA_PDATAALIGN_BYTE);
    }
}

static void daq_clear_buff(daq_buff_t* buff)
{
    buff->chans = 0;
    buff->len = 0;
    if (buff->data != NULL)
        free(buff->data);
}

int daq_bit_set(daq_data_t* self, enum daq_bits bits)
{
    if (bits != B12 && bits != B8 && bits != B1)
        return -1;

    self->set.bits = bits;
    if (self->mode == SCOPE || self->mode == VM)
    {
        //int reen = 0;
        //if (self->enabled)
        //{
        //    reen = 1;
            daq_enable(self, 0);
            daq_reset(self);
        //}

        uint32_t bits_raw = LL_ADC_RESOLUTION_12B;
#ifdef PS_ADC_BIT8
        if (bits == B8)
            bits_raw = LL_ADC_RESOLUTION_8B;
#endif

#ifdef PS_ADC_MODE_ADC1
        adc_set_res(ADC1, bits_raw);
#endif

#ifdef PS_ADC_MODE_ADC12
        adc_set_res(ADC2, bits_raw);
#endif

#ifdef PS_ADC_MODE_ADC1234
        adc_set_res(ADC3, bits_raw);
        adc_set_res(ADC4, bits_raw);
#endif
        int ret = daq_mem_set(self, self->set.mem);

        //if (reen)
            daq_enable(self, 1);

        return ret;
    }
    return 0;
}

int daq_fs_set(daq_data_t* self, float fs)
{
    if (fs < 0 || fs > PS_DAQ_MAX_FS)
        return -1;

    self->set.fs = fs;
    //int reen = 0;
    //if (self->enabled)
    //{
    //    reen = 1;
        daq_enable(self, 0);
        daq_reset(self);
    //}

    int prescaler = 1;
    int reload = 1;
    self->set.fs = get_freq(&prescaler, &reload, PS_TIM_ADC_MAX, PS_TIM_ADC_FREQ, fs);

    LL_TIM_SetPrescaler(PS_TIM_ADC, prescaler);
    LL_TIM_SetAutoReload(PS_TIM_ADC, reload);
    //LL_TIM_SetPrescaler(PS_TIM_TRIG, prescaler); // maybe not needed
    //LL_TIM_SetAutoReload(PS_TIM_TRIG, reload);

    daq_trig_update(self);

    //if (reen)
        daq_enable(self, 1);
    return 0;
}

int daq_ch_set(daq_data_t* self, uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4)
{
    self->set.ch1_en = ch1;
    self->set.ch2_en = ch2;
    self->set.ch3_en = ch3;
    self->set.ch4_en = ch4;

    int reen = 0;
    if (self->enabled)
    {
        reen = 1;
        daq_enable(self, 0);
        daq_reset(self);
    }

    if (self->mode != LA)
    {
#if defined(PS_ADC_MODE_ADC1)
        adc_set_ch(ADC1, ch1, ch2, ch3, ch4, PS_ADC_SMPL_TIME, 1);
#elif defined(PS_ADC_MODE_ADC12)
        adc_set_ch(ADC1, ch1, ch2, 0, 0, PS_ADC_SMPL_TIME, 1);
        adc_set_ch(ADC2, 0, 0, ch3, ch4, PS_ADC_SMPL_TIME, 0);
#elif defined(PS_ADC_MODE_ADC1234)
        adc_set_ch(ADC1, ch1, 0, 0, 0, PS_ADC_SMPL_TIME, 1);
        adc_set_ch(ADC2, 0, ch2, 0, 0, PS_ADC_SMPL_TIME, 0);
        adc_set_ch(ADC1, 0, 0, ch3, 0, PS_ADC_SMPL_TIME, 0);
        adc_set_ch(ADC2, 0, 0, 0, ch4, PS_ADC_SMPL_TIME, 0);
#endif
    }

    int ret = daq_mem_set(self, self->set.mem);

    if (reen)
        daq_enable(self, 1);
    return ret;
}

void daq_reset(daq_data_t* self)
{
    LL_TIM_DisableCounter(PS_TIM_TRIG);
    self->trig.ready = 0;
    self->trig.cntr = 0;
    self->trig.all_cntr = 0;
    //self->trig.pos_frst = 0;
    //self->trig.pos_trig = 0;
    //self->trig.pos_last = 0;
    //self->trig.pos_diff = 0;
    self->trig.pretrig_cntr = 0;
    self->trig.is_post = 0;

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
    if (self->enabled && self->dis_hold)
        return;

    if (self->mode == SCOPE || self->mode == VM)
    {
#ifdef PS_ADC_MODE_ADC1
        daq_enable_adc(self, ADC1, enable);
#endif

#ifdef PS_ADC_MODE_ADC12
        daq_enable_adc(self, ADC2, enable);
#endif

#ifdef PS_ADC_MODE_ADC1234
        daq_enable_adc(self, ADC3, enable);
        daq_enable_adc(self, ADC4, enable);
#endif
    }
    else //if(self->mode == LA)
    {
        ASSERT(self->trig.exti_trig != 0);

        if (enable)
        {
            LL_DMA_EnableChannel(DMA1, PS_DMA_LA);
            if (self->trig.set.mode != DISABLED)
                NVIC_EnableIRQ(self->trig.exti_trig);
        }
        else
        {
            LL_DMA_DisableChannel(DMA1, PS_DMA_LA);
            NVIC_DisableIRQ(self->trig.exti_trig);
        }
    }

    if (enable)
        LL_TIM_EnableCounter(PS_TIM_ADC);
    else
        LL_TIM_EnableCounter(PS_TIM_ADC);
    self->enabled = enable;
}

static void daq_enable_adc(daq_data_t* self, ADC_TypeDef* adc, uint8_t enable)
{
    if (enable)
    {
        LL_ADC_REG_StartConversionExtTrig(adc, LL_ADC_REG_TRIG_EXT_RISING);
        if (self->trig.set.mode != DISABLED)
        {
            ASSERT(self->trig.ch_reg != 0);
            LL_ADC_SetAnalogWDMonitChannels(adc, self->trig.ch_reg);
        }
    }
    else
    {
        LL_ADC_REG_StopConversionExtTrig(adc);
        LL_ADC_SetAnalogWDMonitChannels(adc, LL_ADC_AWD_DISABLE);
    }
}

void daq_mode_set(daq_data_t* self, enum daq_mode mode)
{
    if (self->mode == SCOPE)
        daq_settings_save(&self->set, &self->trig.set, &self->save_s, &self->trig.save_s);
    else if (self->mode == LA)
        daq_settings_save(&self->set, &self->trig.set, &self->save_l, &self->trig.save_l);

    self->mode = mode;
    //int reen = 0;
    //if (self->enabled)
    //{
    //    reen = 1;
        daq_enable(self, 0);
        daq_trig_disable(self);
        daq_reset(self);
        self->dis_hold = 1;
    //}

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PS_DAQ_CH1 | PS_DAQ_CH2 | PS_DAQ_CH3 | PS_DAQ_CH4;

    if (mode == SCOPE) // save settings
    {
        GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
        LL_GPIO_Init(PS_DAQ_PORT, &GPIO_InitStruct);

        daq_mem_set(self, 3); // safety guard
        daq_bit_set(self, self->save_s.bits);
        daq_ch_set(self, self->save_s.ch1_en, self->save_s.ch2_en, self->save_s.ch3_en, self->save_s.ch4_en);
        daq_fs_set(self, self->save_s.fs);
        daq_mem_set(self, self->save_s.mem);
        daq_trig_set(self, self->trig.save_s.ch, self->trig.save_s.val, self->trig.save_s.edge,
                     self->trig.save_s.mode, self->trig.save_s.pretrigger);
    }
    else if (mode == VM)
    {
        GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
        LL_GPIO_Init(PS_DAQ_PORT, &GPIO_InitStruct);

        daq_mem_set(self, 3); // safety guard
        daq_bit_set(self, B12);
        daq_ch_set(self, 1, 1, 1, 1);
        daq_mem_set(self, 200);
        daq_fs_set(self, 100);
        daq_trig_set(self, 0, 0, RISING, DISABLED, 50);
    }
    else // if (mode == LA)
    {
        GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
        LL_GPIO_Init(PS_DAQ_PORT, &GPIO_InitStruct);

        daq_mem_set(self, 3); // safety guard
        daq_bit_set(self, self->save_l.bits);
        daq_ch_set(self, self->save_l.ch1_en, self->save_l.ch2_en, self->save_l.ch3_en, self->save_l.ch4_en);
        daq_fs_set(self, self->save_l.fs);
        daq_mem_set(self, self->save_l.mem);
        daq_trig_set(self, self->trig.save_l.ch, self->trig.save_l.val, self->trig.save_l.edge,
                     self->trig.save_l.mode, self->trig.save_l.pretrigger);
    }

    //if (reen)
    self->dis_hold = 0;
    daq_enable(self, 1);
}
