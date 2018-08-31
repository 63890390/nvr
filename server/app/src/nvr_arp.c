
#include <nvr_server_headers.h>

/* ��Ҫ����� glibc �汾�� */
#if __GLIBC__ >= 2 && __GLIBC_MINOR >= 1
#include <netpacket/packet.h>
#include <net/ethernet.h> /* ��·�㣨L2��Э�� */
#else
#include <asm/types.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h> /* ��·��Э�� */
#endif
#include <netinet/if_ether.h>
#include <pthread.h>
#include <sys/prctl.h>

#include <net_api.h>
#include <nvr_net_config.h>
#include <nvr_arp.h>

// ��̫����ͷ���ṹ:
/*
   struct ether_header
   {
   u_int8_t ether_dhost[ETH_ALEN];      // destination eth addr
   u_int8_t ether_shost[ETH_ALEN];      // source ether addr   
   u_int16_t ether_type;                // packet type ID field
   } __attribute__ ((__packed__));
   */
//#define ETH_ALEN 		6 	  //��̫����ַ�ĳ���
//#define ETH_HALEN 		14 	  //��̫��ͷ�����ܳ���  (6+6+2)
//#define ETH_ZLEN 		60 	  //����CRCУ�����ݵ�������С����(46+14)
//#define ETH_DATA_LEN 	1500  //֡�����ݵ���󳤶�
//#define ETH_FRAME_LEN 	1514  //����CRC�����̫������(1500+14)
// ARPͷ����Ϣ:
/*
   struct arphdr{
   __be16 ar_hrd;//Ӳ������ 1-Ӳ���ӿ�Ϊ��̫���ӿ�
   __be16 ar_pro;//Э������-0x0800�߲�Э��ΪIPЭ�� 
   unsigned char ar_hln;//Ӳ����ַ����-6�ֽ� MAC
   unsigned char ar_pln;//Э���ַ����-4�ֽ�ΪIP
   __be16 ar_op;//ARP������-1 ARP����

   }
   */
// ARPЭ�����ݽṹ:
/*
   struct ether_arp{
   struct arphdr ea_hdr; //ARPfixed-size header(ARP�̶���С�ı�ͷ)
   u_char arp_sha[ETHER_ADDR_LEN]; //sender hardware address(���Ͷ�Ӳ����ַ)
   u_char arp_spa[4]; //sender protocol address(���Ͷ�Э���ַ)
   u_char arp_tha[ETHER_ADDR_LEN]; // target hardware address(���ն�Ӳ����ַ)
   u_char arp_tpa[4]; //target protocol address(���ն�Э���ַ)
   };
   */
#define arp_hrd ea_hdr.ar_hrd
#define arp_pro ea_hdr.ar_pro
#define arp_hln ea_hdr.ar_hln
#define arp_pln ea_hdr.ar_pln
#define arp_op  ea_hdr.ar_op

// sockaddr_llΪ�豸�޹ص�������ַ�ṹ���������Ͷ˵ĵ�ַ�ṹ
/*
   struct sockaddr_ll
   {
   unsigned short sll_family;
   unsigned short sll_protocol;
   int sll_ifindex;
   unsigned short sll_hatype;
   unsigned char sll_pkttype;
   unsigned char sll_halen;
   unsigned char sll_addr[8];
   };
   */

#define NVR_ETH_NAME "eth0"
#define NVR_ARP_PADDING_SIZE (512) //���ܳ���1400

typedef struct _NVR_NET_ARP_PACK_S_
{
	struct ether_header eh;	//��̫����ͷ��  14
	struct ether_arp ea;	//arp�����ݽṹ 28
} NVR_NET_ARP_PACK_S;		//������CRCУ�����̫����֡����С����Ϊ60���ֽ�

typedef struct _NVR_ARP_IP_CONFLICT_S_
{
	uint32_t u32DevIp;
	ArpIpConflictFunc func;
	gpointer userData;
}NVR_ARP_IP_CONFLICT_S;

// �ж��Ƿ���IP��ͻ��Ҫ��ص���IP��ַ
static GList *gListenIpList;
static GThread *gArpThread = NULL;
static GAsyncQueue *gQueue = NULL;

G_LOCK_DEFINE_STATIC(ip);

static int arp_pack_send(int hSock,void *pbuf,int size, 
					   struct sockaddr * distAddr, int addrSize)
{
    int  block  = 0;	
    int  alllen = size;
    int  sended = 0;

