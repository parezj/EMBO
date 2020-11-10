/*
 * CTU/UniLabTool project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef APP_H
#define APP_H

#include "periph.h"

#define CHANNELS        3
#define CH_BUF_SZ       500
#define ADC_BUFF_SIZE   CH_BUF_SZ * CHANNELS
#define OUT_BUFF_SIZE   CH_BUF_SZ * (CHANNELS - 1)


uint16_t buff_adc1[ADC_BUFF_SIZE];
char buff_adc_out[OUT_BUFF_SIZE * 2];

enum system_mode
{
    SCOPE = 0,  /** Oscilloscope */
    VM = 1,     /** Voltmeter */
    LA = 2      /** Logic Analyzer */
};

typedef struct
{
    enum system_mode mode;
}system_data_t;

system_data_t syst;
pwm_data_t pwm;
led_data_t led;
trig_data_t trig;
daq_data_t daq;

#endif /* APP_H */

