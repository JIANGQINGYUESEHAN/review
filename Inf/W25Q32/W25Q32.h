#ifndef W25Q32_H__
#define W25Q32_H__
#include "Drive_SPI.h"
#include "stm32f10x.h"
void Inf_W25Q32_Init(void);

void Inf_W25Q32_ReadId(uint8_t *mid, uint16_t *did);

void Inf_W25q32_WiteEnable(void);

void Inf_W25q32_WriteEnable(void);

void Inf_W25Q32_WaiteNotBusy(void);

void Inf_W25Q32_EraseSector(uint8_t block, uint8_t sector);

void Inf_W25Q32_WritePage(uint8_t block, uint8_t sector, uint8_t page,
                          uint8_t *data, uint16_t len);

void Inf_W25Q32_Read(uint8_t block, uint8_t sector, uint8_t page, uint8_t *data,
                     uint16_t len);
void Inf_W25Q32_RadromPage(uint32_t addr, uint8_t *data, uint16_t len);
void Inf_W25Q32_RadromRead(uint32_t addr, uint8_t *data, uint16_t len);
#endif /* W25Q32_H__ */