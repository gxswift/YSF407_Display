/**
  ******************************************************************************
  * �ļ�����: bsp_lcd.c 
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2017-03-30
  * ��    ��: Һ���ײ���������ʵ��
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
#include "lcd/bsp_lcd.h"
#include "lcd/ascii.h"

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
__IO uint32_t lcd_id=0;                // ���浱ǰ��鵽��Һ��ģ��ID
SRAM_HandleTypeDef hlcd;               // SRAM������
static int FSMC_LCD_Initialized = 0;   // FSMC��ʼ����־λ��0��δ��ʼ����1������ɳ�ʼ��
static int FSMC_LCD_DeInitialized = 0; // FSMC����ʼ����־λ��0��δ����ʼ����1������ɷ���ʼ��

/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/
/**
  * ��������: ��ʼ��LCD��IO����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ����LCD������ILI9488�൱��һ���ⲿSRAM����
  *           �ú�����HAL_SRAM_MspInit��������
  */
static void HAL_FSMC_LCD_MspInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;	

  /* ����Ѿ���ɳ�ʼ���������ʼ���ڶ��� */
  if(FSMC_LCD_Initialized)
  {
    return;
  }
  FSMC_LCD_Initialized = 1;
  
  /* ʹ����ض˿�ʱ�� */
  FSMC_LCD_CS_GPIO_ClK_ENABLE();
  FSMC_LCD_DC_GPIO_ClK_ENABLE();
  FSMC_LCD_BK_GPIO_ClK_ENABLE();  
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  
  /* ʹ��FSMC����ʱ�� */
  __HAL_RCC_FSMC_CLK_ENABLE();

  /** FSMC GPIO Configuration  
  PF0   ------> FSMC_A0
  PE7   ------> FSMC_D4
  PE8   ------> FSMC_D5
  PE9   ------> FSMC_D6
  PE10   ------> FSMC_D7
  PE11   ------> FSMC_D8
  PE12   ------> FSMC_D9
  PE13   ------> FSMC_D10
  PE14   ------> FSMC_D11
  PE15   ------> FSMC_D12
  PD8   ------> FSMC_D13
  PD9   ------> FSMC_D14
  PD10   ------> FSMC_D15
  PD14   ------> FSMC_D0
  PD15   ------> FSMC_D1
  PD0   ------> FSMC_D2
  PD1   ------> FSMC_D3
  PD4   ------> FSMC_NOE
  PD5   ------> FSMC_NWE
  PG12   ------> FSMC_NE4
  */
  GPIO_InitStruct.Pin = FSMC_LCD_DC_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;

  HAL_GPIO_Init(FSMC_LCD_DC_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = FSMC_LCD_CS_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(FSMC_LCD_CS_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4 
                          |GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* ����͵�ƽ�����ⲻ�� */
  HAL_GPIO_WritePin(FSMC_LCD_BK_PORT, FSMC_LCD_BK_PIN, GPIO_PIN_RESET);

  /* Һ������������ų�ʼ�� */
  GPIO_InitStruct.Pin = FSMC_LCD_BK_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
  HAL_GPIO_Init(FSMC_LCD_BK_PORT, &GPIO_InitStruct);
}

/**
  * ��������: ��ʼ��FSMC��IO����
  * �������: hsram��SRAM������ָ��
  * �� �� ֵ: ��
  * ˵    �����ú�����HAL���ڲ���������
  */	
void HAL_SRAM_MspInit(SRAM_HandleTypeDef* hsram)
{
  HAL_FSMC_LCD_MspInit();
}

/**
  * ��������: ����ʼ��LCD��IO����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ����LCD������ILI9488�൱��һ���ⲿSRAM����
  *           �ú�����HAL_SRAM_MspDeInit��������
  */
static void HAL_FSMC_LCD_MspDeInit(void)
{
  /* ����Ѿ���ɷ���ʼ���������ʼ���ڶ��� */
  if(FSMC_LCD_DeInitialized)
  {
    return;
  }
  FSMC_LCD_DeInitialized = 1;
  
  /* ����FSMC����ʱ�� */
  __HAL_RCC_FSMC_CLK_DISABLE();
  
  /** FSMC GPIO Configuration  
  PF0   ------> FSMC_A0
  PE7   ------> FSMC_D4
  PE8   ------> FSMC_D5
  PE9   ------> FSMC_D6
  PE10   ------> FSMC_D7
  PE11   ------> FSMC_D8
  PE12   ------> FSMC_D9
  PE13   ------> FSMC_D10
  PE14   ------> FSMC_D11
  PE15   ------> FSMC_D12
  PD8   ------> FSMC_D13
  PD9   ------> FSMC_D14
  PD10   ------> FSMC_D15
  PD14   ------> FSMC_D0
  PD15   ------> FSMC_D1
  PD0   ------> FSMC_D2
  PD1   ------> FSMC_D3
  PD4   ------> FSMC_NOE
  PD5   ------> FSMC_NWE
  PG12   ------> FSMC_NE4
  */
  HAL_GPIO_DeInit(GPIOE, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15);

  HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4 
                          |GPIO_PIN_5);
  HAL_GPIO_DeInit(FSMC_LCD_DC_PORT, FSMC_LCD_DC_PIN);
  HAL_GPIO_DeInit(FSMC_LCD_CS_PORT, FSMC_LCD_CS_PIN);
}

