/*
*********************************************************************************************************
*	                                  
*	ģ������ : ��������̶�̬��ʾ
*	�ļ����� : MainTask.c
*	��    �� : V1.0
*	˵    �� : ʵ������
*              1. ���������Ҫ�Ƕ�̬���̵���ʾ������ʹ�ô������ܡ�
*              2. ��Ҫ��ʾ��������̬���̣�ÿ�����̶��ǽ�����һ�������ϣ�ͨ������
*                 ���ڵ���ʾ��Ӷ�ʵ��������ʾ��
*              3. ˢ�µ�ʱ�򣬽���̬ͼ�Ͷ�̬ͼ�ֿ���ֻ��ˢ�¶�̬ͼ���ɡ�
*              4. ע�⺯��GUI_SetClipRect��ʹ�á�
*              
*	�޸ļ�¼ :
*		�汾��   ����         ����          ˵��
*		V1.0    2016-11-26   Eric2013  	    �װ�    
*                                     
*	Copyright (C), 2015-2020, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include "MainTask.h"


/*
*********************************************************************************************************
*                                         �궨��
*********************************************************************************************************
*/
#define COLOR_BEER       0x0DC5FD

#define APP_NEXT_FRAME  (WM_USER + 0)
#define APP_DRAW        (WM_USER + 1)
#define APP_HIDE        (WM_USER + 2)
#define APP_FIRST_FRAME (WM_USER + 3)
#define GRID_DRAW_FULL  (WM_USER + 4)
#define GRID_DRAW_START (WM_USER + 5)


#define ID_BUTTON_0		(GUI_ID_USER + 0x01)

/*
*********************************************************************************************************
*                                         extern
*********************************************************************************************************
*/
extern GUI_CONST_STORAGE GUI_FONT GUI_FontF16B_AA;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontF19B_AA;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontF24B_AA;

extern GUI_CONST_STORAGE GUI_BITMAP bm320_Bubbles;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_ArrowDown;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_ArrowDown_2;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_ArrowLeft;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_ArrowRight;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Barrel;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Tank_2;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Whirlpool_B;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_SeggerLogo;

extern GUI_CONST_STORAGE GUI_BITMAP bmLogo_armflySmall;

extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Boiling_00;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Boiling_01;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Boiling_02;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Boiling_03;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Boiling_04;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Boiling_05;

extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Lautering_00;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Lautering_01;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Lautering_02;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Lautering_03;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Lautering_04;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Lautering_05;

extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Mashing_00;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Mashing_01;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Mashing_02;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Mashing_03;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Mashing_04;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Mashing_05;

extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Whirlpool_00;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Whirlpool_01;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Whirlpool_02;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Whirlpool_03;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Whirlpool_04;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Whirlpool_05;

/*
*********************************************************************************************************
*                                         ����
*********************************************************************************************************
*/
typedef struct {
  int TextY[5];
  int Cnt;
  int DrawBk;
} BkState;

typedef struct {
  int Cnt;
  int Draw;
} MashingState;


static int _Cnt;

