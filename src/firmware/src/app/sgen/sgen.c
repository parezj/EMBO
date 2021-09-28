/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"

#ifdef EM_DAC

#include "sgen.h"

#include "main.h"
#include "periph/periph_dma.h"

#include <string.h>
#include <math.h>
#include <stdlib.h>

#ifndef EMBO
    #define EM_TRUE                1
    #define EM_FALSE               0
    #define EM_DAC                 DAC1                 // sgen1 available
    #define EM_DAC_CH              LL_DAC_CHANNEL_1     // sgen1 channel
    #define EM_DAC2                DAC1                 // sgen2 available
    #define EM_DAC2_CH             LL_DAC_CHANNEL_2     // sgen2 channel
    #define EM_DAC_BUFF_LEN        0                    // sgen buffer max len
    #define EM_DAC_MAX_VAL         4095.0               // DAC max value
    #define EM_DAC_TIM_MAX_F       4500000              // DAC max sampling time
    #define EM_DMA_SGEN            DMA1
    #define EM_DMA_SGEN2           DMA1
    #define EM_DMA_CH_SGEN         LL_DMA_CHANNEL_3
    #define EM_DMA_CH_SGEN2        LL_DMA_CHANNEL_4
    #define EM_TIM_SGEN            TIM6
    #define EM_TIM_SGEN_FREQ       EM_FREQ_PCLK1
    #define EM_TIM_SGEN_MAX        65535
    #define EM_TIM_SGEN2           TIM7
    #define EM_TIM_SGEN2_FREQ      EM_FREQ_PCLK1
    #define EM_TIM_SGEN2_MAX       65535
    #define EM_SGEN_MAX_F          EM_DAC_TIM_MAX_F     // SGEN max output freq.
#endif


static void sgen_ch_set(sgen_ch_t* ch, enum sgen_mode mode, float A, float f, int offset, int phase, uint8_t recreate);
static void sgen_ch_init(sgen_ch_t* ch, DAC_TypeDef* dac, uint32_t dac_ch, uint32_t dac_trig_src, DMA_TypeDef* dma, uint32_t dma_ch,
                         TIM_TypeDef* tim, int freq, int ampl, int offset, int phase, enum sgen_mode mode);

static void gen_const(uint32_t* data, float A, int N);
static void gen_sine(uint32_t* data, float A, float f, int offset, int N);
static void gen_square(uint32_t* data, float A, float f, int offset, int N);
static void gen_triangle(uint32_t* data, float A, float f, int offset, int N);
static void gen_saw(uint32_t* data, float A, float f, int offset, int N);
static void gen_noise(uint32_t* data, float A, float f, int offset, int N);

static int get_rnd(int* m_w, int* m_z);


void sgen_init(sgen_data_t* self)
{
    sgen_ch_init(&self->ch1, EM_DAC, EM_DAC_CH, EM_DAC_SRC, EM_DMA_SGEN, EM_DMA_CH_SGEN, EM_TIM_SGEN,
                 1000, 50, 50, 0, SINE);
    #ifdef EM_DAC2
        sgen_ch_init(&self->ch2, EM_DAC2, EM_DAC2_CH, EM_DAC2_SRC, EM_DMA_SGEN2, EM_DMA_CH_SGEN2, EM_TIM_SGEN2,
                     1000, 50, 50, 120, SINE);
    #endif
}

