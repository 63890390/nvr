
#include <nvr_headers.h>
#include <nvr_lib_common.h>
#include <nvr_lib_interface.h>



/*�����ƿ���̨��������*/
int nvr_lib_send_ptz_cmd(uint8_t u8Chn, void* pPtz)
{	
	if(NULL == pPtz)
		return NVR_FAILURE;
	
	char *sendBuf = (char*)malloc(sizeof(NVR_CTRL_PTZ_S)+sizeof(NVR_NET_HDR_S)*2);

	nvr_make_net_hdr((NVR_NET_HDR_S*)sendBuf, u8Chn, NVR_CMD_CTRL_PTZ, sizeof(NVR_CTRL_PTZ_S), 0);
	memcpy(sendBuf+sizeof(NVR_NET_HDR_S), pPtz, sizeof(NVR_CTRL_PTZ_S));
	
	if(0 > nvr_send_cmd(NULL, 0, 
                        sendBuf, sizeof(NVR_NET_HDR_S)+sizeof(NVR_CTRL_PTZ_S)))
	{
		__ERR("send data packet failed ...\n");
		free(sendBuf);
		return NVR_FAILURE;
	}

	free(sendBuf);
	return NVR_SUCCESS;
}
/* ����λ�÷��� */
int Nvr_Client_Crtl_Ptz(uint16_t u16PtzCmd, uint8_t u8Chn, uint8_t u8Speed, uint8_t u8PresetNo)
{
	NVR_CTRL_PTZ_S ptz;

	if (u8Chn >= NVR_MAX_CHANNEL_NUM)
		return NVR_FAILURE;

	memset(&ptz, 0, sizeof(NVR_CTRL_PTZ_S));	

	ptz.u16PtzCmd = (uint8_t)u16PtzCmd;
	ptz.struPreset.u8Chn = (uint8_t)u8Chn;
	ptz.struPreset.u8PresetNo = (uint8_t)u8PresetNo;
	ptz.struPreset.u8Speed = (uint8_t)u8Speed;

	return nvr_lib_send_ptz_cmd(u8Chn, &ptz);

}
/* �����Զ�Ѳ�� */
int Nvr_client_Ctrl_Ptz_Cruise(uint8_t u8Chn, uint8_t u8CruisePresetNo, uint8_t u8CruisePresetEnable, 
								uint8_t u8CruisePresetSec, uint8_t u8CruisePresetSpeed)
{
	NVR_CTRL_PTZ_S ptz;

	if (u8Chn >= NVR_MAX_CHANNEL_NUM)
		return NVR_FAILURE;
	memset(&ptz, 0, sizeof(NVR_CTRL_PTZ_S));	

	ptz.u16PtzCmd = PTZ_CMD_SET_CRUISE;
	ptz.struCruise.u8CruisePresetEnable = (uint8_t)u8CruisePresetEnable;
	ptz.struCruise.u8CruisePresetNo = (uint8_t)u8CruisePresetNo;
	ptz.struCruise.u8CruisePresetSec = (uint8_t)u8CruisePresetSec;
	ptz.struCruise.u8CruisePresetSpeed = (uint8_t)u8CruisePresetSpeed;

	return nvr_lib_send_ptz_cmd(u8Chn, &ptz);

}

/* �����Զ�ɨ�� */
int Nvr_Client_Ctrl_Ptz_AutoScan(uint8_t u8Chn, uint8_t u8SetVerticalPos, uint8_t u8Speed)
{

	NVR_CTRL_PTZ_S ptz;

	if (u8Chn >= NVR_MAX_CHANNEL_NUM)
		return NVR_FAILURE;
	memset(&ptz, 0, sizeof(NVR_CTRL_PTZ_S));	

	ptz.u16PtzCmd = PTZ_CMD_SET_AUTOSCAN_SETTING;
	ptz.struAutoScan.u8SetVerticalPos = (uint8_t)u8SetVerticalPos;
	ptz.struAutoScan.u8Speed = (uint8_t)u8Speed;

	return nvr_lib_send_ptz_cmd(u8Chn, &ptz);

}

