/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.22                          *
*        Compiled Jul  4 2013, 15:16:01                              *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG               *
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
#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "str.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_TEXT_0 (GUI_ID_USER + 0x01)
#define ID_TEXT_1 (GUI_ID_USER + 0x02)
#define ID_TEXT_2 (GUI_ID_USER + 0x03)
#define ID_TEXT_3 (GUI_ID_USER + 0x04)
#define ID_TEXT_4 (GUI_ID_USER + 0x05)

#define ID_SLIDER_0 (GUI_ID_USER + 0x14)
#define ID_SLIDER_1 (GUI_ID_USER + 0x15)
#define ID_SLIDER_2 (GUI_ID_USER + 0x16)
#define ID_SLIDER_3 (GUI_ID_USER + 0x17)

#define ID_SPINBOX_0 (GUI_ID_USER + 0x21)
#define ID_SPINBOX_1 (GUI_ID_USER + 0x22)
#define ID_SPINBOX_2 (GUI_ID_USER + 0x23)
#define ID_SPINBOX_3 (GUI_ID_USER + 0x24)
#define ID_SPINBOX_4 (GUI_ID_USER + 0x25)

#define ID_BUTTON_0 (GUI_ID_USER + 0x31)
#define ID_BUTTON_1 (GUI_ID_USER + 0x32)
#define ID_BUTTON_2 (GUI_ID_USER + 0x33)
#define ID_BUTTON_3 (GUI_ID_USER + 0x34)

#define ID_RADIO_0 (GUI_ID_USER + 0x41)
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
	
  { TEXT_CreateIndirect, "temperature", ID_TEXT_0, 20, 15, 140, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Single-click", ID_TEXT_1, 20, 82, 140, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "double-click", ID_TEXT_2, 20, 149, 140, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "longpress", ID_TEXT_3, 20, 216, 140, 30, 0, 0x0, 0 },	
  { TEXT_CreateIndirect, "longpress", ID_TEXT_4, 350, 15, 140, 30, 0, 0x0, 0 },	
	
  { SLIDER_CreateIndirect, "Slider", ID_SLIDER_0, 20, 47, 300, 25, 0, 0x0, 0 },
  { SLIDER_CreateIndirect, "Slider", ID_SLIDER_1, 20, 114, 300, 25, 0, 0x0, 0 },
  { SLIDER_CreateIndirect, "Slider", ID_SLIDER_2, 20, 181, 300, 25, 0, 0x0, 0 },
  { SLIDER_CreateIndirect, "Slider", ID_SLIDER_3, 20, 248, 300, 25, 0, 0x0, 0 },	
	
  { SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_0, 150, 13, 100, 30, 0, 0x0, 0 },
  { SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_1, 150, 80, 100, 30, 0, 0x0, 0 },
  { SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_2, 150, 147, 100, 30, 0, 0x0, 0 },
	
  { SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_3, 150, 214, 100, 30, 0, 0x0, 0 },	
	
//  { BUTTON_CreateIndirect, "Upgrade", ID_BUTTON_0, 350, 20, 80, 40, 0, 0x0, 0 },	
//  { BUTTON_CreateIndirect, "Time", ID_BUTTON_1, 350, 90, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Cancel", ID_BUTTON_2, 350, 160, 80, 40, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Confirm", ID_BUTTON_3, 350, 230, 80, 40, 0, 0x0, 0 },
	
	{ SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_4, 350, 60, 80, 60, 0, 0, 0 },
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
extern GUI_CONST_STORAGE GUI_FONT GUI_FontB24;
extern WM_HWIN CalenderWindow(void);
extern WM_HWIN SelectWindow(void);
extern WM_HWIN CreateSoftWare(void);
extern WM_HWIN CreateWindow(void);
extern const char *HZStr[];
static uint16_t slider_temp;



/*
SetFont(hItem,Get_Font(Set.language));
SetText(hItem,String[Find_Str("")][Set.language]);
*/
// USER END

/*********************************************************************
*
*       _cbDialog
*/

static void _cbDialog(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
  int NCode;
  int Id;
	uint8_t i;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
		case WM_INIT_DIALOG:
			hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
			SLIDER_SetRange(hItem, 0, 60);
			SLIDER_SetValue(hItem,Set.circletime);
			
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_1);
			SLIDER_SetRange(hItem, 0, 60);
			SLIDER_SetValue(hItem,Set.circleinterval);

			hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_2);
			SLIDER_SetRange(hItem, 1, 10);
			SLIDER_SetValue(hItem,Set.circlespeed);		

			hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_3);
			SLIDER_SetRange(hItem, 1, 10);
			SLIDER_SetValue(hItem,Set.outspeed);			
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
			SPINBOX_SetRange(hItem, 0, 60);
			SPINBOX_SetFont(hItem,GUI_FONT_20B_1);
			SPINBOX_SetEdge(hItem,SPINBOX_EDGE_CENTER);
			SPINBOX_SetButtonSize(hItem,20);
			SPINBOX_SetValue(hItem,Set.circletime);
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_1);
			SPINBOX_SetFont(hItem,GUI_FONT_20B_1);
			SPINBOX_SetRange(hItem, 0, 60);
			SPINBOX_SetEdge(hItem,SPINBOX_EDGE_CENTER);
			SPINBOX_SetButtonSize(hItem,20);
			SPINBOX_SetValue(hItem,Set.circleinterval);
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_2);
			SPINBOX_SetRange(hItem, 1, 10);	
			SPINBOX_SetFont(hItem,GUI_FONT_20B_1);	
			SPINBOX_SetEdge(hItem,SPINBOX_EDGE_CENTER);
			SPINBOX_SetButtonSize(hItem,20);
			SPINBOX_SetValue(hItem,Set.circlespeed);
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_3);
			SPINBOX_SetRange(hItem, 1, 10);	
			SPINBOX_SetFont(hItem,GUI_FONT_20B_1);	
			SPINBOX_SetEdge(hItem,SPINBOX_EDGE_CENTER);
			SPINBOX_SetButtonSize(hItem,20);
			SPINBOX_SetValue(hItem,Set.outspeed);
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_4);
			SPINBOX_SetRange(hItem, 0, 10);	
			SPINBOX_SetFont(hItem,GUI_FONT_20B_1);	
			SPINBOX_SetEdge(hItem,SPINBOX_EDGE_RIGHT);
			SPINBOX_SetButtonSize(hItem,40);
			SPINBOX_SetValue(hItem,Set.lighttime);
