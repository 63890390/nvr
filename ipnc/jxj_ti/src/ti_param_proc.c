#include <stdio.h>
#include <string.h>
#include "ti_net_struct.h"
#include "ti_type.h"
#include "ti_struct.h"
#include "ti_net_interface.h"
#include "ti_net_common.h"
#include "net_api.h"
#include "ti_param_proc.h"

#include "ipnc_lib.h"
#include "net_api.h"


static void nvr_string_copy(char* dstStr, int dstStrSize, char* srcStr)
{
	int len = 0;
	
	if(NULL == dstStr || NULL == srcStr)
		return;

	if(0 == strlen(srcStr))
		return;
	
	memset(dstStr, 0, dstStrSize);
	len	 =  strlen(srcStr);
	if(len > (dstStrSize-1))
		len = (dstStrSize-1);
	strncpy(dstStr, srcStr, len);
	dstStr[len+1] = '\0';
}

/*netͨ�ýṹ�庯��************************************************************/
static int ti_param_get_net_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_NET_CFG_S *pNetInfo = (IPNC_NET_CFG_S *)pData;
	TI_DEV_NET_CFG_S devNet;
	int ret = -1;
	int i   =  0;
	
	memset(&devNet, 0, sizeof(TI_DEV_NET_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&devNet, 
								sizeof(TI_DEV_NET_CFG_S), 
								TI_CMD_GET_NET_CFG);
	if(0 < ret)
	{
		//�˿�
		pNetInfo->u16NetPort = devNet.u16NetPort;
		pNetInfo->u16HttpPort= devNet.u16HttpPort;
		
		//ip
		net_ip_n2a(devNet.struEtherCfg[0].u32IpAddr, pNetInfo->ipAddr, 32);
		net_ip_n2a(devNet.struEtherCfg[0].u32SubMask, pNetInfo->subMask, 32);
		net_ip_n2a(devNet.struEtherCfg[0].u32GateWay, pNetInfo->gateWay, 32);
		net_ip_n2a(devNet.u32DnsIp1, pNetInfo->dnsIp1, 32);
		net_ip_n2a(devNet.u32DnsIp2, pNetInfo->dnsIp2, 32);
	
		//mac��ַ
		for(i = 0; i < TI_MAC_ADDR_LEN; i++)
		{
			if(0 <= devNet.struEtherCfg[0].u8MacAddr[i] &&
				    devNet.struEtherCfg[0].u8MacAddr[i] <= 9)
				sprintf(pNetInfo->macAddr + i*2,"0%x", devNet.struEtherCfg[0].u8MacAddr[i]);
			else
				sprintf(pNetInfo->macAddr + i*2,"%x", devNet.struEtherCfg[0].u8MacAddr[i]);
		}
	}
	else
		__ERR("ti_param_get_net_param faile!\n");
	
	
	return ((ret > 0) ? sizeof(IPNC_NET_CFG_S) : ret);
}
static int ti_param_set_net_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_NET_CFG_S *pNetInfo = (IPNC_NET_CFG_S *)pData;
	TI_DEV_NET_CFG_S devNet;
	int ret = -1;

	memset(&devNet, 0, sizeof(TI_DEV_NET_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&devNet, 
								sizeof(TI_DEV_NET_CFG_S), 
								TI_CMD_GET_NET_CFG);
	if(0 < ret)
	{
		//�˿�
		devNet.u16NetPort = pNetInfo->u16NetPort;
		devNet.u16HttpPort = pNetInfo->u16HttpPort;

		//��ַ
		devNet.struEtherCfg[0].u32IpAddr = net_ip_a2n(pNetInfo->ipAddr);
		devNet.struEtherCfg[0].u32SubMask = net_ip_a2n(pNetInfo->subMask);
		devNet.struEtherCfg[0].u32GateWay = net_ip_a2n(pNetInfo->gateWay);
		devNet.u32DnsIp1 = net_ip_a2n(pNetInfo->dnsIp1);
		devNet.u32DnsIp2 = net_ip_a2n(pNetInfo->dnsIp2);

		//mac
		char mac_buf[5] = {'0', 'x'};
		int j = 0;
		for(j = 0; j < TI_MAC_ADDR_LEN; j++)
		{
			strncpy(mac_buf+2, (pNetInfo->macAddr+j*2), 2);
			mac_buf[4] = '\0';
			__DBUG("mac_buf:%s\n", mac_buf);
			devNet.struEtherCfg[0].u8MacAddr[j] = (uint8_t)strtoul(mac_buf, NULL, 16);
		}

		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&devNet, 
									sizeof(TI_DEV_NET_CFG_S), 
									TI_CMD_SET_NET_CFG);
		
	}
	else
		__ERR("ti_param_set_net_param faile!\n");
	
	return ret;
}
static int ti_param_check_net_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
	
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_NET_CFG_S): %d\n", sizeof(IPNC_NET_CFG_S));
	if(dataSize != sizeof(IPNC_NET_CFG_S))
		return -1;
		
	return 0;
}

/*devͨ�ýṹ�庯��************************************************************/
static int ti_param_get_dev_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_CFG_S *pDevInfo = NULL;
	TI_DEV_INFO_S devInfo;
	int ret = -1;

	memset(&devInfo, 0, sizeof(TI_DEV_INFO_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&devInfo, 
								sizeof(TI_DEV_INFO_S), 
								TI_CMD_GET_DEV_INFO);
	if(0 < ret)
	{
		pDevInfo = (IPNC_DEV_CFG_S *)pData;
		//�豸ID
		nvr_string_copy(pDevInfo->serialId, sizeof(pDevInfo->serialId), 
						(char*)devInfo.stStableInfo.u8SerialId);

		//Ӳ���汾
		net_ip_n2a(devInfo.stStableInfo.u32HwVer, pDevInfo->hwVer, 32);

		//����汾
		net_ip_n2a(devInfo.stStableInfo.u32SoftVer, pDevInfo->sofrVer, 32);

		//�ں˰汾
		net_ip_n2a(devInfo.stStableInfo.u32CoreVer, pDevInfo->codeVer, 32);

		//�豸�ɸ�����Ϣ
		nvr_string_copy(pDevInfo->stVarInfo.szDevName, sizeof(pDevInfo->stVarInfo.szDevName), 
						(char*)devInfo.stVarInfo.szDevName);
		//����0 ����1Ӣ��
		pDevInfo->stVarInfo.u8Language = devInfo.stVarInfo.u8Language;
		//��ʽ1 pal 0 ntfc
		pDevInfo->stVarInfo.u8PalStand = devInfo.stVarInfo.u8PalStand;
		//��ԴƵ��0 50Hz 1 60HZ
		pDevInfo->stVarInfo.u8Hz	   = devInfo.stVarInfo.u8Hz;
		
		//__DBUG("pDevInfo->serialId: %s\n",pDevInfo->serialId);
		//__DBUG("pDevInfo->hwVer: %s\n",pDevInfo->hwVer);
		//__DBUG("pDevInfo->sofrVer: %s\n",pDevInfo->sofrVer);
		//__DBUG("pDevInfo->codeVer: %s\n",pDevInfo->codeVer);
		
	}
	else
		__ERR("ti_param_get_dev_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_DEV_CFG_S) : ret);
	
}
static int ti_param_set_dev_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	
	IPNC_DEV_CFG_S *pDevInfo = (IPNC_DEV_CFG_S *)pData;
	TI_DEV_INFO_S devInfo;
	int ret = -1;

	memset(&devInfo, 0, sizeof(TI_DEV_INFO_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&devInfo, 
								sizeof(TI_DEV_INFO_S), 
								TI_CMD_GET_DEV_INFO);
	if(0 < ret)
	{
		//�豸ID
		//nvr_string_copy(devInfo.stStableInfo.u8SerialId, sizeof(devInfo.stStableInfo.u8SerialId), 
		//				pDevInfo->serialId);

		//Ӳ���汾
		//devInfo.stStableInfo.u32HwVer = strtoul(pDevInfo->hwVer, NULL, 10);
		//devInfo.stStableInfo.u32HwVer = net_ip_a2n(pDevInfo->hwVer);
		
		//����汾
		//devInfo.stStableInfo.u32SoftVer = strtoul(pDevInfo->sofrVer, NULL, 10);
		//devInfo.stStableInfo.u32SoftVer = net_ip_a2n(pDevInfo->sofrVer);
		
		//�ں˰汾
		//devInfo.stStableInfo.u32CoreVer = strtoul(pDevInfo->codeVer, NULL, 10);
		//devInfo.stStableInfo.u32CoreVer = net_ip_a2n(pDevInfo->codeVer);

		//�豸�ɸ�����Ϣ
		nvr_string_copy(devInfo.stVarInfo.szDevName, sizeof(devInfo.stVarInfo.szDevName), 
						pDevInfo->stVarInfo.szDevName);
		//����0 ����1Ӣ��
		devInfo.stVarInfo.u8Language = !!pDevInfo->stVarInfo.u8Language;
		//��ʽ1 pal 0 ntfc
		devInfo.stVarInfo.u8PalStand = !!pDevInfo->stVarInfo.u8PalStand;
		//��ԴƵ��0 50Hz 1 60HZ
		devInfo.stVarInfo.u8Hz	     = !!pDevInfo->stVarInfo.u8Hz;
		
		//__DBUG("pDevInfo->serialId: %s\n",pDevInfo->serialId);
		//__DBUG("pDevInfo->hwVer: %s\n",pDevInfo->hwVer);
		//__DBUG("pDevInfo->sofrVer: %s\n",pDevInfo->sofrVer);
		//__DBUG("pDevInfo->codeVer: %s\n",pDevInfo->codeVer);
		
		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&devInfo, 
									sizeof(TI_DEV_INFO_S), 
									TI_CMD_SET_DEV_INFO);
		
	}
	else
		__ERR("ti_param_set_dev_param faile!\n");

	return ret;
	
	return 0;
}
static int ti_param_check_dev_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
	
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_DEV_CFG_S): %d\n", sizeof(IPNC_DEV_CFG_S));
	if(dataSize != sizeof(IPNC_DEV_CFG_S))
		return -1;
		
	return 0;
}
/*ftpͨ�ýṹ�庯��************************************************************/

static int ti_param_get_ftp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	
	IPNC_FTP_CFG_S *pFtpInfo = (IPNC_FTP_CFG_S *)pData;
	TI_FTP_CFG_S ftpInfo;
	int ret = -1;

	memset(&ftpInfo, 0, sizeof(TI_FTP_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&ftpInfo, 
								sizeof(TI_FTP_CFG_S), 
								TI_CMD_GET_FTP_CFG);
	
	if((0 < ret) && (NULL != pFtpInfo))
	{
		
		//�˿�
		pFtpInfo->u16FtpPort = ftpInfo.u16FtpPort;

		//��������ַ
		nvr_string_copy(pFtpInfo->ftpSvr, sizeof(pFtpInfo->ftpSvr),
						ftpInfo.szFtpSvr);
		//�û���
		nvr_string_copy(pFtpInfo->ftpUsr, sizeof(pFtpInfo->ftpUsr), 
						ftpInfo.szFtpUsr);
		//����
		nvr_string_copy(pFtpInfo->ftpPsw, sizeof(pFtpInfo->ftpPsw), 
						ftpInfo.szFtpPsw);
		//�洢·��
		nvr_string_copy(pFtpInfo->ftpPath, sizeof(pFtpInfo->ftpPath), 
						ftpInfo.szFtpPath);

		//__DBUG("pFtpInfo->u16FtpPort: %d\n",pFtpInfo->u16FtpPort);
		//__DBUG("pFtpInfo->ftpSvr: %s\n",pFtpInfo->ftpSvr);
		//__DBUG("pFtpInfo->ftpUsr: %s\n",pFtpInfo->ftpUsr);
		//__DBUG("pFtpInfo->ftpPsw: %s\n",pFtpInfo->ftpPsw);
		//__DBUG("pFtpInfo->ftpPath: %s\n",pFtpInfo->ftpPath);
		
	}
	else
		__ERR("ti_param_get_ftp_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_FTP_CFG_S) : ret);
}
static int ti_param_set_ftp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_FTP_CFG_S *pFtpInfo = (IPNC_FTP_CFG_S *)pData;
	TI_FTP_CFG_S ftpInfo;
	int ret = -1;

	memset(&ftpInfo, 0, sizeof(TI_FTP_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&ftpInfo, 
								sizeof(TI_FTP_CFG_S), 
								TI_CMD_GET_FTP_CFG);
	
	if((0 < ret) && (NULL != pFtpInfo))
	{
		//�˿�
		ftpInfo.u16FtpPort = pFtpInfo->u16FtpPort;

		//��������ַ
		nvr_string_copy(ftpInfo.szFtpSvr, sizeof(ftpInfo.szFtpSvr), 
						pFtpInfo->ftpSvr);
		//�û���
		nvr_string_copy(ftpInfo.szFtpUsr, sizeof(ftpInfo.szFtpUsr), 
						pFtpInfo->ftpUsr);
		//����
		nvr_string_copy(ftpInfo.szFtpPsw, sizeof(ftpInfo.szFtpPsw), 
						pFtpInfo->ftpPsw);
		//�洢·��
		nvr_string_copy(ftpInfo.szFtpPath, sizeof(ftpInfo.szFtpPath), 
						pFtpInfo->ftpPath);
		
		//__DBUG("ftpInfo.u16FtpPort: %d\n",ftpInfo.u16FtpPort);
		//__DBUG("ftpInfo.szFtpSvr: %s\n",ftpInfo.szFtpSvr);
		//__DBUG("ftpInfo.szFtpUsr: %s\n",ftpInfo.szFtpUsr);
		//__DBUG("ftpInfo.szFtpPsw: %s\n",ftpInfo.szFtpPsw);
		//__DBUG("ftpInfo.szFtpPath: %s\n",ftpInfo.szFtpPath);
		
		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&ftpInfo, 
									sizeof(TI_FTP_CFG_S), 
									TI_CMD_SET_FTP_CFG);
		
	}
	else
		__ERR("ti_param_set_ftp_param faile!\n");

	return ret;
}
static int ti_param_check_ftp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
	
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_FTP_CFG_S): %d\n", sizeof(IPNC_FTP_CFG_S));
	if(dataSize != sizeof(IPNC_FTP_CFG_S))
		return -1;
		
	return 0;
}

/*smtpͨ�ýṹ�庯��************************************************************/

static int ti_param_get_smtp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_SMTP_CFG_S *pSmtpInfo = (IPNC_SMTP_CFG_S *)pData;
	TI_SMTP_CFG_S smtpInfo;
	int ret = -1;

	memset(&smtpInfo, 0, sizeof(TI_SMTP_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&smtpInfo, 
								sizeof(TI_SMTP_CFG_S), 
								TI_CMD_GET_EMAIL_CFG);
	
	if((0 < ret) && (NULL != pSmtpInfo))
	{
		
		//�˿�
		pSmtpInfo->u16MailPort = smtpInfo.u16MailPort;

		//��������ַ
		nvr_string_copy(pSmtpInfo->mailHub, sizeof(pSmtpInfo->mailHub), 
						smtpInfo.szMailHub);
		//���͵�ַ
		nvr_string_copy(pSmtpInfo->mailAddr, sizeof(pSmtpInfo->mailAddr), 
						smtpInfo.szMailAddr);
		//�����˻�
		nvr_string_copy(pSmtpInfo->mailUsr, sizeof(pSmtpInfo->mailUsr), 
						smtpInfo.szMailUsr);
		//����
		nvr_string_copy(pSmtpInfo->mailPsw, sizeof(pSmtpInfo->mailPsw), 
						smtpInfo.szMailPsw);
		//���յ�ַ
		nvr_string_copy(pSmtpInfo->mailRctp1, sizeof(pSmtpInfo->mailRctp1), 
						smtpInfo.szMailRctp1);
		nvr_string_copy(pSmtpInfo->mailRctp2, sizeof(pSmtpInfo->mailRctp2), 
						smtpInfo.szMailRctp2);
		nvr_string_copy(pSmtpInfo->mailRctp3, sizeof(pSmtpInfo->mailRctp3), 
						smtpInfo.szMailRctp3);

		//__DBUG("pSmtpInfo->u16MailPort: %d\n",pSmtpInfo->u16MailPort);
		//__DBUG("pSmtpInfo->mailHub: %s\n",pSmtpInfo->mailHub);
		//__DBUG("pSmtpInfo->mailAddr: %s\n",pSmtpInfo->mailAddr);
		//__DBUG("pSmtpInfo->mailUsr: %s\n",pSmtpInfo->mailUsr);
		//__DBUG("pSmtpInfo->mailPsw: %s\n",pSmtpInfo->mailPsw);
		//__DBUG("pSmtpInfo->mailRctp1: %s\n",pSmtpInfo->mailRctp1);
		//__DBUG("pSmtpInfo->mailRctp2: %s\n",pSmtpInfo->mailRctp2);
		//__DBUG("pSmtpInfo->mailRctp3: %s\n",pSmtpInfo->mailRctp3);
		
	}
	else
		__ERR("ti_param_get_smtp_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_SMTP_CFG_S) : ret);
}
static int ti_param_set_smtp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_SMTP_CFG_S *pSmtpInfo = (IPNC_SMTP_CFG_S *)pData;
	TI_SMTP_CFG_S smtpInfo;
	int ret = -1;

	memset(&smtpInfo, 0, sizeof(TI_SMTP_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&smtpInfo, 
								sizeof(TI_SMTP_CFG_S), 
								TI_CMD_GET_EMAIL_CFG);
	
	if((0 < ret) && (NULL != pSmtpInfo))
	{
		
		//�˿�
		pSmtpInfo->u16MailPort = smtpInfo.u16MailPort;

		//��������ַ
		nvr_string_copy(smtpInfo.szMailHub, sizeof(smtpInfo.szMailHub), 
						pSmtpInfo->mailHub);
		//���͵�ַ
		nvr_string_copy(smtpInfo.szMailAddr, sizeof(smtpInfo.szMailAddr), 
						pSmtpInfo->mailAddr);
		//�����˻�
		nvr_string_copy(smtpInfo.szMailUsr, sizeof(smtpInfo.szMailUsr), 
						pSmtpInfo->mailUsr);
		//����
		nvr_string_copy(smtpInfo.szMailPsw, sizeof(smtpInfo.szMailPsw), 
						pSmtpInfo->mailPsw);
		//���յ�ַ
		nvr_string_copy(smtpInfo.szMailRctp1, sizeof(smtpInfo.szMailRctp1), 
						pSmtpInfo->mailRctp1);
		nvr_string_copy(smtpInfo.szMailRctp2, sizeof(smtpInfo.szMailRctp2), 
						pSmtpInfo->mailRctp2);
		nvr_string_copy(smtpInfo.szMailRctp3, sizeof(smtpInfo.szMailRctp3), 
						pSmtpInfo->mailRctp3);

		//__DBUG("smtpInfo.u16MailPort: %d\n",smtpInfo.u16MailPort);
		//__DBUG("smtpInfo.szMailHub: %s\n",smtpInfo.szMailHub);
		//__DBUG("smtpInfo.szMailAddr: %s\n",smtpInfo.szMailAddr);
		//__DBUG("smtpInfo.szMailUsr: %s\n",smtpInfo.szMailUsr);
		//__DBUG("smtpInfo.szMailPsw: %s\n",smtpInfo.szMailPsw);
		//__DBUG("smtpInfo.szMailRctp1: %s\n",smtpInfo.szMailRctp1);
		//__DBUG("smtpInfo.szMailRctp2: %s\n",smtpInfo.szMailRctp2);
		//__DBUG("smtpInfo.szMailRctp3: %s\n",smtpInfo.szMailRctp3);

		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&smtpInfo, 
									sizeof(TI_SMTP_CFG_S), 
									TI_CMD_SET_EMAIL_CFG);
		
	}
	else
		__ERR("ti_param_set_smtp_param faile!\n");

	return ret;
}
static int ti_param_check_smtp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
		
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_SMTP_CFG_S): %d\n", sizeof(IPNC_SMTP_CFG_S));		
	if(dataSize != sizeof(IPNC_SMTP_CFG_S))
		return -1;
		
	return 0;
}
/*ntpͨ�ýṹ�庯��************************************************************/

