#ifndef _POWER_H
#define _POWER_H

#include "stm32f4xx_hal.h"

void EN_Set(GPIO_PinState i);
void Reset(void);
void Jump_Step(uint8_t step);
uint8_t Get_Step(void);
void Up(void);
void Down(void);
	


#endif

