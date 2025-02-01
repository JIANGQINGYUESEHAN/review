#include "Drive_BaseTick.h"

void Drive_BaseTick_Init() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
    TIM7->PSC = 7200 - 1;
    TIM7->ARR = 10000 - 1;
    TIM7->DIER |= TIM_DIER_UIE; // �ж�ʹ��

    NVIC_SetPriorityGrouping(3);
    /* 6. �����ж����ȼ� */
    NVIC_SetPriority(TIM7_IRQn, 1);
    /* 7. ʹ�ܶ�ʱ��6���ж� */
    NVIC_EnableIRQ(TIM7_IRQn);

    TIM7->CR1 |= TIM_CR1_CEN; // ������ʹ��
}
void TIM7_IRQHandler() {
    // ����ж�
    TIM7->SR &= ~TIM_SR_UIF;
    Driver_LED_Toggle(LED_1);

    printf("1");
}