	if (hSock <= 0 || pbuf == NULL || size <= 0 || distAddr == NULL)
		return 0;
	
    while(alllen > 0)
    {	
		sended = sendto(hSock,pbuf,alllen,0, distAddr, addrSize);
		if(0 == sended)
		{
            return NET_RETURN_FAIL;
		}
		else if(sended < 1)
		{
			if(block > NET_MAX_BLOCK_SEND_TIME)
			{
				return NET_RETURN_FAIL;
			}
			if(errno == EWOULDBLOCK || errno == EINTR || errno == EAGAIN)
			{			
				if(block++ < NET_MAX_BLOCK_SEND_TIME)
				{
					usleep(1000);
                    continue;
				}
				else
				{
					break;
				}
			}
			return NET_RETURN_FAIL;
		}
		else
		{		
			pbuf += sended;
			alllen -= sended;
		}
    }
    
    if(alllen > 0)
		return NET_RETURN_FAIL;
    return size;
}

static int nvr_arp_pack_send(const char *pEthName, void *pSendData, int nSendLen)
{
	int sendfd	= 0;
	struct sockaddr_ll send_to;

	if(0 > (sendfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_RARP))))
	{
		j_warning("send socket create failed.");
		return -1;
	}
	
	//����ARP���ݰ�
	bzero(&send_to, sizeof(struct sockaddr_ll));
	send_to.sll_family  = PF_PACKET;
	send_to.sll_ifindex = if_nametoindex(pEthName);//���ض�Ӧ�ӿ����ı��

	//����arp�����
	
	if(arp_pack_send(sendfd, pSendData, nSendLen, (struct sockaddr *)&send_to, sizeof(send_to)) < 0)
	{
		j_warning("Send arp packet failed.");
		net_close_socket(&sendfd);
		return -1;
	}
	
	net_close_socket(&sendfd);
	
	return 0;
}

static int nvr_arp_pack_recv(int sock, char *pbuf, int bufLen)
{
	int len = 0;
	int ret = 0;
	struct sockaddr_ll  recv_to;
	
	if(NULL == pbuf)
		return -1;
		
	if(bufLen < ETH_FRAME_LEN)
		return -1;
		
	//����ARP��Ӧ��
	len = sizeof(recv_to);
	bzero(pbuf, bufLen);
	bzero(&recv_to, sizeof(recv_to));
	
	//��������
	if(0 > (ret = net_udp_recv(sock, pbuf, bufLen, 0,
							   (struct sockaddr*)&recv_to, &len)))
		j_warning("recv failed: %d", ret);
	
	return ret;
}


/*arp���ݰ���ʼ��:
	pEthName: ������,��eth0,eth1....
	arpCtrlCmd: �����룬
				������� ARPOP_REQUEST, 
				��Ӧ���� ARPOP_REPLY.
	pArpReq: 	arp���ݰ�.
�ɹ�����0, ʧ�ܷ���-1.
*/
static int nvr_arp_pack_init(const char *pEthName, int arpCtrlCmd, uint32_t u32DstIp, NVR_NET_ARP_PACK_S *pArpReq)
{
	char ethDstMac[ETH_ALEN] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};//Ŀ��MAC
	char ethSrcMac[ETH_ALEN] = {0};
	char srcIp[16] = {0};
	struct in_addr srcAddr;
	
	if(NULL == pArpReq || 
	   NULL == pEthName)
		return -1;
	
	if(ARPOP_REQUEST != arpCtrlCmd &&
	   ARPOP_REPLY   != arpCtrlCmd)
	   return -1;
	
	bzero(pArpReq, sizeof(NVR_NET_ARP_PACK_S));
	
	/* ��д��̫��ͷ��*/
	if(0 > nvr_netcfg_get_mac_addr((char*)pEthName, ethSrcMac))
	{
		j_warning("get mac failed.");
		return -1;
	}
	
	memcpy(pArpReq->eh.ether_dhost, ethDstMac, ETH_ALEN);	//ԴMAC
	memcpy(pArpReq->eh.ether_shost, ethSrcMac, ETH_ALEN);	//Ŀ��MAC
	pArpReq->eh.ether_type = htons(ETHERTYPE_ARP);			//Э������ARPЭ��
	
	/* ��дarp���� */
	pArpReq->ea.arp_hrd = htons(ARPHRD_ETHER);		//Ӳ�����ͣ������ֽ���ת���������ֽ���
	pArpReq->ea.arp_pro = htons(ETHERTYPE_IP);		//Э������
	pArpReq->ea.arp_hln = ETH_ALEN;					//MAC��ַ����6�ֽ�
	pArpReq->ea.arp_pln = 4;						//IP��ַ����
	pArpReq->ea.arp_op  = htons(arpCtrlCmd);		//�����룬ARP�����
	memcpy(pArpReq->ea.arp_sha, ethSrcMac, ETH_ALEN);
	
	//Դ��IP
	if(0 > nvr_netcfg_get_ip_addr((char*)pEthName, srcIp))
	{
		j_warning("get ipaddr failed.");
		return -1;
	}
	inet_pton(AF_INET, srcIp, &srcAddr);
	memcpy(pArpReq->ea.arp_spa, &srcAddr, sizeof(srcAddr));
	
	//Ŀ��IP
	//inet_pton(AF_INET, pDstIp, &dstAddr);
	u32DstIp = htonl(u32DstIp);
	memcpy(pArpReq->ea.arp_tpa, &u32DstIp, sizeof(u32DstIp));
	
	return 0;
}

