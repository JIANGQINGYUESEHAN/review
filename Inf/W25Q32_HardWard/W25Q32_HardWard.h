#ifndef W25Q32_HARDWARD_H__
#define W25Q32_HARDWARD_H__

#include "Drive_SPI_HardWare.h"
#include "stm32f10x.h"
void Inf_W25Q32_HardWare_Init(void);

void Inf_W25Q32_HardWare_ReadId(uint8_t *mid, uint16_t *did);

void Inf_W25Q32_HardWare_WriteEnable(void);

void Inf_W25Q32_HardWare_WaiteNotBusy(void);

void Inf_W25Q32_HardWare_EraseSector(uint8_t block, uint8_t sector);

void Inf_W25Q32_HardWare_WritePage(uint8_t block, uint8_t sector, uint8_t page,
                                   uint8_t *data, uint16_t len);

void Inf_W25Q32_HardWare_Read(uint8_t block, uint8_t sector, uint8_t page,
                              uint8_t *data, uint16_t len);

#endif /* W25Q32_HARDWARD_H__ */