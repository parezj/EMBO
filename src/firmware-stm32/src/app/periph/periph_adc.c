/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"
#include "periph_adc.h"


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
    #if defined(EM_ADC_MODE_ADC1) || defined(EM_ADC_MODE_ADC12) || defined(EM_ADC_MODE_ADC1234)
        adc_init_calib(EM_ADC1);

        #if defined(EM_ADC_DUALMODE)
            adc_init_calib(ADC2); // TODO
        #endif

    #endif

    #if defined(EM_ADC_MODE_ADC12) || defined(EM_ADC_MODE_ADC1234)
        adc_init_calib(EM_ADC2);
    #endif

    #if defined(EM_ADC_MODE_ADC1234)
        adc_init_calib(EM_ADC3);
        adc_init_calib(EM_ADC4);
    #endif
}

void adc_init_calib(ADC_TypeDef* adc)
{
    #if defined(EM_ADC_CAL_EN)
        LL_ADC_Enable(adc);

        uint32_t  wait_loop_index = ((EM_ADC_EN_TICKS * 32) >> 1);
        while(wait_loop_index != 0) wait_loop_index--;
    #endif

    #if defined(ADC_CR2_TSVREFE)
        adc->CR2 |= ADC_CR2_TSVREFE;
    #endif

    #if defined(EM_ADC_DEEPPWD)
        LL_ADC_DisableDeepPowerDown(adc);
    #endif

    #if defined(EM_ADC_LINREG)
        LL_ADC_EnableInternalRegulator(adc);
        for (int i = 0; i <  10000; ++i) asm("nop"); // ?
    #endif

        //LL_ADC_EnableInternalRegulator(adc);
        //LL_ADC_DisableDeepPowerDown(adc);
        //for (int i = 0; i <  1000; ++i) asm("nop");

        //LL_ADC_Disable(adc);
        const uint32_t dma_tx_mode = LL_ADC_REG_GetDMATransfer(adc);
        LL_ADC_REG_SetDMATransfer(adc, LL_ADC_REG_DMA_TRANSFER_NONE);

    #ifdef LL_ADC_DIFFERENTIAL_ENDED
        LL_ADC_StartCalibration(adc, LL_ADC_SINGLE_ENDED);
    #else
        LL_ADC_StartCalibration(adc);
    #endif
        while (LL_ADC_IsCalibrationOnGoing(adc) != 0);

        for (int i = 0; i <  10000; ++i) asm("nop");

        LL_ADC_REG_SetDMATransfer(adc, dma_tx_mode);

    #if !defined(EM_ADC_CAL_EN)
        LL_ADC_Enable(adc);

        uint32_t  wait_loop_index = ((EM_ADC_EN_TICKS * 32) >> 1);
        while(wait_loop_index != 0) wait_loop_index--;
    #endif
}

