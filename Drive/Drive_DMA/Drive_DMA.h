#ifndef DRIVE_DMA_H__
#define DRIVE_DMA_H__
#include "stm32f10x.h"
void Drive_DMA_Init();
void Drive_DMA_TransmitData(uint32_t srcAddr, uint32_t desAddr,
                            uint16_t dataLen);

#endif /* DRIVE_DMA_H__ */