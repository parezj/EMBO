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

pwm_data_t em_pwm;
led_data_t em_led;
daq_data_t em_daq;
cntr_data_t em_cntr;
comm_data_t em_comm;

#ifdef EM_DAC
sgen_data_t em_sgen;
#endif

#endif /* APP_DATA_H */

