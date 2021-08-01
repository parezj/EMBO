/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"

#ifdef EM_DAC

#include "sgen.h"

#include "main.h"
#include "periph.h"

#include <string.h>
#include <math.h>
#include <stdlib.h>

#ifndef EMBO
#define EM_TRUE                1
#define EM_FALSE               0
#define EM_DAC                 DAC1                 // sgen available
#define EM_DAC_CH              LL_DAC_CHANNEL_1     // DAC channel
#define EM_DAC_BUFF_LEN        0                    // sgen buffer max len
#define EM_DAC_MAX_VAL         4095.0               // DAC max value
#define EM_DAC_TIM_MAX_F       4500000              // DAC max sampling time
#define EM_DMA_SGEN            DMA1
#define EM_DMA_CH_SGEN         LL_DMA_CHANNEL_3
#define EM_TIM_SGEN            TIM6
#define EM_TIM_SGEN_FREQ       EM_FREQ_PCLK1
#define EM_TIM_SGEN_MAX        65535
#define EM_SGEN_MAX_F          EM_DAC_TIM_MAX_F     // SGEN max output freq.
#endif

static void gen_const(uint32_t* data, float A, int N);
static void gen_sine(uint32_t* data, float A, float f, int offset, int N);
static void gen_square(uint32_t* data, float A, float f, int offset, int N);
static void gen_triangle(uint32_t* data, float A, float f, int offset, int N);
static void gen_saw(uint32_t* data, float A, float f, int offset, int N);
static void gen_noise(uint32_t* data, float A, float f, int offset, int N);

static int get_rnd(int* m_w, int* m_z);


void sgen_init(sgen_data_t* self)
{
    self->enabled = EM_FALSE;
    self->freq = 1000;
    self->ampl = 50;
    self->offset = 50;
    self->samples = EM_DAC_BUFF_LEN;
    self->tim_f = self->freq * EM_DAC_BUFF_LEN;
    self->tim_f_real = self->tim_f;

    self->mode = SINE;
    gen_sine(self->data, self->ampl, self->freq, self->offset, self->samples);

    LL_DAC_Enable(EM_DAC, EM_DAC_CH);

    uint32_t wait_loop_index = ((LL_DAC_DELAY_STARTUP_VOLTAGE_SETTLING_US * (SystemCoreClock / (100000 * 2))) / 10);
    while(wait_loop_index != 0)
        wait_loop_index--;
}

