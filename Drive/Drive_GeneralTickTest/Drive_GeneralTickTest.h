#ifndef DRIVE_GENERALTICKTEST_H__
#define DRIVE_GENERALTICKTEST_H__

#include "stm32f10x.h"
void Drive_GeneralTickTestTest_Init(void);
void Drive_GeneralTickTestTest_Start(void);
void Drive_GeneralTickTestTest_Stop(void);

double Driver_GeneralTickTestTest_GetPWMCycle(void);

double Driver_GeneralTickTestTest_GetPWMFreq(void);

#endif /* DRIVE_GENERALTICKTEST_H__ */