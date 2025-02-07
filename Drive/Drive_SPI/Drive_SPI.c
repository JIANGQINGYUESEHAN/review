#include "Drive_SPI.h"
void Drive_SPI_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    /* 2. �������ŵĹ���ģʽ */
    /* 2.1 cs: ������� PC13*  CNF=00 MODE=11 */
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13;
    /* 2.2 sck: ������� PA5*/
    /* 2.3 mosi: ������� PA7*/
    GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_CNF7);
    GPIOA->CRL |= (GPIO_CRL_MODE5 | GPIO_CRL_MODE7);
    /* 2.4 miso: �������� PA6  CNF=01 MODE=00*/
    GPIOA->CRL &= ~(GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6);
    GPIOA->CRL |= GPIO_CRL_CNF6_0;
    /* 3. spi��ģʽ0  sck����״̬�� 0   */
    SCK_LOW;
    CS_HIGH; // Ƭѡ��ѡ��
    SPI_DELAY;
}
void Drive_SPI_Start(void) { CS_LOW; }
void Drive_SPI_Stop(void) { CS_HIGH; }
uint8_t Drive_SPI_SwapByte(uint8_t byte) {
    uint8_t rbyte = 0x00;
    for (uint8_t i = 0; i < 8; i++) {
        if (byte & 0x80) {
            MOSI_HIGH;
        } else {
            MOSI_LOW;
        }
        byte <<= 1;
        SCK_HIGH;
        rbyte <<= 1;
        if (MISO_READ) {
            rbyte |= 0x01;
        }
        SCK_LOW;
    }
    return rbyte;
}