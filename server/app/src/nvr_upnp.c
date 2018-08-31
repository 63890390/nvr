
#include <nvr_headers.h>

/*���Ž� ��װ����*/
#include <upnp_api.h>
#include "nvr_net_common.h"
#include "nvr_net_config.h"
#include "nvr_param_proc.h"
#include "nvr_upnp.h" 

#undef	G_LOG_DOMAIN
#define	G_LOG_DOMAIN "upnp"


/*��ȡ����IP*/
#define GET_LOCAL_IPADDR(name, retBuf)	\
do										\
{	if(-1 == net_get_ip_addr(name,retBuf))	\
	{												\
		perror("get local ip failed:");				\
		return 0;									\
	}												\
}while(0)
	
//����������
typedef enum _NVR_UPNP_CTRL_CMD_E_
{
	NVR_UPNP_START_MAP = 0x01,//��ʼӳ��
	NVR_UPNP_CHECK_MAP = 0x02,//���ӳ��״̬
	NVR_UPNP_STOP_MAP = 0x03,//ֹͣӳ��
}NVR_UPNP_CTRL_CMD_E;


static GThreadPool *gUpnpThreadPool;
static uint32_t gMapLocalIp = 0, gMapLocalGateway = 0;

/*�˿�״̬����*/
//�ı����ݶ˿�ӳ��״̬
static void nvr_change_dataport_status(NVR_UPNP_CFG_S *pUpnpCfg, int val)
{
	pUpnpCfg->u16UpnpDataPortS = val;
}
//�ı�web�˿�ӳ��״̬
static void nvr_change_webport_status(NVR_UPNP_CFG_S *pUpnpCfg, int val)
{
	pUpnpCfg->u16UpnpWebPortS = val;
}
//�ı�rtsp�˿�ӳ��״̬
static void nvr_change_rtspport_status(NVR_UPNP_CFG_S *pUpnpCfg, int val)
{
	pUpnpCfg->u16UpnpRtspPortS = val;
}
//�ı�SDk����˿�ӳ��״̬
static void nvr_change_sdkcmdport_status(NVR_UPNP_CFG_S *pUpnpCfg, int val)
{
	pUpnpCfg->u16UpnpCmdPortS = val;
}
//�ı�SDk RTSP�˿�ӳ��״̬
static void nvr_change_sdkrtspport_status(NVR_UPNP_CFG_S *pUpnpCfg, int val)
{
	pUpnpCfg->u16UpnpJXJDataPortS = val;
}
//�ı�SDk �Խ��˿�ӳ��״̬
static void nvr_change_sdktalkport_status(NVR_UPNP_CFG_S *pUpnpCfg, int val)
{
	pUpnpCfg->u16UpnpTalkPortS = val;
}

/*�˿�ӳ��*/
static int nvr_port_map(unsigned long hd, unsigned int port, char* localIpAddr,
				  unsigned int autoMap, char* infoStr, char *szExternalIp)
{
	int externPort;

	if(port == 0)
		return 0;
	externPort = upnp_add_map_port(hd, localIpAddr, port,
									 port, 0, autoMap, infoStr, szExternalIp);	// tcp
	if(externPort < 0)
	{
		j_warning("Upnp map %s failed!", infoStr);
		return 0;
	}
	j_debug("upnp %s %s:%u map to %s:%d!", infoStr, localIpAddr, port, szExternalIp, externPort);
	return externPort;
}

//ɾ���˿�ӳ��
static void nvr_del_port(unsigned long hd, unsigned int portStatus, unsigned int port)
{
	if(portStatus)
	{	
		if(-1 == upnp_del_map_port(hd, portStatus, 0))
			j_warning("delete Port map %d tcp failed!", port);	
		//if(-1 == upnp_del_map_port(hd, portStatus, 1))
		//	j_warning("delete Port map %d udp failed!", port);
	}
}

