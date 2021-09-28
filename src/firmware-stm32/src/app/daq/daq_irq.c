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

static void la_irq_ch1(void);
static void la_irq_ch2(void);

#ifdef EM_DAQ_4CH
    static void la_irq_ch3(void);
    static void la_irq_ch4(void);
#endif

#ifdef EM_LA_EXTI_UNUSED
    static void la_irq_unused(void);
#endif


#if defined(EM_ADC1_USED) || defined(EM_ADC2_USED)
    void EM_ADC12_IRQh(void)
    {
        em_daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(em_daq.trig.buff_trig->len, em_daq.trig.dma_ch_trig, em_daq.trig.dma_trig); // critical

        traceISR_ENTER();
        uint8_t ret = -1;

    #ifdef EM_ADC1_USED
        if (LL_ADC_IsActiveFlag_AWD1(ADC1) == 1) // ADC1 AWD triggered
        {
            NVIC_DisableIRQ(em_daq.trig.adcirq_trig);
            LL_ADC_SetAnalogWDMonitChannels(em_daq.trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_DISABLE);

            ret = daq_trig_trigger_scope(&em_daq);
            LL_ADC_ClearFlag_AWD1(ADC1);
        }
    #endif

    #ifdef EM_ADC2_USED
        else if (LL_ADC_IsActiveFlag_AWD1(ADC2) == 1) // ADC2 AWD triggered
        {
            NVIC_DisableIRQ(em_daq.trig.adcirq_trig);
            LL_ADC_SetAnalogWDMonitChannels(em_daq.trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_DISABLE);

            ret = daq_trig_trigger_scope(&em_daq);
            LL_ADC_ClearFlag_AWD1(ADC2);
        }
    #endif

        //if (LL_ADC_IsActiveFlag_EOS(ADC1) == 1)
        //    LL_ADC_ClearFlag_EOS(ADC1);
        //if (LL_ADC_IsActiveFlag_EOS(ADC2) == 1)
        //    LL_ADC_ClearFlag_EOS(ADC2);

        if (ret == 0)
            traceISR_EXIT();
    }
#endif

#if defined(EM_ADC3_USED)
    void EM_ADC3_IRQh(void)
    {
        em_daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(em_daq.trig.buff_trig->len, em_daq.trig.dma_ch_trig, em_daq.trig.dma_trig); // critical

        traceISR_ENTER();
        uint8_t ret = -1;

        if (LL_ADC_IsActiveFlag_AWD1(ADC3) == 1) // ADC3 AWD triggered
        {
            NVIC_DisableIRQ(em_daq.trig.adcirq_trig);
            LL_ADC_SetAnalogWDMonitChannels(em_daq.trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_DISABLE);

            ret = daq_trig_trigger_scope(&em_daq);
            LL_ADC_ClearFlag_AWD1(ADC3);
        }

        //if (LL_ADC_IsActiveFlag_EOS(ADC3) == 1)
        //    LL_ADC_ClearFlag_EOS(ADC3);

        if (ret == 0)
            traceISR_EXIT();
    }
#endif

#if defined(EM_ADC4_USED)
    void EM_ADC4_IRQh(void)
    {
        em_daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(em_daq.trig.buff_trig->len, em_daq.trig.dma_ch_trig, em_daq.trig.dma_trig); // critical

        traceISR_ENTER();
        uint8_t ret = -1;

        if (LL_ADC_IsActiveFlag_AWD1(ADC4) == 1) // ADC4 AWD triggered
        {
            NVIC_DisableIRQ(em_daq.trig.adcirq_trig);
            LL_ADC_SetAnalogWDMonitChannels(em_daq.trig.adc_trig, EM_ADC_AWD LL_ADC_AWD_DISABLE);

            ret = daq_trig_trigger_scope(&em_daq);
            LL_ADC_ClearFlag_AWD1(ADC4);
        }

        //if (LL_ADC_IsActiveFlag_EOS(ADC4) == 1)
        //    LL_ADC_ClearFlag_EOS(ADC4);

        if (ret == 0)
            traceISR_EXIT();
    }
