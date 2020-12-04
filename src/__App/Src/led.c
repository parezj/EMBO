/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"
#include "led.h"
#include "main.h"


void led_init(led_data_t* self)
{
    self->blink_cntr = 0;
    self->blink_len = 0;
    self->blink_cntr = 0;
    self->enabled = 0;
}

void led_set(led_data_t* self, uint8_t enable)
{
    self->enabled = enable;
    if (!self->enabled)
        PS_LED_PORT->BSRR |= (1 << PS_LED_PIN);  // 1
    else
        PS_LED_PORT->BRR |= (1 << PS_LED_PIN);   // 0
}

void led_toggle(led_data_t* self)
{
    if (self->enabled)
        PS_LED_PORT->BSRR |= (1 << PS_LED_PIN);  // 1
    else
        PS_LED_PORT->BRR |= (1 << PS_LED_PIN);   // 0
    self->enabled = !self->enabled;
}

void led_blink_set(led_data_t* self, int num, int len)
{
    self->blink_num = (num * 2) - 1;
    self->blink_len = len;
    self->blink_cntr = len;
    led_set(self, 1);
}

void led_blink_do(led_data_t* self)
{
    if (self->blink_num > 0)
    {
        if (self->blink_cntr > 0)
            self->blink_cntr--;
        else
        {
            self->blink_cntr = self->blink_len;
            self->blink_num--;
            led_toggle(self);
        }
    }
}
