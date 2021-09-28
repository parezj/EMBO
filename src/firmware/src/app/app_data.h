/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef APP_DATA_H
#define APP_DATA_H

#include "cntr/cntr.h"
#include "comm/comm.h"
#include "daq/daq.h"
#include "daq/daq_trig.h"
#include "led/led.h"
#include "pwm/pwm.h"
#include "sgen/sgen.h"

/* objects manage by dependency injection style - app is the master, so it creates all the data */

extern pwm_data_t em_pwm;       // PWM module data
extern daq_data_t em_daq;       // DAW module data
extern cntr_data_t em_cntr;     // Counter module data
extern comm_data_t em_comm;     // Communication module data

#ifdef EM_LED
extern led_data_t em_led;;      // LED module data
#endif

#ifdef EM_DAC
extern sgen_data_t em_sgen;     // Signal Generator module data
#endif

#endif /* APP_DATA_H */

