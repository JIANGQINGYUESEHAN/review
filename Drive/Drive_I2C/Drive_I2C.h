#ifndef DRIVE_I2C_H__
#define DRIVE_I2C_H__
#include "Delay.h"
#include "stm32f10x.h"

#define ACK 1
#define NACK 0
#define SCL_HIGH (GPIOB->ODR |= GPIO_ODR_ODR10)
#define SCL_LOW (GPIOB->ODR &= ~GPIO_ODR_ODR10)

#define SDA_HIGH (GPIOB->ODR |= GPIO_ODR_ODR11)
#define SDA_LOW (GPIOB->ODR &= ~GPIO_ODR_ODR11)

#define READ_SDA (GPIOB->IDR & GPIO_IDR_IDR11)

#define I2C_Delay Delay_ms(5)
/* ½ÇÉ« Îª stm32 */
void Driver_I2C2_Init(void);
void Driver_I2C2_Init(void);
void Driver_I2C2_Start(void);
void Driver_I2C2_Stop(void);
void Driver_I2C2_Ack(void);
void Driver_I2C2_NAck(void);
uint8_t Driver_I2C2_WaitAck(void);
void Driver_I2C_SendByte(uint8_t byte);
uint8_t Driver_I2C_ReadByte(void);

#endif /* DRIVE_I2C_H__ */