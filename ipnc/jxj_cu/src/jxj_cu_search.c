#include "jxj_cu_heads.h"

#include "mb_api.h"
#include "jxj_cu_logon.h"
#include "jxj_cu_search.h"

#define JXJ_CU_SEARCH_MAX_CLIENT_NUM 50

typedef struct mb_msg_s {
 
    char    src[MB_SERIAL_LEN];     //ԴID
    char    dst[MB_SERIAL_LEN];     //Ŀ��ID
    int     msg_id;                 //����ID
    int     req_no;                 //�������
    int     args;                   //�����û��ǻ�ȡMB_MSG_DIR_E
    int     port;                   //ͨ���ĸ��˿ڷ���ȥ��

    int     error;                  //������

    char    user[MB_USER_LEN];      //�û���cfgʱ�õ�
    char    pass[MB_PASS_LEN];      //����      cfgʱ��

    int     size;
    char    data[0];                //��Ϣ��
}mb_msg_t;

//������Ϣ
typedef struct _JXJ_CU_SEARCH_INFO_S_
{
	J_Device_T devCfg; //�豸��Ϣ
	char dstId[J_SDK_MAX_ID_LEN]; //�����豸��ʶ�ַ���(�������û��õ�)
	char usr[J_SDK_MAX_NAME_LEN]; //�û���
	char pwd[J_SDK_MAX_PWD_LEN];  //����
}JXJ_CU_SEARCH_INFO_S;

//��������ڵ���Ϣ
typedef struct _JXJ_CU_SEARCH_NODE_S_
{
	JXJ_CU_SEARCH_INFO_S devInfo;//������Ϣ
	struct _JXJ_CU_SEARCH_NODE_S_ *next;
}JXJ_CU_SEARCH_NODE_S;

//�û���Ϣ��
typedef struct _JXJ_CU_SEARCH_USER_TABLE_S_
{
	int id;//�û���ʶID 
	JXJ_CU_SEARCH_NODE_S *pLastNode;//��¼�������ʵĽڵ�
}JXJ_CU_SEARCH_USER_TABLE_S;

//�������ƽṹ��
typedef struct _JXJ_CU_SEARCH_STRUCT_
{
	volatile long searchHld;	//������ʼ���
	volatile uint8_t searching; //��ʼ������ʶ
	volatile int u32DevCnt;		//��������豸��

	JXJ_CU_SEARCH_NODE_S *pSearchNodeHead;//ͷ�ڵ�
	JXJ_CU_SEARCH_NODE_S *pSearchNodeEnd; //β�ڵ�

	pthread_mutex_t lock; //������
	volatile int userCnt; //�û���
	pthread_mutex_t userlock; //�û���ɾ��
	JXJ_CU_SEARCH_USER_TABLE_S userCT[JXJ_CU_SEARCH_MAX_CLIENT_NUM]; //�û���Ϣ��
	
}JXJ_CU_SEARCH_STRUCT;

static JXJ_CU_SEARCH_STRUCT gJxjCuSearch;
/*
static int jxj_cu_search_check_user(long userDefId)
{
	int i = 0;
	pthread_mutex_lock(&gJxjCuSearch.userlock);
	for(; i < JXJ_CU_SEARCH_MAX_CLIENT_NUM; i++)
	{
		if(userDefId == gJxjCuSearch.userCT[i].id)
		{
			pthread_mutex_unlock(&gJxjCuSearch.userlock);
			return 1;
		}
	}
	
	pthread_mutex_unlock(&gJxjCuSearch.userlock);
	return 0;
}*/

//���������û�
static int jxj_cu_search_add_user(long userDefId)
{
	int i = 0;
	pthread_mutex_lock(&gJxjCuSearch.userlock);
	if(JXJ_CU_SEARCH_MAX_CLIENT_NUM <= gJxjCuSearch.userCnt)
	{
		pthread_mutex_unlock(&gJxjCuSearch.userlock);
		return 0;
	}

	for(i = 0; i < JXJ_CU_SEARCH_MAX_CLIENT_NUM; i++)
	{
		if(userDefId == gJxjCuSearch.userCT[i].id)//�Ѿ����
		{
			pthread_mutex_unlock(&gJxjCuSearch.userlock);
			return 1;
		}
	}
	
	for(i = 0; i < JXJ_CU_SEARCH_MAX_CLIENT_NUM; i++)
	{
		if(0 == gJxjCuSearch.userCT[i].id)
		{
			gJxjCuSearch.userCnt++;
			gJxjCuSearch.userCT[i].id = userDefId;
			pthread_mutex_unlock(&gJxjCuSearch.userlock);
			return 1;
		}
	}
	
	pthread_mutex_unlock(&gJxjCuSearch.userlock);
	return 0;
}

