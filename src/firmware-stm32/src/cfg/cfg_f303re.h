/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_CFG_CFG_F303RE_H_
#define INC_CFG_CFG_F303RE_H_

#if defined(EM_F303RE)

#include "stm32f3xx.h"

/*
 * =========layout=========
 *  DAQ CH1 ........... PC0  (Arduino A5)   - both ADC + LA
 *  DAQ CH2 ........... PC1  (Arduino A4)   - both ADC + LA
 *  ADC CH3 ........... PB0  (Arduino A3)
 *  ADC CH4 ........... PB14 (Morpho CN10-28)
 *  LA  CH3 ........... PC2  (Morpho CN7-35)
 *  LA  CH4 ........... PC3  (Morpho CN7-37)
 *  PWM CH1 ........... PB10 (Arduino D6)
 *  PWM CH2 ........... PB8  (Arduino D15)
 *  CNTR .............. PC9  (Morpho CN10-1)
 *  DAC CH1 ........... PA4  (Arduino A2)
 *  DAC CH2 ........... PA5
 *  UART RX ........... PA3
 *  UART TX ........... PA2
 *  USB D- ............ PA11
 *  USB D+ ............ PA12
 *  =======================
*/

// device -----------------------------------------------------------
#define EM_DEV_NAME            "EMBO-STM32F303RE-Nucleo64"   // device specific name
#define EM_DEV_COMM            "USB + USART2 (115200 bps)"   // device comm methods
#define EM_LL_VER              "1.11.2"                      // STM32 CubeMX LL drivers

// pins ------------------------------------------------------------
#define EM_PINS_SCOPE_VM       "C0-C1-B0-B14"
#define EM_PINS_LA             "C0-C1-C2-C3"
#define EM_PINS_CNTR           "C9"
#define EM_PINS_PWM            "B8-B10"
#define EM_PINS_SGEN           "A4-A5"

// stack size ------------------------------------------------------
#define EM_STACK_MIN           128
#define EM_STACK_T1            128
#define EM_STACK_T2            128
#define EM_STACK_T3            128
#define EM_STACK_T4            512
#define EM_STACK_T5            128

// IRQ priorities --------------------------------------------------
#define EM_IT_PRI_CNTR         4   // counter - overflow bit
#define EM_IT_PRI_ADC          5   // analog watchdog ADC
#define EM_IT_PRI_EXTI         5   // logic analyzer GPIO
#define EM_IT_PRI_UART         6   // UART RX
#define EM_IT_PRI_USB          7   // USB RX
#define EM_IT_PRI_SYST         15  // systick

// freqs  -----------------------------------------------------------
#define EM_FREQ_LSI            40000     // LSI clock - wdg
#define EM_FREQ_HCLK           72000000  // HCLK clock - main
#define EM_FREQ_ADCCLK         72000000  // ADC clock
#define EM_FREQ_PCLK1          72000000  // APB1 clock
#define EM_FREQ_PCLK2          72000000  // APB2 clock
#define EM_FREQ_PLLCLK2_x2     144000000 // doubled PLL clock
#define EM_SYSTICK_FREQ        1000      // Systick clock

// UART -------------------------------------------------------------
#define EM_UART                USART2               // UART periph
#define EM_UART_RX_IRQHandler  USART2_IRQHandler    // UART IRQ handler
#define EM_UART_CLEAR_FLAG(x)  LL_USART_ClearFlag_RTO(x);  // RTO flags needs clearing
//#define EM_UART_CLEAR_FLAG(x)  LL_USART_ClearFlag_RXNE(x);  // RXNE flags needs clearing
#define EM_USB                                      // if emulated USB enabled
#define EM_UART_POLLINIT                            // if defined poll for init

// LED -------------------------------------------------------------
//#define EM_LED                                    // LED enabled
#define EM_LED_PORT            GPIOA                // main LED port
#define EM_LED_PIN             5                    // main LED pin
#define EM_LED_INVERTED                             // inverted behavior

// DAC -------------------------------------------------------------
#define EM_DAC                 DAC1                         // sgen ch.1 available
#define EM_DAC_CH              LL_DAC_CHANNEL_1             // sgen ch.1 channel
#define EM_DAC_SRC             LL_DAC_TRIG_EXT_TIM6_TRGO    // sgen ch.1 trigger source
#define EM_DAC2                DAC1                         // sgen ch.2 available
#define EM_DAC2_CH             LL_DAC_CHANNEL_2             // sgen ch.2 channel
#define EM_DAC2_SRC            LL_DAC_TRIG_EXT_TIM7_TRGO    // sgen ch.2 trigger source
#define EM_DAC_BUFF_LEN        1000                         // buffer max len
#define EM_DAC_MAX_VAL         4095.0                       // DAC max value
#define EM_DAC_TIM_MAX_F       4500000                      // DAC max sampling time

