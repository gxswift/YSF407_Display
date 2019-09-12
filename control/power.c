#include "power.h"

//X9C104
#define X9C104_RESISTANCE 100000 //X9C104 = 100kOhm

#define X9_STEP		100

#define HIGH	GPIO_PIN_SET
#define LOW		GPIO_PIN_RESET
//CS INC UD EN
static uint8_t R_Step;
/*
VCC3.3
GND
UD
INC
CS
EN
*/

#define UD_GPIO				GPIOH
#define UD_GPIO_PIN		GPIO_PIN_10

#define INC_GPIO			GPIOH
#define INC_GPIO_PIN	GPIO_PIN_11

#define CS_GPIO				GPIOH
#define CS_GPIO_PIN		GPIO_PIN_12

#define EN_GPIO				GPIOA
#define EN_GPIO_PIN		GPIO_PIN_6

static void delay_us(uint16_t time)
{
	uint16_t i;
	while(time--)
	{
		i = 100;
		while(i--);
	}
}

void CS_Set(GPIO_PinState i)
{
	HAL_GPIO_WritePin(CS_GPIO,CS_GPIO_PIN,i);
}
void UD_Set(GPIO_PinState i)
{
	HAL_GPIO_WritePin(UD_GPIO,UD_GPIO_PIN,i);
}
void INC_Set(GPIO_PinState i)
{
	HAL_GPIO_WritePin(INC_GPIO,INC_GPIO_PIN,i);
}
void EN_Set(GPIO_PinState i)
{
	HAL_GPIO_WritePin(EN_GPIO,EN_GPIO_PIN,i);
}

void Down(void)
{
	INC_Set(HIGH);
	CS_Set(LOW);
	UD_Set(LOW);
	delay_us(10);
	INC_Set(LOW);

	if (R_Step > 0)
	{
		R_Step--;
	}
}


void Up(void)
{
	INC_Set(HIGH);
	CS_Set(LOW);
	UD_Set(HIGH);
	delay_us(10);
	INC_Set(LOW);
	if (R_Step < X9_STEP)
	{
		R_Step++;
	}
}

void Reset(void)
{
	uint8_t i;
	CS_Set(LOW);
	UD_Set(LOW);
	INC_Set(HIGH);
	for (i = 0;i<X9_STEP;i++)
	{
		Down();
	}
	CS_Set(HIGH);
	UD_Set(HIGH);
	R_Step = 0;
}

void Jump_Step(uint8_t step)
{
	if (step > X9_STEP)
		return;
	while(R_Step != step)
	{
		if (R_Step > step)
		{
			Down();
		}
		else
		{
			Up();
		}
	}
	CS_Set(HIGH);
}

uint8_t Get_Step(void)
{
	return R_Step;
}


void Store(void)
{
	INC_Set(HIGH);
	CS_Set(HIGH);
	HAL_Delay(100);
	CS_Set(LOW);
}

/*

1~9  	22.9
10	21.8
11	19.9
12	18.3
13	17
14	15.8
15	14.8
16	13.9
17	13.2
18	12.5
19	11.9
20	11.3
21	10.8
22	10.3
23	9.9
24	9.5
25	9.2
26	8.9
27	8.6
28	8.3
29	8.1
30	7.8
31	7.6
32	7.4
33	7.3
34	7.1
35	6.9
36	6.8
37	6.6
39	6.5
40	6.3
41	6.2
42	6.1
43	5.9
44	5.8

*/


