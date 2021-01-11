/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef CFG_H
#define CFG_H

#include <utility.h>

/*-----------------------------------------------------------------------------------------------------------+
 +                                                  general                                                  +
 +-----------------------------------------------------------------------------------------------------------*/

#define PS_DEBUG

#define PS_DEV_VER             "0.1.5"
#define PS_DEV_AUTHOR          "CTU/Jakub Parez"

/*-----------------------------------------------------------------------------------------------------------+
 +                                               board specific                                              +
 +-----------------------------------------------------------------------------------------------------------*/

/*................................................... F103 ..................................................*/

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
 *  =======================
*/

// freqs  -----------------------------------------------------------
#define PS_FREQ_LSI            40000     // LSI clock - wdg
#define PS_FREQ_HCLK           72000000  // HCLK clock - main
#define PS_FREQ_ADCCLK         12000000  // ADC clock
#define PS_FREQ_PCLK1          72000000  // APB1 clock - TIM2,3,4
#define PS_FREQ_PCLK2          72000000  // APB2 clock - TIM1
#define PS_SYSTICK_FREQ        1000      // Systick clock

// device name ------------------------------------------------------
#define PS_DEV_NAME            "PillScope-F103C8"   // device specific name

// UART -------------------------------------------------------------
#define PS_UART                USART1               // UART periph
#define PS_UART_RX_IRQHandler  USART1_IRQHandler    // UART IRQ handler
//#define PS_UART_CLEAR_FLAG(x)  LL_USART_ClearFlag_RTO(x);  // RTO flags needs clearing
#define PS_UART_CLEAR_FLAG(x)  LL_USART_ClearFlag_RXNE(x);  // RXNE flags needs clearing
#define PS_USB                                      // if emulated USB enabled

// LED -------------------------------------------------------------
#define PS_LED_PORT            GPIOC                // main LED port
#define PS_LED_PIN             13                   // main LED pin

// DAC -------------------------------------------------------------
//#define PS_DAC               DAC1                 // sgen available
//#define PS_DAC_CH            LL_DAC_CHANNEL_1     // DAC channel
//#define PS_DAC_BUFF_LEN      1000                 // buffer max len

// GPIO ------------------------------------------------------------
#define PS_GPIO_EXTI_SRC       LL_GPIO_AF_SetEXTISource        // GPIO EXTI source

// ADC -------------------------------------------------------------
#define PS_ADC_MODE_ADC1                                       // 1 ADC (1 DMA)
//#define PS_ADC_MODE_ADC12                                    // 2 full ADCs (2 DMA)
//#define PS_ADC_MODE_ADC1234                                  // 4 full ADCs (4 DMA)
#define PS_ADC_BIT12                                           // 12-bit mode available
//#define PS_ADC_BIT8                                          // 8-bit mode available
//#define PS_ADC_INTERLEAVED                                   // interleaved mode available
//#define PS_ADC_DUALMODE                                      // dual mode available

#define PS_ADC_VREF_CAL        1200                            // vref cal value
//#define PS_ADC_VREF_CAL      *((uint16_t*)VREFINT_CAL_ADDR)  // Vref cal value
#define PS_ADC_SMPLT_MAX       LL_ADC_SAMPLINGTIME_1CYCLE_5    // max sampling time in ticks
#define PS_ADC_SMPLT_MAX_N     1.5                             // max smpl time value
#define PS_ADC_TCONV8          8.5                             // ADC Tconversion ticks for 8-bit
#define PS_ADC_TCONV12         12.5                            // ADC Tconversion ticks for 12-bit
#define PS_ADC_C_F             0.000000008 // 8pF              // ADC internal capacitance in F
#define PS_ADC_R_KOHM          1.0                             // ADC internal impedance in kOhm
#define PS_ADC_SMPLT_CNT       8                               // count of available smpl times
#define PS_ADC_CAL_EN                                          // calibration while enabled
#define LL_ADC_SPEC_START                                      // special start stop methods needed
#define PS_ADC_AWD                                             // Analog Watchdog
#define PS_ADC_TRIG_12         LL_ADC_REG_TRIG_EXT_TIM3_TRGO   // ADC TIM trig TRGO 12
//#define PS_ADC_TRIG_34       LL_ADC_REG_TRIG_EXT_TIM3_TRGO   // ADC TIM trig TRGO 34
#define PS_ADC_EN_TICKS        LL_ADC_DELAY_ENABLE_CALIB_ADC_CYCLES