/* ����AB����ɨ�� */
int Nvr_Client_Ctrl_Ptz_ABScan(uint8_t u8Chn, uint8_t u8SetVerticalPos, uint8_t u8Speed)
{

	NVR_CTRL_PTZ_S ptz;

	if (u8Chn >= NVR_MAX_CHANNEL_NUM)
		return NVR_FAILURE;
	memset(&ptz, 0, sizeof(NVR_CTRL_PTZ_S));	

	ptz.u16PtzCmd = PTZ_CMD_SET_ABSCAN_SETTING;
	ptz.struABScan.u8SetVerticalPos = (uint8_t)u8SetVerticalPos;
	ptz.struABScan.u8Speed = (uint8_t)u8Speed;

	return nvr_lib_send_ptz_cmd(u8Chn, &ptz);

}
int Nvr_Client_Ctrl_Ptz_ABScan_Left_Pos(uint8_t u8Chn)
{

	NVR_CTRL_PTZ_S ptz;

	if (u8Chn >= NVR_MAX_CHANNEL_NUM)
		return NVR_FAILURE;
	memset(&ptz, 0, sizeof(NVR_CTRL_PTZ_S));	

	ptz.u16PtzCmd = PTZ_CMD_SET_ABSCAN_LEFT_POS;

	return nvr_lib_send_ptz_cmd(u8Chn,&ptz);	
}
int Nvr_Client_Ctrl_Ptz_ABScan_Right_Pos(uint8_t u8Chn)
{

	NVR_CTRL_PTZ_S ptz;

	if (u8Chn >= NVR_MAX_CHANNEL_NUM)
		return NVR_FAILURE;
	memset(&ptz, 0, sizeof(NVR_CTRL_PTZ_S));	

	ptz.u16PtzCmd = PTZ_CMD_SET_ABSCAN_RIGHT_POS;

	return nvr_lib_send_ptz_cmd(u8Chn,&ptz);
}

/* �������ö��� */
int Nvr_Client_Ctrl_Ptz_SetIdle(uint8_t u8Chn, uint8_t u8IdleActionIndex, uint8_t u8IdleSec)
{

	NVR_CTRL_PTZ_S ptz;

	if (u8Chn >= NVR_MAX_CHANNEL_NUM)
		return NVR_FAILURE;
	memset(&ptz, 0, sizeof(NVR_CTRL_PTZ_S));	

	ptz.u16PtzCmd = PTZ_CMD_SET_IDLE_SETTING;
	ptz.struIdleAction.u8IdleActionIndex = (uint8_t)u8IdleActionIndex;
	ptz.struIdleAction.u8IdleSec = (uint8_t)u8IdleSec;

	return nvr_lib_send_ptz_cmd(u8Chn, &ptz);

}

/* ���ö�ʱ���� */
int Nvr_Client_Ctrl_Ptz_SetOntime(uint8_t u8Chn, uint8_t u8OntimeIndex, uint8_t u8OntimeActionIndex,
								uint8_t u8BeginHour, uint8_t u8BeginMin, uint8_t u8EndHour, uint8_t u8EndMin)
{
	NVR_CTRL_PTZ_S ptz;

	if (u8Chn >= NVR_MAX_CHANNEL_NUM)
		return NVR_FAILURE;
	memset(&ptz, 0, sizeof(NVR_CTRL_PTZ_S));	

	ptz.u16PtzCmd = PTZ_CMD_SET_ONTIME_SETTING;
	ptz.struOntimeAction.u8OntimeIndex = (uint8_t)u8OntimeIndex;
	ptz.struOntimeAction.u8OntimeActionIndex = (uint8_t)u8OntimeActionIndex;
	ptz.struOntimeAction.u8BeginHour = (uint8_t)u8BeginHour;
	ptz.struOntimeAction.u8BeginMin = (uint8_t)u8BeginMin;
	ptz.struOntimeAction.u8EndHour = (uint8_t)u8EndHour;
	ptz.struOntimeAction.u8EndMin = (uint8_t)u8EndMin;
	return nvr_lib_send_ptz_cmd(u8Chn,&ptz);
}


