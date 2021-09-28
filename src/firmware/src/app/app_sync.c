/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */
 
 #include "app_sync.h"
 
StaticSemaphore_t buff_sem1_comm;
StaticSemaphore_t buff_sem2_trig;
StaticSemaphore_t buff_sem3_cntr;
StaticSemaphore_t buff_mtx1;

SemaphoreHandle_t sem1_comm;
SemaphoreHandle_t sem2_trig;
SemaphoreHandle_t sem3_cntr;
SemaphoreHandle_t mtx1;