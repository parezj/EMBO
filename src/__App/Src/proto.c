/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"
#include "cfg.h"
#include "proto.h"
#include "app_data.h"
#include "main.h"

/************************* [System Actions] *************************/

scpi_result_t PS_System_Mode(scpi_t * context)
{
    const char* p1;
    size_t p1l;

    if (!SCPI_ParamCharacters(context, &p1, &p1l, TRUE))
    {
        SCPI_ErrorPush(context, SCPI_ERROR_MISSING_PARAMETER);
        return SCPI_RES_ERR;
    }

    if (strcmp(p1, "SCOPE\r\n") == 0)
        daq_mode_set(&daq, SCOPE);
    else if (strcmp(p1, "VM\r\n") == 0)
        daq_mode_set(&daq, VM);
    else if (strcmp(p1, "LA\r\n") == 0)
        daq_mode_set(&daq, LA);
    else
    {
        SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
        return SCPI_RES_ERR;
    }


    return SCPI_RES_OK;
}

scpi_result_t PS_System_ModeQ(scpi_t * context)
{
    char buff[10];
    int len;

    if (daq.mode == SCOPE)
        len = sprintf(buff, "SCOPE");
    else if (daq.mode == VM)
        len = sprintf(buff, "VM");
    else
        len = sprintf(buff, "LA");

    SCPI_ResultCharacters(context, buff, len);

    return SCPI_RES_OK;
}

/************************* [VM Actions] *************************/

scpi_result_t PS_VM_ReadQ(scpi_t * context)
{
    //char f1[10];
    //sprintFast(f1, " %s M", , 0);
    if (daq.mode == VM)
    {
        //uint16_t raw_ch3 = adc_read(LL_ADC_CHANNEL_3);
        //uint16_t raw_ch4 = adc_read(LL_ADC_CHANNEL_4);

        //uint16_t raw_vref = readADC(LL_ADC_CHANNEL_VREFINT);

        //int vcc_mv = (3300 * raw_cal) / raw_vref;
        //int vcc_mv = (4095 * 1200) / raw_vref;

        //int ch3 = (3300 * raw_cal * raw_ch3) / (raw_vref * 4095);
        //int ch4 = (3300 * raw_cal * raw_ch4) / (raw_vref * 4095);

        daq_enable(&daq, 0);

        uint32_t p1 = 0;
        SCPI_ParamUInt32(context, &p1, FALSE);

        float vcc_raw = 0;
        float ch1_raw = 0;
        float ch2_raw = 0;
        float ch3_raw = 0;
        float ch4_raw = 0;

        int avg_num = 1;
        if (p1 > 0)
            avg_num = (int)p1;

        if (avg_num > daq.set.mem)
        {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }

#if defined(PS_ADC_MODE_ADC1)
        int last1 = PS_DMA_LAST_IDX(daq.buff1.len, PS_DMA_ADC1);

        get_avg_from_circ(last1, 5, avg_num, daq.buff1.data, &vcc_raw, &ch1_raw, &ch2_raw, &ch3_raw, &ch4_raw);

#elif defined(PS_ADC_MODE_ADC12
        int last1 = PS_DMA_LAST_IDX(daq.buff1.len, PS_DMA_ADC1);
        int last2 = PS_DMA_LAST_IDX(daq.buff2.len, PS_DMA_ADC2);

        get_avg_from_circ(last1, 3, avg_num, daq.buff1.data, &vcc_raw, &ch1_raw, &ch2_raw, NULL, NULL);
        get_avg_from_circ(last2, 2, avg_num, daq.buff2.data, &ch3_raw, &ch4_raw, NULL, NULL, NULL);

#elif defined(PS_ADC_MODE_ADC1234)
        int last1 = PS_DMA_LAST_IDX(daq.buff1.len, PS_DMA_ADC1);
        int last2 = PS_DMA_LAST_IDX(daq.buff2.len, PS_DMA_ADC2);
        int last3 = PS_DMA_LAST_IDX(daq.buff3.len, PS_DMA_ADC3);
        int last4 = PS_DMA_LAST_IDX(daq.buff4.len, PS_DMA_ADC4);

        get_avg_from_circ(last1, 2, avg_num, daq.buff1.data, &vcc_raw, &ch1_raw, NULL, NULL, NULL);
        get_avg_from_circ(last2, 1, avg_num, daq.buff2.data, &ch2_raw, NULL, NULL, NULL, NULL);
        get_avg_from_circ(last3, 1, avg_num, daq.buff3.data, &ch3_raw, NULL, NULL, NULL, NULL);
        get_avg_from_circ(last4, 1, avg_num, daq.buff4.data, &ch4_raw, NULL, NULL, NULL, NULL);
#endif

        char vcc_s[10];
        char ch1_s[10];
        char ch2_s[10];
        char ch3_s[10];
        char ch4_s[10];

        float vcc = 4095.0 * PS_ADC_VREF_CAL / vcc_raw / 1000;
        float ch1 = vcc * ch1_raw / 4095 / 1000;
        float ch2 = vcc * ch2_raw / 4095 / 1000;
        float ch3 = vcc * ch3_raw / 4095 / 1000;
        float ch4 = vcc * ch4_raw / 4095 / 1000;

        sprint_fast(vcc_s, "%s", vcc, 4);
        sprint_fast(ch1_s, "%s", ch1, 4);
        sprint_fast(ch2_s, "%s", ch2, 4);
        sprint_fast(ch3_s, "%s", ch3, 4);
        sprint_fast(ch4_s, "%s", ch4, 4);

        char buff[100];
        int len = sprintf(buff, "%s,%s,%s,%s,%s", ch1_s, ch2_s, ch3_s, ch4_s, vcc_s);

        daq_enable(&daq, 1);
        SCPI_ResultCharacters(context, buff, len);
    }
    else
    {
        SCPI_ErrorPush(context, SCPI_ERROR_INVALID_MODE);
        return SCPI_RES_ERR;
    }


    return SCPI_RES_OK;
}

