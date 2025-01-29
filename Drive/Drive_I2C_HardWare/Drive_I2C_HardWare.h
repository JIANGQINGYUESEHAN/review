#ifndef DRIVE_I2C_HARDWARE_H__
#define DRIVE_I2C_HARDWARE_H__
#include "stm32f10x.h"
#define OK 1
#define FALT 0

void Driver_I2C2_HardWare_Init(void);

uint8_t Driver_I2C2_HardWare_Start(void);

void Driver_I2C2_HardWare_Stop(void);

void Driver_I2C2_HardWare_Ack(void);

void Driver_I2C2_HardWare_NAck(void);

uint8_t Driver_I2C2_HardWare_SendAddr(uint8_t addr);

uint8_t Driver_I2C2_HardWare_SendByte(uint8_t byte);

uint8_t Driver_I2C2_HardWare_ReadByte(void);

#endif /* DRIVE_I2C_HARDWARE_H__ */