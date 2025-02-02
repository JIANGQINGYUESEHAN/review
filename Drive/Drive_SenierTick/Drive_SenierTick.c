#include "Drive_SenierTick.h"
#include "Drive_USART_Interrupt.h"
void Drive_SenierTick_Init() {

    /* 1. 开启时钟 */
    /* 1.1 TIM1的时钟 */
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    /* 1.2 GPIO的时钟 */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    /* 2. 给PA8配置复用推挽输出 CNF=10  MODE=11*/
    GPIOA->CRH |= (GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8);
    GPIOA->CRH &= ~GPIO_CRH_CNF8_0;
    /* 时基部分 */
    TIM1->PSC |= 7200 - 1;
    TIM1->ARR = 5000 - 1;
    TIM1->CR1 &= ~TIM_CR1_DIR; // 向上计数

    TIM1->RCR |= 4;                 // 重复计数器
    TIM1->CCMR1 &= ~TIM_CCMR1_CC1S; // 配置为输出

    TIM1->CCR1 = 2500; /* 占空比 50% */

    TIM1->CCER &= ~TIM_CCER_CC1P; // 低电平有效
    TIM1->CCER |= TIM_CCER_CC1E;  // 输出1通道使能

    TIM1->CCMR1 |= TIM_CCMR1_OC1M_2; // 配置pwm模式1：110
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_1;
    TIM1->CCMR1 &= ~TIM_CCMR1_OC1M_0;

    /* 高级定时器部分 */
    TIM1->BDTR |= TIM_BDTR_MOE; // 主输出使能

    /* 立即产生更新事件 */
    TIM1->EGR |= TIM_EGR_UG;
    TIM1->SR &= ~TIM_SR_UIF;
    // 重复计数器结束后的中断
    /* 5.1 定时器更新中断使能 */
    TIM1->DIER |= TIM_DIER_UIE;

    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM1_UP_IRQn, 3);
    NVIC_EnableIRQ(TIM1_UP_IRQn);
}

void Drive_SenierTick_Start() { TIM1->CR1 |= TIM_CR1_CEN; }

void Drive_SenierTick_Stop() { TIM1->CR1 &= ~TIM_CR1_CEN; }
void TIM1_UP_IRQHandler(void) {
    // 停掉计数器
    printf("a\r\n");
    TIM1->SR &= ~TIM_SR_UIF;
    Drive_SenierTick_Stop();
}
