#include "Drive_BaseTick.h"

void Drive_BaseTick_Init() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
    TIM7->PSC = 7200 - 1;
    TIM7->ARR = 10000 - 1;
    TIM7->DIER |= TIM_DIER_UIE; // 中断使能

    NVIC_SetPriorityGrouping(3);
    /* 6. 设置中断优先级 */
    NVIC_SetPriority(TIM7_IRQn, 1);
    /* 7. 使能定时器6的中断 */
    NVIC_EnableIRQ(TIM7_IRQn);

    TIM7->CR1 |= TIM_CR1_CEN; // 计数器使能
}
void TIM7_IRQHandler() {
    // 清除中断
    TIM7->SR &= ~TIM_SR_UIF;
    Driver_LED_Toggle(LED_1);

    printf("1");
}