/* ���ñ������� */
int Nvr_Client_Ctrl_Ptz_SetAlarm(uint8_t u8Chn, uint8_t u8AlarmTypeIndex, uint8_t u8AlarmActionIndex,
									uint8_t u8AlarmDurationSec)
{
		NVR_CTRL_PTZ_S ptz;
		
		if (u8Chn >= NVR_MAX_CHANNEL_NUM)
			return NVR_FAILURE;
		memset(&ptz, 0, sizeof(NVR_CTRL_PTZ_S));	
		
		ptz.u16PtzCmd = PTZ_CMD_SET_ALARM_SETTING;
		ptz.struAlarm.u8AlarmTypeIndex = (uint8_t)u8AlarmTypeIndex;
		ptz.struAlarm.u8AlarmActionIndex = (uint8_t)u8AlarmActionIndex;
		ptz.struAlarm.u8AlarmDurationSec =(uint8_t)u8AlarmDurationSec;
		
		return nvr_lib_send_ptz_cmd(u8Chn,&ptz);

}

/* �����Զ������*/ 
/*u8IRMode: 0:Զ�����Զ��л�,1:Զ����ͬʱ���� */
int Nvr_Client_Ctrl_Ptz_SetIRMode( uint8_t u8Chn, uint8_t u8IRMode)
{
	NVR_CTRL_PTZ_S ptz;

	if (u8Chn >= NVR_MAX_CHANNEL_NUM)
		return NVR_FAILURE;
	memset(&ptz, 0, sizeof(NVR_CTRL_PTZ_S));	

	ptz.u16PtzCmd = PTZ_CMD_SET_IR_MODE;
	ptz.u8IRMode = (uint8_t)u8IRMode;

	return nvr_lib_send_ptz_cmd(u8Chn, &ptz);

}
/*  ������ҹģʽ */
/* 0:����ģʽ,1:ҹ��ģʽ,2:�Զ�ģʽ 3:���ⶨʱ����ģʽ */
int Nvr_Client_Ctrl_Ptz_SetDayNightMode( uint8_t u8Chn, uint8_t u8DayNightMode)
{
	NVR_CTRL_PTZ_S ptz;

	if (u8Chn >= NVR_MAX_CHANNEL_NUM)
		return NVR_FAILURE;
	memset(&ptz, 0, sizeof(NVR_CTRL_PTZ_S));	

	ptz.u16PtzCmd = PTZ_CMD_SET_DAY_NIGHT_MODE;
	ptz.u8DayNightMode = (uint8_t)u8DayNightMode;

	return nvr_lib_send_ptz_cmd(u8Chn, &ptz);

}

/*  ���ñ䱶�ٶ� */
/*  0 ����, 1 ����, 2 ����*/
int Nvr_Client_Ctrl_Ptz_SetZoomSpeed( uint8_t u8Chn, uint8_t u8ZoomSpeed)
{

	NVR_CTRL_PTZ_S ptz;

	if (u8Chn >= NVR_MAX_CHANNEL_NUM)
		return NVR_FAILURE;
	memset(&ptz, 0, sizeof(NVR_CTRL_PTZ_S));	

	ptz.u16PtzCmd = (uint8_t)PTZ_CMD_ZOOM_SPEED;
	ptz.u8ZoomSpeed = (uint8_t)u8ZoomSpeed;

	return nvr_lib_send_ptz_cmd(u8Chn, &ptz);

}

/*  ���ð�ƽ�⹤��ģʽ */
/* 0 ����,1 ���� ,2 �Զ� ,3 �ֶ� */
int Nvr_Client_Ctrl_Ptz_SetWBMode( uint8_t u8Chn, uint8_t u8WBMode)
{
	NVR_CTRL_PTZ_S ptz;

	if (u8Chn >= NVR_MAX_CHANNEL_NUM)
		return NVR_FAILURE;
	memset(&ptz, 0, sizeof(NVR_CTRL_PTZ_S));	

	ptz.u16PtzCmd = PTZ_CMD_SET_WB_MODE;
	ptz.u8WBMode = (uint8_t)u8WBMode;

	return nvr_lib_send_ptz_cmd(u8Chn, &ptz);

}

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

int Nvr_Client_Ctrl_Ptz_SetEnable( uint8_t u8Chn, uint16_t u8PtzCmd, uint8_t u8Enable)
{
	NVR_CTRL_PTZ_S ptz;

	if (u8Chn >= NVR_MAX_CHANNEL_NUM)
		return NVR_FAILURE;
	memset(&ptz, 0, sizeof(NVR_CTRL_PTZ_S));	

	ptz.u16PtzCmd = u8PtzCmd;
	ptz.u8OpenOrClose = (uint8_t)u8Enable;

	return nvr_lib_send_ptz_cmd(u8Chn, &ptz);

}






