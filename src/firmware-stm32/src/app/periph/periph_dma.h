/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INC_PERIPH_DMA_H_
#define INC_PERIPH_DMA_H_

#include "main.h"

#include <stdint.h>

/*
static inline void iwdg_feed()
{
    EM_IWDG_RST;
};
*/

// p_sz=periph size, m_sz=memory size, dir=periph-to-mem / mem-to-periph / mem-to-mem
void dma_set(uint32_t src, DMA_TypeDef* dma, uint32_t dma_ch, uint32_t dst, uint32_t buff_size, uint32_t p_sz, uint32_t m_sz, uint32_t dir);

#endif /* INC_PERIPH_DMA_H_ */
