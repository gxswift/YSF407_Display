#include "stm32f4xx_hal.h"
#include "usart/bsp_debug_usart.h"
#include "lcd/bsp_lcd.h"
#include "stdlib.h"
#include "rtc.h"
#include "adc.h"
#include "dma.h"
#include "gpio.h"
#include "touch/bsp_touch.h"
#include "led/bsp_led.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"
#include "timers.h"

#include "GUI.h"
#include "WM.h"
#include "temp.h"
#include "control.h"
#include "command.h"
/**
  * 函数功能: 系统时钟配置
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
	
uint32_t ADC_Value;
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
extern WM_HWIN CreateWindow();
extern WM_HWIN HeadWindow(void);
extern void Skin();
static void vTaskGUI(void *pvParameters)//显示
{
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_Init();
	Skin();
	HAL_Delay(100);
	HeadWindow();
	CreateWindow();
	while (1)
	{
		GUI_Exec();
	}
}

static void vTaskTouch(void *pvParameters)//触摸
{
	while(1)
	{
		GUI_TOUCH_Exec();	
		vTaskDelay(10);
	}
}

static void vTaskTimer(void *pvParameters)//计时，传感器
{
	TickType_t Tick;
	
	vTaskDelay(100);

	Tick  = xTaskGetTickCount();
	while(1)
	{		
		vTaskDelayUntil(&Tick,1);
		TimerTask();
	}
}

static void vTaskScreen(void *pvParameters)//屏保
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
			if (cnt < Set.lighttime*600)
				cnt++;
			else
			{
				if (Set.lighttime != 0)
				LCD_BK_OFF();
			}
		}
		HAL_GPIO_TogglePin(LED2_GPIO,LED2_GPIO_PIN);
		vTaskDelay(100);
	}
}

static void vTaskFun(void *pvParameters)//控制
{
	uint16_t cnt = 0;

	while(1)
	{
		HAL_GPIO_TogglePin(LED3_GPIO,LED3_GPIO_PIN);
		Func();
		vTaskDelay(20);
	}
}

QueueHandle_t xQueue;
//xQueueSend(xQueue1,(void *) &ucCount,(TickType_t)10)

//uint8_t cmd[] = "1test\r\n";//{0xaa,0x00};
static void vTaskCom(void *pvParameters)
{
//	cmd[0] = '1';//不加就是2，why？
//	HAL_UART_Transmit(&huart3, cmd, 7, 20);	
	uint8_t mode = 1;
	BaseType_t xResult;
	
	xQueue = xQueueCreate( 10,sizeof (uint8_t));
	if (xQueue == 0)
	{
		printf("创建失败\r\n");
	}
	MX_USART3_UART_Init();
	Uart3_IT();
	while(1)
	{
		xResult = xQueueReceive(xQueue,&mode,10);
		if (xResult == pdPASS)
		{
			printf("消息%d\r\n",mode);
		}
		else
			mode = 1;
		
		Send_Data(mode);
		vTaskDelay(20);
	}
}

void HAL_Delay(__IO uint32_t Delay)
{
	vTaskDelay(Delay);
}

//uint32_t HAL_GetTick()
//{
//	return xTaskGetTickCount();
//}
extern uint8_t r_temp;
int main(void)
{
	SCB->VTOR = FLASH_BASE | 0x10000;//设置偏移量
	
  HAL_Init();
	__set_PRIMASK(1);
  /* 配置系统时钟 */
  SystemClock_Config();
  __HAL_RCC_CRC_CLK_ENABLE();
  MX_DEBUG_USART_Init();
	
  LED_GPIO_Init();
	MX_GPIO_Init();
	MX_RTC_Init();
  /* 电阻触摸相关GPIO初始化 */
  Touch_Init_GPIO();
  lcd_id=BSP_LCD_Init();  
	LCD_BK_ON();
	Setting_Init();

	MX_DMA_Init();
  MX_ADC1_Init();
	if(HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADC_Value, 1)!= HAL_OK)
	{
	}

	xTaskCreate(vTaskGUI,
							"vTaskGUI",
							4096,
							NULL,
							2,
							NULL);
	xTaskCreate(vTaskTouch,
							"vTaskTouch",
							256,
							NULL,
							3,
							NULL);
	xTaskCreate(vTaskTimer,
							"vTaskTimer",
							256,
							NULL,
							2,
							NULL);
	xTaskCreate(vTaskScreen,
							"vTaskScreen",
							256,
							NULL,
							2,
							NULL);
	xTaskCreate(vTaskFun,
							"vTaskFun",
							256,
							NULL,
							2,
							NULL);
	xTaskCreate(vTaskCom,
						"vTaskCom",
						512,
						NULL,
						2,
						NULL);
	vTaskStartScheduler();
}