/*
*********************************************************************************************************
*	�� �� ��: _DrawMovingBitmapClipRect
*	����˵��: �����������Ҫ������ʵ��λͼ�Ķ�̬�ƶ�Ч������ͨ������GUI_SetClipRect()��������Ĳü�����
*             Ĭ������£��ü���������Ϊ���õ� �����⣩��ʾ����С��
*             ĳЩ����£�ʹ��ͨ���˺����������õĽ�С�Ĳü����αȽ����á�
*             ���õľ���Ӧ���ֲ��䣬ֱ��ʹ�ÿ�ָ���ٴε��øú�����
*	��    �Σ�pBitmap     λͼ��ַ
*             ClipRectX0  �ü��������׵�ַ
*             ClipRectY0  �ü��������׵�ַ
*             ClipRectX1  �ü�������������ַ
*             ClipRectY1  �ü�������������ַ 
* 			  Step		  Number of current step
*			  StepDist	  Distance of a single step, use negative values to turn direction	
*             MovDir	  0 == x; 1 == y;								 
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void _DrawMovingBitmapClipRect(GUI_CONST_STORAGE GUI_BITMAP * pBitmap,
                                                               int   ClipRectX0, int ClipRectY0,
                                                               int   ClipRectX1, int ClipRectY1,
                                                               int   Step,      
                                                               int   StepDist, 
                                                               int   MovDir)   
{ 
	int Stop = 0;
	GUI_RECT Rect;
	int x0, y0, x1, y1, dx, dy;

	Rect.x0 = ClipRectX0;
	Rect.y0 = ClipRectY0;
	Rect.x1 = ClipRectX1;
	Rect.y1 = ClipRectY1;

	GUI_SetClipRect(&Rect);
	
	y0 = ClipRectY0;
	
	/* ����X�����Y��ĵ�������ȷ��λͼ����ʼ�㣬��ȷ��ÿ�ε�����ֵ */
	if (MovDir) 
	{
		dx = 0;
		dy = pBitmap->YSize;
		x0 = ClipRectX0;
		y0 = ClipRectY0 - pBitmap->YSize + Step * StepDist;
	} 
	else 
	{
		dx = pBitmap->XSize;
		dy = 0;
		x0 = ClipRectX0 - pBitmap->XSize + Step * StepDist;
		y0 = ClipRectY0;
	}
	
	/* ȷ��λͼ�Ľ����� */
	x1 = x0 + pBitmap->XSize - 1;
	y1 = y0 + pBitmap->YSize - 1;
	
	/* �������õ���ʾ������λͼ����ʾ��������� */
	do 
	{
		GUI_DrawBitmap(pBitmap, x0, y0);
		x0 += dx;
		y0 += dy;
		x1 += dx;
		y1 += dy;
		if ((x0 > ClipRectX1) || (y0 > ClipRectY1)) 
		{
			Stop = 1;
		}
	} while (Stop == 0);
	
	GUI_SetClipRect(NULL);
}