/* ���ܣ����ӳ��˿�,����ֵ��1��ɹ�,0ʧ��*/
static int nvr_upnp_add_map_port(NVR_UPNP_CFG_S *pUpnpCfg, char *pUpnpServer, char *pMapLocalIp)
{
	unsigned long hd;
	
	unsigned int webPort  = pUpnpCfg->u16UpnpWebPort;
	unsigned int rtspPort	= pUpnpCfg->u16UpnpRtspPort;

	unsigned int cmdPort      = pUpnpCfg->u16UpnpCmdPort;
	unsigned int jxjDataPort  = pUpnpCfg->u16UpnpJXJDataPort;
	unsigned int talkPort     = pUpnpCfg->u16UpnpTalkPort;
	
	unsigned int autoMap  = 1;//pUpnpCfg->u8UpnpModel;
	char szExternalIp[32] = {0};
	
	//j_debug("upnp server:%s",pUpnpServer);
	hd = upnp_map_init(pUpnpServer);
	if (hd)
	{
		//WEB�˿�
		if(!upnp_check_port_mapped(hd, pUpnpCfg->u16UpnpWebPortS, 0))
		{
			pUpnpCfg->u16UpnpWebPortS = nvr_port_map(hd, webPort,pMapLocalIp,
				  								autoMap, "NVRWeb", szExternalIp);
			g_strlcpy(pUpnpCfg->szExternalIp, szExternalIp, sizeof(pUpnpCfg->szExternalIp));
		}
		//����RTSP�˿�
		if(!upnp_check_port_mapped(hd, pUpnpCfg->u16UpnpRtspPortS, 0))
		{
			pUpnpCfg->u16UpnpRtspPortS = nvr_port_map(hd, rtspPort,pMapLocalIp,
				  								autoMap, "NVRRtsp", szExternalIp);
			g_strlcpy(pUpnpCfg->szExternalIp, szExternalIp, sizeof(pUpnpCfg->szExternalIp));
		}
		//SDK����˿�
		if(!upnp_check_port_mapped(hd, pUpnpCfg->u16UpnpCmdPortS, 0))
		{
			pUpnpCfg->u16UpnpCmdPortS = nvr_port_map(hd, cmdPort,pMapLocalIp,
				  								autoMap, "NVRCmd", szExternalIp);
			g_strlcpy(pUpnpCfg->szExternalIp, szExternalIp, sizeof(pUpnpCfg->szExternalIp));
		}
		//SDK RTSP�˿�
		if(!upnp_check_port_mapped(hd, pUpnpCfg->u16UpnpJXJDataPortS, 0))
		{
			pUpnpCfg->u16UpnpJXJDataPortS = nvr_port_map(hd, jxjDataPort,pMapLocalIp,
					  								autoMap, "NVRData", szExternalIp);
			g_strlcpy(pUpnpCfg->szExternalIp, szExternalIp, sizeof(pUpnpCfg->szExternalIp));
		}
		//SDK Talk�˿�
		if(!upnp_check_port_mapped(hd, pUpnpCfg->u16UpnpTalkPortS, 0))
		{
			pUpnpCfg->u16UpnpTalkPortS = nvr_port_map(hd, talkPort,pMapLocalIp,
				  								autoMap, "NVRTalk", szExternalIp);
			g_strlcpy(pUpnpCfg->szExternalIp, szExternalIp, sizeof(pUpnpCfg->szExternalIp));
		}
		
		upnp_map_destroy(hd);
		return 1;
	}
	else
		j_warning("no network device!");

	return 0;
}