static int ti_param_get_ntp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_NTP_CFG_S *pNtpInfo = (IPNC_NTP_CFG_S *)pData;
	TI_NTP_CFG_S ntpInfo;
	int ret = -1;

	memset(&ntpInfo, 0, sizeof(TI_NTP_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&ntpInfo, 
								sizeof(TI_NTP_CFG_S), 
								TI_CMD_GET_NTP_CFG);
	
	if((0 < ret) && (NULL != pNtpInfo))
	{
		pNtpInfo->enable = ntpInfo.u8NtpOpen;
		//��������ַ
		nvr_string_copy(pNtpInfo->ntpServer, sizeof(pNtpInfo->ntpServer), 
						ntpInfo.szNtpServer);
		//ʱ��
		pNtpInfo->timeZone = ntpInfo.nTimeZone;
		
		//����ʱ����
		pNtpInfo->euroTime = ntpInfo.u8EuroTime;

		//��ʱ����ʱ��
		pNtpInfo->ntpRefTime = ntpInfo.u8NtpRefTime;
		//__DBUG("pNtpInfo->ntpServer: %s\n",pNtpInfo->ntpServer);
		//__DBUG("pNtpInfo->timeZone: %d\n",pNtpInfo->timeZone);
		//__DBUG("pNtpInfo->euroTime: %d\n",pNtpInfo->euroTime);

	}
	else
		__ERR("ti_param_get_ntp_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_NTP_CFG_S) : ret);
}
static int ti_param_set_ntp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_NTP_CFG_S *pNtpInfo = (IPNC_NTP_CFG_S *)pData;
	TI_NTP_CFG_S ntpInfo;
	int ret = -1;

	memset(&ntpInfo, 0, sizeof(TI_NTP_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&ntpInfo, 
								sizeof(TI_NTP_CFG_S), 
								TI_CMD_GET_NTP_CFG);
	
	if((0 < ret) && (NULL != pNtpInfo))
	{
		ntpInfo.u8NtpOpen = pNtpInfo->enable;
		//��������ַ
		nvr_string_copy(ntpInfo.szNtpServer, sizeof(ntpInfo.szNtpServer), 
						pNtpInfo->ntpServer);
		//ʱ��
		ntpInfo.nTimeZone = pNtpInfo->timeZone;
		
		//����ʱ����
		ntpInfo.u8EuroTime = pNtpInfo->euroTime;

		//��ʱ����
		ntpInfo.u8NtpRefTime = pNtpInfo->ntpRefTime;
		//__DBUG("ntpInfo.szNtpServer: %s\n",ntpInfo.szNtpServer);
		//__DBUG("ntpInfo.nTimeZone: %d\n",ntpInfo.nTimeZone);
		//__DBUG("ntpInfo.u8EuroTime: %d\n",ntpInfo.u8EuroTime);

		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&ntpInfo, 
									sizeof(TI_NTP_CFG_S), 
									TI_CMD_SET_NTP_CFG);
	}
	else
		__ERR("ti_param_get_ntp_param faile!\n");

	return ret;
}
static int ti_param_check_ntp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
	
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_NTP_CFG_S): %d\n", sizeof(IPNC_NTP_CFG_S));
	if(dataSize != sizeof(IPNC_NTP_CFG_S))
		return -1;
		
	return 0;
}

/*upnpͨ�ýṹ�庯��************************************************************/
static int ti_param_get_upnp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_UPNP_CFG_S *pUpnpInfo = (IPNC_UPNP_CFG_S *)pData;
	TI_UPNP_CFG_S upnpInfo;
	int ret = -1;

	memset(&upnpInfo, 0, sizeof(TI_UPNP_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&upnpInfo, 
								sizeof(TI_UPNP_CFG_S), 
								TI_CMD_GET_UPNP_CFG);
	
	if((0 < ret) && (NULL != pUpnpInfo))
	{
		//��������ַ
		net_ip_n2a(upnpInfo.u32UpnpSvr,pUpnpInfo->szUpnpSvr, 32);
		
		//�˿�
		pUpnpInfo->u16UpnpWebPort = upnpInfo.u16UpnpWebPort;
		pUpnpInfo->u16UpnpDataPort = upnpInfo.u16UpnpDataPort;

		pUpnpInfo->u16UpnpWebPortS = upnpInfo.u16UpnpWebPortS;
		pUpnpInfo->u16UpnpDataPortS = upnpInfo.u16UpnpDataPortS;

		//__DBUG("pUpnpInfo->upnpSvr: %s\n",pUpnpInfo->upnpSvr);
		//__DBUG("pUpnpInfo->u16UpnpWebPort: %d\n",pUpnpInfo->u16UpnpWebPort);
		//__DBUG("pUpnpInfo->u16UpnpDataPort: %d\n",pUpnpInfo->u16UpnpDataPort);
	}
	else
		__ERR("ti_param_get_upnp_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_UPNP_CFG_S) : ret);
}
static int ti_param_set_upnp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_UPNP_CFG_S *pUpnpInfo = (IPNC_UPNP_CFG_S *)pData;
	TI_UPNP_CFG_S upnpInfo;
	int ret = -1;

	memset(&upnpInfo, 0, sizeof(TI_UPNP_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&upnpInfo, 
								sizeof(TI_UPNP_CFG_S), 
								TI_CMD_GET_UPNP_CFG);
	
	if((0 < ret) && (NULL != pUpnpInfo))
	{
		//��������ַ
		upnpInfo.u32UpnpSvr = net_ip_a2n(pUpnpInfo->szUpnpSvr);
		
		//�˿�
		upnpInfo.u16UpnpWebPort = pUpnpInfo->u16UpnpWebPort;
		upnpInfo.u16UpnpDataPort = pUpnpInfo->u16UpnpDataPort;

		upnpInfo.u16UpnpWebPortS = pUpnpInfo->u16UpnpWebPortS;
		upnpInfo.u16UpnpDataPortS = pUpnpInfo->u16UpnpDataPortS;
		
		//__DBUG("pUpnpInfo->upnpSvr: %s\n",pUpnpInfo->upnpSvr);
		//__DBUG("pUpnpInfo->u16UpnpWebPort: %d\n",pUpnpInfo->u16UpnpWebPort);
		//__DBUG("pUpnpInfo->u16UpnpDataPort: %d\n",pUpnpInfo->u16UpnpDataPort);

		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&upnpInfo, 
									sizeof(TI_UPNP_CFG_S), 
									TI_CMD_SET_UPNP_CFG);
	}
	else
		__ERR("ti_param_set_upnp_param faile!\n");

	return ret;
}
static int ti_param_check_upnp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
	
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_UPNP_CFG_S): %d\n", sizeof(IPNC_UPNP_CFG_S));	
	if(dataSize != sizeof(IPNC_UPNP_CFG_S))
		return -1;
		
	return 0;
}

/*ddnsͨ�ýṹ�庯��************************************************************/
static int ti_param_get_ddns_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DDNS_CFG_S *pDdnsInfo = (IPNC_DDNS_CFG_S *)pData;
	TI_DDNS_CFG_S ddnsInfo;
	int ret = -1;

	memset(&ddnsInfo, 0, sizeof(TI_DDNS_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&ddnsInfo, 
								sizeof(TI_DDNS_CFG_S), 
								TI_CMD_GET_DDNS_CFG);
	
	if((0 < ret) && (NULL != pDdnsInfo))
	{
		//�������˿�
		pDdnsInfo->u16DDNSPort = ddnsInfo.u16DDNSPort;

		//ddnsע������
		nvr_string_copy(pDdnsInfo->szDDNSAccount, sizeof(pDdnsInfo->szDDNSAccount),
						ddnsInfo.szDDNSAccount);
		//�û���
		nvr_string_copy(pDdnsInfo->szDDNSUsr, sizeof(pDdnsInfo->szDDNSUsr),
						ddnsInfo.szDDNSUsr);
		//����
		nvr_string_copy(pDdnsInfo->szDDNSPsw, sizeof(pDdnsInfo->szDDNSPsw),
						ddnsInfo.szDDNSPsw);
		//����ʱ��
		pDdnsInfo->u32DDNSTimes = ddnsInfo.u32DDNSTimes;

		//__DBUG("pDdnsInfo->szDDNSAccount: %s\n",pDdnsInfo->szDDNSAccount);
		//__DBUG("pDdnsInfo->u16DDNSPort: %d\n",pDdnsInfo->u16DDNSPort);
		//__DBUG("pDdnsInfo->u32DDNSTimes: %d\n",pDdnsInfo->u32DDNSTimes);
		//__DBUG("pDdnsInfo->szDDNSUsr: %s\n",pDdnsInfo->szDDNSUsr);
		//__DBUG("pDdnsInfo->szDDNSPsw: %s\n",pDdnsInfo->szDDNSPsw);
	}
	else
		__ERR("ti_param_get_upnp_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_DDNS_CFG_S) : ret);
}
static int ti_param_set_ddns_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DDNS_CFG_S *pDdnsInfo = (IPNC_DDNS_CFG_S *)pData;
	TI_DDNS_CFG_S ddnsInfo;
	int ret = -1;

	memset(&ddnsInfo, 0, sizeof(TI_DDNS_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&ddnsInfo, 
								sizeof(TI_DDNS_CFG_S), 
								TI_CMD_GET_DDNS_CFG);
	
	if((0 < ret) && (NULL != pDdnsInfo))
	{
		//�������˿�
		ddnsInfo.u16DDNSPort = pDdnsInfo->u16DDNSPort;

		//ddnsע������
		nvr_string_copy(ddnsInfo.szDDNSAccount, sizeof(ddnsInfo.szDDNSAccount),
						pDdnsInfo->szDDNSAccount);
		//�û���
		nvr_string_copy(ddnsInfo.szDDNSUsr, sizeof(ddnsInfo.szDDNSUsr),
						pDdnsInfo->szDDNSUsr);
		//����
		nvr_string_copy(ddnsInfo.szDDNSPsw, sizeof(ddnsInfo.szDDNSPsw),
						pDdnsInfo->szDDNSPsw);
		//����ʱ��
		ddnsInfo.u32DDNSTimes = pDdnsInfo->u32DDNSTimes;

		//__DBUG("ddnsInfo.szDDNSAccount: %s\n",ddnsInfo.szDDNSAccount);
		//__DBUG("ddnsInfo.u16DDNSPort: %d\n",ddnsInfo.u16DDNSPort);
		//__DBUG("ddnsInfo.u32DDNSTimes: %d\n",ddnsInfo.u32DDNSTimes);
		//__DBUG("ddnsInfo.szDDNSUsr: %s\n",ddnsInfo.szDDNSUsr);
		//__DBUG("ddnsInfo.szDDNSPsw: %s\n",ddnsInfo.szDDNSPsw);

		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&ddnsInfo, 
									sizeof(TI_DDNS_CFG_S), 
									TI_CMD_SET_DDNS_CFG);
		
	}
	else
		__ERR("ti_param_set_upnp_param faile!\n");

	return ret;
}
static int ti_param_check_ddns_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
		
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_DDNS_CFG_S): %d\n", sizeof(IPNC_DDNS_CFG_S));
	if(dataSize != sizeof(IPNC_DDNS_CFG_S))
		return -1;
		
	return 0;
}

/*commͨ�ýṹ�庯��************************************************************/

static int ti_param_get_comm_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_COMM_CFG_S *pCommInfo = (IPNC_COMM_CFG_S *)pData;
	TI_DEV_COMM_CFG_S commInfo;
	int ret = -1;

	memset(&commInfo, 0, sizeof(TI_DEV_COMM_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&commInfo, 
								sizeof(TI_DEV_COMM_CFG_S), 
								TI_CMD_GET_COMM_CFG);
	
	if((0 < ret) && (NULL != pCommInfo))
	{
		//������
		pCommInfo->u32BaudRate = commInfo.u32BaudRate;
		//����λ
		pCommInfo->u8DataBit = commInfo.u8DataBit;
		//ֹͣλ
		pCommInfo->u8StopBit = commInfo.u8StopBit;
		//����λ
		pCommInfo->u8Parity = commInfo.u8Parity;
		//����λ
		pCommInfo->u8Flowcontrol = commInfo.u8Flowcontrol;

		//__DBUG("pDdnsInfo->u32BaudRate: %d\n",pCommInfo->u32BaudRate);
		//__DBUG("pDdnsInfo->u8DataBit: %d\n",pCommInfo->u8DataBit);
		//__DBUG("pDdnsInfo->u8StopBit: %d\n",pCommInfo->u8StopBit);
		//__DBUG("pDdnsInfo->u8Parity: %d\n",pCommInfo->u8Parity);
		//__DBUG("pDdnsInfo->u8Flowcontrol: %d\n",pCommInfo->u8Flowcontrol);
	}
	else
		__ERR("ti_param_get_comm_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_COMM_CFG_S) : ret);
}
static int ti_param_set_comm_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_COMM_CFG_S *pCommInfo = (IPNC_COMM_CFG_S *)pData;
	TI_DEV_COMM_CFG_S commInfo;
	int ret = -1;

	memset(&commInfo, 0, sizeof(TI_DEV_COMM_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&commInfo, 
								sizeof(TI_DEV_COMM_CFG_S), 
								TI_CMD_GET_COMM_CFG);
	
	if((0 < ret) && (NULL != pCommInfo))
	{
		//������
		//commInfo.u32BaudRate = pCommInfo->u32BaudRate;
		//����λ
		commInfo.u8DataBit = pCommInfo->u8DataBit;
		//ֹͣλ
		commInfo.u8StopBit = pCommInfo->u8StopBit;
		//����λ
		commInfo.u8Parity = pCommInfo->u8Parity;
		//����λ
		commInfo.u8Flowcontrol = pCommInfo->u8Flowcontrol;

		//__DBUG("commInfo.u32BaudRate: %d\n",commInfo.u32BaudRate);
		//__DBUG("commInfo.u8DataBit: %d\n",commInfo.u8DataBit);
		//__DBUG("commInfo.u8StopBit: %d\n",commInfo.u8StopBit);
		//__DBUG("commInfo.u8Parity: %d\n",commInfo.u8Parity);
		//__DBUG("commInfo.u8Flowcontrol: %d\n",commInfo.u8Flowcontrol);

		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&commInfo, 
									sizeof(TI_DEV_COMM_CFG_S), 
									TI_CMD_SET_COMM_CFG);
	}
	else
		__ERR("ti_param_set_comm_param faile!\n");

	return ret;
}
static int ti_param_check_comm_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_COMM_CFG_S): %d\n", sizeof(IPNC_COMM_CFG_S));
	if(dataSize != sizeof(IPNC_COMM_CFG_S))
		return -1;
		
	return 0;
}

/*pppoeͨ�ýṹ�庯��************************************************************/
static int ti_param_get_pppoe_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_PPPOE_CFG_S *pPppoeInfo = (IPNC_PPPOE_CFG_S *)pData;
	
	TI_DEV_NET_CFG_S netInfo;
	TI_DEV_PPPOE_CFG_S *pPppoeCfg;
	int ret = -1;

	memset(&netInfo, 0, sizeof(TI_DEV_NET_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&netInfo, 
								sizeof(TI_DEV_NET_CFG_S), 
								TI_CMD_GET_NET_CFG);

	pPppoeCfg = &netInfo.struPppoeCfg;
	if((0 < ret) && (NULL != pPppoeInfo) && (NULL != pPppoeCfg))
	{
		//pppoe�û���
		nvr_string_copy(pPppoeInfo->pppoeUsr, sizeof(pPppoeInfo->pppoeUsr),
						pPppoeCfg->szPppoeUsr);
		//pppoe����
		nvr_string_copy(pPppoeInfo->pppoePsw, sizeof(pPppoeInfo->pppoePsw),
						pPppoeCfg->szPppoePsw);
		//ip
		net_ip_n2a(pPppoeCfg->u32PppoeIp,pPppoeInfo->pppoeIp, 32);

		//__DBUG("pPppoeCfg->u32PppoeIp: %u\n",pPppoeCfg->u32PppoeIp);
		//__DBUG("pPppoeInfo->pppoeUsr: %s\n",pPppoeInfo->pppoeUsr);
		//__DBUG("pPppoeInfo->pppoePsw: %s\n",pPppoeInfo->pppoePsw);
		//__DBUG("pPppoeInfo->pppoeIp: %s\n",pPppoeInfo->pppoeIp);

	}
	else
		__ERR("ti_param_get_pppoe_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_PPPOE_CFG_S) : ret);
	
}
static int ti_param_set_pppoe_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_PPPOE_CFG_S *pPppoeInfo = (IPNC_PPPOE_CFG_S *)pData;
	
	TI_DEV_NET_CFG_S netInfo;
	TI_DEV_PPPOE_CFG_S *pPppoeCfg;
	int ret = -1;

	memset(&netInfo, 0, sizeof(TI_DEV_NET_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&netInfo, 
								sizeof(TI_DEV_NET_CFG_S), 
								TI_CMD_GET_NET_CFG);

	pPppoeCfg = &netInfo.struPppoeCfg;
	if((0 < ret) && (NULL != pPppoeInfo) && (NULL != pPppoeCfg))
	{
		//pppoe�û���
		nvr_string_copy(pPppoeCfg->szPppoeUsr, sizeof(pPppoeCfg->szPppoeUsr),
						pPppoeInfo->pppoeUsr);
		//pppoe����
		nvr_string_copy(pPppoeCfg->szPppoePsw, sizeof(pPppoeCfg->szPppoePsw),
						pPppoeInfo->pppoePsw);
		//ip
		pPppoeCfg->u32PppoeIp = net_ip_a2n(pPppoeInfo->pppoeIp);

		/*__DBUG("pPppoeCfg->szPppoeUsr: %s\n",pPppoeCfg->szPppoeUsr);
		__DBUG("pPppoeCfg->szPppoePsw: %s\n",pPppoeCfg->szPppoePsw);
		__DBUG("pPppoeCfg->u32PppoeIp: %u\n",pPppoeCfg->u32PppoeIp);
		__DBUG("pPppoeCfg->u32PppoeIp: %d.%d.%d.%d\n",pPppoeCfg->u32PppoeIp >> 24 &0xff,
													  pPppoeCfg->u32PppoeIp >> 16 &0xff,
													  pPppoeCfg->u32PppoeIp >>  8 &0xff,
													  pPppoeCfg->u32PppoeIp & 0xff);
		*/
		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&netInfo, 
									sizeof(TI_DEV_NET_CFG_S), 
									TI_CMD_SET_NET_CFG);

	}
	else
		__ERR("ti_param_set_pppoe_param faile!\n");

	return ret;
}
static int ti_param_check_pppoe_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
	
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_PPPOE_CFG_S): %d\n", sizeof(IPNC_PPPOE_CFG_S));	
	if(dataSize != sizeof(IPNC_PPPOE_CFG_S))
		return -1;
		
	return 0;
}

/*ptzͨ�ýṹ�庯��************************************************************/
static int ti_param_get_ptz_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_PTZ_CFG_S *pPtzInfo = (IPNC_PTZ_CFG_S *)pData;
	TI_DEV_PTZ_CFG_S ptzInfo;
	int ret = -1;

	memset(&ptzInfo, 0, sizeof(TI_DEV_PTZ_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&ptzInfo, 
								sizeof(TI_DEV_PTZ_CFG_S), 
								TI_CMD_GET_PTZ_CFG);

	if((0 < ret) && (NULL != pPtzInfo))
	{
		//��̨Э��
		pPtzInfo->u8ProtocalType = ptzInfo.u8ProtocalType;
		//��̨��ַ��
		pPtzInfo->u8PtzAddr = ptzInfo.u8PtzAddr;

		//__DBUG("pPtzInfo->u32PppoeIp: %u\n",pPtzInfo->u8ProtocalType);
		//__DBUG("pPtzInfo->pppoeUsr: %u\n",pPtzInfo->u8PtzAddr);

	}
	else
		__ERR("ti_param_get_ptz_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_PTZ_CFG_S) : ret);
}
static int ti_param_set_ptz_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_PTZ_CFG_S *pPtzInfo = (IPNC_PTZ_CFG_S *)pData;
	TI_DEV_PTZ_CFG_S ptzInfo;
	int ret = -1;

	memset(&ptzInfo, 0, sizeof(TI_DEV_PTZ_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&ptzInfo, 
								sizeof(TI_DEV_PTZ_CFG_S), 
								TI_CMD_GET_PTZ_CFG);

	if((0 < ret) && (NULL != pPtzInfo))
	{
		//��̨Э��
		ptzInfo.u8ProtocalType = !!pPtzInfo->u8ProtocalType;
		//��̨��ַ��
		ptzInfo.u8PtzAddr = (uint8_t)pPtzInfo->u8PtzAddr;

		//__DBUG("pPtzInfo->u32PppoeIp: %u\n",pPtzInfo->u8ProtocalType);
		//__DBUG("pPtzInfo->pppoeUsr: %u\n",pPtzInfo->u8PtzAddr);

		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&ptzInfo, 
									sizeof(TI_DEV_PTZ_CFG_S), 
									TI_CMD_SET_PTZ_CFG);

	}
	else
		__ERR("ti_param_get_ptz_param faile!\n");

	return ret;
}
static int ti_param_check_ptz_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
	
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_PTZ_CFG_S): %d\n", sizeof(IPNC_PTZ_CFG_S));	
	if(dataSize != sizeof(IPNC_PTZ_CFG_S))
		return -1;
		
	return 0;
}

/*audioͨ�ýṹ�庯��************************************************************/

