#include "Drive_GeneralTickTest.h"
void Drive_GeneralTickTestTest_Init() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    /* ����������� */
    GPIOB->CRL &= ~(GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6);
    GPIOB->CRL |= GPIO_CRL_CNF6_0;

    TIM4->PSC = 72 - 1;
    /* 3.2 �Զ���װ�ؼĴ�����ֵ: �������,����������� */
    TIM4->ARR = 65535;

    TIM4->CR1 &= ~TIM_CR1_DIR; // ���������ϼ�����

    /* 4.1 TI1��ѡ��: ��CH1ֱ�����ӵ�TI1 */
    TIM4->CR2 &= ~TIM_CR2_TI1S;

    /* 3.7 ʹ��ͨ��2  CCER_CC2E=1 */
    TIM4->CCER |= TIM_CCER_CC2E;
    TIM4->DIER |= TIM_DIER_CC1IE; // ������/�Ƚ�1�жϡ�
    TIM4->CCER &= ~TIM_CCER_CC1P;
    TIM4->CCMR1 &= ~TIM_CCMR1_CC1S_1;
    TIM4->CCMR1 |= TIM_CCMR1_CC1S_0; // CC1ͨ��������Ϊ���룬IC1ӳ����TI1�ϣ�

    TIM4->CCMR1 &= ~TIM_CCMR1_IC1F;   // ���˲���
    TIM4->CCMR1 &= ~TIM_CCMR1_IC1PSC; // �޷�Ƶ��

    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM4_IRQn, 3);
    NVIC_EnableIRQ(TIM4_IRQn);
    TIM4->CCER |= TIM_CCER_CC1E; // ����/����1���ʹ��
}

void Drive_GeneralTickTestTest_Start() { TIM4->CR1 |= TIM_CR1_CEN; }

void Drive_GeneralTickTestTest_Stop() { TIM4->CR1 &= ~TIM_CR1_CEN; }
uint8_t count = 0;
uint8_t t = 0;
void TIM4_IRQHandler(void) {
    // ����ж�
    TIM4->SR &= ~TIM_SR_CC1IF;
    count++;
    if (count == 1) {
        TIM4->CNT = 0; /* ���������� */
    } else if (count == 2) {
        t = TIM4->CCR1;
        /* �����صļ�����0���¼��� */
        count = 0;
    }
}
double Driver_GeneralTickTestTest_GetPWMCycle(void) { return t / 1000.0; }

/* ����PWM��Ƶ�� */
double Driver_GeneralTickTestTest_GetPWMFreq(void) { return 1000000 / t; }