// Timers ----------------------------------------------------------
#define PS_HAL_SYSTICK
#define PS_TIM_DAQ             TIM3
#define PS_TIM_DAQ_MAX         65535
#define PS_TIM_DAQ_FREQ        PS_FREQ_PCLK1
#define PS_TIM_DAQ_IRQh        TIM3_IRQHandler
#define PS_TIM_PWM1            TIM2
#define PS_TIM_PWM1_MAX        65535
#define PS_TIM_PWM1_FREQ       PS_FREQ_PCLK1
#define PS_TIM_PWM1_CH         LL_TIM_CHANNEL_CH1
#define PS_TIM_PWM2            TIM4
#define PS_TIM_PWM2_MAX        65535
#define PS_TIM_PWM2_FREQ       PS_FREQ_PCLK1
#define PS_TIM_PWM2_CH         LL_TIM_CHANNEL_CH1
#define PS_TIM_CNTR            TIM1
#define PS_TIM_CNTR_FREQ       PS_FREQ_PCLK2
#define PS_TIM_CNTR_UP_IRQh    TIM1_UP_IRQHandler
#define PS_TIM_CNTR_CCR_IRQh   TIM1_CC_IRQHandler
#define PS_TIM_CNTR_MAX        65535
#define PS_TIM_CNTR_CH         LL_TIM_CHANNEL_CH1
#define PS_TIM_CNTR_CCR        CCR1
#define PS_TIM_CNTR_CC(a)      a##CC1
//#define PS_TIM_SGEN          TIM6
//#define PS_TIM_SGEN_FREQ     PS_FREQ_PCLK1
//#define PS_TIM_SGEN_MAX      65535

// Max values ------------------------------------------------------
#define PS_DAQ_MAX_MEM         9000      // DAQ max total memory
#define PS_LA_MAX_FS           5000000   // Logic Analyzer max FS
#define PS_DAQ_MAX_B12_FS      800000    // DAQ ADC max fs per 1 channel - 12 bit
#define PS_DAQ_MAX_B8_FS       0         // DAQ ADC max fs per 1 channel - 8 bit
#define PS_PWM_MAX_F           1000000   // PWM max freq - TODO
#define PS_MEM_RESERVE         10        // DAQ circ buff memory reserve (min 2)

// DMA -------------------------------------------------------------
#define PS_DMA_ADC1            DMA1
//#define PS_DMA_ADC2          DMA1
//#define PS_DMA_ADC3          DMA2
//#define PS_DMA_ADC4          DMA2
#define PS_DMA_LA              DMA1
#define PS_DMA_CNTR            DMA1
//#define PS_DMA_SGEN          DMA1

// DMA channels ----------------------------------------------------
#define PS_DMA_CH_ADC1         LL_DMA_CHANNEL_1
//#define PS_DMA_CH_ADC2       LL_DMA_CHANNEL_3
//#define PS_DMA_CH_ADC3       LL_DMA_CHANNEL_4
//#define PS_DMA_CH_ADC4       LL_DMA_CHANNEL_5
#define PS_DMA_CH_LA           LL_DMA_CHANNEL_6
#define PS_DMA_CH_CNTR         LL_DMA_CHANNEL_2
//#define PS_DMA_CH_SGEN       LL_DMA_CHANNEL_2

// IRQ map ---------------------------------------------------------
#define PS_IRQN_ADC12          ADC1_2_IRQn
//#define PS_IRQN_ADC3         ADC3_IRQn
//#define PS_IRQN_ADC4         ADC4_IRQn
#define PS_IRQN_UART           USART1_IRQn
#define PS_IRQN_DAQ_TIM        TIM3_IRQn
#define PS_LA_IRQ_EXTI1        EXTI1_IRQn
#define PS_LA_IRQ_EXTI2        EXTI2_IRQn
#define PS_LA_IRQ_EXTI3        EXTI3_IRQn
#define PS_LA_IRQ_EXTI4        EXTI4_IRQn