#endif

/************************************************************************************************************************/

#ifdef EM_LA_CH1_IRQh
    void EM_LA_CH1_IRQh(void)
    {
        em_daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(em_daq.trig.buff_trig->len, em_daq.trig.dma_ch_trig, EM_DMA_LA); // critical

        #ifdef EM_LA_IRQ1_CH1
            EM_LA_IRQ1_CH1();
        #endif
        #ifdef EM_LA_IRQ1_CH2
            EM_LA_IRQ1_CH2();
        #endif
        #ifdef EM_LA_IRQ1_CH3
            EM_LA_IRQ1_CH3();
        #endif
        #ifdef EM_LA_IRQ1_CH4
            EM_LA_IRQ1_CH4();
        #endif

    }
#endif

#ifdef EM_LA_CH2_IRQh
    void EM_LA_CH2_IRQh(void)
    {
        em_daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(em_daq.trig.buff_trig->len, em_daq.trig.dma_ch_trig, EM_DMA_LA); // critical

        #ifdef EM_LA_IRQ2_CH1
            EM_LA_IRQ2_CH1();
        #endif
        #ifdef EM_LA_IRQ2_CH2
            EM_LA_IRQ2_CH2();
        #endif
        #ifdef EM_LA_IRQ2_CH3
            EM_LA_IRQ2_CH3();
        #endif
        #ifdef EM_LA_IRQ2_CH4
            EM_LA_IRQ2_CH4();
        #endif
    }
#endif

#ifdef EM_LA_CH3_IRQh
    void EM_LA_CH3_IRQh(void)
    {
        em_daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(em_daq.trig.buff_trig->len, em_daq.trig.dma_ch_trig, EM_DMA_LA); // critical

        #ifdef EM_LA_IRQ3_CH1
            EM_LA_IRQ3_CH1();
        #endif
        #ifdef EM_LA_IRQ3_CH2
            EM_LA_IRQ3_CH2();
        #endif
        #ifdef EM_LA_IRQ3_CH3
            EM_LA_IRQ3_CH3();
        #endif
        #ifdef EM_LA_IRQ3_CH4
            EM_LA_IRQ3_CH4();
        #endif
    }
#endif

#ifdef EM_LA_CH4_IRQh
    void EM_LA_CH4_IRQh(void)
    {
        em_daq.trig.dma_pos_catched = EM_DMA_LAST_IDX(em_daq.trig.buff_trig->len, em_daq.trig.dma_ch_trig, EM_DMA_LA); // critical

        #ifdef EM_LA_IRQ4_CH1
            EM_LA_IRQ4_CH1();
        #endif
        #ifdef EM_LA_IRQ4_CH2
            EM_LA_IRQ4_CH2();
        #endif
        #ifdef EM_LA_IRQ4_CH3
            EM_LA_IRQ4_CH3();
        #endif
        #ifdef EM_LA_IRQ4_CH4
            EM_LA_IRQ4_CH4();
        #endif
    }
#endif

#ifdef EM_LA_EXTI_UNUSED
    void EM_LA_UNUSED_IRQh(void)
    {
        la_irq_unused();
    }
#endif

/************************************************************************************************************************/

void la_irq_ch1(void)
{
    traceISR_ENTER();
    uint8_t ret = -1;

    #ifdef EM_GPIO_EXTI_R_F
        if ((EM_GPIO_EXTI_ACTIVE_R(EM_LA_EXTI1) == 1) || (EM_GPIO_EXTI_ACTIVE_F(EM_LA_EXTI1) == 1))
    #else
        if (EM_GPIO_EXTI_ACTIVE_R(EM_LA_EXTI1) == 1)
    #endif
        {
            NVIC_DisableIRQ(EM_LA_IRQ_EXTI1);
            ret = daq_trig_trigger_la(&em_daq);
        }

    EM_GPIO_EXTI_CLEAR_R(EM_LA_EXTI1);

    #ifdef EM_GPIO_EXTI_R_F
        EM_GPIO_EXTI_CLEAR_F(EM_LA_EXTI1);
    #endif

    if (ret == 0)
        traceISR_EXIT();
}