static int ti_param_get_audio_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_AUDIO_CFG_S *pAudioInfo = (IPNC_AUDIO_CFG_S *)pData;
	TI_DEV_AUDIO_CFG_S audioInfo;
	int ret = -1;

	memset(&audioInfo, 0, sizeof(TI_DEV_AUDIO_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&audioInfo, 
								sizeof(TI_DEV_AUDIO_CFG_S), 
								TI_CMD_GET_AUDIO_CFG);

	if((0 < ret) && (NULL != pAudioInfo))
	{
		//ʹ�ܿ���
		pAudioInfo->u8Open = audioInfo.u8Open;
		
		//��Ƶ��������
		pAudioInfo->u8Type = audioInfo.u8Type;

		//ѹ����ʽ
		pAudioInfo->u8AEncType = audioInfo.u8AEncType;
		
		//������
		pAudioInfo->u32SampleRate = audioInfo.u32SampleRate;
		
		//__DBUG("pPtzInfo->u8Open: %u\n",pAudioInfo->u8Open);
		//__DBUG("pPtzInfo->u8Type: %u\n",pAudioInfo->u8Type);
		//__DBUG("pPtzInfo->u8AEncType: %u\n",pAudioInfo->u8AEncType);
		//__DBUG("pPtzInfo->u32SampleRate: %u\n",pAudioInfo->u32SampleRate);

	}
	else
		__ERR("ti_param_get_audio_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_AUDIO_CFG_S) : ret);
}
static int ti_param_set_audio_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_AUDIO_CFG_S *pAudioInfo = (IPNC_AUDIO_CFG_S *)pData;
	TI_DEV_AUDIO_CFG_S audioInfo;
	int ret = -1;

	memset(&audioInfo, 0, sizeof(TI_DEV_AUDIO_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&audioInfo, 
								sizeof(TI_DEV_AUDIO_CFG_S), 
								TI_CMD_GET_AUDIO_CFG);

	if((0 < ret) && (NULL != pAudioInfo))
	{
		//ʹ�ܿ���
		audioInfo.u8Open = !!pAudioInfo->u8Open;
		
		//��Ƶ�������� 0--mic������� 1--������
		audioInfo.u8Type = !!pAudioInfo->u8Type;

		//ѹ����ʽ 0--PCM 1--G711A 2-G711U 3--G726
		audioInfo.u8AEncType = pAudioInfo->u8AEncType;
		
		//������ 8k
		audioInfo.u32SampleRate = pAudioInfo->u32SampleRate;
		
		//__DBUG("audioInfou8Open: %u\n",audioInfo.u8Open);
		//__DBUG("audioInfo.u8Type: %u\n",audioInfo.u8Type);
		//__DBUG("audioInfo.u8AEncType: %u\n",audioInfo.u8AEncType);
		//__DBUG("audioInfo.u32SampleRate: %u\n",audioInfo.u32SampleRate);

		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&audioInfo, 
									sizeof(TI_DEV_AUDIO_CFG_S), 
									TI_CMD_SET_AUDIO_CFG);

	}
	else
		__ERR("ti_param_set_audio_param faile!\n");

	return ret;
}
static int ti_param_check_audio_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_AUDIO_CFG_S): %d\n", sizeof(IPNC_AUDIO_CFG_S));
	if(dataSize != sizeof(IPNC_AUDIO_CFG_S))
		return -1;
		
	return 0;
}

/*userͨ�ýṹ�庯��************************************************************/

static int ti_param_get_user_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_USER_CFG_S *pUserInfo = (IPNC_USER_CFG_S *)pData;
	TI_DEV_USER_CFG_S userInfo;
	int ret = -1;

	memset(&userInfo, 0, sizeof(TI_DEV_USER_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&userInfo, 
								sizeof(TI_DEV_USER_CFG_S), 
								TI_CMD_GET_USR_CFG);

	if((0 < ret) && (NULL != pUserInfo))
	{
		//�û���
		nvr_string_copy(pUserInfo->userName, sizeof(pUserInfo->userName), 
						userInfo.szUsrName);
		
		//����
		nvr_string_copy(pUserInfo->passWord, sizeof(pUserInfo->passWord), 
						userInfo.szPsw);

		//__DBUG("userInfo.szUsrName: %s\n",userInfo.szUsrName);
		//__DBUG("userInfo.szPsw: %s\n",userInfo.szPsw);
		//__DBUG("pPtzInfo->userName: %s\n",pUserInfo->userName);
		//__DBUG("pPtzInfo->passWord: %s\n",pUserInfo->passWord);

	}
	else
		__ERR("ti_param_get_user_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_USER_CFG_S) : ret);
}
static int ti_param_set_user_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_USER_CFG_S *pUserInfo = (IPNC_USER_CFG_S *)pData;
	TI_DEV_USER_CFG_S userInfo;
	int ret = -1;

	memset(&userInfo, 0, sizeof(TI_DEV_USER_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&userInfo, 
								sizeof(TI_DEV_USER_CFG_S), 
								TI_CMD_GET_USR_CFG);

	if((0 < ret) && (NULL != pUserInfo))
	{
		//�û���
		nvr_string_copy(userInfo.szUsrName, sizeof(userInfo.szUsrName), 
						pUserInfo->userName);
		
		//����
		if(0 == strcmp(pUserInfo->passWord, pUserInfo->cfmPassWord))
			nvr_string_copy(userInfo.szPsw, sizeof(userInfo.szPsw), 
							pUserInfo->passWord);
		else
		{
			__ERR("Passwords do not match!\n");
			return -1;
		}
			

		//__DBUG("userInfo.szUsrName: %s\n",userInfo.szUsrName);
		//__DBUG("userInfo.szPsw: %s\n",userInfo.szPsw);
		//__DBUG("pPtzInfo->userName: %s\n",pUserInfo->userName);
		//__DBUG("pPtzInfo->passWord: %s\n",pUserInfo->passWord);

		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&userInfo, 
									sizeof(TI_DEV_USER_CFG_S), 
									TI_CMD_SET_USR_CFG);
	}
	else
		__ERR("ti_param_set_user_param faile!\n");

	return ret;
}
static int ti_param_check_user_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
	
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_USER_CFG_S): %d\n", sizeof(IPNC_USER_CFG_S));		
	if(dataSize != sizeof(IPNC_USER_CFG_S))
		return -1;
		
	return 0;
}

/*osdͨ�ýṹ�庯��************************************************************/

static int ti_param_get_osd_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_OSD_CFG_S *pOsdInfo = (IPNC_DEV_OSD_CFG_S *)pData;
	TI_DEV_OSD_CFG_S osdInfo;
	int ret = -1;

	memset(&osdInfo, 0, sizeof(TI_DEV_OSD_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&osdInfo, 
								sizeof(TI_DEV_OSD_CFG_S), 
								TI_CMD_GET_OSD_CFG);

	if((0 < ret) && (NULL != pOsdInfo))
	{
#if 0
		//����ʹ�� --1 ��ʾ����osd 0--���ر���osd
		pOsdInfo->u8EnableTitleOsd = osdInfo.u8EnableTitleOsd;
		//ʱ��ʹ�� --1 ��ʾʱ��osd 0--����ʱ��osd
		pOsdInfo->u8EnableTimeOsd = osdInfo.u8EnableTimeOsd;
		//����ʹ�� --1 ��ʾ���� 0--��������
		pOsdInfo->u8DispWeek = osdInfo.u8DispWeek;
		//����ʹ�� --1��ʾ����osd  0--��������osd
		pOsdInfo->u8EnableBitrateOsd = osdInfo.u8EnableBitrateOsd;
		//��ʾʱ���ʽ
		//--0 YYYY-MM-DD HH:MM:SS
  		//--1 MM-DD-YYYY HH:MM:SS
  		//--2 DD-MM-YYYY HH:MM:SS
		//--3 YYYY/MM/DD HH:MM:SS
		//--4 MM/DD/YYYY HH:MM:SS
		//--5 DD/MM/YYYY HH:MM:SS
		pOsdInfo->u8TimeOsdType =  osdInfo.u8TimeOsdType;
		//ʱ�����  --0 24 hour --1 12 hour
		pOsdInfo->u8HourOsdType =  osdInfo.u8HourOsdType;
		//������ɫ
		//----0 ---black
  		//---1---white
  		//---2---blue
  		//---3---yellow
		pOsdInfo->u8OsdColor =  osdInfo.u8OsdColor;
		//ʱ��������ʾλ��
		pOsdInfo->struTimeOrg.s32Y =  osdInfo.struTimeOrg.s32Y;
		pOsdInfo->struTimeOrg.s32X =  osdInfo.struTimeOrg.s32X;
		//������ʾλ��
		pOsdInfo->struTitleOrg.s32Y =  osdInfo.struTitleOrg.s32Y;
		pOsdInfo->struTitleOrg.s32X =  osdInfo.struTitleOrg.s32X;
		//��������
		nvr_string_copy(pOsdInfo->szChnName, sizeof(pOsdInfo->szChnName), 
						osdInfo.szChnName);
		
		//__DBUG("pOsdInfo->u8EnableTitleOsd: %d\n",pOsdInfo->u8EnableTitleOsd);
		//__DBUG("pOsdInfo->u8EnableTimeOsd: %d\n",pOsdInfo->u8EnableTimeOsd);
		//__DBUG("pOsdInfo->.u8DispWeek: %d\n",pOsdInfo->u8DispWeek);
		//__DBUG("pOsdInfo->u8EnableBitrateOsd: %d\n",pOsdInfo->u8EnableBitrateOsd);
		
		//__DBUG("pOsdInfo->u8TimeOsdType: %d\n",pOsdInfo->u8TimeOsdType);
		//__DBUG("pOsdInfo->u8HourOsdType: %d\n",pOsdInfo->u8HourOsdType);
		//__DBUG("pOsdInfo->u8OsdColor: %d\n",pOsdInfo->u8OsdColor);
		//__DBUG("pOsdInfo->struTimeOrg.s32Y: %d\n",pOsdInfo->struTimeOrg.s32Y);
		//__DBUG("pOsdInfo->struTimeOrg.s32X: %d\n",pOsdInfo->struTimeOrg.s32X);
		//__DBUG("pOsdInfo->struTitleOrg.s32Y: %d\n",pOsdInfo->struTitleOrg.s32Y);
		//__DBUG("pOsdInfo->struTitleOrg.s32X: %d\n",pOsdInfo->struTitleOrg.s32X);
		//__DBUG("pOsdInfo->szChnName: %s\n",pOsdInfo->szChnName);
#endif
		memcpy(pOsdInfo, &osdInfo, sizeof(IPNC_DEV_OSD_CFG_S));
	}
	else
		__ERR("ti_param_get_osd_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_DEV_OSD_CFG_S) : ret);
}
static int ti_param_set_osd_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_OSD_CFG_S *pOsdInfo = (IPNC_DEV_OSD_CFG_S *)pData;
	TI_DEV_OSD_CFG_S osdInfo;
	int ret = -1;

	memset(&osdInfo, 0, sizeof(TI_DEV_OSD_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&osdInfo, 
								sizeof(TI_DEV_OSD_CFG_S), 
								TI_CMD_GET_OSD_CFG);

	if((0 < ret) && (NULL != pOsdInfo))
	{
		/*//����ʹ�� --1 ��ʾ����osd 0--���ر���osd
		osdInfo.u8EnableTitleOsd = !!pOsdInfo->u8EnableTitleOsd;
		//ʱ��ʹ�� --1 ��ʾʱ��osd 0--����ʱ��osd
		osdInfo.u8EnableTimeOsd = !!pOsdInfo->u8EnableTimeOsd;
		//����ʹ�� --1 ��ʾ���� 0--��������
		osdInfo.u8DispWeek = !!pOsdInfo->u8DispWeek;
		//����ʹ�� --1��ʾ����osd  0--��������osd
		osdInfo.u8EnableBitrateOsd = !!pOsdInfo->u8EnableBitrateOsd;
		//��ʾʱ���ʽ
		//--0 YYYY-MM-DD HH:MM:SS
  		//--1 MM-DD-YYYY HH:MM:SS
  		//--2 DD-MM-YYYY HH:MM:SS
		//--3 YYYY/MM/DD HH:MM:SS
		//--4 MM/DD/YYYY HH:MM:SS
		//--5 DD/MM/YYYY HH:MM:SS
		osdInfo.u8TimeOsdType = pOsdInfo->u8TimeOsdType;
		//ʱ�����  --0 24 hour --1 12 hour
		osdInfo.u8HourOsdType = pOsdInfo->u8HourOsdType;
		//������ɫ
		//---0---black
  		//---1---white
  		//---2---blue
  		//---3---yellow
		osdInfo.u8OsdColor = pOsdInfo->u8OsdColor;
		//ʱ��������ʾλ��
		osdInfo.struTimeOrg.s32Y = pOsdInfo->struTimeOrg.s32Y;
		osdInfo.struTimeOrg.s32X = pOsdInfo->struTimeOrg.s32X;
		//������ʾλ��
		osdInfo.struTitleOrg.s32Y = pOsdInfo->struTitleOrg.s32Y;
		osdInfo.struTitleOrg.s32X = pOsdInfo->struTitleOrg.s32X;
		//��������
		nvr_string_copy(osdInfo.szChnName, sizeof(osdInfo.szChnName), 
						pOsdInfo->szChnName);

		//__DBUG("osdInfo.u8EnableTitleOsd: %d\n",osdInfo.u8EnableTitleOsd);
		//__DBUG("osdInfo.u8EnableTimeOsd: %d\n",osdInfo.u8EnableTimeOsd);
		//__DBUG("osdInfo.u8DispWeek: %d\n",osdInfo.u8DispWeek);
		//__DBUG("osdInfo.u8EnableBitrateOsd: %d\n",osdInfo.u8EnableBitrateOsd);
		
		//__DBUG("osdInfo.u8TimeOsdType: %d\n",osdInfo.u8TimeOsdType);
		//__DBUG("osdInfo.u8HourOsdType: %d\n",osdInfo.u8HourOsdType);
		//__DBUG("osdInfo.u8OsdColor: %d\n",osdInfo.u8OsdColor);
		//__DBUG("osdInfo.struTimeOrg.s32Y: %d\n",osdInfo.struTimeOrg.s32Y);
		//__DBUG("osdInfo.struTimeOrg.s32X: %d\n",osdInfo.struTimeOrg.s32X);
		//__DBUG("osdInfo.struTitleOrg.s32Y: %d\n",osdInfo.struTitleOrg.s32Y);
		//__DBUG("osdInfo.struTitleOrg.s32X: %d\n",osdInfo.struTitleOrg.s32X);
		//__DBUG("osdInfo.szChnName: %s\n",osdInfo.szChnName);*/

		memcpy(&osdInfo, pOsdInfo,sizeof(IPNC_DEV_OSD_CFG_S));
		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&osdInfo, 
									sizeof(TI_DEV_OSD_CFG_S), 
									TI_CMD_SET_OSD_CFG);

	}
	else
		__ERR("ti_param_set_osd_param faile!\n");
	
	return ret;
}
static int ti_param_check_osd_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
	
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_DEV_OSD_CFG_S): %d\n", sizeof(IPNC_DEV_OSD_CFG_S));
	if(dataSize != sizeof(IPNC_DEV_OSD_CFG_S))
		return -1;
		
	return 0;
}
/*vmaskͨ�ýṹ�庯��************************************************************/
static int ti_param_get_vmask_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	
	IPNC_DEV_VMASK_CFG_S *pVmaskInfo = (IPNC_DEV_VMASK_CFG_S *)pData;
	TI_DEV_VMASK_CFG_S vmaskInfo;
	int ret = -1;

	memset(&vmaskInfo, 0, sizeof(TI_DEV_VMASK_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&vmaskInfo, 
								sizeof(TI_DEV_VMASK_CFG_S), 
								TI_CMD_GET_VMASK_CFG);

	if((0 < ret) && (NULL != pVmaskInfo))
	{
		__ERR("sizeof(IPNC_DEV_VMASK_CFG_S): %d\n", sizeof(IPNC_DEV_VMASK_CFG_S));
		__ERR("sizeof(TI_DEV_VMASK_CFG_S): %d\n", sizeof(TI_DEV_VMASK_CFG_S));
		memcpy(pVmaskInfo, &vmaskInfo, sizeof(IPNC_DEV_VMASK_CFG_S));
	}
	else
		__ERR("ti_param_get_vmask_param faile!\n");
	
	return ((ret > 0) ? sizeof(IPNC_DEV_VMASK_CFG_S) : ret);
}

static int ti_param_set_vmask_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_VMASK_CFG_S *pVmaskInfo = (IPNC_DEV_VMASK_CFG_S *)pData;
	TI_DEV_VMASK_CFG_S vmaskInfo;
	int i = 0, ret = -1;

	memset(&vmaskInfo, 0, sizeof(TI_DEV_VMASK_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&vmaskInfo, 
								sizeof(TI_DEV_VMASK_CFG_S), 
								TI_CMD_GET_VMASK_CFG);

	if((0 < ret) && (NULL != pVmaskInfo))
	{
		//--1.������Ƶ�ڵ�0--������Ƶ�ڵ�
		vmaskInfo.u8Open = !!pVmaskInfo->u8Open;
		//��Ƶ�ڵ�����
		for(i = 0; i < IPNC_VMASK_REG_NUM; i++)
		{
			vmaskInfo.struArea[i].s32X = pVmaskInfo->struArea[i].s32X;
			vmaskInfo.struArea[i].s32Y = pVmaskInfo->struArea[i].s32Y;
			vmaskInfo.struArea[i].u32Height = pVmaskInfo->struArea[i].u32Height;
			vmaskInfo.struArea[i].u32Width = pVmaskInfo->struArea[i].u32Width;
		}

		//����
		ret = ti_send_set_param_cmd(logonHandle, 
								&vmaskInfo, 
								sizeof(TI_DEV_VMASK_CFG_S), 
								TI_CMD_SET_VMASK_CFG);
	}
	else
		__ERR("ti_param_set_vmask_param faile!\n");


	return ret;
}
static int ti_param_check_vmask_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
		
	if(dataSize != sizeof(IPNC_DEV_VMASK_CFG_S))
		return -1;
	
	return 0;
}
/*main vencͨ�ýṹ�庯��************************************************************/
static int ti_param_get_vmain_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	
	IPNC_DEV_VENC_CFG_S *pVmainInfo = (IPNC_DEV_VENC_CFG_S *)pData;
	TI_DEV_VENC_CFG_S vmainInfo;
	int ret = -1;

	memset(&vmainInfo, 0, sizeof(TI_DEV_VENC_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&vmainInfo, 
								sizeof(TI_DEV_VENC_CFG_S), 
								TI_CMD_GET_VMAIN_CFG);

	if((0 < ret) && (NULL != pVmainInfo))
	{
		//__ERR("sizeof(IPNC_DEV_VENC_CFG_S): %d\n", sizeof(IPNC_DEV_VENC_CFG_S));
		//__ERR("sizeof(TI_DEV_VENC_CFG_S): %d\n", sizeof(TI_DEV_VENC_CFG_S));
		memcpy(pVmainInfo, &vmainInfo, sizeof(IPNC_DEV_VENC_CFG_S));
	}
	else
		__ERR("ti_param_get_vmain_param faile!\n");
	
	return ((ret > 0) ? sizeof(IPNC_DEV_VENC_CFG_S) : ret);
}

static int ti_param_set_vmain_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_VENC_CFG_S *pVmainInfo = (IPNC_DEV_VENC_CFG_S *)pData;
	TI_DEV_VENC_CFG_S vmainInfo;
	int ret = -1;

	memset(&vmainInfo, 0, sizeof(TI_DEV_VENC_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&vmainInfo, 
								sizeof(TI_DEV_VENC_CFG_S), 
								TI_CMD_GET_VMAIN_CFG);

	if((0 < ret) && (NULL != pVmainInfo))
	{
		//��Ƶ������
		vmainInfo.u16Width = pVmainInfo->u16Width;
		//��Ƶ����߶�
		vmainInfo.u16Height = pVmainInfo->u16Height;
		//��Ƶ�����ʽ0--h264 1--MJPEG
		vmainInfo.u8VideoEncType = pVmainInfo->u8VideoEncType;
		//��������0-��ã�1-�κã�2-�Ϻã�3-һ�㣬4-�ϲ5-��	
		vmainInfo.u8PicQuilty = pVmainInfo->u8PicQuilty;
		//I֡���1-200
		vmainInfo.u8Gop = pVmainInfo->u8Gop;
		//�������� 0--������1--������
		vmainInfo.u8FlowType = pVmainInfo->u8FlowType;
		//�������� 32kbps-16Mkbps
		vmainInfo.u32BitrateRate = pVmainInfo->u32BitrateRate;
		//����֡��1-25/30
		vmainInfo.u8FrameRate = pVmainInfo->u8FrameRate;

		ret = ti_send_set_param_cmd(logonHandle, 
								&vmainInfo, 
								sizeof(TI_DEV_VENC_CFG_S), 
								TI_CMD_SET_VMAIN_CFG);
	}
	else
		__ERR("ti_param_set_vmain_param faile!\n");

	return ret;
}
static int ti_param_check_vmain_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
		
	if(dataSize != sizeof(IPNC_DEV_VENC_CFG_S))
		return -1;
	
	return 0;
}
/*sub vencͨ�ýṹ�庯��************************************************************/
static int ti_param_get_vsub_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	
	IPNC_DEV_VENC_CFG_S *pVsubInfo = (IPNC_DEV_VENC_CFG_S *)pData;
	TI_DEV_VENC_CFG_S vsubInfo;
	int ret = -1;

	memset(&vsubInfo, 0, sizeof(TI_DEV_VENC_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&vsubInfo, 
								sizeof(TI_DEV_VENC_CFG_S), 
								TI_CMD_GET_VSUB_CFG);

	if((0 < ret) && (NULL != pVsubInfo))
	{
		__ERR("sizeof(IPNC_DEV_VENC_CFG_S): %d\n", sizeof(IPNC_DEV_VENC_CFG_S));
		__ERR("sizeof(TI_DEV_VENC_CFG_S): %d\n", sizeof(TI_DEV_VENC_CFG_S));
		memcpy(pVsubInfo, &vsubInfo, sizeof(IPNC_DEV_VENC_CFG_S));
	}
	else
		__ERR("ti_param_get_vsub_param faile!\n");
	
	return ((ret > 0) ? sizeof(IPNC_DEV_VENC_CFG_S) : ret);
}

