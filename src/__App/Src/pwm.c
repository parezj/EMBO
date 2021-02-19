/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "pwm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "cfg.h"
#include "main.h"


void pwm_init(pwm_data_t* self)
{
    self->ch1.enabled = 0;
    self->ch2.enabled = 0;
    self->ch1.freq = 1000;
    self->ch2.freq = 1000;
    self->ch1.duty = 50;
    self->ch2.duty = 50;
}

int pwm_set(pwm_data_t* self, int freq, int duty1, int duty2, int offset2, int enable1, int enable2)
{
    if (freq <= 0 || freq > PS_PWM_MAX_F || duty1 < 0 || duty1 > 100 ||
        duty2 < 0 || duty2 > 100 || offset2 < 0 || offset2 > 100)
    {
        return -1;
    }

    LL_TIM_DisableCounter(PS_TIM_PWM1);
    LL_TIM_DisableCounter(PS_TIM_PWM2);

    if (!enable1)
        return 0;

    int prescaler = 1;
    int reload = 0;

    self->ch1.enabled = enable1;
    self->ch1.freq = get_freq(&prescaler, &reload, PS_TIM_PWM1_MAX, PS_TIM_PWM1_FREQ, freq);
    self->ch1.prescaler = prescaler;
    self->ch1.reload = reload;
    self->ch1.offset = 0;

    self->ch2.enabled = enable2;
    self->ch2.freq = self->ch1.freq;
    self->ch2.prescaler = prescaler;
    self->ch2.reload = reload;
    self->ch2.offset = offset2;

    LL_TIM_SetAutoReload(PS_TIM_PWM1, reload);
    LL_TIM_SetAutoReload(PS_TIM_PWM2, reload);
    LL_TIM_SetPrescaler(PS_TIM_PWM1, prescaler);
    LL_TIM_SetPrescaler(PS_TIM_PWM2, prescaler);

    int compare1 = (duty1 / (float)100) * reload;
    float real_duty1 = ((float)compare1 / (float)reload) * (float)100;

    int compare2 = (duty2 / (float)100) * reload;
    float real_duty2 = ((float)compare2 / (float)reload) * (float)100;

    self->ch1.duty = real_duty1;
    self->ch2.duty = real_duty2;

    LL_TIM_OC_SetCompareCH1(PS_TIM_PWM1, compare1);
    LL_TIM_OC_SetCompareCH1(PS_TIM_PWM2, compare2);
    
    LL_TIM_SetCounter(PS_TIM_PWM1, 0);
    LL_TIM_SetCounter(PS_TIM_PWM2, 0);

    // http://www.micromouseonline.com/2016/02/05/clock-pulses-with-variable-phase-stm32/
    if (offset2 > 0)
        LL_TIM_SetCounter(PS_TIM_PWM2, (int)((float)offset2 / 100.0 * (float)reload));

    if (enable1)
        LL_TIM_CC_EnableChannel(PS_TIM_PWM1, PS_TIM_PWM1_CH);

    if (enable2)
        LL_TIM_CC_EnableChannel(PS_TIM_PWM2, PS_TIM_PWM2_CH);

    LL_TIM_EnableCounter(PS_TIM_PWM1);

    return 0;
}
