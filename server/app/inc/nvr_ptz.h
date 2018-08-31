#ifndef _NVR_CLIENT_H
#define _NVR_CLIENT_H

/*###############################################  API  ############################################### */


/* ����λ�÷��� */
int Nvr_Client_Crtl_Ptz(uint16_t u16PtzCmd, uint8_t u8Chn, uint8_t u8Speed, uint8_t u8PresetNo);

/* �����Զ�Ѳ�� */
int Nvr_client_Ctrl_Ptz_Cruise(uint8_t u8Chn, uint8_t u8CruisePresetNo, NVR_BOOL u8CruisePresetEnable, 
								uint8_t u8CruisePresetSec, uint8_t u8CruisePresetSpeed);
/* �����Զ�ɨ�� */
int Nvr_Client_Ctrl_Ptz_AutoScan(uint8_t u8Chn, uint8_t u8SetVerticalPos, uint8_t u8Speed);

/* ����AB����ɨ�� */
int Nvr_Client_Ctrl_Ptz_ABScan(uint8_t u8Chn, uint8_t u8SetVerticalPos, uint8_t u8Speed);
int Nvr_Client_Ctrl_Ptz_ABScan_Left_Pos(uint8_t u8Chn);
int Nvr_Client_Ctrl_Ptz_ABScan_Right_Pos(uint8_t u8Chn);

/* �������ö��� */
int Nvr_Client_Ctrl_Ptz_SetIdle(uint8_t u8Chn, uint8_t u8IdleActionIndex, uint8_t u8IdleSec);

/* ���ö�ʱ���� */
int Nvr_Client_Ctrl_Ptz_SetOntime(uint8_t u8Chn, uint8_t u8OntimeIndex, uint8_t u8OntimeActionIndex,
								uint8_t u8BeginHour, uint8_t u8BeginMin, uint8_t u8EndHour, uint8_t u8EndMin);

/* ���ñ������� */
int Nvr_Client_Ctrl_Ptz_SetAlarm(uint8_t u8Chn, uint8_t u8AlarmTypeIndex, uint8_t u8AlarmActionIndex,
									uint8_t u8AlarmDurationSec);
/* �����Զ������*/ 
/*u8IRMode: 0:Զ�����Զ��л�,1:Զ����ͬʱ���� */
int Nvr_Client_Ctrl_Ptz_SetIRMode(uint8_t u8Chn, uint8_t u8IRMode);

/*  ������ҹģʽ */
/* 0:����ģʽ,1:ҹ��ģʽ,2:�Զ�ģʽ 3:���ⶨʱ����ģʽ */
int Nvr_Client_Ctrl_Ptz_SetDayNightMode(uint8_t u8Chn, uint8_t u8DayNightMode);

/*  ���ñ䱶�ٶ� */
/*  0 ����, 1 ����, 2 ����*/
int Nvr_Client_Ctrl_Ptz_SetZoomSpeed(uint8_t u8Chn, uint8_t u8ZoomSpeed);

/*  ���ð�ƽ�⹤��ģʽ */
/* 0 ����,1 ���� ,2 �Զ� ,3 �ֶ� */
int Nvr_Client_Ctrl_Ptz_SetWBMode(uint8_t u8Chn, uint8_t u8WBMode);

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
int Nvr_Client_Ctrl_Ptz_SetEnable(uint8_t u8Chn, uint16_t u8PtzCmd, uint8_t u8Enable);

/* ��̨����� */ 
int nvr_send_ptz_cmd(int chnNum, void* pPtz); 


/*###############################################  API  ############################################### */

#endif

