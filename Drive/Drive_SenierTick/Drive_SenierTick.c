#include "Drive_SenierTick.h"
#include "Drive_USART_Interrupt.h"
void Drive_SenierTick_Init() {

    /* 1. ����ʱ�� */
    /* 1.1 TIM1��ʱ�� */
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    /* 1.2 GPIO��ʱ�� */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    /* 2. ��PA8���ø���������� CNF=10  MODE=11*/
    GPIOA->CRH |= (GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8);
    GPIOA->CRH &= ~GPIO_CRH_CNF8_0;
    /* ʱ������ */
    TIM1->PSC |= 7200 - 1;
    TIM1->ARR = 5000 - 1;
    TIM1->CR1 &= ~TIM_CR1_DIR; // ���ϼ���

    TIM1->RCR |= 4;                 // �ظ�������
    TIM1->CCMR1 &= ~TIM_CCMR1_CC1S; // ����Ϊ���

    TIM1->CCR1 = 2500; /* ռ�ձ� 50% */

    TIM1->CCER &= ~TIM_CCER_CC1P; // �͵�ƽ��Ч
    TIM1->CCER |= TIM_CCER_CC1E;  // ���1ͨ��ʹ��

    TIM1->CCMR1 |= TIM_CCMR1_OC1M_2; // ����pwmģʽ1��110
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_1;
    TIM1->CCMR1 &= ~TIM_CCMR1_OC1M_0;

    /* �߼���ʱ������ */
    TIM1->BDTR |= TIM_BDTR_MOE; // �����ʹ��

    /* �������������¼� */
    TIM1->EGR |= TIM_EGR_UG;
    TIM1->SR &= ~TIM_SR_UIF;
    // �ظ���������������ж�
    /* 5.1 ��ʱ�������ж�ʹ�� */
    TIM1->DIER |= TIM_DIER_UIE;

    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM1_UP_IRQn, 3);
    NVIC_EnableIRQ(TIM1_UP_IRQn);
}

void Drive_SenierTick_Start() { TIM1->CR1 |= TIM_CR1_CEN; }

void Drive_SenierTick_Stop() { TIM1->CR1 &= ~TIM_CR1_CEN; }
void TIM1_UP_IRQHandler(void) {
    // ͣ��������
    printf("a\r\n");
    TIM1->SR &= ~TIM_SR_UIF;
    Drive_SenierTick_Stop();
}