// LA pins and IRQs ------------------------------------------------
#define PS_LA_EXTI_PORT        LL_GPIO_AF_EXTI_PORTA

#define PS_LA_EXTI1            LL_EXTI_LINE_1
#define PS_LA_EXTI2            LL_EXTI_LINE_2
#define PS_LA_EXTI3            LL_EXTI_LINE_3
#define PS_LA_EXTI4            LL_EXTI_LINE_4
#define PS_LA_EXTI_UNUSED      LL_EXTI_LINE_0
#define PS_LA_EXTILINE1        LL_GPIO_AF_EXTI_LINE1
#define PS_LA_EXTILINE2        LL_GPIO_AF_EXTI_LINE2
#define PS_LA_EXTILINE3        LL_GPIO_AF_EXTI_LINE3
#define PS_LA_EXTILINE4        LL_GPIO_AF_EXTI_LINE4
#define PS_LA_CH1_IRQh         EXTI1_IRQHandler
#define PS_LA_CH2_IRQh         EXTI2_IRQHandler
#define PS_LA_CH3_IRQh         EXTI3_IRQHandler
#define PS_LA_CH4_IRQh         EXTI4_IRQHandler
#define PS_LA_UNUSED_IRQh      EXTI0_IRQHandler

// ADC pins --------------------------------------------------------
#define PS_ADC_AWD1            LL_ADC_AWD_CHANNEL_1_REG
#define PS_ADC_AWD2            LL_ADC_AWD_CHANNEL_2_REG
#define PS_ADC_AWD3            LL_ADC_AWD_CHANNEL_3_REG
#define PS_ADC_AWD4            LL_ADC_AWD_CHANNEL_4_REG
#define PS_ADC_CH1             LL_ADC_CHANNEL_1
#define PS_ADC_CH2             LL_ADC_CHANNEL_2
#define PS_ADC_CH3             LL_ADC_CHANNEL_3
#define PS_ADC_CH4             LL_ADC_CHANNEL_4

// ADC - GPIO pins --------------------------------------------------
#define PS_GPIO_ADC_PORT1      GPIOA
#define PS_GPIO_ADC_PORT2      GPIOA
#define PS_GPIO_ADC_PORT3      GPIOA
#define PS_GPIO_ADC_PORT4      GPIOA
#define PS_GPIO_ADC_CH1        LL_GPIO_PIN_1
#define PS_GPIO_ADC_CH2        LL_GPIO_PIN_2
#define PS_GPIO_ADC_CH3        LL_GPIO_PIN_3
#define PS_GPIO_ADC_CH4        LL_GPIO_PIN_4

// LA - GPIO pins --------------------------------------------------
#define PS_GPIO_LA_PORT        GPIOA
#define PS_GPIO_LA_CH1         LL_GPIO_PIN_1
#define PS_GPIO_LA_CH2         LL_GPIO_PIN_2
#define PS_GPIO_LA_CH3         LL_GPIO_PIN_3
#define PS_GPIO_LA_CH4         LL_GPIO_PIN_4

#elif defined(STM32F303xE)

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
#define PS_FREQ_LSI            40000     // LSI clock - wdg
#define PS_FREQ_HCLK           72000000  // HCLK clock - main
#define PS_FREQ_ADCCLK         72000000  // ADC clock
#define PS_FREQ_PCLK1          72000000  // APB1 clock - TIM2,3,4
#define PS_FREQ_PCLK2          72000000  // APB2 clock - TIM1
#define PS_SYSTICK_FREQ        1000      // Systick clock

// device name ------------------------------------------------------
#define PS_DEV_NAME            "PillScope-F303RE"   // device specific name

// UART -------------------------------------------------------------
#define PS_UART                USART2               // UART periph
#define PS_UART_RX_IRQHandler  USART2_IRQHandler    // UART IRQ handler
#define PS_UART_CLEAR_FLAG(x)  LL_USART_ClearFlag_RTO(x);  // RTO flags needs clearing
//#define PS_UART_CLEAR_FLAG(x)  LL_USART_ClearFlag_RXNE(x);  // RXNE flags needs clearing
//#define PS_USB                                    // if emulated USB enabled

