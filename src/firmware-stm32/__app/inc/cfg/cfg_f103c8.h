/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_CFG_CFG_F103C8_H_
#define INC_CFG_CFG_F103C8_H_

#if defined(STM32F103xB)

#include "stm32f1xx.h"

/*
 * =========layout=========
 *  DAQ CH1 ........... PA1
 *  DAQ CH2 ........... PA2
 *  DAQ CH3 ........... PA3
 *  DAQ CH4 ........... PA4
 *  PWM CH1 ........... PA15
 *  PWM CH2 ........... PB6
 *  CNTR .............. PA8
 *  UART RX ........... PA10
 *  UART TX ........... PA9
 *  =======================
*/

// pins strings
#define EM_PINS_SCOPE_VM       "A1-A2-A3-A4"
#define EM_PINS_LA             "A1-A2-A3-A4"
#define EM_PINS_CNTR           "A8"
#define EM_PINS_PWM            "A15-B6"
#define EM_PINS_SGEN           "-"

#define EM_LL_VER              "1.8.3" // TODO automate

// freqs  -----------------------------------------------------------
#define EM_FREQ_LSI            40000     // LSI clock - wdg
#define EM_FREQ_HCLK           72000000  // HCLK clock - main
#define EM_FREQ_ADCCLK         12000000  // ADC clock
#define EM_FREQ_PCLK1          72000000  // APB1 clock - TIM2,3,4
#define EM_FREQ_PCLK2          72000000  // APB2 clock - TIM1
#define EM_SYSTICK_FREQ        1000      // Systick clock

// device -----------------------------------------------------------
#define EM_DEV_NAME            "EMBO-STM32F103C8-BluePill"   // device specific name
#define EM_DEV_COMM            "USB + UART (115200 bps)"     // device comm methods

// UART -------------------------------------------------------------
#define EM_UART                USART1               // UART periph
#define EM_UART_RX_IRQHandler  USART1_IRQHandler    // UART IRQ handler
//#define EM_UART_CLEAR_FLAG(x)  LL_USART_ClearFlag_RTO(x);  // RTO flags needs clearing
#define EM_UART_CLEAR_FLAG(x)  LL_USART_ClearFlag_RXNE(x);  // RXNE flags needs clearing
#define EM_USB                                      // if emulated USB enabled

// LED -------------------------------------------------------------
#define EM_LED_PORT            GPIOC                // main LED port
#define EM_LED_PIN             13                   // main LED pin

// DAC -------------------------------------------------------------
//#define EM_DAC               DAC1                 // sgen available
#define EM_DAC_CH              LL_DAC_CHANNEL_1     // DAC channel
#define EM_DAC_BUFF_LEN        1000                 // buffer max len
#define EM_DAC_MAX_VAL         4095.0               // DAC max value

// GPIO ------------------------------------------------------------
#define EM_GPIO_EXTI_SRC       LL_GPIO_AF_SetEXTISource        // GPIO EXTI source

// ADC -------------------------------------------------------------
#define EM_ADC_MODE_ADC1                                       // 1 ADC (1 DMA)              - verified
//#define EM_ADC_MODE_ADC12                                    // 2 full ADCs (2 DMA)        - N/A
//#define EM_ADC_MODE_ADC1234                                  // 4 full ADCs (4 DMA)        - N/A
#define EM_ADC_BIT12                                           // 12-bit mode available      - verified
//#define EM_ADC_BIT8                                          // 8-bit mode available       - N/A
//#define EM_ADC_INTERLEAVED                                   // interleaved mode available - TODO
//#define EM_ADC_DUALMODE                                      // dual mode available        - TODO

#define EM_VREF                3300                            // main voltage reference in mV
#define EM_ADC_VREF_CAL        1200                            // vref cal value
//#define EM_ADC_VREF_CAL      *((uint16_t*)VREFINT_CAL_ADDR)  // Vref cal value
#define EM_ADC_SMPLT_MAX       LL_ADC_SAMPLINGTIME_1CYCLE_5    // max sampling time in ticks
#define EM_ADC_SMPLT_MAX_N     1.5                             // max smpl time value
#define EM_ADC_TCONV8          8.5                             // ADC Tconversion ticks for 8-bit
#define EM_ADC_TCONV12         12.5                            // ADC Tconversion ticks for 12-bit
#define EM_ADC_C_F             0.000000000008 // 8pF           // ADC internal capacitance in F
#define EM_ADC_R_OHM           1000.0                          // ADC internal impedance in Ohm
#define EM_ADC_SMPLT_CNT       8                               // count of available smpl times
#define EM_ADC_CAL_EN                                          // calibration while enabled
#define LL_ADC_SPEC_START                                      // special start stop methods needed
#define EM_ADC_AWD                                             // Analog Watchdog
#define EM_ADC_TRIG_12         LL_ADC_REG_TRIG_EXT_TIM3_TRGO   // ADC TIM trig TRGO 12
//#define EM_ADC_TRIG_34       LL_ADC_REG_TRIG_EXT_TIM3_TRGO   // ADC TIM trig TRGO 34
#define EM_ADC_EN_TICKS        LL_ADC_DELAY_ENABLE_CALIB_ADC_CYCLES

