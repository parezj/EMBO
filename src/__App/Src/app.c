/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include <string.h>

#include "cfg.h"
#include "app_data.h"
#include "periph.h"
#include "comm.h"
#include "main.h"


void app_main(void)
{
    pwm_init(&pwm);
    led_init(&led);
    daq_init(&daq);
    cntr_init(&cntr);

    // init PWM (debug enable)
    pwm_set(&pwm, 1, 10, 50);
    pwm_set(&pwm, 2, 10, 50);
    LL_TIM_EnableCounter(PS_TIM_PWM);
    LL_TIM_CC_EnableChannel(PS_TIM_PWM, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(PS_TIM_PWM, LL_TIM_CHANNEL_CH2);

    LL_USART_EnableIT_RXNE(PS_UART);
    uart_put_text(WELCOME_STR);

    comm_init();

    //LL_TIM_EnableIT_CC1(PS_TIM_ADC);
    //LL_TIM_EnableIT_CC1(PS_TIM_TRIG);

    daq_mode_set(&daq, SCOPE);
    daq_enable(&daq, 1);

    led_blink_set(&led, 3, PS_BLINK_LONG);

    while (1)
    {
        IWDG->KR = 0xAAAA;

        daq_trig_check(&daq); // 100x less??

        led_blink_do(&led);

        if (comm_main())
            led_blink_set(&led, 1, PS_BLINK_SHORT);
    }
}
