#ifndef __NVR_NET_INTERFACE_H__
#define __NVR_NET_INTERFACE_H__


#define NVR_NET_VERSION	 		0x0100
#define NVR_NET_MAGIC_FLAG	 	0x30404891
#define NVR_NET_MAX_MSG_LEN 	0x1000
#define NVR_NET_STREAM_DATA_LEN	1360
#define NVR_NET_RECV_TIMEOUT	3000
#define NVR_NET_SEND_TIMEOUT	3000

typedef enum _NVR_NET_ERR_CODE_E_
{
	NVR_NET_ERR_SUCCESS   			= 0,
	NVR_NET_ERR_USER_NO_EXIST		= -1,	
	NVR_NET_ERR_PASSWORD 			= -2,
	NVR_NET_ERR_NO_PERMIT			= -3,
	NVR_NET_ERR_NO_INIT				= -4,
	NVR_NET_ERR_CHANNEL				= -5,
	NVR_NET_ERR_OVER_MAX_LINK		= -6,
	NVR_NET_ERR_VERSION_NO_MATCH	= -7,
	NVR_NET_ERR_CREATE_SOCKET		= -8,
	NVR_NET_ERR_SET_SOCKET			= -9,
	NVR_NET_ERR_LISTEN_FAIL			= -10,
	NVR_NET_ERR_BIND_FAIL			= -11,
	NVR_NET_ERR_CONNECT_FAIL 		= -12, 
	NVR_NET_ERR_SEND_FAIL			= -13,
	NVR_NET_ERR_RECV_FAIL			= -14,
	NVR_NET_ERR_RECV_TIME_OUT	 	= -15,	
	NVR_NET_ERR_ORDER_ERR	 		= -16,
	NVR_NET_ERR_PARAMETER			= -17,
	NVR_NET_ERR_NO_DISK				= -18,
	NVR_NET_ERR_DISK_NUM			= -19,
	NVR_NET_ERR_DISK_FULL			= -20,
	NVR_NET_ERR_DISK_ERR			= -21,
	NVR_NET_ERR_NO_SUPPORT			= -22,
	NVR_NET_ERR_DEV_BUSY			= -23,
	NVR_NET_ERR_MODIFY_FAIL			= -24,
	NVR_NET_ERR_DISK_FORMATING		= -25,
	NVR_NET_ERR_NO_RESOURCE			= -26,
	NVR_NET_ERR_OPERATE_FAIL		= -27,
	NVR_NET_ERR_VOICE_OPEN			= -28,
	NVR_NET_ERR_INPUT_TIME_ERR		= -29,
	NVR_NET_ERR_NO_FILE				= -30,
	NVR_NET_ERR_FILE				= -31,
	NVR_NET_ERR_ALLOC_RESOURCE		= -32,
	NVR_NET_ERR_WRITE_FLASH			= -33,
	NVR_NET_ERR_PROTACAL			= -34,
	NVR_NET_ERR_MANULE_STOP			= -35,
	NVR_NET_ERR_DATA_FORMAT			= -36,
	NVR_NET_ERR_DATA_SIZE			= -37,//��������ݳ���
	NVR_NET_ERR_NO_MORE_FILE		= -38,//û�и����ļ� ���ҽ���
	NVR_NET_ERR_IS_FINDING			= -39,//���ڲ���	
	NVR_NET_ERR_KEEP_ALIVE			= -40
}NVR_NET_ERR_CODE_E;

