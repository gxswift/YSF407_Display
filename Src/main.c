/**
  ******************************************************************************
  * 文件名程: main.c 
  * 作    者: 硬石嵌入式开发团队
  * 版    本: V1.0
  * 编写日期: 2017-03-30
  * 功    能: Button按钮控件
  ******************************************************************************
  * 说明：
  * 本例程配套硬石stm32开发板YS-F4Pro使用。
  * 
  * 淘宝：
  * 论坛：http://www.ing10bbs.com
  * 版权归硬石嵌入式开发团队所有，请勿商用。
  ******************************************************************************
  */
/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "usart/bsp_debug_usart.h"
#include "lcd/bsp_lcd.h"
#include "stdlib.h"
#include "rtc.h"
#include "touch/bsp_touch.h"
#include "led/bsp_led.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"
#include "timers.h"

#include "GUI.h"
#include "WM.h"
/**
  * 函数功能: 系统时钟配置
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * 函数功能: 主函数.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */

//
extern void Skin();
extern WM_HWIN CreateWindow();
extern WM_HWIN HeadWindow(void);

static void vTaskGUI(void *pvParameters)
{
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_Init();
	Skin();
	CreateWindow();
	HeadWindow();

	while (1)
	{
		GUI_Exec();
	}
}

static void vTaskTouch(void *pvParameters)
{
	while(1)
	{
		GUI_TOUCH_Exec();	
		vTaskDelay(10);
	}
}

static void vTaskLed1(void *pvParameters)
{
	vTaskDelay(100);
		MX_RTC_Init();
	while(1)
	{
		HAL_GPIO_TogglePin(LED1_GPIO,LED1_GPIO_PIN);
		vTaskDelay(800);
	}
}

static void vTaskLed2(void *pvParameters)
{
	uint16_t cnt = 0;
	while(1)
	{
		if (GUI_PID_IsPressed())
		{
			cnt = 0;
			LCD_BK_ON();
		}
		else
		{
			if (cnt < 600)
				cnt++;
			else
			{
				LCD_BK_OFF();
			}
		}
		HAL_GPIO_TogglePin(LED2_GPIO,LED2_GPIO_PIN);
		vTaskDelay(100);
	}
}
static void vTaskLed3(void *pvParameters)
{
	while(1)
	{
		HAL_GPIO_TogglePin(LED3_GPIO,LED3_GPIO_PIN);
		vTaskDelay(300);
	}
}

//static void vTaskTouchtest(void *pvParameters)
//{
//	GUI_PID_STATE State;
//	while(1)
//	{
//		GUI_PID_GetState(&State);
//		printf("x:%d\ty:%d\r\n",State.x,State.y);
//		vTaskDelay(300);
//	}
//}

void HAL_Delay(__IO uint32_t Delay)
{
	vTaskDelay(Delay);
}

//uint32_t HAL_GetTick()
//{
//	return xTaskGetTickCount();
//}

int main(void)
{
  /* 复位所有外设，初始化Flash接口和系统滴答定时器 */
	SCB->VTOR = FLASH_BASE | 0x10000;//设置偏移量
	
  HAL_Init();
	__set_PRIMASK(1);
  /* 配置系统时钟 */
  SystemClock_Config();
  __HAL_RCC_CRC_CLK_ENABLE();
  MX_DEBUG_USART_Init();
  LED_GPIO_Init();
	
  /* 电阻触摸相关GPIO初始化 */
  Touch_Init_GPIO();
  lcd_id=BSP_LCD_Init();  
  /* 初始化GUI */
//  GUI_Init();	
	LCD_BK_ON();
	xTaskCreate(vTaskGUI,
							"vTaskGUI",
							4096,
							NULL,
							1,
							NULL);
		xTaskCreate(vTaskTouch,
							"vTaskTouch",
							512,
							NULL,
							1,
							NULL);
	xTaskCreate(vTaskLed1,
							"vTaskLed1",
							512,
							NULL,
							2,
							NULL);
	xTaskCreate(vTaskLed2,
							"vTaskLed2",
							512,
							NULL,
							2,
							NULL);
	xTaskCreate(vTaskLed3,
							"vTaskLed3",
							512,
							NULL,
							2,
							NULL);
//		xTaskCreate(vTaskTouchtest,
//							"vTaskTouchtest",
//							512,
//							NULL,
//							2,
//							NULL);
	vTaskStartScheduler();
//  while (1)
//  {
//		LCD_BK_ON();
//    MainTask();    
//  }
}


/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
