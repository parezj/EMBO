/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_APP_SYNC_H_
#define INC_APP_SYNC_H_

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* synchronization primitives */

extern StaticSemaphore_t buff_sem1_comm; // comm respond init
extern StaticSemaphore_t buff_sem2_trig; // post trig count init
extern StaticSemaphore_t buff_sem3_cntr; // counter enable
extern StaticSemaphore_t buff_mtx1;      // mutex for comm and trig

extern SemaphoreHandle_t sem1_comm;      // semaphore - communication processing respond
extern SemaphoreHandle_t sem2_trig;      // semaphore - trigger process
extern SemaphoreHandle_t sem3_cntr;      // semaphore - counter enable/disable
extern SemaphoreHandle_t mtx1;           // mutex - critical section for SCPI output

#endif /* INC_APP_SYNC_H_ */
