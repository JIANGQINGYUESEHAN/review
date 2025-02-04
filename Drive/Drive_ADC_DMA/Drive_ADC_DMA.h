#ifndef DRIVE_ADC_DMA_H__
#define DRIVE_ADC_DMA_H__

#include "stm32f10x.h"
void Driver_ADC1_Init(void);

void Driver_ADC1_DMA_Init(void);

void Driver_ADC1_DMA_Start(uint32_t desAddr, uint8_t len);

#endif /* DRIVE_ADC_DMA_H__ */