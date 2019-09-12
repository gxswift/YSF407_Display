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
#include "str.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_RADIO_0 (GUI_ID_USER + 0x01)
#define ID_PROGBAR_0 (GUI_ID_USER + 0x02)
#define ID_BUTTON_0 (GUI_ID_USER + 0x03)
#define ID_BUTTON_1 (GUI_ID_USER + 0x04)
#define ID_BUTTON_2 (GUI_ID_USER + 0x05)
#define ID_SLIDER_0 (GUI_ID_USER + 0x06)
#define ID_SPINBOX_0 (GUI_ID_USER + 0x07)

// USER START (Optionally insert additional defines)
#define MY_MESSAGE_OUT (WM_USER + 0)
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
 /* { RADIO_CreateIndirect, "Radio", ID_RADIO_0, 111, 15, 100, 45, 0, 0x1402, 0 },*/
  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_0, 40, 130, 400, 20, 0, 0x0, 0 },
	
//	 { BUTTON_CreateIndirect, "Status", ID_BUTTON_0, 350, 90, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Setting", ID_BUTTON_1, 350, 230, 80, 40, 0, 0x0, 0 },
	
  { BUTTON_CreateIndirect, "Start", ID_BUTTON_2, 190, 170, 100, 100, 0, 0x0, 0 },
 { SLIDER_CreateIndirect, "Slider", ID_SLIDER_0, 40, 60, 400, 40, 0, 0x0, 0 },
 
  { SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_0, 200, 15, 90, 35, 0, 0x0, 0 },
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

extern const char *HZStr[];

extern WM_HWIN CreateWindow(void);
extern WM_HWIN CreateSoftWare(void);

extern GUI_CONST_STORAGE GUI_BITMAP bmstart;
extern GUI_CONST_STORAGE GUI_BITMAP bmstop;

static uint16_t slider_temp;

uint16_t out_vol;

// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
  int NCode;
  int Id;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
		case WM_USER:
			//WM_SendMessageNoPara(H_Hand,WM_USER);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);	
			PROGBAR_SetMinMax(hItem, 0, Set.volhand);		
			PROGBAR_SetValue(hItem,Set.volhand - Time.out);
			if (Time.out == 0)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
				BUTTON_SetTextColor(hItem,BUTTON_CI_UNPRESSED,GUI_GREEN);
				BUTTON_SetText(hItem,String[Find_Str("Start")][Set.language]);
				BUTTON_SetBitmap(hItem,BUTTON_BI_PRESSED,&bmstart);
				BUTTON_SetBitmap(hItem,BUTTON_BI_UNPRESSED,&bmstart);
			}
			
			break;
		case WM_INIT_DIALOG:
	//	printf("slider_temp = %d\r\n",slider_temp);
			State.hwinflag = 1;
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
			SLIDER_SetRange(hItem, 0, 2000);
			SLIDER_SetValue(hItem,Set.volhand);
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
			SPINBOX_SetRange(hItem, 0, 2000);
			SPINBOX_SetFont(hItem,GUI_FONT_20B_1);
			SPINBOX_SetEdge(hItem,SPINBOX_EDGE_CENTER);
			SPINBOX_SetButtonSize(hItem,20);
			SPINBOX_SetValue(hItem,Set.volhand);
/*			
		hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);
		RADIO_SetText(hItem,"English",0);
		RADIO_SetText(hItem,"hanzi",1);
	*/
