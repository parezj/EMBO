/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"
#include "app.h"
#include "app_data.h"
#include "app_sync.h"
#include "periph.h"
#include "comm.h"
#include "proto.h"
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define PS_STACK_T1     64
#define PS_STACK_T2     64
#define PS_STACK_T3     64
#define PS_STACK_T4     512

#define PS_PRI_T1       3
#define PS_PRI_T2       1
#define PS_PRI_T3       4
#define PS_PRI_T4       2

void t1_wd(void* p);
void t2_trig_check(void* p);
void t3_trig_post_count(void* p);
void t4_comm_and_init(void* p);

StackType_t stack_t1[PS_STACK_T1];
StackType_t stack_t2[PS_STACK_T2];
StackType_t stack_t3[PS_STACK_T3];
StackType_t stack_t4[PS_STACK_T4];

StaticTask_t buff_t1;
StaticTask_t buff_t2;
StaticTask_t buff_t3;
StaticTask_t buff_t4;

StaticSemaphore_t buff_sem1_comm; // comm respond init
StaticSemaphore_t buff_sem2_trig; // post trig count init
StaticSemaphore_t buff_mtx1;      // mutex for comm and trig

volatile uint8_t init_done = 0;   // system initialized


void app_main(void)
{
    __disable_irq();

    sem1_comm = xSemaphoreCreateBinaryStatic(&buff_sem1_comm);
    sem2_trig = xSemaphoreCreateBinaryStatic(&buff_sem2_trig);
    mtx1 = xSemaphoreCreateMutexStatic(&buff_mtx1);

    ASSERT(sem1_comm != NULL);
    ASSERT(sem2_trig != NULL);
    ASSERT(mtx1 != NULL);

    ASSERT(xTaskCreateStatic(t1_wd, "T1", PS_STACK_T1, NULL, PS_PRI_T1, stack_t1, &buff_t1) != NULL);
    ASSERT(xTaskCreateStatic(t2_trig_check, "T2", PS_STACK_T2, NULL, PS_PRI_T2, stack_t2, &buff_t2) != NULL);
    ASSERT(xTaskCreateStatic(t3_trig_post_count, "T3", PS_STACK_T3, NULL, PS_PRI_T3, stack_t3, &buff_t3) != NULL);
    ASSERT(xTaskCreateStatic(t4_comm_and_init, "T4", PS_STACK_T4, NULL, PS_PRI_T4, stack_t4, &buff_t4) != NULL);

    __enable_irq();

    vTaskStartScheduler();

    ASSERT(0);
}

void t1_wd(void* p)
{
    while (!init_done)
        vTaskDelay(2);

    while(1)
    {
        iwdg_feed();
        led_blink_do(&led);

        vTaskDelay(10);
    }
}

void t2_trig_check(void* p)
{
    while (!init_done)
        vTaskDelay(2);

    while(1)
    {
        ASSERT(xSemaphoreTake(mtx1, portMAX_DELAY) == pdPASS);

        daq_trig_check(&daq);

        ASSERT(xSemaphoreGive(mtx1) == pdPASS);

        vTaskDelay(5);
    }
}

void t3_trig_post_count(void* p)
{
    while (!init_done)
        vTaskDelay(2);

    while(1)
    {
        ASSERT(xSemaphoreTake(sem2_trig, portMAX_DELAY) == pdPASS);
        ASSERT(xSemaphoreTake(mtx1, portMAX_DELAY) == pdPASS);

        daq_trig_postcount(&daq);

        ASSERT(xSemaphoreGive(mtx1) == pdPASS);
    }
}

void t4_comm_and_init(void* p)
{
    pwm_init(&pwm);
    led_init(&led);
    cntr_init(&cntr);
    comm_init(&comm);
    daq_init(&daq);
    daq_mode_set(&daq, VM);
    led_blink_set(&led, 3, PS_BLINK_LONG_MS);

#ifdef PS_DEBUG
    pwm_set(&pwm, 1000, 25, 25, 50, 1, 1);
    //LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_256);
    //LL_IWDG_SetReloadCounter(IWDG, 0x0FFF);
#endif

    while (PS_VM_ReadQ(NULL) == SCPI_RES_ERR); // read vcc
    init_done = 1;

    while(1)
    {
        ASSERT(xSemaphoreTake(sem1_comm, portMAX_DELAY) == pdPASS);
        ASSERT(xSemaphoreTake(mtx1, portMAX_DELAY) == pdPASS);

        //iwdg_feed();
        if (comm_main(&comm))
            led_blink_set(&led, 1, PS_BLINK_SHORT_MS);

        ASSERT(xSemaphoreGive(mtx1) == pdPASS);
    }
}


