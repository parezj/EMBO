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

void assert2(const char *file, uint32_t line)
{
    while(1);
    //__asm("bkpt 3");
}

void get_avg_from_circ(int last_idx, int ch_num, int avg_num, uint16_t* buff, float* v1, float* v2, float* v3, float* v4, float* v5)
{
    int total = ch_num * avg_num;
    ASSERT(v1 != NULL && total > 0 && buff != NULL);

    for (int i = last_idx, j = 0; j < total; j++, i++)
    {
        if (i >= total)
            i = 0;

        if (i % ch_num == 0)
            *v1 += buff[i];
        else if (ch_num > 1 && i % ch_num == 1)
            *v2 += buff[i];
        else if (ch_num > 2 && i % ch_num == 2)
            *v3 += buff[i];
        else if (ch_num > 3 && i % ch_num == 3)
            *v4 += buff[i];
        else if (ch_num > 4)  // && i % ch_num == 4)
            *v5 += buff[i];
    }
    *v1 /= avg_num;
    if (v2 != NULL) *v2 /= avg_num;
    if (v3 != NULL) *v3 /= avg_num;
    if (v4 != NULL) *v4 /= avg_num;
    if (v5 != NULL) *v5 /= avg_num;
}

int get_vcc_from_circ(int from, int total, int ch_num, int daq_bits, void* buff)
{
    ASSERT(ch_num > 0 && total > 0 && buff != NULL);

    for (int k = 0, i = from; k < total; k++, i++)
    {
        if (i >= total)
            i = 0;

        if (i % ch_num == 0)
        {
           if (daq_bits == 12)
               return (int)(((uint16_t*)buff)[i]);
           else
               return (int)(((uint8_t*)buff)[i]);
        }
    }
    return -1;
}

int get_1ch_from_circ(int from, int total, int ch, int ch_num, int daq_bits, float vcc, float vref_cal, void* buff, uint8_t* out, int* idx)
{
    ASSERT(ch > 0 && ch_num > 0 && total > 0 && buff != NULL);

    int mod2 = ch_num - 1;
    int mod3 = mod2 - 1;
    int mod4 = mod3 - 1;

    int found = 0;
    for (int k = 0, i = from; k < total; k++, i++)
    {
        if (i >= total)
            i = 0;

        if (i % ch_num == ch - 1)
        {
            found++;
            float val = 0;
            if (daq_bits == 12)
            {
                val = (float)(((uint16_t*)buff)[i]);
                uint16_t ret = (uint16_t)(vref_cal * (val / vcc)); // 0.8 mV precision rounded (output in mV*10)
                out[(*idx)++] = LO_BYTE16(ret);
                out[(*idx)++] = HI_BYTE16(ret);
                found++;
            }
            else // (daq_bits == 8)
            {
                val = (float)(((uint8_t*)buff)[i]);
                uint8_t ret = (uint8_t)(vref_cal * (val / vcc));   // 13 mV precision rounded (output in mV/10)
                out[(*idx)++] = ret;
            }
        }
    }
    return found;
}

int get_last_circ_idx(int pos, int len)
{
    int last_idx = pos - 1;
    if (last_idx < 0)
        last_idx = len - 1;
    return last_idx;
}

float get_freq(int* prescaler, int* reload, int max_reload, int freq_osc, int freq_want)
{
    ASSERT(freq_osc >= freq_want && freq_want > 0 && freq_osc > 0 && max_reload > 0);
    *prescaler = 1;

    do
    {
        *reload = (float)freq_osc / freq_want;
        if (*reload > max_reload)
        {
            (*prescaler)++;
            freq_want = freq_osc / *prescaler;
        }
    }
    while (*reload > max_reload);

    return (float)freq_osc / (float)(*prescaler) / (float)(*reload);
}

void busy_wait(int us)
{
    for (int i = 0; i < 2000000; ++i)
        asm("nop");
}

void itoa_fast(char* s, int num, int radix)
{
    char sign = 0;
    char temp[17];  //an int can only be 16 bits long
                    //at radix 2 (binary) the string
                    //is at most 16 + 1 null long.
    int temp_loc = 0;
    int digit;
    int str_loc = 0;

    //save sign for radix 10 conversion
    if (radix == 10 && num < 0) {
        sign = 1;
        num = -num;
    }

    //construct a backward string of the number.
    do {
        digit = (unsigned int)num % radix;
        if (digit < 10)
            temp[temp_loc++] = digit + '0';
        else
            temp[temp_loc++] = digit - 10 + 'A';
        num = (((unsigned int)num) / radix);
    } while ((unsigned int)num > 0);

    //now add the sign for radix 10
    if (radix == 10 && sign) {
        temp[temp_loc] = '-';
    } else {
        temp_loc--;
    }


    //now reverse the string.
    while ( temp_loc >=0 ) {// while there are still chars
        s[str_loc++] = temp[temp_loc--];
    }
    s[str_loc] = 0; // add null termination.
}

void sprint_fast(char* s, const char* format, float fVal, int prec)
{
    char result[100] = { '\0' };
    char result_rev[100] = { '\0' };
    int dVal, dec, i, j, k;

    if (prec <= 0)
    {
        sprintf(result, "%d", (int)fVal);
        sprintf(s, format, result);
        return;
    }

    fVal += 0.5 * pow(0.1, prec);
    k = pow(10, prec);

    dVal = fVal;
    dec = ((int)(fVal * k)) % k;

    for (i = 0; i < prec; i++)
    {
        result[i] = (dec % 10) + '0';
        dec /= 10;
    }

    result[i] = '.';
    i++;

    if (dVal > 0)
    {
        while (dVal > 0)
        {
            result[i] = (dVal % 10) + '0';
            dVal /= 10;
            i++;
        }
        i--;
    }
    else
        result[i] = '0';

    for (j = 0; i >= 0; i--, j++)
        result_rev[j] = result[i];

    sprintf(s, format, result_rev);
}
