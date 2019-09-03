#include "usart/bsp_debug_usart.h"

UART_HandleTypeDef husart_debug;


void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  if(huart->Instance==DEBUG_USARTx)
  {
    /* 串口外设时钟使能 */
    DEBUG_USART_RCC_CLK_ENABLE();
  
    /* 串口外设功能GPIO配置 */
    GPIO_InitStruct.Pin = DEBUG_USARTx_Tx_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = DEBUG_USARTx_AFx;
    HAL_GPIO_Init(DEBUG_USARTx_Tx_GPIO, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = DEBUG_USARTx_Rx_GPIO_PIN;  
    HAL_GPIO_Init(DEBUG_USARTx_Tx_GPIO, &GPIO_InitStruct);       
  }  
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

  if(huart->Instance==DEBUG_USARTx)
  {
    /* 串口外设时钟禁用 */
    DEBUG_USART_RCC_CLK_DISABLE();
  
    /* 串口外设功能GPIO配置 */
    HAL_GPIO_DeInit(DEBUG_USARTx_Tx_GPIO, DEBUG_USARTx_Tx_GPIO_PIN);
    HAL_GPIO_DeInit(DEBUG_USARTx_Rx_GPIO, DEBUG_USARTx_Rx_GPIO_PIN);
    
    /* 串口中断禁用 */
    HAL_NVIC_DisableIRQ(DEBUG_USART_IRQn);
  }
}


void MX_DEBUG_USART_Init(void)
{
  /* 使能串口功能引脚GPIO时钟 */
  DEBUG_USARTx_GPIO_ClK_ENABLE();
  
  husart_debug.Instance = DEBUG_USARTx;
  husart_debug.Init.BaudRate = DEBUG_USARTx_BAUDRATE;
  husart_debug.Init.WordLength = UART_WORDLENGTH_8B;
  husart_debug.Init.StopBits = UART_STOPBITS_1;
  husart_debug.Init.Parity = UART_PARITY_NONE;
  husart_debug.Init.Mode = UART_MODE_TX_RX;
  husart_debug.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  husart_debug.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&husart_debug);
  
}

int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&husart_debug, (uint8_t *)&ch, 1, 20);
  return ch;
}


