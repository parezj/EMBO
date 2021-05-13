/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef CFG_H
#define CFG_H

#include "utility.h"

/*-----------------------------------------------------------------------------------------------------------+
 +                                                  general                                                  +
 +-----------------------------------------------------------------------------------------------------------*/

#define EM_DEBUG      // auto enable PWM, SGEN on start and more verbose
//#define EM_SYSVIEW  // SEGGER System View enabled - less DAQ memory

#define EM_DEV_VER      "0.1.9"
#define EM_DEV_AUTHOR   "CTU/Jakub Parez"


/*-----------------------------------------------------------------------------------------------------------+
 +                                               board specific                                              +
 +-----------------------------------------------------------------------------------------------------------*/

/*.................................................. F103C8 .................................................*/

#if defined(STM32F103xB)

#define EM_F103C8

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

#include "cfg_f103c8.h"

#elif defined(STM32F103xE)
/*.................................................. F103RE .................................................*/

#define EM_F103RE

/*
 * =========layout=========
 *  DAQ CH1 ........... PA0
 *  DAQ CH2 ........... PA1
 *  DAQ CH3 ........... PA2
 *  DAQ CH4 ........... PA3
 *  PWM CH1 ........... PA15
 *  PWM CH2 ........... PB6
 *  CNTR .............. PA8
 *  DAC ............... PA4
 *  =======================
*/

#include "cfg_f103re.h"

#elif defined(STM32F303xE)
/*.................................................. F303RE .................................................*/

#define EM_F303RE

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

#include "cfg_f303re.h"

#elif defined(STM32G031xx)
/*.................................................. G031K8 .................................................*/

#if defined(K8)
#define EM_G031K8

/*
 * =========layout=========
 *  DAQ CH1 ........... PA0  (Arduino A0)
 *  DAQ CH2 ........... PA1  (Arduino A1)
 *  DAQ CH3 ........... PA4  (Arduino A2)
 *  DAQ CH4 ........... PA5  (Arduino A3)
 *  PWM CH1 ........... PA15 (Arduino D2)
 *  CNTR .............. PA8  (Arduino D9)
 *  =======================
*/

#include "cfg_g031k8.h"

#elif defined(J6)
/*.................................................. G031J6 .................................................*/

#define EM_G031J6

/*
 * =========layout=========
 *  DAQ CH1 ........... PA0  (Arduino A0)
 *  DAQ CH2 ........... PA1  (Arduino A1)
 *  DAQ CH3 ........... PA4  (Arduino A2)
 *  DAQ CH4 ........... PA5  (Arduino A3)
 *  PWM CH1 ........... PA15 (Arduino D2)
 *  CNTR .............. PA8  (Arduino D9)
 *  =======================
*/

#include "cfg_g031j6.h"

#endif

#endif

/*-----------------------------------------------------------------------------------------------------------+
 +                                                  Common                                                   +
 +-----------------------------------------------------------------------------------------------------------*/

// generic constants -----------------------------------------------
#define EM_LN2POW14            9.70406    // ln(2^14)
#define EM_LN2POW10            6.93147    // ln(2^10)
#define EM_UWTICK_MAX          4294967295 // (2^32) - 1

// Async respond strings -------------------------------------------
#define EM_RESP_NRDY           "Not ready!"
#define EM_RESP_RDY_N          "\"ReadyN\""  // normal trigger data ready
#define EM_RESP_RDY_S          "\"ReadyS\""  // normal trigger data ready (single)
#define EM_RESP_RDY_A          "\"ReadyA\""  // auto trigger data ready
#define EM_RESP_RDY_D          "\"ReadyD\""  // disabled trigger data ready
#define EM_RESP_RDY_F          "\"ReadyF\""  // forced trigger

// IWDG ------------------------------------------------------------
#define EM_IWDG_RST_VAL        0xAAAA  // watchdog reset key value
#define EM_IWDG_RST            (IWDG->KR = EM_IWDG_RST_VAL) // watchdog reset

// DAQ -------------------------------------------------------------
#define EM_AUTRIG_MIN_MS       500   // auto trigger ms delay
#define EM_PRETRIG_MIN_MS      10    // pre trigger minimum ms

// Counter common --------------------------------------------------
#define EM_CNTR_BUFF_SZ        200   // buffer size for high frequencies - fast mode
#define EM_CNTR_BUFF_SZ2       30    // buffer size for slow frequencies - precise mode
#define EM_CNTR_MEAS_MS        2000  // counter max measure time ms
#define EM_CNTR_INT_DELAY      10    // counter internal read delay

// Voltmeter common ------------------------------------------------
#define EM_VM_FS               100  // voltmeter fs (Hz)
#define EM_VM_MEM              300  // voltmeter mem