typedef enum _NVR_NET_CMD_TYPE_E_
{
/*******************************************/
	NVR_CMD_LOGON_SERVER	= 0x1001,//��¼������
	NVR_CMD_LOGOFF_SERVER	= 0x1002,//ע��
	NVR_CMD_OPEN_PREVIEW	= 0x1003,
	NVR_CMD_CLOSE_PREVIEW	= 0x1004,
	NVR_CMD_REQUEST_I_FRAME	= 0x1005,//ǿ��I֡
	NVR_CMD_RESTART_SERVER	= 0x1006,//����ϵͳ
	NVR_CMD_SHUTDOWN_SERVER	= 0x1007,//�ر�ϵͳ
	NVR_CMD_SW_RESET_SERVER	= 0x1008,//�ָ�����
	NVR_CMD_SET_HWGPIO_CHECK	= 0x1009,//����Ӳ����λ��⿪��
/*******************************************/

/******������ȡ��������***********/	
	NVR_CMD_GET_DEV_INFO	= 0x2000,		//��ȡ�豸ϵͳ����
	NVR_CMD_SET_DEV_INFO	= 0x2001,		//�����豸ϵͳ����
	NVR_CMD_GET_VAR_CFG   	= 0x2002,       //��ȡ��̬�豸��Ϣ
	NVR_CMD_SET_VAR_CFG		= 0x2003,       //���ö�̬�豸��Ϣ
	NVR_CMD_GET_STABLE_CFG  = 0x2004,       //��ȡ�豸��Ϣ
	NVR_CMD_SET_STABLE_CFG	= 0x2005,       //�����豸��Ϣ
	NVR_CMD_GET_NET_CFG		= 0x2006,		//��ȡ�豸��������
	NVR_CMD_SET_NET_CFG		= 0x2007,		//�����豸��������
	NVR_CMD_GET_FTP_CFG		= 0x2008,		//��ȡftp��������
	NVR_CMD_SET_FTP_CFG		= 0x2009,		//����ftp��������
	NVR_CMD_GET_EMAIL_CFG	= 0x200A,		//��ȡemail��������
	NVR_CMD_SET_EMAIL_CFG	= 0x200B,		//����email��������
	NVR_CMD_GET_DDNS_CFG	= 0x200C,		//��ȡddns��������
	NVR_CMD_SET_DDNS_CFG	= 0x200D,		//����ddns��������
	NVR_CMD_GET_UPNP_CFG	= 0x200E,		//��ȡupnp��������
	NVR_CMD_SET_UPNP_CFG	= 0x200F,		//����upnp��������
	NVR_CMD_GET_NTP_CFG		= 0x2010,		//��ȡntp��������
	NVR_CMD_SET_NTP_CFG		= 0x2011,		//����ntp��������
	NVR_CMD_GET_TIME_CFG	= 0x2012,		//��ȡʱ���������
	NVR_CMD_SET_TIME_CFG	= 0x2013,		//����ʱ���������
	NVR_CMD_GET_USR_CFG		= 0x2014,		//��ȡ�û���������
	NVR_CMD_SET_USR_CFG		= 0x2015,		//�����û���������
	NVR_CMD_GET_COMM_CFG 	= 0x2016,		//��ȡCOMM��������
	NVR_CMD_SET_COMM_CFG	= 0x2017,		//����COMM��������
	NVR_CMD_GET_CHANNEL_CFG = 0x2018,		//��ȡͨ����������
	NVR_CMD_SET_CHANNEL_CFG = 0x2019,		//����ͨ����������
	NVR_CMD_GET_AUTO_CFG	= 0x201a,		//��ȡ�Զ������������
	NVR_CMD_SET_AUTO_CFG	= 0x201b,		//���������������
	
	NVR_CMD_GET_JXJ_PLF_CFG = 0x201c,		//��ȡjxjƽ̨����
	NVR_CMD_SET_JXJ_PLF_CFG = 0x201d,		//����jxjƽ̨����
	NVR_CMD_GET_VMAIN_CFG	= 0x201e,		//���������
	NVR_CMD_SET_VMAIN_CFG	= 0x201f,		//����������
	NVR_CMD_GET_REC_CFG		= 0x2020,		//��ȡ¼���������
	NVR_CMD_SET_REC_CFG		= 0x2021,		//����¼���������
	NVR_CMD_GET_DI_CFG		= 0x2022,		//��ȡDI����
	NVR_CMD_SET_DI_CFG		= 0x2023,		//����DI����
	
	NVR_CMD_GET_IPNC_ALARM_CFG		= 0x2024,		//��ȡIPNC_ALARM����
	NVR_CMD_SET_IPNC_ALARM_CFG		= 0x2025,		//����IPNC_ALARM
	NVR_CMD_GET_DIANXIN_PLF_CFG = 0x2026,		//��ȡdianxinƽ̨����
	NVR_CMD_SET_DIANXIN_PLF_CFG = 0x2027,		//����dianxinƽ̨����
	
	NVR_CMD_GET_AUTO_CTRL_CFG = 0x2028,
	NVR_CMD_SET_AUTO_CTRL_CFG = 0x2029,
	NVR_CMD_GET_OSD_CFG = 0x202a,
	NVR_CMD_SET_OSD_CFG = 0x202b,
	
	NVR_CMD_GET_HD_CFG		,		//��ȡ������Ϣ
	NVR_CMD_SET_HD_CFG		,		//��ȡ������Ϣ
	NVR_CMD_GET_PTZ_CFG		,		//��ȡ��̨����
	NVR_CMD_SET_PTZ_CFG		,		//������̨����

	NVR_CMD_CFG_MAX			= 0x2100,	//����������
/*******************************************/
	NVR_CMD_KEEP_ALIVE		= 0x3000,
	NVR_CMD_ALARM_MSG			= 0x3001,
	NVR_CMD_SEARCH_SERVER_MSG   = 0x3003,
	
	NVR_CMD_START_SEARCH		= 0x4000,
	NVR_CMD_STOP_SEARCH			= 0x4001,
	NVR_CMD_GET_SEARCH			= 0x4002,
	NVR_CMD_TEST_IPC_STATUS		= 0x4003,
	NVR_CMD_SEARCH_CFG			= 0x4004,
	
	NVR_CMD_GET_PARAM			= 0x4005,
	NVR_CMD_SET_PARAM			= 0x4006,
	NVR_CMD_CTRL_PTZ			= 0x4007,	//��̨��������

	NVR_CMD_GET_PROT_TAB_INFO 	= 0x4008,	//��ȡ֧��Э����Ϣ
	NVR_CMD_GET_PROT_TAB_NUM 	= 0x4009,	//��ȡ֧��Э������
	NVR_CMD_EXPORT_PARAM	= 0x400a,
	NVR_CMD_IMPORT_PARAM	= 0x400b,
	NVR_CMD_START_MANUAL_REC	= 0x400c,	// ��ʼ�ֶ�¼��
	NVR_CMD_STOP_MANUAL_REC	= 0x400d,	// ֹͣ�ֶ�¼��
/*******************************************/

/*==================test cmd==start========*/
	NVR_TEST_CMD_SMTP			= 0xf001,
	NVR_TEST_CMD_FTP			= 0xf002,
/*==================test cmd==end==========*/
}NVR_NET_CMD_TYPE_E;


#endif