/*
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
			BUTTON_SetFont(hItem, GUI_FONT_20B_1);

			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetFont(hItem,GUI_FONT_20_1);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
			BUTTON_SetFont(hItem,GUI_FONT_20_1);			
*/
/*
SetFont(hItem,Get_Font(Set.language));
SetText(hItem,String[Find_Str("")][Set.language]);
*/
	/*		
			for(i = 0;i < 2;i++)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2+i);
				
				if (Lang_Flag)
				{
					BUTTON_SetFont(hItem,&GUI_FontB24);	
					BUTTON_SetText(hItem,HZStr[6-i]);
				}
				else
				{
					BUTTON_SetFont(hItem,GUI_FONT_20B_1);	
				}
			}
			
			for(i = 0;i < 3;i++)
			{	
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0+i);
				if (Lang_Flag)
				{
					TEXT_SetFont(hItem,&GUI_FontB24);
					if(i == 0)
						TEXT_SetText(hItem,HZStr[1]);
					else
						TEXT_SetText(hItem,HZStr[2+i]);
				}
				else
				{
					TEXT_SetFont(hItem,GUI_FONT_20B_1);
				}
			}
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
			TEXT_SetFont(hItem,GUI_FONT_20B_1);
		*/	
		
			for(i = 0;i < 2;i++)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2+i);
				
				BUTTON_SetFont(hItem,Set.language?&GUI_FontB24:&GUI_Font20_1);
				BUTTON_SetText(hItem,String[Find_Str("Cancel")+i][Set.language]);
			}
			
			for(i = 0;i < 4;i++)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0+i);
				
				TEXT_SetFont(hItem,Set.language?&GUI_FontB24:&GUI_Font20_1);
				//TEXT_SetText(hItem,String[Find_Str("")][Set.language]);
				TEXT_SetText(hItem,String[Find_Str("Circle Time")+i][Set.language]);
			}
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
			TEXT_SetFont(hItem,Set.language?&GUI_FontB24:&GUI_Font20_1);
			TEXT_SetText(hItem,String[Find_Str("Screen Time")][Set.language]);
			
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);
/*			
			RADIO_SetFont(hItem,GUI_FONT_20_1);
			RADIO_SetText(hItem,"English",0);
			RADIO_SetText(hItem,"Chinese",1);*/
			
			RADIO_SetFont(hItem,Set.language?&GUI_FontB24:&GUI_Font20_1);
			RADIO_SetText(hItem,String[Find_Str("English")][Set.language],0);
			RADIO_SetText(hItem,String[Find_Str("Chinese")][Set.language],1);
			RADIO_SetValue(hItem,Set.language);
			break;
		case WM_PAINT:
			GUI_DrawGradientV(0,0,479,319,GUI_LIGHTBLUE,GUI_BLUE);
			GUI_SetTextMode(GUI_TM_TRANS);
			GUI_SetFont(GUI_FONT_32B_1);
			GUI_SetColor(GUI_GRAY);
			GUI_DispStringHCenterAt("dotcom",240,65);
		
			GUI_SetColor(GUI_YELLOW);
			GUI_SetFont(GUI_FONT_24B_1);
			GUI_DispStringAt("Sec",270,15);
			GUI_DispStringAt("Min",270,82);
		
			break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_SLIDER_0: // Notifications sent by 'Slider'
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
					hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
					slider_temp = SLIDER_GetValue(hItem);		
					SPINBOX_SetValue(WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0),slider_temp);
			
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_1: // Notifications sent by 'Slider'
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
					hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_1);
					slider_temp = SLIDER_GetValue(hItem);

					SPINBOX_SetValue(WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_1),slider_temp);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_2: // Notifications sent by 'Slider'
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
					hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_2);
					slider_temp = SLIDER_GetValue(hItem);
			
					SPINBOX_SetValue(WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_2),slider_temp);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_3: // Notifications sent by 'Slider'
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
					hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_3);
					slider_temp = SLIDER_GetValue(hItem);
			
					SPINBOX_SetValue(WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_3),slider_temp);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SPINBOX_0: // Notifications sent by 'Spinbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
					hItem = WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_0 );
					slider_temp = SPINBOX_GetValue(hItem);
					SLIDER_SetValue(WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0),slider_temp);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SPINBOX_1: // Notifications sent by 'Spinbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
					hItem = WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_1 );
					slider_temp = SPINBOX_GetValue(hItem);
					SLIDER_SetValue(WM_GetDialogItem(pMsg->hWin, ID_SLIDER_1),slider_temp);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SPINBOX_2: // Notifications sent by 'Spinbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
					hItem = WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_2);
					slider_temp = SPINBOX_GetValue(hItem);
			
					SLIDER_SetValue(WM_GetDialogItem(pMsg->hWin, ID_SLIDER_2),slider_temp);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
		 case ID_SPINBOX_3: // Notifications sent by 'Spinbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
					hItem = WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_3);
					slider_temp = SPINBOX_GetValue(hItem);
			
					SLIDER_SetValue(WM_GetDialogItem(pMsg->hWin, ID_SLIDER_3),slider_temp);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = pMsg->hWin;
				WM_DeleteWindow(hItem);
				CreateSoftWare();
			
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;			
    case ID_BUTTON_1: // Notifications sent by 'Button'
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
    case ID_BUTTON_2: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = pMsg->hWin;
				WM_DeleteWindow(hItem);
				SelectWindow();

        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
		case ID_BUTTON_3: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)

				Set.circletime = SPINBOX_GetValue(WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_0 ));
				Set.circleinterval = SPINBOX_GetValue(WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_1));			
				Set.circlespeed = SPINBOX_GetValue(WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_2 ));
				Set.outspeed= SPINBOX_GetValue(WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_3 ));

				Set.lighttime = SPINBOX_GetValue(WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_4 ));			
				Setting_Save();
				hItem = pMsg->hWin;
				WM_DeleteWindow(hItem);
				SelectWindow();
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
		case ID_RADIO_0: // Notifications sent by 'Radio'
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
WM_HWIN SettingWindow2(void);
WM_HWIN SettingWindow2(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/