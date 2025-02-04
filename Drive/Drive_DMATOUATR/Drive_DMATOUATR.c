#include "Drive_DMATOUATR.h"

void Drive_DMATOUART_Init() {
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    // DMA1_Channel4->CCR &= ~DMA_CCR1_MEM2MEM; // ：非存储器到存储器模式；
    DMA1_Channel4->CCR |= DMA_CCR1_DIR; // 从外设读

    DMA1_Channel4->CCR &= ~DMA_CCR1_MSIZE; // 8位
    DMA1_Channel4->CCR &= ~DMA_CCR1_PSIZE; // 8位

    DMA1_Channel4->CCR |= DMA_CCR1_MINC;  //  执行存储器地址增量操作
    DMA1_Channel4->CCR &= ~DMA_CCR1_PINC; // 外设地址不增量模式

    DMA1_Channel4->CCR |= DMA_CCR1_TCIE; // 允许传输完成中断
    // 串口DMA设置
    USART1->CR3 |= USART_CR3_DMAT;
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel4_IRQn, 3);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
}
void Drive_DMATOUART_TransmitData(uint32_t srcAddr, uint32_t desAddr,
                                  uint16_t dataLen) {

    DMA1_Channel4->CPAR = desAddr;
    /* 2. 设置存储器地址 */
    DMA1_Channel4->CMAR = srcAddr;

    /* 3. 设置要传输的数据量 */;
    DMA1_Channel4->CNDTR = dataLen;

    /* 4. 开启通道,开始传输 */
    DMA1_Channel4->CCR |= DMA_CCR4_EN;
}
#include "Drive_USART_Interrupt.h"

void DMA1_Channel4_IRQHandler(void) {

    if (DMA1->ISR & DMA_ISR_TCIF4) {
        /* 清除传输完成中断完成标志位 */
        DMA1->IFCR |= DMA_IFCR_CGIF4;
        printf("1");
        /* 通道不需要了,可以关闭 */
        // DMA1_Channel4->CCR &= ~DMA_CCR4_EN;
    }
}
