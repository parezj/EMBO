/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */
 
#include "app_data.h"
 
pwm_data_t em_pwm;
daq_data_t em_daq;
cntr_data_t em_cntr;
comm_data_t em_comm;

#ifdef EM_LED
led_data_t em_led;
#endif

#ifdef EM_DAC
sgen_data_t em_sgen;
#endif