/*
 * CTU/UniLabTool project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef PERIPH_H
#define PERIPH_H


enum trig_mode
{
    AUTO = 0,
    NORMAL = 1,
    SINGLE = 2
};

enum trig_edge
{
    RISING = 0,
    FALLING = 1,
};

enum trig_pre_post
{
    T_50_50 = 0,
    T_85_15 = 1,
    T_15_85 = 2
};

enum daq_bits
{
    B12 = 0,
    B8 = 1,
    B1 = 2
};

typedef struct __attribute__((packed))
{
    enum trig_pre_post prepost;
    enum trig_mode mode;
    enum trig_edge edge;
    uint32_t ch;
    int val;

    uint8_t ignore;
    uint8_t ready;
    int cntr;
    int all_cntr;

    int pos_frst;
    int pos_trig;
    int pos_last;
    int pos_diff;

    int uwtick_last;
    int pretrig_cntr;
}trig_data_t;

typedef struct __attribute__((packed))
{
    void* buff1;
    void* buff2;

    uint16_t buff1_chans;
    uint16_t buff1_len;
    uint16_t buff2_chans;
    uint16_t buff2_len;

    uint32_t fs;
    uint16_t mem; // per_ch;
    enum daq_bits bits;

    uint8_t enabled;
}daq_data_t;

typedef struct
{
    int blink_num;
    int blink_len;
    int blink_cntr;
    int enabled;
}led_data_t;

typedef struct
{
    uint8_t enabled_ch1;
    uint8_t enabled_ch2;
    float freq;
    float duty_ch1;
    float duty_ch2;
}pwm_data_t;


void dma_init(ADC_TypeDef* adc, DMA_TypeDef* dma, uint32_t dma_ch, uint16_t* buff, uint32_t buff_size);

void adc_init(ADC_TypeDef* adc);
uint16_t adc_read(uint32_t ch); // DEBUG

void led_init(led_data_t* self);
void led_set(led_data_t* self, uint8_t enable);
void led_toggle(led_data_t* self);
void led_blink_set(led_data_t* self, int num, int len);
void led_blink_do(led_data_t* self);

void pwm_init(pwm_data_t* self);
void pwm_set(pwm_data_t* self, int ch, float freq, float duty);

void trig_init(trig_data_t* self);
void trig_set(trig_data_t* self, ADC_TypeDef* adc, uint32_t ch, uint16_t level, enum trig_edge edge, enum trig_mode mode);
void trig_pre_post_set(trig_data_t* self, enum trig_pre_post pre_post);

void daq_init(daq_data_t* self);
void daq_mem_set(daq_data_t* self, uint16_t mem_per_ch);
void daq_bit_set(daq_data_t* self, enum daq_bits bits);
void daq_fs_set(daq_data_t* self, uint32_t fs);
void daq_ch_set(daq_data_t* self, uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4);
void daq_enable(daq_data_t* self, uint8_t mode, uint8_t enable);


#endif /* PERIPH_H */