/* ���ܣ�ɾ��ӳ��˿�, ����ֵ��1��ɹ�,0ʧ��*/
static int nvr_upnp_del_map_port(NVR_UPNP_CFG_S *pUpnpCfg, char *pUpnpServer)
{
	unsigned long hd;
	
	//unsigned int dataPort = pUpnpCfg->u16UpnpDataPort;
	unsigned int webPort  = pUpnpCfg->u16UpnpWebPort ;
	unsigned int rtspPort = pUpnpCfg->u16UpnpRtspPort;

	unsigned int cmdPort      = pUpnpCfg->u16UpnpCmdPort;
	unsigned int jxjDataPort  = pUpnpCfg->u16UpnpJXJDataPort;
	unsigned int talkPort     = pUpnpCfg->u16UpnpTalkPort;

	hd = upnp_map_init(pUpnpServer);
	if(hd)
	{
		/*ɾ��ӳ��˿�*/
		//���ݶ˿�
		//nvr_del_port(hd, pUpnpCfg->u16UpnpDataPortS, dataPort);
		//nvr_change_dataport_status(pUpnpCfg, 0);

		//WEB�˿�
		nvr_del_port(hd, pUpnpCfg->u16UpnpWebPortS, webPort);
		nvr_change_webport_status(pUpnpCfg, 0);
		
		//RTSP�˿�
		nvr_del_port(hd, pUpnpCfg->u16UpnpRtspPortS, rtspPort);
		nvr_change_rtspport_status(pUpnpCfg, 0);

		//SDK����˿�
		nvr_del_port(hd, pUpnpCfg->u16UpnpCmdPortS, cmdPort);
		nvr_change_sdkcmdport_status(pUpnpCfg, 0);
		
		//SDK RTSP�˿�
		nvr_del_port(hd, pUpnpCfg->u16UpnpJXJDataPortS, jxjDataPort);
		nvr_change_sdkrtspport_status(pUpnpCfg, 0);
		
		//SDK Talk�˿�
		nvr_del_port(hd, pUpnpCfg->u16UpnpTalkPortS, talkPort);
		nvr_change_sdktalkport_status(pUpnpCfg, 0);
		
		upnp_map_destroy(hd);

		memset(pUpnpCfg->szUpnpSvr, 0, sizeof(pUpnpCfg->szUpnpSvr));
		memset(pUpnpCfg->szExternalIp, 0, sizeof(pUpnpCfg->szExternalIp));
		return 1;
	}
	
	return 0;
}

static int nvr_upnp_get_net_info(char *pUseIP, int nUseIpLen, char *pUseGateway, int nUseGatewayLen)
{	
	char szIp[32];
	uint32_t eth0Ip = 0, eth0_1Ip = 0;
	uint32_t eth0Gateway = 0;
	uint32_t useIp, useGateway;
	int nMetric;
	
	if(nvr_netcfg_get_gw_addr("eth0", szIp, &nMetric) == 0)
		eth0Gateway = net_ip_a2n(szIp);
	else
	{
		j_warning("Get eth0 gateway ip failed.");
		return -1;
	}
	useGateway = eth0Gateway;
	
	if(nvr_netcfg_get_ip_addr("eth0", szIp) == 0)
		eth0Ip = net_ip_a2n(szIp);
	if(nvr_netcfg_get_ip_addr("eth0:1", szIp) == 0)
		eth0_1Ip = net_ip_a2n(szIp);
	//j_debug("eth0 Ip: %08x", eth0Ip);
	//j_debug("eth0 Gateway: %08x", eth0Gateway);
	//j_debug("eth0:1 Ip: %08x", eth0_1Ip);
	if(eth0_1Ip != 0)
	{
		useIp = eth0_1Ip;
	}
	else if(eth0Ip != 0)
	{
		useIp = eth0Ip;
	}
	else
	{
		j_warning("Upnp map failed.\n");
		return -1;
	}
	net_ip_n2a(useIp, pUseIP, nUseIpLen);
	net_ip_n2a(useGateway, pUseGateway, nUseGatewayLen);
	
	return 0;
}

