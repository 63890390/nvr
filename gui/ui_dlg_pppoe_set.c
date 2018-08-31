#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <minigui/mgext.h>
#include <minigui/skin.h>

#include "ui_config.h"
#include "myedit.h"
#include "ctrl_ipaddress.h"
#include "nvr_lib_interface.h"

#include "gui_core.h"

#include "ui_dlg_head.h"

#define PPPOE_DLG_W	490
#define PPPOE_DLG_H	350
#define PPPOE_DLG_X	((NVR_SCREEN_WIDTH - PPPOE_DLG_W)>>1)
#define PPPOE_DLG_Y	((NVR_SCREEN_HEIGHT - PPPOE_DLG_H)>>1)
#define PPPOE_TEXT_W	100
#define PPPOE_EDIT_W	190

#define PPPOE_LEFT_W		70
#define PPPOE_RIGHT_W	60
#define PPPOE_STATE_W	50

#define PPPOE_EDIT_H	20

#define PPPOE_BUTTON_W  110

#define PPPOE_TEXT_INC_Y	(PPPOE_EDIT_H+10)

#define PPPOE_TEXT_START_X	40

#define PPPOE_TEXT_START_Y	60


typedef enum
{
		IDC_STATIC_PPPOE_TYPE = 1600,
		IDC_PPPOE_ENABLE,

		IDC_PPPOE_USER,
        IDC_PPPOE_PASSWARD,
        IDC_PPPOE_SERVERIP,
        IDC_PPPOE_ONLINE,
        IDC_PPPOE_STATUS,

		IDC_PPPOE_REFRESH,
        IDC_PPPOE_SURE,
        IDC_PPPOE_CANCEL,
        
}UI_PPPOE_SETTING_ID;

