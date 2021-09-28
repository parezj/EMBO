/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "periph_dma.h"


void dma_set(uint32_t src, DMA_TypeDef* dma, uint32_t dma_ch, uint32_t dst, uint32_t buff_size, uint32_t p_sz, uint32_t m_sz, uint32_t dir)
{
    LL_DMA_DisableChannel(dma, dma_ch);

    // DMA transfer addresses and size.
    LL_DMA_ConfigAddresses(dma, dma_ch, src, dst, dir);
    LL_DMA_SetPeriphSize(dma, dma_ch, p_sz);
    LL_DMA_SetMemorySize(dma, dma_ch, m_sz);
    LL_DMA_SetDataLength(dma, dma_ch, buff_size);

    //LL_DMA_EnableIT_TC(dma, dma_ch); // Enable transfer complete interrupt.
    //LL_DMA_EnableIT_HT(dma, dma_ch); // Enable half transfer interrupt.
    //LL_DMA_EnableIT_TE(dma, dma_ch); // Enable transfer error interrupt.

    // Enable
    LL_DMA_EnableChannel(dma, dma_ch);
}
