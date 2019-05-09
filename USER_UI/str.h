#ifndef _STR_H
#define _STR_H

#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "GUI.h"

typedef struct 
{
	uint8_t language;
	uint8_t visible;
	uint8_t temperature;
	uint32_t manual_vol;
	uint32_t single_vol;
	uint32_t double_vol;
	uint32_t long_vol;
}SET_PARAM;

extern GUI_CONST_STORAGE GUI_FONT GUI_FontB24;
extern SET_PARAM Set;
extern const char *String[][2];
GUI_FONT Get_Font(uint8_t lang);
uint8_t Find_Str(const char *str);


#endif