// LED timing ------------------------------------------------------
#define EM_BLINK_LONG_MS       500  // long blink - startup
#define EM_BLINK_SHORT_MS      50   // short blink - rx msg

// SCPI  -----------------------------------------------------------
#define SCPI_IDN1              EM_DEV_AUTHOR
#define SCPI_IDN2              EM_DEV_NAME
#define SCPI_IDN3              EM_DEV_VER
#define SCPI_IDN4              "0"

// calc helpers ----------------------------------------------------
#define EM_ADC_ADDR(x)           (uint32_t)LL_ADC_DMA_GetRegAddr(x, LL_ADC_DMA_REG_REGULAR_DATA) // ADC DMA address
#define EM_ADC_1CH_SMPL_TM(T,B)  ((1.0 / (double)EM_FREQ_ADCCLK) * ((double)T + (B))) // ADC 1 channel sampling time in seconds (T - smpl ticks, B - Tconv)
#define EM_ADC_MAXZ(k,L)         (((k - 0.5) / ((double)EM_FREQ_ADCCLK * EM_ADC_C_F * (L))) - EM_ADC_R_OHM) // ADC max input impedance (k - smpl ticks, L - ln2^(N+2))
#define EM_DMA_LAST_IDX(x,y,z)   (get_last_circ_idx((x - LL_DMA_GetDataLength(z, y)), x)) // last DMA index from circular buffer (x - buff len, y - dma ch, z - dma)
#define EM_MILIS(x)              (x / portTICK_PERIOD_MS) // FreeRTOS miliseconds

// ADC sampling times and their float values -----------------------
extern const uint32_t EM_ADC_SMPLT[EM_ADC_SMPLT_CNT];
extern const float EM_ADC_SMPLT_N[EM_ADC_SMPLT_CNT];

// Welcome string  -------------------------------------------------
#define WELCOME_STR "\n  Welcome to:\n\
 .-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-.\n\
 |  _       _   _  _   _   _  _     __  _  _   _   _ |\n\
 | |_ |\\/| |_) |_ | \\ | \\ |_ | \\   (_  /  / \\ |_) |_ |\n\
 | |_ |  | |_) |_ |_/ |_/ |_ |_/   __) \\_ \\_/ |   |_ |\n\
 |                                                   |\n\
 `-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-'\n\n"

/*-----------------------------------------------------------------------------------------------------------+
 +                                                    USB                                                    +
 +-----------------------------------------------------------------------------------------------------------*/

// need to include cfg.h in USB_DEVICE/App/usbd_desc.c !!

#define USBD_VID                        0x0483
#define USBD_LANGID_STRING              0x5740
#define USBD_MANUFACTURER_STRING        EM_DEV_AUTHOR
#define USBD_PID_FS                     22336
#define USBD_PRODUCT_STRING_FS          EM_DEV_NAME
#define USBD_CONFIGURATION_STRING_FS    "CDC Config"
#define USBD_INTERFACE_STRING_FS        "CDC Interface"

/*-----------------------------------------------------------------------------------------------------------+
 +                                                   utils                                                   +
 +-----------------------------------------------------------------------------------------------------------*/

#define EM_TRUE                       1
#define EM_FALSE                      0
#define PI                            3.14159265359
#define J(a,b)                        a##b
#define WTF                           assert(0)
#define NUMARGS8(...)                 (sizeof((uint8_t[]){__VA_ARGS__})/sizeof(uint8_t))
#define BITMAP_GET_BIT(m,b,s)         (*(m + (b / s)) &  (uint8_t)(1 << (b % s)))
#define BITMAP_SET_BIT(m,b,s)         (*(m + (b / s)) |= (uint8_t)(1 << (b % s)))
#define U8_TO_U16(h,l)                ((uint16_t)(h << 8u) | l)
#define U8_TO_U32(h,a,b,l)            ((uint32_t)(h << 24u) | (uint32_t)(a << 16u) | (uint32_t)(b << 8u) | l)
#define U16_TO_U8_L(x)                ((uint8_t)(((x) & 0x00FF)))
#define U16_TO_U8_H(x)                ((uint8_t)(((x) & 0xFF00) >> 8))
#define U32_TO_U8_L(x)                ((uint8_t)(((x) & 0x000000FF)))
#define U32_TO_U8_B(x)                ((uint8_t)(((x) & 0x0000FF00) >> 8))
#define U32_TO_U8_A(x)                ((uint8_t)(((x) & 0x00FF0000) >> 16))
#define U32_TO_U8_H(x)                ((uint8_t)(((x) & 0xFF000000) >> 24))

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