//��������û���Ϣ
static JXJ_CU_SEARCH_USER_TABLE_S* jxj_cu_search_get_user(long userDefId)
{
	int i = 0;
	pthread_mutex_lock(&gJxjCuSearch.userlock);
	for(; i < JXJ_CU_SEARCH_MAX_CLIENT_NUM; i++)
	{
		if(userDefId == gJxjCuSearch.userCT[i].id)
		{
			pthread_mutex_unlock(&gJxjCuSearch.userlock);
			return &gJxjCuSearch.userCT[i];
		}
	}
	
	pthread_mutex_unlock(&gJxjCuSearch.userlock);
	return NULL;
}

//ɾ�������û�
static void jxj_cu_search_del_user(long userDefId)
{
	int i = 0;
	pthread_mutex_lock(&gJxjCuSearch.userlock);
	for(; i < JXJ_CU_SEARCH_MAX_CLIENT_NUM; i++)
	{
		if(userDefId == gJxjCuSearch.userCT[i].id)
		{
			gJxjCuSearch.userCT[i].id = 0;
			gJxjCuSearch.userCT[i].pLastNode = NULL;
			gJxjCuSearch.userCnt--;
			pthread_mutex_unlock(&gJxjCuSearch.userlock);
			return;
		}
	}
	
	pthread_mutex_unlock(&gJxjCuSearch.userlock);
}

static int jxj_cu_search_get_user_num(void)
{
	int cnt = 0;
	pthread_mutex_lock(&gJxjCuSearch.userlock);
	cnt = gJxjCuSearch.userCnt;
	pthread_mutex_unlock(&gJxjCuSearch.userlock);
	return cnt;
}


//��ӵ�����
static void jxj_cu_search_add_to_list(JXJ_CU_SEARCH_NODE_S *pResNode)
{
	//β������
	if(gJxjCuSearch.pSearchNodeHead == NULL)
	{
		gJxjCuSearch.pSearchNodeHead = pResNode;
		pResNode->next = NULL;
		gJxjCuSearch.pSearchNodeEnd = gJxjCuSearch.pSearchNodeHead;//β�ڵ�
		gJxjCuSearch.u32DevCnt++;
	}
	else
	{
		gJxjCuSearch.pSearchNodeEnd->next = pResNode;
		pResNode->next = NULL;
		gJxjCuSearch.pSearchNodeEnd = pResNode;//β�ڵ�
		gJxjCuSearch.u32DevCnt++;
	}
}

//�ͷ�����
static void jxj_cu_search_list_free()
{
	JXJ_CU_SEARCH_NODE_S *pResNode;
	JXJ_CU_SEARCH_NODE_S *pTmpResNode;
	pResNode = gJxjCuSearch.pSearchNodeHead;
	while(pResNode != NULL)
	{
		pTmpResNode = pResNode->next;
		free(pResNode);
		pResNode = pTmpResNode;
	}
	gJxjCuSearch.pSearchNodeHead = NULL;
	gJxjCuSearch.pSearchNodeEnd  = NULL;
	//gJxjCuSearch.pSearchLastNode = NULL;
}

#if 0
static void jxj_cu_search_list_print(void)
{
	int i = 0;

	JXJ_CU_SEARCH_NODE_S *pTmpResNode = gJxjCuSearch.pSearchNodeHead;
	while (NULL != pTmpResNode) 
	{
		__DBUG("<<<<<<<<<<>>>>>>>>>>%-2d get ip: %s, %s\n", i++,
				pTmpResNode->devInfo.devCfg.NetworkInfo.network[0].ip, pTmpResNode->devInfo.devCfg.SysCfg.serial_no);
		
		pTmpResNode = pTmpResNode->next; 
	}
}
#endif

