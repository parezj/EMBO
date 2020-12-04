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
    cntr_init(&cntr);
    comm_init(&comm);
    daq_init(&daq);
    daq_mode_set(&daq, VM);
    led_blink_set(&led, 3, PS_BLINK_LONG);

    pwm_set(&pwm, 15, 20, 10, 50, 1, 1);

    while (1)
    {
        iwdg_feed();

        daq_trig_check(&daq);

        if (daq.trig.post_start)
            daq_trig_postcount(&daq);

        led_blink_do(&led);

        if (comm_main(&comm))
            led_blink_set(&led, 1, PS_BLINK_SHORT);
    }
}