static int nvr_arp_send_request_pack(uint32_t u32DevIp)
{
	NVR_NET_ARP_PACK_S stArpPack;
	
	if(nvr_arp_pack_init("eth0", ARPOP_REQUEST, u32DevIp, &stArpPack) < 0)
	{
		j_warning("Initialize arp packet failed.");
		return -1;
	}
	if(nvr_arp_pack_send("eth0", &stArpPack, sizeof(stArpPack)) < 0)
	{
		j_warning("Send arp packet failed.");
		return -1;
	}

	return 0;
}

int nvr_arp_check_ip_conflict(uint32_t u32DevIp)
{
	int nRet, nSock;
	int bRecv = 0;
	uint8_t szRecvMac[ETH_ALEN];
	gint64 startTime, curTime;
	NVR_NET_ARP_PACK_S *pArpPack;
	uint8_t szRecvData[2048];
	
	nSock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if(nSock < 0)
	{
		j_warning("Create arp socket failed.");
		return -1;
	}

	if(nvr_arp_send_request_pack(u32DevIp) < 0)
	{
		j_warning("Arp send request packet failed.");
		close(nSock);
		return -1;
	}

	u32DevIp = htonl(u32DevIp);
	startTime = g_get_monotonic_time();
	curTime = startTime;

	do
	{
		nRet = net_select(&nSock, 1, 0x1, 1000);
		if(nRet < 0)
		{
			j_warning("Select arp socket failed.");
			close(nSock);
			return -1;
		}
		else if(nRet == (nSock | 0x10000))
		{
			if((nRet = nvr_arp_pack_recv(nSock, (char *)szRecvData, sizeof(szRecvData))) < 0)
			{
				j_warning("Receive arp data failed.");
				close(nSock);
				return -1;
			}
			pArpPack = (NVR_NET_ARP_PACK_S *)szRecvData;
			//j_debug("arp_spa: %u.%u.%u.%u", 
			//		pArpPack->ea.arp_spa[0], pArpPack->ea.arp_spa[1],
			//		pArpPack->ea.arp_spa[2], pArpPack->ea.arp_spa[3]);
			if(ntohs(pArpPack->ea.arp_op) == ARPOP_REPLY &&
				memcmp(pArpPack->ea.arp_spa, &u32DevIp, 4) == 0)
			{
				if(bRecv == 0)
				{
					bRecv = 1;
					memcpy(szRecvMac, pArpPack->ea.arp_sha, ETH_ALEN);
				}
				else if(memcmp(szRecvMac, pArpPack->ea.arp_sha, ETH_ALEN) != 0)
				{
					close(nSock);
					return 1;
				}
			}
		}
		
		curTime = g_get_monotonic_time();
	}while(curTime - startTime < 1000000);
	close(nSock);

	return 0;
}

static gpointer __nvr_arp_conflict_func(gpointer data)
{
	GList *list;
	NVR_ARP_IP_CONFLICT_S *pIpConflict;
	gpointer cmd;

	while(cmd != NULL)
	{
		G_LOCK(ip);
		for(list = g_list_first(gListenIpList); list != NULL; list = g_list_next(list))
		{
			pIpConflict = (NVR_ARP_IP_CONFLICT_S *)list->data;
			if(nvr_arp_check_ip_conflict(pIpConflict->u32DevIp) == 1)	// ip conflict
			{
				if(pIpConflict->func)
					pIpConflict->func(pIpConflict->u32DevIp, pIpConflict->userData);
			}
		}
		G_UNLOCK(ip);
		
		cmd = g_async_queue_timeout_pop(gQueue, G_USEC_PER_SEC * 5);
	}
	
	return NULL;
}