//�����豸
static int jxj_cu_search_save_dev(JXJ_CU_SEARCH_INFO_S *pDevIfno)
{
	JXJ_CU_SEARCH_NODE_S *pSearchNode = NULL;
	JXJ_CU_SEARCH_NODE_S *pResNodeTmp = NULL;
	
	if(pDevIfno == NULL)
		return -1;

	pthread_mutex_lock(&gJxjCuSearch.lock);

	if(J_Dev_IPNC_ < (pDevIfno->devCfg.SysCfg.dev_type))
		goto _OUT;
	
	pResNodeTmp = gJxjCuSearch.pSearchNodeHead;
	//�����豸�Ƿ��Ѿ�����
	while(NULL != pResNodeTmp)
	{
		if(0 == memcmp(&pResNodeTmp->devInfo, pDevIfno, 
					   sizeof(JXJ_CU_SEARCH_INFO_S)))
		{
			pthread_mutex_unlock(&gJxjCuSearch.lock);
			return 0;
		}

		pResNodeTmp = pResNodeTmp->next;

	}
	
	pSearchNode = (JXJ_CU_SEARCH_NODE_S*)malloc(sizeof(JXJ_CU_SEARCH_NODE_S));
	if(pSearchNode == NULL)
	{
		pthread_mutex_unlock(&gJxjCuSearch.lock);
		return -1;
	}	
	
	memcpy(&pSearchNode->devInfo, pDevIfno, sizeof(JXJ_CU_SEARCH_INFO_S));
	pSearchNode->next = NULL;
	//__DBUG("<<<<<<<<<<>>>>>>>>>>%x get ip: %s, %s\n",pDevIfno->devCfg.SysCfg.dev_type,
	//			pSearchNode->devInfo.devCfg.NetworkInfo.network[0].ip, pSearchNode->devInfo.devCfg.SysCfg.serial_no);
	//��ӵ�����
	jxj_cu_search_add_to_list(pSearchNode);

_OUT:	
	pthread_mutex_unlock(&gJxjCuSearch.lock);
	
	return 0;
}


//������ʼ��
int jxj_cu_search_init()
{
	memset(&gJxjCuSearch, 0, sizeof(JXJ_CU_SEARCH_STRUCT));
	pthread_mutex_init(&gJxjCuSearch.lock, NULL);
	pthread_mutex_init(&gJxjCuSearch.userlock, NULL);
	return 0;
}

int jxj_cu_search_uninit()
{
	jxj_cu_search_list_free();
	pthread_mutex_destroy(&gJxjCuSearch.lock);
	pthread_mutex_destroy(&gJxjCuSearch.userlock);
	return 0;
}

//�����豸
static int jxj_cu_search_device_cb(mb_cu_notify_t *handle, mb_cu_parm_t *parm)
{
	JXJ_CU_SEARCH_INFO_S devInfo;
	if(parm == NULL)
	{
		__ERR("The pu param is null.\n");
		return MB_NOTIFY_ERR_FAILED;
	}

	/*__DBUG("jxj_cu_search_device_cb ............\n");
	__DBUG("ID : 0x%08x\n", parm->id);
	__DBUG("error : %d\n", parm->error);
	__DBUG("size : %d\n", parm->size);
	__DBUG("data : %s\n", parm->data);
	__DBUG("dst_id : %s\n", parm->dst_id);
	*/
	if(0 ==  parm->error)
	{
		//__DBUG("Get device param...\n");
		switch(parm->id)
		{
			case J_MB_Device_Id:
			{
				//__DBUG("Get device J_MB_Device_Id\n");
				memset(&devInfo, 0, sizeof(devInfo));
				strncpy(devInfo.dstId, parm->dst_id, sizeof(devInfo.dstId)-1);
				memcpy(&devInfo.devCfg, parm->data, sizeof(J_Device_T));
				jxj_cu_search_save_dev(&devInfo);//�����豸
				break;
			}
			case MB_MSG_GET:
			{
				__DBUG("Get device MB_MSG_GET\n");
				break;
			}
			default:
				break;
		}
	}
	
	return parm->error;
}
static mb_cu_notify_t jxj_cu_notify_cb =
{
	.user_arg = NULL,
	.callback = jxj_cu_search_device_cb,
};