/**
  * ��������: ����ʼ��FSMC��IO����
  * �������: hsram��SRAM������ָ��
  * �� �� ֵ: ��
  * ˵    �����ú�����HAL���ڲ���������
  */	
void HAL_SRAM_MspDeInit(SRAM_HandleTypeDef* hsram)
{
  HAL_FSMC_LCD_MspDeInit();
}

/**
  * ��������: LCD  FSMC ģʽ����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������дʹ����ͬʱ������
  */
void MX_FSMC_Init(void)
{
  FSMC_NORSRAM_TimingTypeDef Timing;

  /* ����FSMC���� */
  hlcd.Instance = FSMC_NORSRAM_DEVICE;
  hlcd.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;

  hlcd.Init.NSBank = FSMC_LCD_BANKx;
  hlcd.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hlcd.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  hlcd.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hlcd.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  hlcd.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hlcd.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  hlcd.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  hlcd.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  hlcd.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  hlcd.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  hlcd.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hlcd.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
  hlcd.Init.PageSize = FSMC_PAGE_SIZE_NONE;
  
  Timing.AddressSetupTime      = 0x02; //��ַ����ʱ��
  Timing.AddressHoldTime       = 0x00; //��ַ����ʱ��
  Timing.DataSetupTime         = 0x05; //���ݽ���ʱ��
  Timing.BusTurnAroundDuration = 0x00;
  Timing.CLKDivision           = 0x00;
  Timing.DataLatency           = 0x00;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  HAL_SRAM_Init(&hlcd, &Timing, &Timing);

}

/**
  * ��������: ��ʼ��LCD�Ĵ���
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������Ҫ������Щ�Ĵ�������Ҫ����ʲôֵ��Һ��������������������أ�
  *           ������Щ�����ɳ����ṩ����ͬ���ҿ��ܲ�ͬ��Ҳ���Ը���ILI9488оƬ
  *           �ֲ����ݲο��޸ġ�
  */