// LED -------------------------------------------------------------
#define PS_LED_PORT            GPIOA                // main LED port
#define PS_LED_PIN             5                    // main LED pin

// DAC -------------------------------------------------------------
#define PS_DAC                 DAC1                 // sgen available
#define PS_DAC_CH              LL_DAC_CHANNEL_1     // DAC channel
#define PS_DAC_BUFF_LEN        1000                 // sgen buffer max len

// GPIO ------------------------------------------------------------
#define PS_GPIO_EXTI_SRC       LL_SYSCFG_SetEXTISource         // GPIO EXTI source

// ADC -------------------------------------------------------------
//#define PS_ADC_MODE_ADC1                                     // 1 ADC (1 DMA)
//#define PS_ADC_MODE_ADC12                                    // 2 full ADCs (2 DMA)
#define PS_ADC_MODE_ADC1234                                    // 4 full ADCs (4 DMA)
#define PS_ADC_BIT12                                           // 12-bit mode available
#define PS_ADC_BIT8                                            // 8-bit mode available
//#define PS_ADC_INTERLEAVED                                   // interleaved mode available
//#define PS_ADC_DUALMODE                                      // dual mode available

//#define PS_ADC_VREF_CAL      1200                            // vref cal value
#define PS_ADC_VREF_CAL        *((uint16_t*)VREFINT_CAL_ADDR)  // Vref cal value TODO
#define PS_ADC_SMPLT_MAX       LL_ADC_SAMPLINGTIME_1CYCLE_5    // max sampling time in ticks
#define PS_ADC_SMPLT_MAX_N     1.5                             // max smpl time value
#define PS_ADC_TCONV8          8.5                             // ADC Tconversion ticks for 8-bit
#define PS_ADC_TCONV12         12.5                            // ADC Tconversion ticks for 12-bit
#define PS_ADC_C_F             0.000000008 // 8pF              // ADC internal capacitance in F
#define PS_ADC_R_KOHM          1.0                             // ADC internal impedance in kOhm
#define PS_ADC_SMPLT_CNT       8                               // count of available smpl times
#define PS_ADC_CAL_EN                                          // calibration while enabled
//#define LL_ADC_SPEC_START                                    // special start stop methods needed
#define PS_ADC_AWD             LL_ADC_AWD1,                    // Analog Watchdog
#define PS_ADC_TRIG_12         LL_ADC_REG_TRIG_EXT_TIM3_TRGO_ADC12     // ADC TIM trig TRGO 12
#define PS_ADC_TRIG_34         LL_ADC_REG_TRIG_EXT_TIM3_TRGO__ADC34    // ADC TIM trig TRGO 34
#define PS_ADC_EN_TICKS        LL_ADC_DELAY_CALIB_ENABLE_ADC_CYCLES


// Timers ----------------------------------------------------------
//#define PS_HAL_SYSTICK
#define PS_TIM_DAQ             TIM3
#define PS_TIM_DAQ_MAX         65535
#define PS_TIM_DAQ_FREQ        PS_FREQ_PCLK1
#define PS_TIM_DAQ_IRQh        TIM3_IRQHandler
#define PS_TIM_PWM1            TIM4
#define PS_TIM_PWM1_MAX        65535
#define PS_TIM_PWM1_FREQ       PS_FREQ_PCLK1
#define PS_TIM_PWM1_CH         LL_TIM_CHANNEL_CH3
#define PS_TIM_PWM2            TIM2
#define PS_TIM_PWM2_MAX        65535
#define PS_TIM_PWM2_FREQ       PS_FREQ_PCLK1
#define PS_TIM_PWM2_CH         LL_TIM_CHANNEL_CH3
#define PS_TIM_CNTR            TIM8
#define PS_TIM_CNTR_FREQ       PS_FREQ_PCLK2
#define PS_TIM_CNTR_UP_IRQh    TIM8_UP_IRQHandler
#define PS_TIM_CNTR_CCR_IRQh   TIM8_CC_IRQHandler
#define PS_TIM_CNTR_MAX        65535
#define PS_TIM_CNTR_CH         LL_TIM_CHANNEL_CH4
#define PS_TIM_CNTR_CCR        CCR4
#define PS_TIM_CNTR_CC(a)      a##CC4
#define PS_TIM_SGEN            TIM6
#define PS_TIM_SGEN_FREQ       PS_FREQ_PCLK1
#define PS_TIM_SGEN_MAX        65535