// GPIO ------------------------------------------------------------
#define EM_GPIO_EXTI_SRC       LL_SYSCFG_SetEXTISource      // GPIO EXTI source
#define EM_GPIO_EXTI_ACTIVE_R  LL_EXTI_IsActiveFlag_0_31    // GPIO EXTI is active rising?
#define EM_GPIO_EXTI_ACTIVE_F  LL_EXTI_IsActiveFlag_0_31    // GPIO EXTI is active falling?
#define EM_GPIO_EXTI_CLEAR_R   LL_EXTI_ClearFlag_0_31       // GPIO EXTI clear rising flag
#define EM_GPIO_EXTI_CLEAR_F   LL_EXTI_ClearFlag_0_31       // GPIO EXTI clear rising flag
//#define EM_GPIO_EXTI_R_F

// DAQ -------------------------------------------------------------
#define EM_DAQ_4CH   // if defined, DAQ operates with 4 channels, else with 2 channels

// ADC -------------------------------------------------------------
//#define EM_ADC_MODE_ADC1                                     // 1 ADC (1 DMA)               - verified
//#define EM_ADC_MODE_ADC12                                    // 2 full ADCs (2 DMA)         - verified
#define EM_ADC_MODE_ADC1234                                    // 4 full ADCs (4 DMA)         - verified
#define EM_ADC_BIT12                                           // 12-bit mode available       - verified
#define EM_ADC_BIT8                                            // 8-bit mode available        - verified
//#define EM_ADC_INTERLEAVED                                   // interleaved mode available  - TODO
//#define EM_ADC_DUALMODE                                      // dual mode available         - TODO

#define EM_VREF                3300                            // main voltage reference in mV
#define EM_ADC_VREF_CAL        *((uint16_t*)VREFINT_CAL_ADDR)  // Vref cal value
#define EM_ADC_VREF_CALVAL     3.3
#define EM_ADC_SMPLT_MAX       LL_ADC_SAMPLINGTIME_1CYCLE_5    // min sampling time in ticks
#define EM_ADC_SMPLT_MAX_N     1.5                             // min smpl time value
#define EM_ADC_TCONV8          8.5                             // ADC Tconversion ticks for 8-bit
#define EM_ADC_TCONV12         12.5                            // ADC Tconversion ticks for 12-bit
#define EM_ADC_C_F             0.000000000005 // 5pF           // ADC internal capacitance in F
#define EM_ADC_R_OHM           1000.0                          // ADC internal impedance in Ohm
#define EM_ADC_SMPLT_CNT       8                               // count of available smpl times
//#define EM_ADC_LINREG                                        // before calibration enable regulator
//#define EM_ADC_CAL_EN                                        // calibration while enabled
//#define LL_ADC_SPEC_START                                    // special start stop methods needed
#define EM_ADC_SEQ_CONF                                        // fully configurable sequencer
#define EM_ADC_AWD             LL_ADC_AWD1,                    // Analog Watchdog
#define EM_ADC_EN_TICKS        LL_ADC_DELAY_CALIB_ENABLE_ADC_CYCLES


