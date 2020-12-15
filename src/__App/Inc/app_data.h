/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef APP_DATA_H
#define APP_DATA_H

#include "pwm.h"
#include "led.h"
#include "daq.h"
#include "daq_trig.h"
#include "cntr.h"
#include "comm.h"

pwm_data_t pwm;
led_data_t led;
daq_data_t daq;
cntr_data_t cntr;
comm_data_t comm;

#endif /* APP_DATA_H */