/*
*********************************************************************************************************
*	�� �� ��: _OverviewStatic
*	����˵��: ���ƾ�̬ͼ�����ڴ���hWinBk���ػ沿��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void _OverviewStatic(void) 
{
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_DrawBitmap( &bm320_Overview_Whirlpool_B    , 270,  88);
	GUI_DrawBitmap( &bm320_Overview_Tank_2         ,   7, 125);
	GUI_DrawBitmap( &bm320_Overview_Tank_2         ,  88, 125);
	GUI_DrawBitmap( &bm320_Overview_Barrel         , 184, 184);
	GUI_DrawBitmap( &bm320_Overview_Barrel         , 227, 184);
	GUI_DrawBitmap( &bm320_Overview_Barrel         , 271, 184);
	//
	// Draw pipes
	//
	GUI_SetColor(GUI_BLACK);
	//
	// ��һ���� whirlpooling �� fermenting֮��ĳ����ӹ�
	//
	GUI_FillRect(304,  88, 304, 109);
	GUI_FillRect(313,  88, 313, 118);
	GUI_FillRect( 35, 109, 303, 109);
	GUI_FillRect( 44, 118, 312, 118);
	GUI_FillRect( 35, 110,  35, 123);
	GUI_FillRect( 44, 119,  44, 123);
	//
	// �ڶ�����fermenting��storage֮��Ķ����ӹ�
	//
	GUI_FillRect( 71, 162,  87, 162);
	GUI_FillRect( 71, 171,  87, 171);
	//
	// ��������torage �� barrels֮��ĳ����ӹ�
	//
	GUI_FillRect(152, 162, 291, 162);
	GUI_FillRect(152, 171, 199, 171);
	GUI_FillRect(204, 171, 242, 171);
	GUI_FillRect(247, 171, 286, 171);
	//
	// ���Ĳ���storage �� barrelsֱ�ӵĶ̹�����
	//
	GUI_FillRect(199, 172, 199, 182);
	GUI_FillRect(204, 172, 204, 182);
	GUI_FillRect(242, 172, 242, 182);
	GUI_FillRect(247, 172, 247, 182);
	GUI_FillRect(286, 172, 286, 182);
	GUI_FillRect(291, 163, 291, 182);
	//
	// ���岽��mashing �� lautering֮��Ĺս�����
	//
	GUI_FillRect( 60,  88,  60, 103);
	GUI_FillRect( 61, 103,  98, 103);
	GUI_FillRect( 98,  88,  98, 102);
	GUI_FillRect( 70,  88,  70,  94);
	GUI_FillRect( 71,  94,  88,  94);
	GUI_SetColor(0x5A525A);
	GUI_FillRect( 88,  88,  88,  93);
	GUI_SetColor(0x18738B);
	GUI_FillRect( 69,  88,  69,  94);
	GUI_FillRect( 97,  88,  97, 102);
	GUI_SetColor(0x737373);
	GUI_FillRect( 71,  93,  87,  93);
	GUI_SetColor(0x109CC5);
	GUI_FillRect( 89,  88,  89,  94);
	GUI_SetColor(GUI_BLACK);
	//
	// ��������lautering �� boiling֮��Ĺս�����
	//
	GUI_FillRect(141,  88, 141, 103);
	GUI_FillRect(142, 103, 179, 103);
	GUI_FillRect(179,  88, 179, 102);
	GUI_FillRect(151,  88, 151,  94);
	GUI_FillRect(152,  94, 169,  94);
	GUI_SetColor(0x5A525A);
	GUI_FillRect(169,  88, 169,  93);
	GUI_SetColor(0x18738B);
	GUI_FillRect(150,  88, 150,  94);
	GUI_FillRect(178,  88, 178, 102);
	GUI_SetColor(0x737373);
	GUI_FillRect(152,  93, 168,  93);
	GUI_SetColor(0x109CC5);
	GUI_FillRect(170,  88, 170,  94);
	GUI_SetColor(GUI_BLACK);
	//
	// ���߲���boiling �� whirlpoolingֱ�ӵĹս�����
	//
	GUI_FillRect(222,  88, 222, 103);
	GUI_FillRect(223, 103, 260, 103);
	GUI_FillRect(260,  88, 260, 102);
	GUI_FillRect(232,  88, 232,  94);
	GUI_FillRect(233,  94, 250,  94);
	GUI_SetColor(0x5A525A);
	GUI_FillRect(250,  88, 250,  93);
	GUI_SetColor(0x18738B);
	GUI_FillRect(231,  88, 231,  94);
	GUI_FillRect(259,  88, 259, 102);
	GUI_SetColor(0x737373);
	GUI_FillRect(233,  93, 249,  93);
	GUI_SetColor(0x109CC5);
	GUI_FillRect(251,  88, 251,  94);
	GUI_SetColor(GUI_BLACK);
	
	
	//
	// �������7�������Ĺܵ�
	//
	GUI_SetColor(COLOR_BEER);
	//
	// Fill 1
	//
	GUI_FillRect(305,  88, 312, 117);
	GUI_FillRect( 36, 110, 304, 117);
	GUI_FillRect( 36, 118,  43, 123);
	//
	// Fill 2
	//
	GUI_FillRect( 71, 163,  87, 170);
	//
	// Fill 3
	//
	GUI_FillRect(152, 163, 290, 170);
	//
	// Fill 4
	//
	GUI_FillRect(200, 171, 203, 182);
	GUI_FillRect(243, 171, 246, 182);
	GUI_FillRect(287, 171, 290, 182);
	//
	// Fill 5
	//
	GUI_FillRect( 61,  88,  68, 102);
	GUI_FillRect( 69,  95,  96, 102);
	GUI_FillRect( 90,  88,  96,  94);
	//
	// Fill 6
	//
	GUI_FillRect(142,  88, 149, 102);
	GUI_FillRect(150,  95, 177, 102);
	GUI_FillRect(171,  88, 177,  94);
	//
	// Fill 7
	//
	GUI_FillRect(223,  88, 230, 102);
	GUI_FillRect(231,  95, 258, 102);
	GUI_FillRect(252,  88, 258,  94);
	
	//
	// Segger Logo
	//
//	GUI_DrawBitmap(&bmLogo_armflySmall, 236, 121);
}

/*
*********************************************************************************************************
*	�� �� ��: _OverviewDynamic
*	����˵��: ���ƶ�̬ͼ�����ڴ���hWinBk���ػ沿��
*	��    �Σ�pBkState  ����ָ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void _OverviewDynamic(BkState * pBkState) 
{
	GUI_CONST_STORAGE GUI_BITMAP * apbm320_Overview_Mashing[] = 
	{
		&bm320_Overview_Mashing_00,
		&bm320_Overview_Mashing_01,
		&bm320_Overview_Mashing_02,
		&bm320_Overview_Mashing_03,
		&bm320_Overview_Mashing_04,
		&bm320_Overview_Mashing_05,
	};

	GUI_CONST_STORAGE GUI_BITMAP * apbm320_Overview_Lautering[] = 
	{
		&bm320_Overview_Lautering_00,
		&bm320_Overview_Lautering_01,
		&bm320_Overview_Lautering_02,
		&bm320_Overview_Lautering_03,
		&bm320_Overview_Lautering_04,
		&bm320_Overview_Lautering_05,
	};

	GUI_CONST_STORAGE GUI_BITMAP * apbm320_Overview_Boiling[] = 
	{
		&bm320_Overview_Boiling_00,
		&bm320_Overview_Boiling_01,
		&bm320_Overview_Boiling_02,
		&bm320_Overview_Boiling_03,
		&bm320_Overview_Boiling_04,
		&bm320_Overview_Boiling_05,
	};

	GUI_CONST_STORAGE GUI_BITMAP * apbm320_Overview_Whirlpool[] = 
	{
		&bm320_Overview_Whirlpool_00,
		&bm320_Overview_Whirlpool_01,
		&bm320_Overview_Whirlpool_02,
		&bm320_Overview_Whirlpool_03,
		&bm320_Overview_Whirlpool_04,
		&bm320_Overview_Whirlpool_05,
	};

	int       j;
	char *    TextString[5] = {"STM32-V6", "armfly", "Brewing", "Automation", "Demo"};
	const int TextX[5]      = {167,      171,     167,       157,          175};
	GUI_RECT  Rect          = {153, 121, 234, 159};

	/* ��һ�����Ȼ����ĸ�С�ֿ� */
	GUI_SetBkColor(GUI_WHITE);
	GUI_DrawBitmap(apbm320_Overview_Mashing[pBkState->Cnt],     7,  5);
	GUI_DrawBitmap(apbm320_Overview_Lautering[pBkState->Cnt],  88,  5);
	GUI_DrawBitmap(apbm320_Overview_Boiling[pBkState->Cnt],   169,  5);
	GUI_DrawBitmap(apbm320_Overview_Whirlpool[pBkState->Cnt], 250, 21);
	 
	//
	// Moving Arrows
	//
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowDown,   306,  88, 311, 111, pBkState->Cnt,  4, 1);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowLeft,    37, 111, 311, 116, pBkState->Cnt, -4, 0);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowRight,   72, 164,  86, 169, pBkState->Cnt,  4, 0);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowRight,  153, 164, 289, 169, pBkState->Cnt,  4, 0);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowDown_2, 200, 171, 203, 182, pBkState->Cnt,  2, 1);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowDown_2, 243, 171, 246, 182, pBkState->Cnt,  2, 1);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowDown_2, 287, 171, 290, 182, pBkState->Cnt,  2, 1);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowRight,   62,  96,  95, 101, pBkState->Cnt,  4, 0);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowRight,  143,  96, 176, 101, pBkState->Cnt,  4, 0);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowRight,  224,  96, 257, 101, pBkState->Cnt,  4, 0);
	_DrawMovingBitmapClipRect(&bm320_Bubbles,               48, 136,  64, 163, pBkState->Cnt, -2, 1);
	_DrawMovingBitmapClipRect(&bm320_Bubbles,               45, 177,  65, 195, pBkState->Cnt, -2, 1);
	_DrawMovingBitmapClipRect(&bm320_Bubbles,               47, 208,  63, 232, pBkState->Cnt, -2, 1);
	_DrawMovingBitmapClipRect(&bm320_Bubbles,              128, 136, 144, 163, pBkState->Cnt, -2, 1);
	_DrawMovingBitmapClipRect(&bm320_Bubbles,              125, 177, 145, 195, pBkState->Cnt, -2, 1);
	_DrawMovingBitmapClipRect(&bm320_Bubbles,              127, 208, 143, 232, pBkState->Cnt, -2, 1);
	
	//
	// Moving Text
	//
	/*
		����������������Ĳü����Ρ�
		Ĭ������£��ü���������Ϊ���õ� �����⣩��ʾ����С��
		ĳЩ����£�ʹ��ͨ���˺����������õĽ�С�Ĳü����αȽ����á�
		���õľ���Ӧ���ֲ��䣬ֱ��ʹ�ÿ�ָ���ٴε��øú�����
	*/
	GUI_SetClipRect(&Rect);
	GUI_SetFont(&GUI_FontF16B_AA); //GUI_Font16B_ASCII
	GUI_SetColor(0x9c4a31);
	
	for (j = 0; j < 5; j++) 
	{
		(void)_Cnt; /* ��ֹ���� */
		/* ����������ʾ��ǰ��ѡ������ָ���ַ�����X��С */
		_Cnt = GUI_GetStringDistX(TextString[j]);
		GUI_DispStringAt(TextString[j], TextX[j], pBkState->TextY[j]);
	}

	GUI_SetClipRect(NULL);
}

