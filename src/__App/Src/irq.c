/*
 * CTU/PillScope project
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
    if (LL_USART_IsActiveFlag_RXNE(PS_UART))
    {
        LL_USART_ClearFlag_RXNE(PS_UART);
        char rx = LL_USART_ReceiveData8(PS_UART);

        comm_d_uart.rx_buffer[comm_d_uart.rx_index++] = rx;

        if (comm_d_uart.rx_index >= RX_BUFF_LAST)
            comm_d_uart.rx_index = 0;

        if (rx == '\n')
            comm_d_uart.available = 1;
    }
}

void ADC1_2_IRQHandler(void)
{
#if defined(PS_ADC_MODE_ADC1)
    if (LL_ADC_IsActiveFlag_AWD1(ADC1))
#elif defined(PS_ADC_MODE_ADC12)
    if (LL_ADC_IsActiveFlag_AWD1(ADC1) || LL_ADC_IsActiveFlag_AWD1(ADC2))
#elif defined(PS_ADC_MODE_ADC1234)
    if (LL_ADC_IsActiveFlag_AWD1(ADC1) || LL_ADC_IsActiveFlag_AWD1(ADC2) ||
        LL_ADC_IsActiveFlag_AWD1(ADC3) || LL_ADC_IsActiveFlag_AWD1(ADC4))
#endif
    {

#ifdef PS_ADC_MODE_ADC1
        LL_ADC_ClearFlag_AWD1(ADC1);
#endif

#ifdef PS_ADC_MODE_ADC12
        LL_ADC_ClearFlag_AWD1(ADC2);
#endif

#ifdef PS_ADC_MODE_ADC1234
        LL_ADC_ClearFlag_AWD1(ADC3);
        LL_ADC_ClearFlag_AWD1(ADC4);
#endif

        daq_trig_trigger_scope(&daq);
    }
}

void ADC3_4_IRQHandler(void)
{
    ADC1_2_IRQHandler();
}


void DMA1_Channel1_IRQHandler(void)
{
    asm("nop");
}

void PS_TIM_TRIG_IRQh(void)
{
    if(LL_TIM_IsActiveFlag_CC1(PS_TIM_TRIG) == 1)
    {
        ASSERT(daq.trig.buff_trig != NULL);
        ASSERT(daq.trig.dma_trig != 0);

        int pos = daq.trig.buff_trig->len - LL_DMA_GetDataLength(DMA1, daq.trig.dma_trig);

        int last_idx = pos - 1;
        if (last_idx < 0)
            last_idx = daq.trig.buff_trig->len - 1;

        daq.trig.pos_last = last_idx;
        daq.trig.pos_diff = daq.trig.pos_last - daq.trig.pos_trig;

        if (daq.trig.pos_diff < 0)
            daq.trig.pos_diff += daq.trig.buff_trig->len;

        if (daq.trig.pos_diff >= daq.trig.posttrig_size)
        {
            daq_enable(&daq, 0);
            //LL_TIM_DisableCounter(PS_TIM_TRIG);
            LL_TIM_DisableIT_CC1(PS_TIM_ADC);
            daq.trig.ready = 1;
            daq.trig.is_post = 0;
        }

        LL_TIM_ClearFlag_CC1(PS_TIM_TRIG);
    }
}

void PS_TIM_CNTR_IRQh(void)
{
    if(LL_TIM_IsActiveFlag_UPDATE(PS_TIM_CNTR) == 1)
    {
        LL_TIM_ClearFlag_UPDATE(PS_TIM_CNTR);
        cntr.ovf++;
    }
}

void PS_LA_CH1_IRQh(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(PS_LA_EXTI1) != RESET)
    {
        LL_EXTI_ClearFlag_0_31(PS_LA_EXTI1);
        daq_trig_trigger_la(&daq);
    }
}

void PS_LA_CH2_IRQh(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(PS_LA_EXTI2) != RESET)
    {
        LL_EXTI_ClearFlag_0_31(PS_LA_EXTI2);
        daq_trig_trigger_la(&daq);
    }
}

void PS_LA_CH3_IRQh(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(PS_LA_EXTI3) != RESET)
    {
        LL_EXTI_ClearFlag_0_31(PS_LA_EXTI3);
        daq_trig_trigger_la(&daq);
    }
}

void PS_LA_CH4_IRQh(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(PS_LA_EXTI4) != RESET)
    {
        LL_EXTI_ClearFlag_0_31(PS_LA_EXTI4);
        daq_trig_trigger_la(&daq);
    }
}
