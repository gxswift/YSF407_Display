#ifndef __BSP_XPT2046_H__
#define	__BSP_XPT2046_H__

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* 类型定义 ------------------------------------------------------------------*/
#pragma pack(4)     // 4字节对齐
typedef struct 
{	
  int32_t cal_flag;
  int32_t lcd_x[5];
	int32_t lcd_y[5];
  int32_t touch_x[5];
  int32_t touch_y[5];
	int32_t adjust[7];
}XPT2046_Calibration;
#pragma pack()

/* 宏定义 --------------------------------------------------------------------*/
/******************************* XPT2046 触摸屏中断引脚定义 ***************************/
#define XPT2046_EXTI_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOH_CLK_ENABLE() 
#define XPT2046_EXTI_PORT                            GPIOH
#define XPT2046_EXTI_PIN                             GPIO_PIN_4
#define XPT2046_EXTI_ActiveLevel                     0
#define XPT2046_EXTI_Read()                          HAL_GPIO_ReadPin(XPT2046_EXTI_PORT,XPT2046_EXTI_PIN )

/******************************* XPT2046 触摸屏模拟SPI引脚定义 ***************************/
#define XPT2046_SPI_GPIO_CLK_ENABLE()                __HAL_RCC_GPIOI_CLK_ENABLE()
#define XPT2046_SPI_CS_PORT		                       GPIOI
#define XPT2046_SPI_CS_PIN		                       GPIO_PIN_8

#define XPT2046_SPI_PORT		                         GPIOH
#define	XPT2046_SPI_CLK_PIN	                         GPIO_PIN_2
#define	XPT2046_SPI_MOSI_PIN	                       GPIO_PIN_3
#define	XPT2046_SPI_MISO_PIN	                       GPIO_PIN_5

#define XPT2046_CS_HIGT()                            HAL_GPIO_WritePin(XPT2046_SPI_CS_PORT,XPT2046_SPI_CS_PIN,GPIO_PIN_SET)
#define XPT2046_CS_LOW()                             HAL_GPIO_WritePin(XPT2046_SPI_CS_PORT,XPT2046_SPI_CS_PIN,GPIO_PIN_RESET)

#define XPT2046_CLK_HIGH()                           HAL_GPIO_WritePin(XPT2046_SPI_PORT,XPT2046_SPI_CLK_PIN,GPIO_PIN_SET)
#define XPT2046_CLK_LOW()                            HAL_GPIO_WritePin(XPT2046_SPI_PORT,XPT2046_SPI_CLK_PIN,GPIO_PIN_RESET)

#define XPT2046_MOSI_HIGH()                          HAL_GPIO_WritePin(XPT2046_SPI_PORT,XPT2046_SPI_MOSI_PIN,GPIO_PIN_SET)
#define XPT2046_MOSI_LOW()                           HAL_GPIO_WritePin(XPT2046_SPI_PORT,XPT2046_SPI_MOSI_PIN,GPIO_PIN_RESET)

#define XPT2046_MISO_READ()                          HAL_GPIO_ReadPin(XPT2046_SPI_PORT,XPT2046_SPI_MISO_PIN)

/******************************* XPT2046 触摸屏参数定义 ***************************/
#define	XPT2046_CHANNEL_X 	                          0x90 	          //驱动YN YP，测量X+	
#define	XPT2046_CHANNEL_Y 	                          0xd0	          //驱动XN XP，测量Y+

/* 扩展变量 ------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
void Touch_Init_GPIO(void);
uint16_t XPT2046_ReadAdc_Fliter(uint8_t channel);

#endif /* __BSP_XPT2046_H__ */

/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