static CTRLDATA ui_pppoeset_control[] =
{
	#if 1
	{
        GUI_BUTTON,
        WS_VISIBLE | BS_AUTOCHECKBOX ,//| BS_CHECKED,
		PPPOE_TEXT_START_X,PPPOE_TEXT_START_Y, PPPOE_BUTTON_W, PPPOE_EDIT_H,
        IDC_PPPOE_ENABLE,
        "����PPPOE",
        0,
        WS_EX_TRANSPARENT
    },

     {
        CTRL_STATIC,
        WS_CHILD | SS_SIMPLE | WS_VISIBLE,
        PPPOE_TEXT_START_X, PPPOE_TEXT_START_Y+1*PPPOE_TEXT_INC_Y, PPPOE_TEXT_W, PPPOE_EDIT_H,
        IDC_STATIC,
        "�û���",
        0,
		WS_EX_TRANSPARENT
    },
    {
        CTRL_MYEDIT,
        WS_CHILD | WS_VISIBLE |ES_LEFT|WS_TABSTOP,
        PPPOE_TEXT_START_X+PPPOE_TEXT_W, PPPOE_TEXT_START_Y+1*PPPOE_TEXT_INC_Y, PPPOE_EDIT_W, PPPOE_EDIT_H,
        IDC_PPPOE_USER,
        "0",
        0,
		WS_EX_EDIT_NUMINPUT| WS_EX_EDIT_CHARINPUT | WS_EX_USEPARENTFONT
    },
     {
        CTRL_STATIC,
        WS_CHILD | SS_SIMPLE | WS_VISIBLE,
        PPPOE_TEXT_START_X, PPPOE_TEXT_START_Y+2*PPPOE_TEXT_INC_Y, PPPOE_TEXT_W, PPPOE_EDIT_H,
        IDC_STATIC,
        "����",
        0,
		WS_EX_TRANSPARENT
    },
    {
        CTRL_MYEDIT,
        WS_CHILD | WS_VISIBLE |ES_LEFT|WS_TABSTOP|ES_PASSWORD,
        PPPOE_TEXT_START_X+PPPOE_TEXT_W, PPPOE_TEXT_START_Y+2*PPPOE_TEXT_INC_Y, PPPOE_EDIT_W, PPPOE_EDIT_H,
        IDC_PPPOE_PASSWARD,
        "0",
        0,
		WS_EX_EDIT_NUMINPUT| WS_EX_EDIT_CHARINPUT | WS_EX_USEPARENTFONT
    },
    {
        CTRL_STATIC,
        WS_CHILD | SS_SIMPLE | WS_VISIBLE,
        PPPOE_TEXT_START_X, PPPOE_TEXT_START_Y+3*PPPOE_TEXT_INC_Y, PPPOE_TEXT_W, PPPOE_EDIT_H,
        IDC_STATIC,
        "�豸IP",
        0,
		WS_EX_TRANSPARENT
    },

    {
        CTRL_IP_ADDRESS,
        WS_CHILD | WS_VISIBLE |ES_LEFT|WS_TABSTOP|ES_READONLY,
        PPPOE_TEXT_START_X+PPPOE_TEXT_W, PPPOE_TEXT_START_Y+3*PPPOE_TEXT_INC_Y, PPPOE_EDIT_W, PPPOE_EDIT_H,
        IDC_PPPOE_SERVERIP,
        "0.0.0.0",
        0,
        WS_EX_USEPARENTFONT|WS_EX_EDIT_NUMINPUT
    },	
    {
        CTRL_STATIC,
        WS_CHILD | SS_SIMPLE | WS_VISIBLE,
        PPPOE_TEXT_START_X, PPPOE_TEXT_START_Y+4*PPPOE_TEXT_INC_Y, PPPOE_TEXT_W, PPPOE_EDIT_H,
        IDC_STATIC,
        "����ʱ��",
        0,
		WS_EX_TRANSPARENT
    },
    {
        CTRL_MYEDIT,
        WS_CHILD | WS_VISIBLE |ES_LEFT|WS_TABSTOP|ES_READONLY,
        PPPOE_TEXT_START_X+PPPOE_TEXT_W, PPPOE_TEXT_START_Y+4*PPPOE_TEXT_INC_Y, PPPOE_RIGHT_W, PPPOE_EDIT_H,
        IDC_PPPOE_ONLINE,
        "0",
        0,
		WS_EX_EDIT_NUMINPUT| WS_EX_USEPARENTFONT
    },

    {
        CTRL_STATIC,
        WS_CHILD | SS_SIMPLE | WS_VISIBLE,
        PPPOE_TEXT_START_X+PPPOE_TEXT_W+PPPOE_RIGHT_W+5, PPPOE_TEXT_START_Y+4*PPPOE_TEXT_INC_Y, PPPOE_STATE_W, PPPOE_EDIT_H,
        IDC_STATIC,
        "״̬",
        0,
		WS_EX_TRANSPARENT
    },
    {
        CTRL_MYEDIT,
        WS_CHILD | WS_VISIBLE |ES_LEFT|WS_TABSTOP|ES_READONLY,
        PPPOE_TEXT_START_X+PPPOE_TEXT_W+PPPOE_RIGHT_W+PPPOE_STATE_W, PPPOE_TEXT_START_Y+4*PPPOE_TEXT_INC_Y, PPPOE_RIGHT_W+20, PPPOE_EDIT_H,
        IDC_PPPOE_STATUS,
        "0",
        0,
		WS_EX_EDIT_NUMINPUT| WS_EX_USEPARENTFONT
    },
   
	//////////////////////////// GUI_BUTTON ////////////////////////////////////
	CONFIG_TWO_WORDS_BUTTON("ˢ��", IDC_PPPOE_REFRESH, PPPOE_TEXT_START_X, PPPOE_DLG_H - 50),
	CONFIG_TWO_WORDS_BUTTON("ȷ��", IDC_PPPOE_SURE, PPPOE_DLG_W - 160, PPPOE_DLG_H - 50),
	CONFIG_TWO_WORDS_BUTTON("ȡ��", IDC_PPPOE_CANCEL, PPPOE_DLG_W - 80 , PPPOE_DLG_H - 50),

	#endif	
};


static DLGTEMPLATE PppoesetDlg =
{
    WS_NONE,
    WS_EX_NONE,
    PPPOE_DLG_X, PPPOE_DLG_Y, PPPOE_DLG_W, PPPOE_DLG_H,
    "¼�����",
    0, 0,
    TABLESIZE(ui_pppoeset_control), NULL,
    0
};

