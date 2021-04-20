/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"
#include "utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void assert2(const char *file, uint32_t line)
{
    while(1);
    //__asm("bkpt 3");
}

void get_avg_from_circ(int last_idx, int ch_num, int avg_num, int bufflen, void* buff, int daq_bits,
                       double* v1, double* v2, double* v3, double* v4, double* v5)
{
    int total = ch_num * avg_num;
    ASSERT(v1 != NULL && total > 0 && buff != NULL);

    for (int i = last_idx, j = 0; j < total; j++, i--)
    {
        if (i < 0)
            i = bufflen - 1;

        double val;
        if (daq_bits == 12)
            val = (double)(*((uint16_t*)(((uint8_t*)buff)+(i*2))));
        else
            val = (double)(((uint8_t*)buff)[i]);

        if (i % ch_num == 0)
            *v1 += val;
        else if (ch_num > 1 && i % ch_num == 1)
            *v2 += val;
        else if (ch_num > 2 && i % ch_num == 2)
            *v3 += val;
        else if (ch_num > 3 && i % ch_num == 3)
            *v4 += val;
        else if (ch_num > 4)  // && i % ch_num == 4)
            *v5 += val;
    }

    *v1 /= avg_num;
    if (v2 != NULL) *v2 /= avg_num;
    if (v3 != NULL) *v3 /= avg_num;
    if (v4 != NULL) *v4 /= avg_num;
    if (v5 != NULL) *v5 /= avg_num;
}

void get_1val_from_circ(int last_idx, int ch_num, int bufflen, void* buff, int daq_bits,
                        double* v1, double* v2, double* v3, double* v4, double* v5)
{
    int total = ch_num;
    ASSERT(v1 != NULL && total > 0 && buff != NULL);

    for (int i = last_idx, j = 0; j < total; j++, i--)
    {
        if (i < 0)
            i = bufflen - 1;

        double val;
        if (daq_bits == 12)
            val = (double)(*((uint16_t*)(((uint8_t*)buff)+(i*2))));
        else
            val = (double)(((uint8_t*)buff)[i]);

        if (i % ch_num == 0)
            *v1 = val;
        else if (ch_num > 1 && i % ch_num == 1)
            *v2 = val;
        else if (ch_num > 2 && i % ch_num == 2)
            *v3 = val;
        else if (ch_num > 3 && i % ch_num == 3)
            *v4 = val;
        else if (ch_num > 4)  // && i % ch_num == 4)
            *v5 = val;
    }
}

int get_vcc_from_circ(int from, int total, int bufflen, int ch_num, int daq_bits, void* buff)
{
    ASSERT(ch_num > 0 && total > 0 && buff != NULL);

    float ret = 0;
    int avg_num = 0;
    for (int i = from, j = 0; j < total; j++, i++)
    {
        if (i >= bufflen)
            i = 0;

        float val;
        if (daq_bits == 12)
            val = (float)(*((uint16_t*)(((uint8_t*)buff)+(i*2))));
        else
            val = (float)(((uint8_t*)buff)[i]);

        if (i % ch_num == 0)
        {
            ret += val;
            avg_num++;
        }
    }
    return ret /= avg_num;
}

