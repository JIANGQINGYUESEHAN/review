#ifndef DRIVE_SPI_H__
#define DRIVE_SPI_H__
#include "Delay.h"
#include "stm32f10x.h"
#define CS_HIGH (GPIOC->ODR |= GPIO_ODR_ODR13)
#define CS_LOW (GPIOC->ODR &= ~GPIO_ODR_ODR13)
#define SCK_HIGH (GPIOA->ODR |= GPIO_ODR_ODR5)
#define SCK_LOW (GPIOA->ODR &= ~GPIO_ODR_ODR5)

#define MOSI_HIGH (GPIOA->ODR |= GPIO_ODR_ODR7)
#define MOSI_LOW (GPIOA->ODR &= ~GPIO_ODR_ODR7)

#define MISO_READ (GPIOA->IDR & GPIO_IDR_IDR6)

#define SPI_DELAY Delay_us(5)

void Drive_SPI_Init(void);
void Drive_SPI_Start(void);
void Drive_SPI_Stop(void);
uint8_t Driver_SPI_SwapByte(uint8_t byte);
#endif /* DRIVE_SPI_H__ */