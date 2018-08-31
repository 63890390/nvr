
#include "ipnc_lib.h"
#include "jxj_cu_ipnc_mng.h"
#include "jxj_cu_logon.h"
#include "jxj_cu_net_param.h"
#include "jxj_cu_ptz.h"
#include "jxj_cu_ipnc_logon.h"

int jxj_cu_ipnc_test_logon(const char* DesIP, const char* User, 
					 const char* Password, const char* port)
{
	
	if(DesIP == NULL || User == NULL || 
	   Password == NULL || port == NULL)
		return -1;

	//printf(">>>>>>>>>DesIP: %s \n", DesIP);
	//printf(">>>>>>>>>User: %s \n", User);
	//printf(">>>>>>>>>Password: %s \n", Password);
	//printf(">>>>>>>>>port: %s \n", port);
	return jxj_cu_logon_test(DesIP, User, Password, port);
}


int jxj_cu_ipnc_logon(long handle, long *logonHandle)
{
	JXJ_CU_PROTOCOL_MNG *ipncHandle = (JXJ_CU_PROTOCOL_MNG *)handle;
	JXJ_CU_LOGON_S * pUserInfo = NULL;
	IPNC_DEV_IMA_CFG_S stImaCfg;
	IPNC_DEV_IRCFMODE_CFG_S stIrcfCfg;
	
	if(NULL == ipncHandle)
		return -1;

	char port[10] = {0};
	sprintf(port, "%d", ipncHandle->port);

	//��¼
	*logonHandle = jxj_cu_logon(ipncHandle->ipAddr, ipncHandle->user, 
								ipncHandle->passwd, port, 
								NULL, &ipncHandle->poolCh);

	if((long)NULL == *logonHandle)
		return -1;
	// Ԥ�Ȼ�ȡ���������������ݣ���Ϊ�����������ٴ�
	// ͨ��ʱ��Ƚ� ��
	//jxj_cu_ipnc_get_param(*logonHandle, IPNC_CMD_IMA_CFG, &stImaCfg, sizeof(stImaCfg));
	//jxj_cu_ipnc_get_param(*logonHandle, IPNC_CMD_IRCFMODE_CFG, &stIrcfCfg, sizeof(stIrcfCfg));
	pUserInfo = (JXJ_CU_LOGON_S *)(*logonHandle);
	return pUserInfo->sock;
}

int jxj_cu_ipnc_logout(long logonHandle)
{
	if(((long)NULL == logonHandle) || (0 == logonHandle))
		return -1;
	//ע����¼
	return jxj_cu_logout(logonHandle);
}

int jxj_cu_ipnc_get_param(long logonHandle, IPNC_CMD_TYPE_E cmd, void *pParam, int dataSize)
{
	JXJ_CU_NET_CMD_PARAM_S* pCmdParam = NULL;
	
	if(NULL == pParam)
		return -1;
	if(((long)NULL == logonHandle) || (0 == logonHandle))
		return -1;

	//��ȡ�������Ӧ�Ļ�ȡ�����ӿ�
	pCmdParam = (JXJ_CU_NET_CMD_PARAM_S*)jxj_cu_net_param_cmd(cmd);
	
	if(NULL != pCmdParam)
	{
		if(pCmdParam->getParamProc != NULL)
			return pCmdParam->getParamProc(logonHandle, 0, pParam, dataSize);
	}
	else		
		__ERR("pCmdParam is null!\n");

	__ERR("pParam check is error!\n");
	return -1;
}
int jxj_cu_ipnc_set_param(long logonHandle, IPNC_CMD_TYPE_E cmd, void *pParam, int dataSize)
{
	int ret = 0;
	JXJ_CU_NET_CMD_PARAM_S* pCmdParam = NULL;

	//if(NULL == pParam)
	//	return -1;

	if(((long)NULL == logonHandle) || (0 == logonHandle))
		return -1;

	//��ȡ�������Ӧ�����ò����ӿ�
	pCmdParam = (JXJ_CU_NET_CMD_PARAM_S*)jxj_cu_net_param_cmd(cmd);
	if(NULL != pCmdParam)
	{
		if(pCmdParam->checkParamProc != NULL)
			ret = pCmdParam->checkParamProc(logonHandle, 0, pParam, dataSize);
		if(ret == 0 && pCmdParam->setParamProc != NULL)
			return pCmdParam->setParamProc(logonHandle, 0, pParam, dataSize);
	}
	else		
		__ERR("pCmdParam is null!\n");

	__ERR("pParam check is error!\n");
	return -1;
}

