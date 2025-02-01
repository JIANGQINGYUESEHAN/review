#include "Drive_GeneralTickTest.h"
void Drive_GeneralTickTestTest_Init() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    /* 复用推挽输出 */
    GPIOB->CRL &= ~(GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6);
    GPIOB->CRL |= GPIO_CRL_CNF6_0;

    TIM4->PSC = 72 - 1;
    /* 3.2 自动重装载寄存器的值: 设置最大,尽量避免溢出 */
    TIM4->ARR = 65535;

    TIM4->CR1 &= ~TIM_CR1_DIR; // 计数器向上计数；

    /* 4.1 TI1的选择: 把CH1直接连接到TI1 */
    TIM4->CR2 &= ~TIM_CR2_TI1S;

    /* 3.7 使能通道2  CCER_CC2E=1 */
    TIM4->CCER |= TIM_CCER_CC2E;
    TIM4->DIER |= TIM_DIER_CC1IE; // 允许捕获/比较1中断。
    TIM4->CCER &= ~TIM_CCER_CC1P;
    TIM4->CCMR1 &= ~TIM_CCMR1_CC1S_1;
    TIM4->CCMR1 |= TIM_CCMR1_CC1S_0; // CC1通道被配置为输入，IC1映射在TI1上；

    TIM4->CCMR1 &= ~TIM_CCMR1_IC1F;   // 无滤波器
    TIM4->CCMR1 &= ~TIM_CCMR1_IC1PSC; // 无分频器

    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM4_IRQn, 3);
    NVIC_EnableIRQ(TIM4_IRQn);
    TIM4->CCER |= TIM_CCER_CC1E; // 输入/捕获1输出使能
}

void Drive_GeneralTickTestTest_Start() { TIM4->CR1 |= TIM_CR1_CEN; }

void Drive_GeneralTickTestTest_Stop() { TIM4->CR1 &= ~TIM_CR1_CEN; }
uint8_t count = 0;
uint8_t t = 0;
void TIM4_IRQHandler(void) {
    // 清除中断
    TIM4->SR &= ~TIM_SR_CC1IF;
    count++;
    if (count == 1) {
        TIM4->CNT = 0; /* 计数器清零 */
    } else if (count == 2) {
        t = TIM4->CCR1;
        /* 上升沿的计数从0重新计数 */
        count = 0;
    }
}
double Driver_GeneralTickTestTest_GetPWMCycle(void) { return t / 1000.0; }

/* 返回PWM的频率 */
double Driver_GeneralTickTestTest_GetPWMFreq(void) { return 1000000 / t; }