static void sgen_ch_init(sgen_ch_t* ch, DAC_TypeDef* dac, uint32_t dac_ch, uint32_t dac_trig_src, DMA_TypeDef* dma, uint32_t dma_ch,
                         TIM_TypeDef* tim, int freq, int ampl, int offset, int phase, enum sgen_mode mode)
{
    ch->dac = dac;
    ch->dac_ch = dac_ch;
    ch->dac_trig_src = dac_trig_src;
    ch->dma = dma;
    ch->dma_ch = dma_ch;
    ch->tim = tim;

    ch->freq = freq;
    ch->ampl = ampl;
    ch->offset = offset;
    ch->phase = phase;
    ch->mode = mode;
    ch->enabled = EM_FALSE;

    ch->samples = EM_DAC_BUFF_LEN;
    ch->tim_f = ch->freq * EM_DAC_BUFF_LEN;
    ch->tim_f_real = ch->tim_f;
    ch->freq_real = ch->tim_f_real / (double)ch->samples;

    gen_sine(ch->data, ch->ampl, ch->freq, ch->offset, ch->samples);

    if (LL_DAC_IsEnabled(ch->dac, ch->dac_ch) == 0)
    {
        LL_DAC_Enable(ch->dac, ch->dac_ch);

        uint32_t wait_loop_index = ((LL_DAC_DELAY_STARTUP_VOLTAGE_SETTLING_US * (SystemCoreClock / (100000 * 2))) / 10);
        while(wait_loop_index != 0)
            wait_loop_index--;
    }
}

