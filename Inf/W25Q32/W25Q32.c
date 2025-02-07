#include "W25Q32.h"

void Inf_W25Q32_Init(void) { Drive_SPI_Init(); }

void Inf_W25Q32_ReadId(uint8_t *mid, uint16_t *did) {
    Drive_SPI_Start();
    Drive_SPI_SwapByte(0x9f);
    *mid = Drive_SPI_SwapByte(0x00);

    *did = 0;
    *did = Drive_SPI_SwapByte(0x00) << 8;
    *did = Drive_SPI_SwapByte(0x00);
    Drive_SPI_Stop();
}
void Inf_W25q32_WriteEnable(void) {
    Drive_SPI_Start();
    Drive_SPI_SwapByte(0x06);

    Drive_SPI_Stop();
}

void Inf_W25q32_WiteDisanable(void) {
    Drive_SPI_Start();
    Drive_SPI_SwapByte(0x04);

    Drive_SPI_Stop();
}

void Inf_W25Q32_WaiteNotBusy(void) {
    Drive_SPI_Start();
    Drive_SPI_SwapByte(0x05);
    while (Drive_SPI_SwapByte(0x00) & 0x01)
        ;

    Drive_SPI_Stop();
}

void Inf_W25Q32_EraseSector(uint8_t block, uint8_t sector) {
    Inf_W25Q32_WaiteNotBusy();

    Inf_W25q32_WriteEnable();
    Drive_SPI_Start();

    uint32_t addr = (block << 16) + (sector << 12);
    Drive_SPI_SwapByte(0x20);
    Drive_SPI_SwapByte(addr >> 16 & 0xff);
    Drive_SPI_SwapByte(addr >> 8 & 0xff);
    Drive_SPI_SwapByte(addr >> 0 & 0xff);
    Drive_SPI_Stop();
}
void Inf_W25Q32_WritePage(uint8_t block, uint8_t sector, uint8_t page,
                          uint8_t *data, uint16_t len) {
    Inf_W25Q32_WaiteNotBusy();

    Inf_W25q32_WriteEnable();
    Drive_SPI_Start();

    uint32_t addr = (block << 16) + (sector << 12) + (page << 8);
    Drive_SPI_SwapByte(0x02);
    Drive_SPI_SwapByte(addr >> 16 & 0xff);
    Drive_SPI_SwapByte(addr >> 8 & 0xff);
    Drive_SPI_SwapByte(addr >> 0 & 0xff);
    for (uint16_t i = 0; i < len; i++) {
        Drive_SPI_SwapByte(data[i]);
    }

    Drive_SPI_Stop();
}

void Inf_W25Q32_Read(uint8_t block, uint8_t sector, uint8_t page, uint8_t *data,
                     uint16_t len) {

    Inf_W25Q32_WaiteNotBusy();

    Inf_W25q32_WriteEnable();
    Drive_SPI_Start();

    uint32_t addr = (block << 16) + (sector << 12) + (page << 8);
    Drive_SPI_SwapByte(0x03);
    Drive_SPI_SwapByte(addr >> 16 & 0xff);
    Drive_SPI_SwapByte(addr >> 8 & 0xff);
    Drive_SPI_SwapByte(addr >> 0 & 0xff);
    for (uint16_t i = 0; i < len; i++) {
        data[i] = Drive_SPI_SwapByte(0x00);
    }

    Drive_SPI_Stop();
}

void Inf_W25Q32_RadromPage(uint32_t addr, uint8_t *data, uint16_t len) {
    Inf_W25Q32_WaiteNotBusy();

    Inf_W25q32_WriteEnable();
    Drive_SPI_Start();

    Drive_SPI_SwapByte(0x02);
    Drive_SPI_SwapByte(addr >> 16 & 0xff);
    Drive_SPI_SwapByte(addr >> 8 & 0xff);
    Drive_SPI_SwapByte(addr >> 0 & 0xff);
    for (uint16_t i = 0; i < len; i++) {
        Drive_SPI_SwapByte(data[i]);
    }

    Drive_SPI_Stop();
}
void Inf_W25Q32_RadromRead(uint32_t addr, uint8_t *data, uint16_t len) {

    Inf_W25Q32_WaiteNotBusy();

    Inf_W25q32_WriteEnable();
    Drive_SPI_Start();

    Drive_SPI_SwapByte(0x03);
    Drive_SPI_SwapByte(addr >> 16 & 0xff);
    Drive_SPI_SwapByte(addr >> 8 & 0xff);
    Drive_SPI_SwapByte(addr >> 0 & 0xff);
    for (uint16_t i = 0; i < len; i++) {
        data[i] = Drive_SPI_SwapByte(0x00);
    }

    Drive_SPI_Stop();
}