int nvr_arp_get_mac(uint32_t u32DevIp, uint8_t *pDevMac)
{
	int nRet, nSock;
	gint64 startTime, curTime;
	NVR_NET_ARP_PACK_S *pArpPack;
	uint8_t szRecvData[2048];

	if(u32DevIp == 0)
		return -1;
	nSock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if(nSock < 0)
	{
		j_warning("Create arp socket failed.");
		return -1;
	}
	
	if(nvr_arp_send_request_pack(u32DevIp) < 0)
	{
		j_warning("Arp send request packet failed.");
		close(nSock);
		return -1;
	}
	
	u32DevIp = htonl(u32DevIp);
	startTime = g_get_monotonic_time();
	curTime = startTime;
	
	do
	{
		nRet = net_select(&nSock, 1, 0x1, 1000);
		if(nRet < 0)
		{
			j_warning("Select arp socket failed.");
			close(nSock);
			return -1;
		}
		else if(nRet == (nSock | 0x10000))
		{
			if((nRet = nvr_arp_pack_recv(nSock, (char *)szRecvData, sizeof(szRecvData))) < 0)
			{
				j_warning("Receive arp data failed.");
				close(nSock);
				return -1;
			}
			pArpPack = (NVR_NET_ARP_PACK_S *)szRecvData;
			//j_debug("arp_spa: %u.%u.%u.%u", 
			//		pArpPack->ea.arp_spa[0], pArpPack->ea.arp_spa[1],
			//		pArpPack->ea.arp_spa[2], pArpPack->ea.arp_spa[3]);
			if(ntohs(pArpPack->ea.arp_op) == ARPOP_REPLY &&
				memcmp(pArpPack->ea.arp_spa, &u32DevIp, 4) == 0)
			{
				memcpy(pDevMac, pArpPack->ea.arp_sha, ETH_ALEN);
				close(nSock);
				return ETH_ALEN;
			}
		}
		else
		{
			nvr_arp_send_request_pack(u32DevIp);
		}
		
		curTime = g_get_monotonic_time();
	}while(curTime - startTime < 1000000);
	close(nSock);

	return -1;
}

void nvr_arp_add_listen_ip(uint32_t u32DevIp, ArpIpConflictFunc func, gpointer userData)
{
	NVR_ARP_IP_CONFLICT_S *pIpConflict;

	pIpConflict = g_malloc0(sizeof(NVR_ARP_IP_CONFLICT_S));
	pIpConflict->u32DevIp = u32DevIp;
	pIpConflict->func = func;
	pIpConflict->userData = userData;
	
	G_LOCK(ip);
	gListenIpList = g_list_prepend(gListenIpList, pIpConflict);
	G_UNLOCK(ip);
}

void nvr_arp_remove_listen_ip(uint32_t u32DevIp)
{
	GList *list;
	NVR_ARP_IP_CONFLICT_S *pIpConflict;
	
	G_LOCK(ip);
	for(list = g_list_first(gListenIpList); list != NULL; list = g_list_next(list))
	{
		pIpConflict = (NVR_ARP_IP_CONFLICT_S *)list->data;
		if(pIpConflict->u32DevIp == u32DevIp)
		{
			gListenIpList = g_list_delete_link(gListenIpList, list);
			g_free(pIpConflict);
			break;
		}
	}
	G_UNLOCK(ip);
}

int nvr_arp_init()
{
	gQueue = g_async_queue_new ();
	
	// ��Ϊ���̼߳���һ�����ڱȽ�����ʱ�䣬
	// ���Բ��ڶ�ʱ������ʵ���������
	gArpThread = g_thread_new("ARP", __nvr_arp_conflict_func, NULL);

	return 0;
}

void nvr_arp_uninit()
{
	g_async_queue_push(gQueue, GINT_TO_POINTER(1));
	g_thread_join(gArpThread);
	g_async_queue_unref(gQueue);
	
	gListenIpList = g_list_remove_all(gListenIpList, g_free);
}


