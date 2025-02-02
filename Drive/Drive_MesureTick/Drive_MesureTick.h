#ifndef DRIVE_MESURETICK_H__
#define DRIVE_MESURETICK_H__
#include "stm32f10x.h"
void Drive_MesureTick_Init();
void Drive_MesureTick_Start();
void Drive_MesureTick_Stop();
double Drive_MesureTick_GetPWMCycle();
double Drive_MesureTick_GetPWMFreq();
double Drive_MesureTick_GetDutyCycle();
#endif /* DRIVE_MESURETICK_H__ */