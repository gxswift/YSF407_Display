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
	uint32_t vol1;//单击
	uint32_t vol2;//双击
	uint32_t vol3;//长按
	uint32_t volhand;//手动
	uint32_t out;//出水
	uint32_t temperature;//温度
	uint32_t language;//语言
	uint32_t visable;//可见
	uint32_t init;//首次设置
	
	uint32_t lighttime;//屏幕时间 min
	uint32_t circletime;//循环时间 s
	uint32_t circleinterval;//循环间隔 min
	uint32_t outspeed;//出水等级
	uint32_t circlespeed;//循环等级

}SETTING;

typedef struct
{
	uint32_t wait;
	uint32_t circle;
	uint32_t out;
	uint32_t tick;
}TIME;


typedef struct
{
	//运行状态
	uint8_t inflag;
	uint8_t outflag;
	uint8_t heaterflag;
	uint8_t circleflag;	
	uint8_t handflag;
	//水位标志
	uint8_t lowflag;
	uint8_t highflag;
	uint8_t warnflag;
	
	uint8_t temperature;//温度
	uint8_t hwinflag;//主窗口标志
	uint8_t flash;//闪
	uint8_t connect;//连接
	uint32_t totalvolume;//总流量
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



