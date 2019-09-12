#ifndef _STR_H
#define _STR_H

#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "GUI.h"
#include "control.h"

extern GUI_CONST_STORAGE GUI_FONT GUI_FontB24;

extern const char *String[][2];
GUI_FONT Get_Font(uint8_t lang);
uint8_t Find_Str(const char *str);


#endif