//upnp�˿�ӳ���߳�
static int nvr_upnp_start_map()
{
	NVR_UPNP_CFG_S upnpCfg;
	char szIp[32], szUseIp[32], szUseGateway[32];
	uint32_t useIp, useGateway;
	
	if(nvr_upnp_get_net_info(szUseIp, sizeof(szUseIp), szUseGateway, sizeof(szUseGateway)) < 0)
		return -1;
	
	/*��ȡ ����*/
	nvr_get_upnp_cfg(0, &upnpCfg);
	//j_debug("upnpCfg.u8UpnpOpen: %u\n", upnpCfg.u8UpnpOpen);
	//j_debug("upnpCfg.szUpnpSvr : %s", upnpCfg.szUpnpSvr);
	//j_debug("upnpCfg.u8UpnpModel: %d", upnpCfg.u8UpnpModel);
	
	if(upnpCfg.u8UpnpOpen)/*UPNP�����Ƿ���*/
	{
		useIp = net_ip_a2n(szUseIp);
		useGateway = net_ip_a2n(szUseGateway);
		if(gMapLocalGateway != 0 && (useIp != gMapLocalIp || useGateway != gMapLocalGateway))
		{
			net_ip_n2a(gMapLocalGateway, szIp, sizeof(szIp));
			nvr_upnp_del_map_port(&upnpCfg, szIp);
		}
		gMapLocalIp = useIp;
		gMapLocalGateway = useGateway;
		//�˿�ӳ��
		if (nvr_upnp_add_map_port(&upnpCfg, szUseGateway, szUseIp))
		{
			g_strlcpy(upnpCfg.szUpnpSvr, szUseGateway, sizeof(upnpCfg.szUpnpSvr));
			nvr_set_upnp_cfg(0, &upnpCfg);
		}
		else
		{
			j_warning("nvr upnp add map port failed!");
			return -1;
		}
	}
	else
	{
		if(gMapLocalGateway != 0)
		{
			net_ip_n2a(gMapLocalGateway, szIp, sizeof(szIp));
			nvr_upnp_del_map_port(&upnpCfg, szIp);
			nvr_set_upnp_cfg(0, &upnpCfg);
			gMapLocalIp = 0;
			gMapLocalGateway = 0;
		}
	}
	
	return 0;
}
static int nvr_upnp_stop_map()
{	
	NVR_UPNP_CFG_S upnpCfg;
	char szIp[32];
	
	if(gMapLocalGateway != 0)
	{
		nvr_get_upnp_cfg(0, &upnpCfg);
		net_ip_n2a(gMapLocalGateway, szIp, sizeof(szIp));
		nvr_upnp_del_map_port(&upnpCfg, szIp);
		nvr_set_upnp_cfg(0, &upnpCfg);
		gMapLocalIp = 0;
		gMapLocalGateway = 0;
	}
	
	return 0;
}
//upnp�̴߳�����
static void nvr_upnp_server_func (gpointer data, gpointer user_data)
{
	NVR_UPNP_CTRL_CMD_E cmdVal = GPOINTER_TO_INT(data);

	//ӳ�䴦��
	switch(cmdVal)
	{
		case NVR_UPNP_START_MAP:
		{
			nvr_upnp_start_map();
			break;
		}
		case NVR_UPNP_STOP_MAP:
		{
			nvr_upnp_stop_map();
			break;
		}
		default:
			break;
	}
}

//upnp�̷߳��Ϳ�����Ϣ
static inline gboolean nvr_upnp_send_cmd(NVR_UPNP_CTRL_CMD_E cmdVal)
{
	return g_thread_pool_push(gUpnpThreadPool, GINT_TO_POINTER(cmdVal), NULL);
}

/*��ʱ���¶˿�ӳ��*/
static gboolean nvr_upnp_auto_map_timeout(gpointer user_data)
{
	//ӳ���ɾ��ӳ��
	nvr_upnp_send_cmd(NVR_UPNP_START_MAP);
	return G_SOURCE_CONTINUE;
}

//��ʼ������
int nvr_upnp_init(void)
{	
	gUpnpThreadPool = g_thread_pool_new(nvr_upnp_server_func, NULL, 1, FALSE, NULL);
	g_timeout_add_seconds(30, nvr_upnp_auto_map_timeout, NULL);

	return 0;
}

void nvr_upnp_uninit(void)
{
	j_warning("upnp uninit.");

	nvr_upnp_send_cmd(NVR_UPNP_STOP_MAP);
	g_thread_pool_free(gUpnpThreadPool, FALSE, TRUE);
	
	j_warning("upnp uninit finish.");
}


