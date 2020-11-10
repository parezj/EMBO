/*
 * CTU/UniLabTool project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>


#include "cfg.h"
#include "periph.h"
#include "main.h"



/************************* DMA  *************************/


void dma_init(ADC_TypeDef* adc, DMA_TypeDef* dma, uint32_t dma_ch, uint16_t* buff, uint32_t buff_size)
{
    // Select ADC as DMA transfer request.
    //LL_DMAMUX_SetRequestID(DMAMUX1, LL_DMAMUX_CHANNEL_0, LL_DMAMUX_REQ_ADC1);

    // DMA transfer addresses and size.
    LL_DMA_ConfigAddresses(dma, dma_ch,
                           LL_ADC_DMA_GetRegAddr(adc, LL_ADC_DMA_REG_REGULAR_DATA),
                           (uint32_t)buff,
                           LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    LL_DMA_SetDataLength(dma, dma_ch, buff_size);

    //LL_DMA_EnableIT_TC(dma, dma_ch); // Enable transfer complete interrupt.
    //LL_DMA_EnableIT_HT(dma, dma_ch); // Enable half transfer interrupt.
    //LL_DMA_EnableIT_TE(dma, dma_ch); // Enable transfer error interrupt.

    // Enable
    LL_DMA_EnableChannel(dma, dma_ch);
}

/************************* ADC  *************************/

uint16_t adc_read(uint32_t ch) // DEBUG
{
    LL_ADC_REG_StartConversionSWStart(ADC2);

    while(LL_ADC_IsActiveFlag_EOS(ADC2) == 0);
    if( LL_ADC_IsActiveFlag_EOS(ADC2) )
        LL_ADC_ClearFlag_EOS(ADC2);

    return LL_ADC_REG_ReadConversionData12(ADC2);
}

void adc_init(ADC_TypeDef* adc)
{
    //LL_ADC_Disable(adc);
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

    const uint32_t dma_tx_mode = LL_ADC_REG_GetDMATransfer(adc);
    LL_ADC_REG_SetDMATransfer(adc, LL_ADC_REG_DMA_TRANSFER_NONE);

    LL_ADC_StartCalibration(adc);
    while (LL_ADC_IsCalibrationOnGoing(adc) != 0);

    for (int i = 0; i <  1000; ++i) asm("nop");

    LL_ADC_REG_SetDMATransfer(adc, dma_tx_mode);
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
        ULT_LED_PORT->BSRR |= (1 << ULT_LED_PIN);  // 1
    else
        ULT_LED_PORT->BRR |= (1 << ULT_LED_PIN);   // 0
}

void led_toggle(led_data_t* self)
{
    if (self->enabled)
        ULT_LED_PORT->BSRR |= (1 << ULT_LED_PIN);  // 1
    else
        ULT_LED_PORT->BRR |= (1 << ULT_LED_PIN);   // 0
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

/************************** PWM *********************************/

void pwm_init(pwm_data_t* self)
{
    self->enabled_ch1 = 0;
    self->enabled_ch2 = 0;
}

void pwm_set(pwm_data_t* self, int ch, float freq, float duty)
{
    assert(ch >= 1 && ch <= 2);

    // TODO Disable Counter ??
    LL_TIM_CC_DisableChannel(ULT_TIM_PWM, (ch == 1 ? LL_TIM_CHANNEL_CH1 : LL_TIM_CHANNEL_CH2));

    int prescaler = 1;
    int max_reload = pow(2, ULT_PWM_BITS);
    int pwm_osc = ULT_TIM_PWM_FREQ;
    int reload;

    do
    {
        reload = (float)pwm_osc / freq;
        if (reload > max_reload)
        {
            prescaler++;
            pwm_osc = ULT_TIM_PWM_FREQ / prescaler;
        }
    }
    while (reload > max_reload);

    self->freq = (float)ULT_TIM_PWM_FREQ / (float)prescaler / (float)reload;

    LL_TIM_SetAutoReload(ULT_TIM_PWM, reload);
    if (prescaler > 1)
        LL_TIM_SetPrescaler(ULT_TIM_PWM, prescaler);

    int compare = (duty / (float)100) * reload;
    float real_duty = ((float)compare / (float)reload) * (float)100;
    if (ch == 1)
    {
        self->duty_ch1 = real_duty;
        LL_TIM_OC_SetCompareCH1(ULT_TIM_PWM, compare);
        if (self->enabled_ch1)
            LL_TIM_CC_EnableChannel(ULT_TIM_PWM, LL_TIM_CHANNEL_CH1);
    }
    else // if (param1 == 2)
    {
        self->duty_ch2 = real_duty;
        LL_TIM_OC_SetCompareCH2(ULT_TIM_PWM, compare);
        if (self->enabled_ch2)
            LL_TIM_CC_EnableChannel(ULT_TIM_PWM, LL_TIM_CHANNEL_CH2);
    }

    // TODO EnableCounter ??
}

/************************** trigger *********************************/

void trig_init(trig_data_t* self)
{
    self->ignore = 0;
    self->ready = 0;
    self->cntr = 0;
    self->all_cntr = 0;
    self->pos_frst = 0;
    self->pos_trig = 0;
    self->pos_last = 0;
    self->pos_diff = 0;
    self->uwtick_last = 0;
    self->pretrig_cntr = 0;
}

void trig_set(trig_data_t* self, ADC_TypeDef* adc, uint32_t ch, uint16_t level, enum trig_edge edge, enum trig_mode mode)
{
    assert(level > 0 && level < 4095);
    self->val = level;

    if (ch == LL_ADC_AWD_DISABLE)
    {
        LL_ADC_SetAnalogWDMonitChannels(adc, LL_ADC_AWD_DISABLE);
        return;
    }

    LL_ADC_SetAnalogWDMonitChannels(adc, ch);

    if (edge == RISING)
    {
        LL_ADC_SetAnalogWDThresholds(adc, LL_ADC_AWD_THRESHOLD_HIGH, level);
        LL_ADC_SetAnalogWDThresholds(adc, LL_ADC_AWD_THRESHOLD_LOW, 0);
    }
    else // (edge == FALLING)
    {
        LL_ADC_SetAnalogWDThresholds(adc, LL_ADC_AWD_THRESHOLD_HIGH, 4095);
        LL_ADC_SetAnalogWDThresholds(adc, LL_ADC_AWD_THRESHOLD_LOW, level);
    }

    self->mode = mode;
    self->edge = edge;
    self->ch = ch;
}

void trig_pre_post_set(trig_data_t* self, enum trig_pre_post pre_post) // merge with up?
{

}

/************************** DAQ *********************************/

void daq_init(daq_data_t* self)
{
    self->fs = 1000;
    self->mem = 500;
    self->bits = B12;

    self->buff1 = NULL;
    self->buff2 = NULL;

    self->enabled = 0;
}

void daq_mem_set(daq_data_t* self, uint16_t mem_per_ch)
{

}

void daq_bit_set(daq_data_t* self, enum daq_bits bits)
{

}

void daq_fs_set(daq_data_t* self, uint32_t fs)
{

}

void daq_ch_set(daq_data_t* self, uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4)
{

}

void daq_enable(daq_data_t* self, uint8_t mode, uint8_t enable)
{
    //if (mode == 0 || mode == 2)
    //{
#ifdef ULT_ADC1
    if (enable)
        LL_ADC_REG_StartConversionExtTrig(ADC1, LL_ADC_REG_TRIG_EXT_RISING);
    else
        LL_ADC_REG_StopConversionExtTrig(ADC1);
#endif

#ifdef ULT_ADC2
    if (enable)
        LL_ADC_REG_StartConversionExtTrig(ADC2, LL_ADC_REG_TRIG_EXT_RISING);
    else
        LL_ADC_REG_StopConversionExtTrig(ADC2);
#endif
    //}
    self->enabled = enable;
}
