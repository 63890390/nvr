
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <net_api.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>

#include "ipnc_lib.h"
#include "ti_ipnc_mng.h"
#include "ti_net_search.h"
#include "ti_net_common.h"
#include "ti_net_interface.h"
#include "ti_ping.h"


static TI_IPNC_PROTOCOL_MNG *gMngHead = NULL;
static pthread_mutex_t gListMutex = PTHREAD_MUTEX_INITIALIZER;

static void ti_ipnc_mng_add_to_list(TI_IPNC_PROTOCOL_MNG *pMng)
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

static void ti_ipnc_mng_del_from_list(TI_IPNC_PROTOCOL_MNG *pMng)
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
		TI_IPNC_PROTOCOL_MNG *node = gMngHead;
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

void ti_ipnc_mng_print_list()
{
	int i;
	TI_IPNC_PROTOCOL_MNG *node = gMngHead;
	printf("The ti ipnc information ===>\n");
	pthread_mutex_lock(&gListMutex);
	while(node != NULL)
	{
		printf("ipncHandle: %ld(%p)\n", (long)node, node);
		printf("\tIP address: %s\n", node->ipAddr);
		printf("\tPort: %d\n", node->port);
		printf("\tUser: %s, Password: %s\n", node->user, node->passwd);
		printf("\tRefence count: %d\n", node->refCount);
		for(i = 0; i < 2; i++)
		{
			TI_IPNC_STREAM_S *pStream = (TI_IPNC_STREAM_S*)node->stream[i];
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

int ti_ipnc_mng_check_handle_valid(TI_IPNC_PROTOCOL_MNG *pMng)
{
	TI_IPNC_PROTOCOL_MNG *node = gMngHead;
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

int ti_ipnc_mng_check_ipnc_handle_valid(TI_IPNC_PROTOCOL_MNG *pMng, TI_IPNC_STREAM_S *pStream)
{
	TI_IPNC_PROTOCOL_MNG *node = gMngHead;
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

void ti_ipnc_mng_ref(TI_IPNC_PROTOCOL_MNG *pMng)
{
	pMng->refCount++;
}

void ti_ipnc_mng_unref(TI_IPNC_PROTOCOL_MNG *pMng)
{
	if(--pMng->refCount == 0)
	{
		if(pMng->stream[0] != NULL || pMng->stream[1] != NULL)
		{
			printf("Warning: We should close resource of stream handle before closing ipnc handle.\n");
			if(pMng->stream[0] != NULL)
				ti_ipnc_stop_get_stream((long)pMng, (long)pMng->stream[0]);
			if(pMng->stream[1] != NULL)
				ti_ipnc_stop_get_stream((long)pMng, (long)pMng->stream[1]);
		}
		ti_ipnc_mng_del_from_list(pMng);
		free(pMng);
	}
}

int ti_ipnc_connect(int poolCh, const char *ipAddr, int port, const char *user, const char *passwd, long *ipncHandle)
{
	int sock;
	char strPort[32];
	TI_IPNC_PROTOCOL_MNG *pMng;
	TI_IPNC_PROTOCOL_MNG *node = gMngHead;

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
			ti_ipnc_mng_ref(node);
			*ipncHandle = (long)node;
			pthread_mutex_unlock(&gListMutex);
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
		//printf("Can't connect to the remote ipnc device.\n");
		return -1;
	}
	net_close_socket(&sock);
	// ���û�з���,�����ṹ����ʼ��
	pMng = (TI_IPNC_PROTOCOL_MNG *)malloc(sizeof(TI_IPNC_PROTOCOL_MNG));
	if(pMng == NULL)
	{
		printf("Malloc for TI_IPNC_PROTOCOL_MNG failed.\n");
		return -1;
	}
	memset(pMng, 0, sizeof(TI_IPNC_PROTOCOL_MNG));
	strcpy(pMng->ipAddr, ipAddr);
	pMng->port = port;
	strcpy(pMng->user, user);
	strcpy(pMng->passwd, passwd);
	pMng->poolCh = poolCh;
	pMng->refCount = 1;
	
	*ipncHandle = (long)pMng;
	ti_ipnc_mng_add_to_list(pMng);
	return 0;
}

int ti_ipnc_disconnect(long handle)
{
	TI_IPNC_PROTOCOL_MNG *pMng = (TI_IPNC_PROTOCOL_MNG *)handle;
	if(!ti_ipnc_mng_check_handle_valid(pMng))
		return -1;
	ti_ipnc_mng_unref(pMng);
	return 0;
}

int ti_ipnc_search_cfg(IPNC_NET_SEARCH_CFG_REQ_S* pIpncSearchCfg)
{
	//�����û���������
	return Ti_Net_Search_Cfg(pIpncSearchCfg);
}

int ti_ipnc_start_search(long lHandle)
{
	//__DBUG(">>>>>>>>>lHandle: %lx \n", lHandle);
	return Ti_Net_Search_Do(lHandle);
}

int ti_ipnc_stop_search(long lHandle)
{
	//__DBUG(">>>>>>>>>lHandle: %lx \n", lHandle);
	return Ti_Net_Search_Done(lHandle);
}

int ti_ipnc_get_search(long lHandle, IPNC_NET_SEARCH_RES_S *pDev)
{
	if(pDev == NULL)
		return -1;
	if(1 == Ti_Net_Get_Search(lHandle, pDev))
		return sizeof(IPNC_NET_SEARCH_RES_S);
	
	return 0;
}

int ti_ipnc_test_ipc(const char* DesIP, const char* User, 
					 const char* Password, const char* port)
{
	char sendBuf[1024];
	int sock;
	int sendLen;
	int recvLen;
	TI_NET_HDR_S *pNetHdr = (TI_NET_HDR_S *)sendBuf;
	TI_NET_LOGON_S *pNetLogon = (TI_NET_LOGON_S *)(pNetHdr + 1);

	if(DesIP == NULL || User == NULL || Password == NULL || port == NULL)
		return -1;
		
	sock = net_tcp_noblock_connect(NULL, NULL, DesIP, port, 100);
	if(sock < 0)
		return -1;
	net_set_sock_noblock(sock);
	
	net_set_net_hdr((TI_NET_HDR_S *)sendBuf, sizeof(TI_NET_LOGON_S), TI_CMD_LOGON_SERVER, 0, 0);

	strcpy(pNetLogon->szUsr, User);
	strcpy(pNetLogon->szPsw, Password);

	ti_net_encrypt(pNetLogon->szUsr, strlen(pNetLogon->szUsr));
	ti_net_encrypt(pNetLogon->szPsw, strlen(pNetLogon->szPsw));
	sendLen = sizeof(TI_NET_HDR_S) + sizeof(TI_NET_LOGON_S);
	if(net_tcp_noblock_send(sock, sendBuf, sendLen, NULL, 100) != sendLen)
	{
		__ERR("(%s:%d:%s)send data to server is failed !\n", __FILE__, __LINE__, __FUNCTION__);
		net_close_socket(&sock);
		return -1;
	}
	if(net_select(&sock, 1, 1, 100) < 0)
	{
		net_close_socket(&sock);
		return -1;
	}
	recvLen = net_tcp_noblock_recv(sock, pNetHdr, TI_NET_HDR_LEN, TI_NET_HDR_LEN,  100);
	if(recvLen != TI_NET_HDR_LEN)
	{
		__ERR("(%s:%d:%s)recv data from server is failed !\n", __FILE__, __LINE__, __FUNCTION__);
		net_close_socket(&sock);
		return -1;
	}
	net_close_socket(&sock);
	if(ti_net_check_netHdr(pNetHdr) < 0)
	{
		__ERR("Ti net hdr check failed.\n");
		return -1;
	}	
	if(pNetHdr->s32ErrNo < 0)
		return -1;
	return 0;
}

