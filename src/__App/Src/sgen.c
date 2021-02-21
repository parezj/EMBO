/*
 * CTU/EMBO - Embedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */


#include "cfg.h"

#ifdef EM_DAC

#include "sgen.h"

#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "main.h"
#include "periph.h"

static void sgen_const(sgen_data_t* self, float A);
static void sgen_sine(sgen_data_t* self, float A, float f, int N);
static void sgen_square(sgen_data_t* self, float A, float f, int N);
static void sgen_triangle(sgen_data_t* self, float A, float f, int N);
static void sgen_saw(sgen_data_t* self, float A, float f, int N);
static void sgen_rand(sgen_data_t* self, float A, float f, int N);

static int get_rnd(int* m_w, int* m_z);


void sgen_init(sgen_data_t* self)
{
    self->enabled = 0;
    self->tim_f_real = 0;
    memset(self->data, 0x00, EM_DAC_BUFF_LEN * sizeof(uint16_t));
    sgen_const(self, 50);
}

void sgen_enable(sgen_data_t* self, enum sgen_mode mode, float A, float f, int N)
{
    if (self->enabled)
        return;

    if (mode == SINE)
        sgen_sine(self, A, f, N);
    else if (mode == SQUARE)
        sgen_square(self, A, f, N);
    else if (mode == TRIANGLE)
        sgen_triangle(self, A, f, N);
    else if (mode == SAW)
        sgen_saw(self, A, f, N);
    else if (mode == RAND)
        sgen_rand(self, A, f, N);
    else // mode == CONST
        sgen_const(self, A);

    int prescaler = 1;
    int reload = 0;

    self->tim_f_real = get_freq(&prescaler, &reload, EM_TIM_SGEN_MAX, EM_TIM_SGEN_FREQ, self->tim_f);

    dma_set((uint32_t)&self->data, EM_DMA_SGEN, EM_DMA_CH_SGEN,
            LL_DAC_DMA_GetRegAddr(EM_DAC, EM_DAC_CH, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED), self->samples,
            LL_DMA_PDATAALIGN_HALFWORD, LL_DMA_MDATAALIGN_HALFWORD, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

    LL_DAC_EnableDMAReq(EM_DAC, EM_DAC_CH);
    LL_DAC_EnableTrigger(EM_DAC, EM_DAC_CH);
    LL_TIM_SetAutoReload(EM_TIM_SGEN, reload);
    LL_TIM_SetPrescaler(EM_TIM_SGEN, prescaler);
    LL_TIM_EnableCounter(EM_TIM_SGEN);

    self->enabled = 1;
}

void sgen_disable(sgen_data_t* self)
{
    LL_TIM_DisableCounter(EM_TIM_SGEN);
    LL_DAC_DisableDMAReq(EM_DAC, EM_DAC_CH);
    LL_DAC_DisableTrigger(EM_DAC, EM_DAC_CH);

    self->enabled = 0;
}

static void sgen_const(sgen_data_t* self, float A)
{
    ASSERT(A >= 0 && A <= 100);

    self->mode = CONST;
    self->freq = 0;
    self->ampl = A;
    self->samples = EM_DAC_BUFF_LEN;
    self->tim_f = EM_DAC_BUFF_LEN;

    for (int i = 0; i < EM_DAC_BUFF_LEN; i++)
    {
        self->data[i] = (uint16_t)(EM_DAC_MAX_VAL * A);
    }
}

// https://controllerstech.com/dac-in-stm32/
static void sgen_sine(sgen_data_t* self, float A, float f, int N)
{
    ASSERT(A >= 0 && A <= 100 && f > 0 && N > 0 && N < EM_DAC_BUFF_LEN);

    self->mode = SINE;
    self->freq = f;
    self->ampl = A;
    self->samples = N;
    self->tim_f = f * N;

    float a = ((A/100.0*EM_DAC_MAX_VAL)/2);
    for (int i = 0; i < N; i++)
    {
        self->data[i] = (uint16_t)(a*(sin((float)i*2.0*PI/(float)N) + 1));
    }
}

static void sgen_square(sgen_data_t* self, float A, float f, int N)
{
    ASSERT(A >= 0 && A <= 100 && f > 0 && N > 0 && N < EM_DAC_BUFF_LEN);

    self->mode = SINE;
    self->freq = f;
    self->ampl = A;
    self->samples = N;
    self->tim_f = f * N;

    float a = (A/100.0*EM_DAC_MAX_VAL);
    int half = N / 2;
    for (int i = 0; i < N; i++)
    {
        self->data[i] = (uint16_t)((i >= half) < a ? a : 0);
    }
}

static void sgen_triangle(sgen_data_t* self, float A, float f, int N)
{
    ASSERT(A >= 0 && A <= 100 && f > 0 && N > 0 && N < EM_DAC_BUFF_LEN);

    self->mode = SINE;
    self->freq = f;
    self->ampl = A;
    self->samples = N;
    self->tim_f = f * N;
    
    float a = (A/100.0*EM_DAC_MAX_VAL);
    for (int i = 0; i < N; i++)
    {
        self->data[i] = (uint16_t)(a - abs(i % (uint16_t)(2*a) - a));
    }
}

static void sgen_saw(sgen_data_t* self, float A, float f, int N)
{
    ASSERT(A >= 0 && A <= 100 && f > 0 && N > 0 && N < EM_DAC_BUFF_LEN);

    self->mode = SINE;
    self->freq = f;
    self->ampl = A;
    self->samples = N;
    self->tim_f = f * N;

    float a = (A/100.0*EM_DAC_MAX_VAL);
    float inc = a / (float)N;
    float _a;
    for (int i = 0; i < N; i++)
    {
        self->data[i] = (uint16_t)(_a);
        _a += inc;
    }
}

static void sgen_rand(sgen_data_t* self, float A, float f, int N)
{
    ASSERT(A >= 0 && A <= 100 && f > 0 && N > 0 && N < EM_DAC_BUFF_LEN);

    self->mode = SINE;
    self->freq = f;
    self->ampl = A;
    self->samples = N;
    self->tim_f = f * N;

    int m_w = 1;
    int m_z = 2; 

    for (int i = 0; i < N; i++)
    {
        self->data[i] = (uint16_t)(((float)get_rnd(&m_w, &m_z) / 2147483647.0) * EM_DAC_MAX_VAL);
    }
}

static int get_rnd(int* m_w, int* m_z)
{
    *m_z = 36969L * (*m_z & 65535L) + (*m_z >> 16);
    *m_w = 18000L * (*m_w & 65535L) + (*m_w >> 16);
    return (*m_z << 16) + *m_w;
} 

#endif
