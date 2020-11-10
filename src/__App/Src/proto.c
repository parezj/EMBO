/*
 * CTU/UniLabTool project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "cfg.h"
#include "proto.h"
#include "app_data.h"
#include "main.h"
#include "utils.h"

/************************* [System Actions] *************************/

scpi_result_t ULT_System_Mode(scpi_t * context)
{
    char buffer[100];
    size_t copy_len;

    if (!SCPI_ParamCopyText(context, buffer, sizeof (buffer), &copy_len, FALSE))
    {
        SCPI_ErrorPush(context, SCPI_ERROR_MISSING_PARAMETER);
        return SCPI_RES_ERR;
    }

    if (strcmp(buffer, "SCOPE") == 0)
        syst.mode = SCOPE;
    else if (strcmp(buffer, "VM") == 0)
        syst.mode = VM;
    else if (strcmp(buffer, "LA") == 0)
        syst.mode = LA;
    else
    {
        SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
        return SCPI_RES_ERR;
    }


    return SCPI_RES_OK;
}

scpi_result_t ULT_System_ModeQ(scpi_t * context)
{
    char buff[10];
    int len;

    if (syst.mode == SCOPE)
        len = sprintf(buff, "\"SCOPE\"");
    else if (syst.mode == VM)
        len = sprintf(buff, "\"VM\"");
    else
        len = sprintf(buff, "\"LA\"");

    SCPI_ResultCharacters(context, buff, len);

    return SCPI_RES_OK;
}

/************************* [VM Actions] *************************/

scpi_result_t ULT_VM_ReadAll(scpi_t * context)
{
    //char f1[10];
    //sprintFast(f1, " %s M", , 0);
    if (syst.mode == VM)
    {
        //uint16_t raw_ch3 = adc_read(LL_ADC_CHANNEL_3);
        //uint16_t raw_ch4 = adc_read(LL_ADC_CHANNEL_4);

        //uint16_t raw_vref = readADC(LL_ADC_CHANNEL_VREFINT);

        //int vcc_mv = (3300 * raw_cal) / raw_vref;
        //int vcc_mv = (4095 * 1200) / raw_vref;

        //int ch3 = (3300 * raw_cal * raw_ch3) / (raw_vref * 4095);
        //int ch4 = (3300 * raw_cal * raw_ch4) / (raw_vref * 4095);

        //int pos = ADC1_BUFF_SIZE - LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_1);

        int vcc = 4095 * 1200 / buff_adc1[0];
        int ch1 = vcc * buff_adc1[1] / 4095;
        int ch2 = vcc * buff_adc1[2] / 4095;
        //int ch3 = vref * raw_ch3 / 4095;
        //int ch4 = vref * raw_ch4 / 4095;

        char buff[100];
        int len = sprintf(buff, "\"%hu,%hu,%hu,%hu,%u\"", ch1, ch2, 0, 0, vcc);

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

scpi_result_t ULT_SCOPE_ReadAll(scpi_t * context)
{
    if (syst.mode == SCOPE)
    {
        if (trig.ready == 0)
        {
            SCPI_ResultText(context, "0");
            return SCPI_RES_OK;
        }

        //daq_enable(&daq, syst.mode, 0);
        int len = OUT_BUFF_SIZE * 2;
        int i, j, k;

        float vcc = 1494;
        for (k = 0, j = 0, i = trig.pos_frst; k < ADC_BUFF_SIZE; k++, i++)
        {
            if (i >= ADC_BUFF_SIZE)
                i = 0;
            if (i == 0 || i % 3 == 0)
            {
                vcc = buff_adc1[i];
                continue;
            }
            uint16_t val = ULT_ADC_VREF_CAL2 * ((float)buff_adc1[i] / vcc); // 0.8 mV precision rounded (output in mV*10)
            buff_adc_out[j++] = (char)LO_BYTE16(val);
            buff_adc_out[j++] = (char)HI_BYTE16(val);
        }

        trig.ready = 0;
        LL_ADC_SetAnalogWDMonitChannels(ADC1, trig.ch);
        daq_enable(&daq, syst.mode, 1);

        SCPI_ResultArbitraryBlock(context, buff_adc_out, len);
    }
    else
    {
        SCPI_ErrorPush(context, SCPI_ERROR_INVALID_MODE);
        return SCPI_RES_ERR;
    }


    return SCPI_RES_OK;
}

/************************* [PWM Actions] *************************/

scpi_result_t ULT_PWM_SetChQ(scpi_t * context)
{
    int param1;
    double param1d;

    char buff[30];
    char buff_freq[10];
    char buff_duty[10];

    if (!SCPI_ParamDouble(context, &param1d, TRUE))
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
    int len = sprintf(buff, "\"%d,%s,%s\"", enabled, buff_freq, buff_duty);

    SCPI_ResultCharacters(context, buff, len);

    return SCPI_RES_OK;
}

scpi_result_t ULT_PWM_SetCh(scpi_t * context)
{
    int param1;
    double param1d, param2, param3;

    if (!SCPI_ParamDouble(context, &param1d, TRUE) ||
        !SCPI_ParamDouble(context, &param2, TRUE) ||
        !SCPI_ParamDouble(context, &param3, TRUE))
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

scpi_result_t ULT_PWM_StartCh(scpi_t * context)
{
    int param1;
    double param1d;

    if (!SCPI_ParamDouble(context, &param1d, TRUE))
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

    LL_TIM_CC_EnableChannel(ULT_TIM_PWM, (param1 == 1 ? LL_TIM_CHANNEL_CH1 : LL_TIM_CHANNEL_CH2));
    return SCPI_RES_OK;
}

scpi_result_t ULT_PWM_StopCh(scpi_t * context)
{
    int param1;
    double param1d;

    if (!SCPI_ParamDouble(context, &param1d, TRUE))
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

    LL_TIM_CC_DisableChannel(ULT_TIM_PWM, (param1 == 1 ? LL_TIM_CHANNEL_CH1 : LL_TIM_CHANNEL_CH2));
    return SCPI_RES_OK;
}

/************************* [LA Actions] *************************/


/************************* [Counter Actions] *************************/




