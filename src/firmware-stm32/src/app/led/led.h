/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#ifdef EM_LED

typedef struct
{
    int num;             // num of blink
    int ms;              // total amount if ticks in ms
    int uwtick_first;    // start timestamp
    int enabled;
}led_data_t;

void led_init(led_data_t* self);
void led_set(led_data_t* self, uint8_t enable);
void led_toggle(led_data_t* self);
void led_blink_set(led_data_t* self, int num, int len, uint32_t _uwTick);
void led_blink_do(led_data_t* self, uint32_t _uwTick);

#endif

#endif /* INC_LED_H_ */
