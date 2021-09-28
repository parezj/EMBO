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
	DAC_TypeDef* dac;
	uint32_t dac_ch;
	uint32_t dac_trig_src;
	DMA_TypeDef* dma;
	uint32_t dma_ch;
	TIM_TypeDef* tim;
	uint32_t tim_ch;

    uint8_t enabled;
    enum sgen_mode mode;
    int freq;	// 1 - fMAX
    float ampl; // 0 - 100 %
    int offset; // 0 - 100 %
    int phase;  // 0 - 360 °
    int tim_f;
    double tim_f_real;
    double freq_real;
    int samples;
    uint32_t data[EM_DAC_BUFF_LEN];
}sgen_ch_t;

typedef struct
{
	sgen_ch_t ch1;
#ifdef EM_DAC2
	sgen_ch_t ch2;
#endif
}sgen_data_t;

void sgen_init(sgen_data_t* self);
void sgen_set(sgen_data_t* self, sgen_ch_t* ch, enum sgen_mode mode, float A, float f, int offset, int phase, uint8_t en);

#endif

#endif /* INC_SGEN_H_ */
