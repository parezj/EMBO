/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef CFG_H
#define CFG_H

#include <util.h>

/*-----------------------------------------------------------------------------------------------------------+
 +                                                  general                                                  +
 +-----------------------------------------------------------------------------------------------------------*/

#define EM_DEBUG      // auto enable PWM, SGEN on start and more verbose
//#define EM_SYSVIEW  // SEGGER System View enabled - less DAQ memory

#define EM_DEV_VER      "0.2.4"
#define EM_DEV_AUTHOR   "CTU/Jakub Parez"


/*-----------------------------------------------------------------------------------------------------------+
 +                                               board specific                                              +
 +-----------------------------------------------------------------------------------------------------------*/

/*.................................................. F103C8 .................................................*/

#if defined(STM32F103xB)

    #define EM_F103C8
    #define EM_CORTEX_M3

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

    #include "cfg_f103c8.h"

#elif defined(STM32F103xE)
/*.................................................. F103RE .................................................*/

    #define EM_F103RE
    #define EM_CORTEX_M3

    /*
     * =========layout=========
     *  DAQ CH1 ........... PA0
     *  DAQ CH2 ........... PA1
     *  DAQ CH3 ........... PA2
     *  DAQ CH4 ........... PA3
     *  PWM CH1 ........... PA15
     *  PWM CH2 ........... PB6
     *  CNTR .............. PA8
     *  DAC CH1 ........... PA4
     *  DAC CH2 ........... PA5
     *  UART RX ........... PA10
     *  UART TX ........... PA9
     *  USB D- ............ PA11
     *  USB D+ ............ PA12
     *  SWDIO ............. PA13
     *  SWDCLK ............ PA14
     *  =======================
     */

    #include "cfg_f103re.h"

#elif defined(STM32F303xE)
/*.................................................. F303RE .................................................*/

    #define EM_F303RE
    #define EM_CORTEX_M4F

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
     *  DAC CH1 ........... PA4  (Arduino A2)
     *  DAC CH2 ........... PA5
     *  UART RX ........... PA3
     *  UART TX ........... PA2
     *  USB D- ............ PA11
     *  USB D+ ............ PA12
     *  =======================
     */

    #include "cfg_f303re.h"

#elif defined(STM32L412xx)
/*.................................................. L412KB .................................................*/

    #define EM_L412KB
    #define EM_CORTEX_M4F

    /*
     * =========layout=========
     *  DAQ CH1 ........... PA0  (Arduino A0)
     *  DAQ CH2 ........... PA1  (Arduino A1)
     *  DAQ CH3 ........... PA3  (Arduino A2)
     *  DAQ CH4 ........... PA4  (Arduino A3)
     *  PWM CH1 ........... PA5  (Arduino A4)
     *  CNTR .............. PA8  (Arduino D9)
     *  UART RX ........... PA15
     *  UART TX ........... PA2
     *  USB D- ............ PA11
     *  USB D+ ............ PA12
     *  SWDIO ............. PA13
     *  SWDCLK ............ PA14
     *  =======================
     */

    #include "cfg_l412kb.h"

#elif defined(STM32G031xx)

    #if defined(K8)
/*.................................................. G031K8 .................................................*/

        #define EM_G031K8
        #define EM_CORTEX_M0

        /*
         * =========layout=========
         *  DAQ CH1 ........... PA0  (Arduino A0)
         *  DAQ CH2 ........... PA1  (Arduino A1)
         *  DAQ CH3 ........... PA4  (Arduino A2)
         *  DAQ CH4 ........... PA5  (Arduino A3)
         *  PWM CH1 ........... PA15 (Arduino D2)
         *  CNTR .............. PA8  (Arduino D9)
         *  UART RX ........... PA3
         *  UART TX ........... PA2
         *  =======================
         */

        #include "cfg_g031k8.h"

    #elif defined(J6)
/*.................................................. G031J6 .................................................*/

        #define EM_G031J6
        #define EM_CORTEX_M0

        /*
         * =========layout=========
         *  DAQ CH1 ........... PA13
         *  DAQ CH2 ........... PA10
         *  PWM CH1 ........... PA0
         *  CNTR .............. PA8
         *  UART RX ........... PB7
         *  UART TX ........... PB6
         *  =======================
         */

        #include "cfg_g031j6.h"

    #endif

#elif defined(STM32G431xx)
/*.................................................. L412KB .................................................*/

    #define EM_G431KB
    #define EM_CORTEX_M4F

    /*
     * =========layout=========
     *  DAQ CH1 ........... PA0
     *  DAQ CH2 ........... PA1
     *  DAQ CH3 ........... PA6
     *  DAQ CH4 ........... PA7
     *  PWM CH1 ........... PA15
     *  PWM CH2 ........... PB6
     *  CNTR .............. PA8
     *  DAC CH1 ........... PA4
     *  DAC CH2 ........... PA5
     *  UART RX ........... PA2
     *  UART TX ........... PA3
     *  USB D- ............ PA11
     *  USB D+ ............ PA12
     *  SWDIO ............. PA13
     *  SWDCLK ............ PA14
     *  =======================
     */

    #include "cfg_g431kb.h"

#endif

#if !defined(EM_DAQ_4CH) && (defined(EM_ADC_MODE_ADC12) || defined(EM_ADC_MODE_ADC1234))
    #error ADC12 or ADC1234 must be implemented with 4 channels only!
#endif

/*-----------------------------------------------------------------------------------------------------------+
 +                                                  Common                                                   +
 +-----------------------------------------------------------------------------------------------------------*/

#define EMBO

// generic constants -----------------------------------------------
#define EM_TRUE                1
#define EM_FALSE               0
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

// DAQ common ------------------------------------------------------
#define EM_AUTRIG_MIN_MS       500   // auto trigger ms delay
#define EM_PRETRIG_MIN_MS      10    // pre trigger minimum ms

// Counter common --------------------------------------------------
#define EM_CNTR_BUFF_SZ        200   // buffer size for high frequencies - fast mode
#define EM_CNTR_BUFF_SZ2       30    // buffer size for slow frequencies - precise mode
#define EM_CNTR_MEAS_MS        2000  // counter max measure time ms
#define EM_CNTR_INT_DELAY      10    // counter internal read delay

// Voltmeter common ------------------------------------------------
#define EM_VM_FS               100  // voltmeter fs (Hz)
#define EM_VM_MEM              100  // voltmeter mem

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


#endif /* CFG_H */
