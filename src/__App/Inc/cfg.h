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

#define PS_DEV_VER             "0.1.0"
#define PS_DEV_AUTHOR          "CTU/Jakub Parez"

/*-----------------------------------------------------------------------------------------------------------+
 +                                               board specific                                              +
 +-----------------------------------------------------------------------------------------------------------*/

/*................................................... F103 ..................................................*/

#if defined(STM32F103xB)

#include "stm32f1xx.h"


/*
 * - USART3 nefunguje preruseni
 * - ADC2 nema DMA
 * - ADC pouze 12 bit
 * - Vrefint_CAL neexistuje
 * - min 41.5 ADC cyklu, jinak vrefint je spatna
 * =========layout ============
 *  ADC CH1 ...... PA1
 *  ADC CH2 ...... PA2
 *  ADC CH3 ...... PA3
 *  ADC CH4 ...... PA4
 *  PWM CH1 ...... PA15
 *  PWM CH2 ...... PB6
 *  CNTR ......... PA8
 *  ===========================
*/

#define PS_FREQ_LSI            40000
#define PS_FREQ_HCLK           72000000
#define PS_FREQ_ADCCLK         12000000
#define PS_FREQ_PCLK1          36000000  // TIM2,3,4
#define PS_FREQ_PCLK2          72000000  // TIM1

#define PS_DEV_NAME            "PillScope-F103C8"
#define PS_UART                USART1
#define PS_UART_RX_IRQHandler  USART1_IRQHandler
#define PS_LED_PORT            GPIOC
#define PS_LED_PIN             13   // main led pin

#define PS_CNTR_BUFF_SZ        100  // countetr buffer size
//#define PS_DAC               DAC1

#define PS_ADC_MODE_ADC1
//#define PS_ADC_MODE_ADC12
//#define PS_ADC_MODE_ADC1234
#define PS_ADC_MSPS            1
#define PS_ADC_BIT12
//#define PS_ADC_BIT8
//#define PS_ADC_VREF_CAL      *((uint16_t*)VREFINT_CAL_ADDR)
#define PS_ADC_SMPL_TIME       LL_ADC_SAMPLINGTIME_41CYCLES_5 // LL_ADC_SAMPLINGTIME_71CYCLES_5
#define PS_ADC_SMPL_TIME_N     41.5 //71.5
#define PS_ADC_TCONV           12.5
#define PS_ADC_TRIG_TIM        LL_ADC_REG_TRIG_EXT_TIM3_TRGO
#define PS_ADC_VREF_CAL        1200
#define PS_ADC_VREF_CAL_B12    12000.0
#define PS_ADC_VREF_CAL_B8     120.0

#define PS_TIM_ADC             TIM3
#define PS_TIM_ADC_MAX         65535
#define PS_TIM_ADC_FREQ        PS_FREQ_PCLK1
#define PS_TIM_ADC_IRQh        TIM3_IRQHandler
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
#define PS_TIM_CNTR_IRQh       TIM1_UP_IRQHandler
#define PS_TIM_CNTR_MAX        65535
#define PS_TIM_CNTR_CH         LL_TIM_CHANNEL_CH1
#define PS_TIM_CNTR_CCR        CNT // ?? CCR1

#define PS_SYSTICK_FREQ        1000
#define PS_DAQ_MAX_MEM         12000
#define PS_MEM_RESERVE         2
#define PS_LA_MAX_FS           1000000 // TODO ??

#define PS_DMA_ADC             DMA1
#define PS_DMA_LA              DMA1
#define PS_DMA_CNTR            DMA1

#define PS_DMA_CH_ADC1         LL_DMA_CHANNEL_1
//#define PS_DMA_CH_ADC2         LL_DMA_CHANNEL_3
//#define PS_DMA_CH_ADC3         LL_DMA_CHANNEL_4
//#define PS_DMA_CH_ADC4         LL_DMA_CHANNEL_5
#define PS_DMA_CH_LA           LL_DMA_CHANNEL_6
#define PS_DMA_CH_CNTR         LL_DMA_CHANNEL_2

