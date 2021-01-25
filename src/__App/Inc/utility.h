/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

#define ASSERT(expr) \
  do {                                          \
    if (!(expr)) {                              \
      assert2(__FILE__, __LINE__);              \
    }                                           \
  } while (0)

void assert2(const char *file, uint32_t line);

void get_avg_from_circ(int last_idx, int ch_num, int avg_num, int bufflen, void* buff, int daq_bits, float* v1, float* v2, float* v3, float* v4, float* v5);
int get_vcc_from_circ(int from, int total, int bufflen, int ch_num, int daq_bits, void* buff);
int get_1ch_from_circ(int from, int total, int bufflen, int ch, int ch_num, int daq_bits, float vcc, float vref_cal, void* buff, uint8_t* out, int* idx);

static inline int get_last_circ_idx(int pos, int len)
{
    int last_idx = pos - 1;
    if (last_idx < 0)
        last_idx = len - 1;
    return last_idx;
}

float get_freq(int* prescaler, int* reload, int max_reload, int freq_osc, int freq_want);

void busy_wait(int us);
float fastlog2 (float x);
float fastlog(float x);
float fastexp(float p);
float fastpow2(float p);
void itoa_fast(char* s, int num, int radix);

/* Author: Jakub Parez
 * Descr:  ultra fast float sprintf
 */
void sprint_fast(char* s, const char* format, float fVal, int prec);

#endif /* UTILS_H */
