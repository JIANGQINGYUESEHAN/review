#include "Drive_SPI.h"
void Drive_SPI_Init(void) {}
void Drive_SPI_Start(void) {}
void Drive_SPI_Stop(void) {}
uint8_t Driver_SPI_SwapByte(uint8_t byte) {
    uint8_t rbyte = 0x00;
    for (uint8_t i = 0; i < 8; i++) {
        if (byte & 0x80) {
            MOSI_HIGH;
        } else {
            MOSI_LOW;
        }
        byte <<= 1;
        rbyte <<= 1;
        if (MISO_READ) {
            rbyte |= 0x01;
        }
    }
}