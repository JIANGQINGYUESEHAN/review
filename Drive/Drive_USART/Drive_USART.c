#include "Drive_USART.h"
void Drive_USART_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    /* 复用推挽输出 mode:11,cnf:10 */
    GPIOA->CRH |= GPIO_CRH_MODE9;
    GPIOA->CRH |= GPIO_CRH_CNF9_1;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;

    /* �?空输�? mode:00;cnf:01*/
    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;
    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;

    USART1->CR1 |= USART_CR1_TE; // 发送使�?
    USART1->CR1 |= USART_CR1_RE; // 接收使能
    USART1->SR &= ~USART_SR_PE;  // 检验控制使�?
    USART1->BRR |= 0x271;        // 波特�?
    USART1->CR1 &= ~USART_CR1_M;
    USART1->CR2 &= ~USART_CR2_STOP;

    USART1->CR1 |= USART_CR1_UE; // 串口使能
}
void Drive_USART_Sendchar(uint8_t ch) {
    // 先判�?发送数�?寄存器空�?否为�?
    while ((USART1->SR & USART_SR_TXE) == 0)
        ;
    // 在进行发�?
    USART1->DR = ch;
}

uint8_t Driver_USART1_ReceiveChar(void) {
    // 先判�?发送数�?寄存器空�?否为�?
    while ((USART1->SR & USART_SR_RXNE) == 0)
        ;
    // 在进行发�?
    return USART1->DR;
}
void Drive_USART_Sendstr(uint8_t *str, uint16_t len) {
    uint8_t i = 0;
    for (uint8_t i = 0; i < len; i++) {
        Drive_USART_Sendchar(str[i]);
    }
}
uint8_t buff[100];
void Driver_USART1_ReceiveString(uint8_t buff[], uint8_t *len) {
    uint8_t i = 0;

    while (1) {
        while ((USART1->SR & USART_SR_RXNE) == 0)
        // 0,然后�?&一下为0，�?�明USART_SR_RXNE==1,即�?�测到读数�?寄存器结�?
        {
            if ((USART1->SR & USART_SR_IDLE) == 0) {
                *len = i;
                return;
            }
        }
        buff[i] = USART1->DR;
        i++;
    }
}