#define VREFINT_CAL_ADDR       0x1FFFF7BA

#define PS_BLINK_LONG          300000
#define PS_BLINK_SHORT         30000

#elif defined(STM32F303)

#endif /* STM32F103xB */

/*-----------------------------------------------------------------------------------------------------------+
 +                                                  common                                                   +
 +-----------------------------------------------------------------------------------------------------------*/

#define PS_RESP_NRDY           "Not ready!"
#define PS_RESP_RDY            "\"Ready\"\r\n"

#define PS_IWDG_RST_VAL        0xAAAA
#define PS_IWDG_RST            (IWDG->KR = PS_IWDG_RST_VAL)     // watchdog reset

#define PS_AUTRIG_MIN_MS       500   // auto trigger milisecond delay
#define PS_MIN_OP_VCC          2500  // minimum operating vcc

#define PS_ADC_1CH_SMPL_TM     ((1.0 / (float)PS_FREQ_ADCCLK) * (float)(PS_ADC_SMPL_TIME_N + PS_ADC_TCONV))

#define PS_ADC_AWD1            LL_ADC_AWD_CHANNEL_1_REG
#define PS_ADC_AWD2            LL_ADC_AWD_CHANNEL_2_REG
#define PS_ADC_AWD3            LL_ADC_AWD_CHANNEL_3_REG
#define PS_ADC_AWD4            LL_ADC_AWD_CHANNEL_4_REG
#define PS_ADC_CH1             LL_ADC_CHANNEL_1
#define PS_ADC_CH2             LL_ADC_CHANNEL_2
#define PS_ADC_CH3             LL_ADC_CHANNEL_3
#define PS_ADC_CH4             LL_ADC_CHANNEL_4

#define PS_DAQ_PORT            GPIOA
#define PS_DAQ_CH1             LL_GPIO_PIN_1
#define PS_DAQ_CH2             LL_GPIO_PIN_2
#define PS_DAQ_CH3             LL_GPIO_PIN_3
#define PS_DAQ_CH4             LL_GPIO_PIN_4

#define PS_LA_EXTI_PORT        LL_GPIO_AF_EXTI_PORTA
#define PS_LA_IRQ_EXTI1        EXTI1_IRQn
#define PS_LA_IRQ_EXTI2        EXTI2_IRQn
#define PS_LA_IRQ_EXTI3        EXTI3_IRQn
#define PS_LA_IRQ_EXTI4        EXTI4_IRQn
#define PS_LA_EXTI1            LL_EXTI_LINE_1
#define PS_LA_EXTI2            LL_EXTI_LINE_2
#define PS_LA_EXTI3            LL_EXTI_LINE_3
#define PS_LA_EXTI4            LL_EXTI_LINE_4
#define PS_LA_EXTILINE1        LL_GPIO_AF_EXTI_LINE1
#define PS_LA_EXTILINE2        LL_GPIO_AF_EXTI_LINE2
#define PS_LA_EXTILINE3        LL_GPIO_AF_EXTI_LINE3
#define PS_LA_EXTILINE4        LL_GPIO_AF_EXTI_LINE4
#define PS_LA_CH1_IRQh         EXTI1_IRQHandler
#define PS_LA_CH2_IRQh         EXTI2_IRQHandler
#define PS_LA_CH3_IRQh         EXTI3_IRQHandler
#define PS_LA_CH4_IRQh         EXTI4_IRQHandler


#define PS_ADC_ADDR(x)         (uint32_t)LL_ADC_DMA_GetRegAddr(x, LL_ADC_DMA_REG_REGULAR_DATA)
#define PS_DMA_LAST_IDX(x,y)   (get_last_circ_idx((x - LL_DMA_GetDataLength(DMA1, y)), x))


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
 +                                                  SCPI ID                                                  +
 +-----------------------------------------------------------------------------------------------------------*/

#define SCPI_IDN1       PS_DEV_AUTHOR
#define SCPI_IDN2       PS_DEV_NAME
#define SCPI_IDN3       PS_DEV_VER
#define SCPI_IDN4       "0"

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