static void setPppoeEditLength(HWND hWnd)
{
	HWND userHwnd,pwdHwnd;

	userHwnd = GetDlgItem(hWnd, IDC_PPPOE_USER);
	SendMessage(userHwnd, EM_LIMITTEXT, 31, 0L);

	pwdHwnd = GetDlgItem(hWnd, IDC_PPPOE_PASSWARD);
	SendMessage(pwdHwnd, EM_LIMITTEXT, 31, 0L);

}

static void setEnablePppoewindow(HWND hDlg, BOOL enable)
{
	EnableDlgItem(hDlg, IDC_PPPOE_USER, enable);
	EnableDlgItem(hDlg, IDC_PPPOE_PASSWARD, enable);	
	
	EnableDlgItem(hDlg, IDC_PPPOE_SERVERIP, FALSE);
	EnableDlgItem(hDlg, IDC_PPPOE_ONLINE, FALSE);	
	EnableDlgItem(hDlg, IDC_PPPOE_STATUS, FALSE);
}

static void InitPppoeParam(HWND hDlg)
{
	NVR_DEV_NET_CFG_S netCfg;
	char acIp[32];

	memset(&netCfg, 0, sizeof(NVR_DEV_NET_CFG_S));
	if(nvr_logon_get_net_cfg(0, &netCfg) < 0)
	{
		printf("[error]--------->>>get pppoe cfg error\n");
		return ;
	}

	if(netCfg.struPppoeCfg.u8PppoeOn)
	{
		SendDlgItemMessage(hDlg, IDC_PPPOE_ENABLE, BM_SETCHECK, BST_CHECKED, 0);
		setEnablePppoewindow(hDlg, TRUE);

	}
	else
	{
		SendDlgItemMessage(hDlg, IDC_PPPOE_ENABLE, BM_SETCHECK, BST_UNCHECKED, 0);
		setEnablePppoewindow(hDlg, FALSE);
	}
		
	SetDlgItemText(hDlg, IDC_PPPOE_USER, netCfg.struPppoeCfg.szPppoeUsr);//�û���
	
	SetDlgItemText(hDlg, IDC_PPPOE_PASSWARD, netCfg.struPppoeCfg.szPppoePsw);//����

	sprintf(acIp, "%d.%d.%d.%d", (netCfg.struPppoeCfg.u32PppoeIp>>24)&0xff,
											(netCfg.struPppoeCfg.u32PppoeIp>>16)&0xff,
											(netCfg.struPppoeCfg.u32PppoeIp>>8)&0xff,
											(netCfg.struPppoeCfg.u32PppoeIp>>0)&0xff);
	SetDlgItemText(hDlg, IDC_PPPOE_SERVERIP, acIp);//cmd�˿�
	
	sprintf(acIp, "%d", netCfg.struPppoeCfg.u32PppoeTimes);
	SetDlgItemText(hDlg, IDC_PPPOE_ONLINE, acIp);//����ʱ��

	if(1 == netCfg.struPppoeCfg.u8PppoeStatus)
		sprintf(acIp, "%s", LTR("������"));
	else if(2 == netCfg.struPppoeCfg.u8PppoeStatus)
		sprintf(acIp, "%s", LTR("���ųɹ�"));
	else
		sprintf(acIp, "%s", LTR("δ����"));

	SetDlgItemText(hDlg, IDC_PPPOE_STATUS, acIp);//״̬
}

static void SavePppoesetParam(HWND hDlg)
{
	NVR_DEV_NET_CFG_S netCfg;
	int checked;
	char acIp[32];
	HWND hUser,hPwd;

	memset(&netCfg, 0, sizeof(NVR_DEV_NET_CFG_S));
	if(nvr_logon_get_net_cfg(0, &netCfg) < 0)
	{
		printf("[error]--------->>>get pppoe cfg error\n");
		return ;
	}
	
	checked = SendDlgItemMessage(hDlg, IDC_PPPOE_ENABLE, BM_GETCHECK, 0, 0);
 	netCfg.struPppoeCfg.u8PppoeOn = checked;

 	hUser = GetDlgItem (hDlg, IDC_PPPOE_USER);
	GetWindowText(hUser, acIp, 32);
	memcpy(netCfg.struPppoeCfg.szPppoeUsr, acIp, 32);
 	hPwd = GetDlgItem (hDlg, IDC_PPPOE_PASSWARD);
	GetWindowText(hPwd, acIp, 32);
	memcpy(netCfg.struPppoeCfg.szPppoePsw, acIp, 32);
	if(nvr_logon_set_net_cfg(0, &netCfg) < 0)
	{
		printf("[error]---------->>>set pppoe cfg error\n");
	}
	
}

