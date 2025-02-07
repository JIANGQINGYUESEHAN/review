#include "Drive_SPI_HardWare.h"
void Drive_SPI_HardWare_Init(void) {
    /* 1. ����SPI1��ʱ�� ����GPIOʱ�� PA��PC*/
    RCC->APB2ENR |=
        (RCC_APB2ENR_SPI1EN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPAEN);

    /* 2. �������ŵĹ���ģʽ */
    /* 2.1 cs: ͨ��������� PC13*  CNF=00 MODE=11 */
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13;
    /* 2.2 sck: ������� PA5*/ /* cnf=10  mode=11 */
    /* 2.3 mosi: ������� PA7*/
    GPIOA->CRL |=
        (GPIO_CRL_MODE5 | GPIO_CRL_MODE7 | GPIO_CRL_CNF7_1 | GPIO_CRL_CNF5_1);
    GPIOA->CRL &= ~(GPIO_CRL_CNF5_0 | GPIO_CRL_CNF7_0);
    /* 2.4 miso: �������� PA6  CNF=01 MODE=00*/
    GPIOA->CRL &= ~(GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6);
    GPIOA->CRL |= GPIO_CRL_CNF6_0;

    /* spiӲ������ */
    SPI1->CR1 |= SPI_CR1_MSTR; // ȷ��Ϊ���豸

    /* 3.2 NSS����, ���豸��Ƭѡʹ����ͨ��GPIO����*/
    SPI1->CR1 |= SPI_CR1_SSM;
    SPI1->CR2 &= ~SPI_CR2_SSOE;
    SPI1->CR1 |= SPI_CR1_SSI;

    SPI1->CR1 &= ~SPI_CR1_BR_2; // 4��Ƶ
    SPI1->CR1 &= ~SPI_CR1_BR_1;
    SPI1->CR1 |= SPI_CR1_BR_0;

    SPI1->CR1 &= ~SPI_CR1_LSBFIRST; // �ȷ���MSB
    SPI1->CR1 &= ~SPI_CR1_DFF;      // ʹ��8λ����֡��ʽ���з���/���գ�
    SPI1->CR1 &= ~SPI_CR1_CPOL;
    SPI1->CR1 &= ~SPI_CR1_CPHA;
    SPI1->CR1 |= SPI_CR1_SPE; // ʹ��
}
void Drive_SPI_HardWare_Start(void) { CS_LOW; }
void Drive_SPI_HardWare_Stop(void) { CS_HIGH; }
uint8_t Drive_SPI_HardWare_SwapByte(uint8_t byte) {

    while (SPI1->SR & SPI_SR_TXE)
        ;
    SPI1->DR = byte;
    while (SPI1->SR & SPI_SR_RXNE)
        ;
    return (uint8_t)(SPI1->DR & 0xff);
}