int jxj_cu_search_start(long userDefId)
{
	pthread_mutex_lock(&gJxjCuSearch.lock);

	if(0 == userDefId)
	{
		__ERR("jxj_cu_search_start: userDefId is zero\n");
		goto _FAILED;
	}

	if(JXJ_CU_SEARCH_MAX_CLIENT_NUM <= gJxjCuSearch.userCnt)//��ʼ�û����ж�
	{
		__ERR("jxj_cu_search_start: user cnt is max\n");
		goto _FAILED;
	}

	if(gJxjCuSearch.searching)//�ѿ�ʼ������, ��ֱ�����Ӹ��û�
		goto _ADD_USER;
	
	if(!gJxjCuSearch.searching)//�Ƿ��ѿ�ʼ���� 
	{
		//��ʼ����
		gJxjCuSearch.searchHld = (long)mb_query(J_MB_Device_Id, &jxj_cu_notify_cb);//����������
		if(0 != gJxjCuSearch.searchHld)
			gJxjCuSearch.searching = 1;
		else
			goto _FAILED;
	}

_ADD_USER:
	//�����û�
	if(jxj_cu_search_add_user(userDefId))
	{
		pthread_mutex_unlock(&gJxjCuSearch.lock);
		return 0;
	}
	else
		__DBUG("jxj_cu_search_add_user failed.\n");
	
_FAILED:
	pthread_mutex_unlock(&gJxjCuSearch.lock);
	return -1;
}

//����汾ת��
static int jxj_cu_search_sfver_convert(uint32_t *sfver, char *srcSfVerStr)
{
	int i = 0;
	int pointCnt = 0;
	int data[4]  = {0};
	
	if(NULL == srcSfVerStr)
		return -1;
	
	for(i = 0; i < strlen(srcSfVerStr); i++)
	{
		if('.' == srcSfVerStr[i])
			pointCnt++;
	}

	switch(pointCnt)
	{
		case 3:
		{
			sscanf(srcSfVerStr, "%u.%u.%u.%u", 
			       &data[0],&data[1],&data[2],&data[3]);
			*sfver = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
			break;
		}
		case 2:
		{
			sscanf(srcSfVerStr, "%u.%u.%u", 
			       &data[0],&data[1],&data[2]);
			*sfver = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
			break;
		}
		case 1:
		{
			sscanf(srcSfVerStr, "%u.%u", 
			       &data[0],&data[1]);
			*sfver = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
			break;
		}
		default:
			break;
	}
	
	return 0;
}
static void jxj_cu_search_sfver_reconvert(char *dstSfVerStr, uint8_t *srcSfver)
{
	if(srcSfver[0] && srcSfver[1] &&
	   srcSfver[2] && srcSfver[3])
	{
		sprintf(dstSfVerStr,"%u.%u.%u.%u", 
			srcSfver[0], srcSfver[1], srcSfver[2], srcSfver[3]);
	}
	else if(0 == srcSfver[3] && 0 != srcSfver[2])
	{
		sprintf(dstSfVerStr,"%u.%u.%u", 
			srcSfver[0], srcSfver[1], srcSfver[2]);
	}
	else if(0 == srcSfver[3] 
		&& 0 == srcSfver[2] && 0 != srcSfver[1])
	{
		sprintf(dstSfVerStr,"%u.%u", 
			srcSfver[0], srcSfver[1]);
	}
}

//MAC��ַת��
static int jxj_cu_search_convert_mac(uint8_t *dstMac, const char *srcMacStr)
{
	if(sscanf(srcMacStr, "%02x:%02x:%02x:%02x:%02x:%02x", 
	//if(sscanf(srcMacStr, "%02c:%02c:%02c:%02c:%02c:%02c", 
			(int*)&dstMac[0], (int*)&dstMac[1],(int*)&dstMac[2], 
			(int*)&dstMac[3], (int*)&dstMac[4], (int*)&dstMac[5]) != 6)
		return -1;
	
	return 0;
}
static void jxj_cu_search_reconvert_mac(char *dstMacStr, uint8_t *srcMac)
{
	sprintf(dstMacStr, "%02x:%02x:%02x:%02x:%02x:%02x", 
			srcMac[0], srcMac[1],srcMac[2], 
			srcMac[3], srcMac[4], srcMac[5]);

}

//IP��ַת��
static int jxj_cu_search_convert_ip(uint32_t *dstIp, const char *srcIpStr)
{
	unsigned int data[4];
	
	if(sscanf(srcIpStr, "%u.%u.%u.%u", 
			&data[0],&data[1],&data[2],&data[3]) != 4)
		return -1;
	*dstIp = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
	return 0;
}
static void jxj_cu_search_reconvert_ip(char *dstIpStr, unsigned long srcIp)
{
	sprintf(dstIpStr, "%lu.%lu.%lu.%lu", 
			(srcIp >> 24) & 0xff, (srcIp >> 16) & 0xff,
			(srcIp >> 8) & 0xff, (srcIp >> 0) & 0xff);
}

