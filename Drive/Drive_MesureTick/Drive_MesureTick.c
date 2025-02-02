#include "Drive_MesureTick.h"

void Drive_MesureTick_Init() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    /* 2. PB6����Ϊ����: �������� CNF=01 MODE=00 */
    GPIOB->CRL &= ~(GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6);
    GPIOB->CRL |= GPIO_CRL_CNF6_0;

    TIM4->PSC |= 72 - 1;
    TIM4->ARR |= 65535;
    TIM4->CR1 &= ~TIM_CR1_DIR;      // ���ϼ���
    TIM4->CCMR1 &= ~TIM_CCMR1_IC1F; // �޷�Ƶ

    TIM4->CCER &= ~TIM_CCER_CC1P; // �ȽϼĴ���1�ߵ�ƽ��Ч
    TIM4->CCER |= TIM_CCER_CC2P;  // �ȽϼĴ���2�͵�ƽ��Ч

    TIM4->CCMR1 &= ~TIM_CCMR1_CC1S_1;
    TIM4->CCMR1 |= TIM_CCMR1_CC1S_0; // CC1ͨ��������Ϊ���룬IC1ӳ����TI1�ϣ�01

    TIM4->CCMR1 |= TIM_CCMR1_CC2S_1;
    TIM4->CCMR1 &= ~TIM_CCMR1_CC2S_0; // CC2ͨ��������Ϊ���룬IC2ӳ����TI2�ϣ�10

    TIM4->CCMR1 &= ~TIM_CCMR1_IC1PSC;
    TIM4->CCMR1 &= ~TIM_CCMR1_IC2PSC;

    TIM4->SMCR |= TIM_SMCR_TS_2; // ���˲���Ķ�ʱ������1(TI1FP1) 101
    TIM4->SMCR &= ~TIM_SMCR_TS_1;
    TIM4->SMCR |= TIM_SMCR_TS_0;

    TIM4->SMCR |= TIM_SMCR_SMS_2;
    TIM4->SMCR &= ~(TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0);

    TIM4->CCER |= TIM_CCER_CC1E; // �ȽϼĴ���1ʹ��
    TIM4->CCER |= TIM_CCER_CC2E; // �ȽϼĴ���2ʹ��
}

void Drive_MesureTick_Start() { TIM4->CR1 |= TIM_CR1_CEN; }

void Drive_MesureTick_Stop() { TIM4->CR1 &= ~TIM_CR1_CEN; }

double Drive_MesureTick_GetPWMCycle() { return TIM4->CCR1 / 1000.0; }

double Drive_MesureTick_GetPWMFreq() { return 1000000.0 / TIM4->CCR1; }
double Drive_MesureTick_GetDutyCycle() { return TIM4->CCR2 * 1.0 / TIM4->CCR1; }
