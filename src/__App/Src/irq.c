/*
 * CTU/UniLabTool project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "cfg.h"
#include "irq.h"
#include "periph.h"
#include "main.h"
#include "app_data.h"
#include "comm.h"

/*
static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)       // OVERIDE THIS in: /USB_DEVICE/App/usbd_cdc_if.c !!!
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
     comm_d_usb.rx_buffer[comm_d_usb.rx_index++] = *Buf;

     if (comm_d_usb.rx_index >= RX_BUFF_LAST)
         comm_d_usb.rx_index = 0;

     if (*Buf == '\n')
         comm_d_usb.available = 1;
     Buf++;
  }

  return USBD_OK;
}
*/

void USART1_IRQHandler(void)
{
    if (LL_USART_IsActiveFlag_RXNE(ULT_UART))
    {
        LL_USART_ClearFlag_RXNE(ULT_UART);
        char rx = LL_USART_ReceiveData8(ULT_UART);

        comm_d_uart.rx_buffer[comm_d_uart.rx_index++] = rx;

        if (comm_d_uart.rx_index >= RX_BUFF_LAST)
            comm_d_uart.rx_index = 0;

        if (rx == '\n')
            comm_d_uart.available = 1;
    }
}

void ADC1_2_IRQHandler(void)
{
    if (LL_ADC_IsActiveFlag_AWD1(ADC1))
    {
        int pos = ADC_BUFF_SIZE - LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_1);

        LL_ADC_ClearFlag_AWD1(ADC1);

        if (trig.ready)
            return;

        /*
        if (tignore)
        {
            tignore = 0;

            uint32_t h = LL_ADC_GetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_HIGH);
            uint32_t l = LL_ADC_GetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_LOW);

            LL_ADC_SetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_HIGH, l);
            LL_ADC_SetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_LOW, h);
        }
        else
        {
        */
            int last_idx = pos - 1;
            if (last_idx < 0)
                last_idx = ADC_BUFF_SIZE - 1;
            int prev_last_idx = last_idx - CHANNELS;
            if (prev_last_idx < 0)
                prev_last_idx += ADC_BUFF_SIZE;

            if ((trig.edge == RISING && buff_adc1[last_idx] > trig.val && buff_adc1[prev_last_idx] <= trig.val) ||
                (trig.edge == FALLING && buff_adc1[last_idx] < trig.val && buff_adc1[prev_last_idx] >= trig.val)) // trig cond success
            {
                trig.cntr++;
                trig.pos_trig = last_idx;
                trig.pos_frst = last_idx - (ADC_BUFF_SIZE / 2);
                if (trig.pos_frst < 0)
                    trig.pos_frst += ADC_BUFF_SIZE;

                if (trig.pretrig_cntr > 2000) // pretrigger counter
                {
                    LL_ADC_SetAnalogWDMonitChannels(ADC1, LL_ADC_AWD_DISABLE);
                    // start timer - count posttriger (half buffer)

                    LL_TIM_SetAutoReload(ULT_TIM_TRIG, 70); // posttrigger counter
                    LL_TIM_EnableCounter(ULT_TIM_TRIG);
                    LL_TIM_CC_EnableChannel(ULT_TIM_TRIG, LL_TIM_CHANNEL_CH1);
                    trig.pretrig_cntr = 0;
                }
                if (uwTick > trig.uwtick_last)
                    trig.pretrig_cntr += uwTick - trig.uwtick_last;
                else
                    trig.pretrig_cntr += (uwTick - trig.uwtick_last) + 4294967295;
                trig.uwtick_last = uwTick;
            }
            trig.all_cntr++;

            /*
            //else // false trig, switch edges and wait for another window
            //{
                tignore = 1;

                uint32_t h = LL_ADC_GetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_HIGH);
                uint32_t l = LL_ADC_GetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_LOW);

                LL_ADC_SetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_HIGH, l);
                LL_ADC_SetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_LOW, h);
                trig_false_cntr++;
            //}
             */
        //}
    }
}

void DMA1_Channel1_IRQHandler(void)
{
    asm("nop");
}

void TIM4_IRQHandler(void)
{
    if(LL_TIM_IsActiveFlag_CC1(ULT_TIM_TRIG) == 1)
    {
        int buffsz = ADC_BUFF_SIZE;
        trig.pos_last = buffsz - LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_1) - 1;

        LL_TIM_ClearFlag_CC1(ULT_TIM_TRIG);

        trig.pos_diff = trig.pos_last - trig.pos_trig;
        if (trig.pos_diff < 0)
            trig.pos_diff += buffsz;

        if (trig.pos_diff >= buffsz / 2)
        {
            daq_enable(&daq, syst.mode, 0);
            LL_TIM_DisableCounter(ULT_TIM_TRIG);
            trig.ready = 1;
        }
    }
}