//����Ϊͨ������ cu����ת����ipnc����
static void jxj_cu_search_parse_cu2ipnc(IPNC_NET_SEARCH_RES_S *pIpncRes, JXJ_CU_SEARCH_INFO_S *pDevInfo)
{
	J_Device_T *pDev  = NULL;

	if(NULL == pIpncRes ||NULL == pDevInfo)
		return;
	pDev = &pDevInfo->devCfg;
	
	//���к�
	memcpy(pIpncRes->u8SerialId, pDev->SysCfg.serial_no, sizeof(pDev->SysCfg.serial_no));
	//����汾
	jxj_cu_search_sfver_convert(&pIpncRes->u32SoftVer, 
							 (char *)pDev->SysCfg.software_ver);
	//�豸����
	pIpncRes->u16DevType = (uint16_t)pDev->SysCfg.dev_type;
	//�˿�
	pIpncRes->u16DevPort = (uint16_t)pDev->NetworkInfo.cmd_port;
	//pIpncRes->u16DevPort = (uint16_t)pDev->NetworkInfo.data_port;
	//ip
	jxj_cu_search_convert_ip(&pIpncRes->u32DevIp, 
							 (char *)pDev->NetworkInfo.network[0].ip);
	//mac��ַ
	//__DBUG("pDev->NetworkInfo.network[0].mac[i]: %s\n", pDev->NetworkInfo.network[0].mac);
	jxj_cu_search_convert_mac(pIpncRes->u8MacAddr, 
							  (char*)pDev->NetworkInfo.network[0].mac);
	//dns\DHCPʹ��
	pIpncRes->u8Dns = (uint8_t)pDev->NetworkInfo.auto_dns_enable;
	pIpncRes->u8DHCP = (uint8_t)pDev->NetworkInfo.network[0].dhcp_enable;
	//����
	jxj_cu_search_convert_ip(&pIpncRes->u32DevIpMask, 
							 (char *)pDev->NetworkInfo.network[0].netmask);
	//����
	jxj_cu_search_convert_ip(&pIpncRes->u32DevGwAddr, 
							 (char *)pDev->NetworkInfo.network[0].gateway);
	//DNS
	jxj_cu_search_convert_ip(&pIpncRes->u32DevDns1, 
							 (char *)pDev->NetworkInfo.main_dns);
	jxj_cu_search_convert_ip(&pIpncRes->u32DevDns2, 
							 (char *)pDev->NetworkInfo.backup_dns);

	// private data
	memcpy(pIpncRes->szPriData, pDevInfo->dstId, J_SDK_MAX_ID_LEN);
	memcpy(pIpncRes->szPriData + J_SDK_MAX_ID_LEN, &pDevInfo->devCfg, sizeof(pDevInfo->devCfg));
}

//ipnc����ת����cu����
static void jxj_cu_search_parse_ipnc2cu(JXJ_CU_SEARCH_INFO_S *pDevInfo, IPNC_NET_SEARCH_CFG_REQ_S *pIpncReqCfg)
{
	J_Device_T *pDev  = NULL;

	if(pDevInfo == NULL || pIpncReqCfg == NULL)
		return;
	memset(pDevInfo, 0, sizeof(JXJ_CU_SEARCH_INFO_S));
	pDev = &pDevInfo->devCfg;
	
	memcpy(pDevInfo->dstId, pIpncReqCfg->szPriData, J_SDK_MAX_ID_LEN);
	memcpy(&pDevInfo->devCfg, pIpncReqCfg->szPriData + J_SDK_MAX_ID_LEN, sizeof(pDevInfo->devCfg));
	strncpy(pDevInfo->usr, pIpncReqCfg->szUsrName, sizeof(pDevInfo->usr)-1);
	pDevInfo->usr[sizeof(pDevInfo->usr) - 1] = '\0';
	strncpy(pDevInfo->pwd, pIpncReqCfg->szPsw, sizeof(pDevInfo->pwd)-1);
	pDevInfo->pwd[sizeof(pDevInfo->pwd) - 1] = '\0';
	
	//�˿�
	pDev->NetworkInfo.cmd_port = pIpncReqCfg->u16DevPort;
	//ip
	jxj_cu_search_reconvert_ip((char *)pDev->NetworkInfo.network[0].ip, 
							   pIpncReqCfg->u32DevIp);
	//mac��ַ
	jxj_cu_search_reconvert_mac((char*)pDev->NetworkInfo.network[0].mac,
	           					pIpncReqCfg->u8MacAddr);
	//dns\DHCPʹ��
	pDev->NetworkInfo.auto_dns_enable = pIpncReqCfg->u8Dns;
	pDev->NetworkInfo.network[0].dhcp_enable = pIpncReqCfg->u8DHCP;
	//����
	jxj_cu_search_reconvert_ip((char *)pDev->NetworkInfo.network[0].netmask, 
								pIpncReqCfg->u32DevIpMask);
	//����
	jxj_cu_search_reconvert_ip((char *)pDev->NetworkInfo.network[0].gateway, 
								pIpncReqCfg->u32DevGwAddr);
	//DNS
	jxj_cu_search_reconvert_ip((char *)pDev->NetworkInfo.main_dns,
								pIpncReqCfg->u32DevDns1);
	jxj_cu_search_reconvert_ip((char *)pDev->NetworkInfo.backup_dns, 
								pIpncReqCfg->u32DevDns2);
}