static int ti_param_set_vsub_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_VENC_CFG_S *pVsubInfo = (IPNC_DEV_VENC_CFG_S *)pData;
	TI_DEV_VENC_CFG_S vsubInfo;
	int ret = -1;

	memset(&vsubInfo, 0, sizeof(TI_DEV_VENC_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&vsubInfo, 
								sizeof(TI_DEV_VENC_CFG_S), 
								TI_CMD_GET_VSUB_CFG);

	if((0 < ret) && (NULL != pVsubInfo))
	{
		//��Ƶ������
		vsubInfo.u16Width = pVsubInfo->u16Width;
		//��Ƶ����߶�
		vsubInfo.u16Height = pVsubInfo->u16Height;
		//��Ƶ�����ʽ0--h264 1--MJPEG
		vsubInfo.u8VideoEncType = pVsubInfo->u8VideoEncType;
		//��������0-��ã�1-�κã�2-�Ϻã�3-һ�㣬4-�ϲ5-��	
		vsubInfo.u8PicQuilty = pVsubInfo->u8PicQuilty;
		//I֡���1-200
		vsubInfo.u8Gop = pVsubInfo->u8Gop;
		//�������� 0--������1--������
		vsubInfo.u8FlowType = pVsubInfo->u8FlowType;
		//�������� 32kbps-16Mkbps
		vsubInfo.u32BitrateRate = pVsubInfo->u32BitrateRate;
		//����֡��1-25/30
		vsubInfo.u8FrameRate = pVsubInfo->u8FrameRate;

		ret = ti_send_set_param_cmd(logonHandle, 
								&vsubInfo, 
								sizeof(TI_DEV_VENC_CFG_S), 
								TI_CMD_SET_VSUB_CFG);
	}
	else
		__ERR("ti_param_set_vmain_param faile!\n");

	return ret;
}
static int ti_param_check_vsub_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
		
	if(dataSize != sizeof(IPNC_DEV_VENC_CFG_S))
		return -1;
	
	return 0;
}
/*vcapͨ�ýṹ�庯��************************************************************/
static int ti_param_get_vcap_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_CAPTURE_CFG_S *pVcapInfo = (IPNC_DEV_CAPTURE_CFG_S *)pData;
	TI_DEV_CAPTURE_CFG_S vcapInfo;
	int ret = -1;

	memset(&vcapInfo, 0, sizeof(TI_DEV_CAPTURE_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&vcapInfo, 
								sizeof(TI_DEV_CAPTURE_CFG_S), 
								TI_CMD_GET_VCAP_CFG);

	if((0 < ret) && (NULL != pVcapInfo))
	{
		__ERR("sizeof(IPNC_DEV_CAPTURE_CFG_S): %d\n", sizeof(IPNC_DEV_CAPTURE_CFG_S));
		__ERR("sizeof(TI_DEV_CAPTURE_CFG_S): %d\n", sizeof(TI_DEV_CAPTURE_CFG_S));
		memcpy(pVcapInfo, &vcapInfo, sizeof(IPNC_DEV_CAPTURE_CFG_S));
	}
	else
		__ERR("ti_param_get_vcap_param faile!\n");
	
	return ((ret > 0) ? sizeof(IPNC_DEV_CAPTURE_CFG_S) : ret);
}

static int ti_param_set_vcap_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_CAPTURE_CFG_S *pVcapInfo = (IPNC_DEV_CAPTURE_CFG_S *)pData;
	TI_DEV_CAPTURE_CFG_S vcapInfo;
	int ret = -1;

	memset(&vcapInfo, 0, sizeof(TI_DEV_CAPTURE_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&vcapInfo, 
								sizeof(TI_DEV_CAPTURE_CFG_S), 
								TI_CMD_GET_VCAP_CFG);

	if((0 < ret) && (NULL != pVcapInfo))
	{
		
		vcapInfo.u16Width = pVcapInfo->u16Width;
		vcapInfo.u16Height = pVcapInfo->u16Height;
		vcapInfo.u8VideoEncType = pVcapInfo->u8VideoEncType;
		vcapInfo.u8Quilty = pVcapInfo->u8Quilty;
		
		ret = ti_send_set_param_cmd(logonHandle, 
								&vcapInfo, 
								sizeof(TI_DEV_CAPTURE_CFG_S), 
								TI_CMD_SET_VCAP_CFG);
	}
	else
		__ERR("ti_param_set_vcap_param faile!\n");


	return ret;
}
static int ti_param_check_vcap_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
		
	if(dataSize != sizeof(IPNC_DEV_VENC_CFG_S))
		return -1;
	
	return 0;
}


/*video������ͨ�ýṹ�庯��************************************************************/

