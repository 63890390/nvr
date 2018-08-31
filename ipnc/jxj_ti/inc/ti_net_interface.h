#ifndef _TI_NET_INTERFACE_H_
#define _TI_NET_INTERFACE_H_

#include "ti_type.h"

#define TI_NET_MAX_PREVIEW_USER	16
#define TI_NET_MAX_LOGON_USER	16
#define TI_NET_MAX_VOD_USER		8
#define TI_NET_MAX_FIND_USER	4

typedef enum _IPC_FRAME_TYPE_E_
{
	VIDEO_FRAME_I = 0x7,
	VIDEO_FRAME_P = 0x8,
	VIDEO_FRAME_B = 0xB,
	AUDIO_FRAME_A = 0xA, 
}IPC_FRAME_TYPE_E;

typedef enum _TI_NET_ERR_CODE_E_
{
	TI_NET_ERR_SUCCESS   		= 0,
	TI_NET_ERR_USER_NO_EXIST	= -1,	
	TI_NET_ERR_PASSWORD 		= -2,
	TI_NET_ERR_NO_PERMIT		= -3,
	TI_NET_ERR_NO_INIT			= -4,
	TI_NET_ERR_CHANNEL			= -5,
	TI_NET_ERR_OVER_MAX_LINK	= -6,
	TI_NET_ERR_VERSION_NO_MATCH	= -7,
	TI_NET_ERR_CREATE_SOCKET	= -8,
	TI_NET_ERR_SET_SOCKET		= -9,
	TI_NET_ERR_LISTEN_FAIL		= -10,
	TI_NET_ERR_BIND_FAIL		= -11,
	TI_NET_ERR_CONNECT_FAIL 	= -12, 
	TI_NET_ERR_SEND_FAIL		= -13,
	TI_NET_ERR_RECV_FAIL		= -14,
	TI_NET_ERR_RECV_TIME_OUT	= -15,	
	TI_NET_ERR_ORDER_ERR	 	= -16,
	TI_NET_ERR_PARAMETER		= -17,
	TI_NET_ERR_NO_DISK			= -18,
	TI_NET_ERR_DISK_NUM			= -19,
	TI_NET_ERR_DISK_FULL		= -20,
	TI_NET_ERR_DISK_ERR			= -21,
	TI_NET_ERR_NO_SUPPORT		= -22,
	TI_NET_ERR_DEV_BUSY			= -23,
	TI_NET_ERR_MODIFY_FAIL		= -24,
	TI_NET_ERR_DISK_FORMATING	= -25,
	TI_NET_ERR_NO_RESOURCE		= -26,
	TI_NET_ERR_OPERATE_FAIL		= -27,
	TI_NET_ERR_VOICE_OPEN		= -28,
	TI_NET_ERR_INPUT_TIME_ERR	= -29,
	TI_NET_ERR_NO_FILE			= -30,
	TI_NET_ERR_FILE				= -31,
	TI_NET_ERR_ALLOC_RESOURCE	= -32,
	TI_NET_ERR_WRITE_FLASH		= -33,
	TI_NET_ERR_PROTACAL			= -34,
	TI_NET_ERR_MANULE_STOP		= -35,
	TI_NET_ERR_DATA_FORMAT		= -36,
	TI_NET_ERR_DATA_SIZE		= -37,			//��������ݳ���
	TI_NET_ERR_NO_MORE_FILE		= -38,			//û�и����ļ� ���ҽ���
	TI_NET_ERR_IS_FINDING		= -39,			//���ڲ���	
	TI_NET_ERR_KEEP_ALIVE		= -40
}TI_NET_ERR_CODE_E;