static int PppoeSetWinProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	int bChecked;
    switch (message)
    {

    case MSG_INITDIALOG:
    {	
		InitPppoeParam(hDlg);
		setPppoeEditLength(hDlg);
		push_open_dlg(&headOpenDlg, hDlg);
        break;
    }
#if 0	
	case MSG_PAINT:
	{
		HDC hdc;
       	hdc = BeginPaint (hDlg);		
       	EndPaint (hDlg, hdc);		
		Gui_DrawCaption(hDlg, "PPPOE����");
        break;
	}
#endif
	case MSG_ERASEBKGND:
	{
		RECT title = {0, 0, 490, 50};
		HDC hdc = (HDC)wParam; 
		const RECT* clip = (const RECT*) lParam; 
		BOOL fGetDC = FALSE; 
		RECT rcTemp; 
		if (hdc == 0) 
		{ 
			hdc = GetClientDC (hDlg); 
			fGetDC = TRUE; 
		} 
		if (clip) 
		{ 
			rcTemp = *clip; 
			ScreenToClient (hDlg, &rcTemp.left, &rcTemp.top); 
			ScreenToClient (hDlg, &rcTemp.right, &rcTemp.bottom); 
			IncludeClipRect (hdc, &rcTemp); 
		} 
		/* ��ͼƬ��䱳��*/ 
		FillBoxWithBitmap (hdc, 0, 0, 0, 0, &bk_pic[SIZE_490x350]); 
		Gui_WriteTitleName(hdc, &title, LTR("PPPOE����"));
		if (fGetDC) 
			ReleaseDC (hdc); 
		return 0; 
	}
	break;

	case MSG_RBUTTONUP:
    {
		PostMessage(hDlg, MSG_CLOSE, 0, 0);
		
        break;
    }

    case MSG_COMMAND:
    { 
    	switch(wParam)
		{
			case IDC_PPPOE_ENABLE:
				bChecked = SendDlgItemMessage(hDlg, IDC_PPPOE_ENABLE, BM_GETCHECK, 0, 0);
				if(bChecked)
				{
					setEnablePppoewindow(hDlg, TRUE);
				}
				else
				{
					setEnablePppoewindow(hDlg, FALSE);
				}

				break;
			case IDC_PPPOE_REFRESH:
			{
				InitPppoeParam(hDlg);
				InvalidateRect(hDlg, NULL, TRUE);
				return 0;
			}	
			case IDC_PPPOE_SURE:
			{
				SavePppoesetParam(hDlg);
				SendNotifyMessage(hDlg, MSG_CLOSE, 0, 0);
				return 0;
			}
			case IDC_PPPOE_CANCEL:
				PostMessage(hDlg, MSG_CLOSE, 0, 0);
				break;
		}
		
        break;
    }
    case MSG_CLOSE:
    {	
    	HWND hWind;
    	pop_open_dlg(&headOpenDlg, &hWind);
        EndDialog (hDlg, 0);
        break;
    }

    }

    return DefaultDialogProc (hDlg, message, wParam, lParam);
}

//Զ���豸����
void CreatePppoeSetDlgWin(HWND hParent)
{
	#ifdef _MGRM_PROCESSES
    JoinLayer(NAME_DEF_LAYER , "PppoeSetDlg" , 0 , 0);
#endif
	PCTRLDATA ctrolTmp;
	
	ctrolTmp = (PCTRLDATA)malloc(sizeof(ui_pppoeset_control));
	if(NULL == ctrolTmp)
		return ;	
	memcpy(ctrolTmp, ui_pppoeset_control, sizeof(ui_pppoeset_control));
	DLG_CAPTION_LANGUAGE_TRANS(ui_pppoeset_control)
    PppoesetDlg.controls = ui_pppoeset_control;
    
    DialogBoxIndirectParam (&PppoesetDlg, hParent, PppoeSetWinProc, 0L);
	memcpy(ui_pppoeset_control, ctrolTmp, sizeof(ui_pppoeset_control));
	free(ctrolTmp);
	ctrolTmp = NULL;
}

