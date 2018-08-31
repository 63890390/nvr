
#include "jxj_cu_heads.h"
#include "jxj_cu_ipnc_mng.h"
#include "jxj_cu_search.h"
#include "jxj_cu_logon.h"


static JXJ_CU_PROTOCOL_MNG *gMngHead = NULL;
static pthread_mutex_t gListMutex = PTHREAD_MUTEX_INITIALIZER;

static void jxj_cu_ipnc_mng_add_to_list(JXJ_CU_PROTOCOL_MNG *pMng)
{
	pthread_mutex_lock(&gListMutex);
	if(gMngHead == NULL)
	{
		gMngHead = pMng;
		pMng->next = NULL;
	}
	else
	{
		pMng->next = gMngHead;
		gMngHead = pMng;
	}
	pthread_mutex_unlock(&gListMutex);
}

static void jxj_cu_ipnc_mng_del_from_list(JXJ_CU_PROTOCOL_MNG *pMng)
{
	if(pMng == NULL)
		return;
	pthread_mutex_lock(&gListMutex);
	if(pMng == gMngHead)
	{
		gMngHead = gMngHead->next;
	}
	else
	{
		JXJ_CU_PROTOCOL_MNG *node = gMngHead;
		while(node->next != NULL)
		{
			if(node->next == pMng)
			{
				node->next = pMng->next;
				break;
			}
			node = node->next;
		}
	}
	pthread_mutex_unlock(&gListMutex);
}

void jxj_cu_ipnc_mng_print_list()
{
	int i;
	JXJ_CU_PROTOCOL_MNG *node = gMngHead;
	printf("The jxj cu information ===>\n");
	pthread_mutex_lock(&gListMutex);
	while(node != NULL)
	{
		printf("handle: %ld(%p)\n", (long)node, node);
		printf("\tIP address: %s\n", node->ipAddr);
		printf("\tPort: %d\n", node->port);
		printf("\tUser: %s, Password: %s\n", node->user, node->passwd);
		printf("\tRefence count: %d\n", node->refCount);
		for(i = 0; i < 2; i++)
		{
			JXJ_CU_STREAM_S *pStream = (JXJ_CU_STREAM_S*)node->stream[i];
			if(pStream != NULL)
			{
				printf("\tStream handle 0: %ld(%p)\n", (long)pStream, pStream);
				printf("\t\tChannel: %d, Stream: %d\n", pStream->chn, pStream->streamNo);
				printf("\t\tPool Channel: %d, Stream: %d\n", pStream->poolChn, pStream->poolStreamNo);
				printf("\t\tReal play handle: %ld\n", pStream->lRealPlayHandle);
				printf("\t\tVideo id: %ld\n", pStream->videoId);
				printf("\t\tRefence count: %d\n", pStream->refCount);
			}
		}
		node = node->next;
	}
	pthread_mutex_unlock(&gListMutex);
}

int jxj_cu_ipnc_mng_check_handle_valid(JXJ_CU_PROTOCOL_MNG *pMng)
{
	JXJ_CU_PROTOCOL_MNG *node = gMngHead;
	if(pMng == NULL)
		return 0;
	pthread_mutex_lock(&gListMutex);
	while(node != NULL)
	{
		if(node == pMng)
		{
			pthread_mutex_unlock(&gListMutex);
			return 1;
		}
		node = node->next;
	}
	pthread_mutex_unlock(&gListMutex);
	return 0;
}

int jxj_cu_ipnc_mng_check_ipnc_handle_valid(JXJ_CU_PROTOCOL_MNG *pMng, JXJ_CU_STREAM_S *pStream)
{
	JXJ_CU_PROTOCOL_MNG *node = gMngHead;
	if(pMng == NULL || pStream == NULL)
		return 0;
	pthread_mutex_lock(&gListMutex);
	while(node != NULL)
	{
		if(node == pMng && (pMng->stream[0] == pStream || pMng->stream[1] == pStream))
		{
			pthread_mutex_unlock(&gListMutex);
			return 1;
		}
		node = node->next;
	}
	pthread_mutex_unlock(&gListMutex);
	return 0;
}

void jxj_cu_ipnc_mng_ref(JXJ_CU_PROTOCOL_MNG *pMng)
{
	pMng->refCount++;
}

