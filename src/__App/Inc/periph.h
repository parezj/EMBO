/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef PERIPH_H
#define PERIPH_H

enum daq_mode
{
    SCOPE = 0,  /** Oscilloscope */
    VM = 1,     /** Voltmeter */
    LA = 2      /** Logic Analyzer */
};

enum trig_mode
{
    AUTO = 0,
    NORMAL = 1,
    SINGLE = 2,
    DISABLED = 3
};

enum trig_edge
{
    RISING = 0,
    FALLING = 1,
};

enum daq_bits
{
    B12 = 12,
    B8 = 8,
    B1 = 1
};

typedef struct //__attribute__((packed))
{
    int pretrigger;             // pretrigger percentage 1-99
    enum trig_mode mode;        // main mode
    enum trig_edge edge;        // edge mode
    int ch;                     // channel 1-4
    int val;                    // raw ADC value
    int val_percent;            // percentage trig val
}trig_settings_t;

typedef struct //__attribute__((packed))
{
    void* data;             // data storage
    uint16_t chans;         // number of channels in this buffer
    uint16_t len;           // total length of this buffer
    uint16_t reserve;       // additional length (to compensate DMA stop)
}daq_buff_t;

typedef struct //__attribute__((packed))
{
    trig_settings_t set;    // user settings actual
    trig_settings_t save_s; // user settings saved for SCOPE
    trig_settings_t save_l; // user settings saved for LA

    // internal values
    uint32_t ch_reg;        // trigger channel address
    uint8_t is_post;        // if daq is in posttrigger stage
    uint8_t ignore;         // AWD helper var
    uint8_t ready;          // if data is ready to read by user
    uint8_t ready_last;     // previous value of ready
    int cntr;               // success trigger counter
    int all_cntr;           // all WDT debug counter

    int pos_frst;           // pointer to first data pos
    int pos_trig;           // pointer to trigger data pos
    int pos_last;           // pointer to last data pos
    int pos_diff;           // helper var to compare last trig pos

    int uwtick_last;        // systick last value
    int pretrig_cntr;       // pre trig helper counter
    int pretrig_val;        // pre trig systick count
    int posttrig_size;      // post trig sample count
    int fullmem_val;        // systick tick count of full mem

    daq_buff_t* buff_trig;  // pointer to buffer 1-4, which is triggered
    uint32_t dma_trig;      // DMA channel, which is triggered
    uint32_t exti_trig;     // EXTI channel, which is triggered
    int order;              // order from bottom of triggered ch in circular buffer

    int trig_ready;         // TODO
    int trig_data_pos;
    int trig_data_last_idx;
}trig_data_t;

typedef struct //__attribute__((packed))
{
    uint8_t ch1_en;         // channel 1 enabled
    uint8_t ch2_en;         // channel 2 enabled
    uint8_t ch3_en;         // channel 3 enabled
    uint8_t ch4_en;         // channel 4 enabled
    //uint8_t ch_count;

    float fs;               // sampling freq per 1 channel
    uint16_t mem;           // memory per 1 channel;
    enum daq_bits bits;     // bits per 1 channel
}daq_settings_t;

typedef struct //__attribute__((packed))
{
    daq_buff_t buff1;       // DAQ buffer1
    daq_buff_t buff2;       // DAQ buffer2
    daq_buff_t buff3;       // DAQ buffer3
    daq_buff_t buff4;       // DAQ buffer4

    daq_buff_t buff_out;    // UART / USB output buffer

    uint8_t buff_raw[PS_DAQ_MAX_MEM+100];  // static allocation of main buffer
    uint16_t buff_raw_ptr;  // top pointer of main raw buffer

    daq_settings_t set;     // user settings actual
    daq_settings_t save_s;  // user settings saved for SCOPE
    daq_settings_t save_l;  // user settings saved for LA

    uint8_t dis_hold;       // keep disabled until is 0
    uint8_t enabled;        // main DAQ control
    enum daq_mode mode;     // main system mode

    trig_data_t trig;       // trigger substruct
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

typedef struct
{
    uint16_t* data;
    uint16_t data_len;

    uint8_t enabled;
    float freq;
    uint32_t ovf;
}cntr_data_t;


void led_init(led_data_t* self);
void led_set(led_data_t* self, uint8_t enable);
void led_toggle(led_data_t* self);
void led_blink_set(led_data_t* self, int num, int len);
void led_blink_do(led_data_t* self);

void cntr_init(cntr_data_t* self);
void cntr_enable(cntr_data_t* self, uint8_t enable);

void pwm_init(pwm_data_t* self);
void pwm_set(pwm_data_t* self, int ch, float freq, float duty);
void pwm_enable(pwm_data_t* self, uint8_t ch, uint8_t enable);

void daq_trig_init(daq_data_t* self);
void daq_trig_check(daq_data_t* self);
void daq_trig_trigger_scope(daq_data_t* self);
void daq_trig_trigger_la(daq_data_t* self);
void daq_trig_trigger(daq_data_t* self, int pos, int last_idx);
void daq_trig_update(daq_data_t* self);
int daq_trig_set(daq_data_t* self, uint32_t ch, uint8_t level, enum trig_edge edge, enum trig_mode mode, int pretrigger);

void daq_init(daq_data_t* self);
int daq_mem_set(daq_data_t* self, uint16_t mem_per_ch);
int daq_bit_set(daq_data_t* self, enum daq_bits bits);
int daq_fs_set(daq_data_t* self, float fs);
int daq_ch_set(daq_data_t* self, uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4);
void daq_reset(daq_data_t* self);
void daq_enable(daq_data_t* self, uint8_t enable);
void daq_mode_set(daq_data_t* self, enum daq_mode mode);
void daq_settings_save(daq_settings_t* src1, trig_settings_t* src2, daq_settings_t* dst1, trig_settings_t* dst2);
void daq_settings_init(daq_data_t* self);

void daq_trig_trigger2(daq_data_t* self);


#endif /* PERIPH_H */