// Timers ----------------------------------------------------------
//#define EM_HAL_SYSTICK
#define EM_TIM_DAQ             TIM3
#define EM_TIM_DAQ_MAX         65535
#define EM_TIM_DAQ_FREQ        EM_FREQ_PLLCLK2_x2
#define EM_TIM_DAQ_CC(a)       a##CC1
#define EM_TIM_PWM1            TIM2
#define EM_TIM_PWM1_MAX        65535
#define EM_TIM_PWM1_FREQ       EM_FREQ_PLLCLK2_x2
#define EM_TIM_PWM1_CH         LL_TIM_CHANNEL_CH3
#define EM_TIM_PWM1_CHN(a)     a##CH3
#define EM_TIM_PWM2            TIM4
#define EM_TIM_PWM2_MAX        65535
#define EM_TIM_PWM2_FREQ       EM_FREQ_PLLCLK2_x2
#define EM_TIM_PWM2_CH         LL_TIM_CHANNEL_CH3
#define EM_TIM_PWM2_CHN(a)     a##CH3
#define EM_TIM_CNTR            TIM8
#define EM_TIM_CNTR_FREQ       EM_FREQ_PLLCLK2_x2
#define EM_TIM_CNTR_UP_IRQh    TIM8_UP_IRQHandler
#define EM_TIM_CNTR_MAX        65535
#define EM_TIM_CNTR_CH         LL_TIM_CHANNEL_CH4 // direct input capture - channel
#define EM_TIM_CNTR_CH2        LL_TIM_CHANNEL_CH3 // indirect input capture - channel
#define EM_TIM_CNTR_CCR        CCR4   // direct input capture - ccr register
#define EM_TIM_CNTR_CCR2       CCR2   // ovf store - ccr register
#define EM_TIM_CNTR_CC(a)      a##CC4 // direct input capture - cc name
#define EM_TIM_CNTR_CC2(a)     a##CC3 // indirect input capture - cc name
#define EM_TIM_CNTR_OVF(a)     a##CH2 // ovf store
#define EM_TIM_CNTR_PSC_FAST   8      // prescaler for fast mode
#define EM_TIM_SGEN            TIM6
#define EM_TIM_SGEN_FREQ       EM_FREQ_PCLK1
#define EM_TIM_SGEN_MAX        65535
#define EM_TIM_SGEN2           TIM7
#define EM_TIM_SGEN2_FREQ      EM_FREQ_PCLK1
#define EM_TIM_SGEN2_MAX       65535

// max values ------------------------------------------------------
#ifdef EM_SYSVIEW
#define EM_DAQ_MAX_MEM         40000  // DAQ memory is lees because SysView
#else
#define EM_DAQ_MAX_MEM         44000  // DAQ max total memory in release mode
#endif
#define EM_LA_MAX_FS           14400000   // Logic Analyzer max FS
#define EM_DAQ_MAX_B12_FS      4965517    // DAQ ADC max fs per 1 channel - 12 bit
#define EM_DAQ_MAX_B8_FS       4965517    // DAQ ADC max fs per 1 channel - 8 bit TODO
#define EM_PWM_MAX_F           48000000   // PWM max freq
#define EM_SGEN_MAX_F          EM_DAC_TIM_MAX_F    // SGEN max output freq.
#define EM_CNTR_MAX_F          57000000   // CNTR max input frequency
#define EM_MEM_RESERVE         10         // DAQ circ buff memory reserve (min 2)

// ADC -------------------------------------------------------------
#define EM_ADC1                ADC1
#define EM_ADC2                ADC2
#define EM_ADC3                ADC3
#define EM_ADC4                ADC4

#define EM_ADC1_USED
#define EM_ADC2_USED
#define EM_ADC3_USED
#define EM_ADC4_USED

#define EM_ADC12_IRQh          ADC1_2_IRQHandler
#define EM_ADC3_IRQh           ADC3_IRQHandler
#define EM_ADC4_IRQh           ADC4_IRQHandler

// DMA -------------------------------------------------------------
#define EM_DMA_ADC1            DMA1
#define EM_DMA_ADC2            DMA2
#define EM_DMA_ADC3            DMA2
#define EM_DMA_ADC4            DMA2
#define EM_DMA_LA              DMA1
#define EM_DMA_CNTR            DMA2
#define EM_DMA_CNTR2           DMA2
#define EM_DMA_SGEN            DMA1
#define EM_DMA_SGEN2           DMA1

// DMA channels ----------------------------------------------------
#define EM_DMA_CH_ADC1         LL_DMA_CHANNEL_1
#define EM_DMA_CH_ADC2         LL_DMA_CHANNEL_3
#define EM_DMA_CH_ADC3         LL_DMA_CHANNEL_5
#define EM_DMA_CH_ADC4         LL_DMA_CHANNEL_4
#define EM_DMA_CH_LA           LL_DMA_CHANNEL_6
#define EM_DMA_CH_CNTR         LL_DMA_CHANNEL_2
#define EM_DMA_CH_CNTR2        LL_DMA_CHANNEL_1
#define EM_DMA_CH_SGEN         LL_DMA_CHANNEL_3
#define EM_DMA_CH_SGEN2        LL_DMA_CHANNEL_4