/************************* [SCOPE Actions] *************************/

scpi_result_t PS_SCOPE_ReadQ(scpi_t * context)
{
    if (daq.mode == SCOPE)
    {
        if (daq.trig.ready == 0)
        {
            SCPI_ResultText(context, "0");
            return SCPI_RES_OK;
        }

        if (daq.trig.set.mode == DISABLED)
        {
            daq_enable(&daq, 0);
            daq.trig.pos_frst = PS_DMA_LAST_IDX(daq.buff1.len, PS_DMA_ADC1) - daq.buff1.len;
            if (daq.trig.pos_frst < 0)
                daq.trig.pos_frst += daq.buff1.len;
        }

        float cal = PS_ADC_VREF_CAL_B12;
        if (daq.set.bits == B8)
            cal = PS_ADC_VREF_CAL_B8;

        float vcc = get_vcc_from_circ(daq.trig.pos_frst, daq.buff1.len, daq.buff1.chans, daq.set.bits, daq.buff1.data);
        if (vcc == 0)
        {
            SCPI_ResultText(context, "VCC = 0 ?!"); // TODO DEBUG
            return SCPI_RES_OK;
        }
        //ASSERT(vcc > 0); // TODO INVESTIGAE

#if defined(PS_ADC_MODE_ADC1)
        int added = 0;
        int idx = 0;
        int ch_it = 2;

        if (daq.set.ch1_en)
            added += get_1ch_from_circ(daq.trig.pos_frst, daq.buff1.len, ch_it++, daq.buff1.chans,
                                       daq.set.bits, vcc, cal, daq.buff1.data, daq.buff_out.data, &idx);
        if (daq.set.ch2_en)
            added += get_1ch_from_circ(daq.trig.pos_frst, daq.buff1.len, ch_it++, daq.buff1.chans,
                                       daq.set.bits, vcc, cal, daq.buff1.data, daq.buff_out.data, &idx);
        if (daq.set.ch3_en)
            added += get_1ch_from_circ(daq.trig.pos_frst, daq.buff1.len, ch_it++, daq.buff1.chans,
                                       daq.set.bits, vcc, cal, daq.buff1.data, daq.buff_out.data, &idx);
        if (daq.set.ch4_en)
            added += get_1ch_from_circ(daq.trig.pos_frst, daq.buff1.len, ch_it++, daq.buff1.chans,
                                       daq.set.bits, vcc, cal, daq.buff1.data, daq.buff_out.data, &idx);

#elif defined(PS_ADC_MODE_ADC12)

       int added = 0;
        int idx = 0;
        int ch_it = 2;

        if (daq.set.ch1_en)
            added += get_1ch_from_circ(daq.trig.pos_frst, daq.buff1.len, ch_it++, daq.buff1.chans,
                                       daq.set.bits, vcc, cal, daq.buff1.data, daq.buff_out.data, &idx);
        if (daq.set.ch2_en)
            added += get_1ch_from_circ(daq.trig.pos_frst, daq.buff1.len, ch_it++, daq.buff1.chans,
                                       daq.set.bits, vcc, cal, daq.buff1.data, daq.buff_out.data, &idx);

        ch_it = 1;
        if (daq.set.ch3_en)
            added += get_1ch_from_circ(daq.trig.pos_frst, daq.buff2.len, ch_it++, daq.buff2.chans,
                                       daq.set.bits, vcc, cal, daq.buff2.data, daq.buff_out.data, &idx);
        if (daq.set.ch4_en)
            added += get_1ch_from_circ(daq.trig.pos_frst, daq.buff2.len, ch_it++, daq.buff2.chans,
                                       daq.set.bits, vcc, cal, daq.buff2.data, daq.buff_out.data, &idx);

#elif defined(PS_ADC_MODE_ADC1234)
        /*
        int last1 = PS_DMA_LAST_IDX(daq.buff1.len, PS_DMA_ADC1);
        int last2 = PS_DMA_LAST_IDX(daq.buff2.len, PS_DMA_ADC2);
        int last3 = PS_DMA_LAST_IDX(daq.buff3.len, PS_DMA_ADC3);
        int last4 = PS_DMA_LAST_IDX(daq.buff4.len, PS_DMA_ADC4);
        */

        int added = 0;
        int idx = 0;

        if (daq.set.ch1_en)
            added += get_1ch_from_circ(daq.trig.pos_frst, daq.buff1.len, 2, daq.buff1.chans,
                                       daq.set.bits, vcc, cal, daq.buff1.data, daq.buff_out.data, &idx);
        if (daq.set.ch2_en)
            added += get_1ch_from_circ(daq.trig.pos_frst, daq.buff2.len, 1, daq.buff2.chans,
                                       daq.set.bits, vcc, cal, daq.buff2.data, daq.buff_out.data, &idx);
        if (daq.set.ch3_en)
            added += get_1ch_from_circ(daq.trig.pos_frst, daq.buff3.len, 1, daq.buff3.chans,
                                       daq.set.bits, vcc, cal, daq.buff3.data, daq.buff_out.data, &idx);
        if (daq.set.ch4_en)
            added += get_1ch_from_circ(daq.trig.pos_frst, daq.buff4.len, 1, daq.buff4.chans,
                                       daq.set.bits, vcc, cal, daq.buff4.data, daq.buff_out.data, &idx);
#endif

        daq.trig.pretrig_cntr = 0;
        daq.trig.ready = 0;
        daq_enable(&daq, 1);

        ASSERT(added == daq.buff_out.len);

        SCPI_ResultArbitraryBlock(context, daq.buff_out.data, daq.buff_out.len); // idx??
    }
    else
    {
        SCPI_ErrorPush(context, SCPI_ERROR_INVALID_MODE);
        return SCPI_RES_ERR;
    }


    return SCPI_RES_OK;
}

