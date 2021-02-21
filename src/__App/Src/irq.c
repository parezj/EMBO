/*
 * CTU/EMBO - Embedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"

#include "FreeRTOS.h"
#include "semphr.h"

#include "periph.h"
#include "main.h"
#include "app_data.h"
#include "app_sync.h"
#include "comm.h"


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
#ifdef EM_HAL_SYSTICK
    HAL_IncTick();
#endif
    daq.uwTick++;
}

void SVC_Handler(void)
{
    vPortSVCHandler();
}

void PendSV_Handler(void)
{
    xPortPendSVHandler();
}

