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

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_ICONVIEW_0 (GUI_ID_USER + 0x01)
#define ID_BUTTON_0 (GUI_ID_USER + 0x11)


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
	{ BUTTON_CreateIndirect, "Return", ID_BUTTON_0, 30, 230, 80, 40, 0, 0x0, 0 },
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

/*********************************************************************
*
*       _cbDialog
*/
extern GUI_CONST_STORAGE GUI_BITMAP bmwz;


extern GUI_CONST_STORAGE GUI_BITMAP bmstart;
extern GUI_CONST_STORAGE GUI_BITMAP bmstop;

extern GUI_CONST_STORAGE GUI_BITMAP bmoperate;
extern GUI_CONST_STORAGE GUI_BITMAP bmbasicset;


extern WM_HWIN SettingWindow(void);
extern WM_HWIN CalenderWindow(void);
extern WM_HWIN CreateSoftWare(void);
extern WM_HWIN CreateWindow(void);

static void _cbDialog(WM_MESSAGE * pMsg) {
  int NCode;
  int Id;
	WM_HWIN hItem;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
	case WM_PAINT:
		GUI_DrawGradientV(0,0,479,319,GUI_LIGHTBLUE,GUI_BLUE);
		GUI_SetTextMode(GUI_TM_TRANS);
		GUI_SetFont(GUI_FONT_20_1);
		break;
	
	case WM_INIT_DIALOG:

		break;
	
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
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
				CreateWindow();
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_ICONVIEW_0: // Notifications sent by 'Iconview'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				switch (ICONVIEW_GetSel(pMsg->hWinSrc))
				{
					case 0:
						hItem = pMsg->hWin;
						WM_DeleteWindow(hItem);
						SettingWindow();
						break;
					case 1:
					WM_DeleteWindow(pMsg->hWin);
					CalenderWindow();
						break;
					case 2:
						WM_DeleteWindow(pMsg->hWin);
						CreateSoftWare();
						break;
					default:
						break;
				}
				break;
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SCROLL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
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
WM_HWIN SelectWindow(void);
WM_HWIN SelectWindow(void) {
  WM_HWIN hWin;
	ICONVIEW_Handle hIcon;
  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	hIcon = ICONVIEW_CreateEx(20,
		30, 
		440,
		200, 
		hWin,//WM_HBKWIN, 
		WM_CF_SHOW | WM_CF_HASTRANS,
		ICONVIEW_CF_AUTOSCROLLBAR_V, //0,//
		ID_ICONVIEW_0,
		130,//
		150);

		ICONVIEW_SetSpace(hIcon, GUI_COORD_X, 20);
		ICONVIEW_SetSpace(hIcon, GUI_COORD_Y, 30);
		ICONVIEW_SetFont(hIcon, &GUI_Font20B_ASCII);
		ICONVIEW_SetIconAlign(hIcon, ICONVIEW_IA_VCENTER);
	
		ICONVIEW_AddBitmapItem(hIcon,&bmbasicset,"Basic");
		ICONVIEW_AddBitmapItem(hIcon,&bmbasicset,"Time");
		ICONVIEW_AddBitmapItem(hIcon,&bmbasicset,"info");
	
		ICONVIEW_SetTextColor(hIcon, ICONVIEW_CI_UNSEL, GUI_BLUE);
		ICONVIEW_SetTextColor(hIcon, ICONVIEW_CI_SEL, GUI_RED);
		ICONVIEW_SetBkColor(hIcon, ICONVIEW_CI_BK, GUI_LIGHTBLUE | 0x30000000);
		ICONVIEW_SetBkColor(hIcon, ICONVIEW_CI_SEL, GUI_LIGHTGREEN | 0x80000000);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/