scpi_result_t PS_SCOPE_Set(scpi_t * context)
{
    if (daq.mode == SCOPE)
    {
        uint32_t p1, p2, p3, p5, p6, p9;
        const char* p4;
        const char* p7;
        const char* p8;
        size_t p4l, p7l, p8l;

        if (!SCPI_ParamUInt32(context, &p1, TRUE) ||
            !SCPI_ParamUInt32(context, &p2, TRUE) ||
            !SCPI_ParamUInt32(context, &p3, TRUE) ||
            !SCPI_ParamCharacters(context, &p4, &p4l, TRUE) ||
            !SCPI_ParamUInt32(context, &p5, TRUE) ||
            !SCPI_ParamUInt32(context, &p6, TRUE) ||
            !SCPI_ParamCharacters(context, &p7, &p7l, TRUE) ||
            !SCPI_ParamCharacters(context, &p8, &p8l, TRUE) ||
            !SCPI_ParamUInt32(context, &p9, TRUE))
        {
            SCPI_ErrorPush(context, SCPI_ERROR_MISSING_PARAMETER);
            return SCPI_RES_ERR;
        }

        if (p4l != 4 || p7l != 1 || p8l != 1 ||
            (p4[0] != 'T' && p4[0] != 'F') || (p4[1] != 'T' && p4[1] != 'F') ||
            (p4[2] != 'T' && p4[2] != 'F') || (p4[3] != 'T' && p4[3] != 'F') ||
            (p7[0] != 'R' && p7[0] != 'F') || (p8[0] != 'A' && p8[0] != 'N' && p8[0] != 'D'))
        {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }

        //int reen = 0;
        //if (daq.enabled)
        //{
        //    reen = 1;
            daq_enable(&daq, 0);
            daq_reset(&daq);
            daq.dis_hold = 1;
        //}

        daq_mem_set(&daq, 3); // safety guard
        int ret2 = daq_bit_set(&daq, (int)p1);
        int ret4 = daq_ch_set(&daq, p4[0] == 'T' ? 1 : 0, p4[1] == 'T' ? 1 : 0,
                                    p4[2] == 'T' ? 1 : 0, p4[3] == 'T' ? 1 : 0);
        int ret3 = daq_fs_set(&daq, (int)p3);
        int ret1 = daq_mem_set(&daq, (int)p2);
        int ret5 = daq_trig_set(&daq, p5, p6, (p7[0] == 'R' ? RISING : FALLING),
                                (p8[0] == 'A' ? AUTO : (p8[0] == 'N' ? NORMAL : DISABLED)), (int)p9);

        if (ret1 + ret2 + ret3 + ret4 + ret5 == 0)
        {
            //if (reen)
                daq.dis_hold = 0;
                daq_enable(&daq, 1);

            return SCPI_RES_OK;
        }
        else
        {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }
    }
    else
    {
        SCPI_ErrorPush(context, SCPI_ERROR_INVALID_MODE);
        return SCPI_RES_ERR;
    }
}