// Timers ----------------------------------------------------------
#define EM_HAL_SYSTICK
#define EM_TIM_DAQ             TIM3
#define EM_TIM_DAQ_MAX         65535
#define EM_TIM_DAQ_FREQ        EM_FREQ_PCLK1
#define EM_TIM_DAQ_IRQh        TIM3_IRQHandler
#define EM_TIM_PWM1            TIM2
#define EM_TIM_PWM1_MAX        65535
#define EM_TIM_PWM1_FREQ       EM_FREQ_PCLK1
#define EM_TIM_PWM1_CH         LL_TIM_CHANNEL_CH1
#define EM_TIM_PWM2            TIM4
#define EM_TIM_PWM2_MAX        65535
#define EM_TIM_PWM2_FREQ       EM_FREQ_PCLK1
#define EM_TIM_PWM2_CH         LL_TIM_CHANNEL_CH1
#define EM_TIM_CNTR            TIM1
#define EM_TIM_CNTR_FREQ       EM_FREQ_PCLK2
#define EM_TIM_CNTR_UP_IRQh    TIM1_UP_IRQHandler
#define EM_TIM_CNTR_MAX        65535
#define EM_TIM_CNTR_CH         LL_TIM_CHANNEL_CH1 // direct input capture - channel
#define EM_TIM_CNTR_CH2        LL_TIM_CHANNEL_CH2 // indirect input capture - channel
#define EM_TIM_CNTR_CCR        CCR1   // direct input capture - ccr register
#define EM_TIM_CNTR_CCR2       CCR3   // ovf store - ccr register
#define EM_TIM_CNTR_CC(a)      a##CC1 // direct input capture - cc name
#define EM_TIM_CNTR_CC2(a)     a##CC2 // indirect input capture - cc name
#define EM_TIM_CNTR_OVF(a)     a##CH3 // ovf store
#define EM_TIM_CNTR_PSC_FAST   8      // prescaler for fast mode
//#define EM_TIM_SGEN          TIM6
//#define EM_TIM_SGEN_FREQ     EM_FREQ_PCLK1
//#define EM_TIM_SGEN_MAX      65535

// Max values ------------------------------------------------------
#ifdef EM_SYSVIEW
#define EM_DAQ_MAX_MEM         7000  // DAQ memory is lees because SysView
#else
#define EM_DAQ_MAX_MEM         10000 // DAQ max total memory in release mode
#endif
#define EM_LA_MAX_FS           5142857   // Logic Analyzer max FS
#define EM_DAQ_MAX_B12_FS      857142    // DAQ ADC max fs per 1 channel - 12 bit
#define EM_DAQ_MAX_B8_FS       0         // DAQ ADC max fs per 1 channel - 8 bit
#define EM_PWM_MAX_F           (EM_TIM_PWM1_FREQ / 2)  // PWM max freq
#define EM_SGEN_MAX_F          5000000   // SGEB max output freq. TODO
#define EM_MEM_RESERVE         10        // DAQ circ buff memory reserve

// DMA -------------------------------------------------------------
#define EM_DMA_ADC1            DMA1
//#define EM_DMA_ADC2          DMA1
//#define EM_DMA_ADC3          DMA2
//#define EM_DMA_ADC4          DMA2
#define EM_DMA_LA              DMA1
#define EM_DMA_CNTR            DMA1
#define EM_DMA_CNTR2           DMA1
//#define EM_DMA_SGEN          DMA1