int jxj_cu_ipnc_ptz_ctrl(long logonHandle, void *ptzPacket)
{
	int ret = 0;
	IPNC_PTZ_CTRL_S *pPtzCtrl    = NULL;
	JPTZControl jPtzCtrl = {0};
	
	if(((long)NULL == logonHandle) 
		 || (0 == logonHandle)
		 || (NULL == ptzPacket))
		return -1;

	pPtzCtrl = (IPNC_PTZ_CTRL_S *)ptzPacket;

	//printf(">>>>>>>>>>>>>>>>>>>pPtzCtrl->u16PtzCmd: 	     %x\n", pPtzCtrl->u16PtzCmd);
	//printf(">>>>>>>>>>>>>>>>>>>pPtzCtrl->struPreset.u8Speed: %d\n", pPtzCtrl->struPreset.u8Speed);
	//printf(">>>>>>>>>>>>>>>>>>>pPtzCtrl->struPreset.u8PresetNo: %d\n", pPtzCtrl->struPreset.u8PresetNo);
	switch(pPtzCtrl->u16PtzCmd)
	{
		case PTZ_CMD_STOP:	// ֹͣ
		{
			jPtzCtrl.action = PTZ_STOP;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}	
		case PTZ_CMD_SET_AUTOSCAN_START:	// �Զ�
		{
			jPtzCtrl.action = PTZ_AUTO;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}	
		case PTZ_CMD_LEFT:	// ��
		{
			jPtzCtrl.action = PTZ_LEFT;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}	
		case PTZ_CMD_RIGHT:	// ��
		{
			jPtzCtrl.action = PTZ_RIGHT;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}	
		case PTZ_CMD_UP:	// ��
		{
			jPtzCtrl.action = PTZ_UP;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		case PTZ_CMD_DOWN:	// ��
		{
			jPtzCtrl.action = PTZ_DOWN;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		case PTZ_CMD_LEFT_UP:	//����
		{
			jPtzCtrl.action = PTZ_LEFT_UP;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		case PTZ_CMD_LEFT_DOWN:	//����
		{
			jPtzCtrl.action = PTZ_LEFT_DOWN;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		case PTZ_CMD_RIGHT_UP:	//����
		{
			jPtzCtrl.action = PTZ_RIGHT_UP;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		case PTZ_CMD_RIGHT_DOWN:	//����
		{
			jPtzCtrl.action = PTZ_RIGHT_DOWN;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		case PTZ_CMD_SET_PRESET:	// ����Ԥ�õ�
		{
			jPtzCtrl.action = PTZ_SET_PP;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8PresetNo;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		case PTZ_CMD_GOTO_PRESET:	// ����Ԥ�õ�
		{
			jPtzCtrl.action = PTZ_USE_PP;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8PresetNo;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		case PTZ_CMD_CLR_PRESET:	// ɾ��Ԥ�õ�
		{
			jPtzCtrl.action = PTZ_DEL_PP;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8PresetNo;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		case PTZ_CMD_ZOOM_TELE:	// ����Ŵ�
		{
			jPtzCtrl.action = PTZ_ADD_ZOOM;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		case PTZ_CMD_ZOOM_WIDE:	// ������С
		{
			jPtzCtrl.action = PTZ_SUB_ZOOM;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		case PTZ_CMD_FOCUS_FAR:	// Զ����
		{
			jPtzCtrl.action = PTZ_ADD_FOCUS;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		case PTZ_CMD_FOCUS_NEAR:	// ������
		{
			jPtzCtrl.action = PTZ_SUB_FOCUS;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		/*case PTZ_TURN_ON:	// �����ƹ�
			break;
		case PTZ_TURN_OFF:	// �رյƹ�
			break;
		case PTZ_WIPERS_ON:	// ��ˢ��
			break;
		case PTZ_WIPERS_OFF:	// ��ˢ��
			break;*/
		case PTZ_CMD_SET_CRUISE:	//����Ѳ��
		{
			//pStruCruisePoint = &jPtzCtrl.strCruisePoint;
			ret = jxj_cu_client_ptz_cruise(logonHandle,
										   pPtzCtrl->struCruise.u8CruisePresetNo, 
										   pPtzCtrl->struCruise.u8CruisePresetEnable, 
							               pPtzCtrl->struCruise.u8CruisePresetSec,
							               pPtzCtrl->struCruise.u8CruisePresetSpeed);
			break;
		}
		case PTZ_CMD_SET_CRUISE_START:	//��ʼѲ��
		{
			jPtzCtrl.action = PTZ_START_CRZ;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		case PTZ_CMD_STOP_CRUISE:	//ֹͣѲ��
		{
			jPtzCtrl.action = PTZ_STOP_CRZ;
			jPtzCtrl.param = pPtzCtrl->struPreset.u8Speed;
			ret = jxj_cu_ptz_set(logonHandle, &jPtzCtrl);
			break;
		}
		case PTZ_CMD_DEL_CRUISE:	//ɾ��Ѳ��
		{
			//pStruCruisePoint = &jPtzCtrl.strCruisePoint;
			ret = jxj_cu_client_ptz_cruise(logonHandle,
										   pPtzCtrl->struCruise.u8CruisePresetNo, 
										   pPtzCtrl->struCruise.u8CruisePresetEnable, 
							               pPtzCtrl->struCruise.u8CruisePresetSec,
							               pPtzCtrl->struCruise.u8CruisePresetSpeed);
			break;
		}
		default:
			break;
	}

	return ret;
}