scpi_result_t PS_SCOPE_SetQ(scpi_t * context)
{
    if (daq.mode == SCOPE)
    {
        char buff[100];
        char freq_s[30];
        char chans_en[5];
        char edge_s[2];
        char mode_s[2];

        sprint_fast(freq_s, "%s", daq.set.fs, 3);
        chans_en[0] = daq.set.ch1_en ? 'T' : 'F';
        chans_en[1] = daq.set.ch2_en ? 'T' : 'F';
        chans_en[2] = daq.set.ch3_en ? 'T' : 'F';
        chans_en[3] = daq.set.ch4_en ? 'T' : 'F';
        edge_s[0] = daq.trig.set.edge == RISING ? 'R' : 'F';
        mode_s[0] = daq.trig.set.mode == AUTO ? 'A' : (daq.trig.set.mode == NORMAL ? 'N' : 'D');
        chans_en[4] = '\0';
        edge_s[1] = '\0';
        mode_s[1] = '\0';

        int len = sprintf(buff, "%d,%d,%s,%s,%d,%d,%s,%s,%d", daq.set.bits, daq.set.mem, freq_s, chans_en,
                          daq.trig.set.ch, daq.trig.set.val_percent, edge_s, mode_s, daq.trig.set.pretrigger);

        SCPI_ResultCharacters(context, buff, len);

        return SCPI_RES_OK;
    }
    else
    {
        SCPI_ErrorPush(context, SCPI_ERROR_INVALID_MODE);
        return SCPI_RES_ERR;
    }
}

