#ifndef _TI_PARAM_PROC_H
#define _TI_PARAM_PROC_H

#include "ti_type.h"
#include <ipnc_lib.h>

typedef int (*funcGetParam)(long logonHandle, int nPort, void *pData, uint32_t dataSize);
typedef int (*funcSetParam)(long logonHandle, int nPort, void *pData, uint32_t dataSize);
typedef int (*funcCheckParam)(long logonHandle, int nPort, void *pData, uint32_t dataSize);

typedef struct _TI_NET_CMD_PARAM_S_
{
	IPNC_CMD_TYPE_E paramCmd;
	TI_S32			s32MaxSuppPort;	
	funcGetParam	getParamProc;
	funcSetParam	setParamProc;
	funcCheckParam	checkParamProc;		
}TI_NET_CMD_PARAM_S;

/* ��ȡ�豸���� */
/* pParam ��������ṹ�� */
/* u32PackLen �����ṹ�峤��*/
/* ��ȡ�������� */
int ti_send_get_param_cmd(long handle, void* pParam, TI_U32 u32PackLen, TI_U32 u32PackCmd);

/*�������ò�������*/
int ti_send_set_param_cmd(long handle, void* pParam, TI_U32 u32PackLen, TI_U32 u32PackCmd);

/*���ݲ�������,������Ӧ�ṹ����������.
�ɹ����ز������������,
ʧ�ܷ��ؿ�.
*/
long ti_net_param_cmd(IPNC_CMD_TYPE_E paramCmd);

//test
int ti_param_get_net(long handle);
int ti_param_get_net_ball(long handle);

#endif

