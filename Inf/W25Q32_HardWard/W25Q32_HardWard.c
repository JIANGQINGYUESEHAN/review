#include "W25Q32.h"

void Inf_W25Q32_HardWare_Init(void) { Drive_SPI_HardWare_Init(); }

void Inf_W25Q32_HardWare_ReadId(uint8_t *mid, uint16_t *did) {
    Drive_SPI_HardWare_Start();
    Drive_SPI_HardWare_SwapByte(0x9f);
    *mid = Drive_SPI_HardWare_SwapByte(0x00);

    *did = 0;
    *did = Drive_SPI_HardWare_SwapByte(0x00) << 8;
    *did = Drive_SPI_HardWare_SwapByte(0x00);
    Drive_SPI_HardWare_Stop();
}
void Inf_W25Q32_HardWare_WriteEnable(void) {
    Drive_SPI_HardWare_Start();
    Drive_SPI_HardWare_SwapByte(0x06);

    Drive_SPI_HardWare_Stop();
}

void Inf_W25Q32_HardWare_WiteDisanable(void) {
    Drive_SPI_HardWare_Start();
    Drive_SPI_HardWare_SwapByte(0x04);

    Drive_SPI_HardWare_Stop();
}

void Inf_W25Q32_HardWare_WaiteNotBusy(void) {
    Drive_SPI_HardWare_Start();
    Drive_SPI_HardWare_SwapByte(0x05);
    while (Drive_SPI_HardWare_SwapByte(0x00) & 0x01)
        ;

    Drive_SPI_HardWare_Stop();
}

void Inf_W25Q32_HardWare_EraseSector(uint8_t block, uint8_t sector) {
    Inf_W25Q32_HardWare_WaiteNotBusy();

    Inf_W25Q32_HardWare_WriteEnable();
    Drive_SPI_HardWare_Start();

    uint32_t addr = (block << 16) + (sector << 12);
    Drive_SPI_HardWare_SwapByte(0x20);
    Drive_SPI_HardWare_SwapByte(addr >> 16 & 0xff);
    Drive_SPI_HardWare_SwapByte(addr >> 8 & 0xff);
    Drive_SPI_HardWare_SwapByte(addr >> 0 & 0xff);
    Drive_SPI_HardWare_Stop();
}
void Inf_W25Q32_HardWare_WritePage(uint8_t block, uint8_t sector, uint8_t page,
                                   uint8_t *data, uint16_t len) {
    Inf_W25Q32_HardWare_WaiteNotBusy();

    Inf_W25Q32_HardWare_WriteEnable();
    Drive_SPI_HardWare_Start();

    uint32_t addr = (block << 16) + (sector << 12) + (page << 8);
    Drive_SPI_HardWare_SwapByte(0x02);
    Drive_SPI_HardWare_SwapByte(addr >> 16 & 0xff);
    Drive_SPI_HardWare_SwapByte(addr >> 8 & 0xff);
    Drive_SPI_HardWare_SwapByte(addr >> 0 & 0xff);
    for (uint16_t i = 0; i < len; i++) {
        Drive_SPI_HardWare_SwapByte(data[i]);
    }

    Drive_SPI_HardWare_Stop();
}

void Inf_W25Q32_HardWare_Read(uint8_t block, uint8_t sector, uint8_t page,
                              uint8_t *data, uint16_t len) {

    Inf_W25Q32_HardWare_WaiteNotBusy();

    Inf_W25Q32_HardWare_WriteEnable();
    Drive_SPI_HardWare_Start();

    uint32_t addr = (block << 16) + (sector << 12) + (page << 8);
    Drive_SPI_HardWare_SwapByte(0x03);
    Drive_SPI_HardWare_SwapByte(addr >> 16 & 0xff);
    Drive_SPI_HardWare_SwapByte(addr >> 8 & 0xff);
    Drive_SPI_HardWare_SwapByte(addr >> 0 & 0xff);
    for (uint16_t i = 0; i < len; i++) {
        data[i] = Drive_SPI_HardWare_SwapByte(0x00);
    }

    Drive_SPI_HardWare_Stop();
}
