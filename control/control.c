#include "control.h"
#include "temp.h"
#include "stdio.h"
#include "WM.h"
#include "power.h"
#include "led/bsp_led.h"
#include "rtc.h"

SIGNAL Water[3];
SETTING 	Set;
TIME 			Time;
STATE			State;

uint8_t Init_Step,Wash_Step;
uint8_t status;

void GetSigal(SIGNAL *sig,uint8_t val)
{
  uint8_t s=sig->sta;
  if(s^val)
  {
  	sig->cnt++;
    if(sig->cnt>=sig->set)
    {
		sig->sta=val;
		sig->cnt=0;
    }
  }
  else
  {
    sig->cnt=0; 
  }
}

void Signal_Init(void)
{
	uint8_t i;
	for (i = 0;i < 3;i++)
	{
		Water[i].sta = 0;
		Water[i].cnt = 0;
		Water[i].set = 10;
	}
}



#define Water_LOW			HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6)
#define Water_HIGH		HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7)
#define Water_WARN		HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15)


void Get_Signal(void)
{
	GetSigal(&Water[LOW],Water_LOW);
	GetSigal(&Water[HIGH],Water_HIGH);
	GetSigal(&Water[WARN],Water_WARN);

	State.lowflag =! (Water[LOW].sta);
	State.highflag =! (Water[HIGH].sta);
	State.warnflag =! (Water[WARN].sta);
}

/*

typedef struct
{
	uint32_t wait;
	uint32_t circle;
	uint32_t out;
}TIME;


typedef struct
{
	uint8_t inflag;
	uint8_t outflag;
	uint8_t heaterflag;
	uint8_t lowflag;
	uint8_t highflag;
	uint8_t warnflag;
	uint8_t temp;
}STATE;

*/





#define Heater(i)		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,i)

#define In(i)				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,i)

#define Out(i)			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,i)

#define Circle(i)		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,i)


enum{Init,Wash,Normal};

//0关闭	1出水 2循环
void Pump_Out(uint8_t state)
{
	if(state == 1)
	{
		EN_Set(1);
		Jump_Step(19-Set.outspeed);
	}
	else if (state == 2)
	{
		EN_Set(1);
		Jump_Step(19-Set.circlespeed);//16
	}
	else
	{
		EN_Set(0);
		
	}
}


void Out_Start(uint32_t time)
{
	Time.out = time;
	Time.circle = 0;//清一下循环时间
	Pump_Out (1);
	Out (ON);
	State.outflag = 1;
}

void Out_Stop()
{
	Set.out = 0;
	Time.out = 0;
	State.handflag = 0;
	
	Pump_Out (0);
	Out (OFF);
	State.outflag = 0;
}

void Circle_Start()
{
	Pump_Out(2);
	Circle(ON);
	State.circleflag = 1;
}


void Circle_Stop()
{
	Pump_Out(0);
	Circle(OFF);
	State.circleflag = 0;
	
}
/*

typedef struct 
{
	uint32_t vol1;//单击
	uint32_t vol2;//双击
	uint32_t vol3;//长按
	uint32_t volhand;//手动
	uint32_t out;//出水
	uint32_t temperature;//温度
	uint32_t language;//语言
	uint32_t visable;//可见
	uint32_t init;//首次设置
	
	uint32_t lighttime;//屏幕时间 min
	uint32_t circletime;//循环时间 s
	uint32_t circleinterval;//循环间隔 min
	uint32_t outspeed;//出水等级
	uint32_t circlespeed;//循环等级

}SETTING;

HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1);
HAL_RTCEx_BKUPWrite(&hrtc,RTC_BKP_DR1, Number);
*/
#define COUNT(a)	(sizeof(a) / sizeof(uint32_t))
void Setting_Save()
{
	uint8_t i;
	for(i = 0;i < COUNT(Set);i++)
	{
		HAL_RTCEx_BKUPWrite(&hrtc,RTC_BKP_DR1+i, *((uint32_t *)&Set+i));
		printf("set%d ->%d\r\n",i,*((uint32_t *)&Set+i));
	}
}


void Setting_Init()
{
	uint8_t i;
	if (HAL_RTCEx_BKUPRead(&hrtc,RTC_BKP_DR1 + 8) != 1)
	{
		Set.vol1 = 300;
		Set.vol2 = 500;
		Set.vol3 = 1000;
		Set.volhand = 1500;
		Set.out = 0;
		Set.temperature = 35;
		Set.language = 1;
		Set.visable = 1;
		Set.init = 1;
		Set.lighttime = 2;
		Set.circletime = 10;
		Set.circleinterval = 15;
		Set.circlespeed = 3;
		Set.outspeed = 10;
		
		Setting_Save();
	}
	for(i = 0;i < COUNT(Set);i++)
	{
		*((uint32_t *)&Set+i) = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1+i);
		printf("set%d ->%d\r\n",i,*((uint32_t *)&Set+i));
	}
}