typedef enum _TI_NET_CMD_TYPE_E_
{
/*******************************************/
	TI_CMD_LOGON_SERVER		= 0x1001,
	TI_CMD_LOGOFF_SERVER	= 0x1002,	
	TI_CMD_OPEN_PREVIEW		= 0x1003,
	TI_CMD_CLOSE_PREVIEW	= 0x1004,
	TI_CMD_REQUEST_I_FRAME 	= 0x1005,
	TI_CMD_OPEN_TALK		= 0x1006,				//�򿪶Խ�
	TI_CMD_CLOSE_TALK		= 0x1007,				//�رնԽ�
	TI_CMD_START_UPGRADE	= 0x1008,				//��������
	TI_CMD_STOP_UPGRADE		= 0x1009,				//ֹͣ����	
	TI_CMD_START_FIND_FILE	= 0x100a,				//��ʼ����
	TI_CMD_STOP_FIND_FILE	= 0x100b,				//ֹͣ����
	TI_CMD_START_REC		= 0x100c,				//��ʼ¼�����ػ�ط�
	TI_CMD_STOP_REC			= 0x100d,				//ֹͣ¼�����ػ�ط�	
/*******************************************/
/******������ȡ��������***********/
	
	TI_CMD_GET_DEV_INFO		= 0x2000,		//��ȡ�豸ϵͳ����
	TI_CMD_SET_DEV_INFO		= 0x2001,		//�����豸ϵͳ����
	TI_CMD_GET_NET_CFG		= 0x2002,		//��ȡ�豸��������
	TI_CMD_SET_NET_CFG		= 0x2003,		//�����豸��������
	TI_CMD_GET_VIDEO_CFG	= 0x2004,		//��ȡ�豸��Ƶ����
	TI_CMD_SET_VIDEO_CFG	= 0x2005,		//�����豸��Ƶ����
	TI_CMD_GET_OSD_CFG		= 0x2006,		//��ȡ�豸��Ƶosd����
	TI_CMD_SET_OSD_CFG		= 0x2007,		//�����豸��Ƶosd����
	TI_CMD_GET_VMASK_CFG	= 0x2008,		//��ȡ�豸��Ƶ�ڵ�����
	TI_CMD_SET_VMASK_CFG	= 0x2009,		//�����豸��Ƶ�ڵ�����
	TI_CMD_GET_VMD_CFG		= 0x200a,		//��ȡ�豸��Ƶ�ƶ�������
	TI_CMD_SET_VMD_CFG		= 0x200b,		//�����豸��Ƶ�ƶ�������
	TI_CMD_GET_VMAIN_CFG	= 0x200c,		//��ȡ�豸��Ƶ����������
	TI_CMD_SET_VMAIN_CFG	= 0x200d,		//�����豸��Ƶ����������
	TI_CMD_GET_VSUB_CFG		= 0x200e,		//��ȡ�豸��Ƶ����������
	TI_CMD_SET_VSUB_CFG		= 0x200f,		//�����豸��Ƶ����������
	TI_CMD_GET_VCAP_CFG		= 0x2010,		//��ȡ�豸��Ƶץ�Ĳ���
	TI_CMD_SET_VCAP_CFG		= 0x2011,		//�����豸��Ƶץ�Ĳ���
	TI_CMD_GET_IMA_CFG		= 0x2012,		//��ȡ�豸ͼ�����
	TI_CMD_SET_IMA_CFG		= 0x2013,		//�����豸ͼ�����
	TI_CMD_GET_3A_CFG		= 0x2014,		//��ȡ�豸3A����
	TI_CMD_SET_3A_CFG		= 0x2015,		//�����豸3A����
	TI_CMD_GET_AUDIO_CFG	= 0x2016,		//��ȡ��Ƶ����
	TI_CMD_SET_AUDIO_CFG	= 0x2017,		//������Ƶ����
	TI_CMD_GET_COMM_CFG		= 0x2018,		//��ȡ������Ϣ
	TI_CMD_SET_COMM_CFG		= 0x2019,		//���ô�����Ϣ
	TI_CMD_GET_FTP_CFG		= 0x201a,		//��ȡftp��������
	TI_CMD_SET_FTP_CFG		= 0x201b,		//����ftp��������
	TI_CMD_GET_EMAIL_CFG	= 0x201c,		//��ȡemail��������
	TI_CMD_SET_EMAIL_CFG	= 0x201d,		//����email��������
	TI_CMD_GET_DDNS_CFG		= 0x201e,		//��ȡddns��������
	TI_CMD_SET_DDNS_CFG		= 0x201f,		//����ddns��������
	TI_CMD_GET_UPNP_CFG		= 0x2020,		//��ȡupnp��������
	TI_CMD_SET_UPNP_CFG		= 0x2021,		//����upnp��������
	TI_CMD_GET_NTP_CFG		= 0x2022,		//��ȡntp��������
	TI_CMD_SET_NTP_CFG		= 0x2023,		//����ntp��������
	TI_CMD_GET_TIME_CFG		= 0x2024,		//��ȡʱ���������
	TI_CMD_SET_TIME_CFG		= 0x2025,		//����ʱ���������
	TI_CMD_GET_USR_CFG		= 0x2026,		//��ȡ�û���������
	TI_CMD_SET_USR_CFG		= 0x2027,		//�����û���������
	TI_CMD_GET_DI_CFG		= 0x2028,		//��ȡ�����������	
	TI_CMD_SET_DI_CFG		= 0x2029,		//���ñ����������	
	TI_CMD_GET_REC_CFG		= 0x202a,		//��ȡ¼���������
	TI_CMD_SET_REC_CFG		= 0x202b,		//����¼���������
	TI_CMD_GET_HD_CFG		= 0x202c,		//��ȡ������Ϣ
	TI_CMD_GET_PTZ_CFG		= 0x202e,		//��ȡ��̨����
	TI_CMD_SET_PTZ_CFG		= 0x202f,		//������̨����
	TI_CMD_GET_STABLE_CFG   = 0x2030,       //��ȡ�豸��Ϣ
	TI_CMD_SET_STABLE_CFG   = 0x2031,       //�����豸��Ϣ
/* BEGIN: Added by xq, 2011/12/20 */
	TI_CMD_GET_BALL_CFG		= 0x2032,		//��ȡ����������
	TI_CMD_SET_BALL_CFG		= 0x2033,		//���ø���������
/* END:   Added by xq, 2011/12/20 */
	TI_CMD_GET_DEV_CAP			= 0x2034,	//��ȡ�豸����ϸ��Ϣ
	TI_CMD_SET_DEV_CAP			= 0x2035,	//�����豸����ϸ��Ϣ
	TI_CMD_GET_JXJ_PLATFORM_CFG	= 0x2036,
	TI_CMD_SET_JXJ_PLATFORM_CFG	= 0x2037,
	TI_CMD_GET_ONVIF_CFG		= 0x2038,
	TI_CMD_SET_ONVIF_CFG		= 0x2039,
	
	TI_CMD_GET_PP_SET_CFG		= 0x2040,	//��ȡԤ�õ�����
	TI_CMD_SET_PP_SET_CFG		= 0x2041,	//����Ԥ�õ�����

	TI_CMD_GET_OSD_LABEL_CFG 		= 0x2044,		//��ȡOSD��չ��ע
	TI_CMD_SET_OSD_LABEL_CFG		= 0x2045,		//����OSD��չ��ע

	TI_CMD_GET_HXHT_PLATFORM_CFG	= 0x203a,
	TI_CMD_SET_HXHT_PLATFORM_CFG	= 0x203b,	
	TI_CMD_GET_GB28181_PLATFORM_CFG	= 0x203c,
	TI_CMD_SET_GB28181_PLATFORM_CFG	= 0x203d,
	TI_CMD_GET_IRCFMODE_CFG 	= 0x203e,		//��ȡ��������
	TI_CMD_SET_IRCFMODE_CFG 	= 0x203f,		//���ú�������


	TI_CMD_CFG_MAX				= 0x2100,		//����������

	TI_CMD_CTRL_PTZ				= 0x2101,		//��̨��������
	TI_CMD_SEND_SERIAL_DATA		= 0x2102,		//�������ݵ���������
	TI_CMD_CTRL_SERIAL			= 0x2103,		//����/ֹͣ ���ڲɼ�

	/* BEGIN: Added by xq, 2011/9/26 */
	TI_CMD_SET_ALARM_OUT		= 0x2104,	    //���ñ������״̬
	/* END:   Added by xq, 2011/9/26 */
	/* BEGIN: Added by hx, 2012/12/14 */
	TI_CMD_WIFI_SCAN 			= 0x2106,		// WIFIɨ��
	TI_CMD_CTRL_WIFI 			= 0x2107,		// WIFI���ӻ�Ͽ�
	/* END: Added by hx, 2011/12/14 */
	
	TI_CMD_RESTART_DEV			= 0x2110,		//�����豸
	TI_CMD_RESET_DEV			= 0x2111,		//��λ�豸

	TI_CMD_FORMAD_DISK			= 0x2120,
	TI_CMD_GET_FORMAD_PERCENT	= 0x2121,
	
	TI_CMD_GET_SEARCH_RES 		= 0x2f01, 		//�����ڲ���ȡ����
	TI_CMD_SET_SEARCH_CFG 		= 0x2f02,		//�����ڲ����ò���



/*******************************************/
	TI_CMD_KEEP_ALIVE			= 0x3000,
	TI_CMD_ALARM_MSG			= 0x3001,
	TI_CMD_COMM_DATA_MSG		= 0x3002,
	TI_CMD_SEARCH_SERVER_MSG    = 0x3003,		//����
	TI_CMD_SEARCH_CONFIG_SERVER	= 0x3004,		//��������
	TI_CMD_UPDATE_PRECENT		= 0x3005,
	TI_CMD_UPDATE_ERR			= 0x3006,
	TI_CMD_UPDATE_FINISH		= 0x3007,
	TI_CMD_UPDATE_INFO			= 0x3008,		//�����ļ���Ϣ
	TI_CMD_UPDATE_DATA			= 0x3009,	
	TI_CMD_FIND_DATA			= 0x300a,
	TI_CMD_REC_CTRL				= 0x300b,		//¼�����ء�¼��طſ���
	TI_CMD_SEARCH_INFO_SERVER	= 0x300c,
/*****************************************/	

/*****************************************/
	TI_CMD_GET_STATS			= 0x4001,		// ���ڻ�ȡͳ����Ϣ
/*****************************************/
}TI_NET_CMD_TYPE_E;