//�������
int jxj_cu_search_get(long userDefId, IPNC_NET_SEARCH_RES_S *pIpncRes)
{
	JXJ_CU_SEARCH_NODE_S *pResNode;
	JXJ_CU_SEARCH_USER_TABLE_S* pUserTb = NULL;

	if(0 == userDefId ||
	   NULL == pIpncRes)
	   return 0;
	
	pthread_mutex_lock(&gJxjCuSearch.lock);
	if(!gJxjCuSearch.searching)
	{	
		pthread_mutex_unlock(&gJxjCuSearch.lock);
		return 0;
	}

	//����û���Ϣ
	pUserTb = jxj_cu_search_get_user(userDefId);
	if(NULL == pUserTb)
	{
		__ERR("user table is null. \n");
		pthread_mutex_unlock(&gJxjCuSearch.lock);
		return 0;
	}

	if(gJxjCuSearch.pSearchNodeHead == NULL)
	{
		pthread_mutex_unlock(&gJxjCuSearch.lock);
		return 0;
	}

	if(NULL == pUserTb->pLastNode)
		pResNode = gJxjCuSearch.pSearchNodeHead;
	else
		pResNode = pUserTb->pLastNode->next;

	if(NULL == pResNode)
	{
		pthread_mutex_unlock(&gJxjCuSearch.lock);
		return 0;
	}

	//��ȡ�����豸��Ϣ cu����ת����IPNC����
	jxj_cu_search_parse_cu2ipnc(pIpncRes, &pResNode->devInfo);
	pUserTb->pLastNode = pResNode;

	//jxj_cu_search_list_print();
	
	pthread_mutex_unlock(&gJxjCuSearch.lock);
	return 1;
}

//���������豸����
int jxj_cu_search_set(IPNC_NET_SEARCH_CFG_REQ_S *pIpncReqCfg)
{
	int ret = 0;
	JXJ_CU_SEARCH_INFO_S devInfo;
	
	if(NULL == pIpncReqCfg)
		return -1;

	pthread_mutex_lock(&gJxjCuSearch.lock);

	//ת������ IPNC����ת��cu����
	jxj_cu_search_parse_ipnc2cu(&devInfo, pIpncReqCfg);

	//������������
	ret = mb_cfg_set(J_MB_Device_Id, devInfo.dstId, 
					devInfo.usr, devInfo.pwd, 
			   		2, sizeof(devInfo.devCfg), &devInfo.devCfg, 
			   		NULL, 1);
	
	pthread_mutex_unlock(&gJxjCuSearch.lock);
	return ret;
}

//��������豸��
int jxj_cu_search_get_dev_cnt(void)
{
	int devCnt = 0;
	pthread_mutex_lock(&gJxjCuSearch.lock);
	devCnt =  gJxjCuSearch.u32DevCnt;
	pthread_mutex_unlock(&gJxjCuSearch.lock);
	
	return devCnt;
}

//ֹͣ����
int jxj_cu_search_stop(long userDefId)
{
	if(0 == userDefId)
		return -1;
	
	pthread_mutex_lock(&gJxjCuSearch.lock);
	jxj_cu_search_del_user(userDefId);
	if(0 == jxj_cu_search_get_user_num())
	{
		jxj_cu_search_list_free();
		mb_release((mb_query_t*)gJxjCuSearch.searchHld);
		gJxjCuSearch.u32DevCnt = 0;
		gJxjCuSearch.searching = 0;
		gJxjCuSearch.searchHld = 0;
	}
	pthread_mutex_unlock(&gJxjCuSearch.lock);
	return 0;
}

