#include "Inf_E2PROM_HardWare.h"
#include "Delay.h"
/* վ��stm32�ĽǶ� */
void Inf_W24C02_HardWare_Init(void) { Driver_I2C2_HardWare_Init(); }

void Inf_W24C02_HardWare_WriteByte(uint8_t innerAddr, uint8_t byte) {
    Driver_I2C2_HardWare_Start();
    /* �豸��ַ */
    Driver_I2C2_HardWare_SendByte(W_AD);

    /* ���豸���Ϳ�ʼд�ĵ�ַ */
    Driver_I2C2_HardWare_SendByte(innerAddr);
    /* ���豸�ȴ����մ��豸����Ӧ */

    /* д���� */
    Driver_I2C2_HardWare_SendByte(byte);

    Driver_I2C2_HardWare_Stop();
    Delay_ms(5);
}

uint8_t Inf_W24C02_HardWare_ReadByte(uint8_t innerAddr) {
    Driver_I2C2_HardWare_Start();

    Driver_I2C2_HardWare_SendByte(W_AD);

    Driver_I2C2_HardWare_SendByte(innerAddr);

    Driver_I2C2_HardWare_Start();
    Driver_I2C2_HardWare_SendByte(R_AD);

    uint8_t data = Driver_I2C2_HardWare_ReadByte();
    Driver_I2C2_HardWare_NAck();
    Driver_I2C2_HardWare_Stop();

    return data;
}

void Inf_W24C02_HardWare_WriteBytes(uint8_t innerAddr, uint8_t *bytes,
                                    uint8_t len) {
    Driver_I2C2_HardWare_Start();
    Driver_I2C2_HardWare_SendByte(W_AD);

    Driver_I2C2_HardWare_SendByte(innerAddr);

    for (uint8_t i = 0; i < len; i++) {
        Driver_I2C2_HardWare_SendByte(bytes[i]);
    }
    Driver_I2C2_HardWare_Stop();
    Delay_ms(5);
}

void Inf_W24C02_HardWare_ReadBytes(uint8_t innerAddr, uint8_t *bytes,
                                   uint8_t len) {

    Driver_I2C2_HardWare_Start();

    Driver_I2C2_HardWare_SendByte(W_AD);

    Driver_I2C2_HardWare_SendByte(innerAddr);

    Driver_I2C2_HardWare_Start();
    Driver_I2C2_HardWare_SendByte(R_AD);

    for (uint8_t i = 0; i < len; i++) {
        bytes[i] = Driver_I2C2_HardWare_ReadByte();
        if (i == len - 1) {

            Driver_I2C2_HardWare_NAck();
        } else {
            Driver_I2C2_HardWare_Ack();
        }
    }

    Driver_I2C2_HardWare_NAck();
    Driver_I2C2_HardWare_Stop();
}
