/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef APP_DATA_H
#define APP_DATA_H

#include "cntr.h"
#include "comm.h"
#include "daq.h"
#include "daq_trig.h"
#include "led.h"
#include "pwm.h"
#include "sgen.h"

pwm_data_t pwm;
led_data_t led;
daq_data_t daq;
cntr_data_t cntr;
comm_data_t comm;

#ifdef EM_DAC
sgen_data_t sgen;
#endif

#endif /* APP_DATA_H */

