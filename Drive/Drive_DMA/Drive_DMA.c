#include "Drive_DMA.h"
void Drive_DMA_Init() {
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    DMA1_Channel1->CCR |= DMA_CCR1_MEM2MEM; // �洢�����洢��ģʽ
    DMA1_Channel1->CCR &= ~DMA_CCR1_DIR;    // �������

    DMA1_Channel1->CCR &= ~DMA_CCR1_MSIZE; // �洢�����ݿ��
    DMA1_Channel1->CCR &= ~DMA_CCR1_PSIZE; // �������ݿ��
    DMA1_Channel1->CCR |= DMA_CCR1_PINC;   /* �����ַ���� */

    DMA1_Channel1->CCR |= DMA_CCR1_MINC; /* �洢����ַ���� */

    DMA1_Channel1->CCR |= DMA_CCR1_TCIE; // ����������ж�
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel1_IRQn, 3);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}
void Drive_DMA_TransmitData(uint32_t srcAddr, uint32_t desAddr,
                            uint16_t dataLen) {
    DMA1_Channel1->CPAR |= srcAddr;
    DMA1_Channel1->CMAR |= desAddr;
    DMA1_Channel1->CNDTR = dataLen;

    /* 4. ����ͨ��,��ʼ���� */
    DMA1_Channel1->CCR |= DMA_CCR1_EN;
}
uint8_t isTransmitFinished = 0;
void DMA1_Channel1_IRQHandler(void) {
    if (DMA1->ISR & DMA_ISR_TCIF1) {
        /* �����������ж���ɱ�־λ */
        DMA1->IFCR |= DMA_IFCR_CGIF1;

        /* ͨ������Ҫ��,���Թر� */
        DMA1_Channel1->CCR &= ~DMA_CCR1_EN;
        isTransmitFinished = 1;
    }
}
