/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_CNTR_H_
#define INC_CNTR_H_

#include "cfg.h"

#ifndef EMBO
#define EM_CNTR_BUFF_SZ        200   // buffer size for high frequencies - fast mode
#define EM_CNTR_BUFF_SZ2       30    // buffer size for slow frequencies - precise mode
#define EM_CNTR_MEAS_MS        2000  // counter max measure time ms
#define EM_CNTR_INT_DELAY      10    // counter internal read delay
#endif


typedef struct
{
    uint16_t data_ccr[EM_CNTR_BUFF_SZ];
    uint16_t data_ovf[EM_CNTR_BUFF_SZ];
    uint8_t enabled;
    double freq;
    uint16_t ovf;
    uint8_t fast_mode;
    uint8_t fast_mode_now;
}cntr_data_t;

void cntr_init(cntr_data_t* self);
void cntr_enable(cntr_data_t* self, uint8_t enable, uint8_t fast_mode);
void cntr_start(cntr_data_t* self, uint8_t start);
void cntr_meas(cntr_data_t* self);

#endif /* INC_CNTR_H_ */
