#include "Inf_E2PROM.h"
#include "Delay.h"
/* վ��stm32�ĽǶ� */
void Inf_W24C02_Init(void) { Driver_I2C2_Init(); }

void Inf_W24C02_WriteByte(uint8_t innerAddr, uint8_t byte) {
    Driver_I2C2_Start();
    /* �豸��ַ */
    Driver_I2C_SendByte(W_AD);
    Driver_I2C2_WaitAck();
    /* ���豸���Ϳ�ʼд�ĵ�ַ */
    Driver_I2C_SendByte(innerAddr);
    /* ���豸�ȴ����մ��豸����Ӧ */
    Driver_I2C2_WaitAck();
    /* д���� */
    Driver_I2C_SendByte(byte);
    Driver_I2C2_WaitAck();
    Driver_I2C2_Stop();
    Delay_ms(5);
}

uint8_t Inf_W24C02_ReadByte(uint8_t innerAddr) {
    Driver_I2C2_Start();

    Driver_I2C_SendByte(W_AD);
    Driver_I2C2_WaitAck();
    Driver_I2C_SendByte(innerAddr);
    Driver_I2C2_WaitAck();

    Driver_I2C2_Start();
    Driver_I2C_SendByte(R_AD);
    Driver_I2C2_WaitAck();
    uint8_t data = Driver_I2C_ReadByte();
    Driver_I2C2_NAck();
    Driver_I2C2_Stop();

    return data;
}

void Inf_W24C02_WriteBytes(uint8_t innerAddr, uint8_t *bytes, uint8_t len) {
    Driver_I2C2_Start();
    Driver_I2C_SendByte(W_AD);
    Driver_I2C2_WaitAck();

    Driver_I2C_SendByte(innerAddr);
    Driver_I2C2_WaitAck();

    for (uint8_t i = 0; i < len; i++) {
        Driver_I2C_SendByte(bytes[i]);
        Driver_I2C2_WaitAck();
    }
    Driver_I2C2_Stop();
    Delay_ms(5);
}

void Inf_W24C02_ReadBytes(uint8_t innerAddr, uint8_t *bytes, uint8_t len) {

    Driver_I2C2_Start();

    Driver_I2C_SendByte(W_AD);
    Driver_I2C2_WaitAck();
    Driver_I2C_SendByte(innerAddr);
    Driver_I2C2_WaitAck();

    Driver_I2C2_Start();
    Driver_I2C_SendByte(R_AD);
    Driver_I2C2_WaitAck();
    for (uint8_t i = 0; i < len; i++) {
        bytes[i] = Driver_I2C_ReadByte();
        if (i == len - 1) {

            Driver_I2C2_NAck();
        } else {
            Driver_I2C2_Ack();
        }
    }

    Driver_I2C2_NAck();
    Driver_I2C2_Stop();
}
