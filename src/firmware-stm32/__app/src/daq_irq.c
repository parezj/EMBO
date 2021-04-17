/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"

#include "app_data.h"
#include "main.h"

#include "FreeRTOS.h"
#include "semphr.h"

#ifdef EM_SYSVIEW
#include "SEGGER_SYSVIEW.h"
#endif


void ADC1_2_IRQHandler(void)
{
    daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(daq.trig.buff_trig->len, daq.trig.dma_ch_trig, daq.trig.dma_trig); // critical
    ASSERT(!(LL_ADC_IsActiveFlag_AWD1(ADC1) && LL_ADC_IsActiveFlag_AWD1(ADC2)));

    traceISR_ENTER();
    uint8_t ret = -1;

    if (LL_ADC_IsActiveFlag_AWD1(ADC1) == 1)
    {
        LL_ADC_SetAnalogWDMonitChannels(daq.trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_DISABLE);
        ret = daq_trig_trigger_scope(&daq);
        LL_ADC_ClearFlag_AWD1(ADC1);
    }
    else if (LL_ADC_IsActiveFlag_AWD1(ADC2) == 1)
    {
        LL_ADC_SetAnalogWDMonitChannels(daq.trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_DISABLE);
        ret = daq_trig_trigger_scope(&daq);
        LL_ADC_ClearFlag_AWD1(ADC2);
    }

    if (ret == 0)
        traceISR_EXIT();
}

#if defined(EM_ADC_MODE_ADC1234)
void ADC3_IRQHandler(void)
{
    daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(daq.trig.buff_trig->len, daq.trig.dma_ch_trig, daq.trig.dma_trig); // critical

    traceISR_ENTER();
    uint8_t ret = -1;

    if (LL_ADC_IsActiveFlag_AWD1(ADC3) == 1)
    {
        LL_ADC_SetAnalogWDMonitChannels(daq.trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_DISABLE);
        ret = daq_trig_trigger_scope(&daq);
        LL_ADC_ClearFlag_AWD1(ADC3);
    }

    if (ret == 0)
        traceISR_EXIT();
}

void ADC4_IRQHandler(void)
{
    daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(daq.trig.buff_trig->len, daq.trig.dma_ch_trig, daq.trig.dma_trig); // critical

    traceISR_ENTER();
    uint8_t ret = -1;

    if (LL_ADC_IsActiveFlag_AWD1(ADC4) == 1)
    {
        LL_ADC_SetAnalogWDMonitChannels(daq.trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_DISABLE);
        ret = daq_trig_trigger_scope(&daq);
        LL_ADC_ClearFlag_AWD1(ADC4);
    }

    if (ret == 0)
        traceISR_EXIT();
}
#endif

void EM_LA_CH1_IRQh(void)
{
    daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(daq.trig.buff_trig->len, daq.trig.dma_ch_trig, EM_DMA_LA); // critical

    daq.trig.la_state = 0;

    traceISR_ENTER();
    uint8_t ret = -1;

    if (LL_EXTI_IsActiveFlag_0_31(EM_LA_EXTI1) == 1)
    {
        daq.trig.la_state = 1;

        NVIC_DisableIRQ(EM_LA_IRQ_EXTI1);
        ret = daq_trig_trigger_la(&daq);
    }
    LL_EXTI_ClearFlag_0_31(EM_LA_EXTI1);

    if (ret == 0)
        traceISR_EXIT();
}

void EM_LA_CH2_IRQh(void)
{
    daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(daq.trig.buff_trig->len, daq.trig.dma_ch_trig, EM_DMA_LA); // critical

    traceISR_ENTER();
    uint8_t ret = -1;

    if (LL_EXTI_IsActiveFlag_0_31(EM_LA_EXTI2) == 1)
    {
        NVIC_DisableIRQ(EM_LA_IRQ_EXTI2);
        ret = daq_trig_trigger_la(&daq);
    }
    LL_EXTI_ClearFlag_0_31(EM_LA_EXTI2);

    if (ret == 0)
        traceISR_EXIT();
}

void EM_LA_CH3_IRQh(void)
{
    daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(daq.trig.buff_trig->len, daq.trig.dma_ch_trig, EM_DMA_LA); // critical

    traceISR_ENTER();
    uint8_t ret = -1;

    if (LL_EXTI_IsActiveFlag_0_31(EM_LA_EXTI3) == 1)
    {
        NVIC_DisableIRQ(EM_LA_IRQ_EXTI3);
        ret = daq_trig_trigger_la(&daq);
    }
    LL_EXTI_ClearFlag_0_31(EM_LA_EXTI3);

    if (ret == 0)
        traceISR_EXIT();
}

void EM_LA_CH4_IRQh(void)
{
    daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(daq.trig.buff_trig->len, daq.trig.dma_ch_trig, EM_DMA_LA); // critical

    traceISR_ENTER();
    uint8_t ret = -1;

    if (LL_EXTI_IsActiveFlag_0_31(EM_LA_EXTI4) == 1)
    {
        NVIC_DisableIRQ(EM_LA_IRQ_EXTI4);
        ret = daq_trig_trigger_la(&daq);
    }
    LL_EXTI_ClearFlag_0_31(EM_LA_EXTI4);

    if (ret == 0)
        traceISR_EXIT();
}

void EM_LA_UNUSED_IRQh(void)
{
    traceISR_ENTER();

    if (LL_EXTI_IsActiveFlag_0_31(EM_LA_EXTI_UNUSED) == 1)
    {
    }
    LL_EXTI_ClearFlag_0_31(EM_LA_EXTI_UNUSED);

    traceISR_EXIT();
}

