/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_DAQ_H_
#define INC_DAQ_H_


enum daq_mode
{
    SCOPE = 0,  /** Oscilloscope */
    VM = 1,     /** Voltmeter */
    LA = 2      /** Logic Analyzer */
};

enum daq_bits
{
    B12 = 12,
    B8 = 8,
    B1 = 1
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
    BOTH = 2
};

typedef struct
{
    int pretrigger;         // pretrigger percentage 1-99
    enum trig_mode mode;    // main mode
    enum trig_edge edge;    // edge mode
    int ch;                 // channel 1-4
    int val;                // raw ADC value
    int val_percent;        // percentage trig val
}trig_settings_t;

typedef struct
{
    void* data;             // data storage
    uint16_t chans;         // number of channels in this buffer
    uint16_t len;           // total length of this buffer in bytes
    uint16_t reserve;       // additional length (to compensate DMA stop)
}daq_buff_t;

typedef struct
{
    // settings
    trig_settings_t set;    // user settings actual
    trig_settings_t save_s; // user settings saved for SCOPE
    trig_settings_t save_l; // user settings saved for LA

    // flags
    uint8_t is_post;        // if daq is in posttrigger stage
    uint8_t ignore;         // AWD helper var
    uint8_t ready;          // if data is ready to read by user
    uint8_t ready_last;     // previous value of ready
    uint8_t respond;        // initiating async ReadyX respond
    uint8_t irq_en;         // irq enabled after pre-trigger filled

    // counters
    int cntr;               // success trigger counter
    int all_cntr;           // all WDT debug counter

    // main positions
    int pos_frst;           // pointer to first data pos
    int pos_trig;           // pointer to trigger data pos
    int pos_last;           // pointer to last data pos
    int pos_diff;           // helper var to compare last trig pos

    // awd limits
    uint32_t awd_hi;        // ADC AWD high limit raw value
    uint32_t awd_mid;       // ADC AWD trigger limit raw value
    uint32_t awd_lo;        // ADC AWD low limit raw value
    uint8_t awd_rising;     // AWD limits state, either rising or falling - defined by user
    uint8_t awd_rising2;    // AWD limits state, either rising or falling - current value

    // misc
    uint32_t uwtick_first;  // systick timestamp when sampling start
    int pretrig_cntr;       // pre trig counter - ms
    int pretrig_val;        // pre trig systick count - ms
    int auttrig_val;        // auto trig systick count - ms
    int posttrig_size;      // post trig sample count
    int fullmem_val;        // systick tick count of full mem

    // periph addrs
    uint32_t awd_trig;      // analog watchdog address
    daq_buff_t* buff_trig;  // pointer to buffer 1-4, which is triggered
    uint32_t dma_ch_trig;   // DMA channel, which is triggered
    DMA_TypeDef* dma_trig;  // DMA, which is triggered
    ADC_TypeDef* adc_trig;  // ADC, which is triggered
    uint32_t exti_trig;     // EXTI IRQ, which is triggered
    uint32_t adcirq_trig;   // ADC IRQ, which is triggered

    // helpers
    uint8_t forced;         // flag when set forced trigger is responded instead normal/single
    uint8_t force_single;   // flag when set single trigger is forced after start from FORC
    uint8_t order;          // order from bottom of triggered ch in circular buffer
    uint8_t post_start;     // flag when set posttrigger counting starts
    int post_from;          // position from where start counting posttrigger
    int dma_pos_catched;    // catched actual DMA circular buffer position
}daq_trig_data_t;

typedef struct
{
    uint8_t ch1_en;         // channel 1 enabled
    uint8_t ch2_en;         // channel 2 enabled
    uint8_t ch3_en;         // channel 3 enabled
    uint8_t ch4_en;         // channel 4 enabled
    //uint8_t ch_count;

    double fs_real;         // sampling freq per 1 channel - real
    int fs;                 // sampling freq per 1 channel
    uint16_t mem;           // memory per 1 channel in samples
    enum daq_bits bits;     // bits per 1 channel
}daq_settings_t;

typedef struct
{
    daq_buff_t buff1;       // DAQ buffer1
    daq_buff_t buff2;       // DAQ buffer2
    daq_buff_t buff3;       // DAQ buffer3
    daq_buff_t buff4;       // DAQ buffer4

    uint8_t buff_raw[EM_DAQ_MAX_MEM + (EM_MEM_RESERVE * 2 * 5) + 20];  // static allocation of main buffer
    uint16_t buff_raw_ptr;  // top pointer of main raw buffer

    daq_settings_t set;     // user settings actual
    daq_settings_t save_s;  // user settings saved for SCOPE
    daq_settings_t save_l;  // user settings saved for LA

    float vref;             // last raw vref readout by DMA
    float vcc_mv;           // last vcc value in milivots
    float smpl_time;        // dynamic ADC sampling time
    float adc_max_val;      // max adc value
    uint32_t uwTick;        // 1 kHz counter
    uint32_t uwTick_start;  // tick count when mode start
    int vm_seq;             // VM sequential number

    enum daq_mode mode;     // main system mode
    uint8_t dis_hold;       // keep disabled until is 0
    uint8_t enabled;        // main DAQ control
    uint8_t interleaved;    // interleaved enabled
    uint8_t dualmode;       // dual mode enabled

    daq_trig_data_t trig;       // trigger substruct
}daq_data_t;

void daq_init(daq_data_t* self);
int daq_mem_set(daq_data_t* self, uint16_t mem_per_ch);
int daq_bit_set(daq_data_t* self, enum daq_bits bits);
int daq_fs_set(daq_data_t* self, int fs);
int daq_ch_set(daq_data_t* self, uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, int fs);
void daq_reset(daq_data_t* self);
void daq_enable(daq_data_t* self, uint8_t enable);
void daq_mode_set(daq_data_t* self, enum daq_mode mode);
void daq_settings_save(daq_settings_t* src1, trig_settings_t* src2, daq_settings_t* dst1, trig_settings_t* dst2);
void daq_settings_init(daq_data_t* self, uint8_t scope, uint8_t la);

#endif /* INC_DAQ_H_ */