// IRQ map ---------------------------------------------------------
#define EM_IRQN_ADC1           ADC1_2_IRQn
#define EM_IRQN_ADC2           ADC1_2_IRQn
#define EM_IRQN_ADC3           ADC3_IRQn
#define EM_IRQN_ADC4           ADC4_IRQn
#define EM_IRQN_UART           USART2_IRQn
#define EM_LA_IRQ_EXTI1        EXTI0_IRQn
#define EM_LA_IRQ_EXTI2        EXTI1_IRQn
#define EM_LA_IRQ_EXTI3        EXTI2_TSC_IRQn
#define EM_LA_IRQ_EXTI4        EXTI3_IRQn
#define EM_CNTR_IRQ            TIM8_UP_IRQn

// IRQ helpers -----------------------------------------------------
#define EM_IRQ_ADC1            EM_IRQN_ADC1
#define EM_IRQ_ADC2            EM_IRQN_ADC2
#define EM_IRQ_ADC3            EM_IRQN_ADC3
#define EM_IRQ_ADC4            EM_IRQN_ADC4

// LA pins and IRQs ------------------------------------------------
#define EM_LA_EXTI_PORT        LL_SYSCFG_EXTI_PORTC
#define EM_LA_EXTI1            LL_EXTI_LINE_0
#define EM_LA_EXTI2            LL_EXTI_LINE_1
#define EM_LA_EXTI3            LL_EXTI_LINE_2
#define EM_LA_EXTI4            LL_EXTI_LINE_3
#define EM_LA_EXTI_UNUSED      LL_EXTI_LINE_4
#define EM_LA_EXTILINE1        LL_SYSCFG_EXTI_LINE0
#define EM_LA_EXTILINE2        LL_SYSCFG_EXTI_LINE1
#define EM_LA_EXTILINE3        LL_SYSCFG_EXTI_LINE2
#define EM_LA_EXTILINE4        LL_SYSCFG_EXTI_LINE3
#define EM_LA_CH1_IRQh         EXTI0_IRQHandler
#define EM_LA_CH2_IRQh         EXTI1_IRQHandler
#define EM_LA_CH3_IRQh         EXTI2_TSC_IRQHandler
#define EM_LA_CH4_IRQh         EXTI3_IRQHandler
#define EM_LA_UNUSED_IRQh      EXTI4_IRQHandler

// LA IRQ dynamic handlers ---------------------------------------
#define EM_LA_IRQ1_CH1         la_irq_ch1
#define EM_LA_IRQ2_CH2         la_irq_ch2
#define EM_LA_IRQ3_CH3         la_irq_ch3
#define EM_LA_IRQ4_CH4         la_irq_ch4

// ADC pins --------------------------------------------------------
#define EM_ADC_AWD1            LL_ADC_AWD_CHANNEL_6_REG
#define EM_ADC_AWD2            LL_ADC_AWD_CHANNEL_7_REG
#define EM_ADC_AWD3            LL_ADC_AWD_CHANNEL_12_REG
#define EM_ADC_AWD4            LL_ADC_AWD_CHANNEL_4_REG
#define EM_ADC_CH1             LL_ADC_CHANNEL_6
#define EM_ADC_CH2             LL_ADC_CHANNEL_7
#define EM_ADC_CH3             LL_ADC_CHANNEL_12
#define EM_ADC_CH4             LL_ADC_CHANNEL_4

// ADC - GPIO pins -------------------------------------------------
#define EM_GPIO_ADC_PORT1      GPIOC
#define EM_GPIO_ADC_PORT2      GPIOC
#define EM_GPIO_ADC_PORT3      GPIOB
#define EM_GPIO_ADC_PORT4      GPIOB
#define EM_GPIO_ADC_CH1        LL_GPIO_PIN_0
#define EM_GPIO_ADC_CH2        LL_GPIO_PIN_1
#define EM_GPIO_ADC_CH3        LL_GPIO_PIN_0
#define EM_GPIO_ADC_CH4        LL_GPIO_PIN_14

// LA - GPIO pins --------------------------------------------------
#define EM_GPIO_LA_PORT        GPIOC
#define EM_GPIO_LA_OFFSET      0
#define EM_GPIO_LA_CH1         LL_GPIO_PIN_0
#define EM_GPIO_LA_CH2         LL_GPIO_PIN_1
#define EM_GPIO_LA_CH3         LL_GPIO_PIN_2
#define EM_GPIO_LA_CH4         LL_GPIO_PIN_3

// LA - GPIO pin numbers -------------------------------------------
#define EM_GPIO_LA_CH1_NUM     0
#define EM_GPIO_LA_CH2_NUM     1
#define EM_GPIO_LA_CH3_NUM     2
#define EM_GPIO_LA_CH4_NUM     3

#endif
#endif /* INC_CFG_CFG_F303RE_H_ */
