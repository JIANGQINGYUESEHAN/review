#include "Drive_GeneralTick.h"

void Drive_GeneralTick_Init() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    /* ����������� */
    GPIOA->CRL |= (GPIO_CRL_CNF1_1 | GPIO_CRL_MODE1);
    GPIOA->CRL &= ~GPIO_CRL_CNF1_0;

    /* ��ʱ���������� */
    TIM5->PSC = 7200 - 1;
    /* 3.2 �Զ���װ�ؼĴ��������� */
    TIM5->ARR = 100 - 1;

    TIM5->CR1 &= ~TIM_CR1_DIR; // ���¼���
    TIM5->CCR2 = 97;
    /* ��������Ƚ�ģʽ */
    /* 3.5 ��ͨ��2����Ϊ���  CCMR1_CC2S=00 */
    TIM5->CCMR1 &= ~TIM_CCMR1_CC2S;

    /* ����PWMģʽ */
    TIM5->CCMR1 |= TIM_CCMR1_OC2M_2;
    TIM5->CCMR1 |= TIM_CCMR1_OC2M_1;
    TIM5->CCMR1 &= ~TIM_CCMR1_OC2M_0;

    /* 3.7 ʹ��ͨ��2  CCER_CC2E=1 */
    TIM5->CCER |= TIM_CCER_CC2E;

    /* 3.8 ����ͨ���ļ��� 0=�ߵ�ƽ��Ч  1=�͵�ƽ��Ч */
    TIM5->CCER &= ~TIM_CCER_CC2P;
}

void Drive_GeneralTick_Start() { TIM5->CR1 |= TIM_CR1_CEN; }

void Drive_GeneralTick_Stop() { TIM5->CR1 &= ~TIM_CR1_CEN; }

void Drive_GeneralTick_AdjustDutyCycle(uint8_t dutyCycle) {
    TIM5->CCR2 = dutyCycle;
}
