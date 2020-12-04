/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_LED_H_
#define INC_LED_H_

typedef struct
{
    int blink_num;
    int blink_len;
    int blink_cntr;
    int enabled;
}led_data_t;

void led_init(led_data_t* self);
void led_set(led_data_t* self, uint8_t enable);
void led_toggle(led_data_t* self);
void led_blink_set(led_data_t* self, int num, int len);
void led_blink_do(led_data_t* self);

#endif /* INC_LED_H_ */
