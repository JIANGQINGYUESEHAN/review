#include "Drive_GeneralTick.h"

void Drive_GeneralTick_Init() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    /* 复用推挽输出 */
    GPIOA->CRL |= (GPIO_CRL_CNF1_1 | GPIO_CRL_MODE1);
    GPIOA->CRL &= ~GPIO_CRL_CNF1_0;

    /* 定时器基本设置 */
    TIM5->PSC = 7200 - 1;
    /* 3.2 自动重装载寄存器的配置 */
    TIM5->ARR = 100 - 1;

    TIM5->CR1 &= ~TIM_CR1_DIR; // 向下计数
    TIM5->CCR2 = 97;
    /* 配置输出比较模式 */
    /* 3.5 把通道2配置为输出  CCMR1_CC2S=00 */
    TIM5->CCMR1 &= ~TIM_CCMR1_CC2S;

    /* 配置PWM模式 */
    TIM5->CCMR1 |= TIM_CCMR1_OC2M_2;
    TIM5->CCMR1 |= TIM_CCMR1_OC2M_1;
    TIM5->CCMR1 &= ~TIM_CCMR1_OC2M_0;

    /* 3.7 使能通道2  CCER_CC2E=1 */
    TIM5->CCER |= TIM_CCER_CC2E;

    /* 3.8 设置通道的极性 0=高电平有效  1=低电平有效 */
    TIM5->CCER &= ~TIM_CCER_CC2P;
}

void Drive_GeneralTick_Start() { TIM5->CR1 |= TIM_CR1_CEN; }

void Drive_GeneralTick_Stop() { TIM5->CR1 &= ~TIM_CR1_CEN; }

void Drive_GeneralTick_AdjustDutyCycle(uint8_t dutyCycle) {
    TIM5->CCR2 = dutyCycle;
}
