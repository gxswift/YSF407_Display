#ifndef _COMMAND_H
#define _COMMAND_H

#include "stm32f4xx_hal.h"

typedef struct
{
	uint8_t Read;
	uint8_t Write;
	uint8_t Lenth;
	uint8_t Data[256];
}RING;

typedef struct
{
	uint8_t head;
	uint8_t add;
	uint8_t len;
	uint8_t cmd;
	uint8_t *data;
	uint8_t crc;
}CMD;

typedef struct
{
	uint8_t func;	
	uint32_t color;

	uint8_t key;
	
	uint8_t verl;
	uint8_t verm;
	uint8_t verh;
	
	uint8_t connect;
}DROP;

extern void Send_Data(uint8_t mode);
void Uart3_IT();


#endif

