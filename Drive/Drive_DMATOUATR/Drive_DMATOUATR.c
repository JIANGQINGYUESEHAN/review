#include "Drive_DMATOUATR.h"

void Drive_DMATOUART_Init() {
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    // DMA1_Channel4->CCR &= ~DMA_CCR1_MEM2MEM; // ���Ǵ洢�����洢��ģʽ��
    DMA1_Channel4->CCR |= DMA_CCR1_DIR; // �������

    DMA1_Channel4->CCR &= ~DMA_CCR1_MSIZE; // 8λ
    DMA1_Channel4->CCR &= ~DMA_CCR1_PSIZE; // 8λ

    DMA1_Channel4->CCR |= DMA_CCR1_MINC;  //  ִ�д洢����ַ��������
    DMA1_Channel4->CCR &= ~DMA_CCR1_PINC; // �����ַ������ģʽ

    DMA1_Channel4->CCR |= DMA_CCR1_TCIE; // ����������ж�
    // ����DMA����
    USART1->CR3 |= USART_CR3_DMAT;
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel4_IRQn, 3);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
}
void Drive_DMATOUART_TransmitData(uint32_t srcAddr, uint32_t desAddr,
                                  uint16_t dataLen) {

    DMA1_Channel4->CPAR = desAddr;
    /* 2. ���ô洢����ַ */
    DMA1_Channel4->CMAR = srcAddr;

    /* 3. ����Ҫ����������� */;
    DMA1_Channel4->CNDTR = dataLen;

    /* 4. ����ͨ��,��ʼ���� */
    DMA1_Channel4->CCR |= DMA_CCR4_EN;
}
#include "Drive_USART_Interrupt.h"

void DMA1_Channel4_IRQHandler(void) {

    if (DMA1->ISR & DMA_ISR_TCIF4) {
        /* �����������ж���ɱ�־λ */
        DMA1->IFCR |= DMA_IFCR_CGIF4;
        printf("1");
        /* ͨ������Ҫ��,���Թر� */
        // DMA1_Channel4->CCR &= ~DMA_CCR4_EN;
    }
}