/************************* [LA Actions] *************************/

scpi_result_t PS_LA_ReadQ(scpi_t * context)
{
    if (daq.mode == LA)
    {
        if (daq.trig.ready == 0)
        {
            SCPI_ResultText(context, "0");
            return SCPI_RES_OK;
        }

        if (daq.trig.set.mode == DISABLED)
        {
            daq_enable(&daq, 0);
            daq.trig.pos_frst = PS_DMA_LAST_IDX(daq.buff1.len, PS_DMA_LA) - daq.buff1.len;
            if (daq.trig.pos_frst < 0)
                daq.trig.pos_frst += daq.buff1.len;
        }

        for (int k = 0, i = daq.trig.pos_frst; k < daq.buff1.len; k++, i++) // TODO compress 4 + 4
        {
            if (i >= daq.buff1.len)
                i = 0;

            ((uint8_t*)daq.buff_out.data)[k] = (uint8_t)(((uint8_t*)daq.buff1.data)[i]);
        }

        daq.trig.pretrig_cntr = 0;
        daq.trig.ready = 0;
        daq_enable(&daq, 1);

        SCPI_ResultArbitraryBlock(context, daq.buff_out.data, daq.buff_out.len); // idx??
    }
    else
    {
        SCPI_ErrorPush(context, SCPI_ERROR_INVALID_MODE);
        return SCPI_RES_ERR;
    }


    return SCPI_RES_OK;
}

scpi_result_t PS_LA_Set(scpi_t * context)
{
    if (daq.mode == LA)
    {
        uint32_t p2, p3, p5, p9;
        const char* p4;
        const char* p7;
        const char* p8;
        size_t p4l, p7l, p8l;

        if (!SCPI_ParamUInt32(context, &p2, TRUE) ||
            !SCPI_ParamUInt32(context, &p3, TRUE) ||
            !SCPI_ParamCharacters(context, &p4, &p4l, TRUE) ||
            !SCPI_ParamUInt32(context, &p5, TRUE) ||
            !SCPI_ParamCharacters(context, &p7, &p7l, TRUE) ||
            !SCPI_ParamCharacters(context, &p8,&p8l, TRUE) ||
            !SCPI_ParamUInt32(context, &p9, TRUE))
        {
            SCPI_ErrorPush(context, SCPI_ERROR_MISSING_PARAMETER);
            return SCPI_RES_ERR;
        }

        if (p4l != 4 || p7l != 1 || p8l != 1 ||
            (p4[0] != 'T' && p4[0] != 'F') || (p4[1] != 'T' && p4[1] != 'F') ||
            (p4[2] != 'T' && p4[2] != 'F') || (p4[3] != 'T' && p4[3] != 'F') ||
            (p7[0] != 'R' && p7[0] != 'F') || (p8[0] != 'A' && p8[0] != 'N' && p8[0] != 'D'))
        {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }

        //int reen = 0;
        //if (daq.enabled)
        //{
        //    reen = 1;
            daq_enable(&daq, 0);
            daq_reset(&daq);
            daq.dis_hold = 1;
        //}

        daq_mem_set(&daq, 3); // safety guard
        int ret2 = daq_bit_set(&daq, B1);
        int ret4 = daq_ch_set(&daq, p4[0] == 'T' ? 1 : 0, p4[1] == 'T' ? 1 : 0,
                                    p4[2] == 'T' ? 1 : 0, p4[3] == 'T' ? 1 : 0);
        int ret3 = daq_fs_set(&daq, (int)p3);
        int ret1 = daq_mem_set(&daq, (int)p2);
        int ret5 = daq_trig_set(&daq, p5, 0, (p7[0] == 'R' ? RISING : FALLING),
                                (p8[0] == 'A' ? AUTO : (p8[0] == 'N' ? NORMAL : DISABLED)), (int)p9);

        if (ret1 + ret2 + ret3 + ret4 + ret5 == 0)
        {
            //if (reen)
                daq.dis_hold = 0;
                daq_enable(&daq, 1);

            return SCPI_RES_OK;
        }
        else
        {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }
    }
    else
    {
        SCPI_ErrorPush(context, SCPI_ERROR_INVALID_MODE);
        return SCPI_RES_ERR;
    }
}

