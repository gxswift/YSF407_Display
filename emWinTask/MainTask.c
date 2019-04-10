/*
*********************************************************************************************************
*	                                  
*	模块名称 : 酿造机过程动态演示
*	文件名称 : MainTask.c
*	版    本 : V1.0
*	说    明 : 实验内容
*              1. 这个工程主要是动态过程的演示，无需使用触摸功能。
*              2. 主要演示了两个动态过程，每个过程都是建立在一个窗口上，通过设置
*                 窗口的显示层从而实现轮流显示。
*              3. 刷新的时候，将静态图和动态图分开，只需刷新动态图即可。
*              4. 注意函数GUI_SetClipRect的使用。
*              
*	修改记录 :
*		版本号   日期         作者          说明
*		V1.0    2016-11-26   Eric2013  	    首版    
*                                     
*	Copyright (C), 2015-2020, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#include "MainTask.h"


/*
*********************************************************************************************************
*                                         宏定义
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
*                                         变量
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
*	函 数 名: _DrawMovingBitmapClipRect
*	功能说明: 这个函数的主要功能是实现位图的动态移动效果，并通过函数GUI_SetClipRect()限制输出的裁剪矩形
*             默认情况下，裁剪区域限制为配置的 （虚拟）显示器大小。
*             某些情况下，使用通过此函数可以设置的较小的裁剪矩形比较有用。
*             引用的矩形应保持不变，直到使用空指针再次调用该函数。
*	形    参：pBitmap     位图地址
*             ClipRectX0  裁剪矩形区首地址
*             ClipRectY0  裁剪矩形区首地址
*             ClipRectX1  裁剪矩形区结束地址
*             ClipRectY1  裁剪矩形区结束地址 
* 			  Step		  Number of current step
*			  StepDist	  Distance of a single step, use negative values to turn direction	
*             MovDir	  0 == x; 1 == y;								 
*	返 回 值: 无
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
	
	/* 根据X轴或者Y轴的递增方向确定位图的起始点，并确定每次的增长值 */
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
	
	/* 确定位图的结束点 */
	x1 = x0 + pBitmap->XSize - 1;
	y1 = y0 + pBitmap->YSize - 1;
	
	/* 根据设置的显示区域，用位图将显示区域填充满 */
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
*	函 数 名: _OverviewStatic
*	功能说明: 绘制静态图，用于窗口hWinBk的重绘部分
*	形    参：无
*	返 回 值: 无
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
	// 第一步： whirlpooling 和 fermenting之间的长连接管
	//
	GUI_FillRect(304,  88, 304, 109);
	GUI_FillRect(313,  88, 313, 118);
	GUI_FillRect( 35, 109, 303, 109);
	GUI_FillRect( 44, 118, 312, 118);
	GUI_FillRect( 35, 110,  35, 123);
	GUI_FillRect( 44, 119,  44, 123);
	//
	// 第二步：fermenting和storage之间的短连接管
	//
	GUI_FillRect( 71, 162,  87, 162);
	GUI_FillRect( 71, 171,  87, 171);
	//
	// 第三步：torage 和 barrels之间的长连接管
	//
	GUI_FillRect(152, 162, 291, 162);
	GUI_FillRect(152, 171, 199, 171);
	GUI_FillRect(204, 171, 242, 171);
	GUI_FillRect(247, 171, 286, 171);
	//
	// 第四步：storage 和 barrels直接的短管连接
	//
	GUI_FillRect(199, 172, 199, 182);
	GUI_FillRect(204, 172, 204, 182);
	GUI_FillRect(242, 172, 242, 182);
	GUI_FillRect(247, 172, 247, 182);
	GUI_FillRect(286, 172, 286, 182);
	GUI_FillRect(291, 163, 291, 182);
	//
	// 第五步：mashing 和 lautering之间的拐角链接
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
	// 第六步：lautering 和 boiling之间的拐角链接
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
	// 第七步：boiling 和 whirlpooling直接的拐角连接
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
	// 填充上面7部建立的管道
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
*	函 数 名: _OverviewDynamic
*	功能说明: 绘制动态图，用于窗口hWinBk的重绘部分
*	形    参：pBkState  参数指针
*	返 回 值: 无
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

	/* 第一步：先绘制四个小仓库 */
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
		设置用于限制输出的裁剪矩形。
		默认情况下，裁剪区域限制为配置的 （虚拟）显示器大小。
		某些情况下，使用通过此函数可以设置的较小的裁剪矩形比较有用。
		引用的矩形应保持不变，直到使用空指针再次调用该函数。
	*/
	GUI_SetClipRect(&Rect);
	GUI_SetFont(&GUI_FontF16B_AA); //GUI_Font16B_ASCII
	GUI_SetColor(0x9c4a31);
	
	for (j = 0; j < 5; j++) 
	{
		(void)_Cnt; /* 防止警告 */
		/* 返回用于显示当前所选字体中指定字符串的X大小 */
		_Cnt = GUI_GetStringDistX(TextString[j]);
		GUI_DispStringAt(TextString[j], TextX[j], pBkState->TextY[j]);
	}

	GUI_SetClipRect(NULL);
}

/*
*********************************************************************************************************
*	函 数 名: _BkOnPaint
*	功能说明: 背景窗口重绘函数
*	形    参：pBkState  参数指针
*	返 回 值: 无
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
*	函 数 名: _IncPosBk
*	功能说明: 调整文本的显示位置，从而实现滚动的效果
*	形    参：pBkState  参数指针
*	返 回 值: 无
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
*	函 数 名: _cbBk
*	功能说明: 窗口hWinBk回调函数
*	形    参：pBkState  参数指针
*	返 回 值: 无
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
*	函 数 名: MainTask
*	功能说明: GUI主函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
WM_HWIN            hWinBk;
void MainTask(void) 
{

	int                i;
	
	
	/* 初始化 */
	GUI_Init();
	 
	/*
	 关于多缓冲和窗口内存设备的设置说明
	   1. 使能多缓冲是调用的如下函数，用户要在LCDConf_Lin_Template.c文件中配置了多缓冲，调用此函数才有效：
		  WM_MULTIBUF_Enable(1);
	   2. 窗口使能使用内存设备是调用函数：WM_SetCreateFlags(WM_CF_MEMDEV);
	   3. 如果emWin的配置多缓冲和窗口内存设备都支持，二选一即可，且务必优先选择使用多缓冲，实际使用
		  STM32F429BIT6 + 32位SDRAM + RGB565/RGB888平台测试，多缓冲可以有效的降低窗口移动或者滑动时的撕裂
		  感，并有效的提高流畅性，通过使能窗口使用内存设备是做不到的。
	   4. 所有emWin例子默认是开启三缓冲。
	*/
	//WM_MULTIBUF_Enable(1);
	
	/*
       触摸校准函数默认是注释掉的，电阻屏需要校准，电容屏无需校准。如果用户需要校准电阻屏的话，执行
	   此函数即可，会将触摸校准参数保存到EEPROM里面，以后系统上电会自动从EEPROM里面加载。
	*/
    //TOUCH_Calibration();

	/* 设置桌面窗口的背景色 */
	WM_SetDesktopColor(GUI_BLUE);
	
		/* 创建两个窗口 
	   1. 窗口hWinBk用于演示第一幅动态效果
	   2. 窗口hWinMashing用于演示第二个动态效果
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
		
		/* 窗口hWinBk显示了之后，回调函数中重绘部分的静态图片不再需要显示了 */
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

