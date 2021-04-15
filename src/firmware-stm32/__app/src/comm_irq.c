/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */
 
#include "cfg.h"
#include "comm.h"

#include "app_data.h"
#include "app_sync.h"
#include "main.h"

#include "FreeRTOS.h"
#include "semphr.h"


void EM_UART_RX_IRQHandler(void)
{
    if (LL_USART_IsActiveFlag_RXNE(EM_UART) == 1)
    {
        char rx = LL_USART_ReceiveData8(EM_UART);

        comm.uart.rx_buffer[comm.uart.rx_index++] = rx;

        if (comm.uart.rx_index >= RX_BUFF_LAST)
            comm.uart.rx_index = 0;

        comm.uart.last = 1;
        comm.usb.last = 0;

        EM_UART_CLEAR_FLAG(EM_UART);

        if (rx == '\n' && comm.uart.rx_index > 1 && comm.uart.rx_buffer[comm.uart.rx_index - 2] == '\r')
        {
            comm.uart.available = 1;

            portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
            ASSERT(xSemaphoreGiveFromISR(sem1_comm, &xHigherPriorityTaskWoken) == pdPASS);
            if (xHigherPriorityTaskWoken != pdFALSE)
                portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
        }
    }
}

/*
int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)       // OVERIDE THIS in: /USB_DEVICE/App/usbd_cdc_if.c !!!
{
  */
  /* USER CODE BEGIN 6 */
  /*
  uint32_t len = *Len;
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

     comm.uart.last = 0;
     comm.usb.last = 1;

     if (*Buf == '\n' && comm.usb.rx_index > 1 && comm.usb.rx_buffer[comm.usb.rx_index - 2] == '\r')
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
  */
  /* USER CODE END 6 */
  /*
}
*/
