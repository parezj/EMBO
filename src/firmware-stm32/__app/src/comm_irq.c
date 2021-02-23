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
        EM_UART_CLEAR_FLAG(EM_UART);
    }
}