// DMA channels ----------------------------------------------------
#define EM_DMA_CH_ADC1         LL_DMA_CHANNEL_1
//#define EM_DMA_CH_ADC2       LL_DMA_CHANNEL_3
//#define EM_DMA_CH_ADC3       LL_DMA_CHANNEL_4
//#define EM_DMA_CH_ADC4       LL_DMA_CHANNEL_5
#define EM_DMA_CH_LA           LL_DMA_CHANNEL_6
#define EM_DMA_CH_CNTR         LL_DMA_CHANNEL_2
#define EM_DMA_CH_CNTR2        LL_DMA_CHANNEL_3
//#define EM_DMA_CH_SGEN       LL_DMA_CHANNEL_2

// IRQ map ---------------------------------------------------------
#define EM_IRQN_ADC12          ADC1_2_IRQn
//#define EM_IRQN_ADC3         ADC3_IRQn
//#define EM_IRQN_ADC4         ADC4_IRQn
#define EM_IRQN_UART           USART1_IRQn
#define EM_LA_IRQ_EXTI1        EXTI1_IRQn
#define EM_LA_IRQ_EXTI2        EXTI2_IRQn
#define EM_LA_IRQ_EXTI3        EXTI3_IRQn
#define EM_LA_IRQ_EXTI4        EXTI4_IRQn

// LA pins and IRQs ------------------------------------------------
#define EM_LA_EXTI_PORT        LL_GPIO_AF_EXTI_PORTA
#define EM_LA_EXTI1            LL_EXTI_LINE_1
#define EM_LA_EXTI2            LL_EXTI_LINE_2
#define EM_LA_EXTI3            LL_EXTI_LINE_3
#define EM_LA_EXTI4            LL_EXTI_LINE_4
#define EM_LA_EXTI_UNUSED      LL_EXTI_LINE_0
#define EM_LA_EXTILINE1        LL_GPIO_AF_EXTI_LINE1
#define EM_LA_EXTILINE2        LL_GPIO_AF_EXTI_LINE2
#define EM_LA_EXTILINE3        LL_GPIO_AF_EXTI_LINE3
#define EM_LA_EXTILINE4        LL_GPIO_AF_EXTI_LINE4
#define EM_LA_CH1_IRQh         EXTI1_IRQHandler
#define EM_LA_CH2_IRQh         EXTI2_IRQHandler
#define EM_LA_CH3_IRQh         EXTI3_IRQHandler
#define EM_LA_CH4_IRQh         EXTI4_IRQHandler
#define EM_LA_UNUSED_IRQh      EXTI0_IRQHandler

// ADC pins --------------------------------------------------------
#define EM_ADC_AWD1            LL_ADC_AWD_CHANNEL_1_REG
#define EM_ADC_AWD2            LL_ADC_AWD_CHANNEL_2_REG
#define EM_ADC_AWD3            LL_ADC_AWD_CHANNEL_3_REG
#define EM_ADC_AWD4            LL_ADC_AWD_CHANNEL_4_REG
#define EM_ADC_CH1             LL_ADC_CHANNEL_1
#define EM_ADC_CH2             LL_ADC_CHANNEL_2
#define EM_ADC_CH3             LL_ADC_CHANNEL_3
#define EM_ADC_CH4             LL_ADC_CHANNEL_4

// ADC - GPIO pins -------------------------------------------------
#define EM_GPIO_ADC_PORT1      GPIOA
#define EM_GPIO_ADC_PORT2      GPIOA
#define EM_GPIO_ADC_PORT3      GPIOA
#define EM_GPIO_ADC_PORT4      GPIOA
#define EM_GPIO_ADC_CH1        LL_GPIO_PIN_1
#define EM_GPIO_ADC_CH2        LL_GPIO_PIN_2
#define EM_GPIO_ADC_CH3        LL_GPIO_PIN_3
#define EM_GPIO_ADC_CH4        LL_GPIO_PIN_4

// LA - GPIO pins --------------------------------------------------
#define EM_GPIO_LA_PORT        GPIOA
#define EM_GPIO_LA_CH1         LL_GPIO_PIN_1
#define EM_GPIO_LA_CH2         LL_GPIO_PIN_2
#define EM_GPIO_LA_CH3         LL_GPIO_PIN_3
#define EM_GPIO_LA_CH4         LL_GPIO_PIN_4

// LA - GPIO pin numbers -------------------------------------------
#define EM_GPIO_LA_CH1_NUM     1
#define EM_GPIO_LA_CH2_NUM     2
#define EM_GPIO_LA_CH3_NUM     3
#define EM_GPIO_LA_CH4_NUM     4


#endif
#endif /* INC_CFG_CFG_F103C8_H_ */