void sgen_enable(sgen_data_t* self, enum sgen_mode mode, float A, float f, int offset)
{
    if (self->enabled == EM_TRUE) // first need to disable
        return;

    ASSERT(f <= EM_SGEN_MAX_F);

    self->mode = mode;
    self->freq = f;
    self->ampl = A;
    self->offset = offset;
    self->tim_f = f * EM_DAC_BUFF_LEN;
    self->samples = EM_DAC_BUFF_LEN;

    if (self->tim_f > EM_DAC_TIM_MAX_F) // frequency too high, need to lower buffer size
    {
        self->tim_f = EM_DAC_TIM_MAX_F;
        self->samples = EM_DAC_TIM_MAX_F / self->freq;
        ASSERT(self->samples > 0);
    }

    if (mode == SINE)
        gen_sine(self->data, self->ampl, self->freq, self->offset, self->samples);
    else if (mode == SQUARE)
        gen_square(self->data, self->ampl, self->freq, self->offset, self->samples);
    else if (mode == TRIANGLE)
        gen_triangle(self->data, self->ampl, self->freq, self->offset, self->samples);
    else if (mode == SAWTOOTH)
        gen_saw(self->data, self->ampl, self->freq, self->offset, self->samples);
    else if (mode == NOISE)
        gen_noise(self->data, self->ampl, self->freq, self->offset, self->samples);
    else // mode == CONST
    {
        self->samples = EM_DAC_BUFF_LEN;
        self->tim_f = EM_DAC_BUFF_LEN;
        gen_const(self->data, self->ampl, self->samples);
    }


    int prescaler = 1;
    int reload = 0;

    self->tim_f_real = get_freq(&prescaler, &reload, EM_TIM_SGEN_MAX, EM_TIM_SGEN_FREQ, self->tim_f);

    dma_set((uint32_t)&self->data, EM_DMA_SGEN, EM_DMA_CH_SGEN,
            LL_DAC_DMA_GetRegAddr(EM_DAC, EM_DAC_CH, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED), self->samples,
            LL_DMA_PDATAALIGN_WORD, LL_DMA_MDATAALIGN_WORD, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

    /*
    if (mode == NOISE)
    {
        LL_DAC_DisableDMAReq(EM_DAC, EM_DAC_CH);
        LL_DAC_SetWaveAutoGeneration(EM_DAC, EM_DAC_CH, LL_DAC_WAVE_AUTO_GENERATION_NOISE);
    }
    else
    */
    {
        LL_DAC_EnableDMAReq(EM_DAC, EM_DAC_CH);
        LL_DAC_SetWaveAutoGeneration(EM_DAC, EM_DAC_CH, LL_DAC_WAVE_AUTO_GENERATION_NONE);
    }

    LL_DAC_EnableTrigger(EM_DAC, EM_DAC_CH);
    LL_TIM_SetAutoReload(EM_TIM_SGEN, reload);
    LL_TIM_SetPrescaler(EM_TIM_SGEN, prescaler);
    LL_TIM_EnableCounter(EM_TIM_SGEN);

    self->enabled = EM_TRUE;
}

void sgen_disable(sgen_data_t* self)
{
    memset(self->data, 0x00, EM_DAC_BUFF_LEN * sizeof(uint32_t));

    /*
    uint32_t wait_loop_index = ((LL_DAC_DELAY_STARTUP_VOLTAGE_SETTLING_US * (SystemCoreClock / (100000 * 2))) / 10);
    while(wait_loop_index != 0)
        wait_loop_index--;
    */

    LL_TIM_DisableCounter(EM_TIM_SGEN);
    LL_DAC_DisableDMAReq(EM_DAC, EM_DAC_CH);
    LL_DAC_DisableTrigger(EM_DAC, EM_DAC_CH);
    LL_DMA_DisableChannel(EM_DMA_SGEN, EM_DMA_CH_SGEN); // ADDED 29.5.21

    self->enabled = EM_FALSE;
}

/**************************** wave generation functions **********************************/

static void gen_const(uint32_t* data, float A, int N)
{
    ASSERT(A >= 0 && A <= 100);

    float a = (A/100.0*EM_DAC_MAX_VAL);

    for (int i = 0; i < N; i++)
    {
        data[i] = (uint32_t)(a);
    }
}

static void gen_sine(uint32_t* data, float A, float f, int offset, int N)
{
    ASSERT(A >= 0 && A <= 100 && f > 0);

    float max = EM_DAC_MAX_VAL;
    float a = ((A/100.0*max)/2);
    uint32_t o = (((float)offset / 100.0 * max) / 2.0);

    for (int i = 0; i < N; i++)
    {
        data[i] = (uint32_t)(a*(sin((float)i*2.0*PI/(float)N) + 1)) + o;

        if (data[i] > EM_DAC_MAX_VAL)
            data[i] = EM_DAC_MAX_VAL;
    }
}

static void gen_square(uint32_t* data, float A, float f, int offset, int N)
{
    ASSERT(A >= 0 && A <= 100 && f > 0);

    float max = EM_DAC_MAX_VAL;
    float a = (A/100.0*max);
    uint32_t o = (((float)offset / 100.0 * max) / 2.0);

    int half = N / 2;

    for (int i = 0; i < N; i++)
    {
        data[i] = (uint32_t)(i >= half ? a : 0) + o;

        if (data[i] > EM_DAC_MAX_VAL)
            data[i] = EM_DAC_MAX_VAL;
    }
}

static void gen_triangle(uint32_t* data, float A, float f, int offset, int N)
{
    ASSERT(A >= 0 && A <= 100 && f > 0);
    
    float max = EM_DAC_MAX_VAL;
    float a = (A/100.0*max);
    uint32_t o = (((float)offset / 100.0 * max) / 2.0);

    int p = N / 2.0;

    for (int i = 0; i < N; i++)
    {
        data[i] = (uint32_t)((a/(float)p) * (float)(p - abs(i % (2*p) - p) )) + o;

        if (data[i] > EM_DAC_MAX_VAL)
            data[i] = EM_DAC_MAX_VAL;
    }
}

static void gen_saw(uint32_t* data, float A, float f, int offset, int N)
{
    ASSERT(A >= 0 && A <= 100 && f > 0);

    float max = EM_DAC_MAX_VAL;
    float a = (A/100.0*max);
    uint32_t o =  (((float)offset / 100.0 * max) / 2.0);

    float inc = a / (float)N;
    float _a = 0;

    for (int i = 0; i < N; i++)
    {
        data[i] = (uint32_t)(_a) + o;

        if (data[i] > EM_DAC_MAX_VAL)
            data[i] = EM_DAC_MAX_VAL;

        _a += inc;
    }
}

static void gen_noise(uint32_t* data, float A, float f, int offset, int N)
{
    ASSERT(A >= 0 && A <= 100 && f > 0);

    float max = EM_DAC_MAX_VAL;
    float a = (A/100.0*max);
    uint32_t o =  (((float)offset / 100.0 * max) / 2.0);

    int m_w = 1;
    int m_z = 2;

    for (int i = 0; i < N; i++)
    {
        data[i] = (uint32_t)(((float)get_rnd(&m_w, &m_z) / 2147483647.0) * a) + o;

        if (data[i] > EM_DAC_MAX_VAL)
            data[i] = EM_DAC_MAX_VAL;
    }
}

static int get_rnd(int* m_w, int* m_z)
{
    *m_z = 36969L * (*m_z & 65535L) + (*m_z >> 16);
    *m_w = 18000L * (*m_w & 65535L) + (*m_w >> 16);
    return (*m_z << 16) + *m_w;
} 

#endif
