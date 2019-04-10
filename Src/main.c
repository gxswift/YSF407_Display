/**
  ******************************************************************************
  * �ļ�����: main.c 
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2017-03-30
  * ��    ��: Button��ť�ؼ�
  ******************************************************************************
  * ˵����
  * ����������Ӳʯstm32������YS-F4Proʹ�á�
  * 
  * �Ա���
  * ��̳��http://www.ing10bbs.com
  * ��Ȩ��ӲʯǶ��ʽ�����Ŷ����У��������á�
  ******************************************************************************
  */
/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "usart/bsp_debug_usart.h"
#include "lcd/bsp_lcd.h"
#include "stdlib.h"

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
  * ��������: ϵͳʱ������
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
 
  __HAL_RCC_PWR_CLK_ENABLE();                                     //ʹ��PWRʱ��

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);  //���õ�ѹ�������ѹ����1

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;      // �ⲿ����8MHz
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;                        //��HSE 
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                    //��PLL
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;            //PLLʱ��Դѡ��HSE
  RCC_OscInitStruct.PLL.PLLM = 8;                                 //8��ƵMHz
  RCC_OscInitStruct.PLL.PLLN = 336;                               //336��Ƶ
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;                     //2��Ƶ���õ�168MHz��ʱ��
  RCC_OscInitStruct.PLL.PLLQ = 7;                                 //USB/SDIO/������������ȵ���PLL��Ƶϵ��
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;       // ϵͳʱ�ӣ�168MHz
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;              // AHBʱ�ӣ� 168MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;               // APB1ʱ�ӣ�42MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;               // APB2ʱ�ӣ�84MHz
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  HAL_RCC_EnableCSS();                                            // ʹ��CSS���ܣ�����ʹ���ⲿ�����ڲ�ʱ��ԴΪ����
  
 	// HAL_RCC_GetHCLKFreq()/1000    1ms�ж�һ��
	// HAL_RCC_GetHCLKFreq()/100000	 10us�ж�һ��
	// HAL_RCC_GetHCLKFreq()/1000000 1us�ж�һ��
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);                // ���ò�����ϵͳ�δ�ʱ��
  /* ϵͳ�δ�ʱ��ʱ��Դ */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* ϵͳ�δ�ʱ���ж����ȼ����� */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * ��������: ������.
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */

//
extern void Skin();
extern void CreateWindow();


static void vTaskGUI(void *pvParameters)
{
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_Init();
	Skin();
	CreateWindow();
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
	while(1)
	{
		HAL_GPIO_TogglePin(LED1_GPIO,LED1_GPIO_PIN);
		vTaskDelay(800);
	}
}

static void vTaskLed2(void *pvParameters)
{
	while(1)
	{
		HAL_GPIO_TogglePin(LED2_GPIO,LED2_GPIO_PIN);
		vTaskDelay(500);
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

int main(void)
{
  /* ��λ�������裬��ʼ��Flash�ӿں�ϵͳ�δ�ʱ�� */
	SCB->VTOR = FLASH_BASE | 0x10000;//����ƫ����
	
  HAL_Init();
	__set_PRIMASK(1);
  /* ����ϵͳʱ�� */
  SystemClock_Config();
  __HAL_RCC_CRC_CLK_ENABLE();
  MX_DEBUG_USART_Init();
  LED_GPIO_Init();
  /* ���败�����GPIO��ʼ�� */
  Touch_Init_GPIO();
  printf("ӲʯSTM32F407��������ֲSTemWin����\n"); 
  lcd_id=BSP_LCD_Init();  
  printf("LCD ID= 0x%x\n",lcd_id);
  /* ��ʼ��GUI */
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


/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
