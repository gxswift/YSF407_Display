/**
  ******************************************************************************
  * 文件名程: main.c 
  * 作    者: 硬石嵌入式开发团队
  * 版    本: V1.0
  * 编写日期: 2017-03-30
  * 功    能: emwin各个功能的实现
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
#include "MainTask.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0   (GUI_ID_USER + 0x01)
#define ID_BUTTON_1   (GUI_ID_USER + 0x02)

/* 私有变量 ------------------------------------------------------------------*/
/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/
/**
  * 函数功能: GUI_WIDGET_CREATE_INFOl类型数组
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = 
{
	{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 320, 480, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 70, 37, 159, 49, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 70, 127, 159, 46, 0, 0x0, 0 },
};
/**
  * 函数功能: 对话框回调函数
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
static void _cbDialog(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	int     NCode;
	int     Id;
    switch (pMsg->MsgId) 
    {
      case WM_INIT_DIALOG:
			//
			// 初始化 'Framewin'
			//
			hItem = pMsg->hWin;
			FRAMEWIN_SetFont(hItem, GUI_FONT_32B_ASCII);
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetText(hItem, "YSF4");
      //
      // 初始化按钮控件
      //
      hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
      BUTTON_SetFont(hItem, GUI_FONT_24B_ASCII);
      BUTTON_SetText(hItem, "LED1");
      //
      // 初始化按钮控件
      //
      hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
      BUTTON_SetFont(hItem, GUI_FONT_24B_ASCII);
      BUTTON_SetText(hItem, "LED2");

			break;
		
      case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch(Id) 
        {
          case ID_BUTTON_0: 
          switch(NCode) 
          {
            case WM_NOTIFICATION_CLICKED:
              LED1_ON;
              break;

            case WM_NOTIFICATION_RELEASED:
              LED1_OFF;
              break;
          }
          break;
          
          case ID_BUTTON_1: 
          switch(NCode) 
          {
            case WM_NOTIFICATION_CLICKED:             
              LED2_ON;
              break;

            case WM_NOTIFICATION_RELEASED:
              LED2_OFF;
              break;
          }
          break;
        }
        break;
         
     default:
			WM_DefaultProc(pMsg);
			break;
    }
}


/**
  * 函数功能: GUI功能函数
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void MainTask(void) 
{	
  GUI_Init();
  
  LCD_BK_ON();
  
  GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialog, WM_HBKWIN, 0, 0);
 
	while(1)
	{	
		GUI_Delay(10);
	}
}

/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
