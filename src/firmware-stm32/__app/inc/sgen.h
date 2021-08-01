/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_SGEN_H_
#define INC_SGEN_H_

#include "cfg.h"

#ifdef EM_DAC

#ifndef EMBO
#define EM_DAC_BUFF_LEN        1000      // sgen buffer max len
#endif

enum sgen_mode
{
    CONST    = 0,
    SINE     = 1,
    TRIANGLE = 2,
    SAWTOOTH = 3,
    SQUARE   = 4,
    NOISE    = 5
};

typedef struct
{
    uint8_t enabled;
    enum sgen_mode mode;
    int freq;
    float ampl;
    int tim_f;
    double tim_f_real;
    int samples;
    int offset;
    uint32_t data[EM_DAC_BUFF_LEN];
}sgen_data_t;


void sgen_init(sgen_data_t* self);
void sgen_enable(sgen_data_t* self, enum sgen_mode mode, float A, float f, int offset);
void sgen_disable(sgen_data_t* self);

#endif

#endif /* INC_SGEN_H_ */
