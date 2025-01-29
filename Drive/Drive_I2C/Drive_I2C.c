#include "Drive_I2C.h"

void Driver_I2C2_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    /* 开漏复用输出  */
    GPIOB->CRH |= GPIO_CRH_MODE10;
    GPIOB->CRH &= ~GPIO_CRH_CNF10_1;
    GPIOB->CRH |= GPIO_CRH_CNF10_0;
    // P11
    GPIOB->CRH |= GPIO_CRH_MODE11;
    GPIOB->CRH &= ~GPIO_CRH_CNF11_1;
    GPIOB->CRH |= GPIO_CRH_CNF11_0;
}

void Driver_I2C2_Start(void) {
    SCL_HIGH;
    SDA_HIGH;
    I2C_Delay;
    SDA_LOW;
    I2C_Delay;
}

void Driver_I2C2_Stop(void) {
    SCL_HIGH;
    SDA_LOW;
    I2C_Delay;
    SDA_HIGH;
    I2C_Delay;
}

void Driver_I2C2_Ack(void) {
    SCL_LOW;
    SDA_HIGH;
    I2C_Delay;
    /* 变化 */
    SDA_LOW;
    I2C_Delay;

    SCL_HIGH;
    SDA_LOW;
    I2C_Delay;

    SCL_LOW;
    SDA_HIGH;
    I2C_Delay;
}

void Driver_I2C2_NAck(void) {
    SCL_LOW;
    SDA_HIGH;
    I2C_Delay;

    SCL_HIGH;
    I2C_Delay;
    SCL_LOW;
    I2C_Delay;
}

uint8_t Driver_I2C2_WaitAck(void) {
    SDA_HIGH;
    SCL_LOW;
    I2C_Delay;
    SCL_HIGH;
    I2C_Delay;

    uint16_t ack = READ_SDA;

    SCL_LOW;
    I2C_Delay;

    return ack ? ACK : NACK;
}

void Driver_I2C_SendByte(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++) {
        SDA_LOW;
        SCL_LOW;
        I2C_Delay;
        if (byte & 0x80) {
            SDA_HIGH;
        } else {
            SDA_LOW;
        }

        SCL_HIGH;
        I2C_Delay;
        SCL_LOW;
        I2C_Delay;

        byte <<= 1;
    }
}

uint8_t Driver_I2C_ReadByte(void) {
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++) {
        SCL_LOW;
        I2C_Delay;
        SCL_HIGH;
        I2C_Delay;
        data <<= 1;
        if (READ_SDA) {
            data |= 0x01;
        }
        SCL_LOW;
        I2C_Delay;
    }
    return data;
}
