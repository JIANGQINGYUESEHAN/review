#include "Drive_KEY.h"
#include "Delay.h"
#include "led.h"
void Drive_Key_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;

    GPIOF->CRH &= ~GPIO_CRH_MODE10;
    // CNF:10
    GPIOF->CRH |= GPIO_CRH_CNF10_1;
    GPIOF->CRH &= ~GPIO_CRH_CNF10_0;

    /* AFIO 寄存器输出配置 （按键输出配置）*/
    GPIOF->ODR &= ~GPIO_ODR_ODR10;

    /* 外部中断配置寄存器配置 */
    AFIO->EXTICR[2] &= ~AFIO_EXTICR3_EXTI10; // 置0
    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI10_PF;

    EXTI->IMR |= EXTI_IMR_MR10;

    EXTI->RTSR |= EXTI_RTSR_TR10; // 上升沿中断
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(EXTI15_10_IRQn, 3);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler(void) {

    // 清除中断
    EXTI->PR |= EXTI_PR_PR10;
    Delay_ms(5);
    if ((GPIOF->ODR & GPIO_ODR_ODR10) == 0) {
        Driver_LED_Toggle(LED_2);
    }
}