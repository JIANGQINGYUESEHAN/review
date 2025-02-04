#include "Drive_ADC.h"
void Drive_ADC1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    // ʱ�ӷ�Ƶ
    RCC->CFGR |= RCC_CFGR_ADCPRE_1;
    RCC->CFGR &= ~RCC_CFGR_ADCPRE_0;

    /* 1.2 gpio��ʱ�� */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    /* 2. gpio����ģʽ: PC0 ģ������  CNF=00 MODE=00 */
    GPIOC->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
    /* ADC���� */
    ADC1->CR1 &= ~ADC_CR1_SCAN;  // �ر�ɨ��ģʽ
    ADC1->CR2 &= ~ADC_CR2_ALIGN; // �Ҷ���
    ADC1->CR2 |= ADC_CR2_CONT;   // ��������ת��
    ADC1->SQR1 &= ~ADC_SQR1_L;   // ת������

    ADC1->CR2 |=
        ADC_CR2_EXTSEL; // ����ͨ����ת�����ⲿ�¼�,SWSTART���������111

    // ת��ͨ��
    /* ����ʱ�� */
    ADC1->SMPR1 &= ~(ADC_SMPR1_SMP10_2 | ADC_SMPR1_SMP10_0);
    ADC1->SMPR1 |= ADC_SMPR1_SMP10_1;

    ADC1->SQR3 &= ~ADC_SQR3_SQ1; // ��0
    ADC1->SQR3 |= (10 << 0);

    ADC1->CR2 |= ADC_CR2_EXTTRIG; /* ������������ⲿת�� */
}
void Drive_ADC1_StartConvert(void) {
    // ����0
    ADC1->CR2 |= ADC_CR2_ADON;
    // �ڽ��п���У׼
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL)
        ; // У׼���

    /* 4. ʹ�������ʼת������ͨ�� */;
    ADC1->CR2 |= ADC_CR2_SWSTART;

    /* 5. �ȴ��״�ת����� */
    while ((ADC1->SR & ADC_SR_EOC) == 0)
        ;
}
double Drive_ADC1_ReadV(void) { return ADC1->DR * 3.3 / 4095; }