static int ti_param_get_video_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_VIDEO_CFG_S *pVideoInfo = (IPNC_DEV_VIDEO_CFG_S *)pData;
	TI_DEV_VIDEO_CFG_S videoInfo;
	int ret = -1;

	memset(&videoInfo, 0, sizeof(TI_DEV_VIDEO_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&videoInfo, 
								sizeof(TI_DEV_VIDEO_CFG_S), 
								TI_CMD_GET_VIDEO_CFG);

	if((0 < ret) && (NULL != pVideoInfo))
	{
#if 0
		int i = 0;
		TI_DEV_OSD_CFG_S      *pOsdInfoTmp    = &videoInfo.struOsd;
		TI_DEV_VMASK_CFG_S    *pVmaskInfoTmp  = &videoInfo.struVMask;
		TI_DEV_VENC_CFG_S	  *pVmainInfoTmp  = &videoInfo.struMainVenc;
		TI_DEV_VENC_CFG_S	  *pVsubInfoTmp   = &videoInfo.struSubVenc;
		//TI_DEV_CAPTURE_CFG_S  *pCaptureInfoTmp  = &videoInfo.struCapture;
		TI_DEV_IMA_CFG_S      *pImaInfoTmp      = &videoInfo.struIma;

		IPNC_DEV_OSD_CFG_S     *pOsdInfo   = &pVideoInfo->struOsd;
		IPNC_DEV_VMASK_CFG_S   *pVmaskInfo = &pVideoInfo->struVMask;
		IPNC_DEV_VENC_CFG_S	  *pVmainInfo = &pVideoInfo->struMainVenc;
		IPNC_DEV_VENC_CFG_S	  *pVsubInfo  = &pVideoInfo->struSubVenc;
		//IPNC_DEV_CAPTURE_CFG_S *pCaptureInfo = &pVideoInfo->struCapture;
		IPNC_DEV_IMA_CFG_S    *pImaInfo     = &pVideoInfo->struIma;
		
		//////////////////////OSD
		//����ʹ�� --1 ��ʾ����osd 0--���ر���osd
		pOsdInfo->u8EnableTitleOsd = pOsdInfoTmp->u8EnableTitleOsd;
		//ʱ��ʹ�� --1 ��ʾʱ��osd 0--����ʱ��osd
		pOsdInfo->u8EnableTimeOsd = pOsdInfoTmp->u8EnableTimeOsd;
		//����ʹ�� --1 ��ʾ���� 0--��������
		pOsdInfo->u8DispWeek = pOsdInfoTmp->u8DispWeek;
		//����ʹ�� --1��ʾ����osd  0--��������osd
		pOsdInfo->u8EnableBitrateOsd = pOsdInfoTmp->u8EnableBitrateOsd;
		//��ʾʱ���ʽ
		//--0 YYYY-MM-DD HH:MM:SS
  		//--1 MM-DD-YYYY HH:MM:SS
  		//--2 DD-MM-YYYY HH:MM:SS
		//--3 YYYY/MM/DD HH:MM:SS
		//--4 MM/DD/YYYY HH:MM:SS
		//--5 DD/MM/YYYY HH:MM:SS
		pOsdInfo->u8TimeOsdType =  pOsdInfoTmp->u8TimeOsdType;
		//ʱ�����  --0 24 hour --1 12 hour
		pOsdInfo->u8HourOsdType =  pOsdInfoTmp->u8HourOsdType;

		//��ɫ���
		pOsdInfo->u8ColorValidFlag = pOsdInfoTmp->u8ColorValidFlag;
		//������ɫ
		//----0 ---black
  		//---1---white
  		//---2---blue
  		//---3---yellow
		pOsdInfo->u8OsdColor =  pOsdInfoTmp->u8OsdColor;
		pOsdInfo->u32TimeColor = pOsdInfoTmp->u32TimeColor;
		pOsdInfo->u32ChnColor = pOsdInfoTmp->u32ChnColor;
		//ʱ��������ʾλ��
		pOsdInfo->struTimeOrg.s32Y =  pOsdInfoTmp->struTimeOrg.s32Y;
		pOsdInfo->struTimeOrg.s32X =  pOsdInfoTmp->struTimeOrg.s32X;
		//������ʾλ��
		pOsdInfo->struTitleOrg.s32Y =  pOsdInfoTmp->struTitleOrg.s32Y;
		pOsdInfo->struTitleOrg.s32X =  pOsdInfoTmp->struTitleOrg.s32X;
		//��������
		nvr_string_copy(pOsdInfo->szChnName, sizeof(pOsdInfo->szChnName), 
						pOsdInfoTmp->szChnName);
		
		/*__DBUG("pOsdInfo->u8EnableTitleOsd: %d\n",pOsdInfo->u8EnableTitleOsd);
		__DBUG("pOsdInfo->u8EnableTimeOsd: %d\n",pOsdInfo->u8EnableTimeOsd);
		__DBUG("pOsdInfo->u8DispWeek: %d\n",pOsdInfo->u8DispWeek);
		__DBUG("pOsdInfo->u8EnableBitrateOsd: %d\n",pOsdInfo->u8EnableBitrateOsd);
		
		__DBUG("pOsdInfo->u8TimeOsdType: %d\n",pOsdInfo->u8TimeOsdType);
		__DBUG("pOsdInfo->u8HourOsdType: %d\n",pOsdInfo->u8HourOsdType);
		__DBUG("pOsdInfo->u8OsdColor: %d\n",pOsdInfo->u8OsdColor);
		__DBUG("pOsdInfo->struTimeOrg.s32Y: %d\n",pOsdInfo->struTimeOrg.s32Y);
		__DBUG("pOsdInfo->struTimeOrg.s32X: %d\n",pOsdInfo->struTimeOrg.s32X);
		__DBUG("pOsdInfo->struTitleOrg.s32Y: %d\n",pOsdInfo->struTitleOrg.s32Y);
		__DBUG("pOsdInfo->struTitleOrg.s32X: %d\n",pOsdInfo->struTitleOrg.s32X);
		__DBUG("pOsdInfo->szChnName: %s\n",pOsdInfo->szChnName);*/

		//////////////////////vmain������
		//��Ƶ������
		pVmainInfo->u16Width = pVmainInfoTmp->u16Width;
		//��Ƶ����߶�
		pVmainInfo->u16Height = pVmainInfoTmp->u16Height;
		//��Ƶ�����ʽ0--h264 1--MJPEG
		pVmainInfo->u8VideoEncType = pVmainInfoTmp->u8VideoEncType;
		//��������0-��ã�1-�κã�2-�Ϻã�3-һ�㣬4-�ϲ5-��	
		pVmainInfo->u8PicQuilty = pVmainInfoTmp->u8PicQuilty;
		//I֡���1-200
		pVmainInfo->u8Gop = pVmainInfoTmp->u8Gop;
		//�������� 0--������1--������
		pVmainInfo->u8FlowType = pVmainInfoTmp->u8FlowType;
		//�������� 32kbps-16Mkbps
		pVmainInfo->u32BitrateRate = pVmainInfoTmp->u32BitrateRate;
		//����֡��1-25/30
		pVmainInfo->u8FrameRate = pVmainInfoTmp->u8FrameRate;

		/*__DBUG("pVmainInfo->u16Width: %d\n",pVmainInfo->u16Width);
		__DBUG("pVmainInfo->u16Height: %d\n",pVmainInfo->u16Height);
		__DBUG("pVmainInfo->u8VideoEncType: %d\n",pVmainInfo->u8VideoEncType);
		__DBUG("pVmainInfo->u8PicQuilty: %d\n",pVmainInfo->u8PicQuilty);
		__DBUG("pVmainInfo->u8Gop: %d\n",pVmainInfo->u8Gop);
		__DBUG("pVmainInfo->u8FlowType: %d\n",pVmainInfo->u8FlowType);
		__DBUG("pVmainInfo->u32BitrateRate: %d\n",pVmainInfo->u32BitrateRate);
		__DBUG("pVmainInfo->u8FrameRate: %d\n",pVmainInfo->u8FrameRate);*/
		
		//////////////////////vsub������
		//��Ƶ������
		pVsubInfo->u16Width = pVsubInfoTmp->u16Width;
		//��Ƶ����߶�
		pVsubInfo->u16Height = pVsubInfoTmp->u16Height;
		//��Ƶ�����ʽ0--h264 1--MJPEG 2--JPEG	
		pVsubInfo->u8VideoEncType = pVsubInfoTmp->u8VideoEncType;
		//��������0-��ã�1-�κã�2-�Ϻã�3-һ�㣬4-�ϲ5-��	
		pVsubInfo->u8PicQuilty = pVsubInfoTmp->u8PicQuilty;
		//I֡���1-200
		pVsubInfo->u8Gop = pVsubInfoTmp->u8Gop;
		//�������� 0--������1--������
		pVsubInfo->u8FlowType = pVsubInfoTmp->u8FlowType;
		//�������� 32kbps-16Mkbps
		pVsubInfo->u32BitrateRate = pVsubInfoTmp->u32BitrateRate;
		//����֡��1-25/30
		pVsubInfo->u8FrameRate = pVsubInfoTmp->u8FrameRate;

		/*__DBUG("pVsubInfo->u16Width: %d\n",pVsubInfo->u16Width);
		__DBUG("pVsubInfo->u16Height: %d\n",pVsubInfo->u16Height);
		__DBUG("pVsubInfo->u8VideoEncType: %d\n",pVsubInfo->u8VideoEncType);
		__DBUG("pVsubInfo->u8PicQuilty: %d\n",pVsubInfo->u8PicQuilty);
		__DBUG("pVsubInfo->u8Gop: %d\n",pVsubInfo->u8Gop);
		__DBUG("pVsubInfo->u8FlowType: %d\n",pVsubInfo->u8FlowType);
		__DBUG("pVsubInfo->u32BitrateRate: %d\n",pVsubInfo->u32BitrateRate);
		__DBUG("pVsubInfo->u8FrameRate: %d\n",pVsubInfo->u8FrameRate);*/
		
		//////////////////////encode level
		pVideoInfo->eEncodeLevel = videoInfo.eEncodeLevel;
		//__DBUG("pVideoInfo->eEncodeLevel: %d\n",pVideoInfo->eEncodeLevel);
		
		//////////////////////vmask��Ƶ�ڵ�
		//--1.������Ƶ�ڵ�0--������Ƶ�ڵ�
		pVmaskInfo->u8Open = pVmaskInfoTmp->u8Open;
		//��Ƶ�ڵ�����
		for(i = 0; i < IPNC_VMASK_REG_NUM; i++)
		{
			pVmaskInfo->struArea[i].s32X = pVmaskInfoTmp->struArea[i].s32X;
			pVmaskInfo->struArea[i].s32Y = pVmaskInfoTmp->struArea[i].s32Y;
			pVmaskInfo->struArea[i].u32Height = pVmaskInfoTmp->struArea[i].u32Height;
			pVmaskInfo->struArea[i].u32Width  = pVmaskInfoTmp->struArea[i].u32Width;
		}
		
		/*__DBUG("pVmaskInfo->u8Open: %d\n", pVmaskInfo->u8Open);
		for(i = 0; i < IPNC_VMASK_REG_NUM; i++)
		{
			__DBUG("pVmaskInfo->struArea[%d].s32X: %d\n", i, pVmaskInfo->struArea[i].s32X);
			__DBUG("pVmaskInfo->struArea[%d].s32Y: %d\n", i, pVmaskInfo->struArea[i].s32Y);
			__DBUG("pVmaskInfo->struArea[%d].u32Height: %d\n", i, pVmaskInfo->struArea[i].u32Height);
			__DBUG("pVmaskInfo->struArea[%d].u32Width: %d\n", i, pVmaskInfo->struArea[i].u32Width);
		}*/
		//////////////////////vcapture
		
		//////////////////////vima
		pImaInfo->eSuppMask = pImaInfoTmp->eSuppMask;
		pImaInfo->eSetMask = pImaInfoTmp->eSetMask;

		//����
		pImaInfo->struBrightness.u8Default = pImaInfoTmp->struBrightness.u8Default;
		pImaInfo->struBrightness.u8Value = pImaInfoTmp->struBrightness.u8Value;
		pImaInfo->struBrightness.u8Step = pImaInfoTmp->struBrightness.u8Step;
		//�Աȶ�
		pImaInfo->struContrast.u8Default = pImaInfoTmp->struContrast.u8Default;
		pImaInfo->struContrast.u8Value = pImaInfoTmp->struContrast.u8Value;
		pImaInfo->struContrast.u8Step = pImaInfoTmp->struContrast.u8Step;
		//���Ͷ�
		pImaInfo->struSaturation.u8Default = pImaInfoTmp->struSaturation.u8Default;
		pImaInfo->struSaturation.u8Value = pImaInfoTmp->struSaturation.u8Value;
		pImaInfo->struSaturation.u8Step = pImaInfoTmp->struSaturation.u8Step;
		//ɫ��
		pImaInfo->struHue.u8Default = pImaInfoTmp->struHue.u8Default;
		pImaInfo->struHue.u8Value = pImaInfoTmp->struHue.u8Value;
		pImaInfo->struHue.u8Step = pImaInfoTmp->struHue.u8Step;
		//٤��
		pImaInfo->struGamma.u8Default = pImaInfoTmp->struGamma.u8Default;
		pImaInfo->struGamma.u8Value = pImaInfoTmp->struGamma.u8Value;
		pImaInfo->struGamma.u8Step = pImaInfoTmp->struGamma.u8Step;
		//���
		pImaInfo->struSharpness.u8Default = pImaInfoTmp->struSharpness.u8Default;
		pImaInfo->struSharpness.u8Value = pImaInfoTmp->struSharpness.u8Value;
		pImaInfo->struSharpness.u8Step = pImaInfoTmp->struSharpness.u8Step;
		//��
		pImaInfo->struRed.u8Default = pImaInfoTmp->struRed.u8Default;
		pImaInfo->struRed.u8Value = pImaInfoTmp->struRed.u8Value;
		pImaInfo->struRed.u8Step = pImaInfoTmp->struRed.u8Step;
		//��
		pImaInfo->struBlue.u8Default = pImaInfoTmp->struBlue.u8Default;
		pImaInfo->struBlue.u8Value = pImaInfoTmp->struBlue.u8Value;
		pImaInfo->struBlue.u8Step = pImaInfoTmp->struBlue.u8Step;

		/*__DBUG("pImaInfo->eSuppMask: %x\n", pImaInfo->eSuppMask);
		__DBUG("pImaInfo->eSetMask: %x\n", pImaInfo->eSetMask);

		__DBUG("pImaInfo->struBrightness.u8Default: %d\n", pImaInfo->struBrightness.u8Default);
		__DBUG("pImaInfo->struBrightness.u8Value: %d\n", pImaInfo->struBrightness.u8Value);
		__DBUG("pImaInfo->struBrightness.u8Step: %d\n", pImaInfo->struBrightness.u8Step);

		__DBUG("pImaInfo->struContrast.u8Default: %d\n", pImaInfo->struContrast.u8Default);
		__DBUG("pImaInfo->struContrast.u8Value: %d\n", pImaInfo->struContrast.u8Value);
		__DBUG("pImaInfo->struContrast.u8Step: %d\n", pImaInfo->struContrast.u8Step);

		__DBUG("pImaInfo->struSaturation.u8Default: %d\n", pImaInfo->struSaturation.u8Default);
		__DBUG("pImaInfo->struSaturation.u8Value: %d\n", pImaInfo->struSaturation.u8Value);
		__DBUG("pImaInfo->struSaturation.u8Step: %d\n", pImaInfo->struSaturation.u8Step);

		__DBUG("pImaInfo->struHue.u8Default: %d\n", pImaInfo->struHue.u8Default);
		__DBUG("pImaInfo->struHue.u8Value: %d\n", pImaInfo->struHue.u8Value);
		__DBUG("pImaInfo->struHue.u8Step: %d\n", pImaInfo->struHue.u8Step);

		__DBUG("pImaInfo->struGamma.u8Default: %d\n", pImaInfo->struGamma.u8Default);
		__DBUG("pImaInfo->struGamma.u8Value: %d\n", pImaInfo->struGamma.u8Value);
		__DBUG("pImaInfo->struGamma.u8Step: %d\n", pImaInfo->struGamma.u8Step);

		__DBUG("pImaInfo->struSharpness.u8Default: %d\n", pImaInfo->struSharpness.u8Default);
		__DBUG("pImaInfo->struSharpness.u8Value: %d\n", pImaInfo->struSharpness.u8Value);
		__DBUG("pImaInfo->struSharpness.u8Step: %d\n", pImaInfo->struSharpness.u8Step);

		__DBUG("pImaInfo->struRed.u8Default: %d\n", pImaInfo->struRed.u8Default);
		__DBUG("pImaInfo->struRed.u8Value: %d\n", pImaInfo->struRed.u8Value);
		__DBUG("pImaInfo->struRed.u8Step: %d\n", pImaInfo->struRed.u8Step);

		__DBUG("pImaInfo->struBlue.u8Default: %d\n", pImaInfo->struBlue.u8Default);
		__DBUG("pImaInfo->struBlue.u8Value: %d\n", pImaInfo->struBlue.u8Value);
		__DBUG("pImaInfo->struBlue.u8Step: %d\n", pImaInfo->struBlue.u8Step);*/
#endif
		//__ERR("sizeof(IPNC_DEV_VIDEO_CFG_S): %d\n", sizeof(IPNC_DEV_VIDEO_CFG_S));
		//__ERR("sizeof(TI_DEV_VIDEO_CFG_S): %d\n", sizeof(TI_DEV_VIDEO_CFG_S));
		memcpy(pVideoInfo, &videoInfo, sizeof(IPNC_DEV_VIDEO_CFG_S));
	}
	else
		__ERR("ti_param_get_video_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_DEV_VIDEO_CFG_S) : ret);
}
static int ti_param_set_video_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_VIDEO_CFG_S *pVideoInfo = (IPNC_DEV_VIDEO_CFG_S *)pData;
	TI_DEV_VIDEO_CFG_S videoInfo;
	int i = 0, ret = -1;

	memset(&videoInfo, 0, sizeof(TI_DEV_VIDEO_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&videoInfo, 
								sizeof(TI_DEV_VIDEO_CFG_S), 
								TI_CMD_GET_VIDEO_CFG);

	if((0 < ret) && (NULL != pVideoInfo))
	{
		TI_DEV_OSD_CFG_S      *pOsdInfoTmp    = &videoInfo.struOsd;
		TI_DEV_VMASK_CFG_S    *pVmaskInfoTmp  = &videoInfo.struVMask;
		TI_DEV_VENC_CFG_S	  *pVmainInfoTmp  = &videoInfo.struMainVenc;
		TI_DEV_VENC_CFG_S	  *pVsubInfoTmp   = &videoInfo.struSubVenc;
		TI_DEV_CAPTURE_CFG_S  *pCaptureInfoTmp  = &videoInfo.struCapture;
		TI_DEV_IMA_CFG_S      *pImaInfoTmp      = &videoInfo.struIma;

		IPNC_DEV_OSD_CFG_S     *pOsdInfo   = &pVideoInfo->struOsd;
		IPNC_DEV_VMASK_CFG_S   *pVmaskInfo = &pVideoInfo->struVMask;
		IPNC_DEV_VENC_CFG_S	  *pVmainInfo = &pVideoInfo->struMainVenc;
		IPNC_DEV_VENC_CFG_S	  *pVsubInfo  = &pVideoInfo->struSubVenc;
		IPNC_DEV_CAPTURE_CFG_S *pCaptureInfo = &pVideoInfo->struCapture;
		IPNC_DEV_IMA_CFG_S    *pImaInfo     = &pVideoInfo->struIma;
		
		//////////////////////OSD
		//����ʹ�� --1 ��ʾ����osd 0--���ر���osd
		pOsdInfoTmp->u8EnableTitleOsd = pOsdInfo->u8EnableTitleOsd;
		//ʱ��ʹ�� --1 ��ʾʱ��osd 0--����ʱ��osd
		pOsdInfoTmp->u8EnableTimeOsd = pOsdInfo->u8EnableTimeOsd;
		//����ʹ�� --1 ��ʾ���� 0--��������
		pOsdInfoTmp->u8DispWeek = pOsdInfo->u8DispWeek;
		//����ʹ�� --1��ʾ����osd  0--��������osd
		pOsdInfoTmp->u8EnableBitrateOsd = pOsdInfo->u8EnableBitrateOsd;
		//��ʾʱ���ʽ
		//--0 YYYY-MM-DD HH:MM:SS
  		//--1 MM-DD-YYYY HH:MM:SS
  		//--2 DD-MM-YYYY HH:MM:SS
		//--3 YYYY/MM/DD HH:MM:SS
		//--4 MM/DD/YYYY HH:MM:SS
		//--5 DD/MM/YYYY HH:MM:SS
		pOsdInfoTmp->u8TimeOsdType =  pOsdInfo->u8TimeOsdType;
		//ʱ�����  --0 24 hour --1 12 hour
		pOsdInfoTmp->u8HourOsdType =  pOsdInfo->u8HourOsdType;
		//��ɫ���
		pOsdInfoTmp->u8ColorValidFlag = pOsdInfo->u8ColorValidFlag;
		//������ɫ
		//----0 ---black
  		//---1---white
  		//---2---blue
  		//---3---yellow
		pOsdInfoTmp->u8OsdColor   = pOsdInfo->u8OsdColor;
		pOsdInfoTmp->u32TimeColor = pOsdInfo->u32TimeColor;
		pOsdInfoTmp->u32ChnColor  = pOsdInfo->u32ChnColor;
		//ʱ��������ʾλ��
		pOsdInfoTmp->struTimeOrg.s32Y =  pOsdInfo->struTimeOrg.s32Y;
		pOsdInfoTmp->struTimeOrg.s32X =  pOsdInfo->struTimeOrg.s32X;
		//������ʾλ��
		pOsdInfoTmp->struTitleOrg.s32Y =  pOsdInfo->struTitleOrg.s32Y;
		pOsdInfoTmp->struTitleOrg.s32X =  pOsdInfo->struTitleOrg.s32X;
		//��������
		nvr_string_copy(pOsdInfoTmp->szChnName, sizeof(pOsdInfoTmp->szChnName), 
						pOsdInfo->szChnName);
		
		/*__DBUG("pOsdInfoTmp->u8EnableTitleOsd: %d\n",pOsdInfoTmp->u8EnableTitleOsd);
		__DBUG("pOsdInfoTmp->u8EnableTimeOsd: %d\n",pOsdInfoTmp->u8EnableTimeOsd);
		__DBUG("pOsdInfoTmp->u8DispWeek: %d\n",pOsdInfoTmp->u8DispWeek);
		__DBUG("pOsdInfoTmp->u8EnableBitrateOsd: %d\n",pOsdInfoTmp->u8EnableBitrateOsd);
		
		__DBUG("pOsdInfoTmp->u8TimeOsdType: %d\n",pOsdInfoTmp->u8TimeOsdType);
		__DBUG("pOsdInfoTmp->u8HourOsdType: %d\n",pOsdInfoTmp->u8HourOsdType);
		__DBUG("pOsdInfoTmp->u8OsdColor: %d\n",pOsdInfoTmp->u8OsdColor);
		__DBUG("pOsdInfoTmp->struTimeOrg.s32Y: %d\n",pOsdInfoTmp->struTimeOrg.s32Y);
		__DBUG("pOsdInfoTmp->struTimeOrg.s32X: %d\n",pOsdInfoTmp->struTimeOrg.s32X);
		__DBUG("pOsdInfoTmp->struTitleOrg.s32Y: %d\n",pOsdInfoTmp->struTitleOrg.s32Y);
		__DBUG("pOsdInfoTmp->struTitleOrg.s32X: %d\n",pOsdInfoTmp->struTitleOrg.s32X);
		__DBUG("pOsdInfoTmp->szChnName: %s\n",pOsdInfoTmp->szChnName);*/

		//////////////////////vmain������
		//��Ƶ������
		pVmainInfoTmp->u16Width = pVmainInfo->u16Width;
		//��Ƶ����߶�
		pVmainInfoTmp->u16Height = pVmainInfo->u16Height;
		//��Ƶ�����ʽ0--h264 1--MJPEG 2--JPEG	
		pVmainInfoTmp->u8VideoEncType = pVmainInfo->u8VideoEncType;
		//��������0-��ã�1-�κã�2-�Ϻã�3-һ�㣬4-�ϲ5-��	
		pVmainInfoTmp->u8PicQuilty = pVmainInfo->u8PicQuilty;
		//I֡���1-200
		pVmainInfoTmp->u8Gop = pVmainInfo->u8Gop;
		//�������� 0--������1--������
		pVmainInfoTmp->u8FlowType = pVmainInfo->u8FlowType;
		//�������� 32kbps-16Mkbps
		pVmainInfoTmp->u32BitrateRate = pVmainInfo->u32BitrateRate;
		//����֡��1-25/30
		pVmainInfoTmp->u8FrameRate = pVmainInfo->u8FrameRate;

		/*__DBUG("pVmainInfoTmp->u16Width: %d\n",pVmainInfoTmp->u16Width);
		__DBUG("pVmainInfoTmp->u16Height: %d\n",pVmainInfoTmp->u16Height);
		__DBUG("pVmainInfoTmp->u8VideoEncType: %d\n",pVmainInfoTmp->u8VideoEncType);
		__DBUG("pVmainInfoTmp->u8PicQuilty: %d\n",pVmainInfoTmp->u8PicQuilty);
		__DBUG("pVmainInfoTmp->u8Gop: %d\n",pVmainInfoTmp->u8Gop);
		__DBUG("pVmainInfoTmp->u8FlowType: %d\n",pVmainInfoTmp->u8FlowType);
		__DBUG("pVmainInfoTmp->u32BitrateRate: %d\n",pVmainInfoTmp->u32BitrateRate);
		__DBUG("pVmainInfoTmp->u8FrameRate: %d\n",pVmainInfoTmp->u8FrameRate);*/
		
		//////////////////////vsub������
		//��Ƶ������
		pVsubInfoTmp->u16Width = pVsubInfo->u16Width;
		//��Ƶ����߶�
		pVsubInfoTmp->u16Height = pVsubInfo->u16Height;
		//��Ƶ�����ʽ0--h264 1--MJPEG 2--JPEG	
		pVsubInfoTmp->u8VideoEncType = pVsubInfo->u8VideoEncType;
		//��������0-��ã�1-�κã�2-�Ϻã�3-һ�㣬4-�ϲ5-��	
		pVsubInfoTmp->u8PicQuilty = pVsubInfo->u8PicQuilty;
		//I֡���1-200
		pVsubInfoTmp->u8Gop = pVsubInfo->u8Gop;
		//�������� 0--������1--������
		pVsubInfoTmp->u8FlowType = pVsubInfo->u8FlowType;
		//�������� 32kbps-16Mkbps
		pVsubInfoTmp->u32BitrateRate = pVsubInfo->u32BitrateRate;
		//����֡��1-25/30
		pVsubInfoTmp->u8FrameRate = pVsubInfo->u8FrameRate;

		/*__DBUG("pVsubInfoTmp->u16Width: %d\n",pVsubInfoTmp->u16Width);
		__DBUG("pVsubInfoTmp->u16Height: %d\n",pVsubInfoTmp->u16Height);
		__DBUG("pVsubInfoTmp->u8VideoEncType: %d\n",pVsubInfoTmp->u8VideoEncType);
		__DBUG("pVsubInfoTmp->u8PicQuilty: %d\n",pVsubInfoTmp->u8PicQuilty);
		__DBUG("pVsubInfoTmp->u8Gop: %d\n",pVsubInfoTmp->u8Gop);
		__DBUG("pVsubInfoTmp->u8FlowType: %d\n",pVsubInfoTmp->u8FlowType);
		__DBUG("pVsubInfoTmp->u32BitrateRate: %d\n",pVsubInfoTmp->u32BitrateRate);
		__DBUG("pVsubInfoTmp->u8FrameRate: %d\n",pVsubInfoTmp->u8FrameRate);*/

		//////////////////////encode level
		videoInfo.eEncodeLevel = pVideoInfo->eEncodeLevel;
		__DBUG("videoInfo.eEncodeLevel: %d\n",videoInfo.eEncodeLevel);	

		//////////////////////vmask
		//--1.������Ƶ�ڵ�0--������Ƶ�ڵ�
		pVmaskInfoTmp->u8Open = !!pVmaskInfo->u8Open;
		//��Ƶ�ڵ�����
		for(i = 0; i < IPNC_VMASK_REG_NUM; i++)
		{
			pVmaskInfoTmp->struArea[i].s32X = pVmaskInfo->struArea[i].s32X;
			pVmaskInfoTmp->struArea[i].s32Y = pVmaskInfo->struArea[i].s32Y;
			pVmaskInfoTmp->struArea[i].u32Height = pVmaskInfo->struArea[i].u32Height;
			pVmaskInfoTmp->struArea[i].u32Width = pVmaskInfo->struArea[i].u32Width;
		}
		
		/*__DBUG("pVmaskInfoTmp->u8Open: %d\n", pVmaskInfo->u8Open);
		for(i = 0; i < IPNC_VMASK_REG_NUM; i++)
		{
			__DBUG("pVmaskInfoTmp->struArea[%d].s32X: %d\n", i, pVmaskInfoTmp->struArea[i].s32X);
			__DBUG("pVmaskInfoTmp->struArea[%d].s32Y: %d\n", i, pVmaskInfoTmp->struArea[i].s32Y);
			__DBUG("pVmaskInfoTmp->struArea[%d].u32Height: %d\n", i, pVmaskInfoTmp->struArea[i].u32Height);
			__DBUG("pVmaskInfoTmp->struArea[%d].u32Width: %d\n", i, pVmaskInfoTmp->struArea[i].u32Width);
		}*/
		//////////////////////vcapture
		pCaptureInfoTmp->u16Width = pCaptureInfo->u16Width;
		pCaptureInfoTmp->u16Height = pCaptureInfo->u16Height;
		pCaptureInfoTmp->u8VideoEncType = pCaptureInfo->u8VideoEncType;
		pCaptureInfoTmp->u8Quilty = pCaptureInfo->u8Quilty;
		//////////////////////vima
		//pImaInfo->eSuppMask = pImaInfoTmp->eSuppMask;
		//pImaInfo->eSetMask = pImaInfoTmp->eSetMask;

		//����
		//pImaInfoTmp->struBrightness.u8Default = pImaInfo->struBrightness.u8Default;
		pImaInfoTmp->struBrightness.u8Value = pImaInfo->struBrightness.u8Value;
		//pImaInfoTmp->struBrightness.u8Step = pImaInfo->struBrightness.u8Step;
		//�Աȶ�
		//pImaInfoTmp->struContrast.u8Default = pImaInfo->struContrast.u8Default;
		pImaInfoTmp->struContrast.u8Value = pImaInfo->struContrast.u8Value;
		//pImaInfoTmp->struContrast.u8Step = pImaInfo->struContrast.u8Step;
		//���Ͷ�
		//pImaInfoTmp->struSaturation.u8Default = pImaInfo->struSaturation.u8Default;
		pImaInfoTmp->struSaturation.u8Value = pImaInfo->struSaturation.u8Value;
		//pImaInfoTmp->struSaturation.u8Step = pImaInfo->struSaturation.u8Step;
		//ɫ��
		//pImaInfoTmp->struHue.u8Default = pImaInfo->struHue.u8Default;
		pImaInfoTmp->struHue.u8Value = pImaInfo->struHue.u8Value;
		//pImaInfoTmp->struHue.u8Step = pImaInfo->struHue.u8Step;
		//٤��
		//pImaInfoTmp->struGamma.u8Default = pImaInfo->struGamma.u8Default;
		pImaInfoTmp->struGamma.u8Value = pImaInfo->struGamma.u8Value;
		//pImaInfoTmp->struGamma.u8Step = pImaInfo->struGamma.u8Step;
		//���
		//pImaInfoTmp->struSharpness.u8Default = pImaInfo->struSharpness.u8Default;
		pImaInfoTmp->struSharpness.u8Value = pImaInfo->struSharpness.u8Value;
		//pImaInfoTmp->struSharpness.u8Step = pImaInfo->struSharpness.u8Step;
		//��
		//pImaInfoTmp->struRed.u8Default = pImaInfo->struRed.u8Default;
		pImaInfoTmp->struRed.u8Value = pImaInfo->struRed.u8Value;
		//pImaInfoTmp->struRed.u8Step = pImaInfo->struRed.u8Step;
		//��
		//pImaInfoTmp->struBlue.u8Default = pImaInfo->struBlue.u8Default;
		pImaInfoTmp->struBlue.u8Value = pImaInfo->struBlue.u8Value;
		//pImaInfoTmp->struBlue.u8Step = pImaInfo->struBlue.u8Step;

		//__DBUG("pImaInfoTmp->eSuppMask: %d\n", pImaInfo->eSuppMask);
		//__DBUG("pImaInfoTmp->eSetMask: %d\n", pImaInfo->eSetMask);

		/*__DBUG("pImaInfoTmp->struBrightness.u8Default: %d\n", pImaInfoTmp->struBrightness.u8Default);
		__DBUG("pImaInfoTmp->struBrightness.u8Value: %d\n", pImaInfoTmp->struBrightness.u8Value);
		__DBUG("pImaInfoTmp->struBrightness.u8Step: %d\n", pImaInfoTmp->struBrightness.u8Step);

		__DBUG("pImaInfoTmp->struContrast.u8Default: %d\n", pImaInfoTmp->struContrast.u8Default);
		__DBUG("pImaInfoTmp->struContrast.u8Value: %d\n", pImaInfoTmp->struContrast.u8Value);
		__DBUG("pImaInfoTmp->struContrast.u8Step: %d\n", pImaInfoTmp->struContrast.u8Step);

		__DBUG("pImaInfoTmp->struSaturation.u8Default: %d\n", pImaInfoTmp->struSaturation.u8Default);
		__DBUG("pImaInfoTmp->struSaturation.u8Value: %d\n", pImaInfoTmp->struSaturation.u8Value);
		__DBUG("pImaInfoTmp->struSaturation.u8Step: %d\n", pImaInfoTmp->struSaturation.u8Step);

		__DBUG("pImaInfoTmp->struHue.u8Default: %d\n", pImaInfoTmp->struHue.u8Default);
		__DBUG("pImaInfoTmp->struHue.u8Value: %d\n", pImaInfoTmp->struHue.u8Value);
		__DBUG("pImaInfoTmp->struHue.u8Step: %d\n", pImaInfoTmp->struHue.u8Step);

		__DBUG("pImaInfoTmp->struGamma.u8Default: %d\n", pImaInfoTmp->struGamma.u8Default);
		__DBUG("pImaInfoTmp->struGamma.u8Value: %d\n", pImaInfoTmp->struGamma.u8Value);
		__DBUG("pImaInfoTmp->struGamma.u8Step: %d\n", pImaInfoTmp->struGamma.u8Step);

		__DBUG("pImaInfoTmp->struSharpness.u8Default: %d\n", pImaInfoTmp->struSharpness.u8Default);
		__DBUG("pImaInfoTmp->struSharpness.u8Value: %d\n", pImaInfoTmp->struSharpness.u8Value);
		__DBUG("pImaInfoTmp->struSharpness.u8Step: %d\n", pImaInfoTmp->struSharpness.u8Step);

		__DBUG("pImaInfoTmp->struRed.u8Default: %d\n", pImaInfoTmp->struRed.u8Default);
		__DBUG("pImaInfoTmp->struRed.u8Value: %d\n", pImaInfoTmp->struRed.u8Value);
		__DBUG("pImaInfoTmp->struRed.u8Step: %d\n", pImaInfoTmp->struRed.u8Step);

		__DBUG("pImaInfoTmp->struBlue.u8Default: %d\n", pImaInfoTmp->struBlue.u8Default);
		__DBUG("pImaInfoTmp->struBlue.u8Value: %d\n", pImaInfoTmp->struBlue.u8Value);
		__DBUG("pImaInfoTmp->struBlue.u8Step: %d\n", pImaInfoTmp->struBlue.u8Step);*/
		
		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&videoInfo, 
									sizeof(TI_DEV_VIDEO_CFG_S), 
									TI_CMD_SET_VIDEO_CFG);

	}
	else
		__ERR("ti_param_set_video_param faile!\n");
	
	return ret;
}
static int ti_param_check_video_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
	
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_DEV_VIDEO_CFG_S): %d\n", sizeof(IPNC_DEV_VIDEO_CFG_S));
	if(dataSize != sizeof(IPNC_DEV_VIDEO_CFG_S))
		return -1;
		
	return 0;
}
/*imaͨ�ýṹ�庯��************************************************************/
static int ti_param_get_ima_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_IMA_CFG_S *pImaInfo = (IPNC_DEV_IMA_CFG_S *)pData;
	TI_DEV_IMA_CFG_S imaInfo;
	int ret = -1;

	memset(&imaInfo, 0, sizeof(TI_DEV_IMA_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&imaInfo, 
								sizeof(TI_DEV_IMA_CFG_S), 
								TI_CMD_GET_IMA_CFG);

	if((0 < ret) && (NULL != pImaInfo))
	{
		//////////////////////ima
		memcpy(pImaInfo, &imaInfo, sizeof(IPNC_DEV_IMA_CFG_S));
		
	}
	else
		__ERR("ti_param_get_ima_param faile!\n");
	
	return ((ret > 0) ? sizeof(IPNC_DEV_IMA_CFG_S) : ret);
}
static int ti_param_set_ima_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_IMA_CFG_S *pImaInfo = (IPNC_DEV_IMA_CFG_S *)pData;
	TI_DEV_IMA_CFG_S imaInfo;
	int ret = -1;

	memset(&imaInfo, 0, sizeof(TI_DEV_IMA_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&imaInfo, 
								sizeof(TI_DEV_IMA_CFG_S), 
								TI_CMD_GET_IMA_CFG);

	if((0 < ret) && (NULL != pImaInfo))
	{
		//////////////////////ima
		//����
		//imaInfo.struBrightness.u8Default = pImaInfo->struBrightness.u8Default;
		imaInfo.struBrightness.u8Value = pImaInfo->struBrightness.u8Value;
		//imaInfo.struBrightness.u8Step = pImaInfo->struBrightness.u8Step;
		//�Աȶ�
		//imaInfo.struContrast.u8Default = pImaInfo->struContrast.u8Default;
		imaInfo.struContrast.u8Value = pImaInfo->struContrast.u8Value;
		//imaInfo.struContrast.u8Step = pImaInfo->struContrast.u8Step;
		//���Ͷ�
		//imaInfo.struSaturation.u8Default = pImaInfo->struSaturation.u8Default;
		imaInfo.struSaturation.u8Value = pImaInfo->struSaturation.u8Value;
		//imaInfo.struSaturation.u8Step = pImaInfo->struSaturation.u8Step;
		//ɫ��
		//imaInfo.struHue.u8Default = pImaInfo->struHue.u8Default;
		imaInfo.struHue.u8Value = pImaInfo->struHue.u8Value;
		//imaInfo.struHue.u8Step = pImaInfo->struHue.u8Step;
		//٤��
		//imaInfo.struGamma.u8Default = pImaInfo->struGamma.u8Default;
		imaInfo.struGamma.u8Value = pImaInfo->struGamma.u8Value;
		//imaInfo.struGamma.u8Step = pImaInfo->struGamma.u8Step;
		//���
		//imaInfo.struSharpness.u8Default = pImaInfo->struSharpness.u8Default;
		imaInfo.struSharpness.u8Value = pImaInfo->struSharpness.u8Value;
		//imaInfo.struSharpness.u8Step = pImaInfo->struSharpness.u8Step;
		//��
		//imaInfo.struRed.u8Default = pImaInfo->struRed.u8Default;
		imaInfo.struRed.u8Value = pImaInfo->struRed.u8Value;
		//imaInfo.struRed.u8Step = pImaInfo->struRed.u8Step;
		//��
		//imaInfo.struBlue.u8Default = pImaInfo->struBlue.u8Default;
		imaInfo.struBlue.u8Value = pImaInfo->struBlue.u8Value;
		//imaInfo.struBlue.u8Step = pImaInfo->struBlue.u8Step;

		ret = ti_send_set_param_cmd(logonHandle, 
								&imaInfo, 
								sizeof(IPNC_DEV_IMA_CFG_S), 
								TI_CMD_SET_IMA_CFG);
	}
	else
		__ERR("ti_param_set_ima_param faile!\n");
	
	return ret;
}
static int ti_param_check_ima_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
		
	if(dataSize != sizeof(IPNC_DEV_IMA_CFG_S))
		return -1;
	
	return 0;
}


