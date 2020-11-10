/*
 * CTU/UniLabTool project
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
    syst.mode = SCOPE;
    pwm_init(&pwm);
    daq_init(&daq);
    led_init(&led);
    trig_init(&trig);

    // init PWM (debug enable)
    pwm_set(&pwm, 1, 10, 50);
    pwm_set(&pwm, 2, 10, 50);
    LL_TIM_EnableCounter(ULT_TIM_PWM);
    LL_TIM_CC_EnableChannel(ULT_TIM_PWM, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(ULT_TIM_PWM, LL_TIM_CHANNEL_CH2);

    LL_USART_EnableIT_RXNE(ULT_UART);
    //uart_put_str("\n===== Welcome to UniLabTool =====\n\n", 36);

    comm_init();

    // init daq
    adc_init(ADC1);
    dma_init(ADC1, DMA1, LL_DMA_CHANNEL_1, buff_adc1, ADC_BUFF_SIZE);
    memset(buff_adc1, 0, ADC_BUFF_SIZE * sizeof(uint16_t));
    LL_TIM_EnableCounter(ULT_TIM_ADC);
    daq_enable(&daq, syst.mode, 1);

    // init trigger
    LL_TIM_EnableIT_CC1(ULT_TIM_TRIG);
    trig_set(&trig, ADC1, LL_ADC_AWD_CHANNEL_2_REG, 2047, RISING, AUTO);

    led_blink_set(&led, 3, BLINK_LONG);

    while (1)
    {
        IWDG->KR = 0xAAAA;
        led_blink_do(&led);

        if (comm_main())
            led_blink_set(&led, 1, BLINK_SHORT);
    }
}