int get_1ch_from_circ(int from, int total, int bufflen, int ch, int ch_num, int daq_bits, float vcc, float vref_cal, void* buff, uint8_t* out, int* idx)
{
    ASSERT(ch > 0 && ch_num > 0 && total > 0 && buff != NULL);

    int found = 0;

    for (int k = 0, i = from; k < total; k++, i++)
    {
        if (i >= bufflen)
            i = 0;

        if (i % ch_num == ch - 1)
        {
            found++;
            float val = 0;
            if (daq_bits == 12)
            {
                val = (float) (*((uint16_t*)(((uint8_t*)buff)+(i*2))));
                uint16_t ret = (uint16_t)(vref_cal * (val / vcc)); // 0.8 mV precision rounded (output in mV*10)
                out[(*idx)++] = U16_TO_U8_L(ret);
                out[(*idx)++] = U16_TO_U8_H(ret);
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

// freq_want = freq_osc/((prescaler+1)*(reload+1))
// (prescaler+1)*(reload+1) = freq_osc/freq_want
double get_freq(int* prescaler, int* reload, int max_reload, int freq_osc, int freq_want)
{
    ASSERT(freq_osc >= freq_want && freq_want > 0 && freq_osc > 0 && max_reload > 0);
    *prescaler = 0;

    do
    {
        *reload = (int)((double)freq_osc / (double)(*prescaler + 1) / (double)freq_want) - 1;
        if (*reload > max_reload)
            (*prescaler)++;
    }
    while (*reload > max_reload);

    double ret  = (double)freq_osc / ((double)(*prescaler + 1) * (double)(*reload + 1));
    return ret;
}

void busy_wait(int us)
{
    for (int i = 0; i < 2000000; ++i)
        asm("nop");
}

float fastlog2 (float x)
{
  union { float f; uint32_t i; } vx = { x };
  union { uint32_t i; float f; } mx = { (vx.i & 0x007FFFFF) | 0x3f000000 };
  float y = vx.i;
  y *= 1.1920928955078125e-7f;

  return y - 124.22551499f
           - 1.498030302f * mx.f
           - 1.72587999f / (0.3520887068f + mx.f);
}

float fastlog(float x)
{
  return 0.69314718f * fastlog2 (x);
}

float fastexp(float p)
{
  return fastpow2 (1.442695040f * p);
}

float fastpow2(float p)
{
    float offset = (p < 0) ? 1.0f : 0.0f;
    float clipp = (p < -126) ? -126.0f : p;
    int w = clipp;
    float z = clipp - w + offset;
    float temp = ( (1L << 23L) * (clipp + 121.2740575f + 27.7280233f / (4.84252568f - z) - 1.49012907f * z) );
    uint32_t temp2 = (long)temp;
    union { uint32_t i; float f; } v = { temp2 };

    return v.f;
}

int itoa_fast(char* s, int num, int radix)
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
    return str_loc;
}

long long lltoa_fast(char* s, long long num, int radix)
{
    char sign = 0;
    char temp[65];
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
    return str_loc;
}

/* Author: Jakub Parez
 * Descr:  ultra fast float sprintf
 */
int sprint_fast(char* s, const char* format, double fVal, int prec)
{
    char result[65]; // = { '\0' };

    int trunc = fVal;

    if (prec <= 0 || (double)trunc == fVal) // treat like ll integer
    {
        int l1 = lltoa_fast(result, (uint64_t)fVal, 10);
        if (prec > 0 && prec < 5)
        {
            result[l1++] = '.';
            if (prec >= 1) result[l1++] = '0';
            if (prec >= 2) result[l1++] = '0';
            if (prec >= 3) result[l1++] = '0';
            if (prec >= 4) result[l1++] = '0';
            result[l1++] = '\0';
        }
        return sprintf(s, format, result);
    }

    /*
    char result[100] = { '\0' };
    char result_rev[100] = { '\0' };
    int dVal, dec, i, j, k;

    //fVal += 0.5 * pow(0.1, prec);
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

    return j;
    */

    ftoa2(fVal, result, prec);
    return sprintf(s, format, result);
}


// https://github.com/antongus/stm32tpl/blob/master/ftoa.c
#define MAX_PRECISION   (10)
static const double rounders[MAX_PRECISION + 1] =
{
    0.5,                // 0
    0.05,               // 1
    0.005,              // 2
    0.0005,             // 3
    0.00005,            // 4
    0.000005,           // 5
    0.0000005,          // 6
    0.00000005,         // 7
    0.000000005,        // 8
    0.0000000005,       // 9
    0.00000000005       // 10
};
char* ftoa2(double f, char * buf, int precision)
{
    char * ptr = buf;
    char * p = ptr;
    char * p1;
    char c;
    long intPart;

    // check precision bounds
    if (precision > MAX_PRECISION)
        precision = MAX_PRECISION;

    // sign stuff
    if (f < 0)
    {
        f = -f;
        *ptr++ = '-';
    }

    if (precision < 0)  // negative precision == automatic precision guess
    {
        if (f < 1.0) precision = 6;
        else if (f < 10.0) precision = 5;
        else if (f < 100.0) precision = 4;
        else if (f < 1000.0) precision = 3;
        else if (f < 10000.0) precision = 2;
        else if (f < 100000.0) precision = 1;
        else precision = 0;
    }

    // round value according the precision
    if (precision)
        f += rounders[precision];

    // integer part...
    intPart = f;
    f -= intPart;

    if (!intPart)
        *ptr++ = '0';
    else
    {
        // save start pointer
        p = ptr;

        // convert (reverse order)
        while (intPart)
        {
            *p++ = '0' + intPart % 10;
            intPart /= 10;
        }

        // save end pos
        p1 = p;

        // reverse result
        while (p > ptr)
        {
            c = *--p;
            *p = *ptr;
            *ptr++ = c;
        }

        // restore end pos
        ptr = p1;
    }

    // decimal part
    if (precision)
    {
        // place decimal point
        *ptr++ = '.';

        // convert
        while (precision--)
        {
            f *= 10.0;
            c = f;
            *ptr++ = '0' + c;
            f -= c;
        }
    }

    // terminating zero
    *ptr = 0;

    return buf;
}