/*md�ƶ����ͨ�ýṹ�庯��************************************************************/

static int ti_param_get_md_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_MD_CFG_S *pMdInfo = (IPNC_DEV_MD_CFG_S *)pData;
	TI_DEV_MD_CFG_S mdInfo;
	int i = 0, j = 0, ret = -1;

	memset(&mdInfo, 0, sizeof(TI_DEV_MD_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&mdInfo, 
								sizeof(TI_DEV_MD_CFG_S), 
								TI_CMD_GET_VMD_CFG);

	if((0 < ret) && (NULL != pMdInfo))
	{
		//�ƶ����ʹ�� 0--�ر� 1--����
		pMdInfo->u8Enable = mdInfo.u8Enable;
		//��������� 0--�ܸ� 1--�� 2--�� 3--�� 4--�ܵ�
		pMdInfo->u8Level = mdInfo.u8Level;
		//�������
		for(i = 0; i < IPNC_VMD_REG_NUM; i++)
		{
			pMdInfo->struRect[i].s32X = mdInfo.struRect[i].s32X;
			pMdInfo->struRect[i].s32Y = mdInfo.struRect[i].s32Y;
			pMdInfo->struRect[i].u32Height = mdInfo.struRect[i].u32Height;
			pMdInfo->struRect[i].u32Width = mdInfo.struRect[i].u32Width;
		}
		//���ʱ��
		for(i = 0; i < IPNC_MAX_SEG_NUM; i++)
		{
			for(j = 0; j < 8; j++)
			{
				pMdInfo->struSeg[i][j].u8Open = mdInfo.struSeg[i][j].u8Open;
				pMdInfo->struSeg[i][j].beginSec = mdInfo.struSeg[i][j].beginSec;
				pMdInfo->struSeg[i][j].endSec = mdInfo.struSeg[i][j].endSec;
			}
		}
		//�������
		pMdInfo->struLinkAct.u32OutPut = mdInfo.struLinkAct.u32OutPut;
		//�����������ʱ��
		pMdInfo->struLinkAct.u32OutPersist = mdInfo.struLinkAct.u32OutPersist;

		//����ץ��
		pMdInfo->struLinkAct.u32ShootChannel = mdInfo.struLinkAct.u32ShootChannel;
		//ץ����
		pMdInfo->struLinkAct.u8ShootNum = mdInfo.struLinkAct.u8ShootNum;
		//ץ�Ĵ洢ģʽ
		pMdInfo->struLinkAct.u8ShootMode = mdInfo.struLinkAct.u8ShootMode;
		//ץ�ĳ���ʱ��
		pMdInfo->struLinkAct.u32ShootInterval = mdInfo.struLinkAct.u32ShootInterval;

		//¼�����
		pMdInfo->struLinkAct.u32RecChannel = mdInfo.struLinkAct.u32RecChannel;
		//¼�����ʱ��
		pMdInfo->struLinkAct.u32RecTime = mdInfo.struLinkAct.u32RecTime;
		//¼��ģʽ
		pMdInfo->struLinkAct.u8RecMode = mdInfo.struLinkAct.u8RecMode;
		//����PC¼��ͨ��
		pMdInfo->struLinkAct.u32PCRecChannel = mdInfo.struLinkAct.u32PCRecChannel;
		
		//����email
		pMdInfo->struLinkAct.u8Email = mdInfo.struLinkAct.u8Email;

		//�����ʱ��
		pMdInfo->u32DetectInterval = mdInfo.u32DetectInterval;
		/*
		__DBUG("pMdInfo->u8Enable: %d\n",pMdInfo->u8Enable);
		__DBUG("pMdInfo->u8Level: %d\n",pMdInfo->u8Level);
		for(i = 0; i < IPNC_VMD_REG_NUM; i++)
		{
			__DBUG("pMdInfo->struRect[%d].s32X: %d\n", i, pMdInfo->struRect[i].s32X);
			__DBUG("pMdInfo->struRect[%d].s32Y: %d\n", i, pMdInfo->struRect[i].s32Y);
			__DBUG("pMdInfo->struRect[%d].u32Height: %d\n", i, pMdInfo->struRect[i].u32Height);
			__DBUG("pMdInfo->struRect[%d].u32Width: %d\n", i, pMdInfo->struRect[i].u32Width);
		}
		for(i = 0; i < IPNC_MAX_SEG_NUM; i++)
		{
			for(j = 0; j < 8; j++)
			{
				__DBUG("pMdInfo->struSeg[%d][%d].u8Open: %d\n", i, j, pMdInfo->struSeg[i][j].u8Open);
				__DBUG("pMdInfo->struSeg[%d][%d].beginSec: %d\n", i, j, pMdInfo->struSeg[i][j].beginSec);
				__DBUG("pMdInfo->struSeg[%d][%d].endSec: %d\n", i, j, pMdInfo->struSeg[i][j].endSec);
				
			}
		}
		
		__DBUG("pMdInfo->struLinkAct.u32OutPut: %d\n",pMdInfo->struLinkAct.u32OutPut);
		__DBUG("pMdInfo->struLinkAct.u32OutPersist: %d\n",pMdInfo->struLinkAct.u32OutPersist);
		
		__DBUG("pMdInfo->struLinkAct.u32ShootChannel: %d\n",pMdInfo->struLinkAct.u32ShootChannel);
		__DBUG("pMdInfo->struLinkAct.u8ShootNum: %d\n",pMdInfo->struLinkAct.u8ShootNum);
		__DBUG("pMdInfo->struLinkAct.u8ShootMode: %d\n",pMdInfo->struLinkAct.u8ShootMode);
		__DBUG("pMdInfo->struLinkAct.u32ShootInterval: %d\n",pMdInfo->struLinkAct.u32ShootInterval);
		
		__DBUG("pMdInfo->struLinkAct.u32RecChannel: %d\n",pMdInfo->struLinkAct.u32RecChannel);
		__DBUG("pMdInfo->struLinkAct.u32RecTime: %d\n",pMdInfo->struLinkAct.u32RecTime);
		__DBUG("ppMdInfo->struLinkAct.u8RecMode: %d\n",pMdInfo->struLinkAct.u8RecMode);
		__DBUG("pMdInfo->struLinkAct.u32PCRecChannel: %d\n",pMdInfo->struLinkAct.u32PCRecChannel);
		
		__DBUG("pMdInfo->struLinkAct.u8Email: %d\n",pMdInfo->struLinkAct.u8Email);
		__DBUG("pMdInfo->u32DetectInterval: %d\n",pMdInfo->u32DetectInterval);*/

	}
	else
		__ERR("ti_param_get_md_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_DEV_MD_CFG_S) : ret);
}
static int ti_param_set_md_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_MD_CFG_S *pMdInfo = (IPNC_DEV_MD_CFG_S *)pData;
	TI_DEV_MD_CFG_S mdInfo;
	int i = 0, j = 0, ret = -1;

	memset(&mdInfo, 0, sizeof(TI_DEV_MD_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&mdInfo, 
								sizeof(TI_DEV_MD_CFG_S), 
								TI_CMD_GET_VMD_CFG);

	if((0 < ret) && (NULL != pMdInfo))
	{
		//�ƶ����ʹ�� 0--�ر� 1--����
		mdInfo.u8Enable = pMdInfo->u8Enable;
		//��������� 0--�ܸ� 1--�� 2--�� 3--�� 4--�ܵ�
		mdInfo.u8Level = pMdInfo->u8Level;
		//�������
		for(i = 0; i < IPNC_VMD_REG_NUM; i++)
		{
			mdInfo.struRect[i].s32X = pMdInfo->struRect[i].s32X;
			mdInfo.struRect[i].s32Y = pMdInfo->struRect[i].s32Y;
			mdInfo.struRect[i].u32Height = pMdInfo->struRect[i].u32Height;
			mdInfo.struRect[i].u32Width = pMdInfo->struRect[i].u32Width;
		}
		//���ʱ��
		for(i = 0; i < IPNC_MAX_SEG_NUM; i++)
		{
			for(j = 0; j < 8; j++)
			{
				mdInfo.struSeg[i][j].u8Open = pMdInfo->struSeg[i][j].u8Open;
				mdInfo.struSeg[i][j].beginSec = pMdInfo->struSeg[i][j].beginSec;
				mdInfo.struSeg[i][j].endSec =pMdInfo->struSeg[i][j].endSec;
			}
		}
		//�������
		mdInfo.struLinkAct.u32OutPut = pMdInfo->struLinkAct.u32OutPut;
		//�����������ʱ��
		mdInfo.struLinkAct.u32OutPersist = pMdInfo->struLinkAct.u32OutPersist;

		//����ץ��
		mdInfo.struLinkAct.u32ShootChannel = pMdInfo->struLinkAct.u32ShootChannel;
		//ץ����
		mdInfo.struLinkAct.u8ShootNum = pMdInfo->struLinkAct.u8ShootNum;
		//ץ�Ĵ洢ģʽ
		mdInfo.struLinkAct.u8ShootMode = pMdInfo->struLinkAct.u8ShootMode;
		//ץ�ĳ���ʱ��
		mdInfo.struLinkAct.u32ShootInterval = pMdInfo->struLinkAct.u32ShootInterval;

		//¼�����
		mdInfo.struLinkAct.u32RecChannel = pMdInfo->struLinkAct.u32RecChannel;
		//¼�����ʱ��
		mdInfo.struLinkAct.u32RecTime = pMdInfo->struLinkAct.u32RecTime;
		//¼��ģʽ
		mdInfo.struLinkAct.u8RecMode = pMdInfo->struLinkAct.u8RecMode;
		//����PC¼��ͨ��
		mdInfo.struLinkAct.u32PCRecChannel = pMdInfo->struLinkAct.u32PCRecChannel;
		
		//����email
		mdInfo.struLinkAct.u8Email = pMdInfo->struLinkAct.u8Email;

		//�����ʱ��
		mdInfo.u32DetectInterval = pMdInfo->u32DetectInterval;
		/*
		__DBUG("mdInfo.u8Enable: %d\n",mdInfo.u8Enable);
		__DBUG("mdInfo.u8Level: %d\n",mdInfo.u8Level);
		for(i = 0; i < IPNC_VMD_REG_NUM; i++)
		{
			__DBUG("mdInfo.struRect[%d].s32X: %d\n", i, mdInfo.struRect[i].s32X);
			__DBUG("mdInfo.struRect[%d].s32Y: %d\n", i, mdInfo.struRect[i].s32Y);
			__DBUG("mdInfo.struRect[%d].u32Height: %d\n", i, mdInfo.struRect[i].u32Height);
			__DBUG("mdInfo.struRect[%d].u32Width: %d\n", i, mdInfo.struRect[i].u32Width);
		}
		for(i = 0; i < IPNC_MAX_SEG_NUM; i++)
		{
			for(j = 0; j < 8; j++)
			{
				__DBUG("mdInfo.struSeg[%d][%d].u8Open: %d\n", i, j, mdInfo.struSeg[i][j].u8Open);
				__DBUG("mdInfo.struSeg[%d][%d].beginSec: %d\n", i, j, mdInfo.struSeg[i][j].beginSec);
				__DBUG("mdInfo.struSeg[%d][%d].endSec: %d\n", i, j, mdInfo.struSeg[i][j].endSec);
				
			}
		}
		
		__DBUG("mdInfo.struLinkAct.u32OutPut: %d\n",mdInfo.struLinkAct.u32OutPut);
		__DBUG("mdInfo.struLinkAct.u32OutPersist: %d\n",mdInfo.struLinkAct.u32OutPersist);
		
		__DBUG("mdInfo.struLinkAct.u32ShootChannel: %d\n",mdInfo.struLinkAct.u32ShootChannel);
		__DBUG("mdInfo.struLinkAct.u8ShootNum: %d\n",mdInfo.struLinkAct.u8ShootNum);
		__DBUG("mdInfo.struLinkAct.u8ShootMode: %d\n",mdInfo.struLinkAct.u8ShootMode);
		__DBUG("mdInfo.struLinkAct.u32ShootInterval: %d\n",mdInfo.struLinkAct.u32ShootInterval);
		
		__DBUG("mdInfo.struLinkAct.u32RecChannel: %d\n",mdInfo.struLinkAct.u32RecChannel);
		__DBUG("mdInfo.struLinkAct.u32RecTime: %d\n",mdInfo.struLinkAct.u32RecTime);
		__DBUG("pmdInfo.struLinkAct.u8RecMode: %d\n",mdInfo.struLinkAct.u8RecMode);
		__DBUG("mdInfo.struLinkAct.u32PCRecChannel: %d\n",mdInfo.struLinkAct.u32PCRecChannel);
		
		__DBUG("mdInfo.struLinkAct.u8Email: %d\n",mdInfo.struLinkAct.u8Email);
		__DBUG("mdInfo.u32DetectInterval: %d\n",mdInfo.u32DetectInterval);*/

		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&mdInfo, 
									sizeof(TI_DEV_MD_CFG_S), 
									TI_CMD_SET_VMD_CFG);
	}
	else
		__ERR("ti_param_set_md_param faile!\n");
	return ret;
}
static int ti_param_check_md_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
	
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_DEV_MD_CFG_S): %d\n", sizeof(IPNC_DEV_MD_CFG_S));
	if(dataSize != sizeof(IPNC_DEV_MD_CFG_S))
		return -1;
		
	return 0;
}

/*di̽ͷ����ͨ�ýṹ�庯��************************************************************/

