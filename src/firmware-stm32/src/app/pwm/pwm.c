/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"
#include "pwm.h"

#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef EMBO
    #define EM_TRUE                1
    #define EM_FALSE               0
    #define EM_TIM_PWM1            TIM2
    #define EM_TIM_PWM1_MAX        65535
    #define EM_TIM_PWM1_FREQ       EM_FREQ_PCLK1
    #define EM_TIM_PWM1_CH         LL_TIM_CHANNEL_CH1
    #define EM_TIM_PWM1_CHN(a)     a##CH1
    #define EM_TIM_PWM2            TIM4
    #define EM_TIM_PWM2_MAX        65535
    #define EM_TIM_PWM2_FREQ       EM_FREQ_PLLCLK2_x2
    #define EM_TIM_PWM2_CH         LL_TIM_CHANNEL_CH3
    #define EM_TIM_PWM2_CHN(a)     a##CH3
    #define EM_PWM_MAX_F           16000000   // PWM max freq
#endif

void pwm_init(pwm_data_t* self)
{
    self->ch1.enabled = EM_FALSE;
    self->ch2.enabled = EM_FALSE;
    self->ch1.freq = 1000;
    self->ch2.freq = 1000;
    self->ch1.duty = 50;
    self->ch2.duty = 50;
    self->ch1.freq_real = 1000;
    self->ch2.freq_real = 1000;
}

void pwm_disable(pwm_data_t* self)
{
    LL_TIM_DisableCounter(EM_TIM_PWM1);
    #ifdef EM_TIM_PWM2
        LL_TIM_DisableCounter(EM_TIM_PWM2);
    #endif
    self->ch1.enabled = EM_FALSE;
    self->ch2.enabled = EM_FALSE;
}

int pwm_set(pwm_data_t* self, int freq, int duty1, int duty2, int offset2, int enable1, int enable2)
{
    if (freq <= 0 || freq > EM_PWM_MAX_F || duty1 < 0 || duty1 > 100 ||
        duty2 < 0 || duty2 > 100 || offset2 < 0 || offset2 > 100)
    {
        return -1;
    }

    LL_TIM_DisableCounter(EM_TIM_PWM1);
    #ifdef EM_TIM_PWM2
        LL_TIM_DisableCounter(EM_TIM_PWM2);
    #endif

    int prescaler = 1;
    int reload = 0;

    self->ch1.enabled = enable1;
    self->ch1.freq = freq;
    self->ch1.freq_real = get_freq(&prescaler, &reload, EM_TIM_PWM1_MAX, EM_TIM_PWM1_FREQ, freq);
    self->ch1.prescaler = prescaler;
    self->ch1.reload = reload;
    self->ch1.offset = 0;

    self->ch2.enabled = enable2;
    self->ch2.freq = self->ch1.freq;
    self->ch2.prescaler = prescaler;
    self->ch2.reload = reload;
    self->ch2.offset = offset2;

    LL_TIM_SetAutoReload(EM_TIM_PWM1, reload);
    LL_TIM_SetPrescaler(EM_TIM_PWM1, prescaler);
    #ifdef EM_TIM_PWM2
        LL_TIM_SetAutoReload(EM_TIM_PWM2, reload);
        LL_TIM_SetPrescaler(EM_TIM_PWM2, prescaler);
    #endif

    int compare1 = (duty1 / (double)100) * reload;
    //double real_duty1 = ((double)compare1 / (double)reload) * 100.0;
    #ifdef EM_TIM_PWM2
        int compare2 = (duty2 / (double)100) * reload;
        //double real_duty2 = ((double)compare2 / (double)reload) * 100.0;
    #endif
    //self->ch1.duty = real_duty1;
    //self->ch2.duty = real_duty2;
    self->ch1.duty = duty1;
    self->ch1.compare = compare1;
    #ifdef EM_TIM_PWM2
        self->ch2.duty = duty2;
        self->ch2.compare = compare2;
    #endif

    EM_TIM_PWM1_CHN(LL_TIM_OC_SetCompare)(EM_TIM_PWM1, compare1);
    LL_TIM_SetCounter(EM_TIM_PWM1, 0);
    
    #ifdef EM_TIM_PWM2
        EM_TIM_PWM2_CHN(LL_TIM_OC_SetCompare)(EM_TIM_PWM2, compare2);
        LL_TIM_SetCounter(EM_TIM_PWM2, 0);

        // http://www.micromouseonline.com/2016/02/05/clock-pulses-with-variable-phase-stm32/
        if (offset2 > 0)
            LL_TIM_SetCounter(EM_TIM_PWM2, (int)((double)offset2 / 100.0 * (double)reload));
    #endif

    if (enable1 == EM_TRUE)
        LL_TIM_CC_EnableChannel(EM_TIM_PWM1, EM_TIM_PWM1_CH);
    else
        LL_TIM_CC_DisableChannel(EM_TIM_PWM1, EM_TIM_PWM1_CH);

    #ifdef EM_TIM_PWM2
        if (enable2 == EM_TRUE)
            LL_TIM_CC_EnableChannel(EM_TIM_PWM2, EM_TIM_PWM2_CH);
        else
            LL_TIM_CC_DisableChannel(EM_TIM_PWM2, EM_TIM_PWM2_CH);
    #endif

    LL_TIM_EnableCounter(EM_TIM_PWM1);

    return 0;
}