void Control()
{
	switch(status)
	{
		case Init:
			Signal_Init();
			Setting_Init();
			status = Normal;
			Reset();
			EN_Set(0);
		
		
		break;
		case Wash:
			switch(Wash_Step)
			{
				case 1://排水
					//小于50度
					if(State.temperature < 50)
					{
						if (State.lowflag == 0)
						{
							Time.wait = 30000;
							Wash_Step++;
							Out(OFF);
							
							State.inflag = 1;
							In(ON);							
						}
						else
						{
							State.outflag = 1;
							Out(ON);
						}
					}
					else
					{
						break;
					}
					break;
				
				//---------------------------------------------------------------
				case 2://加清洗剂
					if (Time.wait == 0)
					{
						State.inflag = 0;
						In(OFF);					

						Wash_Step++;
						Time.circle = 60*60*1000;
					}
					break;
				//---------------------------------------------------------------
				case 3://循环
					if (Time.circle%(20*60*1000)> 5*60*1000)
					{
						Out(ON);
					}
					else
					{
						Out(OFF);
					}
					
					if (Time.circle == 0)
					{
						Wash_Step++;
					}
					break;
				//---------------------------------------------------------------
				case 4://冲洗排出
					Out(1);
					if (State.lowflag)
					{
						Out(0);
						
					}
				break;
			}
		break;
			
		case Normal:
			//加热
			if (State.temperature >= Set.temperature)
			{
				State.heaterflag = 0;
				Heater(OFF);
			}
			if (State.temperature < Set.temperature - 2 )
			{
				if(State.warnflag == 0 && State.lowflag == 1 && Time.tick > 5000)
				{
					Heater (ON);
					State.heaterflag = 1;
				}
				else
				{
					Heater(OFF);
					State.heaterflag = 0;
				}
			}
			//低水位
			//----------------------------------------------
			if (State.lowflag == 0)
			{
				Time.circle = 0;
				In (ON);
				State.inflag = 1;
			}
			//高水位
			//----------------------------------------------
			else
			{
				if (State.highflag == 0)
				{
					Time.circle = 0;
					In (ON);
					State.inflag = 1;
				}
				else
				{
					In (OFF);
					State.inflag = 0;
				}
			}
			//溢水位
			//----------------------------------------------
			if (State.warnflag == 1)
			{
				In (OFF);
				State.inflag = 0;	
			}
			//----------------------------------------------
			//出水关闭，不影响循环开关
			if (Time.out == 0 && State.outflag == 1)
			{
				State.outflag = 0;
				Out_Stop();
			}
			//----------------------------------------------
			//循环
			if (Set.circleinterval == 0 || Set.circletime == 0)
				return;
			if (State.outflag == 0 && State.inflag == 0)
			{
				if(Time.circle > Set.circleinterval * 60 * 1000)
				{
					Circle_Start();
				}
				if (Time.circle > Set.circleinterval * 60 * 1000 + Set.circletime * 1000)
				{
					Time.circle = 0;
					Circle_Stop();
				}
			}
			else
			{
				Circle(OFF);
				Time.circle = 0;
				
			}
		break;
	}
}



void All_Stop()
{
	Heater(0);
	In(0);
	Out(0);
	Circle(0);	
	EN_Set(0);
	printf("关闭所有功能\r\n");
}



extern uint32_t ADC_Value;
void Debug_Print()
{
	printf("加热%d\t进水阀%d\t出水阀%d\r\n",State.heaterflag,State.inflag,State.outflag);
	printf("低%d\t高%d\t报警%d\t温度%d\r\n",State.lowflag,State.highflag,State.warnflag,State.temperature);
	printf("ad = %d\r\n",ADC_Value);
	printf("---------------------------------------------------\r\n\r\n");
}

extern WM_HWIN H_Hand;

extern void GetFreeRam();
void TimerTask()
{
	static uint8_t cnt,cnt10,cnt500;
	cnt++;
	if (cnt > 100)
	{			
		State.temperature = Get_Temp();
		Get_Signal();	
		cnt = 0;
		cnt500++;
		if (cnt500 > 5)
		{
			cnt500 = 0;
			State.flash ^= 1;
			HAL_GPIO_TogglePin(LED1_GPIO,LED1_GPIO_PIN);
	//		Debug_Print();
	 		GetFreeRam();
		}
	}
	
	if (Time.wait)
		Time.wait--;
	
	Time.tick++;
	if (Time.out)//出水
	{
		//-------------------------------
		cnt10++;
		if (cnt10>=10)//设置时间扩大10倍
		{
			cnt10 = 0;
		//-------------------------------	
			State.totalvolume++;
			Time.out--;
			Time.circle = 0;
			if (State.hwinflag == 1 && State.handflag == 1)
				WM_SendMessageNoPara(H_Hand,WM_USER);
		}
		/*
		if (Power < 200)
		{
			Power++;//
		}
		*/
	}
	else
	{
		Time.circle++;
	}
}
//暂不用发送无参变量信号方式，改用窗口定时器自动刷新获取变量
void Func()//20ms
{
	Control();

}

