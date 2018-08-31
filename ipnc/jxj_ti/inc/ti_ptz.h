#ifndef _TI_CLIENT_H
#define _TI_CLIENT_H

#include "ti_param_proc.h"
#include "ti_net_interface.h"
#include "ti_type.h"



/*###############################################  API  ############################################### */


/* ����λ�÷��� */
int Ti_Client_Crtl_Ptz(long handle, TI_U16 u16PtzCmd, TI_U8 u8Chn, TI_U8 u8Speed, TI_U8 u8PresetNo);

/* �����Զ�Ѳ�� */
int ti_client_Ctrl_Ptz_Cruise(long handle, TI_U8 u8Chn, TI_U8 u8CruisePresetNo, TI_BOOL u8CruisePresetEnable, 
								TI_U8 u8CruisePresetSec, TI_U8 u8CruisePresetSpeed);
/* �����Զ�ɨ�� */
int Ti_Client_Ctrl_Ptz_AutoScan(long handle, TI_U8 u8Chn, TI_U8 u8SetVerticalPos, TI_U8 u8Speed);

/* ����AB����ɨ�� */
int Ti_Client_Ctrl_Ptz_ABScan(long handle, TI_U8 u8Chn, TI_U8 u8SetVerticalPos, TI_U8 u8Speed);
int Ti_Client_Ctrl_Ptz_ABScan_Left_Pos(long handle, TI_U8 u8Chn);
int Ti_Client_Ctrl_Ptz_ABScan_Right_Pos(long handle, TI_U8 u8Chn);

/* �������ö��� */
int Ti_Client_Ctrl_Ptz_SetIdle(long handle, TI_U8 u8Chn, TI_U8 u8IdleActionIndex, TI_U8 u8IdleSec);

/* ���ö�ʱ���� */
int Ti_Client_Ctrl_Ptz_SetOntime(long handle,TI_U8 u8Chn, TI_U8 u8OntimeIndex, TI_U8 u8OntimeActionIndex,
								TI_U8 u8BeginHour, TI_U8 u8BeginMin, TI_U8 u8EndHour, TI_U8 u8EndMin);

/* ���ñ������� */
int Ti_Client_Ctrl_Ptz_SetAlarm(long handle ,TI_U8 u8Chn, TI_U8 u8AlarmTypeIndex, TI_U8 u8AlarmActionIndex,
									TI_U8 u8AlarmDurationSec);
/* �����Զ������*/ 
/*u8IRMode: 0:Զ�����Զ��л�,1:Զ����ͬʱ���� */
int Ti_Client_Ctrl_Ptz_SetIRMode(long handle, TI_U8 u8Chn, TI_U8 u8IRMode);

/*  ������ҹģʽ */
/* 0:����ģʽ,1:ҹ��ģʽ,2:�Զ�ģʽ 3:���ⶨʱ����ģʽ */
int Ti_Client_Ctrl_Ptz_SetDayNightMode(long handle, TI_U8 u8Chn, TI_U8 u8DayNightMode);

/*  ���ñ䱶�ٶ� */
/*  0 ����, 1 ����, 2 ����*/
int Ti_Client_Ctrl_Ptz_SetZoomSpeed(long handle, TI_U8 u8Chn, TI_U8 u8ZoomSpeed);

/*  ���ð�ƽ�⹤��ģʽ */
/* 0 ����,1 ���� ,2 �Զ� ,3 �ֶ� */
int Ti_Client_Ctrl_Ptz_SetWBMode(long handle, TI_U8 u8Chn, TI_U8 u8WBMode);

/* ����ĳЩѡ���ʹ��
* ����:
* 	180���Զ���ת
*	���ӷŴ�
*	���ⲹ��
*	�䱶��ʾ
*	֡����
*	��̬
*	�ƶ����
*	����������
*/
/*	0:close, 1:open */
int Ti_Client_Ctrl_Ptz_SetEnable(long handle, TI_U8 u8Chn, TI_U16 u8PtzCmd, TI_U8 u8Enable);

/* ��̨����� */ 
int ti_send_ptz_cmd(long handle, void* pPtz); 


/*###############################################  API  ############################################### */

#endif

