#ifndef DRIVE_USART_H__
#define DRIVE_USART_H__
#include "stm32f10x.h"
void Drive_USART_Init(void);
void Drive_USART_Sendchar(uint8_t ch);
void Drive_USART_Sendstr(uint8_t *str, uint16_t len);

uint8_t Driver_USART1_ReceiveChar(void);

void Driver_USART1_ReceiveString(uint8_t buff[], uint8_t *len);
#endif /* DRIVE_USART_H__ */