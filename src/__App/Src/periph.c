/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utility.h"
#include "cfg.h"
#include "periph.h"
#include "comm.h"
#include "main.h"


void dma_set(uint32_t src, DMA_TypeDef* dma, uint32_t dma_ch, uint32_t dst, uint32_t buff_size, uint32_t sz)
{
    LL_DMA_DisableChannel(dma, dma_ch);
    // Select ADC as DMA transfer request.
    //LL_DMAMUX_SetRequestID(DMAMUX1, LL_DMAMUX_CHANNEL_0, LL_DMAMUX_REQ_ADC1);

    // DMA transfer addresses and size.
    LL_DMA_ConfigAddresses(dma, dma_ch, src,
                           dst,
                           LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    LL_DMA_SetPeriphSize(dma, dma_ch, sz);
    LL_DMA_SetDataLength(dma, dma_ch, buff_size);

    //LL_DMA_EnableIT_TC(dma, dma_ch); // Enable transfer complete interrupt.
    //LL_DMA_EnableIT_HT(dma, dma_ch); // Enable half transfer interrupt.
    //LL_DMA_EnableIT_TE(dma, dma_ch); // Enable transfer error interrupt.

    // Enable
    LL_DMA_EnableChannel(dma, dma_ch);
}


/*
static uint16_t adc_read(uint32_t ch)
{
    LL_ADC_REG_StartConversionSWStart(ADC2);

    while(LL_ADC_IsActiveFlag_EOS(ADC2) == 0);
    if( LL_ADC_IsActiveFlag_EOS(ADC2) )
        LL_ADC_ClearFlag_EOS(ADC2);

    return LL_ADC_REG_ReadConversionData12(ADC2);
}
*/

void adc_init()
{
#if defined(PS_ADC_MODE_ADC1) || defined(PS_ADC_MODE_ADC12) || defined(PS_ADC_MODE_ADC1234)
    adc_init_calib(ADC1);
#endif

#if defined(PS_ADC_MODE_ADC12) || defined(PS_ADC_MODE_ADC1234)
    adc_init_calib(ADC2);
#endif

#if defined(PS_ADC_MODE_ADC1234)
    adc_init_calib(ADC3);
    adc_init_calib(ADC4);
#endif
}

void adc_init_calib(ADC_TypeDef* adc)
{
    LL_ADC_Enable(adc);
    adc->CR2 |= ADC_CR2_TSVREFE;

    uint32_t  wait_loop_index = ((LL_ADC_DELAY_ENABLE_CALIB_ADC_CYCLES * 32) >> 1);
    while(wait_loop_index != 0)
    {
      wait_loop_index--;
    }

    //LL_ADC_EnableInternalRegulator(adc);
    //LL_ADC_DisableDeepPowerDown(adc);
    //for (int i = 0; i <  1000; ++i) asm("nop");

    //LL_ADC_Disable(adc);
    const uint32_t dma_tx_mode = LL_ADC_REG_GetDMATransfer(adc);
    LL_ADC_REG_SetDMATransfer(adc, LL_ADC_REG_DMA_TRANSFER_NONE);

    LL_ADC_StartCalibration(adc);
    while (LL_ADC_IsCalibrationOnGoing(adc) != 0);

    for (int i = 0; i <  1000; ++i) asm("nop");

    LL_ADC_REG_SetDMATransfer(adc, dma_tx_mode);
    //LL_ADC_Enable(adc);
}

void adc_set_ch(ADC_TypeDef* adc, uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint32_t smpl_time, uint8_t vrefint)
{
    LL_ADC_REG_SetTriggerSource(adc, PS_ADC_TRIG_TIM);

    //LL_ADC_Disable(adc);
    int len = ch1 + ch2 + ch3 + ch4 + vrefint;

    uint32_t len_raw = LL_ADC_REG_SEQ_SCAN_DISABLE;
    if (len == 2)
        len_raw = LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS;
    if (len == 3)
        len_raw = LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS;
    else if (len == 4)
        len_raw = LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS;
    else if (len == 5)
        len_raw = LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS;

    LL_ADC_REG_SetSequencerLength(adc, len_raw);

    uint32_t next_rank = LL_ADC_REG_RANK_1;

    if (vrefint)
    {
        LL_ADC_REG_SetSequencerRanks(adc, next_rank, LL_ADC_CHANNEL_VREFINT);
        LL_ADC_SetChannelSamplingTime(adc, LL_ADC_CHANNEL_VREFINT, PS_ADC_SMPL_TIME);
        next_rank = adc_get_next_rank(next_rank);
    }
    if (ch1) {
        LL_ADC_REG_SetSequencerRanks(adc, next_rank, PS_ADC_CH1);
        LL_ADC_SetChannelSamplingTime(adc, PS_ADC_CH1, PS_ADC_SMPL_TIME);
        next_rank = adc_get_next_rank(next_rank);
    }
    if (ch2) {
        LL_ADC_REG_SetSequencerRanks(adc, next_rank, PS_ADC_CH2);
        LL_ADC_SetChannelSamplingTime(adc, PS_ADC_CH2, PS_ADC_SMPL_TIME);
        next_rank = adc_get_next_rank(next_rank);
    }
    if (ch3) {
        LL_ADC_REG_SetSequencerRanks(adc, next_rank, PS_ADC_CH3);
        LL_ADC_SetChannelSamplingTime(adc, PS_ADC_CH3, PS_ADC_SMPL_TIME);
        next_rank = adc_get_next_rank(next_rank);
    }
    if (ch4) {
        LL_ADC_REG_SetSequencerRanks(adc, next_rank, PS_ADC_CH4);
        LL_ADC_SetChannelSamplingTime(adc, PS_ADC_CH4, PS_ADC_SMPL_TIME);
        next_rank = adc_get_next_rank(next_rank);
    }

    //LL_ADC_Enable(adc);
}

uint32_t adc_get_next_rank(uint32_t rank)
{
    if (rank == LL_ADC_REG_RANK_1)
        return LL_ADC_REG_RANK_2;
    if (rank == LL_ADC_REG_RANK_2)
        return LL_ADC_REG_RANK_3;
    else if (rank == LL_ADC_REG_RANK_3)
        return LL_ADC_REG_RANK_4;
    else if (rank == LL_ADC_REG_RANK_4)
        return LL_ADC_REG_RANK_5;
    else
        return LL_ADC_REG_RANK_6;
}

void adc_set_res(ADC_TypeDef* adc, uint32_t resolution) // LL_ADC_RESOLUTION_12B, LL_ADC_RESOLUTION_8B
{
    //LL_ADC_Disable(adc);
#ifdef PS_ADC_BIT8
    LL_ADC_SetResolution(adc, resolution);
#endif
    //LL_ADC_Enable(adc);
}

