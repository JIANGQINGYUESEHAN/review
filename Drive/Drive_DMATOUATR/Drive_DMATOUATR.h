#ifndef DRIVE_DMATOUATR_H__
#define DRIVE_DMATOUATR_H__
#include "stm32f10x.h"
void Drive_DMATOUART_Init(void);
void Drive_DMATOUART_TransmitData(uint32_t srcAddr, uint32_t desAddr,
                                  uint16_t dataLen);

#endif /* DRIVE_DMATOUATR_H__ */