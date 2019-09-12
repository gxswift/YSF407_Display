/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "rtc.h"
#include "stm32f4xx_hal.h"	
#include "str.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0 (GUI_ID_USER + 0x02)
#define ID_BUTTON_1 (GUI_ID_USER + 0x03)
#define ID_BUTTON_2 (GUI_ID_USER + 0x04)

#define ID_CHECKBOX_0 (GUI_ID_USER + 0x05)

#define ID_SPINBOX_0 (GUI_ID_USER + 0x07)
#define ID_SPINBOX_1 (GUI_ID_USER + 0x08)
#define ID_SPINBOX_2 (GUI_ID_USER + 0x09)
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 30, 480, 320, 0, 0x0, 0 },
	{ SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_0, 100, 240, 55, 40, 0, 0x0, 0 },
  { SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_1, 170, 240, 55, 40, 0, 0x0, 0 },
  { SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_2, 240, 240, 55, 40, 0, 0x0, 0 },
	
  { CHECKBOX_CreateIndirect, "check", ID_CHECKBOX_0, 345, 40, 100, 20, 0, 0x0, 0 },
	
//	{ BUTTON_CreateIndirect, "Upgrade", ID_BUTTON_0, 350, 70, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "EXIT", ID_BUTTON_1, 350, 160, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "OK", ID_BUTTON_2, 350, 230, 80, 40, 0, 0x0, 0 },

  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END
extern WM_HWIN CreateWin1(void);
extern WM_HWIN SettingWindow(void);
extern WM_HWIN SelectWindow(void);


CALENDAR_DATE Date;

	int Hour;
	int Min;
	int Sec;

/*********************************************************************
*
*       _cbDialog
*/
extern WM_HWIN            hWinBk;

//uint8_t RTC_SetFlag = 0;

extern	RTC_TimeTypeDef RTC_Time;
extern 	RTC_DateTypeDef RTC_Date;
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  static WM_HWIN hCalen;
	int i;
	GUI_HMEM H_QR;

	RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_PAINT:
		GUI_DrawGradientV(0,0,479,319,GUI_LIGHTBLUE,GUI_BLUE);
	
	  GUI_SetTextMode(GUI_TM_TRANS);
	  GUI_SetColor(GUI_BLACK);
	  GUI_SetFont(&GUI_Font20_1);
	

	  GUI_DispStringAt(":", 160, 250);
	  GUI_DispStringAt(":", 230, 250);
	
		GUI_SetFont(Set.language?&GUI_FontB24:&GUI_Font20_1);
		GUI_DispStringAt(String[Find_Str("Time")][Set.language],30,250);	
	
//	H_QR = GUI_QR_Create("http://www.baidu.com",3,GUI_QR_ECLEVEL_L,0);
//	GUI_QR_Draw(H_QR,320,200);
	  break;
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Listwheel'
    //
	/*
			for(i = 0;i < 3;i++)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0+i);
				BUTTON_SetFont(hItem,GUI_FONT_20_1);	
			}
	*/
			for(i = 0;i < 2;i++)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1+i);
				
				BUTTON_SetFont(hItem,Set.language?&GUI_FontB24:&GUI_Font20_1);
				BUTTON_SetText(hItem,String[Find_Str("Cancel")+i][Set.language]);
			}
	
			hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
			SPINBOX_SetRange(hItem, 0, 23);
			SPINBOX_SetFont(hItem,GUI_FONT_20B_1);
			//SPINBOX_SetEdge(hItem,SPINBOX_EDGE_RIGHT);
			SPINBOX_SetButtonSize(hItem,25);
			SPINBOX_SetValue(hItem,RTC_Time.Hours);
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_1);
			SPINBOX_SetFont(hItem,GUI_FONT_20B_1);
			SPINBOX_SetRange(hItem, 0, 59);
			SPINBOX_SetButtonSize(hItem,25);
			SPINBOX_SetValue(hItem,RTC_Time.Minutes);
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_2);
			SPINBOX_SetRange(hItem, 0, 59);	
			SPINBOX_SetFont(hItem,GUI_FONT_20B_1);	
			SPINBOX_SetButtonSize(hItem,25);
			SPINBOX_SetValue(hItem,RTC_Time.Seconds);

			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
			
				CHECKBOX_SetFont(hItem,Set.language?&GUI_FontB24:&GUI_Font20_1);
				CHECKBOX_SetText(hItem,String[Find_Str("Visible")][Set.language]);
		/*		
			CHECKBOX_SetFont(hItem,GUI_FONT_20B_1);
			CHECKBOX_SetText(hItem, "visible");
			*/
			CHECKBOX_SetState(hItem,Set.visable);
			
		
			CALENDAR_SetDefaultFont(CALENDAR_FI_CONTENT,&GUI_Font20B_1);
			CALENDAR_SetDefaultFont(CALENDAR_FI_HEADER, &GUI_Font20_1);

			CALENDAR_SetDefaultSize(CALENDAR_SI_HEADER,30);
			CALENDAR_SetDefaultSize(CALENDAR_SI_CELL_X,40);
			CALENDAR_SetDefaultSize(CALENDAR_SI_CELL_Y,25);

			hCalen = CALENDAR_Create(pMsg->hWin,20,20,2000+RTC_Date.Year,RTC_Date.Month,RTC_Date.Date,2,0,0);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
			case ID_CHECKBOX_0: // Notifications sent by 'check'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
		 case ID_BUTTON_0: // Notifications sent by 'return'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
			

        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'return'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
			
		  WM_DeleteWindow(pMsg->hWin);
		  SelectWindow();
		
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'OK'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				// hCalen

				CALENDAR_GetSel(hCalen, &Date);
				CALENDAR_SetDate(hCalen, &Date);
			hItem = WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_0 );
				sTime.Hours = SPINBOX_GetValue(hItem);
			hItem = WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_1 );
				sTime.Minutes = SPINBOX_GetValue(hItem);
			hItem = WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_2 );
				sTime.Seconds = SPINBOX_GetValue(hItem);
				sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
				sTime.StoreOperation = RTC_STOREOPERATION_RESET;
				if(HAL_OK!=HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN))
				{
					printf("Time set error\r\n");
				};
			
				sDate.WeekDay = 0;
				sDate.Month = Date.Month;
				sDate.Date = Date.Day;
				sDate.Year = Date.Year-2000;
				if(HAL_OK!=HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN))
				{
					printf("Data set error\r\n");
				}

			hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
			Set.visable = CHECKBOX_GetState(hItem);
			Setting_Save();
				// WM_SendMessageNoPara(WIN_Header, DATE_DIS);
				WM_InvalidateWindow(pMsg->hWin);
			WM_DeleteWindow(pMsg->hWin);
		  SelectWindow(); 
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
	
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/
WM_HWIN CalenderWindow(void);
WM_HWIN CalenderWindow(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
