
#ifndef __JXJ_CU_MNG_H__
#define __JXJ_CU_MNG_H__

#include "ipnc_lib.h"
#include "jxj_cu_ipnc_realplay.h"

typedef struct _JXJ_CU_PROTOCOL_MNG_
{
	int sock;		//�׽���
	char ipAddr[16];//ip��ַ
	int port;		//�˿�
	char user[32];	//�û���
	char passwd[32];//����
	int status;		//״̬
	int isLogon;	//��¼���
	int refCount;	//���Ӽ���
	void *stream[2];//��������������. 0������, 1������
	int poolCh;		//avpoolͨ����

	struct _JXJ_CU_PROTOCOL_MNG_ *next;
}JXJ_CU_PROTOCOL_MNG;


void jxj_cu_ipnc_mng_print_list();

int jxj_cu_ipnc_mng_check_handle_valid(JXJ_CU_PROTOCOL_MNG *pMng);

int jxj_cu_ipnc_mng_check_ipnc_handle_valid(JXJ_CU_PROTOCOL_MNG *pMng, JXJ_CU_STREAM_S *pStream);
void jxj_cu_ipnc_mng_ref(JXJ_CU_PROTOCOL_MNG *pMng);

void jxj_cu_ipnc_mng_unref(JXJ_CU_PROTOCOL_MNG *pMng);

int jxj_cu_ipnc_connect(int poolCh, const char *ipAddr, int port, 
				   const char *user, const char *passwd, long *ipncHandle);

int jxj_cu_ipnc_disconnect(long ipncHandle);

int jxj_cu_ipnc_start_search(long lHandle);
int jxj_cu_ipnc_stop_search(long lHandle);

int jxj_cu_ipnc_get_search(long lHandle, IPNC_NET_SEARCH_RES_S *pDev);
int jxj_cu_ipnc_set_search(IPNC_NET_SEARCH_CFG_REQ_S* pIpncSearchCfg);


#endif