static int ti_param_get_di_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_DI_CFG_S *pDiInfo = (IPNC_DEV_DI_CFG_S *)pData;
	TI_DEV_DI_CFG_S diInfo;
	int i = 0, j = 0, ret = -1;

	memset(&diInfo, 0, sizeof(TI_DEV_DI_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&diInfo, 
								sizeof(TI_DEV_DI_CFG_S), 
								TI_CMD_GET_DI_CFG);

	if((0 < ret) && (NULL != pDiInfo))
	{
		//̽ͷ����ʹ�� 0--�ر� 1--����
		pDiInfo->u8Enable = diInfo.u8Enable;
		//̽ͷ����
		nvr_string_copy(pDiInfo->chDiName, sizeof(pDiInfo->chDiName),
						diInfo.chDiName);
		//̽ͷ���� 0--����̽ͷ 1--����̽ͷ
		pDiInfo->u8DiType = diInfo.u8DiType;

		//̽ͷʱ��
		for(i = 0; i < IPNC_MAX_SEG_NUM; i++)
		{
			for(j = 0; j < 8; j++)
			{
				pDiInfo->struSeg[i][j].u8Open = diInfo.struSeg[i][j].u8Open;
				pDiInfo->struSeg[i][j].beginSec = diInfo.struSeg[i][j].beginSec;
				pDiInfo->struSeg[i][j].endSec = diInfo.struSeg[i][j].endSec;
			}
		}
		//�������
		pDiInfo->struLinkAct.u32OutPut = diInfo.struLinkAct.u32OutPut;
		//�����������ʱ��
		pDiInfo->struLinkAct.u32OutPersist = diInfo.struLinkAct.u32OutPersist;

		//����ץ��
		pDiInfo->struLinkAct.u32ShootChannel = diInfo.struLinkAct.u32ShootChannel;
		//ץ����
		pDiInfo->struLinkAct.u8ShootNum = diInfo.struLinkAct.u8ShootNum;
		//ץ�Ĵ洢ģʽ
		pDiInfo->struLinkAct.u8ShootMode = diInfo.struLinkAct.u8ShootMode;
		//ץ�ĳ���ʱ��
		pDiInfo->struLinkAct.u32ShootInterval = diInfo.struLinkAct.u32ShootInterval;

		//¼�����
		pDiInfo->struLinkAct.u32RecChannel = diInfo.struLinkAct.u32RecChannel;
		//¼�����ʱ��
		pDiInfo->struLinkAct.u32RecTime = diInfo.struLinkAct.u32RecTime;
		//¼��ģʽ
		pDiInfo->struLinkAct.u8RecMode = diInfo.struLinkAct.u8RecMode;
		//����PC¼��ͨ��
		pDiInfo->struLinkAct.u32PCRecChannel = diInfo.struLinkAct.u32PCRecChannel;
		
		//�����ʱ��
		pDiInfo->u32DetectInterval = diInfo.u32DetectInterval;
		/*
		__DBUG("pDiInfo->u8Enable: %d\n",pDiInfo->u8Enable);
		__DBUG("pDiInfo->chDiName: %s\n",pDiInfo->chDiName);
		__DBUG("pDiInfo->u8DiType: %d\n",pDiInfo->u8DiType);

		for(i = 0; i < IPNC_MAX_SEG_NUM; i++)
		{
			for(j = 0; j < 8; j++)
			{
				__DBUG("pDiInfo->struSeg[%d][%d].u8Open: %d\n", i, j, pDiInfo->struSeg[i][j].u8Open);
				__DBUG("pDiInfo->struSeg[%d][%d].beginSec: %d\n", i, j, pDiInfo->struSeg[i][j].beginSec);
				__DBUG("pDiInfo->struSeg[%d][%d].endSec: %d\n", i, j, pDiInfo->struSeg[i][j].endSec);
				
			}
		}
		
		__DBUG("pDiInfo->struLinkAct.u32OutPut: %d\n",pDiInfo->struLinkAct.u32OutPut);
		__DBUG("pDiInfo->struLinkAct.u32OutPersist: %d\n",pDiInfo->struLinkAct.u32OutPersist);
		
		__DBUG("pDiInfo->struLinkAct.u32ShootChannel: %d\n",pDiInfo->struLinkAct.u32ShootChannel);
		__DBUG("pDiInfo->struLinkAct.u8ShootNum: %d\n",pDiInfo->struLinkAct.u8ShootNum);
		__DBUG("pDiInfo->struLinkAct.u8ShootMode: %d\n",pDiInfo->struLinkAct.u8ShootMode);
		__DBUG("pDiInfo->struLinkAct.u32ShootInterval: %d\n",pDiInfo->struLinkAct.u32ShootInterval);
		
		__DBUG("pDiInfo->struLinkAct.u32RecChannel: %d\n",pDiInfo->struLinkAct.u32RecChannel);
		__DBUG("pDiInfo->struLinkAct.u32RecTime: %d\n",pDiInfo->struLinkAct.u32RecTime);
		__DBUG("ppDiInfo->struLinkAct.u8RecMode: %d\n",pDiInfo->struLinkAct.u8RecMode);
		__DBUG("pDiInfo->struLinkAct.u32PCRecChannel: %d\n",pDiInfo->struLinkAct.u32PCRecChannel);
		
		__DBUG("pDiInfo->struLinkAct.u8Email: %d\n",pDiInfo->struLinkAct.u8Email);
		__DBUG("pDiInfo->u32DetectInterval: %d\n",pDiInfo->u32DetectInterval);*/

	}
	else
		__ERR("ti_param_get_di_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_DEV_DI_CFG_S) : ret);
}
static int ti_param_set_di_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_DI_CFG_S *pDiInfo = (IPNC_DEV_DI_CFG_S *)pData;
	TI_DEV_DI_CFG_S diInfo;
	int i = 0, j = 0, ret = -1;

	memset(&diInfo, 0, sizeof(TI_DEV_DI_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&diInfo, 
								sizeof(TI_DEV_DI_CFG_S), 
								TI_CMD_GET_DI_CFG);

	if((0 < ret) && (NULL != pDiInfo))
	{
		//̽ͷ����ʹ�� 0--�ر� 1--����
		diInfo.u8Enable = pDiInfo->u8Enable;
		//̽ͷ����
		nvr_string_copy(diInfo.chDiName, sizeof(diInfo.chDiName),
						pDiInfo->chDiName);
		//̽ͷ���� 0--����̽ͷ 1--����̽ͷ
		diInfo.u8DiType = pDiInfo->u8DiType;

		//̽ͷʱ��
		for(i = 0; i < IPNC_MAX_SEG_NUM; i++)
		{
			for(j = 0; j < 8; j++)
			{
				diInfo.struSeg[i][j].u8Open = pDiInfo->struSeg[i][j].u8Open;
				diInfo.struSeg[i][j].beginSec = pDiInfo->struSeg[i][j].beginSec;
				diInfo.struSeg[i][j].endSec = pDiInfo->struSeg[i][j].endSec;
			}
		}
		//�������
		diInfo.struLinkAct.u32OutPut = pDiInfo->struLinkAct.u32OutPut;
		//�����������ʱ��
		diInfo.struLinkAct.u32OutPersist = pDiInfo->struLinkAct.u32OutPersist;

		//����ץ��
		diInfo.struLinkAct.u32ShootChannel = pDiInfo->struLinkAct.u32ShootChannel;
		//ץ����
		diInfo.struLinkAct.u8ShootNum = pDiInfo->struLinkAct.u8ShootNum;
		//ץ�Ĵ洢ģʽ
		diInfo.struLinkAct.u8ShootMode = pDiInfo->struLinkAct.u8ShootMode;
		//ץ�ĳ���ʱ��
		diInfo.struLinkAct.u32ShootInterval = pDiInfo->struLinkAct.u32ShootInterval;

		//¼�����
		diInfo.struLinkAct.u32RecChannel = pDiInfo->struLinkAct.u32RecChannel;
		//¼�����ʱ��
		diInfo.struLinkAct.u32RecTime = pDiInfo->struLinkAct.u32RecTime;
		//¼��ģʽ
		diInfo.struLinkAct.u8RecMode = pDiInfo->struLinkAct.u8RecMode;
		//����PC¼��ͨ��
		diInfo.struLinkAct.u32PCRecChannel = pDiInfo->struLinkAct.u32PCRecChannel;
		
		//�����ʱ��
		diInfo.u32DetectInterval = pDiInfo->u32DetectInterval;
		/*
		__DBUG("diInfo.u8Enable: %d\n",diInfo.u8Enable);
		__DBUG("diInfo.chDiName: %s\n",diInfo.chDiName);
		__DBUG("diInfo.u8DiType: %d\n",diInfo.u8DiType);

		for(i = 0; i < IPNC_MAX_SEG_NUM; i++)
		{
			for(j = 0; j < 8; j++)
			{
				__DBUG("diInfo.struSeg[%d][%d].u8Open: %d\n", i, j, diInfo.struSeg[i][j].u8Open);
				__DBUG("diInfo.struSeg[%d][%d].beginSec: %d\n", i, j, diInfo.struSeg[i][j].beginSec);
				__DBUG("diInfo.struSeg[%d][%d].endSec: %d\n", i, j, diInfo.struSeg[i][j].endSec);
				
			}
		}
		
		__DBUG("diInfo.struLinkAct.u32OutPut: %d\n",diInfo.struLinkAct.u32OutPut);
		__DBUG("diInfo.struLinkAct.u32OutPersist: %d\n",diInfo.struLinkAct.u32OutPersist);
		
		__DBUG("diInfo.struLinkAct.u32ShootChannel: %d\n",diInfo.struLinkAct.u32ShootChannel);
		__DBUG("diInfo.struLinkAct.u8ShootNum: %d\n",diInfo.struLinkAct.u8ShootNum);
		__DBUG("diInfo.struLinkAct.u8ShootMode: %d\n",diInfo.struLinkAct.u8ShootMode);
		__DBUG("diInfo.struLinkAct.u32ShootInterval: %d\n",diInfo.struLinkAct.u32ShootInterval);
		
		__DBUG("diInfo.struLinkAct.u32RecChannel: %d\n",diInfo.struLinkAct.u32RecChannel);
		__DBUG("diInfo.struLinkAct.u32RecTime: %d\n",diInfo.struLinkAct.u32RecTime);
		__DBUG("pdiInfo.struLinkAct.u8RecMode: %d\n",diInfo.struLinkAct.u8RecMode);
		__DBUG("diInfo.struLinkAct.u32PCRecChannel: %d\n",diInfo.struLinkAct.u32PCRecChannel);
		
		__DBUG("diInfo.struLinkAct.u8Email: %d\n",diInfo.struLinkAct.u8Email);
		__DBUG("diInfo.u32DetectInterval: %d\n",diInfo.u32DetectInterval);*/

		ret = ti_send_set_param_cmd(logonHandle, 
									&diInfo, 
									sizeof(TI_DEV_DI_CFG_S), 
									TI_CMD_SET_DI_CFG);
	}
	else
		__ERR("ti_param_set_di_param faile!\n");
	
	return ret;
}
static int ti_param_check_di_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
	
	//__DBUG("dataSize: %d\n", dataSize);
	//__DBUG("sizeof(IPNC_DEV_DI_CFG_S): %d\n", sizeof(IPNC_DEV_DI_CFG_S));
	if(dataSize != sizeof(IPNC_DEV_DI_CFG_S))
		return -1;
		
	return 0;
}

/*3aͨ�ýṹ�庯��************************************************************/

static int ti_param_get_3a_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_3A_CFG_S *pDev3aInfo = (IPNC_DEV_3A_CFG_S *)pData;
	TI_DEV_3A_CFG_S dev3aInfo;
	int ret = -1;

	memset(&dev3aInfo, 0, sizeof(TI_DEV_3A_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&dev3aInfo, 
								sizeof(TI_DEV_3A_CFG_S), 
								TI_CMD_GET_3A_CFG);

	if((0 < ret) && (NULL != pDev3aInfo))
	{
		pDev3aInfo->eSuppMask = dev3aInfo.eSuppMask;
		pDev3aInfo->eSetMask = dev3aInfo.eSetMask;
		//��תͼ�����·�ת
		pDev3aInfo->struFlip.u8Default = dev3aInfo.struFlip.u8Default;
		pDev3aInfo->struFlip.u8Step = dev3aInfo.struFlip.u8Step;
		pDev3aInfo->struFlip.u8Value = dev3aInfo.struFlip.u8Value;
		//����ͼ�����ҷ�ת
		pDev3aInfo->struMirror.u8Default = dev3aInfo.struMirror.u8Default;
		pDev3aInfo->struMirror.u8Step =  dev3aInfo.struMirror.u8Step;
		pDev3aInfo->struMirror.u8Value =  dev3aInfo.struMirror.u8Value;
		//��ԴƵ��
		pDev3aInfo->struPwdFreq.u8Default = dev3aInfo.struPwdFreq.u8Default;
		pDev3aInfo->struPwdFreq.u8Step =  dev3aInfo.struPwdFreq.u8Step;
		pDev3aInfo->struPwdFreq.u8Value =  dev3aInfo.struPwdFreq.u8Value;
		//����,0:�Զ� 1:����2:����
		pDev3aInfo->struScene.u8Default = dev3aInfo.struScene.u8Default;
		pDev3aInfo->struScene.u8Step =  dev3aInfo.struScene.u8Step;
		pDev3aInfo->struScene.u8Value =  dev3aInfo.struScene.u8Value;
		//����ģʽ��0:�Զ���1:���죬2:����,3:��ʱģʽ
		//pDev3aInfo->struIrcfMode.u8Default = dev3aInfo.struIrcfMode.u8Default;
		//pDev3aInfo->struIrcfMode.u8Step =  dev3aInfo.struIrcfMode.u8Step;
		//pDev3aInfo->struIrcfMode.u8Value =  dev3aInfo.struIrcfMode.u8Value;
		//���ӿ��� 0-8  0���Զ����� 1��											
		//1/25S�� 2��1/50S�� 3��1/100S�� 4��1/500S�� 5��1/1000S�� 											
		//6��1/2000S�� 7��1/5000S�� 8��1/10000S
		pDev3aInfo->struShutterSpeed.u8Default = dev3aInfo.struShutterSpeed.u8Default;
		pDev3aInfo->struShutterSpeed.u8Step =  dev3aInfo.struShutterSpeed.u8Step;
		pDev3aInfo->struShutterSpeed.u8Value =  dev3aInfo.struShutterSpeed.u8Value;
		/*
		__DBUG("dev3aInfo.eSetMask:%#x\n", dev3aInfo.eSetMask);
		__DBUG("dev3aInfo.eSuppMask:%#x\n", dev3aInfo.eSuppMask);
		__DBUG("dev3aInfo.struFlip.u8Default:%d\n", dev3aInfo.struFlip.u8Default);
		__DBUG("dev3aInfo.struFlip.u8Value:%d\n", dev3aInfo.struFlip.u8Value);
		__DBUG("dev3aInfo.struMirror.u8Default:%d\n", dev3aInfo.struMirror.u8Default);
		__DBUG("dev3aInfo.struMirror.u8Value:%d\n", dev3aInfo.struMirror.u8Value);
		__DBUG("dev3aInfo.struPwdFreq.u8Default:%d\n", dev3aInfo.struPwdFreq.u8Default);
		__DBUG("dev3aInfo.struPwdFreq.u8Value:%d\n", dev3aInfo.struPwdFreq.u8Value);
		__DBUG("dev3aInfo.struScene.u8Default:%d\n", dev3aInfo.struScene.u8Default);
		__DBUG("dev3aInfo.struScene.u8Value:%d\n", dev3aInfo.struScene.u8Value);
		__DBUG("dev3aInfo.struIrcfMode.u8Default:%d\n", dev3aInfo.struIrcfMode.u8Default);
		__DBUG("dev3aInfo.struIrcfMode.u8Value:%d\n", dev3aInfo.struIrcfMode.u8Value);
		__DBUG("dev3aInfo.struShutterSpeed.u8Default:%d\n", dev3aInfo.struShutterSpeed.u8Default);
		__DBUG("dev3aInfo.struShutterSpeed.u8Value:%d\n", dev3aInfo.struShutterSpeed.u8Value);
		*/
	}
	else
		__ERR("ti_param_get_3a_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_DEV_3A_CFG_S) : ret);
}
static int ti_param_set_3a_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_3A_CFG_S *pDev3aInfo = (IPNC_DEV_3A_CFG_S *)pData;
	TI_DEV_3A_CFG_S dev3aInfo;
	int ret = -1;

	memset(&dev3aInfo, 0, sizeof(TI_DEV_3A_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&dev3aInfo, 
								sizeof(TI_DEV_3A_CFG_S), 
								TI_CMD_GET_3A_CFG);

	if((0 < ret) && (NULL != pDev3aInfo))
	{
		dev3aInfo.eSuppMask = pDev3aInfo->eSuppMask;
		dev3aInfo.eSetMask = pDev3aInfo->eSetMask;
		//��תͼ�����·�ת
		//dev3aInfo.struFlip.u8Default = pDev3aInfo->struFlip.u8Default;
		//dev3aInfo.struFlip.u8Step = pDev3aInfo->struFlip.u8Step;
		dev3aInfo.struFlip.u8Value = pDev3aInfo->struFlip.u8Value;
		//����ͼ�����ҷ�ת
		//dev3aInfo.struMirror.u8Default = pDev3aInfo->struMirror.u8Default;
		//dev3aInfo.struMirror.u8Step =  pDev3aInfo->struMirror.u8Step;
		dev3aInfo.struMirror.u8Value =  pDev3aInfo->struMirror.u8Value;
		//��ԴƵ��
		//dev3aInfo.struPwdFreq.u8Default = pDev3aInfo->struPwdFreq.u8Default;
		//dev3aInfo.struPwdFreq.u8Step =  pDev3aInfo->struPwdFreq.u8Step;
		dev3aInfo.struPwdFreq.u8Value =  pDev3aInfo->struPwdFreq.u8Value;
		//����,0:�Զ� 1:����2:����
		//dev3aInfo.struScene.u8Default = pDev3aInfo->struScene.u8Default;
		//dev3aInfo.struScene.u8Step =  pDev3aInfo->struScene.u8Step;
		dev3aInfo.struScene.u8Value =  pDev3aInfo->struScene.u8Value;
		//����ģʽ��0:�Զ���1:���죬2:����,3:��ʱģʽ
		//dev3aInfo.struIrcfMode.u8Default = pDev3aInfo->struIrcfMode.u8Default;
		//dev3aInfo.struIrcfMode.u8Step =  pDev3aInfo->struIrcfMode.u8Step;
		//dev3aInfo.struIrcfMode.u8Value =  pDev3aInfo->struIrcfMode.u8Value;
		//���ӿ��� 0-8  0���Զ����� 1��											
		//1/25S�� 2��1/50S�� 3��1/100S�� 4��1/500S�� 5��1/1000S�� 											
		//6��1/2000S�� 7��1/5000S�� 8��1/10000S
		//dev3aInfo.struShutterSpeed.u8Default = pDev3aInfo->struShutterSpeed.u8Default;
		//dev3aInfo.struShutterSpeed.u8Step =  pDev3aInfo->struShutterSpeed.u8Step;
		dev3aInfo.struShutterSpeed.u8Value =  pDev3aInfo->struShutterSpeed.u8Value;
		/*__DBUG("dev3aInfo.eSetMask:%#x\n", dev3aInfo.eSetMask);
		__DBUG("dev3aInfo.eSuppMask:%#x\n", dev3aInfo.eSuppMask);
		__DBUG("dev3aInfo.struFlip.u8Default:%d\n", dev3aInfo.struFlip.u8Default);
		__DBUG("dev3aInfo.struFlip.u8Value:%d\n", dev3aInfo.struFlip.u8Value);
		__DBUG("dev3aInfo.struMirror.u8Default:%d\n", dev3aInfo.struMirror.u8Default);
		__DBUG("dev3aInfo.struMirror.u8Value:%d\n", dev3aInfo.struMirror.u8Value);
		__DBUG("dev3aInfo.struPwdFreq.u8Default:%d\n", dev3aInfo.struPwdFreq.u8Default);
		__DBUG("dev3aInfo.struPwdFreq.u8Value:%d\n", dev3aInfo.struPwdFreq.u8Value);
		__DBUG("dev3aInfo.struScene.u8Default:%d\n", dev3aInfo.struScene.u8Default);
		__DBUG("dev3aInfo.struScene.u8Value:%d\n", dev3aInfo.struScene.u8Value);
		__DBUG("dev3aInfo.struIrcfMode.u8Default:%d\n", dev3aInfo.struIrcfMode.u8Default);
		__DBUG("dev3aInfo.struIrcfMode.u8Value:%d\n", dev3aInfo.struIrcfMode.u8Value);
		__DBUG("dev3aInfo.struShutterSpeed.u8Default:%d\n", dev3aInfo.struShutterSpeed.u8Default);
		__DBUG("dev3aInfo.struShutterSpeed.u8Value:%d\n", dev3aInfo.struShutterSpeed.u8Value);
		*/
		//����
		ret = ti_send_set_param_cmd(logonHandle, 
									&dev3aInfo, 
									sizeof(TI_DEV_3A_CFG_S), 
									TI_CMD_SET_3A_CFG);
		
	}
	else
		__ERR("ti_param_set_3a_param faile!\n");
	
	return ret;
}
static int ti_param_check_3a_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
		
	__DBUG("dataSize: %d\n", dataSize);
	__DBUG("sizeof(IPNC_DEV_3A_CFG_S): %d\n", sizeof(IPNC_DEV_3A_CFG_S));
	if(dataSize != sizeof(IPNC_DEV_3A_CFG_S))
		return -1;
		
	return 0;
}

/*IRCFMODE����ͨ�ýṹ�庯��************************************************************/
static int ti_param_get_ircfmode_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_IRCFMODE_CFG_S *pIrInfo = (IPNC_DEV_IRCFMODE_CFG_S *)pData;
	TI_DEV_IRCFMODE_CFG_S irInfo;
	TI_DEV_3A_CFG_S dev3aInfo;
	int ret = -1;
	int i = 0, j = 0;

	memset(&dev3aInfo, 0, sizeof(TI_DEV_3A_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&dev3aInfo, 
								sizeof(TI_DEV_3A_CFG_S), 
								TI_CMD_GET_3A_CFG);
								
	memset(&irInfo, 0, sizeof(TI_DEV_IRCFMODE_CFG_S));
	ret |= ti_send_get_param_cmd(logonHandle, 
								&irInfo, 
								sizeof(TI_DEV_IRCFMODE_CFG_S), 
								TI_CMD_GET_IRCFMODE_CFG);

	if((0 < ret) && (NULL != pIrInfo))
	{
		pIrInfo->u8Mode = dev3aInfo.struIrcfMode.u8Value;
		for(i = 0; i < IPNC_MAX_IRCF_SEG_NUM; i++)
		{
			for(j = 0; j < 8; j++)
			{
				pIrInfo->struSeg[i][j].u8Open = irInfo.struSeg[i][j].u8Open;
				pIrInfo->struSeg[i][j].beginSec = irInfo.struSeg[i][j].beginSec;
				pIrInfo->struSeg[i][j].endSec = irInfo.struSeg[i][j].endSec;
			}
		}

		/*__DBUG("pIrInfo->u8DiType: %d\n",pIrInfo->u8Enable);
		for(i = 0; i < IPNC_MAX_IRCF_SEG_NUM; i++)
		{
			for(j = 0; j < 8; j++)
			{
				__DBUG("pIrInfo->struSeg[%d][%d].u8Open: %d\n", i, j,pIrInfo->struSeg[i][j].u8Open);
				__DBUG("pIrInfo->struSeg[%d][%d].beginSec: %d\n", i, j, pIrInfo->struSeg[i][j].beginSec);
				__DBUG("pIrInfo->struSeg[%d][%d].endSec: %d\n", i, j, pIrInfo->struSeg[i][j].endSec);
			}
		}*/
	}
	else
		__ERR("ti_param_get_ircfmode_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_DEV_IRCFMODE_CFG_S) : ret);
}
static int ti_param_set_ircfmode_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_IRCFMODE_CFG_S *pIrInfo = (IPNC_DEV_IRCFMODE_CFG_S *)pData;
	TI_DEV_IRCFMODE_CFG_S irInfo;
	TI_DEV_3A_CFG_S dev3aInfo;
	int ret = -1;
	int i = 0, j = 0;

	memset(&dev3aInfo, 0, sizeof(TI_DEV_3A_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&dev3aInfo, 
								sizeof(TI_DEV_3A_CFG_S), 
								TI_CMD_GET_3A_CFG);
	//dev3aInfo.eSetMask = VCT_3A_IRCFMODE;
	dev3aInfo.struIrcfMode.u8Value = pIrInfo->u8Mode;
	if(0 < ret)
	{
		ret = ti_send_set_param_cmd(logonHandle, 
								&dev3aInfo, 
								sizeof(TI_DEV_3A_CFG_S), 
								TI_CMD_SET_3A_CFG);
	}

	if(pIrInfo->u8Mode == 3)
	{
		memset(&irInfo, 0, sizeof(TI_DEV_IRCFMODE_CFG_S));
		ret = ti_send_get_param_cmd(logonHandle, 
									&irInfo, 
									sizeof(TI_DEV_IRCFMODE_CFG_S), 
									TI_CMD_GET_IRCFMODE_CFG);
		if(0 < ret)
		{
			//irInfo.u8Enable = (pIrInfo->u8Mode == 3) ? 1:0;
			for(i = 0; i < IPNC_MAX_IRCF_SEG_NUM; i++)
			{
				for(j = 0; j < 8; j++)
				{
					irInfo.struSeg[i][j].u8Open = pIrInfo->struSeg[i][j].u8Open;
					irInfo.struSeg[i][j].beginSec = pIrInfo->struSeg[i][j].beginSec;
					irInfo.struSeg[i][j].endSec = pIrInfo->struSeg[i][j].endSec;
				}
			}

			//����
			ret = ti_send_set_param_cmd(logonHandle, 
									&irInfo, 
									sizeof(TI_DEV_IRCFMODE_CFG_S), 
									TI_CMD_SET_IRCFMODE_CFG);
		}
	}
	return ret;
}
static int ti_param_check_ircfmode_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
		
	if(dataSize != sizeof(IPNC_DEV_IRCFMODE_CFG_S))
		return -1;
	
	return 0;
}