scpi_result_t PS_LA_SetQ(scpi_t * context)
{
    if (daq.mode == LA)
    {
        char buff[100];
        char freq_s[30];
        char chans_en[5];
        char edge_s[2];
        char mode_s[2];

        sprint_fast(freq_s, "%s", daq.set.fs, 3);
        chans_en[0] = daq.set.ch1_en ? 'T' : 'F';
        chans_en[1] = daq.set.ch2_en ? 'T' : 'F';
        chans_en[2] = daq.set.ch3_en ? 'T' : 'F';
        chans_en[3] = daq.set.ch4_en ? 'T' : 'F';
        edge_s[0] = daq.trig.set.edge == RISING ? 'R' : 'F';
        mode_s[0] = daq.trig.set.mode == AUTO ? 'A' : (daq.trig.set.mode == NORMAL ? 'N' : 'D');
        chans_en[4] = '\0';
        edge_s[1] = '\0';
        mode_s[1] = '\0';

        int len = sprintf(buff, "%d,%s,%s,%d,%s,%s,%d", daq.set.mem, freq_s, chans_en,
                          daq.trig.set.ch, edge_s, mode_s, daq.trig.set.pretrigger);

        SCPI_ResultCharacters(context, buff, len);

        return SCPI_RES_OK;
    }
    else
    {
        SCPI_ErrorPush(context, SCPI_ERROR_INVALID_MODE);
        return SCPI_RES_ERR;
    }
}

/************************* [CNTR Actions] *************************/

scpi_result_t PS_CNTR_ReadQ(scpi_t * context)
{
    cntr_enable(&cntr, 0);
    cntr.ovf = 0;
    int last1 = PS_DMA_LAST_IDX(cntr.data_len, PS_DMA_CNTR);
    cntr_enable(&cntr, 1);
    int timeout = PS_FREQ_HCLK / 50;

    int diff = 0;
    int last2 = 0;
    uint32_t cc = 0;

    while (1)
    {
        cc = cntr.ovf;
        int last2 = PS_DMA_LAST_IDX(cntr.data_len, PS_DMA_CNTR);
        diff = last2 - last1;
        if (diff < 0)
            diff += cntr.data_len;
        timeout--;
        if (diff >= 3 || timeout < 0)
            break;
    }
    if (diff >= 3)
    {
        int debug1 = cntr.data[last1];
        float total = (cc * PS_TIM_CNTR_MAX) + cntr.data[last2];
        if (diff > 3)
            total /= (((float)diff / 2.0) - 0.5); // too fast, 1 period normalize

        char f_s[15];
        char T_s[15];

        float f = total / (float)PS_TIM_CNTR_FREQ;
        float T = 1.0 / f;

        if (f < 1000)
            sprint_fast(f_s, "%s Hz", f, 2);
        else if (f < 1000000)
            sprint_fast(f_s, "%s kHz", f / 1000.0, 2);
        else //if (f < 1000000000)
            sprint_fast(f_s, "%s MHz", f / 1000000.0, 2);

        if (T >= 1)
            sprint_fast(T_s, "%s s", T, 2);
        else if (T >= 0.001)
            sprint_fast(T_s, "%s ms", T * 1000.0, 2);
        else //if (T >= 0.000001)
            sprint_fast(T_s, "%s us", T * 1000000.0, 2);

        char buff[100];
        int len = sprintf(buff, "%s,%s", f_s, T_s);
        SCPI_ResultCharacters(context, buff, len);
    }
    else
    {
        SCPI_ResultText(context, "Measuring failed! (timeout)"); // TODO ERROR
    }

    cntr_enable(&cntr, 0);
    return SCPI_RES_OK;
}