typedef enum _TI_NET_PROTOCAL_TYPE_E_
{
	TI_NET_PROTOCAL_TCP 		= 0,
	TI_NET_PROTOCAL_UDP 		= 1,
	TI_NET_PROTOCAL_MULTICAST 	= 2,
	TI_NET_PROTOCAL_BOARDCAST 	= 3,
	TI_NET_PROTOCAL_BUTT 		= 4,
}TI_NET_PROTOCAL_TYPE_E;

typedef enum _TI_NET_MSG_NOTIFY_
{
	TI_NET_MSG_LOGON_INIT		= 0x0,
	TI_NET_MSG_LOGON_UNINIT		= 0x1,
	TI_NET_MSG_LOGON_START		= 0x2,
	TI_NET_MSG_LOGON_STOP		= 0x3,
	TI_NET_MSG_LOGON_LINK		= 0X4,
	TI_NET_MSG_LOGON_UNLINK		= 0X5,
	
	TI_NET_MSG_PREV_INIT		= 0x10,
	TI_NET_MSG_PREV_UNINIT		= 0x11,
	TI_NET_MSG_PREV_START		= 0x12,
	TI_NET_MSG_PREV_STOP		= 0x13,	
	TI_NET_MSG_PREV_LINK		= 0x14,
	TI_NET_MSG_PREV_UNLINK  	= 0x15,

	TI_NET_MSG_TALK_INIT		= 0x20,
	TI_NET_MSG_TALK_UNINIT		= 0x21,
	TI_NET_MSG_TALK_START		= 0x22,
	TI_NET_MSG_TALK_STOP		= 0x23,	
	TI_NET_MSG_TALK_LINK		= 0x24,
	TI_NET_MSG_TALK_UNLINK		= 0x25,

	TI_NET_MSG_VOD_INIT			= 0x30,
	TI_NET_MSG_VOD_UNINIT		= 0x31,	
	TI_NET_MSG_VOD_START		= 0x32,
	TI_NET_MSG_VOD_STOP			= 0x33,		
	TI_NET_MSG_VOD_LINK			= 0x34,
	TI_NET_MSG_VOD_UNLINK		= 0x35,

	TI_NET_MSG_FIND_INIT		= 0x40,
	TI_NET_MSG_FIND_UNINIT		= 0x41,	
	TI_NET_MSG_FIND_START		= 0x42,
	TI_NET_MSG_FIND_STOP		= 0x43,		
	TI_NET_MSG_FIND_LINK		= 0x44,
	TI_NET_MSG_FIND_UNLINK		= 0x45,
	
	TI_NET_MSG_SEARCH_INIT		= 0x50,
	TI_NET_MSG_SEARCH_UNINIT	= 0x51,	
	TI_NET_MSG_SEARCH_START		= 0x52,
	TI_NET_MSG_SEARCH_STOP		= 0x53,		
	TI_NET_MSG_SEARCH_CMD		= 0x54,

	TI_NET_MSG_SERVER_INIT		= 0x60,
	TI_NET_MSG_SERVER_UNINIT	= 0x61,	
	TI_NET_MSG_SERVER_START		= 0x62,
	TI_NET_MSG_SERVER_STOP		= 0x63,		
	TI_NET_MSG_SERVER_LINK		= 0x64,
	TI_NET_MSG_SERVER_UNLINK	= 0x65,

	TI_NET_MSG_UPDATE_INIT		= 0x70,
	TI_NET_MSG_UPDATE_UNINIT	= 0x71,	
	TI_NET_MSG_UPDATE_START		= 0x72,
	TI_NET_MSG_UPDATE_STOP		= 0x73,		
	TI_NET_MSG_UPDATE_LINK		= 0x74,
	TI_NET_MSG_UPDATE_UNLINK	= 0x75,	

	/* BEGIN: Added by xq, 2011/9/23 */
	TI_PLATFORM_MSG_PREV_INIT		= 0x80,
	TI_PLATFORM_MSG_PREV_UNINIT		= 0x81,	
	TI_PLATFORM_MSG_PREV_START		= 0x82,
	TI_PLATFORM_MSG_PREV_STOP		= 0x83,	
	TI_PLATFORM_MSG_PREV_LINK		= 0x84,
	TI_PLATFORM_MSG_PREV_UNLINK		= 0x85,	
	/* END:   Added by xq, 2011/9/23 */
}TI_NET_MSG_NOTIFY;

