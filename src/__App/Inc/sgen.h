/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_SGEN_H_
#define INC_SGEN_H_

#include "cfg.h"

#ifdef PS_DAC

typedef struct
{
    uint8_t enabled;
    uint16_t data[PS_DAC_BUFF_LEN];
}sgen_data_t;

void sgen_init(sgen_data_t* self);
void sgen_enable(sgen_data_t* self, uint8_t enable);

#endif

#endif /* INC_SGEN_H_ */
