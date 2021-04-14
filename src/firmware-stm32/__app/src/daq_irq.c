/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"

#include "app_data.h"
#include "main.h"

#include "FreeRTOS.h"
#include "semphr.h"


void ADC1_2_IRQHandler(void)
{
    daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(daq.trig.buff_trig->len, daq.trig.dma_ch_trig, daq.trig.dma_trig); // critical
    ASSERT(!(LL_ADC_IsActiveFlag_AWD1(ADC1) && LL_ADC_IsActiveFlag_AWD1(ADC2)));

    if (LL_ADC_IsActiveFlag_AWD1(ADC1) == 1)
    {
        LL_ADC_SetAnalogWDMonitChannels(daq.trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_DISABLE);
        daq_trig_trigger_scope(&daq);
        LL_ADC_ClearFlag_AWD1(ADC1);
    }
    else if (LL_ADC_IsActiveFlag_AWD1(ADC2) == 1)
    {
        LL_ADC_SetAnalogWDMonitChannels(daq.trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_DISABLE);
        daq_trig_trigger_scope(&daq);
        LL_ADC_ClearFlag_AWD1(ADC2);
    }
}

#if defined(EM_ADC_MODE_ADC1234)
void ADC3_IRQHandler(void)
{
    daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(daq.trig.buff_trig->len, daq.trig.dma_ch_trig, daq.trig.dma_trig); // critical

    if (LL_ADC_IsActiveFlag_AWD1(ADC3) == 1)
    {
        LL_ADC_SetAnalogWDMonitChannels(daq.trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_DISABLE);
        daq_trig_trigger_scope(&daq);
        LL_ADC_ClearFlag_AWD1(ADC3);
    }
}

void ADC4_IRQHandler(void)
{
    daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(daq.trig.buff_trig->len, daq.trig.dma_ch_trig, daq.trig.dma_trig); // critical

    if (LL_ADC_IsActiveFlag_AWD1(ADC4) == 1)
    {
        LL_ADC_SetAnalogWDMonitChannels(daq.trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_DISABLE);
        daq_trig_trigger_scope(&daq);
        LL_ADC_ClearFlag_AWD1(ADC4);
    }
}
#endif

void EM_LA_CH1_IRQh(void)
{
    daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(daq.trig.buff_trig->len, daq.trig.dma_ch_trig, EM_DMA_LA); // critical

    daq.trig.la_state = 0;

    if (LL_EXTI_IsActiveFlag_0_31(EM_LA_EXTI1) == 1)
    {
        daq.trig.la_state = 1;

        NVIC_DisableIRQ(EM_LA_IRQ_EXTI1);
        daq_trig_trigger_la(&daq);
    }
    LL_EXTI_ClearFlag_0_31(EM_LA_EXTI1);
}

void EM_LA_CH2_IRQh(void)
{
    daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(daq.trig.buff_trig->len, daq.trig.dma_ch_trig, EM_DMA_LA); // critical

    if (LL_EXTI_IsActiveFlag_0_31(EM_LA_EXTI2) == 1)
    {
        NVIC_DisableIRQ(EM_LA_IRQ_EXTI2);
        daq_trig_trigger_la(&daq);
    }
    LL_EXTI_ClearFlag_0_31(EM_LA_EXTI2);
}

void EM_LA_CH3_IRQh(void)
{
    daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(daq.trig.buff_trig->len, daq.trig.dma_ch_trig, EM_DMA_LA); // critical

    if (LL_EXTI_IsActiveFlag_0_31(EM_LA_EXTI3) == 1)
    {
        NVIC_DisableIRQ(EM_LA_IRQ_EXTI3);
        daq_trig_trigger_la(&daq);
    }
    LL_EXTI_ClearFlag_0_31(EM_LA_EXTI3);
}

void EM_LA_CH4_IRQh(void)
{
    daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(daq.trig.buff_trig->len, daq.trig.dma_ch_trig, EM_DMA_LA); // critical

    if (LL_EXTI_IsActiveFlag_0_31(EM_LA_EXTI4) == 1)
    {
        NVIC_DisableIRQ(EM_LA_IRQ_EXTI4);
        daq_trig_trigger_la(&daq);
    }
    LL_EXTI_ClearFlag_0_31(EM_LA_EXTI4);
}

void EM_LA_UNUSED_IRQh(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(EM_LA_EXTI_UNUSED) == 1)
    {
    }
    LL_EXTI_ClearFlag_0_31(EM_LA_EXTI_UNUSED);
}

