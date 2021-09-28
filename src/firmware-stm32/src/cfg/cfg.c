/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"

/* sampling time datasheet values */

#if defined(STM32F103xB)

    #include "stm32f1xx_ll_adc.h"

    const uint32_t EM_ADC_SMPLT[EM_ADC_SMPLT_CNT] = { LL_ADC_SAMPLINGTIME_1CYCLE_5, LL_ADC_SAMPLINGTIME_7CYCLES_5, LL_ADC_SAMPLINGTIME_13CYCLES_5,
                                                      LL_ADC_SAMPLINGTIME_28CYCLES_5, LL_ADC_SAMPLINGTIME_41CYCLES_5, LL_ADC_SAMPLINGTIME_55CYCLES_5,
                                                      LL_ADC_SAMPLINGTIME_71CYCLES_5, LL_ADC_SAMPLINGTIME_239CYCLES_5};
    const float EM_ADC_SMPLT_N[EM_ADC_SMPLT_CNT]  = { 1.5, 7.5, 13.5, 28.5, 41.5, 55.5, 71.5, 239.5};

#elif defined (STM32F103xE)

    #include "stm32f1xx_ll_adc.h"

    const uint32_t EM_ADC_SMPLT[EM_ADC_SMPLT_CNT] = { LL_ADC_SAMPLINGTIME_1CYCLE_5, LL_ADC_SAMPLINGTIME_7CYCLES_5, LL_ADC_SAMPLINGTIME_13CYCLES_5,
                                                      LL_ADC_SAMPLINGTIME_28CYCLES_5, LL_ADC_SAMPLINGTIME_41CYCLES_5, LL_ADC_SAMPLINGTIME_55CYCLES_5,
                                                      LL_ADC_SAMPLINGTIME_71CYCLES_5, LL_ADC_SAMPLINGTIME_239CYCLES_5};
    const float EM_ADC_SMPLT_N[EM_ADC_SMPLT_CNT]  = { 1.5, 7.5, 13.5, 28.5, 41.5, 55.5, 71.5, 239.5};

#elif defined (STM32F303xE)

    #include "stm32f3xx_ll_adc.h"

    const uint32_t EM_ADC_SMPLT[EM_ADC_SMPLT_CNT] = { LL_ADC_SAMPLINGTIME_1CYCLE_5, LL_ADC_SAMPLINGTIME_2CYCLES_5, LL_ADC_SAMPLINGTIME_4CYCLES_5,
                                                      LL_ADC_SAMPLINGTIME_7CYCLES_5, LL_ADC_SAMPLINGTIME_19CYCLES_5, LL_ADC_SAMPLINGTIME_61CYCLES_5,
                                                      LL_ADC_SAMPLINGTIME_181CYCLES_5, LL_ADC_SAMPLINGTIME_601CYCLES_5};
    const float EM_ADC_SMPLT_N[EM_ADC_SMPLT_CNT]  = { 1.5, 2.5, 4.5, 7.5, 19.5, 61.5, 181.5, 601.5};

#elif defined (STM32L412xx)

    #include "stm32l4xx_ll_adc.h"

    const uint32_t EM_ADC_SMPLT[EM_ADC_SMPLT_CNT] = { LL_ADC_SAMPLINGTIME_2CYCLES_5, LL_ADC_SAMPLINGTIME_6CYCLES_5, LL_ADC_SAMPLINGTIME_12CYCLES_5,
                                                      LL_ADC_SAMPLINGTIME_24CYCLES_5, LL_ADC_SAMPLINGTIME_47CYCLES_5, LL_ADC_SAMPLINGTIME_92CYCLES_5,
                                                      LL_ADC_SAMPLINGTIME_247CYCLES_5, LL_ADC_SAMPLINGTIME_640CYCLES_5};
    const float EM_ADC_SMPLT_N[EM_ADC_SMPLT_CNT]  = { 2.5, 6.5, 12.5, 24.5, 47.5, 92.5, 247.5, 640.5};

#elif defined (STM32G031xx)

    #include "stm32g0xx_ll_adc.h"

    const uint32_t EM_ADC_SMPLT[EM_ADC_SMPLT_CNT] = { LL_ADC_SAMPLINGTIME_1CYCLE_5, LL_ADC_SAMPLINGTIME_3CYCLES_5, LL_ADC_SAMPLINGTIME_7CYCLES_5,
                                                      LL_ADC_SAMPLINGTIME_12CYCLES_5, LL_ADC_SAMPLINGTIME_19CYCLES_5, LL_ADC_SAMPLINGTIME_39CYCLES_5,
                                                      LL_ADC_SAMPLINGTIME_79CYCLES_5, LL_ADC_SAMPLINGTIME_160CYCLES_5};
    const float EM_ADC_SMPLT_N[EM_ADC_SMPLT_CNT]  = { 1.5, 3.5, 7.5, 12.5, 19.5, 39.5, 79.5, 160.5};

#elif defined (STM32G431xx)

    #include "stm32g4xx_ll_adc.h"

    const uint32_t EM_ADC_SMPLT[EM_ADC_SMPLT_CNT] = { LL_ADC_SAMPLINGTIME_2CYCLES_5, LL_ADC_SAMPLINGTIME_6CYCLES_5, LL_ADC_SAMPLINGTIME_12CYCLES_5,
                                                      LL_ADC_SAMPLINGTIME_24CYCLES_5, LL_ADC_SAMPLINGTIME_47CYCLES_5, LL_ADC_SAMPLINGTIME_92CYCLES_5,
                                                      LL_ADC_SAMPLINGTIME_247CYCLES_5, LL_ADC_SAMPLINGTIME_640CYCLES_5};
    const float EM_ADC_SMPLT_N[EM_ADC_SMPLT_CNT]  = { 2.5, 6.5, 12.5, 24.5, 47.5, 92.5, 247.5, 640.5};

#endif

