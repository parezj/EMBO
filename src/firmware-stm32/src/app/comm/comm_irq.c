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


/* UART IRQ handler */
void EM_UART_RX_IRQHandler(void)
{
    traceISR_ENTER();
    int8_t exit = 0;

    if (LL_USART_IsActiveFlag_RXNE(EM_UART) == 1)
    {
        char rx = LL_USART_ReceiveData8(EM_UART);

        if (em_comm.uart.available == EM_FALSE && em_comm.usb.available == EM_FALSE)
        {
            em_comm.uart.rx_buffer[em_comm.uart.rx_index++] = rx;

            if (em_comm.uart.rx_index >= RX_BUFF_LAST)
                em_comm.uart.rx_index = 0;

            em_comm.uart.last = EM_TRUE;
            em_comm.usb.last = EM_FALSE;

            #ifdef EM_UART_CLEAR_FLAG
                EM_UART_CLEAR_FLAG(EM_UART);
            #endif

            /* new message detected */
            if (rx == '\n' && em_comm.uart.rx_index > 1 && em_comm.uart.rx_buffer[em_comm.uart.rx_index - 2] == '\r')
            {
                em_comm.uart.available = EM_TRUE;
                exit = -1;

                portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
                ASSERT(xSemaphoreGiveFromISR(sem1_comm, &xHigherPriorityTaskWoken) == pdPASS);
                portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
            }
        }
        //else
        //    ASSERT(0);
    }

    if (exit == 0)
        traceISR_EXIT();
}

/*
static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
{
  */
  /* USER CODE BEGIN 6 */
  /*
  traceISR_ENTER();
  int8_t ret = 0;
  int8_t exit = 0;

  uint32_t len = *Len;
  if (hUsbDeviceFS.dev_state != USBD_STATE_CONFIGURED)
  {
     ret = USBD_FAIL;
     goto quit;
  }

  if (((Buf == NULL) || (Len == NULL)) || (*Len <= 0))
  {
     ret = USBD_FAIL;
     goto quit;
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

  if (comm.uart.available == EM_FALSE && comm.usb.available == EM_FALSE)
  {
      while (len--)
      {
         comm.usb.rx_buffer[comm.usb.rx_index++] = *Buf;

         if (comm.usb.rx_index >= RX_BUFF_LAST)
             comm.usb.rx_index = 0;

         comm.uart.last = EM_FALSE;
         comm.usb.last = EM_TRUE;

         if (*Buf == '\n' && comm.usb.rx_index > 1 && comm.usb.rx_buffer[comm.usb.rx_index - 2] == '\r')
         {
             comm.usb.available = EM_TRUE;
             exit = -1;

             portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
             ASSERT(xSemaphoreGiveFromISR(sem1_comm, &xHigherPriorityTaskWoken) == pdPASS);
             portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
         }
         Buf++;
      }
  }

  ret = USBD_OK;
  if (exit == 0)
      traceISR_EXIT();

  quit:
  return ret;
  */
  /* USER CODE END 6 */
  /*
}

uint8_t CDC_Busy()
{
    USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
    return hcdc->TxState != 0 ? 1 : 0;
}
*/
