/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_DAQ_TRIG_H_
#define INC_DAQ_TRIG_H_

#include "daq.h"


void daq_trig_check(daq_data_t* self);
int8_t daq_trig_trigger_scope(daq_data_t* self);
int8_t daq_trig_trigger_la(daq_data_t* self);
int8_t daq_trig_poststart(daq_data_t* self, int pos);
void daq_trig_postcount(daq_data_t* self);
void daq_trig_init(daq_data_t* self);
void daq_trig_update(daq_data_t* self);
int daq_trig_set(daq_data_t* self, uint32_t ch, uint8_t level, enum trig_edge edge, enum trig_mode mode, int pretrigger);

#endif /* INC_DAQ_TRIG_H_ */
