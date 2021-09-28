/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef CIRC_H
#define CIRC_H

#include <stdint.h>

void get_avg_from_circ(int last_idx, int ch_num, int avg_num, int bufflen, void* buff, int daq_bits,
                       double* v1, double* v2, double* v3, double* v4, double* v5);

void get_1val_from_circ(int last_idx, int ch_num, int bufflen, void* buff, int daq_bits,
                        double* v1, double* v2, double* v3, double* v4, double* v5);

int get_vcc_from_circ(int from, int total, int bufflen, int ch_num, int daq_bits, void* buff);

int get_1ch_from_circ(int from, int total, int bufflen, int ch, int ch_num, int daq_bits,
                      float vcc, float vref_cal, void* buff, uint8_t* out, int* idx);

#endif /* CIRC_H */