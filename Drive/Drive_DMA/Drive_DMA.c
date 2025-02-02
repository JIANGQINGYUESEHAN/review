#include "Drive_DMA.h"
void Drive_DMA_Init() {
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    DMA1_Channel1->CCR |= DMA_CCR1_MEM2MEM; // 存储器到存储器模式
    DMA1_Channel1->CCR &= ~DMA_CCR1_DIR;    // 从外设读

    DMA1_Channel1->CCR &= ~DMA_CCR1_MSIZE; // 存储器数据宽度
    DMA1_Channel1->CCR &= ~DMA_CCR1_PSIZE; // 外设数据宽度
    DMA1_Channel1->CCR |= DMA_CCR1_PINC;   /* 外设地址自增 */

    DMA1_Channel1->CCR |= DMA_CCR1_MINC; /* 存储器地址自增 */

    DMA1_Channel1->CCR |= DMA_CCR1_TCIE; // 允许传输完成中断
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel1_IRQn, 3);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}
void Drive_DMA_TransmitData(uint32_t srcAddr, uint32_t desAddr,
                            uint16_t dataLen) {
    DMA1_Channel1->CPAR |= srcAddr;
    DMA1_Channel1->CMAR |= desAddr;
    DMA1_Channel1->CNDTR = dataLen;

    /* 4. 开启通道,开始传输 */
    DMA1_Channel1->CCR |= DMA_CCR1_EN;
}
uint8_t isTransmitFinished = 0;
void DMA1_Channel1_IRQHandler(void) {
    if (DMA1->ISR & DMA_ISR_TCIF1) {
        /* 清除传输完成中断完成标志位 */
        DMA1->IFCR |= DMA_IFCR_CGIF1;

        /* 通道不需要了,可以关闭 */
        DMA1_Channel1->CCR &= ~DMA_CCR1_EN;
        isTransmitFinished = 1;
    }
}