/*	
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetFont(hItem,&GUI_FontB24);	
			BUTTON_SetText(hItem,HZStr[10]);
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
			BUTTON_SetFont(hItem,&GUI_FontB24);	
			BUTTON_SetText(hItem,HZStr[11]);
			
				if (out_flag == 0)
				{
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
					BUTTON_SetTextColor(hItem,BUTTON_CI_UNPRESSED,GUI_GREEN);
					BUTTON_SetFont(hItem,&GUI_FontB24);	
					BUTTON_SetText(hItem,HZStr[8]);
					BUTTON_SetBitmap(hItem,BUTTON_BI_PRESSED,&bmstart);
					BUTTON_SetBitmap(hItem,BUTTON_BI_UNPRESSED,&bmstart);
				}
				else
				{
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
					BUTTON_SetFont(hItem,&GUI_FontB24);	
					BUTTON_SetTextColor(hItem,BUTTON_CI_UNPRESSED,GUI_RED);
					BUTTON_SetText(hItem,HZStr[9]);
				}
	*/			
				
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
				BUTTON_SetFont(hItem,Set.language?&GUI_FontB24:&GUI_Font20_1);
				BUTTON_SetText(hItem,String[Find_Str("Return")][Set.language]);
	
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
				BUTTON_SetFont(hItem,Set.language?&GUI_FontB24:&GUI_Font20_1);
				BUTTON_SetTextAlign(hItem,GUI_TA_HCENTER|GUI_TA_BOTTOM);
				if (State.outflag == 0)
				{
					BUTTON_SetTextColor(hItem,BUTTON_CI_UNPRESSED,GUI_GREEN);
					BUTTON_SetText(hItem,String[Find_Str("Start")][Set.language]);
					BUTTON_SetBitmap(hItem,BUTTON_BI_PRESSED,&bmstart);
					BUTTON_SetBitmap(hItem,BUTTON_BI_UNPRESSED,&bmstart);
				}
				else
				{
					BUTTON_SetTextColor(hItem,BUTTON_CI_UNPRESSED,GUI_RED);
					BUTTON_SetText(hItem,String[Find_Str("Stop")][Set.language]);
					BUTTON_SetBitmap(hItem,BUTTON_BI_PRESSED,&bmstop);
					BUTTON_SetBitmap(hItem,BUTTON_BI_UNPRESSED,&bmstop);
				}
				
				
			hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);		
			PROGBAR_SetMinMax(hItem,0,Set.volhand);
	//		PROGBAR_SetValue(hItem,out_vol);
			PROGBAR_SetFont(hItem,GUI_FONT_16B_1);

		break;		
	case WM_PAINT:
		GUI_DrawGradientV(0,0,479,319,GUI_LIGHTBLUE,GUI_BLUE);
		GUI_SetTextMode(GUI_TM_TRANS);
		GUI_SetFont(GUI_FONT_32B_1);
		GUI_SetColor(GUI_GRAY);
		GUI_DispStringHCenterAt("dotcom",240,65);
	
		GUI_SetColor(GUI_YELLOW);
	/*
		GUI_SetFont(&GUI_FontB24);
		GUI_DispStringAt(HZStr[0],50,20);
		GUI_DispString(HZStr[2]);
	*/
		GUI_SetFont(Set.language?&GUI_FontB24:&GUI_Font20_1);
		GUI_DispStringAt(String[Find_Str("Volume")][Set.language],50,20);
		GUI_DispString(String[Find_Str("Setting")][Set.language]);
	
		GUI_SetFont(GUI_FONT_24B_1);
		GUI_DispStringAt("mL",380,20);
		break;
	
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
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
				//	hand_vol = slider_temp;
			//printf("SPINBOX change %d",slider_temp);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
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
					//hand_vol = slider_temp;
			//	printf("slider change %d",slider_temp);		
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
//				tem = SPINBOX_GetValue(WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_0 ));
//				vol1 = SPINBOX_GetValue(WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_1 ));
//				vol2 = SPINBOX_GetValue(WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_2 ));
				State.hwinflag = 0;
				Setting_Save();
				hItem = pMsg->hWin;
				WM_DeleteWindow(hItem);
				CreateWindow();
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
				Set.volhand = SPINBOX_GetValue(WM_GetDialogItem(pMsg->hWin,ID_SPINBOX_0 ));
				hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);		
				PROGBAR_SetMinMax(hItem,0,Set.volhand);
				PROGBAR_SetValue(hItem,out_vol);
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
			BUTTON_SetFont(hItem,Set.language?&GUI_FontB24:&GUI_Font20_1);
				if (State.outflag == 1)//按下停止，显示开始
				{
					Out_Stop();
					BUTTON_SetTextColor(hItem,BUTTON_CI_UNPRESSED,GUI_GREEN);
					BUTTON_SetText(hItem,String[Find_Str("Start")][Set.language]);
					BUTTON_SetBitmap(hItem,BUTTON_BI_PRESSED,&bmstart);
					BUTTON_SetBitmap(hItem,BUTTON_BI_UNPRESSED,&bmstart);
				}
				else
				{
					Out_Start(Set.volhand);
					
					BUTTON_SetTextColor(hItem,BUTTON_CI_UNPRESSED,GUI_RED);
					BUTTON_SetText(hItem,String[Find_Str("Stop")][Set.language]);
					BUTTON_SetBitmap(hItem,BUTTON_BI_PRESSED,&bmstop);
					BUTTON_SetBitmap(hItem,BUTTON_BI_UNPRESSED,&bmstop);
				}
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
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
WM_HWIN Display_set(void);
WM_HWIN Display_set(void) {
  WM_HWIN hWin;
  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);

  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
