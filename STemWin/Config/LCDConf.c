/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.30 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  ARM LIMITED whose registered office
is situated at  110 Fulbourn Road,  Cambridge CB1 9NJ,  England solely
for  the  purposes  of  creating  libraries  for  ARM7, ARM9, Cortex-M
series,  and   Cortex-R4   processor-based  devices,  sublicensed  and
distributed as part of the  MDK-ARM  Professional  under the terms and
conditions  of  the   End  User  License  supplied  with  the  MDK-ARM
Professional. 
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
Licensing information

Licensor:                 SEGGER Software GmbH
Licensed to:              ARM Ltd
Licensed SEGGER software: emWin
License number:           GUI-00181
License model:            LES-SLA-20007, Agreement, effective since October 1st 2011 
Licensed product:         MDK-ARM Professional
Licensed platform:        ARM7/9, Cortex-M/R4
Licensed number of seats: -
----------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/
#include "GUI.h"
#include "GUIDRV_FlexColor.h"
#include "lcd/bsp_lcd.h"

/*********************************************************************
*
*       Layer configuration
*
**********************************************************************
*/
//
// 显示尺寸
//
#define XSIZE_PHYS            LCD_DEFAULT_WIDTH    //【修改】
#define YSIZE_PHYS            LCD_DEFAULT_HEIGTH   //【修改】
/*
#define TOUCH_AD_TOP 	 			  226    //YPhys0
#define TOUCH_AD_BOTTOM  			3854   //YPhys1
#define TOUCH_AD_LEFT 	 			3780   //XPhys0
#define TOUCH_AD_RIGHT 	 			250    //XPhys1
*/

#define TOUCH_AD_TOP 	 			  200    //YPhys0
#define TOUCH_AD_BOTTOM  			3900   //YPhys1
#define TOUCH_AD_LEFT 	 			3900   //XPhys0
#define TOUCH_AD_RIGHT 	 			200    //XPhys1



//
// 颜色转换
//
#define COLOR_CONVERSION GUICC_565

//
// 显示驱动
//
#define DISPLAY_DRIVER GUIDRV_FLEXCOLOR

//
// 方向
//
//#define DISPLAY_ORIENTATION (0)           //【修改】
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_Y)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_MIRROR_Y)
//#define DISPLAY_ORIENTATION (GUI_SWAP_XY)
#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_SWAP_XY)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_Y | GUI_SWAP_XY)//用
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_MIRROR_Y | GUI_SWAP_XY)

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif
#ifndef   DISPLAY_ORIENTATION
  #define DISPLAY_ORIENTATION 0
#endif

/*********************************************************************
*
*       Local code
*
**********************************************************************
*/
/********************************************************************
*
*       LcdWriteReg
*
* Function description:
* 设置显示寄存器
*/
static void LcdWriteReg(U16 Data) 
{
  // ... TBD by user
	LCD_WRITE_CMD(Data);	//【修改】
}

/********************************************************************
*
*       LcdWriteData
*
* Function description:
* 写入一个数据到显示寄存器
*/
static void LcdWriteData(U16 Data) 
{
  // ... TBD by user
	LCD_WRITE_DATA(Data);	//【修改】
}

/********************************************************************
*
*       LcdWriteDataMultiple
*
* Function description:
* 写入多个数据到显示寄存器
*/
static void LcdWriteDataMultiple(U16 * pData, int NumItems) 
{
  while (NumItems--) {
    // ... TBD by user
	 LCD_WRITE_DATA(*pData++); 	//【修改】 
  }
}

/********************************************************************
*
*       LcdReadDataMultiple
*
* Function description:
*   从显示寄存器读取多个数据
*/
static void LcdReadDataMultiple(U16 * pData, int NumItems) 
{
  while (NumItems--) {
    // ... TBD by user
	  *pData++ = LCD_READ_DATA();	//【修改】
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Purpose:
* 初始化配置液晶驱动
*
*/
void LCD_X_Config(void) {
  GUI_DEVICE * pDevice;
  GUI_PORT_API PortAPI = {0};
  CONFIG_FLEXCOLOR Config = {0};

  //
  // 设置显示驱动器和第一层颜色转换
  //
  pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // 显示驱动配置
  //
  if (DISPLAY_ORIENTATION & GUI_SWAP_XY) {
    LCD_SetSizeEx (0, YSIZE_PHYS,   XSIZE_PHYS);
    LCD_SetVSizeEx(0, VYSIZE_PHYS,  VXSIZE_PHYS);
  } else {
    LCD_SetSizeEx (0, XSIZE_PHYS,   YSIZE_PHYS);
    LCD_SetVSizeEx(0, VXSIZE_PHYS,  VYSIZE_PHYS);
  }
  //
  // 方向设置
  //
  Config.FirstCOM = 0;									      //【修改】
  Config.FirstSEG = 0; 									      //【修改】
  Config.Orientation = DISPLAY_ORIENTATION;		//【修改】
  Config.NumDummyReads = 2;								    //【修改】 
  GUIDRV_FlexColor_Config(pDevice, &Config);
  //
  // 将显示驱动用的函数传递给PortAPI，再通过函数GUIDRV_FlexColor_SetFunc进行设置
  // ILI驱动在GUIDRV_FLEXCOLOR_F66709中，接口形式为GUIDRV_FLEXCOLOR_M16C0B16
  PortAPI.pfWrite16_A0  = LcdWriteReg;
  PortAPI.pfWrite16_A1  = LcdWriteData;
  PortAPI.pfWriteM16_A1 = LcdWriteDataMultiple;
  PortAPI.pfReadM16_A1  = LcdReadDataMultiple;
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66709, GUIDRV_FLEXCOLOR_M16C0B16);
  
	  //设置触摸原点 //【修改】
  GUI_TOUCH_SetOrientation((GUI_MIRROR_X * LCD_GetMirrorXEx(0)) |
              (GUI_MIRROR_Y * LCD_GetMirrorYEx(0)) |
              (GUI_SWAP_XY  * LCD_GetSwapXYEx (0)));
  //电阻屏需要设置触摸校准值 //【修改】
//  GUI_TOUCH_Calibrate(GUI_COORD_X, 0, XSIZE_PHYS-1, TOUCH_AD_RIGHT ,TOUCH_AD_LEFT );
//  GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, YSIZE_PHYS-1,TOUCH_AD_BOTTOM ,TOUCH_AD_TOP );

//	GUI_TOUCH_SetOrientation(GUI_MIRROR_Y | GUI_SWAP_XY);
	
  GUI_TOUCH_Calibrate(GUI_COORD_X, 0, XSIZE_PHYS-1 ,TOUCH_AD_LEFT, TOUCH_AD_RIGHT );
  GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, YSIZE_PHYS-1 ,TOUCH_AD_TOP,TOUCH_AD_BOTTOM );
	
	/*
	GUI_SetOrientation(GUI_MIRROR_X | GUI_SWAP_XY);
	*/
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  GUI_USE_PARA(LayerIndex);
  GUI_USE_PARA(Cmd);
  GUI_USE_PARA(pData);
  return 0;
}

/*************************** End of file ****************************/
