#include "temp.h"



/*

--------	VCC
    |
		|
		_
	 | |  	10K
	 | |
	  -
		|
		|-----ADC
		|
		_
	 | |  	NTC (50K	3950)
	 | |
	  -
		|
		|
		|
	_____
	 ___		GND
		_


*/
extern uint32_t ADC_Value;
extern uint32_t OM[];

#define ARRNUM	5
uint16_t AD_Process()
{
	static uint16_t buf[ARRNUM];
	static uint8_t cnt;
	uint16_t sum;
	uint8_t i;
	buf[cnt] = ADC_Value;
	if (++cnt>=ARRNUM)
		cnt = 0;
	
	sum = 0;
	for(i=0;i<ARRNUM;i++)
	{
		sum+=buf[i];
	}
	return sum/ARRNUM;
}

uint16_t Get_Temp()
{
  uint32_t Res;
  uint16_t AD;
  uint8_t i,Temp;;//
  
  AD = AD_Process();
	if(AD<100)
		return 150;//��ʾE1
	else if(AD> 4000)
		return 151;//��ʾE2
  Res = 10000*AD/(4095 - AD);// OM	ת���ɶ�Ӧ����
  
  for(i=0;i<100;i++)
  { 
    Temp= i;
    if( Res<OM[i])
    {
      continue;
    }
    else 
			break;
  }
  return Temp;
}
