/************************* [SGEN Actions] *************************/
scpi_result_t PS_SGEN_Set(scpi_t * context)
{
#ifdef PS_DAC
    double p1;
    if (!SCPI_ParamDouble(context, &p1, TRUE))
    {
        SCPI_ErrorPush(context, SCPI_ERROR_MISSING_PARAMETER);
        return SCPI_RES_ERR;
    }

    // TODO range check

    LL_DAC_SetOutputBuffer(PS_DAC, PS_DAC_CH, p1);

#else
    SCPI_ResultText(context, "DAC not available"); // TODO ERROR
#endif

    return SCPI_RES_OK;
}

/************************* [PWM Actions] *************************/

scpi_result_t PS_PWM_SetChQ(scpi_t * context)
{
    int param1;
    uint32_t param1d;

    char buff[30];
    char buff_freq[10];
    char buff_duty[10];

    if (!SCPI_ParamUInt32(context, &param1d, TRUE))
    {
        SCPI_ErrorPush(context, SCPI_ERROR_MISSING_PARAMETER);
        return SCPI_RES_ERR;
    }

    param1 = param1d;
    float real_freq = pwm.freq;
    float real_duty;
    uint8_t enabled;

    if (param1 == 1)
    {
        real_duty = pwm.duty_ch1;
        enabled = pwm.enabled_ch1;
    }
    else if (param1 == 2)
    {
        real_duty = pwm.duty_ch2;
        enabled = pwm.enabled_ch2;
    }
    else
    {
        SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
        return SCPI_RES_ERR;
    }

    sprint_fast(buff_freq, "%s", real_freq, 5);
    sprint_fast(buff_duty, "%s", real_duty, 5);
    int len = sprintf(buff, "%d,%s,%s", enabled, buff_freq, buff_duty);

    SCPI_ResultCharacters(context, buff, len);

    return SCPI_RES_OK;
}

scpi_result_t PS_PWM_SetCh(scpi_t * context)
{
    int param1;
    uint32_t param1d, param2, param3;

    if (!SCPI_ParamUInt32(context, &param1d, TRUE) ||
        !SCPI_ParamUInt32(context, &param2, TRUE) ||
        !SCPI_ParamUInt32(context, &param3, TRUE))
    {
        SCPI_ErrorPush(context, SCPI_ERROR_MISSING_PARAMETER);
        return SCPI_RES_ERR;
    }

    param1 = param1d;
    if (param1 < 1 || param1 > 2 ||
        (param2 <= 0 || param2 > 12000000) ||
        (param3 < 0 || param3 > 100))
    {
        SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
        return SCPI_RES_ERR;
    }

    pwm_set(&pwm, param1, param2, param3);

    return SCPI_RES_OK;
}

scpi_result_t PS_PWM_StartCh(scpi_t * context)
{
    int param1;
    uint32_t param1d;

    if (!SCPI_ParamUInt32(context, &param1d, TRUE))
    {
        SCPI_ErrorPush(context, SCPI_ERROR_MISSING_PARAMETER);
        return SCPI_RES_ERR;
    }

    param1 = param1d;
    if (param1 < 1 || param1 > 2)
    {
        SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
        return SCPI_RES_ERR;
    }

    LL_TIM_CC_EnableChannel(PS_TIM_PWM, (param1 == 1 ? LL_TIM_CHANNEL_CH1 : LL_TIM_CHANNEL_CH2));
    return SCPI_RES_OK;
}

scpi_result_t PS_PWM_StopCh(scpi_t * context)
{
    int param1;
    uint32_t param1d;

    if (!SCPI_ParamUInt32(context, &param1d, TRUE))
    {
        SCPI_ErrorPush(context, SCPI_ERROR_MISSING_PARAMETER);
        return SCPI_RES_ERR;
    }

    param1 = param1d;
    if (param1 < 1 || param1 > 2)
    {
        SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
        return SCPI_RES_ERR;
    }

    LL_TIM_CC_DisableChannel(PS_TIM_PWM, (param1 == 1 ? LL_TIM_CHANNEL_CH1 : LL_TIM_CHANNEL_CH2));
    return SCPI_RES_OK;
}



