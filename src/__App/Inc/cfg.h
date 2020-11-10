/*
 * CTU/UniLabTool project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef CFG_H
#define CFG_H

/*-----------------------------------------------------------------------------------------------------------+
 +                                                  general                                                  +
 +-----------------------------------------------------------------------------------------------------------*/

#define ULT_DEV_VER             "0.0.2"
#define ULT_DEV_AUTHOR          "CTU/Jakub Parez"


/*-----------------------------------------------------------------------------------------------------------+
 +                                               board specific                                              +
 +-----------------------------------------------------------------------------------------------------------*/

#ifdef STM32F103xB

#include "stm32f1xx.h"

// USART3 nefunguje preruseni
// ADC2 nema DMA
// ADC pouze 12 bit
// Vrefint_CAL neexistuje

#define ULT_FREQ_LSI            40000
#define ULT_FREQ_HCLK           72000000
#define ULT_FREQ_ADCCLK         12000000
#define ULT_FREQ_PCLK1          36000000  // TIM2,3,4
#define ULT_FREQ_PCLK2          72000000  // TIM1

#define ULT_DEV_NAME            "UniLabTool-F103C8"
#define ULT_UART                USART1
#define ULT_UART_RX_IRQHandler  USART1_IRQHandler
#define ULT_LED_PORT            GPIOC
#define ULT_LED_PIN             13
#define ULT_TIM_PWM             TIM2
#define ULT_TIM_PWM_FREQ        ULT_FREQ_PCLK1
#define ULT_PWM_BITS            16
#define ULT_ADC1
//#define ULT_ADC2
#define ULT_ADC_MSPS            1
#define ULT_ADC_BIT12
//#define ULT_ADC_BIT8
//#define ULT_ADC_VREF_CAL      *((uint16_t*)VREFINT_CAL_ADDR)
#define ULT_ADC_VREF_CAL        1200
#define ULT_ADC_VREF_CAL2       12000.0
#define ULT_TIM_ADC             TIM3
#define ULT_TIM_TRIG            TIM4
#define ULT_MAX_MEM             5000
#define ULT_MAX_SPEED           ?

#define VREFINT_CAL_ADDR        0x1FFFF7BA

#define BLINK_LONG              300000
#define BLINK_SHORT             30000

#endif /* STM32F103xB */

/*-----------------------------------------------------------------------------------------------------------+
 +                                                    USB                                                    +
 +-----------------------------------------------------------------------------------------------------------*/

// need to include cfg.h in USB_DEVICE/App/usbd_desc.c !!

#define USBD_VID                        0x0483
#define USBD_LANGID_STRING              0x5740
#define USBD_MANUFACTURER_STRING        ULT_DEV_AUTHOR
#define USBD_PID_FS                     22336
#define USBD_PRODUCT_STRING_FS          ULT_DEV_NAME
#define USBD_CONFIGURATION_STRING_FS    "CDC Config"
#define USBD_INTERFACE_STRING_FS        "CDC Interface"

/*-----------------------------------------------------------------------------------------------------------+
 +                                                  SCPI ID                                                  +
 +-----------------------------------------------------------------------------------------------------------*/

#define SCPI_IDN1       ULT_DEV_AUTHOR
#define SCPI_IDN2       ULT_DEV_NAME
#define SCPI_IDN3       ULT_DEV_VER
#define SCPI_IDN4       "0"

/*-----------------------------------------------------------------------------------------------------------+
 +                                                   utils                                                   +
 +-----------------------------------------------------------------------------------------------------------*/

#define NUMARGS8(...)                  (sizeof((uint8_t[]){__VA_ARGS__})/sizeof(uint8_t))
#define BITMAP_GET_BIT(m,b,s)         (*(m + (b / s)) &  (uint8_t)(1 << (b % s)))
#define BITMAP_SET_BIT(m,b,s)         (*(m + (b / s)) |= (uint8_t)(1 << (b % s)))
#define LO_BYTE16(x)                  ((uint8_t) ((x) & 0xFF))
#define HI_BYTE16(x)                  ((uint8_t) ((x) >> 8u ))
#define IS_EQUAL_3_AND(x,a,b,c)       ((a == x) && (b == x) && (c == x))
#define IS_EQUAL_4_AND(x,a,b,c,d)     ((a == x) && (b == x) && (c == x) && (d == x))
#define NOT_EQUAL_3_AND(x,a,b,c)      ((a != x) && (b != x) && (c != x))
#define NOT_EQUAL_4_AND(x,a,b,c,d)    ((a != x) && (b != x) && (c != x) && (d != x))
#define __CONVERT_U8_TO_U16(h,l)      ((uint16_t)(h << 8u) | l)
#define __CONVERT_U8_TO_U32(h,a,b,l)  ((uint32_t)(h << 24u) | (uint32_t)(a << 16u) | (uint32_t)(b << 8u) | l)

#ifdef IQRF_LITTLE_ENDIAN
#define CONVERT_U8_TO_U16(h,l)        __CONVERT_U8_TO_U16(h,l)
#define CONVERT_U8_TO_U32(h,a,b,l)    __CONVERT_U8_TO_U32(h,a,b,l)
#else
#define CONVERT_U8_TO_U16(h,l)        __CONVERT_U8_TO_U16(l,h)
#define CONVERT_U8_TO_U32(h,a,b,l)    __CONVERT_U8_TO_U32(l,b,a,h)
#endif

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