/*
*********************************************************************************************************
*	�� �� ��: _BkOnPaint
*	����˵��: ���������ػ溯��
*	��    �Σ�pBkState  ����ָ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void _BkOnPaint(BkState * pBkState) 
{
	if (pBkState->DrawBk) 
	{
		_OverviewStatic();
	}
	_OverviewDynamic(pBkState);
}

/*
*********************************************************************************************************
*	�� �� ��: _IncPosBk
*	����˵��: �����ı�����ʾλ�ã��Ӷ�ʵ�ֹ�����Ч��
*	��    �Σ�pBkState  ����ָ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void _IncPosBk(BkState * pBkState) 
{
	int j;

	pBkState->Cnt = (pBkState->Cnt < 5) ? pBkState->Cnt + 1 : 0;
	for (j = 0; j < 5; j++) 
	{
		if (pBkState->TextY[j] < 107) 
		{
			pBkState->TextY[j] = 200;
		} 
		else 
		{
			pBkState->TextY[j]--;
		}
	}
}

/*
*********************************************************************************************************
*	�� �� ��: _cbBk
*	����˵��: ����hWinBk�ص�����
*	��    �Σ�pBkState  ����ָ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
extern	WM_HWIN h_calender;
int show_Flag = 1;
static void _cbBk(WM_MESSAGE * pMsg) 
{
	static BkState BkState = 
	{
		{161, 178, 195, 212, 229},
		0,
		1
	};
	int NCode;
	int Id;
	int i;
	switch (pMsg->MsgId) 
	{
		case APP_DRAW:
			BkState.DrawBk = 1;
			break;
		
		case APP_HIDE:
			BkState.DrawBk = 0;
			break;
		
		case APP_NEXT_FRAME:
			_IncPosBk(&BkState);
			break;
		
		case WM_PAINT:
			_BkOnPaint(&BkState);
			break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
			 case ID_BUTTON_0: // Notifications sent by 'Status'
      switch(NCode) {
				case WM_NOTIFICATION_CLICKED:
					// USER START (Optionally insert code for reacting on notification message)
					// USER END
					break;
				case WM_NOTIFICATION_RELEASED:
					WM_HideWindow(pMsg->hWin);
					WM_ShowWindow( h_calender);
//				WM_BringToTop(h_calender);
//				WM_ShowWindow( h_calender);
				show_Flag = 0;
				//	WM_DeleteWindow(pMsg->hWin);
					//SettingWindow();
					// USER END
					break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
      }
      break;
		}
		break;
	}
}

/*
*********************************************************************************************************
*	�� �� ��: MainTask
*	����˵��: GUI������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
WM_HWIN            hWinBk;
void MainTask(void) 
{

	int                i;
	
	
	/* ��ʼ�� */
	GUI_Init();
	 
	/*
	 ���ڶ໺��ʹ����ڴ��豸������˵��
	   1. ʹ�ܶ໺���ǵ��õ����º������û�Ҫ��LCDConf_Lin_Template.c�ļ��������˶໺�壬���ô˺�������Ч��
		  WM_MULTIBUF_Enable(1);
	   2. ����ʹ��ʹ���ڴ��豸�ǵ��ú�����WM_SetCreateFlags(WM_CF_MEMDEV);
	   3. ���emWin�����ö໺��ʹ����ڴ��豸��֧�֣���ѡһ���ɣ����������ѡ��ʹ�ö໺�壬ʵ��ʹ��
		  STM32F429BIT6 + 32λSDRAM + RGB565/RGB888ƽ̨���ԣ��໺�������Ч�Ľ��ʹ����ƶ����߻���ʱ��˺��
		  �У�����Ч����������ԣ�ͨ��ʹ�ܴ���ʹ���ڴ��豸���������ġ�
	   4. ����emWin����Ĭ���ǿ��������塣
	*/
	//WM_MULTIBUF_Enable(1);
	
	/*
       ����У׼����Ĭ����ע�͵��ģ���������ҪУ׼������������У׼������û���ҪУ׼�������Ļ���ִ��
	   �˺������ɣ��Ὣ����У׼�������浽EEPROM���棬�Ժ�ϵͳ�ϵ���Զ���EEPROM������ء�
	*/
    //TOUCH_Calibration();

	/* �������洰�ڵı���ɫ */
	WM_SetDesktopColor(GUI_BLUE);
	
		/* ������������ 
	   1. ����hWinBk������ʾ��һ����̬Ч��
	   2. ����hWinMashing������ʾ�ڶ�����̬Ч��
	*/
	hWinBk      = WM_CreateWindow(0, 
	                              0,   
	                              480, 
	                              320, 
								  WM_CF_SHOW,  
								  _cbBk,      
								  0);
//
	
	
		WM_DisableMemdev(hWinBk);
		
		
		BUTTON_CreateEx(350,20,80,40,hWinBk, WM_CF_SHOW, 0,ID_BUTTON_0);
		WM_BringToTop(hWinBk);
		
		/* ����hWinBk��ʾ��֮�󣬻ص��������ػ沿�ֵľ�̬ͼƬ������Ҫ��ʾ�� */
		WM_SendMessageNoPara   (hWinBk,      APP_DRAW);
		WM_Exec();
		WM_SendMessageNoPara   (hWinBk, APP_HIDE);
	while (1) 
	{
		if ( show_Flag == 0)
		{
			WM_Exec();
		}
		else
		{
			for (i = 0; i < 100; i++) 
			{
				GUI_Delay(60);
				WM_SendMessageNoPara(hWinBk, APP_NEXT_FRAME);
				WM_InvalidateWindow (hWinBk);
			}	
		}
	}
}