/*ballͨ�ýṹ�庯��************************************************************/

static int ti_param_get_ball_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_BALL_RUN_PARAM_S *pBallInfo = (IPNC_BALL_RUN_PARAM_S *)pData;
	TI_BALL_RUN_PARAM_S ballInfo;
	int ret = -1;
	
	memset(&ballInfo, 0, sizeof(TI_BALL_RUN_PARAM_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&ballInfo, 
								sizeof(TI_BALL_RUN_PARAM_S), 
								TI_CMD_GET_BALL_CFG);

	if((0 < ret) && (NULL != pBallInfo))
	{
		memcpy(pBallInfo, &ballInfo, sizeof(IPNC_BALL_RUN_PARAM_S));
	}
	else
		__ERR("ti_param_get_ball_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_BALL_RUN_PARAM_S) : ret);
}
static int ti_param_set_ball_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{

	IPNC_BALL_RUN_PARAM_S *pBallInfo = (IPNC_BALL_RUN_PARAM_S *)pData;
	TI_BALL_RUN_PARAM_S ballInfo;
	int ret = -1;
	
	memset(&ballInfo, 0, sizeof(TI_BALL_RUN_PARAM_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&ballInfo, 
								sizeof(TI_BALL_RUN_PARAM_S), 
								TI_CMD_GET_BALL_CFG);

	if((0 < ret) && (NULL != pBallInfo))
	{
		memcpy(&ballInfo, pBallInfo, sizeof(TI_BALL_RUN_PARAM_S));

		//����
		ret = ti_send_set_param_cmd(logonHandle, 
								&ballInfo, 
								sizeof(TI_BALL_RUN_PARAM_S), 
								TI_CMD_SET_BALL_CFG);
	}
	else
		__ERR("ti_param_set_ball_param faile!\n");
	
	return ret;
}
static int ti_param_check_ball_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
		
	if((dataSize != sizeof(IPNC_BALL_RUN_PARAM_S)) &&
	   (sizeof(IPNC_BALL_RUN_PARAM_S) != sizeof(TI_BALL_RUN_PARAM_S)))
		return -1;
	
	return 0;
}

/*ppͨ�ýṹ�庯��************************************************************/

static int ti_param_get_pp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_PP_SET_CFG_S *pPpInfo = (IPNC_DEV_PP_SET_CFG_S *)pData;
	TI_DEV_PP_SET_CFG_S ppInfo;
	int ret = -1;
	
	memset(&ppInfo, 0, sizeof(TI_DEV_PP_SET_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&ppInfo, 
								sizeof(TI_DEV_PP_SET_CFG_S), 
								TI_CMD_GET_PP_SET_CFG);

	if((0 < ret) && (NULL != pPpInfo))
	{
		memcpy(pPpInfo, &ppInfo, sizeof(IPNC_DEV_PP_SET_CFG_S));
	}
	else
		__ERR("ti_param_get_pp_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_DEV_PP_SET_CFG_S) : ret);
}
static int ti_param_set_pp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_PP_SET_CFG_S *pPpInfo = (IPNC_DEV_PP_SET_CFG_S *)pData;
	TI_DEV_PP_SET_CFG_S ppInfo;
	int ret = -1;
	
	memset(&ppInfo, 0, sizeof(TI_DEV_PP_SET_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&ppInfo, 
								sizeof(TI_DEV_PP_SET_CFG_S), 
								TI_CMD_GET_PP_SET_CFG);

	if((0 < ret) && (NULL != pPpInfo))
	{
		memcpy(&ppInfo, pPpInfo, sizeof(TI_DEV_PP_SET_CFG_S));
		//����
		ret = ti_send_set_param_cmd(logonHandle, 
								&ppInfo, 
								sizeof(TI_DEV_PP_SET_CFG_S), 
								TI_CMD_SET_PP_SET_CFG);
	}
	else
		__ERR("ti_param_set_pp_param faile!\n");
	
	return ret;
}
static int ti_param_check_pp_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
		
	if((dataSize != sizeof(IPNC_DEV_PP_SET_CFG_S)) &&
	   (sizeof(IPNC_DEV_PP_SET_CFG_S) != sizeof(TI_DEV_PP_SET_CFG_S)))
		return -1;
	
	return 0;
}
/*timeͨ�ýṹ�庯��************************************************************/
static int ti_param_get_time_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_TIME_S *pTimeInfo = (IPNC_TIME_S *)pData;
	TI_TIME_S timeInfo;
	int ret = -1;
	
	memset(&timeInfo, 0, sizeof(TI_TIME_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&timeInfo, 
								sizeof(TI_TIME_S), 
								TI_CMD_GET_TIME_CFG);

	if((0 < ret) && (NULL != pTimeInfo))
	{
		memcpy(pTimeInfo, &timeInfo, sizeof(IPNC_TIME_S));
	}
	else
		__ERR("ti_param_get_time_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_TIME_S) : ret);
}
static int ti_param_set_time_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_TIME_S *pTimeInfo = (IPNC_TIME_S *)pData;
	TI_TIME_S timeInfo;
	int ret = -1;
	
	memset(&timeInfo, 0, sizeof(TI_TIME_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&timeInfo, 
								sizeof(TI_TIME_S), 
								TI_CMD_GET_TIME_CFG);

	if((0 < ret) && (NULL != pTimeInfo))
	{
		memcpy(&timeInfo, pTimeInfo, sizeof(IPNC_TIME_S));
		//����
		ret = ti_send_set_param_cmd(logonHandle, 
								&timeInfo, 
								sizeof(TI_TIME_S), 
								TI_CMD_SET_TIME_CFG);

		//__ERR("ti_param_set_time_param end!\n");
	}
	else
		__ERR("ti_param_set_time_param faile!\n");

	
	
	return ret;

}
static int ti_param_check_time_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
		
	if(dataSize != sizeof(IPNC_TIME_S))
		return -1;
	
	return 0;
}

/*osd_lableͨ�ýṹ�庯��************************************************************/
static int ti_param_get_osd_lable_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_OSD_LABEL_CFG_S *pOsdLable = (IPNC_DEV_OSD_LABEL_CFG_S *)pData;
	TI_DEV_OSD_LABEL_CFG_S osdInfo;
	int ret = -1;
	
	memset(&osdInfo, 0, sizeof(TI_DEV_OSD_LABEL_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&osdInfo, 
								sizeof(TI_DEV_OSD_LABEL_CFG_S), 
								TI_CMD_GET_OSD_LABEL_CFG);

	if((0 < ret) && (NULL != pOsdLable))
	{
		memcpy(pOsdLable, &osdInfo, sizeof(IPNC_DEV_OSD_LABEL_CFG_S));
	}
	else
		__ERR("ti_param_get_osd_lable_param faile!\n");

	return ((ret > 0) ? sizeof(IPNC_DEV_OSD_LABEL_CFG_S) : ret);
	
	
}
static int ti_param_set_osd_lable_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	IPNC_DEV_OSD_LABEL_CFG_S *pOsdLable = (IPNC_DEV_OSD_LABEL_CFG_S *)pData;
	TI_DEV_OSD_LABEL_CFG_S osdInfo;
	int ret = -1;
	
	memset(&osdInfo, 0, sizeof(TI_DEV_OSD_LABEL_CFG_S));
	ret = ti_send_get_param_cmd(logonHandle, 
								&osdInfo, 
								sizeof(TI_DEV_OSD_LABEL_CFG_S), 
								TI_CMD_GET_OSD_LABEL_CFG);

	if((0 < ret) && (NULL != pOsdLable))
	{
		memcpy(&osdInfo, pOsdLable, sizeof(TI_DEV_OSD_LABEL_CFG_S));
		//����
		ret = ti_send_set_param_cmd(logonHandle, 
								&osdInfo, 
								sizeof(TI_DEV_OSD_LABEL_CFG_S), 
								TI_CMD_SET_OSD_LABEL_CFG);
	}
	else
		__ERR("ti_param_set_osd_lable_param faile!\n");

	return ret;
}
static int ti_param_check_osd_lable_param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
		
	if(dataSize != sizeof(IPNC_DEV_OSD_LABEL_CFG_S))
		return -1;
	
	return 0;
}
static int ti_param_set_reboot(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	return ti_send_set_param_cmd(logonHandle, NULL, 0, TI_CMD_RESTART_DEV);
}
static int ti_param_set_halt(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	return 0;
}
static int ti_param_set_default(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	return ti_send_set_param_cmd(logonHandle, NULL, 0, TI_CMD_RESET_DEV);
}

/*ͨ�ýṹ�庯��************************************************************/
/*
static int ti_param_get__param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	return 0;
}
static int ti_param_set__param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	int ret = -1;
	
	return ret;
}
static int ti_param_check__param(long logonHandle, int nPort, void *pData, uint32_t dataSize)
{
	if(NULL == pData)
		return -1;
		
	if(dataSize != sizeof(IPNC_DEV_IRCFMODE_CFG_S))
		return -1;
	
	return 0;
}
*/

//�ṹ�����������
static TI_NET_CMD_PARAM_S sCmdParam[] =
{  
	{IPNC_CMD_DEV_CFG, -1,	/*�豸��Ϣ����*/
		ti_param_get_dev_param,		
		ti_param_set_dev_param,
		ti_param_check_dev_param},
		
	{IPNC_CMD_NET_CFG, -1,	/*�豸��������*/
		ti_param_get_net_param,		
		ti_param_set_net_param,
		ti_param_check_net_param},

	{IPNC_CMD_FTP_CFG, -1,	/*�豸ftp����*/
		ti_param_get_ftp_param,		
		ti_param_set_ftp_param,
		ti_param_check_ftp_param},

	{IPNC_CMD_EMAIL_CFG, -1,/*�豸smtp����*/
		ti_param_get_smtp_param,		
		ti_param_set_smtp_param,
		ti_param_check_smtp_param},

	{IPNC_CMD_NTP_CFG, -1,/*�豸ntp����*/
		ti_param_get_ntp_param,		
		ti_param_set_ntp_param,
		ti_param_check_ntp_param},

	{IPNC_CMD_UPNP_CFG, -1,/*�豸upnp����*/
		ti_param_get_upnp_param,		
		ti_param_set_upnp_param,
		ti_param_check_upnp_param},

	{IPNC_CMD_DDNS_CFG, -1,/*�豸ddns����*/
		ti_param_get_ddns_param,		
		ti_param_set_ddns_param,
		ti_param_check_ddns_param},

	{IPNC_CMD_COMM_CFG, -1,/*�豸comm����*/
		ti_param_get_comm_param,		
		ti_param_set_comm_param,
		ti_param_check_comm_param},

	{IPNC_CMD_PPPOE_CFG, -1,/*�豸pppoe����*/
		ti_param_get_pppoe_param,		
		ti_param_set_pppoe_param,
		ti_param_check_pppoe_param},

	{IPNC_CMD_PTZ_CFG, -1,/*�豸ptz����*/
		ti_param_get_ptz_param,		
		ti_param_set_ptz_param,
		ti_param_check_ptz_param},

	{IPNC_CMD_AUDIO_CFG, -1,/*�豸audio����*/
		ti_param_get_audio_param,		
		ti_param_set_audio_param,
		ti_param_check_audio_param},

	{IPNC_CMD_USR_CFG, -1,/*�豸user����*/
		ti_param_get_user_param,		
		ti_param_set_user_param,
		ti_param_check_user_param},

	{IPNC_CMD_OSD_CFG, -1,/*�豸osd����*/
		ti_param_get_osd_param,		
		ti_param_set_osd_param,
		ti_param_check_osd_param},

	{IPNC_CMD_VMASK_CFG, -1,/*�豸vmask����*/
		ti_param_get_vmask_param,		
		ti_param_set_vmask_param,
		ti_param_check_vmask_param},
		
	{IPNC_CMD_VMAIN_CFG, -1,/*�豸vmain����*/
		ti_param_get_vmain_param,		
		ti_param_set_vmain_param,
		ti_param_check_vmain_param},

	{IPNC_CMD_VSUB_CFG, -1,/*�豸vsub����*/
		ti_param_get_vsub_param,		
		ti_param_set_vsub_param,
		ti_param_check_vsub_param},

	{IPNC_CMD_VCAP_CFG, -1,/*�豸vcap����*/
		ti_param_get_vcap_param,		
		ti_param_set_vcap_param,
		ti_param_check_vcap_param},
	
	{IPNC_CMD_VIDEO_CFG, -1,/*�豸video����*/
		ti_param_get_video_param,		
		ti_param_set_video_param,
		ti_param_check_video_param},

	{IPNC_CMD_IMA_CFG, -1,/*�豸ima����*/
		ti_param_get_ima_param,		
		ti_param_set_ima_param,
		ti_param_check_ima_param},

	{IPNC_CMD_VMD_CFG, -1,/*�豸md�ƶ��������*/
		ti_param_get_md_param,		
		ti_param_set_md_param,
		ti_param_check_md_param},

	{IPNC_CMD_DI_CFG, -1,/*�豸di̽ͷ��������*/
		ti_param_get_di_param,		
		ti_param_set_di_param,
		ti_param_check_di_param},

	{IPNC_CMD_3A_CFG, -1,/*�豸3a����*/
		ti_param_get_3a_param,		
		ti_param_set_3a_param,
		ti_param_check_3a_param},

	{IPNC_CMD_IRCFMODE_CFG, -1,/*�豸��������*/
		ti_param_get_ircfmode_param,		
		ti_param_set_ircfmode_param,
		ti_param_check_ircfmode_param},

	{IPNC_CMD_BALL_CFG, -1,/*�豸����������*/
			ti_param_get_ball_param,		
			ti_param_set_ball_param,
			ti_param_check_ball_param},
			
	{IPNC_CMD_PP_CFG, -1,/*�豸Ԥ�õ�PP����*/
			ti_param_get_pp_param,		
			ti_param_set_pp_param,
			ti_param_check_pp_param},
	{IPNC_CMD_TIME_CFG, -1,/*�豸TIME����*/
			ti_param_get_time_param,		
			ti_param_set_time_param,
			ti_param_check_time_param},

	{IPNC_CMD_OSD_LABEL_CFG, -1,/*�豸OSD LABEL����*/
			ti_param_get_osd_lable_param,		
			ti_param_set_osd_lable_param,
			ti_param_check_osd_lable_param},
			
	{IPNC_CMD_REBOOT, -1,
			NULL, 
			ti_param_set_reboot,
			NULL},
			
	{IPNC_CMD_HALT, -1,
			NULL, 
			ti_param_set_halt,
			NULL},
			
	{IPNC_CMD_DEFAULT, -1,
			NULL, 
			ti_param_set_default,
			NULL},
	//��β
	{0,-1,NULL,NULL,NULL},
};

/*���ݽṹ��С,������Ӧ�ṹ����������.
�ɹ����ز������������,
ʧ�ܷ��ؿ�.
*/
long ti_net_param_cmd(IPNC_CMD_TYPE_E paramCmd)
{
	int i = 0;
	for(i = 0; 
		(sCmdParam[i].paramCmd != 0) &&
			((sCmdParam[i].getParamProc != NULL) || (sCmdParam[i].setParamProc != NULL));
		i++)
	{
		if(paramCmd == sCmdParam[i].paramCmd)
			return (long)&sCmdParam[i];
	}

	return (long)NULL;
}

/*�������ò�������:
	�ɹ����ؽ��մ�С*/
int ti_send_set_param_cmd(long handle, void* pParam, TI_U32 u32PackLen, TI_U32 u32PackCmd)
{	
	TI_LOGON_USER_INFO *userInfo = (TI_LOGON_USER_INFO *)handle;
	char sendBuf[2048]  = {0};
	char recvBuff[2048];
	int ret;
	TI_NET_HDR_S *pNetHdr = (TI_NET_HDR_S *)recvBuff;
	
	if(NULL == userInfo)
		return TI_FAILURE;
	
	//if(pParam == NULL)
	//{
	//	__ERR("parameter is NULL !\r\n");
	//	return TI_FAILURE;
	//}
	
	/*��ʼ����ͷ����������*/
	net_set_net_hdr((TI_NET_HDR_S *)sendBuf, u32PackLen, u32PackCmd, 0, 0);
	if(pParam != NULL && u32PackLen > 0)
		memcpy(sendBuf + sizeof(TI_NET_HDR_S), pParam, u32PackLen);

	
	/*���Ͳ�������*/
	ret = ti_logon_pipe_session(userInfo, sendBuf, sizeof(TI_NET_HDR_S)+u32PackLen,
									recvBuff, sizeof(recvBuff));
	if(ret < TI_NET_HDR_LEN)
	{
		__ERR("send parameter command failed:%d !\r\n", ret);
		return TI_FAILURE;
	}
	
	return pNetHdr->s32ErrNo;
}

/*���ͻ�ȡ��������:
	�ɹ����ؽ��մ�С*/
int ti_send_get_param_cmd(long handle, void* pParam, TI_U32 u32PackLen, TI_U32 u32PackCmd)
{	
	TI_LOGON_USER_INFO *userInfo = (TI_LOGON_USER_INFO *)handle;
	char sendBuf[2048] = {0};
	char recvBuff[2048];
	int ret;
	TI_NET_HDR_S *pNetHdr = (TI_NET_HDR_S *)recvBuff;
	void *pData = pNetHdr + 1;
	
	if(NULL == userInfo)
		return TI_FAILURE;
	
	net_set_net_hdr((TI_NET_HDR_S *)sendBuf, 0, u32PackCmd, 0, 0);
	
	/*���Ͳ�������*/
	ret = ti_logon_pipe_session(userInfo, sendBuf, sizeof(TI_NET_HDR_S),
									recvBuff, sizeof(recvBuff));
	if(0 > ret)
	{
		__ERR("send parameter command failed:%d !\r\n", ret);
		return TI_FAILURE;
	}
	if(ret != TI_NET_HDR_LEN + pNetHdr->u32PacketSize)
	{
		__ERR("The recv lenght is wrong.\n");
		return TI_FAILURE;
	}
	if(pNetHdr->s32ErrNo < 0)
	{
		__ERR("Get param response error.\n");
		return TI_FAILURE;
	}
	//__DBUG("   pNetHdr->u16CmdType: %x\n",pNetHdr->u16CmdType);
	//__DBUG("            u32PackLen: %d\n",u32PackLen);
	//__DBUG("pNetHdr->u32PacketSize: %d\n",pNetHdr->u32PacketSize);
	
	if(pNetHdr->u32PacketSize <= u32PackLen)
		memcpy(pParam, pData, pNetHdr->u32PacketSize);
	else
		return TI_FAILURE;
	
	return pNetHdr->u32PacketSize;
}

//test
int ti_param_get_net(long handle)
{
	if((long)NULL == handle)
		return TI_FAILURE;

	int socket = -1;
	TI_DEV_NET_CFG_S DevNet;
	memset(&DevNet, 0, sizeof(TI_DEV_NET_CFG_S));
	socket = (int)(*(int*)handle);
	
	if(0 > ti_send_get_param_cmd(handle, &DevNet, sizeof(TI_DEV_NET_CFG_S), TI_CMD_GET_NET_CFG))
		__ERR("socket:%d ,send parameter command Failed!\n", socket);
	if(0 == DevNet.u16NetPort)
		printf("socket:%d ,ti_param_get_net failed?????????????????????????????????\n", socket);
	else
		printf("############ socket:%d , NetPort:%d\r\n", socket, DevNet.u16NetPort);
	 
	return TI_SUCCESS;
}
int ti_param_get_net_ball(long handle)
{
	if((long)NULL == handle)
		return TI_FAILURE;
	
	int socket = -1;
	TI_BALL_RUN_PARAM_S ballNet;
	socket = (int)(*(int*)handle);

	memset(&ballNet, 0, sizeof(TI_BALL_RUN_PARAM_S));
	
	if(0 > ti_send_get_param_cmd(handle, &ballNet, sizeof(TI_BALL_RUN_PARAM_S), TI_CMD_GET_BALL_CFG))
		__ERR("socket:%d ,send parameter command Failed!\n", socket);
	if(0 == ballNet.dwSize)
		printf("socket:%d ,ti_param_get_net_ball failed!!!!!!!!!!!!!!!!!!!!!!!!\n", socket);
	else
		printf("############socket:%d , dwSize:%d\n", socket,ballNet.dwSize);
	 
	return TI_SUCCESS;
}


