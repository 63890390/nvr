
#ifndef __JXJ_CU_SEARCH_H__
#define __JXJ_CU_SEARCH_H__

#include "ipnc_lib.h"

//������ʼ��
int jxj_cu_search_init();
int jxj_cu_search_uninit();

/*��ʼ����:
	�ɹ����ط����û����, ʧ�ܷ���0;
*/
int jxj_cu_search_start(long userDefId);

/*�������:
	id: �û����
	pIpcnDev: ����豸�ռ�
*/
int jxj_cu_search_get(long userDefId, IPNC_NET_SEARCH_RES_S *pIpncRes);

/*��ȡ�����豸��*/
int jxj_cu_search_get_dev_cnt(void);
/*���������豸����*/
int jxj_cu_search_set(IPNC_NET_SEARCH_CFG_REQ_S *pIpncReqCfg);

/*ֹͣ����*/
int jxj_cu_search_stop(long userDefId);

//�������������Ƶ����ð�
void jxj_cu_search_cpy_res2req(IPNC_NET_SEARCH_CFG_REQ_S *pIpncCfgReq,
							   IPNC_NET_SEARCH_RES_S *pIpncRes);




#endif




