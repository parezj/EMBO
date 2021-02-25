/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_CFG_CFG_F303RE_H_
#define INC_CFG_CFG_F303RE_H_

#if defined(STM32F303xE)

#include "stm32f3xx.h"

/*
 * =========layout=========
 *  DAQ CH1 ........... PC0  (Arduino A5)   - both ADC + LA
 *  DAQ CH2 ........... PC1  (Arduino A4)   - both ADC + LA
 *  ADC CH3 ........... PB0  (Arduino A3)
 *  ADC CH4 ........... PB14 (Morpho CN10-28)
 *  LA  CH3 ........... PC2  (Morpho CN7-35)
 *  LA  CH4 ........... PC3  (Morpho CN7-37)
 *  PWM CH1 ........... PB8  (Arduino D15)
 *  PWM CH2 ........... PB10 (Arduino D6)
 *  CNTR .............. PC9  (Morpho CN10-1)
 *  DAC ............... PA4  (Arduino A2)
 *  =======================
*/

// freqs  -----------------------------------------------------------
#define EM_FREQ_LSI            40000     // LSI clock - wdg
#define EM_FREQ_HCLK           72000000  // HCLK clock - main
#define EM_FREQ_ADCCLK         72000000  // ADC clock
#define EM_FREQ_PCLK1          72000000  // APB1 clock - TIM2,3,4
#define EM_FREQ_PCLK2          72000000  // APB2 clock - TIM1
#define EM_SYSTICK_FREQ        1000      // Systick clock

// device name ------------------------------------------------------
#define EM_DEV_NAME            "EMBO-STM32F303RE-Nucleo64"   // device specific name

// UART -------------------------------------------------------------
#define EM_UART                USART2               // UART periph
#define EM_UART_RX_IRQHandler  USART2_IRQHandler    // UART IRQ handler
#define EM_UART_CLEAR_FLAG(x)  LL_USART_ClearFlag_RTO(x);  // RTO flags needs clearing
//#define EM_UART_CLEAR_FLAG(x)  LL_USART_ClearFlag_RXNE(x);  // RXNE flags needs clearing
//#define EM_USB                                    // if emulated USB enabled

// LED -------------------------------------------------------------
#define EM_LED_PORT            GPIOA                // main LED port
#define EM_LED_PIN             5                    // main LED pin

// DAC -------------------------------------------------------------
#define EM_DAC                 DAC1                 // sgen available
#define EM_DAC_CH              LL_DAC_CHANNEL_1     // DAC channel
#define EM_DAC_BUFF_LEN        1000                 // sgen buffer max len
#define EM_DAC_MAX_VAL         4095.0               // DAC max value

// GPIO ------------------------------------------------------------
#define EM_GPIO_EXTI_SRC       LL_SYSCFG_SetEXTISource         // GPIO EXTI source

// ADC -------------------------------------------------------------
//#define EM_ADC_MODE_ADC1                                     // 1 ADC (1 DMA)               - N/A
//#define EM_ADC_MODE_ADC12                                    // 2 full ADCs (2 DMA)         - N/A
#define EM_ADC_MODE_ADC1234                                    // 4 full ADCs (4 DMA)         - TODO
#define EM_ADC_BIT12                                           // 12-bit mode available       - TODO
#define EM_ADC_BIT8                                            // 8-bit mode available        - TODO
//#define EM_ADC_INTERLEAVED                                   // interleaved mode available  - N/A ??
//#define EM_ADC_DUALMODE                                      // dual mode available         - N/A

//#define EM_ADC_VREF_CAL      1200                            // vref cal value
#define EM_ADC_VREF_CAL        *((uint16_t*)VREFINT_CAL_ADDR)  // Vref cal value TODO
#define EM_ADC_SMPLT_MAX       LL_ADC_SAMPLINGTIME_1CYCLE_5    // max sampling time in ticks
#define EM_ADC_SMPLT_MAX_N     1.5                             // max smpl time value
#define EM_ADC_TCONV8          8.5                             // ADC Tconversion ticks for 8-bit
#define EM_ADC_TCONV12         12.5                            // ADC Tconversion ticks for 12-bit
#define EM_ADC_C_F             0.000000008 // 8pF              // ADC internal capacitance in F
#define EM_ADC_R_KOHM          1.0                             // ADC internal impedance in kOhm
#define EM_ADC_SMPLT_CNT       8                               // count of available smpl times
#define EM_ADC_CAL_EN                                          // calibration while enabled
//#define LL_ADC_SPEC_START                                    // special start stop methods needed
#define EM_ADC_AWD             LL_ADC_AWD1,                    // Analog Watchdog
#define EM_ADC_TRIG_12         LL_ADC_REG_TRIG_EXT_TIM3_TRGO_ADC12     // ADC TIM trig TRGO 12
#define EM_ADC_TRIG_34         LL_ADC_REG_TRIG_EXT_TIM3_TRGO__ADC34    // ADC TIM trig TRGO 34
#define EM_ADC_EN_TICKS        LL_ADC_DELAY_CALIB_ENABLE_ADC_CYCLES