// Max values ------------------------------------------------------
#define PS_DAQ_MAX_MEM         45000     // DAQ max total memory
#define PS_LA_MAX_FS           5000000   // Logic Analyzer max FS
#define PS_DAQ_MAX_B12_FS      400000    // DAQ ADC max fs per 1 channel - 12 bit
#define PS_DAQ_MAX_B8_FS       500000    // DAQ ADC max fs per 1 channel - 8 bit
#define PS_PWM_MAX_F           1000000   // PWM max freq - TODO
#define PS_MEM_RESERVE         10        // DAQ circ buff memory reserve (min 2)

// DMA -------------------------------------------------------------
#define PS_DMA_ADC1            DMA1
#define PS_DMA_ADC2            DMA2
#define PS_DMA_ADC3            DMA2
#define PS_DMA_ADC4            DMA2
#define PS_DMA_LA              DMA1
#define PS_DMA_CNTR            DMA2
#define PS_DMA_SGEN            DMA1

// DMA channels ----------------------------------------------------
#define PS_DMA_CH_ADC1         LL_DMA_CHANNEL_1
#define PS_DMA_CH_ADC2         LL_DMA_CHANNEL_1
#define PS_DMA_CH_ADC3         LL_DMA_CHANNEL_5
#define PS_DMA_CH_ADC4         LL_DMA_CHANNEL_2
#define PS_DMA_CH_LA           LL_DMA_CHANNEL_6
#define PS_DMA_CH_CNTR         LL_DMA_CHANNEL_2
#define PS_DMA_CH_SGEN         LL_DMA_CHANNEL_3

// IRQ map ---------------------------------------------------------
#define PS_IRQN_ADC12          ADC1_2_IRQn
#define PS_IRQN_ADC3           ADC3_IRQn
#define PS_IRQN_ADC4           ADC4_IRQn
#define PS_IRQN_UART           USART2_IRQn
#define PS_IRQN_DAQ_TIM        TIM3_IRQn
#define PS_LA_IRQ_EXTI1        EXTI0_IRQn
#define PS_LA_IRQ_EXTI2        EXTI1_IRQn
#define PS_LA_IRQ_EXTI3        EXTI2_TSC_IRQn
#define PS_LA_IRQ_EXTI4        EXTI3_IRQn

// LA pins and IRQs ------------------------------------------------
#define PS_LA_EXTI_PORT        LL_SYSCFG_EXTI_PORTC
#define PS_LA_EXTI1            LL_EXTI_LINE_0
#define PS_LA_EXTI2            LL_EXTI_LINE_1
#define PS_LA_EXTI3            LL_EXTI_LINE_2
#define PS_LA_EXTI4            LL_EXTI_LINE_3
#define PS_LA_EXTI_UNUSED      LL_EXTI_LINE_4
#define PS_LA_EXTILINE1        LL_SYSCFG_EXTI_LINE0
#define PS_LA_EXTILINE2        LL_SYSCFG_EXTI_LINE1
#define PS_LA_EXTILINE3        LL_SYSCFG_EXTI_LINE2
#define PS_LA_EXTILINE4        LL_SYSCFG_EXTI_LINE3
#define PS_LA_CH1_IRQh         EXTI0_IRQHandler
#define PS_LA_CH2_IRQh         EXTI1_IRQHandler
#define PS_LA_CH3_IRQh         EXTI2_TSC_IRQHandler
#define PS_LA_CH4_IRQh         EXTI3_IRQHandler
#define PS_LA_UNUSED_IRQh      EXTI4_IRQHandler

