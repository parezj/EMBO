/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef APP_H
#define APP_H

#include "pwm.h"
#include "led.h"
#include "daq.h"
#include "daq_trig.h"
#include "cntr.h"
#include "comm.h"

//#define CHANNELS        3
//#define CH_BUF_SZ       500
//#define ADC_BUFF_SIZE   CH_BUF_SZ * CHANNELS
//#define OUT_BUFF_SIZE   CH_BUF_SZ * (CHANNELS - 1)


//uint16_t buff_adc1[ADC_BUFF_SIZE];
//char buff_adc_out[OUT_BUFF_SIZE * 2];


pwm_data_t pwm;
led_data_t led;
daq_data_t daq;
cntr_data_t cntr;
comm_data_t comm;


#endif /* APP_H */

