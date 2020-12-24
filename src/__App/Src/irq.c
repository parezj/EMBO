/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"
#include "irq.h"
#include "periph.h"
#include "main.h"
#include "app_data.h"
#include "app_sync.h"
#include "comm.h"

#include "FreeRTOS.h"
#include "semphr.h"

/*
int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)       // OVERIDE THIS in: /USB_DEVICE/App/usbd_cdc_if.c !!!
{
    uint32_t len=*Len;
    if (hUsbDeviceFS.dev_state != USBD_STATE_CONFIGURED)
    {
        return USBD_FAIL;
    }

    if (((Buf == NULL) || (Len == NULL)) || (*Len <= 0))
    {
        return USBD_FAIL;
    }

    uint8_t result = USBD_OK;
    do
    {
        result = USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
    }
    while(result != USBD_OK);

    do
    {
        result = USBD_CDC_ReceivePacket(&hUsbDeviceFS);
    }
    while(result != USBD_OK);

    while (len--)
    {
        comm.usb.rx_buffer[comm.usb.rx_index++] = *Buf;

        if (comm.usb.rx_index >= RX_BUFF_LAST)
            comm.usb.rx_index = 0;

        comm.usb.last = 0;
        comm.usb.last = 1;

        if (*Buf == '\n'))
        {
            portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
            if(xSemaphoreGiveFromISR(sem1_comm, &xHigherPriorityTaskWoken) != pdPASS)
            {
                comm.usb.rx_index = 0;
            }
            else
            {
                comm.usb.available = 1;
                if (xHigherPriorityTaskWoken != pdFALSE)
                    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
            }
        }

        Buf++;
    }

    return USBD_OK;
}
*/

void SysTick_Handler(void)
{
    if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
        xPortSysTickHandler();

    HAL_IncTick();
}

void SVC_Handler(void)
{
    vPortSVCHandler();
}

void PendSV_Handler(void)
{
    xPortPendSVHandler();
}

void USART1_IRQHandler(void)
{
    if (LL_USART_IsActiveFlag_RXNE(PS_UART) == 1)
    {
        char rx = LL_USART_ReceiveData8(PS_UART);

        comm.uart.rx_buffer[comm.uart.rx_index++] = rx;

        if (comm.uart.rx_index >= RX_BUFF_LAST)
            comm.uart.rx_index = 0;

        comm.uart.last = 1;
        comm.usb.last = 0;

        if (rx == '\n')
        {
            portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
            if(xSemaphoreGiveFromISR(sem1_comm, &xHigherPriorityTaskWoken) != pdPASS)
            {
                comm.uart.rx_index = 0;
            }
            else
            {
                comm.uart.available = 1;
                if (xHigherPriorityTaskWoken != pdFALSE)
                    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
            }
        }
#ifdef PS_UART_RXNE
        LL_USART_ClearFlag_RXNE(PS_UART);
#endif
    }
}

void ADC1_2_IRQHandler(void)
{
#if defined(PS_ADC_MODE_ADC1)
    if (LL_ADC_IsActiveFlag_AWD1(ADC1) == 1)
    {
        daq_trig_trigger_scope(&daq);
        LL_ADC_ClearFlag_AWD1(ADC1);
    }
#endif

#if defined(PS_ADC_MODE_ADC12)
    if (LL_ADC_IsActiveFlag_AWD1(ADC2) == 1)
    {
        daq_trig_trigger_scope(&daq);
        LL_ADC_ClearFlag_AWD1(ADC2);
    }
#endif
}

void ADC3_4_IRQHandler(void)
{
#if defined(PS_ADC_MODE_ADC1234)
    if (LL_ADC_IsActiveFlag_AWD1(ADC3) == 1)
    {
        daq_trig_trigger_scope(&daq);
        LL_ADC_ClearFlag_AWD1(ADC3);
    }

    if (LL_ADC_IsActiveFlag_AWD1(ADC4) == 1)
    {
        daq_trig_trigger_scope(&daq);
        LL_ADC_ClearFlag_AWD1(ADC4);
    }
#endif
}

void PS_TIM_CNTR_UP_IRQh(void)
{
    if(LL_TIM_IsActiveFlag_UPDATE(PS_TIM_CNTR) == 1)
    {
        LL_TIM_ClearFlag_UPDATE(PS_TIM_CNTR);
        cntr.ovf++;
    }
}

void PS_TIM_CNTR_CCR_IRQh(void)
{
    if (cntr.data_ovf_it < PS_CNTR_BUFF_SZ)
        cntr.data_ovf[cntr.data_ovf_it++] = cntr.ovf; // BUG

    if(LL_TIM_IsActiveFlag_CC1(PS_TIM_CNTR) == 1)
    {
        LL_TIM_ClearFlag_CC1(PS_TIM_CNTR);
    }
}


void PS_LA_CH1_IRQh(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(PS_LA_EXTI1) == 1)
    {
        daq_trig_trigger_la(&daq);
        LL_EXTI_ClearFlag_0_31(PS_LA_EXTI1);
    }
}

void PS_LA_CH2_IRQh(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(PS_LA_EXTI2) == 1)
    {
        daq_trig_trigger_la(&daq);
        LL_EXTI_ClearFlag_0_31(PS_LA_EXTI2);
    }
}

void PS_LA_CH3_IRQh(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(PS_LA_EXTI3) == 1)
    {
        daq_trig_trigger_la(&daq);
        LL_EXTI_ClearFlag_0_31(PS_LA_EXTI3);
    }
}

void PS_LA_CH4_IRQh(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(PS_LA_EXTI4) == 1)
    {
        daq_trig_trigger_la(&daq);
        LL_EXTI_ClearFlag_0_31(PS_LA_EXTI4);
    }
}

void EXTI0_IRQHandler(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0) == 1)
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
    }
}