// ADC pins --------------------------------------------------------
#define PS_ADC_AWD1            LL_ADC_AWD_CHANNEL_6_REG
#define PS_ADC_AWD2            LL_ADC_AWD_CHANNEL_7_REG
#define PS_ADC_AWD3            LL_ADC_AWD_CHANNEL_12_REG
#define PS_ADC_AWD4            LL_ADC_AWD_CHANNEL_4_REG
#define PS_ADC_CH1             LL_ADC_CHANNEL_6
#define PS_ADC_CH2             LL_ADC_CHANNEL_7
#define PS_ADC_CH3             LL_ADC_CHANNEL_12
#define PS_ADC_CH4             LL_ADC_CHANNEL_4

// ADC - GPIO pins --------------------------------------------------
#define PS_GPIO_ADC_PORT1      GPIOC
#define PS_GPIO_ADC_PORT2      GPIOC
#define PS_GPIO_ADC_PORT3      GPIOB
#define PS_GPIO_ADC_PORT4      GPIOB
#define PS_GPIO_ADC_CH1        LL_GPIO_PIN_0
#define PS_GPIO_ADC_CH2        LL_GPIO_PIN_1
#define PS_GPIO_ADC_CH3        LL_GPIO_PIN_0
#define PS_GPIO_ADC_CH4        LL_GPIO_PIN_14

// LA - GPIO pins --------------------------------------------------
#define PS_GPIO_LA_PORT        GPIOC
#define PS_GPIO_LA_CH1         LL_GPIO_PIN_0
#define PS_GPIO_LA_CH2         LL_GPIO_PIN_1
#define PS_GPIO_LA_CH3         LL_GPIO_PIN_2
#define PS_GPIO_LA_CH4         LL_GPIO_PIN_3

#endif

/*-----------------------------------------------------------------------------------------------------------+
 +                                                  Common                                                   +
 +-----------------------------------------------------------------------------------------------------------*/

// generic constants -----------------------------------------------
#define PS_LN2POW14            9.70406    // ln(2^14)
#define PS_LN2POW10            6.93147    // ln(2^10)
#define PS_UWTICK_MAX          4294967295 // (2^32) - 1

// IRQ priorities --------------------------------------------------
#define PS_IT_PRI_TIM3         1   // main DAQ timing
#define PS_IT_PRI_ADC          5   // analog watchdog ADC
#define PS_IT_PRI_EXTI         5   // logic analyzer GPIO
#define PS_IT_PRI_UART         6   // UART RX
#define PS_IT_PRI_USB          7   // USB RX
#define PS_IT_PRI_SYST         15  // systick

// Async respond strings -------------------------------------------
#define PS_RESP_NRDY           "Not ready!"
#define PS_RESP_RDY_N          "\"ReadyN\"\r\n"  // normal trigger data ready (+ single)
#define PS_RESP_RDY_A          "\"ReadyA\"\r\n"  // auto trigger data ready
#define PS_RESP_RDY_D          "\"ReadyD\"\r\n"  // disabled trigger data ready

// IWDG ------------------------------------------------------------
#define PS_IWDG_RST_VAL        0xAAAA  // watchdog reset key value
#define PS_IWDG_RST            (IWDG->KR = PS_IWDG_RST_VAL) // watchdog reset

// DAQ -------------------------------------------------------------
#define PS_AUTRIG_MIN_MS       500   // auto trigger ms delay
#define PS_PRETRIG_MIN_MS      10    // pre trigger minimum ms

// Counter common --------------------------------------------------
#define PS_CNTR_BUFF_SZ        100   // countetr buffer size
#define PS_CNTR_MEAS_MS        2000  // counter max measure time ms

// Voltmeter common ------------------------------------------------
#define PS_VM_FS               100  // voltmeter fs (Hz)
#define PS_VM_MEM              200  // voltmeter mem

// LED timing ------------------------------------------------------
#define PS_BLINK_LONG_MS       500  // long blink - startup
#define PS_BLINK_SHORT_MS      50   // short blink - rx msg

