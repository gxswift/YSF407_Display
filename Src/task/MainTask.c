/**
  ******************************************************************************
  * �ļ�����: main.c 
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2017-03-30
  * ��    ��: emwin�������ܵ�ʵ��
  ******************************************************************************
  * ˵����
  * ����������Ӳʯstm32������YS-F4Proʹ�á�
  * 
  * �Ա���
  * ��̳��http://www.ing10bbs.com
  * ��Ȩ��ӲʯǶ��ʽ�����Ŷ����У��������á�
  ******************************************************************************
  */
/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "MainTask.h"

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0   (GUI_ID_USER + 0x01)
#define ID_BUTTON_1   (GUI_ID_USER + 0x02)

/* ˽�б��� ------------------------------------------------------------------*/
/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/
/**
  * ��������: GUI_WIDGET_CREATE_INFOl��������
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = 
{
	{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 320, 480, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 70, 37, 159, 49, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 70, 127, 159, 46, 0, 0x0, 0 },
};
/**
  * ��������: �Ի���ص�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
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
			// ��ʼ�� 'Framewin'
			//
			hItem = pMsg->hWin;
			FRAMEWIN_SetFont(hItem, GUI_FONT_32B_ASCII);
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetText(hItem, "YSF4");
      //
      // ��ʼ����ť�ؼ�
      //
      hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
      BUTTON_SetFont(hItem, GUI_FONT_24B_ASCII);
      BUTTON_SetText(hItem, "LED1");
      //
      // ��ʼ����ť�ؼ�
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
  * ��������: GUI���ܺ���
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
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

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