void jxj_cu_ipnc_mng_unref(JXJ_CU_PROTOCOL_MNG *pMng)
{
	if(--pMng->refCount == 0)
	{
		if(pMng->stream[0] != NULL || pMng->stream[1] != NULL)
		{
			//printf("Warning %x: We should close resource of stream handle before closing ipnc handle.\n", (long*)pMng);
			//printf("pMng->stream[0] :%x ,pMng->stream[1]: %x.\n", pMng->stream[0], pMng->stream[1] );
			if(pMng->stream[0] != NULL)
			{
				jxj_cu_ipnc_stop_get_stream((long)pMng, (long)pMng->stream[0]);
			}
			if(pMng->stream[1] != NULL)
			{
				jxj_cu_ipnc_stop_get_stream((long)pMng, (long)pMng->stream[1]);
			}
		}
		jxj_cu_ipnc_mng_del_from_list(pMng);

		free(pMng);
	}
}

int jxj_cu_ipnc_connect(int poolCh, const char *ipAddr, int port, const char *user, const char *passwd, long *ipncHandle)
{
	int sock;
	char strPort[32];
	JXJ_CU_PROTOCOL_MNG *pMng;
	JXJ_CU_PROTOCOL_MNG *node = gMngHead;

	if(ipncHandle == NULL)
	{
		printf("The ipnc handle of ipnc connect is null.\n");
		return -1;
	}
	
	// ���ж��������Ƿ����ipnc�����˽ṹ
	pthread_mutex_lock(&gListMutex);
	while(node != NULL)
	{
		if(node->poolCh == poolCh
			&& (strcmp(node->ipAddr, ipAddr) == 0)
			&& (node->port == port)
			&& (strcmp(node->user, user) == 0)
			&& (strcmp(node->passwd, passwd) == 0))
		{
			jxj_cu_ipnc_mng_ref(node);
			*ipncHandle = (long)node;
			pthread_mutex_unlock(&gListMutex);

			printf("The ipnc handle of ipnc connect is already exist.\n");
			return 0;
		}
		node = node->next;
	}
	pthread_mutex_unlock(&gListMutex);

	// ����Զ��IPNC�˿�,�ж��Ƿ��������ͨ��
	// �ж���ɺ���Ҫ�ر�socket
	sprintf(strPort, "%d", port);
	if((sock = net_tcp_noblock_connect(NULL, NULL, ipAddr, strPort, 100)) < 0)
	{
		printf("Can't connect to the remote ipnc device.\n");
		return -1;
	}
	net_close_socket(&sock);
	// ���û�з���,�����ṹ����ʼ��
	pMng = (JXJ_CU_PROTOCOL_MNG *)malloc(sizeof(JXJ_CU_PROTOCOL_MNG));
	if(pMng == NULL)
	{
		printf("Malloc for JXJ_CU_PROTOCOL_MNG failed.\n");
		return -1;
	}
	memset(pMng, 0, sizeof(JXJ_CU_PROTOCOL_MNG));
	strcpy(pMng->ipAddr, ipAddr);
	pMng->port = port;
	strcpy(pMng->user, user);
	strcpy(pMng->passwd, passwd);
	pMng->poolCh = poolCh;
	pMng->refCount = 1;

	//���ؾ����ַ
	*ipncHandle = (long)pMng;
	//��ӵ�����
	jxj_cu_ipnc_mng_add_to_list(pMng);

	return 0;
}

int jxj_cu_ipnc_disconnect(long ipncHandle)
{
	JXJ_CU_PROTOCOL_MNG *pMng = (JXJ_CU_PROTOCOL_MNG *)ipncHandle;
	if(!jxj_cu_ipnc_mng_check_handle_valid(pMng))
		return -1;
	jxj_cu_ipnc_mng_unref(pMng);

	
	return 0;
}


int jxj_cu_ipnc_start_search(long lHandle)
{
	//printf(">>>>>>>>>lHandle: %lx \n", lHandle);
	return jxj_cu_search_start(lHandle);
}

int jxj_cu_ipnc_stop_search(long lHandle)
{
	//printf(">>>>>>>>>lHandle: %lx \n", lHandle);
	return jxj_cu_search_stop(lHandle);
}

int jxj_cu_ipnc_get_search(long lHandle, IPNC_NET_SEARCH_RES_S *pDev)
{
	if(pDev == NULL)
		return -1;

	if(jxj_cu_search_get(lHandle, pDev))
		return sizeof(IPNC_NET_SEARCH_RES_S);
	
	return 0;
}
int jxj_cu_ipnc_set_search(IPNC_NET_SEARCH_CFG_REQ_S* pIpncSearchCfg)
{

	return jxj_cu_search_set(pIpncSearchCfg);
}




