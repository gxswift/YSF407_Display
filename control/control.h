#ifndef _CONTROL_H
#define _CONTROL_H

#include "stm32f4xx_hal.h"

typedef struct
{
  uint16_t sta:2;
  uint16_t cnt:7;
  uint16_t set:7;
}SIGNAL;

typedef struct 
{
	uint32_t vol1;
	uint32_t vol2;
	uint32_t vol3;
	uint32_t volhand;
	uint32_t out;
	uint32_t temperature;
	uint32_t language;
	uint32_t visable;
	uint32_t init;
}SETTING;

typedef struct
{
	uint32_t wait;
	uint32_t circle;
	uint32_t out;
}TIME;


typedef struct
{
	uint8_t inflag;
	uint8_t outflag;
	uint8_t heaterflag;
	uint8_t circleflag;	
	
	uint8_t lowflag;
	uint8_t highflag;
	uint8_t warnflag;
	
	uint8_t temperature;
	uint8_t hwinflag;
}STATE;

#define LOW		0
#define HIGH	1
#define WARN	2


#define ON	1
#define OFF	0


extern SETTING 	Set;
extern TIME 			Time;
extern STATE			State;

void Setting_Save();
void Setting_Init();
void Out_Start();
void Out_Stop();
void TimerTask();
void Func(void);
#endif



