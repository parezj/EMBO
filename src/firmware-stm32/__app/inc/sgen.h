/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_SGEN_H_
#define INC_SGEN_H_

#include "cfg.h"

#ifdef EM_DAC

enum sgen_mode
{
    CONST = 0,
    SINE = 1,
    SQUARE = 2,
    TRIANGLE = 3,
    SAW = 4,
    RAND = 5
};

typedef struct
{
    uint8_t enabled;
    enum sgen_mode mode;
    float freq;
    float ampl;
    float tim_f;
    float tim_f_real;
    int samples;
    uint16_t data[EM_DAC_BUFF_LEN];
}sgen_data_t;


void sgen_init(sgen_data_t* self);
void sgen_enable(sgen_data_t* self, enum sgen_mode mode, float A, float f, int N);
void sgen_disable(sgen_data_t* self);

#endif

#endif /* INC_SGEN_H_ */
