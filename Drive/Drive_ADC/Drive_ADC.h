#ifndef DRIVE_ADC_H__
#define DRIVE_ADC_H__
#include "stm32f10x.h"
void Drive_ADC1_Init(void);
void Drive_ADC1_StartConvert(void);
double Drive_ADC1_ReadV(void);

#endif /* DRIVE_ADC_H__ */