#define TI_NET_LINK_MAX_NUM	8

// �����������
typedef enum _TI_SERVER_TYPE_
{
	TI_NET_LOGON_SERVER_TYPE = 0,
	TI_NET_PREVIEW_SERVER_TYPE,
	
	TI_NET_SERVER_TYPE_NUM,
}TI_SERVER_TYPE;

// ��������״̬��Ϣ
typedef struct _TI_NET_LINK_STATUS_
{
	int bUsed;
	fd_set remoteFdSet;
	char szRemoteAddr[32];
	TI_U32 nConnectNum;
	TI_U32 nDisconnectNum;
}TI_NET_LINK_STATUS;

// �������ͳ����Ϣ
typedef struct _TI_SERVER_STATISTICS_
{
	TI_U32 nConnectNum;
	TI_U32 nDisconnectNum;
	TI_U32 nLostNum;
	TI_U32 nErrorNum;
	TI_U32 nOverrunNum;
	TI_NET_LINK_STATUS stLinkStatus[TI_NET_LINK_MAX_NUM];
}TI_SERVER_STATISTICS;

typedef struct _TI_NET_STATISTICS_
{
	TI_U32 nTotalConnectNum;
	TI_U32 nTotalDisconnectNum;
	TI_SERVER_STATISTICS stServerSta[TI_NET_SERVER_TYPE_NUM];
}TI_NET_STATISTICS;

typedef struct _TI_NET_PREVIEW_NET_STATS_S
{
	TI_U32	u64SendBytes;
	TI_U32	u32AverageBytes;
	TI_U32	u32SendVideoFrames;
	TI_U32	u32SendAudioFrames;
}TI_NET_PREVIEW_NET_STATS_S;




#endif