void adc_set_ch(ADC_TypeDef* adc, uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint32_t smpl_time, uint8_t vrefint)
{
    #ifdef EM_ADC_SEQ_CONF
        int len = ch1 + ch2 + ch3 + ch4 + vrefint;

        uint32_t len_raw = LL_ADC_REG_SEQ_SCAN_DISABLE;
        if (len == 2)
            len_raw = LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS;
        if (len == 3)
            len_raw = LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS;

        #ifdef EM_DAQ_4CH
            else if (len == 4)
                len_raw = LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS;
            else if (len == 5)
                len_raw = LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS;
        #endif

        LL_ADC_REG_SetSequencerLength(adc, len_raw);
        uint32_t next_rank = LL_ADC_REG_RANK_1;
    #else
        #ifdef EM_DAQ_4CH
            LL_ADC_REG_SetSequencerChRem(adc, EM_ADC_CH1 | EM_ADC_CH2 | EM_ADC_CH3 | EM_ADC_CH4 | LL_ADC_CHANNEL_VREFINT);
        #else
            LL_ADC_REG_SetSequencerChRem(adc, EM_ADC_CH1 | EM_ADC_CH2 | LL_ADC_CHANNEL_VREFINT);
        #endif
    #endif

    #ifdef LL_ADC_SAMPLINGTIME_COMMON_1
        LL_ADC_SetSamplingTimeCommonChannels(adc, LL_ADC_SAMPLINGTIME_COMMON_1, smpl_time);
        smpl_time = LL_ADC_SAMPLINGTIME_COMMON_1;
    #endif

    /********************/

    #ifdef EM_ADC_SEQ_CONF
        if (vrefint)
        {
            LL_ADC_REG_SetSequencerRanks(adc, next_rank, LL_ADC_CHANNEL_VREFINT);
            LL_ADC_SetChannelSamplingTime(adc, LL_ADC_CHANNEL_VREFINT, smpl_time);
            next_rank = adc_get_next_rank(next_rank);
        }
        if (ch1) {
            LL_ADC_REG_SetSequencerRanks(adc, next_rank, EM_ADC_CH1);
            LL_ADC_SetChannelSamplingTime(adc, EM_ADC_CH1, smpl_time);
            next_rank = adc_get_next_rank(next_rank);
        }
        if (ch2) {
            LL_ADC_REG_SetSequencerRanks(adc, next_rank, EM_ADC_CH2);
            LL_ADC_SetChannelSamplingTime(adc, EM_ADC_CH2, smpl_time);
            next_rank = adc_get_next_rank(next_rank);
        }

        #ifdef EM_DAQ_4CH
            if (ch3) {
                LL_ADC_REG_SetSequencerRanks(adc, next_rank, EM_ADC_CH3);
                LL_ADC_SetChannelSamplingTime(adc, EM_ADC_CH3, smpl_time);
                next_rank = adc_get_next_rank(next_rank);
            }
            if (ch4) {
                LL_ADC_REG_SetSequencerRanks(adc, next_rank, EM_ADC_CH4);
                LL_ADC_SetChannelSamplingTime(adc, EM_ADC_CH4, smpl_time);
                next_rank = adc_get_next_rank(next_rank);
            }
        #endif
    #else
        if (vrefint)
        {
            LL_ADC_REG_SetSequencerChAdd(adc, LL_ADC_CHANNEL_VREFINT);
            LL_ADC_SetChannelSamplingTime(adc, LL_ADC_CHANNEL_VREFINT, smpl_time);
        }
        if (ch1) {
            LL_ADC_REG_SetSequencerChAdd(adc, EM_ADC_CH1);
            LL_ADC_SetChannelSamplingTime(adc, EM_ADC_CH1, smpl_time);
        }
        if (ch2) {
            LL_ADC_REG_SetSequencerChAdd(adc, EM_ADC_CH2);
            LL_ADC_SetChannelSamplingTime(adc, EM_ADC_CH2, smpl_time);
        }

        #ifdef EM_DAQ_4CH
            if (ch3) {
                LL_ADC_REG_SetSequencerChAdd(adc, EM_ADC_CH3);
                LL_ADC_SetChannelSamplingTime(adc, EM_ADC_CH3, smpl_time);
            }
            if (ch4) {
                LL_ADC_REG_SetSequencerChAdd(adc, EM_ADC_CH4);
                LL_ADC_SetChannelSamplingTime(adc, EM_ADC_CH4, smpl_time);
            }
        #endif

        LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(adc), LL_ADC_PATH_INTERNAL_VREFINT);
    #endif
}

uint32_t adc_get_next_rank(uint32_t rank)
{
    if (rank == LL_ADC_REG_RANK_1)
        return LL_ADC_REG_RANK_2;
    if (rank == LL_ADC_REG_RANK_2)
        return LL_ADC_REG_RANK_3;

    #ifdef EM_DAQ_4CH
        if (rank == LL_ADC_REG_RANK_3)
            return LL_ADC_REG_RANK_4;
        if (rank == LL_ADC_REG_RANK_4)
            return LL_ADC_REG_RANK_5;
        if (rank == LL_ADC_REG_RANK_5)
            return LL_ADC_REG_RANK_6;
    #endif

    return 0;
}

void adc_set_res(ADC_TypeDef* adc, uint32_t resolution) // LL_ADC_RESOLUTION_12B, LL_ADC_RESOLUTION_8B
{
    //LL_ADC_Disable(adc);
    #ifdef EM_ADC_BIT8
        LL_ADC_SetResolution(adc, resolution);
    #endif
    //LL_ADC_Enable(adc);
}

