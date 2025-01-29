#include "Drive_I2C_HardWare.h"

void Driver_I2C2_HardWare_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    /* 通用开漏输出 */
    GPIOB->CRH |=
        (GPIO_CRH_MODE10 | GPIO_CRH_MODE11 | GPIO_CRH_CNF10 | GPIO_CRH_CNF11);

    /* I2C开始配置 */
    I2C2->CR1 &= ~I2C_CR1_SMBUS; // I2C模式

    I2C2->CCR &= ~I2C_CCR_FS; // 标准模式的I2C

    /* 3.2 配置给I2C设备提供的时钟的频率 36MHz*/
    /* 3.3 配置I2C产生时钟的频率 100K or 400K
        Thigh=CCR * Tcplk1

        ccr = Thigh/=Tcplk1 = 5us / (1/36)us = 180

    */

    I2C2->CCR |= 180 << 0;
    /* 3.4 时钟信号的上升沿
          100KHz的时候要求最大上升沿不超过1us(手册)。
            时钟频率是36MHz则 写入：1 /（1/36） + 1 = 37
           其实就是计算的 最大上升沿时间/时钟周期 + 1

    */

    I2C2->TRISE |= 37;

    I2C2->CR1 |= I2C_CR1_PE; // 启用I2C模块
}

uint8_t Driver_I2C2_HardWare_Start(void) {
    I2C2->CR1 |= I2C_CR1_START;
    uint16_t timeout = 0xffff;
    while ((I2C2->SR1 & I2C_SR1_SB) & timeout) {
        timeout--;
    }
    return timeout ? OK : FALT;
}

void Driver_I2C2_HardWare_Stop(void) { I2C2->CR1 |= I2C_CR1_STOP; }

void Driver_I2C2_HardWare_Ack(void) { I2C2->CR1 |= I2C_CR1_ACK; }

void Driver_I2C2_HardWare_NAck(void) { I2C2->CR1 &= ~I2C_CR1_ACK; }

uint8_t Driver_I2C_SendAddr(uint8_t addr) {
    I2C2->DR = addr;
    uint16_t timeout = 0xffff;
    while ((I2C2->SR1 & I2C_SR1_ADDR) & timeout) {
        timeout--;
    }
    if (timeout) {
        I2C2->SR2;
    }
    return timeout ? OK : FALT;
}

uint8_t Driver_I2C2_HardWare_SendByte(uint8_t byte) {

    I2C2->DR = byte;
    uint16_t timeout = 0xffff;
    while ((I2C2->SR1 & I2C_SR1_TXE) & timeout) {
        timeout--;
    }
    timeout = 0xffff;
    /* BTF：字节发送结束位 */
    while (((I2C2->SR1 & I2C_SR1_BTF) == 0) && timeout) {
        timeout--;
    }

    return timeout ? OK : FALT;
}

uint8_t Driver_I2C2_HardWare_ReadByte(void) {

    uint8_t data;
    uint16_t timeout = 0xffff;
    data = I2C2->DR;
    while ((I2C2->SR1 & I2C_SR1_RXNE) & timeout) {
        timeout--;
    }

    return timeout ? data : FALT;
}