// Timers ----------------------------------------------------------
//#define EM_HAL_SYSTICK
#define EM_TIM_DAQ             TIM3
#define EM_TIM_DAQ_MAX         65535
#define EM_TIM_DAQ_FREQ        EM_FREQ_PCLK1
#define EM_TIM_DAQ_IRQh        TIM3_IRQHandler
#define EM_TIM_PWM1            TIM4
#define EM_TIM_PWM1_MAX        65535
#define EM_TIM_PWM1_FREQ       EM_FREQ_PCLK1
#define EM_TIM_PWM1_CH         LL_TIM_CHANNEL_CH3
#define EM_TIM_PWM2            TIM2
#define EM_TIM_PWM2_MAX        65535
#define EM_TIM_PWM2_FREQ       EM_FREQ_PCLK1
#define EM_TIM_PWM2_CH         LL_TIM_CHANNEL_CH3
#define EM_TIM_CNTR            TIM8
#define EM_TIM_CNTR_FREQ       EM_FREQ_PCLK2
#define EM_TIM_CNTR_UP_IRQh    TIM8_UP_IRQHandler
#define EM_TIM_CNTR_CCR_IRQh   TIM8_CC_IRQHandler
#define EM_TIM_CNTR_MAX        65535
#define EM_TIM_CNTR_CH         LL_TIM_CHANNEL_CH4 // direct input capture - channel
#define EM_TIM_CNTR_CH2        LL_TIM_CHANNEL_CH3 // indirect input capture - channel
#define EM_TIM_CNTR_CCR        CCR4   // direct input capture - ccr register
#define EM_TIM_CNTR_CCR2       CCR1   // ovf store - ccr register
#define EM_TIM_CNTR_CC(a)      a##CC4 // direct input capture - cc name
#define EM_TIM_CNTR_CC2(a)     a##CC3 // indirect input capture - cc name
#define EM_TIM_CNTR_OVF(a)     a##CH1 // ovf store
#define EM_TIM_SGEN            TIM6
#define EM_TIM_SGEN_FREQ       EM_FREQ_PCLK1
#define EM_TIM_SGEN_MAX        65535

// Max values ------------------------------------------------------
#define EM_DAQ_MAX_MEM         50000     // DAQ max total memory
#define EM_LA_MAX_FS           5000000   // Logic Analyzer max FS
#define EM_DAQ_MAX_B12_FS      400000    // DAQ ADC max fs per 1 channel - 12 bit
#define EM_DAQ_MAX_B8_FS       500000    // DAQ ADC max fs per 1 channel - 8 bit
#define EM_PWM_MAX_F           1000000   // PWM max freq - TODO
#define EM_MEM_RESERVE         10        // DAQ circ buff memory reserve (min 2)

// DMA -------------------------------------------------------------
#define EM_DMA_ADC1            DMA1
#define EM_DMA_ADC2            DMA2
#define EM_DMA_ADC3            DMA2
#define EM_DMA_ADC4            DMA2
#define EM_DMA_LA              DMA1
#define EM_DMA_CNTR            DMA2
#define EM_DMA_CNTR2           DMA2
#define EM_DMA_SGEN            DMA1

// DMA channels ----------------------------------------------------
#define EM_DMA_CH_ADC1         LL_DMA_CHANNEL_1
#define EM_DMA_CH_ADC2         LL_DMA_CHANNEL_1
#define EM_DMA_CH_ADC3         LL_DMA_CHANNEL_5
#define EM_DMA_CH_ADC4         LL_DMA_CHANNEL_2
#define EM_DMA_CH_LA           LL_DMA_CHANNEL_6
#define EM_DMA_CH_CNTR         LL_DMA_CHANNEL_2
#define EM_DMA_CH_CNTR2        LL_DMA_CHANNEL_3
#define EM_DMA_CH_SGEN         LL_DMA_CHANNEL_3

// IRQ map ---------------------------------------------------------
#define EM_IRQN_ADC12          ADC1_2_IRQn
#define EM_IRQN_ADC3           ADC3_IRQn
#define EM_IRQN_ADC4           ADC4_IRQn
#define EM_IRQN_UART           USART2_IRQn
#define EM_LA_IRQ_EXTI1        EXTI0_IRQn
#define EM_LA_IRQ_EXTI2        EXTI1_IRQn
#define EM_LA_IRQ_EXTI3        EXTI2_TSC_IRQn
#define EM_LA_IRQ_EXTI4        EXTI3_IRQn

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
