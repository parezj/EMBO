/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */


#ifndef INC_PWM_H_
#define INC_PWM_H_

typedef struct
{
    uint8_t enabled;
    double freq_real;
    int freq;
    int duty;
    uint32_t prescaler;
    uint32_t reload;
    uint32_t compare;
    uint32_t offset;        // percentage of reload
}pwm_ch_t;

typedef struct
{
    pwm_ch_t ch1;
    pwm_ch_t ch2;
}pwm_data_t;

void pwm_init(pwm_data_t* self);
void pwm_disable(pwm_data_t* self);
int pwm_set(pwm_data_t* self, int freq, int duty1, int duty2, int offset2, int enable1, int enable2);

#endif /* INC_PWM_H_ */
