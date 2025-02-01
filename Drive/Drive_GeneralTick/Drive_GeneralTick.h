#ifndef DRIVE_GENERALTICK_H__
#define DRIVE_GENERALTICK_H__

#include "stm32f10x.h"
void Drive_GeneralTick_Init(void);
void Drive_GeneralTick_Start(void);
void Drive_GeneralTick_Stop(void);
void Drive_GeneralTick_AdjustDutyCycle(uint8_t dutyCycle);
#endif /* DRIVE_GENERALTICK_H__ */