static void ILI9488_REG_Config ( void )
{
  //************* Start Initial Sequence **********//
  /* PGAMCTRL (Positive Gamma Control) (E0h) */
  LCD_WRITE_CMD(0xE0);
  LCD_WRITE_DATA(0x00);
  LCD_WRITE_DATA(0x07);
  LCD_WRITE_DATA(0x10);
  LCD_WRITE_DATA(0x09);
  LCD_WRITE_DATA(0x17);
  LCD_WRITE_DATA(0x0B);
  LCD_WRITE_DATA(0x41);
  LCD_WRITE_DATA(0x89);
  LCD_WRITE_DATA(0x4B);
  LCD_WRITE_DATA(0x0A);
  LCD_WRITE_DATA(0x0C);
  LCD_WRITE_DATA(0x0E);
  LCD_WRITE_DATA(0x18);
  LCD_WRITE_DATA(0x1B);
  LCD_WRITE_DATA(0x0F);

  /* NGAMCTRL (Negative Gamma Control) (E1h)  */
  LCD_WRITE_CMD(0XE1);
  LCD_WRITE_DATA(0x00);
  LCD_WRITE_DATA(0x17);
  LCD_WRITE_DATA(0x1A);
  LCD_WRITE_DATA(0x04);
  LCD_WRITE_DATA(0x0E);
  LCD_WRITE_DATA(0x06);
  LCD_WRITE_DATA(0x2F);
  LCD_WRITE_DATA(0x45);
  LCD_WRITE_DATA(0x43);
  LCD_WRITE_DATA(0x02);
  LCD_WRITE_DATA(0x0A);
  LCD_WRITE_DATA(0x09);
  LCD_WRITE_DATA(0x32);
  LCD_WRITE_DATA(0x36);
  LCD_WRITE_DATA(0x0F);
  
  /* Adjust Control 3 (F7h)  */
  LCD_WRITE_CMD(0XF7);
  LCD_WRITE_DATA(0xA9);
  LCD_WRITE_DATA(0x51);
  LCD_WRITE_DATA(0x2C);
  LCD_WRITE_DATA(0x82);/* DSI write DCS command, use loose packet RGB 666 */

  /* Power Control 1 (C0h)  */
  LCD_WRITE_CMD(0xC0);
  LCD_WRITE_DATA(0x11);
  LCD_WRITE_DATA(0x09);

  /* Power Control 2 (C1h) */
  LCD_WRITE_CMD(0xC1);
  LCD_WRITE_DATA(0x41);

  /* VCOM Control (C5h)  */
  LCD_WRITE_CMD(0XC5);
  LCD_WRITE_DATA(0x00);
  LCD_WRITE_DATA(0x0A);
  LCD_WRITE_DATA(0x80);

  /* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
  LCD_WRITE_CMD(0xB1);
  LCD_WRITE_DATA(0xB0);
  LCD_WRITE_DATA(0x11);

  /* Display Inversion Control (B4h) */
  LCD_WRITE_CMD(0xB4);
  LCD_WRITE_DATA(0x02);

  /* Display Function Control (B6h)  */
  LCD_WRITE_CMD(0xB6);
  LCD_WRITE_DATA(0x02);
  LCD_WRITE_DATA(0x22);

  /* Entry Mode Set (B7h)  */
  LCD_WRITE_CMD(0xB7);
  LCD_WRITE_DATA(0xc6);

  /* HS Lanes Control (BEh) */
  LCD_WRITE_CMD(0xBE);
  LCD_WRITE_DATA(0x00);
  LCD_WRITE_DATA(0x04);

  /* Set Image Function (E9h)  */
  LCD_WRITE_CMD(0xE9);
  LCD_WRITE_DATA(0x00);
 
  /* ������Ļ����ͳߴ� */
  LCD_WRITE_CMD(0x36); 
  LCD_WRITE_DATA(0x08);   
  LCD_WRITE_CMD(0x2A); 
  LCD_WRITE_DATA(0x00);	/* x start */	
  LCD_WRITE_DATA(0x00);
  LCD_WRITE_DATA(0x01);  /* x end */	
  LCD_WRITE_DATA(0x3F);

  LCD_WRITE_CMD(0x2B); 
  LCD_WRITE_DATA(0x00);	/* y start */  
  LCD_WRITE_DATA(0x00);
  LCD_WRITE_DATA(0x01);	/* y end */   
  LCD_WRITE_DATA(0xdF);		
  
  /* write gram start */
	LCD_WRITE_CMD(0x2C);	
  
  /* Interface Pixel Format (3Ah) */
  LCD_WRITE_CMD(0x3A);
  LCD_WRITE_DATA(0x55);/* 0x55 : 16 bits/pixel  */

  /* Sleep Out (11h) */
  LCD_WRITE_CMD(0x11);
  HAL_Delay(120);
  /* Display On */
  LCD_WRITE_CMD(0x29);

}

/**
  * ��������: ��ȡҺ��ģ��ID
  * �������: ��
  * �� �� ֵ: Һ��ģ���ID
  * ˵    ��������ͨ����ȡ04H�Ĵ�����ȡ�õ�Һ��ģ��ID����IDֵ��Һ�����ұ�̣���ͬҺ��
  *           ���ҵ�Һ��ģ��õ���IDֵ���ܲ�ͬ����Ҳ���Էֱ治ͬ�ͺŵ�Һ��ģ�顣
  */
static uint32_t LCD_ReadID(void)
{
	uint16_t buf[4];

	LCD_WRITE_CMD(0x04);  
	buf[0] = LCD_READ_DATA();        // ��һ����ȡ������Ч
	buf[1] = LCD_READ_DATA()&0x00ff; // ֻ�е�8λ������Ч
	buf[2] = LCD_READ_DATA()&0x00ff; // ֻ�е�8λ������Ч
	buf[3] = LCD_READ_DATA()&0x00ff; // ֻ�е�8λ������Ч
	return (buf[1] << 16) + (buf[2] << 8) + buf[3];  
}

/**
  * ��������: Һ��ģ���ʼ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
uint32_t BSP_LCD_Init(void)
{
  MX_FSMC_Init();
  lcd_id=LCD_ReadID();
  printf("LCD_ReadID=%x\n",lcd_id);
  if(lcd_id==0x548066)
  {
    ILI9488_REG_Config();
  }
  
  return lcd_id;
}

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