void la_irq_ch2(void)
{
    traceISR_ENTER();
    uint8_t ret = -1;

    #ifdef EM_GPIO_EXTI_R_F
        if ((EM_GPIO_EXTI_ACTIVE_R(EM_LA_EXTI2) == 1) || (EM_GPIO_EXTI_ACTIVE_F(EM_LA_EXTI2) == 1))
    #else
        if (EM_GPIO_EXTI_ACTIVE_R(EM_LA_EXTI2) == 1)
    #endif
        {
            NVIC_DisableIRQ(EM_LA_IRQ_EXTI2);
            ret = daq_trig_trigger_la(&em_daq);
        }

    EM_GPIO_EXTI_CLEAR_R(EM_LA_EXTI2);

    #ifdef EM_GPIO_EXTI_R_F
        EM_GPIO_EXTI_CLEAR_F(EM_LA_EXTI2);
    #endif

    if (ret == 0)
        traceISR_EXIT();
}

#ifdef EM_DAQ_4CH
    void la_irq_ch3(void)
    {
        traceISR_ENTER();
        uint8_t ret = -1;

        #ifdef EM_GPIO_EXTI_R_F
            if ((EM_GPIO_EXTI_ACTIVE_R(EM_LA_EXTI3) == 1) || (EM_GPIO_EXTI_ACTIVE_F(EM_LA_EXTI3) == 1))
        #else
            if (EM_GPIO_EXTI_ACTIVE_R(EM_LA_EXTI3) == 1)
        #endif
            {
                NVIC_DisableIRQ(EM_LA_IRQ_EXTI3);
                ret = daq_trig_trigger_la(&em_daq);
            }

        EM_GPIO_EXTI_CLEAR_R(EM_LA_EXTI3);

        #ifdef EM_GPIO_EXTI_R_F
            EM_GPIO_EXTI_CLEAR_F(EM_LA_EXTI3);
        #endif

        if (ret == 0)
            traceISR_EXIT();
    }

    void la_irq_ch4(void)
    {
        traceISR_ENTER();
        uint8_t ret = -1;

        #ifdef EM_GPIO_EXTI_R_F
            if ((EM_GPIO_EXTI_ACTIVE_R(EM_LA_EXTI4) == 1) || (EM_GPIO_EXTI_ACTIVE_F(EM_LA_EXTI4) == 1))
        #else
            if (EM_GPIO_EXTI_ACTIVE_R(EM_LA_EXTI4) == 1)
        #endif
            {
                NVIC_DisableIRQ(EM_LA_IRQ_EXTI4);
                ret = daq_trig_trigger_la(&em_daq);
            }

        EM_GPIO_EXTI_CLEAR_R(EM_LA_EXTI4);

        #ifdef EM_GPIO_EXTI_R_F
            EM_GPIO_EXTI_CLEAR_F(EM_LA_EXTI4);
        #endif

        if (ret == 0)
            traceISR_EXIT();
    }
#endif

#ifdef EM_LA_EXTI_UNUSED
    void la_irq_unused(void)
    {
        traceISR_ENTER();

        #ifdef EM_GPIO_EXTI_R_F
            if ((EM_GPIO_EXTI_ACTIVE_R(EM_LA_EXTI_UNUSED) == 1) || (EM_GPIO_EXTI_ACTIVE_F(EM_LA_EXTI_UNUSED) == 1))
        #else
            if (EM_GPIO_EXTI_ACTIVE_R(EM_LA_EXTI_UNUSED) == 1)
        #endif
        {
        }

        EM_GPIO_EXTI_CLEAR_R(EM_LA_EXTI_UNUSED);

        #ifdef EM_GPIO_EXTI_R_F
            EM_GPIO_EXTI_CLEAR_F(EM_LA_EXTI_UNUSED);
        #endif

        traceISR_EXIT();
    }
#endif