static void sgen_ch_set(sgen_ch_t* ch, enum sgen_mode mode, float A, float f, int offset, int phase, uint8_t recreate)
{
    ASSERT(f <= EM_SGEN_MAX_F);

    /* if frequency is too high, need to lower buffer size */

    if (ch->tim_f > EM_DAC_TIM_MAX_F) //
    {
        ch->tim_f = EM_DAC_TIM_MAX_F;
        ch->samples = EM_DAC_TIM_MAX_F / ch->freq;
        ASSERT(ch->samples > 0);
    }

    /* create one period of a wave + set amplitude and offset */

    if(recreate == EM_TRUE)
    {
        if (mode == SINE)
            gen_sine(ch->data, ch->ampl, ch->freq, ch->offset, ch->samples);
        else if (mode == SQUARE)
            gen_square(ch->data, ch->ampl, ch->freq, ch->offset, ch->samples);
        else if (mode == TRIANGLE)
            gen_triangle(ch->data, ch->ampl, ch->freq, ch->offset, ch->samples);
        else if (mode == SAWTOOTH)
            gen_saw(ch->data, ch->ampl, ch->freq, ch->offset, ch->samples);
        else if (mode == NOISE)
            gen_noise(ch->data, ch->ampl, ch->freq, ch->offset, ch->samples);
        else // mode == CONST
        {
            ch->samples = EM_DAC_BUFF_LEN;
            ch->tim_f = EM_DAC_BUFF_LEN;
            gen_const(ch->data, ch->ampl, ch->samples);
        }

        /* adjust phase */

        float perc = (float)phase / 360.0;
        int shift = (int)(perc * (float)ch->samples);

        if (shift > 0) // right rotate array 'shift' times
        {
            for (int j = 0; j < shift; j++)
            {
                int last_idx = ch->samples - 1;
                int last_val = ch->data[last_idx];

                for (int i = last_idx - 1; i >= 0; i--)
                    ch->data[i + 1] = ch->data[i];
                ch->data[0] = last_val;
            }
        }
    }

    /* set DMA */

    dma_set((uint32_t)&ch->data, ch->dma, ch->dma_ch,
            LL_DAC_DMA_GetRegAddr(ch->dac, ch->dac_ch, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED), ch->samples,
            LL_DMA_PDATAALIGN_WORD, LL_DMA_MDATAALIGN_WORD, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

    /*
    if (mode == NOISE)
    {
        LL_DAC_DisableDMAReq(ch->dac, ch->dac_ch);
        LL_DAC_SetWaveAutoGeneration(ch->dac, ch->dac_ch, LL_DAC_WAVE_AUTO_GENERATION_NOISE);
    }
    else
    */
    {
        LL_DAC_EnableDMAReq(ch->dac, ch->dac_ch);
        LL_DAC_SetWaveAutoGeneration(ch->dac, ch->dac_ch, LL_DAC_WAVE_AUTO_GENERATION_NONE);
    }

    /* get timer parameters */

    int prescaler = 1;
    int reload = 0;

    ch->tim_f_real = get_freq(&prescaler, &reload, EM_TIM_SGEN_MAX, EM_TIM_SGEN_FREQ, ch->tim_f);
    ch->freq_real = ch->tim_f_real / (double)ch->samples;

    /* set up TIM */

    LL_TIM_SetAutoReload(ch->tim, reload);
    LL_TIM_SetPrescaler(ch->tim, prescaler);
}

void sgen_set(sgen_data_t* self, sgen_ch_t* ch, enum sgen_mode mode, float A, float f, int offset, int phase, uint8_t en)
{
    /* disable all */

    LL_TIM_DisableCounter(self->ch1.tim);
    LL_DAC_DisableDMAReq(self->ch1.dac, self->ch1.dac_ch);
    LL_DAC_DisableTrigger(self->ch1.dac, self->ch1.dac_ch);
    LL_DMA_DisableChannel(self->ch1.dma, self->ch1.dma_ch);
    #ifdef EM_DAC2
        LL_TIM_DisableCounter(self->ch2.tim);
        LL_DAC_DisableDMAReq(self->ch2.dac, self->ch2.dac_ch);
        LL_DAC_DisableTrigger(self->ch2.dac, self->ch2.dac_ch);
        LL_DMA_DisableChannel(self->ch2.dma, self->ch2.dma_ch);
    #endif

    /* set current channel */

    ch->mode = mode;
    ch->freq = f;
    ch->ampl = A;
    ch->offset = offset;
    ch->phase = phase;
    ch->tim_f = f * EM_DAC_BUFF_LEN;
    ch->samples = EM_DAC_BUFF_LEN;
    ch->enabled = en;

    /* refresh settings for each channel */

    sgen_ch_set(&self->ch1, self->ch1.mode, self->ch1.ampl, self->ch1.freq, self->ch1.offset, self->ch1.phase,
            (en == EM_TRUE && (ch == &self->ch1)));
    #ifdef EM_DAC2
        sgen_ch_set(&self->ch2, self->ch2.mode, self->ch2.ampl, self->ch2.freq, self->ch2.offset, self->ch2.phase,
                (en == EM_TRUE && (ch == &self->ch2)));

        /* if freqs are the same, use only 1 timer for 2 DAC */

        uint8_t freq_synced = (self->ch1.freq_real == self->ch2.freq_real ? EM_TRUE : EM_FALSE);

        /* set DAC params */

        LL_DAC_InitTypeDef DAC_InitStruct = {0};
        LL_DAC_InitTypeDef DAC2_InitStruct = {0};

        DAC_InitStruct.TriggerSource = self->ch1.dac_trig_src;
        DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
        DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_ENABLE;

        DAC2_InitStruct.TriggerSource = (freq_synced ? self->ch1.dac_trig_src : self->ch2.dac_trig_src);
        DAC2_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
        DAC2_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_ENABLE;

        LL_DAC_Init(self->ch1.dac, self->ch1.dac_ch, &DAC_InitStruct);
        LL_DAC_Init(self->ch2.dac, self->ch2.dac_ch, &DAC2_InitStruct);

        /* finally start generate */

        if (self->ch1.enabled == EM_TRUE)
            LL_DAC_EnableTrigger(self->ch1.dac, self->ch1.dac_ch);
        if (self->ch2.enabled == EM_TRUE)
            LL_DAC_EnableTrigger(self->ch2.dac, self->ch2.dac_ch);

        LL_TIM_EnableCounter(self->ch1.tim);
        LL_TIM_EnableCounter(self->ch2.tim);
    #else
        /*
        LL_DAC_InitTypeDef DAC_InitStruct = {0}

        DAC_InitStruct.TriggerSource = self->ch1.dac_trig_src;
        DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
        DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_ENABLE;

        LL_DAC_Init(self->ch1.dac, self->ch1.dac_ch, &DAC_InitStruct);
        */

        if (self->ch1.enabled == EM_TRUE)
            LL_DAC_EnableTrigger(self->ch1.dac, self->ch1.dac_ch);

        LL_TIM_EnableCounter(self->ch1.tim);
    #endif
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
