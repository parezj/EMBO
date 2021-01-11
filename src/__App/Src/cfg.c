/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"

#if defined(STM32F103xB)

#include "stm32f1xx_ll_adc.h"

const uint32_t PS_ADC_SMPLT[PS_ADC_SMPLT_CNT] = { LL_ADC_SAMPLINGTIME_1CYCLE_5, LL_ADC_SAMPLINGTIME_7CYCLES_5, LL_ADC_SAMPLINGTIME_13CYCLES_5,
                                                  LL_ADC_SAMPLINGTIME_28CYCLES_5, LL_ADC_SAMPLINGTIME_41CYCLES_5, LL_ADC_SAMPLINGTIME_55CYCLES_5,
                                                  LL_ADC_SAMPLINGTIME_71CYCLES_5, LL_ADC_SAMPLINGTIME_239CYCLES_5};
const float PS_ADC_SMPLT_N[PS_ADC_SMPLT_CNT]  = { 1.5, 7.5, 13.5, 28.5, 41.5, 55.5, 71.5, 239.5};

#elif defined (STM32F303xE)

#include "stm32f3xx_ll_adc.h"

const uint32_t PS_ADC_SMPLT[PS_ADC_SMPLT_CNT] = { LL_ADC_SAMPLINGTIME_1CYCLE_5, LL_ADC_SAMPLINGTIME_2CYCLES_5, LL_ADC_SAMPLINGTIME_4CYCLES_5,
                                                  LL_ADC_SAMPLINGTIME_7CYCLES_5, LL_ADC_SAMPLINGTIME_19CYCLES_5, LL_ADC_SAMPLINGTIME_61CYCLES_5,
                                                  LL_ADC_SAMPLINGTIME_181CYCLES_5, LL_ADC_SAMPLINGTIME_601CYCLES_5};
const float PS_ADC_SMPLT_N[PS_ADC_SMPLT_CNT]  = { 1.5, 2.5, 4.5, 7.5, 19.5, 61.5, 181.5, 601.5};

#endif