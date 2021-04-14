/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stddef.h>

#define ASSERT(expr) \
  do {                                          \
    if (!(expr)) {                              \
      assert2(__FILE__, __LINE__);              \
    }                                           \
  } while (0)

void assert2(const char *file, uint32_t line);

void get_avg_from_circ(int last_idx, int ch_num, int avg_num, int bufflen, void* buff, int daq_bits,
                       double* v1, double* v2, double* v3, double* v4, double* v5);

void get_1val_from_circ(int last_idx, int ch_num, int bufflen, void* buff, int daq_bits,
                        double* v1, double* v2, double* v3, double* v4, double* v5);

int get_vcc_from_circ(int from, int total, int bufflen, int ch_num, int daq_bits, void* buff);

int get_1ch_from_circ(int from, int total, int bufflen, int ch, int ch_num, int daq_bits,
                      float vcc, float vref_cal, void* buff, uint8_t* out, int* idx);

static inline int get_last_circ_idx(int pos, int len)
{
    int last_idx = pos - 1;
    if (last_idx < 0)
        last_idx = len - 1;
    return last_idx;
}

double get_freq(int* prescaler, int* reload, int max_reload, int freq_osc, int freq_want);

void busy_wait(int us);
float fastlog2 (float x);
float fastlog(float x);
float fastexp(float p);
float fastpow2(float p);
int itoa_fast(char* s, int num, int radix);
long long lltoa_fast(char* s, long long num, int radix);

/* Author: Jakub Parez
 * Descr:  ultra fast float sprintf
 */
int sprint_fast(char* s, const char* format, double fVal, int prec);

int strncmp2(const char * s1, const char * s2, size_t n);

#endif /* UTILS_H */
