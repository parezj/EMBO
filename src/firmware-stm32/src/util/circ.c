/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

//#include "cfg.h"

#include "circ.h"
#include "util.h"


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

/*
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
*/

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
