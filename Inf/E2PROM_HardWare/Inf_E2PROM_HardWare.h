#ifndef INF_E2PROM_HARDWARE_H__
#define INF_E2PROM_HARDWARE_H__
#include "Drive_I2C_HardWare.h"
#include "stm32f10x.h"
#define W_AD 0xA0
#define R_AD 0xA1
void Inf_W24C02_HardWare_Init(void);
void Inf_W24C02_HardWare_WriteByte(uint8_t innerAddr, uint8_t byte);

uint8_t Inf_W24C02_HardWare_ReadByte(uint8_t innerAddr);

void Inf_W24C02_HardWare_WriteBytes(uint8_t innerAddr, uint8_t *bytes,
                                    uint8_t len);

void Inf_W24C02_HardWare_ReadBytes(uint8_t innerAddr, uint8_t *bytes,
                                   uint8_t len);

#endif /* INF_E2PROM_HARDWARE_H__ */