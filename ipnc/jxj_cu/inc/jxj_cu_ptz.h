
#ifndef __JXJ_CU_PTZ_H__
#define __JXJ_CU_PTZ_H__

#include "j_sdk.h"

//���Ϳ���ptz������
int jxj_cu_ptz_set(long logonHandle, JPTZControl *cfg);

/* ptz���� */
int jxj_cu_client_crtl_ptz(long logonHandle,  
						   JPTZAction action, /*PTZ����������*/
						   uint8_t u8Speed);  /*�ٶ�*/
/* �����Զ�Ѳ�� */
int jxj_cu_client_ptz_cruise(long logonHandle, 
							 uint8_t u8CruisePresetNo, 	   /*Ԥ�ú�*/
							 uint8_t u8CruisePresetEnable, /*ʹ�����*/
							 uint8_t u8CruisePresetSec,    /*����ʱ��*/
							 uint8_t u8CruisePresetSpeed); /*�ٶ�*/

#endif


