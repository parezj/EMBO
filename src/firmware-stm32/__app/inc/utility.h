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
char* ftoa2(double f, char * buf, int precision);

/***********************************************************/

#define PI                            3.14159265359
#define J(a,b)                        a##b
#define WTF                           assert(0)
#define NUMARGS8(...)                 (sizeof((uint8_t[]){__VA_ARGS__})/sizeof(uint8_t))
#define BITMAP_GET_BIT(m,b,s)         (*(m + (b / s)) &  (uint8_t)(1 << (b % s)))
#define BITMAP_SET_BIT(m,b,s)         (*(m + (b / s)) |= (uint8_t)(1 << (b % s)))
#define U8_TO_U16(h,l)                ((uint16_t)(h << 8u) | l)
#define U8_TO_U32(h,a,b,l)            ((uint32_t)(h << 24u) | (uint32_t)(a << 16u) | (uint32_t)(b << 8u) | l)
#define U16_TO_U8_L(x)                ((uint8_t)(((x) & 0x00FF)))
#define U16_TO_U8_H(x)                ((uint8_t)(((x) & 0xFF00) >> 8))
#define U32_TO_U8_L(x)                ((uint8_t)(((x) & 0x000000FF)))
#define U32_TO_U8_B(x)                ((uint8_t)(((x) & 0x0000FF00) >> 8))
#define U32_TO_U8_A(x)                ((uint8_t)(((x) & 0x00FF0000) >> 16))
#define U32_TO_U8_H(x)                ((uint8_t)(((x) & 0xFF000000) >> 24))

#define Pu8 "hu"
#define Pd8 "hd"
#define Px8 "hx"
#define Pu16 "hu"
#define Pd16 "hd"
#define Px16 "hx"
#define Pu32 "u"
#define Pd32 "d"
#define Px32 "x"
#define Pu64 "llu" // or possibly "lu"
#define Pd64 "lld" // or possibly "ld"
#define Px64 "llx" // or possibly "lx"

#endif /* UTILS_H */
