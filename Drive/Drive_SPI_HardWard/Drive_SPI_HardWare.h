#ifndef DRIVE_SPI_HARDWARE_H__
#define DRIVE_SPI_HARDWARE_H__

#include "Delay.h"
#include "stm32f10x.h"
#define CS_HIGH (GPIOC->ODR |= GPIO_ODR_ODR13)
#define CS_LOW (GPIOC->ODR &= ~GPIO_ODR_ODR13)

void Drive_SPI_HardWare_Init(void);
void Drive_SPI_HardWare_Start(void);
void Drive_SPI_HardWare_Stop(void);
uint8_t Drive_SPI_HardWare_SwapByte(uint8_t byte);

#endif /* DRIVE_SPI_HARDWARE_H__ */