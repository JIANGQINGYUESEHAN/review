#ifndef DRIVE_USART_INTERRUPT_H__
#define DRIVE_USART_INTERRUPT_H__
#include "stdio.h"
#include "stm32f10x.h"
void Drive_USART_Interrupt_Init(void);

void Drive_USART_Interrupt_Sendchar(uint8_t ch);

uint8_t Drive_USART_Interrupt_ReceiveChar(void);

void Drive_USART_Interrupt_Sendstr(uint8_t *str, uint16_t len);

void Drive_USART_Interrupt_Receivestr(uint8_t buff[], uint8_t *len);

#endif /* DRIVE_USART_H__ */