#include "Drive_USART_Interrupt.h"
void Drive_USART_Interrupt_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    /* 澶嶇敤鎺ㄦ尳杈撳嚭 mode:11,cnf:10 */
    GPIOA->CRH |= GPIO_CRH_MODE9;
    GPIOA->CRH |= GPIO_CRH_CNF9_1;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;

    /* 娴?绌鸿緭鍏? mode:00;cnf:01*/
    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;
    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;

    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE; // 鎺ユ敹浣胯兘
    USART1->SR &= ~USART_SR_PE;  // 妫�楠屾帶鍒朵娇鑳?
    USART1->BRR |= 0x271;        // 娉㈢壒鐜?
    USART1->CR1 &= ~USART_CR1_M;
    USART1->CR2 &= ~USART_CR2_STOP;

    USART1->CR1 |= USART_CR1_IDLEIE;
    USART1->CR1 |= USART_CR1_RXNEIE;

    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(USART1_IRQn, 3);
    NVIC_EnableIRQ(USART1_IRQn);

    USART1->CR1 |= USART_CR1_UE; // 涓插彛浣胯兘
}
void Drive_USART_Interrupt_Sendchar(uint8_t ch) {

    while ((USART1->SR & USART_SR_TXE) == 0)
        ;
    // 鍦ㄨ繘琛屽彂閫?
    USART1->DR = ch;
}

uint8_t Drive_USART_Interrupt_ReceiveChar(void) {
    // 鍏堝垽鏂?鍙戦�佹暟鎹?瀵勫瓨鍣ㄧ┖鏄?鍚︿负绌?
    while ((USART1->SR & USART_SR_RXNE) == 0)
        ;

    return USART1->DR;
}
void Drive_USART_Interrupt_Sendstr(uint8_t *str, uint16_t len) {
    for (uint8_t i = 0; i < len; i++) {
        Drive_USART_Interrupt_Sendchar(str[i]);
    }
}
void Drive_USART_Interrupt_Receivestr(uint8_t buff[], uint8_t *len) {
    uint8_t i = 0;

    while (1) {
        while ((USART1->SR & USART_SR_RXNE) == 0) {
            if ((USART1->SR & USART_SR_IDLE) == 0) {
                *len = i;
                return;
            }
        }
        buff[i] = USART1->DR;
        i++;
    }
}
uint8_t buffa[100] = {0};
uint8_t len = 0;
void USART1_IRQHandler(void) {
    if ((USART1->SR & USART_SR_IDLE)) {
        /* 总线为空就是要传送的设备已经传送完了要开始接收 */

        USART1->SR; // 先清除中断
        USART1->DR;

        Drive_USART_Interrupt_Sendstr(buffa, len);
        len = 0;

    } else if ((USART1->SR & USART_SR_RXNE)) {
        USART1->DR; // 先清除中断

        // 发送数据
        buffa[len] = USART1->DR;
        len++;
    }
}
int fputc(int c, FILE *file) {
    Drive_USART_Sendchar(c);
    return c;
}
