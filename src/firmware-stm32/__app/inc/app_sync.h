/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_APP_SYNC_H_
#define INC_APP_SYNC_H_

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

StaticSemaphore_t buff_sem1_comm; // comm respond init
StaticSemaphore_t buff_sem2_trig; // post trig count init
StaticSemaphore_t buff_sem3_cntr; // counter enable
StaticSemaphore_t buff_mtx1;      // mutex for comm and trig

SemaphoreHandle_t sem1_comm;
SemaphoreHandle_t sem2_trig;
SemaphoreHandle_t sem3_cntr;
SemaphoreHandle_t mtx1;

#endif /* INC_APP_SYNC_H_ */