// SCPI  -----------------------------------------------------------
#define SCPI_IDN1              PS_DEV_AUTHOR
#define SCPI_IDN2              PS_DEV_NAME
#define SCPI_IDN3              PS_DEV_VER
#define SCPI_IDN4              "0"

// calc helpers ----------------------------------------------------
#define PS_ADC_ADDR(x)           (uint32_t)LL_ADC_DMA_GetRegAddr(x, LL_ADC_DMA_REG_REGULAR_DATA) // ADC DMA address
#define PS_ADC_1CH_SMPL_TM(T,B)  ((1.0 / (float)PS_FREQ_ADCCLK) * ((float)T + (B))) // ADC 1 channel sampling time in seconds (T - smpl ticks, B - Tconv)
#define PS_ADC_MAXZ(T,L)         (((T) / ((float)PS_FREQ_ADCCLK * PS_ADC_C_F * (L))) - PS_ADC_R_KOHM) // ADC max input impedance (T - smpl ticks, L - ln2^(N+2))
#define PS_DMA_LAST_IDX(x,y,z)   (get_last_circ_idx((x - LL_DMA_GetDataLength(z, y)), x)) // last DMA index from circular buffer (x - buff len, y - dma ch, z - dma)
#define PS_MILIS(x)              (x / portTICK_PERIOD_MS) // FreeRTOS miliseconds
#define J(a,b)                   a##b // join two tokens

// ADC sampling times and their float values -----------------------
extern const uint32_t PS_ADC_SMPLT[PS_ADC_SMPLT_CNT];
extern const float PS_ADC_SMPLT_N[PS_ADC_SMPLT_CNT];

// Welcome string  -------------------------------------------------
#define WELCOME_STR "\n  Welcome to:\n\
 .-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-.\n\
 |  __                  __   __   __   __   ___  |\n\
 | |__) | |    |       /__` /  ` /  \\ |__) |__   |\n\
 | |    | |___ |___    .__/ \\__, \\__/ |    |___  |\n\
 |                                               |\n\
 `-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-'\n\n"

/*-----------------------------------------------------------------------------------------------------------+
 +                                                    USB                                                    +
 +-----------------------------------------------------------------------------------------------------------*/

// need to include cfg.h in USB_DEVICE/App/usbd_desc.c !!

#define USBD_VID                        0x0483
#define USBD_LANGID_STRING              0x5740
#define USBD_MANUFACTURER_STRING        PS_DEV_AUTHOR
#define USBD_PID_FS                     22336
#define USBD_PRODUCT_STRING_FS          PS_DEV_NAME
#define USBD_CONFIGURATION_STRING_FS    "CDC Config"
#define USBD_INTERFACE_STRING_FS        "CDC Interface"

/*-----------------------------------------------------------------------------------------------------------+
 +                                                   utils                                                   +
 +-----------------------------------------------------------------------------------------------------------*/

#define WTF                           assert(0)
#define NUMARGS8(...)                 (sizeof((uint8_t[]){__VA_ARGS__})/sizeof(uint8_t))
#define BITMAP_GET_BIT(m,b,s)         (*(m + (b / s)) &  (uint8_t)(1 << (b % s)))
#define BITMAP_SET_BIT(m,b,s)         (*(m + (b / s)) |= (uint8_t)(1 << (b % s)))
#define LO_BYTE16(x)                  ((uint8_t) ((x) & 0xFF))
#define HI_BYTE16(x)                  ((uint8_t) ((x) >> 8u ))
#define U8_TO_U16(h,l)                ((uint16_t)(h << 8u) | l)
#define U8_TO_U32(h,a,b,l)            ((uint32_t)(h << 24u) | (uint32_t)(a << 16u) | (uint32_t)(b << 8u) | l)

#define Pu8 "hu"
#define Pd8 "hd"
#define Px8 "hx"
#define Pu16 "hu"
#define Pd16 "hd"
#define Px16 "hx"
#define Pu32 "u"
#define Pd32 "d"
#define Px32 "x"
#define Pu64 "llu" // or possibly "lu"
#define Pd64 "lld" // or possibly "ld"
#define Px64 "llx" // or possibly "lx"


#endif /* CFG_H */
