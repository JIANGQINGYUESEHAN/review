#include "Drive_ADC_DMA.h"

void Driver_ADC1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC->CFGR |= RCC_CFGR_ADCPRE_1;
    RCC->CFGR &= ~RCC_CFGR_ADCPRE_0;

    /* 1.2 gpio��ʱ�� */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    /* 2. gpio����ģʽ: PC0 PC2 ģ������  CNF=00 MODE=00 */
    GPIOC->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
    GPIOC->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2);

    ADC1->CR1 &= ~ADC_CR1_SCAN;  // �ر�ɨ��ģʽ
    ADC1->CR2 &= ~ADC_CR2_CONT;  // ����ת��
    ADC1->CR2 &= ~ADC_CR2_ALIGN; // �����Ҷ���
    ADC1->CR2 |= ADC_CR2_DMA;    // ʹ��DMAģʽ

    ADC1->SQR1 &= ~ADC_SQR1_L_3;
    ADC1->SQR1 &= ~ADC_SQR1_L_2;
    ADC1->SQR1 &= ~ADC_SQR1_L_1;
    ADC1->SQR1 |= ADC_SQR1_L_0; // ����ת��

    ADC1->SMPR1 &= ~ADC_SMPR1_SMP10_0; // ͨ��10��ת��
    ADC1->SMPR1 |= ADC_SMPR1_SMP10_1;
    ADC1->SMPR1 &= ~ADC_SMPR1_SMP10_2;

    ADC1->SMPR1 &= ~ADC_SMPR1_SMP12_0; // ͨ��12��ת��
    ADC1->SMPR1 |= ADC_SMPR1_SMP12_1;
    ADC1->SMPR1 &= ~ADC_SMPR1_SMP12_2;
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    ADC1->SQR3 &= ~ADC_SQR3_SQ2;

    ADC1->SQR3 |= (10 << 0);
    ADC1->SQR3 |= (12 << 5);
    ADC1->CR2 |= ADC_CR2_EXTSEL;
    ADC1->CR2 &= ~ADC_CR2_EXTTRIG; /* ���ù�������ⲿת�� */
}

void Driver_ADC1_DMA_Init(void) {
    /* 1. ����DMAʱ�� */
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    /* 2. ���ô��䷽�� �������0 ���ڴ��1*/
    DMA1_Channel1->CCR &= ~DMA_CCR1_DIR;
    /* 3. ���ݿ�� 16λ=01 */
    DMA1_Channel1->CCR &= ~DMA_CCR1_PSIZE_1;
    DMA1_Channel1->CCR |= DMA_CCR1_PSIZE_0;

    DMA1_Channel1->CCR &= ~DMA_CCR1_MSIZE_1;
    DMA1_Channel1->CCR |= DMA_CCR1_MSIZE_0;

    /* 4. ������ڴ�ĵ�ַ�Ƿ��� ���費��  �ڴ�Ҫ��*/
    DMA1_Channel1->CCR &= ~DMA_CCR1_PINC;
    DMA1_Channel1->CCR |= DMA_CCR1_MINC;

    /* 5. ����ѭ��ģʽ */
    DMA1_Channel1->CCR |= DMA_CCR1_CIRC;

    /* 6. ��ADC1����DMAģʽ */;
    ADC1->CR2 |= ADC_CR2_DMA;
}

void Driver_ADC1_DMA_Start(uint32_t desAddr, uint8_t len) {
    /* 0. DMA ���� */
    DMA1_Channel1->CPAR = (uint32_t)(&(ADC1->DR));
    DMA1_Channel1->CMAR = desAddr;
    DMA1_Channel1->CNDTR = len;
    DMA1_Channel1->CCR |= DMA_CCR1_EN; /* ʹ��ͨ�� */

    /* 1. �ϵ�: ��ADC������ģʽ���� */
    ADC1->CR2 |= ADC_CR2_ADON;

    /* 2. ִ��У׼ */
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL)
        ;

    /* 3. ADON = 1, ��ʼת�� 0>1 ������ģʽ���� 1->1 ��ʼ */
    ADC1->CR2 |= ADC_CR2_ADON;

    /* 4. ʹ�������ʼת������ͨ�� */;
    ADC1->CR2 |= ADC_CR2_SWSTART;

    /* 5. �ȴ��״�ת����� */
    while ((ADC1->SR & ADC_SR_EOC) == 0)
        ;
}