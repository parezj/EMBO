/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_APP_SYNC_H_
#define INC_APP_SYNC_H_

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t sem1_comm;
SemaphoreHandle_t sem2_trig;
SemaphoreHandle_t sem3_cntr;
SemaphoreHandle_t mtx1;

#endif /* INC_APP_SYNC_H_ */
