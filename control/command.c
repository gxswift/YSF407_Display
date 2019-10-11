#include "command.h"

#include "control.h"


#include "usart/bsp_debug_usart.h"


uint8_t r_temp;
uint8_t Recv[20];
uint8_t Rcnt;

void Uart3_IT()
{
	HAL_UART_Receive_IT(&huart3, &r_temp, 1);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint16_t i;
	if (huart == &huart3)
	{
//用数组		
		Recv[Rcnt] = r_temp;
		if (Rcnt < 15)
			Rcnt++;		
////用队列		
//		if(Ring3.Lenth<255)
//		{
//			Write_Data(&Ring3,r_temp);
//		}
//		
//		
		if (HAL_OK !=HAL_UART_Receive_IT(&huart3, &r_temp, 1))
		{
			printf("IT error!\r\n");
			
			huart3.RxState = HAL_UART_STATE_READY;
			__HAL_UNLOCK(&huart3);
			HAL_UART_Receive_IT(&huart3, &r_temp, 1);
			return;
		}
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if(__HAL_UART_GET_FLAG(huart,UART_FLAG_ORE) != RESET) 
    {
        __HAL_UART_CLEAR_OREFLAG(huart);
        HAL_UART_Receive_IT(huart,(uint8_t *)&r_temp,1);
			printf("run over\r\n");
    }
}

CMD Cmd=
{
	.head = 0xAA,
	.add = 0x01,
};


DROP Drop = 
{
	.func = 1,
	.color = 0x202020,
	.connect = 0
};


#define USECRC 0

uint16_t CRC16(uint16_t crc_gen,uint8_t *_data,uint8_t length)
{
	#if USECRC
	uint16_t result;
	uint8_t i,j;
	
	result=0xFFFF;
	if(length!=0)
	{
		for(i=0;i<length;i++)
		{
			result^=(uint16_t)(_data[i]);
			for(j=0;j<8;j++)
			{
				if((result&0x0001)==0x0001)
				{
					result>>=1;
					result^=crc_gen;//0xA001
				}
				else result>>=1;
			}
		}
	}
	return result;
	#else
	return 0xFFFF;
	#endif
}

void Protocol_Buffer(CMD *pb,uint8_t *buffer,uint8_t *len )
{
	uint8_t i;
	uint16_t crc_temp;
	
	buffer[0] = pb->head;
	buffer[1] = pb->add;
	buffer[2] = pb->len;	
	buffer[3] = pb->cmd;
	if (pb->len > 0)
	{
		for (i = 0;i < pb->len;i++)
		{
			buffer[4+i] = pb->data[i];
		}
	}
	
	crc_temp = CRC16(0xA001,buffer,pb->len+3 );
	
	buffer[3+pb->len] = crc_temp;
	buffer[4+pb->len] = crc_temp>>8;
	*len = 5+pb->len;
	
}

//A0
void Get_Key()
{
	Cmd.cmd = 0xA0;
	Cmd.len = 1;
}
//A1
uint8_t buff[4];
void Set_LED(uint8_t fun,uint32_t color)
{
	Cmd.cmd = 0xA1;
	Cmd.len = 5;
	buff[0] = fun;
	buff[1] = color>>16;
	buff[2] = color>>8;
	buff[3] = color;
	Cmd.data = buff;
}


void Drop_Reset()
{
	Cmd.cmd = 0xA3;
	Cmd.len = 1;
	
}

void Get_Version()
{
	Cmd.cmd = 0xA4;
	Cmd.len = 1;
}




/*
文档版本
send
head add 	len  cmd   data							crc
0xaa 0x01


recv
head add 	len  cmd   data							crc   
0x55 0x01
*/


/*
当前
AA 01 01 A0 FF FF								->55 01 02 0A 00 FF FF 
AA 01 05 A1 01 50 50 50 FF FF		->55 01 01 1A FF FF 
AA 01 01 A2 FF FF								->55 01 01 2A FF FF
AA 01 01 A4 FF FF								->55 01 04 4A 02 02 00 FF FF
AA 01 01 A5 FF FF								->55 01 02 5A 00 FF FF

*/

uint8_t Get_Data(uint8_t *buff)
{
	if ((buff[0] != 0x55) || (buff[1]!= 0x01))
		return 1;
	
	uint8_t len = buff[2];
	if (CRC16(0xA001,buff,len) != (buff[3+len]|buff[4+len]<<8))
		return 2;
	
	switch(buff[3])//ask
	{
		case 0x0A://key
			Drop.key = buff[4];
			if (State.outflag && Drop.key)
			{
				Out_Stop();
				printf("停止出水\r\n");
				break;
			}
				//出水
			if (Drop.key == 1)
			{
				Out_Start(Set.vol1);
				printf("单击出水\r\n");
			}
			else if (Drop.key == 2)
			{
				Out_Start(Set.vol2);
				printf("双击出水\r\n");
			}
			else if (Drop.key == 3)
			{
				Out_Start(Set.vol3);
				printf("长按出水\r\n");
			}
			break;
		case 0x1A://LED
			break;
		case 0x3A://reset
			break;
		case 0x4A://version
			Drop.verl = buff[4];
			Drop.verm = buff[5];
			Drop.verh = buff[6];
			break;
	}
	return 0;
}

void Send_Data(uint8_t mode)
{
	uint8_t send[15];
	uint8_t len;
	uint32_t start;
	uint8_t i;
	uint8_t rec;
	static uint8_t cnt = 0;
	switch(mode)
	{
		case 0:
			Set_LED(Drop.func,Drop.color);
			break;
		case 1:
			Get_Key();
			break;
		case 2:
			Drop_Reset();
			break;
		case 4:
			Get_Version();
			break;
	}
	
	Protocol_Buffer(&Cmd,send,&len);
	Rcnt = 0;
	for(i = 0;i < 15;i++)
		Recv[i] = 0;
	HAL_UART_Transmit(&huart3, send, len, 20);
			HAL_Delay(1);	
	start = HAL_GetTick();
	while(1)
	{	
//		temp = GetOnePacket(&Ring3,Ring_data,&buffer_len);
//		rec = Get_Data(Ring_data);	
		rec = Get_Data(Recv);

		if (rec == 0)
		{
			cnt = 0;
			Drop.connect = 1;
			State.connect = 1;
			return;
		}
		else
		{
		}

		if (HAL_GetTick()-start > 500)//手动测试数值设置大
		{
			if (cnt < 5)
				cnt++;
			else
			{
				Drop.connect = 0;
				State.connect = 0;
			}
		//	printf("超时%d\r\n",cnt);
			return;
		}
	}
}










