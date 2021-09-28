/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_PERIPH_H_
#define INC_PERIPH_H_

#include "main.h"

#include <stdint.h>


void adc_init();
void adc_init_calib(ADC_TypeDef* adc);
uint32_t adc_get_next_rank(uint32_t rank);
void adc_set_ch(ADC_TypeDef* adc, uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint32_t smpl_time, uint8_t vrefint);
void adc_set_res(ADC_TypeDef* adc, uint32_t resolution);
//static uint16_t adc_read(uint32_t ch);

#endif /* INC_PERIPH_H_ */
