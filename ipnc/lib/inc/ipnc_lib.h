#ifndef __IPNC_PROTOCOL_H__
#define __IPNC_PROTOCOL_H__
#include <netinet/in.h>

#define	PROCOTOL_REQUEST_MAGIC		0x34ab12cd
#define	PROTOCOL_RESPONSE_MAGIC		0xab34cd12

#define RECV_BUFF_SIZE	4096*2


typedef struct CmdHead
{
	int 	  magic;			// ħ��
	long 	  ipncHandle;		// ��ʶ�������豸
	long 	  logonHandle;		// ��¼�豸�������
	int 	  cmd;				// ������
	uint32_t  paramCmd;			// ����������:IPNC_CMD_TYPE_E
	int 	  response;			// �Ƿ���Ҫ��Ӧ
	int 	  result;			// ���ؽ��
	int 	  cmdDataLen;		// �������ݴ�С
}CmdHead;
#define CMD_HAED_MAGIC(cmd)	(cmd->magic)
#define CMD_HAED_CMD(cmd)		(cmd->cmd)
#define CMD_HAED_LEN(cmd)		(cmd->cmdDataLen)
#define CMD_HEAD_RESULT(cmd)	(cmd->result)

enum
{
	// common command
	IPNC_CONNECT = 0,
	IPNC_DISCONNECT,
	
	IPNC_START_SEARCH,
	IPNC_STOP_SEARCH,
	IPNC_GET_SEARCH,
	IPNC_SEARCH_CFG,
	
	IPNC_LOGON,
	IPNC_LOGOUT,

	IPNC_GET_PARAM,
	IPNC_SET_PARAM,
	
	IPNC_START_GET_STREAM,
	IPNC_STOP_GET_STREAM,
	IPNC_REQUEST_IFRAME,
	
	// PARAM command
	IPNC_GET_DEV_INFO = 0x1000,
	IPNC_SET_DEV_INFO,

	// PTZ command
	IPNC_PTZ_CTRL,

	IPNC_TEST_IPC_STATUS,
};

typedef struct
{
	char ipAddr[16];
	int port;
	char user[32];
	char passwd[32];
	int poolCh;
}IpncConnect;

typedef struct
{
	unsigned long ipAddr;
	int port;
}IpncSearch;

typedef struct
{
	int chn;
	int streamNo;
	int poolCh;
	int poolStreamNo;
}IpncChannel;

/**********************************************ipnc�ṹ����Ϣ����***********************************************/
#define IPNC_SERIALNO_LEN	48	//���кų���
#define IPNC_COMMON_LEN		64	//����
#define IPNC_IP_ADDR_LEN	64  //ip��ַ��������
#define IPNC_MAC_ADDR_LEN	6	//mac��ַ����
#define	IPNC_USER_NAME_LEN	32	//�û�������
#define	IPNC_PASS_WORD_LEN	32	//�û����볤��
#define	IPNC_MAX_EMAIL_LEN	64	//���䳤��

#define IPNC_VMASK_REG_NUM		4	//��Ƶ�ڵ�����
#define IPNC_VMD_REG_NUM		4	//��Ƶ���������
#define IPNC_MAX_SEG_NUM		4	//���ʱ���
#define IPNC_MAX_IRCF_SEG_NUM	4	//���ⶨʱ���ʱ���
#define IPNC_MAX_OSD_LABEL_NUM 	5	//osd��ע�������� 


//=======================ptz����
typedef enum _IPNC_PTZ_CMD_E_
{
	PTZ_CMD_UP				=	0,	//��
	PTZ_CMD_SENSE			=	1,	//
	PTZ_CMD_DOWN			=	2,	//��
	PTZ_CMD_LEFT			=	3,	//��
	PTZ_CMD_RIGHT			=	4,	//��
	PTZ_CMD_LEFT_UP			=	5,	//����
	PTZ_CMD_LEFT_DOWN		=	6,	//����
	PTZ_CMD_RIGHT_UP		=	7,	//����
	PTZ_CMD_RIGHT_DOWN		=	8,	//����
	PTZ_CMD_AUTOSCAN		=	9,	//�Զ�ɨ��
	PTZ_CMD_MANUALSCAN		=	10,	//�ֶ�ɨ��
	PTZ_CMD_FOCUS_NEAR		=	11, //�۽�+
	PTZ_CMD_FOCUS_FAR		=	12, //�۽�-
	PTZ_CMD_IRIS_CLOSE		=	13, //��Ȧ-
	PTZ_CMD_IRIS_OPEN		=	14,	//��Ȧ+
	PTZ_CMD_ZOOM_WIDE		=	15,	//�䱶+
	PTZ_CMD_ZOOM_TELE		=	16, //�䱶-
	PTZ_CMD_STOP			=	17,	//ֹͣ

	PTZ_CMD_SET_PRESET		=	18,  //Ԥ��λ����
	PTZ_CMD_CLR_PRESET		=	19,	 //Ԥ��λ���
	PTZ_CMD_GOTO_PRESET		=	20,  //Ԥ��λ����
	PTZ_CMD_FLIP			=	21,  //��ת
	PTZ_CMD_GOTO_ZEROPAN	=	22,  //��λ����
	PTZ_CMD_SET_AUX			=	23,  //���ø�������
	PTZ_CMD_CLR_AUX			=	24,  //�����������
	PTZ_CMD_REMOTE_RESET	=	25,  //Զ�ָ̻�
	PTZ_CMD_ZONE_START		=	26,  //���û���ɨ�迪ʼ
	PTZ_CMD_ZONE_END		=	27,  //���û���ɨ�����
	PTZ_CMD_WR_CHAR			=	28,  //д�ַ�
	PTZ_CMD_CLR_SCR			=	29,  //����ַ�
	PTZ_CMD_ALM_ACK			=	30,  //����ȷ��
	PTZ_CMD_ZONE_SCAN_ON	=	31,  //��������ɨ��
	PTZ_CMD_ZONE_SCAN_OFF	=	32,  //ֹͣ����ɨ��
	PTZ_CMD_PTN_START		=	33,  //
	PTZ_CMD_PTN_STOP		=	34,  //
	PTZ_CMD_RUN_PTN			=	35,  //
	PTZ_CMD_ZOOM_SPEED		=	36,  //�䱶�ٶ�
	PTZ_CMD_FOCUS_SPEED		=	37,  //�۽��ٶ�
	PTZ_CMD_RESET_CAMERA	=	38,  //�����λ
	PTZ_CMD_AUTO_FOCUS		=	39,  //�Զ��۽�
	PTZ_CMD_AUTO_IRIS		=	40,  //�Զ���Ȧ 
	PTZ_CMD_AUTO_AGC		=	41,  //�Զ�����
	PTZ_CMD_BACKLIGHT_COMP	=	42,	 //
	PTZ_CMD_AUTO_WB		    =	43,  //�Զ���ƽ��
	PTZ_CMD_DEV_PHASE_DELAY	=	44,  //
	PTZ_CMD_SET_SHTTER_SPEED=	45,  //���ÿ����ٶ�
	PTZ_CMD_ADJ_LL_PHASE_DELAY=	46,
	PTZ_CMD_ADJ_WB_RB		=	47,  //�����Զ���ƽ�����
	PTZ_CMD_ADJ_WB_MG		=	48,  //�����Զ���ƽ��
	PTZ_CMD_ADJ_GAIN		=	49,  //�����Զ�����
	PTZ_CMD_AUTO_IRIS_LV	=	50,  //�����Զ���Ȧlevel
	PTZ_CMD_AUTO_IRIS_PEAK	=	51,  //�����Զ���Ȧpeak
	PTZ_CMD_QUERY			=	52,  //��ѯ
	
	PTZ_CMD_INVALID			=	53,
	
	PTZ_CMD_SET_CRUISE		 = 	1000,	// ����Ѳ��ɨ��
	PTZ_CMD_SET_CRUISE_START =	1001,	// �Զ�Ѳ��ɨ�� 
	PTZ_CMD_SET_GUARD_POS	 =	1002,	// ���ÿ���λ
	PTZ_CMD_GOTO_GUARD_POS	 =	1003,	// ���ÿ���λ
	PTZ_CMD_SET_AUTOSCAN_SETTING = 1004,	// �����Զ�ɨ��
	PTZ_CMD_SET_AUTOSCAN_START	 = 1005,	// �����Զ�ɨ�� 
	PTZ_CMD_SET_ABSCAN_SETTING	 = 1006,	// ����AB����ɨ��
	PTZ_CMD_SET_ABSCAN_LEFT_POS	 = 1007,	// ����AB��������λ 
	PTZ_CMD_SET_ABSCAN_RIGHT_POS = 1008,	// ����AB��������λ
	PTZ_CMD_SET_ABSCAN_START	 = 1009,	// ����AB����ɨ��
	PTZ_CMD_SET_IDLE_SETTING	 = 1010,	// �������ö���
	PTZ_CMD_SET_ONTIME_SETTING	 = 1011,	// ���ö�ʱ����
	PTZ_CMD_SET_ALARM_SETTING	 = 1012,	// ���ñ�������ʱ�Ķ���
	PTZ_CMD_TRIG_ALARM			 = 1013,	// ��������
	PTZ_CMD_CLR_ALARM			 = 1014,
	PTZ_CMD_SET_IR_MODE			 = 1015,	// ����ƹ���
	PTZ_CMD_SET_DAY_NIGHT_MODE	 = 1016,	// ��ҹģʽ
	PTZ_CMD_SET_180_AUTO_FLIP	 = 1017,	// 180�Զ���ת
	PTZ_CMD_SET_IRIS_MODE		 = 1018,	// ��Ȧ����ģʽ
	PTZ_CMD_SET_BLC_MODE		 = 1019,	// ���ⲹ��
	PTZ_CMD_SET_ZOOM_DISPLAY	 = 1020,	// ��λ��ʾ
	PTZ_CMD_SET_FRAME_NOISE		 = 1021,	// ֡����
	PTZ_CMD_SET_WB_MODE			 = 1022,	// ��ƽ��ģʽ
	PTZ_CMD_SET_WDR_MODE		 = 1023,	// ��̬
	PTZ_CMD_SET_AUTO_ZOOM		 = 1024,	// �Զ��䱶
	PTZ_CMD_SET_3D_CONTROL		 =	1025,	// �������3D����
	PTZ_CMD_SET_3D_RECT_CENTER	 = 	1026,	// 3D��λ��ѡ����
	PTZ_CMD_SET_3D_POINT_CENTER	 =	1027,	// 3D��λ�������
	PTZ_CMD_GET_ZOOM		 = 1050,		// ��ȡ�䱶��С
	PTZ_CMD_QUERY_STATUS	 = 1051,		// ��ѯ���״̬
	PTZ_CMD_GET_VERSION_ID	 = 1052,		// ��ȡ������汾��
	PTZ_CMD_SET_BRIGHT		 = 1053,		// ��������
	PTZ_CMD_SET_CONTRAST	 = 1054,		// ���öԱȶ�
	PTZ_CMD_SET_SATURATION	 = 1055,		// ���ñ��Ͷ�
	PTZ_CMD_SET_SHARPNESS	 = 1056,		// �������
	PTZ_CMD_SET_RED			 = 1057,		// ���ú�ɫ
	PTZ_CMD_SET_BLUE		 = 1058,		// ������ɫ
	PTZ_CMD_GET_SOFT_ID		 = 1059,		// ��ȡ���ID
	PTZ_CMD_GET_FEATURE_INFO = 1060,		// ��ȡ������Ϣ
	PTZ_CMD_GET_CAMERA_INFO	 = 1061,		// ��ȡ��о��Ϣ
	PTZ_CMD_GET_FRAME_RATE	 = 1062,		// ��ȡ�����ǰ֡��
	PTZ_CMD_GET_CAMERA_TYPE	 = 1063,		// ��ȡ�����о����
	
	PTZ_CMD_SET_DEFAULT 	= 	1100,		// �ָ�Ĭ�ϳ�������
	PTZ_CMD_SET_REBOOT		=	1101,		//����

	PTZ_CMD_DEL_CRUISE		= 	1102,	// ɾ��Ѳ��ɨ�� jxj_cuʹ��
	PTZ_CMD_STOP_CRUISE     =	1103,	// ֹͣѲ��ɨ�� jxj_cuʹ��
	
	PTZ_CMD_INVALID_CMD 	= 	1200,		// ��Ч����
	
} IPNC_PTZ_CMD_E;

// ========================ipnc protocol������Ϣ
typedef struct _IPNC_USR_PWD_S
{
	char usr[IPNC_USER_NAME_LEN];
	char pwd[IPNC_PASS_WORD_LEN];
}IPNC_USR_PWD_S;

typedef struct _IPNC_PROTOCOL_S
{
	char name[IPNC_USER_NAME_LEN];			//Э����
	char aliasName[IPNC_USER_NAME_LEN];		// Э�����
	char factoryName[IPNC_USER_NAME_LEN];	//Э�鳧��
	IPNC_USR_PWD_S usrPwd[4];
	int dataPort;
	int webPort;
	int rtspPort;	
}IPNC_PROTOCOL_S;

//======================ʱ��ṹ
typedef struct _IPNC_TIME_S
{
	uint8_t		u8Year;			//��(��1900�꿪ʼ)
	uint8_t		u8Month;		//��1~12
	uint8_t		u8Day;			//��1~31
	uint8_t		u8WDay;			//������0 ����һ1.....
	uint8_t		u8Hour;			//ʱ0~23
	uint8_t		u8Minute;		//��0~59
	uint8_t		u8Second;		//��0~59
	uint8_t		u8Millisec;		//����(0~99)(�ٷ�֮һ��)
}IPNC_TIME_S, *LPIPNC_TIME_S;

//=======================ʱ��νṹ
typedef struct _IPNC_SEGMENT_S
{
	uint32_t 	u8Open:8;		//����
	uint32_t	beginSec:24;	//��ʼʱ������ 3600*hour+60*min+sec
	uint32_t	u8Rsvd:8;		//����
	uint32_t	endSec:24;		//����ʱ������ 3600*hour+60*min+sec
}IPNC_SEGMENT_S, *LPIPNC_SEGMENT_S;

//=======================��ṹ
typedef struct _IPNC_POINT_S
{
	int		s32X;		//���x����
	int		s32Y;		//���y����
}IPNC_POINT_S, *LPIPNC_POINT_S;

//=======================����ṹ
typedef struct _IPNC_RECT_S
{
	int			s32X;			//���x����
	int			s32Y;			//���y����
	uint32_t	u32Width;		//������
	uint32_t	u32Height;		//����߶�
}IPNC_RECT_S, *LPIPNC_RECT_S;

//=======================�澯����
typedef struct _IPNC_LINKACT_S
{
	uint32_t	u32ShootChannel;	//ץ��ͨ��(bit)(0 ��ץ�� 1��һͨ��ץ��)
	uint32_t	u32ShootInterval;	//ץ�ļ��(����),0:����ץ��
	uint32_t	u32RecTime;			//¼��ʱ��(��)
	uint32_t	u32RecChannel;		//¼��ͨ��(bit) (0 ��¼�� 1��һͨ��¼��)
	uint32_t	u32PCRecChannel;	//����PC¼��ͨ��	
	uint32_t	u32OutPut;			//�������(bit)
	uint32_t	u32OutPersist;		//�������ʱ��
	uint8_t		u8ShootMode;		//����ץ��ģʽ,0���ش洢��1ftp�ϴ���2email
	uint8_t		u8ShootNum;			//ץ������	
	uint8_t		u8RecMode;			//����¼��ģʽ��0���ش洢��1ftp�ϴ�	
	uint8_t		u8RecPreTime;		//Ԥ¼ʱ��(��)
	uint8_t		u8Email;			//����email
	uint8_t		u8Rsvd[15];
}IPNC_LINKACT_S, *LPIPNC_LINKACT_S;

//�豸��Ϣ
typedef struct _IPNC_DEV_STABLE_INFO_S_
{
	uint8_t		u8SerialId[IPNC_SERIALNO_LEN];  	//�豸Id
	uint8_t		u8DiNum;						//��������·��
	uint8_t		u8DoNum;						//�������·��
	uint8_t		u8ChnNum  ;						//�豸·��
	uint8_t		u8Rs232Num;						//�豸232 ���ڸ���
	uint8_t		u8Rs485Num;						//�豸485 ���ڸ���
	uint8_t		u8NetCardNum;					//��������
	uint16_t	u16DevType ;					//�豸����						
	uint32_t	u32HwVer;						//Ӳ���汾��
	uint32_t	u32CoreVer;						//�ں˰汾��
	uint32_t	u32SoftVer;						//����汾��
	uint32_t	u32ResolutionM;					//֧�ֵ��������ֱ��ʴ�С
	uint32_t	u32ResolutionS;					//֧�ֵĴ������ֱ��ʴ�С	
	uint32_t	u32SensorType;					//ǰ��sensor ����
	uint8_t		u8Res2[12];	
}IPNC_DEV_STABLE_INFO_S, *LPIPNC_DEV_STABLE_INFO_S;

typedef struct _IPNC_DEV_VAR_INFO_S
{
	char		szDevName[IPNC_USER_NAME_LEN];  	//�豸����
	uint8_t		u8Language;						//����0 ����1Ӣ��
	uint8_t		u8PalStand;						//��ʽ1 pal 0 ntfc
	uint8_t		u8Hz;							//��ԴƵ��0 50Hz 1 60HZ
	uint8_t		u8Res[17];
}IPNC_DEV_VAR_INFO_S;

typedef struct _IPNC_DEV_CFG_S_
{
	char serialId[IPNC_SERIALNO_LEN];	//�豸ID,���к�
	char hwVer[IPNC_COMMON_LEN];		//�豸Ӳ���汾
	char codeVer[IPNC_COMMON_LEN];		//�豸�ں˰汾
	char sofrVer[IPNC_COMMON_LEN];		//�豸����汾
	
	IPNC_DEV_VAR_INFO_S stVarInfo;		//ϵͳ�豸���޸���Ϣ

	uint32_t di_num;							//�豸����ӿ���Ŀ
	uint32_t do_num;							//�豸����ӿ���Ŀ
	uint32_t channel_num;						//ͨ����Ŀ
	uint32_t rs485_num;							//RS485�ӿ���Ŀ����0������
	uint32_t rs232_num;							//RS232�ӿ���Ŀ����0������
	
	uint8_t uRes[12];
}IPNC_DEV_CFG_S, *LPIPNC_DEV_CFG_S;

//������Ϣ
typedef struct _IPNC_NET_CFG_S_
{
	char  ipAddr[IPNC_IP_ADDR_LEN];	//IP��ַ
	char  subMask[IPNC_IP_ADDR_LEN];//��������
	char  gateWay[IPNC_IP_ADDR_LEN];//����
	char  macAddr[IPNC_MAC_ADDR_LEN];//MAC��ַ
	char  dnsIp1[IPNC_IP_ADDR_LEN];	//DNS��ַ1
	char  dnsIp2[IPNC_IP_ADDR_LEN];	//DNS��ַ2
	uint16_t u16HttpPort;			//http �˿�
	uint16_t u16NetPort;			//ͨ�Ŷ˿�
	
	uint8_t uRes[32];
}IPNC_NET_CFG_S, *LPIPNC_NET_CFG_S;

//�û���Ϣ
typedef struct _IPNC_USER_CFG_S_
{
	char 	userName[IPNC_USER_NAME_LEN];	//ԭ�û���
	char 	passWord[IPNC_PASS_WORD_LEN];	//Դ����
	//char 	newUserName[IPNC_USER_NAME_LEN];//���û���
	//char 	newPassWord[IPNC_PASS_WORD_LEN];//������
	char 	cfmPassWord[IPNC_PASS_WORD_LEN];//ȷ��������
	uint8_t		u8Res[6];
}IPNC_USER_CFG_S, *LPIPNC_USER_CFG_S;

//ftp��Ϣ
typedef struct _IPNC_FTP_CFG_S_
{
	char 	 ftpSvr[IPNC_IP_ADDR_LEN]; 	//��ftp������ip
	char  	 ftpUsr[IPNC_USER_NAME_LEN];//��½�û���
	char	 ftpPsw[IPNC_PASS_WORD_LEN];//��½����
	char	 ftpPath[IPNC_COMMON_LEN];  //Ftp�ϴ�·��
	uint16_t u16FtpPort;				//ftp�˿�

}IPNC_FTP_CFG_S, *LPIPNC_FTP_CFG_S;

//smtp��Ϣ
typedef struct _IPNC_SMTP_CFG_S_
{
	char 	 mailHub[IPNC_IP_ADDR_LEN]; 	//smtp ��������ַ
	char     mailAddr[IPNC_MAX_EMAIL_LEN];	//�����ʼ� ��ַ
	char  	 mailUsr[IPNC_MAX_EMAIL_LEN]; 	//�����ʼ� �˺�
	char 	 mailPsw[IPNC_PASS_WORD_LEN];  	//�����ʼ� ����
	char 	 mailRctp1[IPNC_MAX_EMAIL_LEN];	//�����ʼ� ��ַ1
	char 	 mailRctp2[IPNC_MAX_EMAIL_LEN];	//�����ʼ� ��ַ2
	char  	 mailRctp3[IPNC_MAX_EMAIL_LEN];	//�����ʼ� ��ַ3
	uint16_t u16MailPort;					//smtp �������˿�
	
}IPNC_SMTP_CFG_S, *LPIPNC_SMTP_CFG_S;

//ntp��Ϣ
typedef struct _IPNC_NTP_CFG_S_
{
	uint8_t	 enable;						//ntp ����
	char   	 ntpServer[IPNC_IP_ADDR_LEN];	//ntp������
	int	  	 timeZone;						//ʱ�� ��λs(-12*3600~11*3600)
	int	  	 euroTime;						//==1:��������ʱ 0:����������ʱ
	uint8_t	 ntpRefTime;					//ntp ��ʱ��ʱʱ��(��λСʱ)
	//uint16_t u16NtpPort;					//�˿�
}IPNC_NTP_CFG_S, *LPIPNC_NTP_CFG_S;

//upnp��Ϣ
typedef struct _IPNC_UPNP_CFG_S_
{
	uint32_t	u32Size;
	uint8_t		u8UpnpOpen;			//upnp ����
	uint8_t		u8UpnpEthNo;		//0ʹ�ñ�������ӳ�� 1 ʹ����������ӳ��
	uint8_t		u8UpnpModel;    	//0�̶�ӳ�� 1�Զ�ӳ��
	uint8_t		u8UpnpRefTime;  	//upnp ˢ��ʱ��(��λСʱ)
	char        szUpnpSvr[IPNC_IP_ADDR_LEN];
	uint16_t	u16UpnpDataPort;	//�̶�ӳ��ģʽ��, ���ݶ˿ڵ������˿�
	uint16_t	u16UpnpWebPort; 	//�̶�ӳ��ģʽ��, Web�˿ڵ������˿�
	uint16_t	u16UpnpRtspPort;	//�̶�ӳ��ģʽ��, RTSP�˿ڵ������˿�
	uint16_t	u16UpnpDataPortS;	//���ݶ˿ڵ������˿� 0����û��ӳ��򲻳ɹ�
	uint16_t	u16UpnpWebPortS;	//Web�˿ڵ������˿� 0����û��ӳ��򲻳ɹ�
	uint16_t	u16UpnpRtspPortS;	//RTSP�˿ڵ������˿� 0����û��ӳ��򲻳ɹ�
	uint16_t	u16UpnpCmdPort;
	uint16_t	u16UpnpTalkPort; 
	uint16_t	u16UpnpJXJDataPort;
	uint16_t	u16UpnpCmdPortS;
	uint16_t	u16UpnpTalkPortS;
	uint16_t	u16UpnpJXJDataPortS;//JXJƽ̨���ݶ˿ڵ������˿�ӳ��״̬
	uint8_t		u8Res[20];

}IPNC_UPNP_CFG_S, *LPIPNC_UPNP_CFG_S;

//ddns��Ϣ
typedef struct _IPNC_DDNS_CFG_S_
{
	uint8_t		u8DDNSOpen;						//DDNS����
	uint8_t		u8DDNSType;						//0-dyndns 1-3322
	uint16_t	u16DDNSPort;						//DDNS�������˿�
	char		szDDNSAccount[IPNC_USER_NAME_LEN];	//DDNS ע����
	char		szDDNSUsr[IPNC_USER_NAME_LEN];		//�û�����
	char		szDDNSPsw[IPNC_PASS_WORD_LEN];		//�û�����	
	uint32_t	u32DDNSTimes;						//����ʱ��
}IPNC_DDNS_CFG_S, *LPIPNC_DDNS_CFG_S;

//PPPOE��Ϣ
typedef struct _IPNC_PPPOE_CFG_S_
{
	//uint8_t		u8PppoeOn;					//pppoe����
	//uint8_t		u8PppoeStatus;				//pppoe ����״̬0 û�в���1 ������2���ųɹ�
	char		pppoeUsr[IPNC_USER_NAME_LEN];	//pppoe�û���
	char		pppoePsw[IPNC_PASS_WORD_LEN];	//pppoe����
	char 		pppoeIp[IPNC_IP_ADDR_LEN];		//pppoe��ȡ��ip
	//uint32_t	u32PppoeTimes;					//pppoe����ʱ��
	uint8_t		u8Res[32];
}IPNC_PPPOE_CFG_S, *LPIPNC_PPPOE_CFG_S;

//COMM����Ϣ
typedef struct _IPNC_COMM_CFG_S_
{
	uint32_t	u32BaudRate;	//������(bps)��0-50��1-75��2-110��3-150��4-300��
								//s5-600��6-1200��7-2400��8-4800��9-9600��
								//10-19200��11-38400��12-57600��13-76800��14-115.2k 
 	uint8_t     u8DataBit;		//����λ��0-5λ��1-6λ��2-7λ��3-8λ
 	uint8_t     u8StopBit;		//ֹͣλ��0-1λ��1-2λ
  	uint8_t     u8Parity;		//�Ƿ�У�飺0-��У�飬1-��У�飬2-żУ��
  	uint8_t     u8Flowcontrol;	//�Ƿ����أ�0-�ޣ�1-������,2-Ӳ����
  	uint32_t	u32BaudMask;
  	uint8_t		u8Res[4];
}IPNC_COMM_CFG_S, *LPIPNC_COMM_CFG_S;

//��̨��Ϣ
typedef struct _IPNC_PTZ_CFG_S_
{
	uint8_t		u8ProtocalType;	// 0 pelco-d 1 pelco-p
	uint8_t		u8PtzAddr;		//0-255
	uint8_t		u8Res[6];
}IPNC_PTZ_CFG_S, *LPIPNC_PTZ_CFG_S;

//��Ƶ��Ϣ
typedef struct _IPNC_AUDIO_CFG_S_
{
	//uint32_t	u32Size;
	uint32_t	u32SampleRate;	//������ 8k 80000
	uint8_t		u8Open;			//�Ƿ�����Ƶ
	uint8_t		u8AEncType;		//0--PCM 1--G711A 2-G711U 3--G726
	uint8_t		u8Type;      	//0--mic������� 1--������
	uint8_t		u8Res[5];
}IPNC_AUDIO_CFG_S, *LPIPNC_AUDIO_CFG_S;

//��Ƶ��Ϣ///////////////////////
//ץ�Ĳ�����Ϣ
typedef struct _IPNC_DEV_CAPTURE_CFG_S_
{
  uint16_t	u16Width;		//ץ��ͼƬ���
  uint16_t	u16Height;		//ץ��ͼƬ�߶�
  uint8_t	u8VideoEncType;	//��Ƶ�����ʽ 2--JPEG �̶�ֵ
  uint8_t	u8Quilty;		//ץ������ 
  uint8_t	u8Res[14];	
  
}IPNC_DEV_CAPTURE_CFG_S, *LPIPNC_DEV_CAPTURE_CFG_S;

//��Ƶ�������	
typedef struct _IPNC_DEV_VENC_CFG_S_
{
  uint16_t	u16Width;		//��Ƶ������
  uint16_t	u16Height;		//��Ƶ����߶�

  uint8_t	u8VideoEncType;	//��Ƶ�����ʽ0--h264 1--MJPEG 2--JPEG	
  uint8_t	u8PicQuilty;	//��������0-��ã�1-�κã�2-�Ϻã�3-һ�㣬4-�ϲ5-��	
  uint8_t	u8Gop;			//I֡���1-200
  uint8_t	u8FlowType;		//�������� 0--������1--������
  uint32_t	u32BitrateRate;	//�������� 32kbps-16Mkbps
  uint8_t	u8FrameRate;	//����֡��1-25/30
  uint8_t	u8Res[7];
  
}IPNC_DEV_VENC_CFG_S, *LPIPNC_DEV_VENC_CFG_S;

//��Ƶ�ڵ�����
typedef struct _IPNC_DEV_VMASK_CFG_S_
{
  uint8_t		u8Open;							//--1.������Ƶ�ڵ�0--������Ƶ�ڵ�
  uint8_t		u8Res1[3];
  IPNC_RECT_S	struArea[IPNC_VMASK_REG_NUM];	//��Ƶ�ڵ�����
  uint8_t		u8Res2[8];
}IPNC_DEV_VMASK_CFG_S, *LPIPNC_DEV_VMASK_CFG_S;

//����5����Ϣ��ע
typedef struct _IPNC_DEV_OSD_LABEL_CFG_S_
{
	uint32_t		u32EnableLabel[IPNC_MAX_OSD_LABEL_NUM];					//--1 ��ʾ����osd 0--���ر���osd
	char		szLabelName[IPNC_MAX_OSD_LABEL_NUM][IPNC_USER_NAME_LEN];			//��ע����
	uint32_t		u32ColorValidFlag[IPNC_MAX_OSD_LABEL_NUM];				// 0:ʹ��u3Osdcolor,ʹ��u32LabelColor
  	uint32_t		u32OsdColor[IPNC_MAX_OSD_LABEL_NUM];						//----0 ---black
  																		//---1---white
  																		//---2---blue
  																		//---3---red
  																		//---4---inv
	IPNC_POINT_S 	struLabelOrg[IPNC_MAX_OSD_LABEL_NUM];						//��עosdλ��
	uint32_t		u32LabelColor[IPNC_MAX_OSD_LABEL_NUM];					// ��ע��ɫ,��ɫ:0-7bit, ��ɫ:8-15bit,��ɫ:16-23bit
}IPNC_DEV_OSD_LABEL_CFG_S, *LPIPNC_DEV_OSD_LABEL_CFG_S;


//osd�˵����� �ݲ�֧���û��Զ���osd �˵�
typedef struct _IPNC_DEV_OSD_CFG_S_
{
  uint8_t		u8EnableTitleOsd;	//--1 ��ʾ����osd 0--���ر���osd
  uint8_t		u8EnableTimeOsd;	//--1 ��ʾʱ��osd 0--����ʱ��osd
  uint8_t		u8DispWeek;			//--1 ��ʾ����0--��������
  uint8_t		u8EnableBitrateOsd;	//--1��ʾ����osd  0--��������osd
  uint8_t		u8TimeOsdType;		//--ʱ����ʾ����
  									//--0 YYYY-MM-DD HH:MM:SS
  									//--1 MM-DD-YYYY HH:MM:SS
  									//--2 DD-MM-YYYY HH:MM:SS
									//--3 YYYY/MM/DD HH:MM:SS
									//--4 MM/DD/YYYY HH:MM:SS
									//--5 DD/MM/YYYY HH:MM:SS
									
  uint8_t		u8HourOsdType;		//--0 24 hour --1 12 hour
  uint8_t		u8OsdColor;			//----0 ---black
  									//---1---white
  									//---2---blue
  									//---3---yellow
  uint8_t		u8EnableUsrOsd; //bit0 ʹ�ܵ�һ���û��˵�
  								//bit1 ʹ�ܵڶ����û��˵�

  IPNC_POINT_S 	struTimeOrg;	//ʱ��osdλ��
  IPNC_POINT_S 	struTitleOrg;	//����osdλ��
  IPNC_POINT_S 	struUsrOrg[2];	//�û��Զ���osdλ��
  char			szChnName[IPNC_USER_NAME_LEN];		 	//ͨ������
  char			szUsrOsdInfo[2][IPNC_USER_NAME_LEN];	//�û��Զ���osd��Ϣ
  
  uint32_t		u32TimeColor;		// ʱ����ɫ,��ɫ:0-7bit, ��ɫ:8-15bit,��ɫ:16-23bit
  uint32_t		u32ChnColor;		// ͨ����ɫ,��ɫ:0-7bit, ��ɫ:8-15bit,��ɫ:16-23bit
  uint8_t		u8ColorValidFlag;	// 0:ʹ��u8Osdcolor��ʼ��u32TimeColor��u32ChnColorֵ, 1:ֱ��ʹ��u32TimeColor��u32ChnColorֵ
  uint8_t		u8Res[7];
}IPNC_DEV_OSD_CFG_S, *LPIPNC_DEV_OSD_CFG_S;

//����ȼ�
typedef enum _IPNC_DEV_H264_ENCODE_LEVEL_E_
{
	IPNC_H264_HIGH = 0,
	IPNC_H264_MAIN,
	IPNC_H264_BASELINE,
}IPNC_DEV_H264_ENCODE_LEVEL_E;


//ͼ���������
typedef struct _IPNC_DEV_IMA_PARA_S_
{
	uint8_t	u8Value;			//����ֵ
	uint8_t	u8Default;			//ȱʡ����ֵ
	uint8_t	u8Step;				//����ֵ����ֵ
	uint8_t	u8Res;
}IPNC_DEV_IMA_PARA_S;

//��Ƶ�����������Ͷ���
typedef enum _IPNC_DEV_IMA_MASK_E_
{
	IPNC_VCT_IMA_BRIGHTNESS 	= 0x00000001,
	IPNC_VCT_IMA_CONTRAST		= 0x00000002,
	IPNC_VCT_IMA_SATURATION 	= 0x00000004,
	IPNC_VCT_IMA_HUE		  	= 0x00000008,
	IPNC_VCT_IMA_GAMMA			= 0x00000010,
	IPNC_VCT_IMA_SHARPNESS		= 0x00000020,
	IPNC_VCT_IMA_BLUE			= 0x00000040,
	IPNC_VCT_IMA_RED			= 0x00000080,
	IPNC_VCT_IMA_ALL			= 0xFFFFFFFF,
}IPNC_DEV_IMA_MASK_E;

//ͼ����Ϣ
typedef struct _IPNC_DEV_IMA_CFG_S_
{	
/*��Ч֧�ֵĲ������ò�������ʱ����Ч
�ڻ�ȡ��ʱ����Ч�������ж��豸�Ƿ�֧�ָò���*/	
	IPNC_DEV_IMA_MASK_E	eSuppMask;
/*������Ч�Ĳ������ò�����ȡʱ����Ч
   �����õ�ʱ����Ч������ָ���������õĲ���*/	
	IPNC_DEV_IMA_MASK_E	eSetMask;	

	IPNC_DEV_IMA_PARA_S	struBrightness;	//����
	IPNC_DEV_IMA_PARA_S	struContrast;	//�Աȶ�
	IPNC_DEV_IMA_PARA_S	struSaturation;	//���Ͷ�
	IPNC_DEV_IMA_PARA_S	struHue;		//ɫ��
	IPNC_DEV_IMA_PARA_S	struGamma;		//٤��gamma
	IPNC_DEV_IMA_PARA_S	struSharpness;	//���sharpness
	IPNC_DEV_IMA_PARA_S	struRed;		//red
	IPNC_DEV_IMA_PARA_S	struBlue;		//blue	
	IPNC_DEV_IMA_PARA_S	struRes[24];
}IPNC_DEV_IMA_CFG_S, *LPIPNC_DEV_IMA_CFG_S;

//��Ƶ��Ϣ
typedef struct _IPNC_DEV_VIDEO_CFG_S_
{
	uint32_t				u32Size;	
	IPNC_DEV_OSD_CFG_S 		struOsd;
	IPNC_DEV_VMASK_CFG_S	struVMask;
	IPNC_DEV_VENC_CFG_S 	struMainVenc;
	IPNC_DEV_VENC_CFG_S 	struSubVenc;
	IPNC_DEV_CAPTURE_CFG_S  struCapture;
	IPNC_DEV_IMA_CFG_S		struIma;
	IPNC_DEV_H264_ENCODE_LEVEL_E	eEncodeLevel;	// 0:high profile, 1:main profile, 2:baseline
	uint8_t   u8PalStand;		//��ʽ1 pal 0 ntfc
	uint8_t					u8Res[27];
}IPNC_DEV_VIDEO_CFG_S, *LPIPNC_DEV_VIDEO_CFG_S;

//�ƶ������Ϣ
typedef struct _IPNC_DEV_MD_CFG_S_
{
  uint32_t			u32Size;
  uint8_t			u8Enable;	//�Ƿ����ƶ���� 0--�ر� 1--����			
  uint8_t			u8Level;	//��������� 0--�ܸ� 1--�� 2--�� 3--�� 4--�ܵ�	
  uint8_t			u8Res1[2];
  IPNC_RECT_S		struRect[IPNC_VMD_REG_NUM];		//�������
  IPNC_SEGMENT_S	struSeg[IPNC_MAX_SEG_NUM][8];  	//0--ÿ��1--������ 2--����һ7--������	
  IPNC_LINKACT_S	struLinkAct;					//�ƶ����������Ϣ
  uint32_t			u32DetectInterval;				//�����ʱ��
  uint8_t			u8Res2[12];
}IPNC_DEV_MD_CFG_S, *LPIPNC_DEV_MD_CFG_S;

//̽ͷ������Ϣ
typedef struct _IPNC_DEV_DI_CFG_S_
{
  uint32_t			u32Size;
  char				chDiName[IPNC_USER_NAME_LEN];//di̽ͷ����
  uint8_t			u8Enable;					 //�Ƿ���di������� 0--������ 1--����
  uint8_t			u8DiType;					 //0--����̽ͷ1--����̽ͷ
  uint8_t			u8Res1[2];
  IPNC_SEGMENT_S	struSeg[IPNC_MAX_SEG_NUM][8]; 	//0--ÿ��1--������ 2--����һ7--������	
  IPNC_LINKACT_S	struLinkAct;					//di����������Ϣ
  uint32_t			u32DetectInterval;				//�����ʱ��
  uint8_t			u8Res2[12];
}IPNC_DEV_DI_CFG_S, *LPIPNC_DEV_DI_CFG_S;

//3A����
//--3A�����������Ͷ���
typedef enum _IPNC_DEV_3A_MASK_E_
{	//��Ȧ
	IPNC_VCT_3A_AUTOIRIS	= 0x00000001,//�Զ���Ȧ
	IPNC_VCT_3A_IRISLEVEL	= 0X00000002,//��Ȧ��ƽ
	//�۽�
	IPNC_VCT_3A_AUTOFOCUS	= 0X00000004,//�Զ��۽�
	IPNC_VCT_3A_FOCUSLEVEL	= 0X00000008,//����
	IPNC_VCT_3A_MINFOCUSLEN = 0X00000010,//������С�۽�����		
	//�䱶
	IPNC_VCT_3A_ZOOMSPEED	 = 0X00000020,//�䱶�ٶ�
	IPNC_VCT_3A_AUTOPTZSPEED = 0X00000040,//�����������
	//��ƽ����
	IPNC_VCT_3A_AUTOALC		= 0X00000080,//�Զ���ƽ����
	IPNC_VCT_3A_ALCLEVEL	= 0X00000100, //��ƽ����ֵ
	//��ת��
	IPNC_VCT_3A_CTB			= 0X00000200,//��ת��
	IPNC_VCT_3A_CTBLEVEL	= 0X00000400,//��ת�ڷ�ֵ������ת��Ϊ�Զ�ʱ��Ч
	//����
	IPNC_VCT_3A_MIRROR		= 0X00000800,//����
	IPNC_VCT_3A_FLIP		= 0X00001000,//��ת
	IPNC_VCT_3A_AUTOFLIP	= 0X00002000,//�Զ���ת
	IPNC_VCT_3A_PWDFREQ		= 0X00004000,//����Ƶ��1
	//����
	IPNC_VCT_3A_IREXIST		= 0X00008000,//�Ƿ��к���
	IPNC_VCT_3A_IRCFMODE	= 0X00010000,//IRCFģʽ
	IPNC_VCT_3A_IRLIGHTTYPE	= 0X00020000,//���������
	//
	IPNC_VCT_3A_WDR 		= 0X00040000,//�Ƿ��п�̬
	IPNC_VCT_3A_WDRLEVEL	= 0X00080000,//��̬��ֵ
	IPNC_VCT_3A_LOWILLUM	= 0X00100000,//���ն�
	IPNC_VCT_3A_IMAGEMODE	= 0X00200000,//ͼ��ģʽ
	//����
	IPNC_VCT_3A_SCENE		=  0X00400000,//����
	
	IPNC_VCT_3A_ALL		  	= 0xFFFFFFFF,
}IPNC_DEV_3A_MASK_E;
typedef struct _IPNC_DEV_3A_PARA_S_
{
	uint8_t	u8Value;		//����ֵ
	uint8_t	u8Default;		//ȱʡ����ֵ
	uint8_t	u8Step;			//����ֵ����ֵ
	uint8_t	u8Res;
}IPNC_DEV_3A_PARA_S;

typedef struct _IPNC_DEV_3A_CFG_S_
{
	uint32_t			u32Size;
/*��Ч֧�ֵĲ������ò�������ʱ����Ч
�ڻ�ȡ��ʱ����Ч�������ж��豸�Ƿ�֧�ָò���*/	
	IPNC_DEV_3A_MASK_E	eSuppMask;
/*������Ч�Ĳ������ò�����ȡʱ����Ч
   �����õ�ʱ����Ч������ָ���������õĲ���*/	
	IPNC_DEV_3A_MASK_E	eSetMask;	
	IPNC_DEV_3A_PARA_S	struFlip;			//��תͼ�����·�ת
	IPNC_DEV_3A_PARA_S	struMirror;			//����ͼ�����ҷ�ת
	IPNC_DEV_3A_PARA_S	struPwdFreq;		//��ԴƵ��
	IPNC_DEV_3A_PARA_S	struScene;			//����,0:�Զ� 1:����2:����
	//IPNC_DEV_3A_PARA_S	struIrcfMode;		//����ģʽ��0:�Զ���1:���죬2:����,3:��ʱģʽ
	IPNC_DEV_3A_PARA_S	struShutterSpeed;	//���ӿ��� 0-8  0���Զ����� 1��
											//1/25S�� 2��1/50S�� 3��1/100S�� 4��1/500S�� 5��1/1000S�� 
											//6��1/2000S�� 7��1/5000S�� 8��1/10000S
	IPNC_DEV_3A_PARA_S	struRes[26];
}IPNC_DEV_3A_CFG_S, *LPIPNC_DEV_3A_CFG_S;

/*������Ӧ��*/
typedef struct _IPNC_NET_SEARCH_RES_S_
{
	struct sockaddr_in	addrClient;
	
	uint8_t	u8SerialId[IPNC_SERIALNO_LEN];
	uint32_t	u32SoftVer;
	uint16_t	u16DevType;
	uint16_t	u16DevPort;
	uint32_t	u32DevIp;
	uint8_t	u8MacAddr[IPNC_MAC_ADDR_LEN];
	uint8_t	u8Dns;
	uint8_t	u8DHCP;	
	uint32_t	u32DevIpMask;
	uint32_t	u32DevGwAddr;
	uint32_t	u32DevDns1;
	uint32_t	u32DevDns2;

	/* ��ͬЭ���˽�а�*/
	uint8_t   szPriData[1024];
}IPNC_NET_SEARCH_RES_S, *LPIPNC_NET_SEARCH_RES_S; 

//�������ð�
typedef struct _IPNC_NET_SEARCH_CFG_REQ_S
{	
	char szUsrName[IPNC_USER_NAME_LEN];
	char szPsw[IPNC_PASS_WORD_LEN];
	
	uint8_t	u8SerialId[IPNC_SERIALNO_LEN];
	uint32_t	u32SoftVer;
	uint16_t	u16DevType;
	uint16_t	u16DevPort;
	uint32_t	u32DevIp;
	uint8_t	u8MacAddr[IPNC_MAC_ADDR_LEN];
	uint8_t	u8Dns;
	uint8_t	u8DHCP; 
	uint32_t	u32DevIpMask;
	uint32_t	u32DevGwAddr;
	uint32_t	u32DevDns1;
	uint32_t	u32DevDns2;
	
	/* ��ͬЭ���˽�а�*/
	uint8_t   szPriData[1024];
}IPNC_NET_SEARCH_CFG_REQ_S, *LPIPNC_NET_SEARCH_CFG_REQ_S; 

#if 0
//�����ṹ����Ϣ
/*����������Ӧ��*/
typedef struct _IPNC_NET_SEARCH_RES_S_
{	
	struct sockaddr_in	addrClient;
	uint32_t 	u32Capability0;
	uint32_t 	u32Capability1;
	uint32_t 	u32Capability2;
	uint8_t		u8MainDevType;
	uint8_t		u8SubDevType;
	uint16_t  	u16PlateformCap;  //�ܹ�֧��ƽ̨��Ӧ�ò����
	uint32_t  	u32UpTime;        //����ʱ��
	
	uint8_t		u8SerialId[IPNC_SERIALNO_LEN];
	uint32_t	u32SoftVer;
	uint16_t	u16DevType;
	uint16_t	u16DevPort;
	uint32_t	u32DevIp;
	uint8_t		u8MacAddr[IPNC_MAC_ADDR_LEN];
	uint8_t		u8Dns;
	uint8_t		u8DHCP;	
	uint32_t	u32DevIpMask;
	uint32_t	u32DevGwAddr;
	uint32_t	u32DevDns1;
	uint32_t	u32DevDns2;
	/*uint32_t 	u32Capability0;
	uint32_t 	u32Capability1;
	uint32_t 	u32Capability2;
	uint8_t		u8MainDevType;
	uint8_t		u8SubDevType;
	uint16_t  	u16PlateformCap;  //�ܹ�֧��ƽ̨��Ӧ�ò����
	uint32_t  	u32UpTime;        //����ʱ��*/

}IPNC_NET_SEARCH_RES_S, *LPIPNC_NET_SEARCH_RES_S; 

//�������ð�
typedef struct _IPNC_NET_SEARCH_CFG_REQ_S
{	
	uint32_t	u32CliMultiIp;
	uint16_t	u16CliMultiPort;
	uint8_t		u8Res[2];
	uint32_t 	u32Capability0;
	uint32_t 	u32Capability1;
	uint32_t 	u32Capability2;	  //ʵ�ʿ���ƽ̨,syscfg��ȡ
	uint8_t		u8MainDevType;
	uint8_t		u8SubDevType;
	uint16_t  	u16PlateformCap;  //�ܹ�֧��ƽ̨��Ӧ�ò����
	uint32_t  	u32UpTime;        
	char 		szUsrName[IPNC_USER_NAME_LEN];
	char 		szPsw[IPNC_PASS_WORD_LEN];
	uint8_t		u8SerialId[IPNC_SERIALNO_LEN];
	uint32_t	u32SoftVer;
	uint16_t	u16DevType;
	uint16_t	u16DevPort;
	uint32_t	u32DevIp;
	uint8_t		u8MacAddr[IPNC_MAC_ADDR_LEN];
	uint8_t		u8Dns;
	uint8_t		u8DHCP;	
	uint32_t	u32DevIpMask;
	uint32_t	u32DevGwAddr;
	uint32_t	u32DevDns1;
	uint32_t	u32DevDns2;
	/*uint32_t 	u32Capability0;
	uint32_t 	u32Capability1;
	uint32_t 	u32Capability2;	  //ʵ�ʿ���ƽ̨,syscfg��ȡ
	uint8_t		u8MainDevType;
	uint8_t		u8SubDevType;
	uint16_t  	u16PlateformCap;  //�ܹ�֧��ƽ̨��Ӧ�ò����
	uint32_t  	u32UpTime;        //����ʱ��*/
}IPNC_NET_SEARCH_CFG_REQ_S, *LPIPNC_NET_SEARCH_CFG_REQ_S; 
#endif

//��ʱ����ģʽ����
typedef struct _IPNC_DEV_IRCFMODE_CFG_S_
{
	uint32_t 			u32Size;
	uint8_t			u8Mode;			// 0:auto 1:day 2:night 3:timer
	IPNC_SEGMENT_S	struSeg[IPNC_MAX_IRCF_SEG_NUM][8];  //0--ÿ��1--������ 2--����һ7--������	
	uint8_t			u8Res1[32];
}IPNC_DEV_IRCFMODE_CFG_S;

// ==========================================================
// ����������
//
#define IPNC_BALL_ONTIME_NUM 8
// ��������
typedef struct _IPNC_BALL_ALARM_PARAM_S_
{
	int nAlarmActionIndex;		// ��������
	int nDurationSec;			// ��������ʱ��
	uint8_t byRes[32];
}IPNC_BALL_ALARM_PARAM_S, *LPIPNC_BALL_ALARM_PARAM_S;
// ��ʱ����
typedef struct _IPNC_BALL_ONTIME_ACTION_S_
{
	uint8_t byBeginHour;					// ��ʼСʱ
	uint8_t byBeginMin;					// ��ʼ����
	uint8_t byEndHour;					// ����Сʱ
	uint8_t byEndMin;						// ��������
	int nActionIndex;
	uint8_t byRes[12];
}IPNC_BALL_ONTIME_ACTION_S, *LPIPNC_BALL_ONTIME_ACTION_S;
// ��ʱ����
typedef struct _IPNC_BALL_ONTIME_PARAM_S_
{
	IPNC_BALL_ONTIME_ACTION_S struOntimeAction[IPNC_BALL_ONTIME_NUM];
	uint8_t byRes[32];
}IPNC_BALL_ONTIME_PARAM_S, *LPIPNC_BALL_ONTIME_PARAM_S;
// Ѳ����
typedef struct _IPNC_BALL_CRUISE_NODE_S_
{
	uint8_t byCruisePresetEnable;		// �Ƿ�ʹ�����Ԥ�õ� 
	uint8_t byCruisePresetSec;		// ͣ��ʱ��(��)
	uint8_t byCruisePresetSpeed;		// �ƶ��ٶ�
	uint8_t byRes[8];
}IPNC_BALL_CRUISE_NODE_S, *LPIPNC_BALL_CRUISE_NODE_S;
// Ѳ������
#define IPNC_BALL_CRUISE_NUM 16
#define IPNC_BALL_CRUISE_NAME_LEN 32
typedef struct _IPNC_BALL_CRUISE_PARAM_S_
{
	IPNC_BALL_CRUISE_NODE_S struCruiseNode[IPNC_BALL_CRUISE_NUM];
	IPNC_BALL_CRUISE_NODE_S struCruiseResNodE[8];
	/* begin:	add by hjl	2013/1/7*/
	char  crz_name[IPNC_BALL_CRUISE_NAME_LEN];	//Ѳ��·����
	unsigned int crz_no;						//Ѳ��·����
	unsigned int crz_enable;					//�Ƿ�ʹ������·��
	/* end:	add by hjl	2013/1/7*/
	uint8_t byRes[64-40];
}IPNC_BALL_CRUISE_PARAM_S, *LPIPNC_BALL_CRUISE_PARAM_S;
// ��������
#define DAY_NIGHT_MASK		(1<<0)
#define IR_MASK				(1<<1)
#define FLIP_MASK			(1<<2)
#define ELEC_ZOOM_MASK		(1<<3)
#define FOCUS_MASK			(1<<4)
#define IRIS_MASK			(1<<5)
#define BLC_MASK			(1<<6)
#define ZOOM_DISPLAY_MASK	(1<<7)
#define FRAME_NOISE_MASK	(1<<8)
#define ZOOM_SPEED_MASK		(1<<9)
#define WB_MASK				(1<<10)
#define WDR_MASK			(1<<11)
#define ZOOM_MASK			(1<<12)
typedef struct _IPNC_BALL_SETTING_PARAM_S_
{
	uint32_t dwMask;				// 0: ��֧��,1:֧��
								// bit0:��ҹģʽ
								// bit1:����ģʽ
								// bit2:��ת
								// bit3:���ӱ䱶
								// bit4:�۽�
								// bit5:��Ȧ
								// bit6:���ⲹ��
								// bit7:�䱶��ʾ
								// bit8:֡����
								// bit9:�䱶�ٶ�
								// bit10:��ƽ��
								// bit11:��̬
	IPNC_BALL_CRUISE_PARAM_S struCruiseParam;
	uint8_t byAutoScanSpeed;			// �Զ�ɨ���ٶ�
	uint8_t byABScanSpeed;			// ABɨ���ٶ�
	int nIdleActionIndex;			// ���ö���
	uint8_t byIdleSec;				// ��������
	uint8_t byIRISMode;				// ��Ȧģʽ:0:�ֶ�,1:�Զ�
	uint8_t byAutoFlip;				// �Զ���ת:0:�ر�,1:��
	uint8_t byDayNightMode;			//0:����ģʽ,1:ҹ��ģʽ,2:�Զ�ģʽ,3:��ʱģʽ
	uint8_t byIRMode;					// Զ�����л�ģʽ:0:�Զ��л�Զ����,1:ͬʱ����Զ����
	uint8_t byBLCMode;				// ���ⲹ��:0:�ر�,1:��
	uint8_t byFrameNoise;				// ����:0:�ر�,1:��
	uint8_t byZoomDisplay;			// �䱶��ʾ:0:�ر�,1:��
	uint8_t byZoomSpeed;				// �䱶�ٶ�:0:����,1:����,2:����
	uint8_t byWBMode;					// ��ƽ��:0:����,1:���� ,2:�Զ�,3:�ֶ�
	uint8_t byWDRMode;				// ��̬:0:�ر�,1:��
	uint8_t byAutoFocus;				// �Զ��۽�:0:�ر�,1:��
	uint8_t byRes[32];
}IPNC_BALL_SETTING_PARAM_S, *LPIPNC_BALL_SETTING_PARAM_S;
// ����������
typedef struct _IPNC_BALL_RUN_PARAM_
{
	uint32_t dwSize;
	IPNC_BALL_ALARM_PARAM_S struAlarmParam;
	IPNC_BALL_ONTIME_PARAM_S struOntimeParam;
	IPNC_BALL_SETTING_PARAM_S struSettingParam;
	uint8_t byRes[64];
}IPNC_BALL_RUN_PARAM_S, *LPIPNC_BALL_RUN_PARAM_S;

//Ԥ�õ�
#define IPNC_MAX_PRESET_PORT_SIZE 	255
#define IPNC_MAX_PRESET_NAME_LEN		64
typedef struct _IPNC_PRESET_POINT_S
{
	uint8_t		name[IPNC_MAX_PRESET_NAME_LEN];	//Ԥ�õ�����
	uint32_t	preset;							//Ԥ�õ�ţ�
}IPNC_PRESET_POINT_S, *LPIPNC_PRESET_POINT_S;

typedef struct _IPNC_DEV_PP_SET_CFG_S
{
	uint32_t	u32Size;
	uint32_t	pp_count;								//Ԥ�õ�����
	IPNC_PRESET_POINT_S pp[IPNC_MAX_PRESET_PORT_SIZE];	//Ԥ�õ㼯��
}IPNC_DEV_PP_SET_CFG_S;

//===========================================================================
//��̨���Ʋ����ṹ��
/* ��Ϊ��Ҫ��ǹ����PTZ���������,���Խṹ��Ĵ�С������֮ǰ�Ĵ�С����һ��*/
#pragma pack(2)
typedef struct _IPNC_PTZ_CTRL_S_
{
	uint16_t	u16PtzCmd;			//��̨��������

	union
	{
		struct
		{
			uint8_t	u8Chn;			//��̨ͨ����
			uint8_t	u8Speed;		//�ٶ�
			uint8_t	u8PresetNo;
			uint8_t	u8Res[3];
		}struPreset;
		struct 
		{
			uint8_t	u8CruisePresetNo;
			uint8_t u8CruisePresetEnable;
			uint8_t	u8CruisePresetSec;
			uint8_t	u8CruisePresetSpeed;
		}struCruise;
		struct
		{
			uint8_t u8SetVerticalPos;	// �Ƿ����ô�ֱλ��
			uint8_t	u8Speed;
		}struAutoScan;
		struct
		{
			uint8_t u8SetVerticalPos;	// �Ƿ����ô�ֱλ��
			uint8_t	u8Speed;
		}struABScan;
		struct
		{
			uint8_t	u8IdleActionIndex;
			uint8_t	u8IdleSec;
		}struIdleAction;
		struct
		{
			uint8_t	u8OntimeIndex;		// 1-8��ĳ����ʱ��
			uint8_t	u8OntimeActionIndex;	// ��ʱ����������
			uint8_t	u8BeginHour;
			uint8_t	u8BeginMin;			
			uint8_t	u8EndHour;
			uint8_t	u8EndMin;
		}struOntimeAction;
		struct
		{
			uint8_t	u8AlarmTypeIndex;		// ��һ�ֱ���
			uint8_t	u8AlarmActionIndex;		// ��������������
			uint8_t u8AlarmDurationSec;
		}struAlarm;
		struct
		{
			unsigned short res;
			int s32XCoordinate;		//(x(fact)-x(total))*10000/x(total)
			int s32YCoordinate;		//(y(total)-y(fact))*10000/y(total)
			int s32Amplify;			//��Ϊ�Ŵ󣬸�Ϊ��С(xwide(total)/xwide(fact)>(ywide(total)/ywide(fact)))?xwide(total)/xwide(fact)*10:ywide(total)/ywide(fact)*10
		}stru3DControl;
		struct
		{
			unsigned char	u8Left;
			unsigned char 	u8Top;
			unsigned char	u8Right;
			unsigned char 	u8Bottom;
		}stru3DRectCenter;			//left,top,right,bottomΪ�ٷֱ����꣬��Χ0-100�� �� left>=right ��bottom<=topʱ��Ϊ��ѡ��С�����������Ϊ��ѡ�Ŵ�
		struct
		{
			unsigned char	u8XCoordinate;
			unsigned char 	u8YCoordinate;
		}stru3DPointCenter;					//x,yΪ�ٷֱ����꣬��Χ0-100 
		uint8_t	u8OpenOrClose;				// 0:close, 1:open
		uint8_t u8WorkMode;					// 0:�ֶ�,1:�Զ�
		uint8_t u8IRMode;					// 0:Զ�����Զ��л�,1:Զ����ͬʱ����
		uint8_t u8DayNightMode;				// 0:����ģʽ,1:ҹ��ģʽ,2:�Զ�ģʽ
		uint8_t u8WBMode;					// 0 ����,1 ���� ,2 �Զ�,3 �ֶ�
		uint8_t u8ZoomSpeed;				// 0 ����, 1 ����, 2 ����
		uint8_t u8Bright;					// ����
		uint8_t u8Contrast;					// �Աȶ�
		uint8_t u8Saturation;				// ���Ͷ�
		uint8_t u8Sharpness;				// ���
		uint8_t u8Red;						// ��ɫ
		uint8_t u8Blue;						// ��ɫ
		unsigned char u8Shutter;			// ���ӿ����ٶ�
	};

}IPNC_PTZ_CTRL_S, *LPIPNC_PTZ_CTRL_S;
#pragma pack()

typedef struct _IPNC_DEV_JXJ_PLATFORM_CFG_S_
{
	uint32_t	u32Size;
	char 		szPuId[IPNC_USER_NAME_LEN];
	char		szCmsIp[IPNC_IP_ADDR_LEN];
	uint16_t	u16CmsPort;
	uint8_t		u8Enable;
	uint8_t		u8ProtocolType;
	uint8_t		u8SyncTimeEnable;
	uint8_t 	u8Res1[61];
}IPNC_DEV_JXJ_PLATFORM_CFG_S;

//===========================================================================
typedef struct _IPNC_DEV_REC_STRC_S_
{
	uint32_t	u32Size;		
	uint8_t		u8OverWrite;	//0 ������1 ����
	uint8_t		u8RecStream;	//0 ������¼��1 ������¼��
	uint8_t		u8PreRecSecs;	//Ԥ¼ʱ��(��)
	uint8_t		u8SaveMode;		//����ģʽ
	uint8_t		u8Enable;		// �Ƿ���¼����
	uint8_t		u8RecType;		// ¼�����ͣ� 0:����¼�� 1:��ʱ¼��2:����¼��,3:��ʱ&����
	uint8_t		u8Res[2];
	
	//��ʱ¼�����
	IPNC_SEGMENT_S	struTimerSeg[IPNC_MAX_SEG_NUM][8]; //0--ÿ��1--������ 2--����һ7--������	

	uint8_t		u8Rec[32];
}IPNC_DEV_REC_STRC_S, *LPIPNC_DEV_REC_STRC_S;
/***************************************************************************************************************/

/**********************************************�ͻ��˲���IPC������********************************************/
typedef enum _IPNC_CMD_TYPE_E_
{
	IPNC_CMD_DEV_CFG		= 0x2000,	//ϵͳ���� 		��Ӧ�ṹ��: IPNC_DEV_CFG_S
	IPNC_CMD_NET_CFG		= 0x2001,	//�������� 		��Ӧ�ṹ��: IPNC_NET_CFG_S
	IPNC_CMD_VIDEO_CFG		= 0x2002,	//��Ƶ���� 		��Ӧ�ṹ��: IPNC_DEV_VIDEO_CFG_S
	IPNC_CMD_OSD_CFG		= 0x2003,	//��Ƶosd		��Ӧ�ṹ��: IPNC_DEV_OSD_CFG_S
	IPNC_CMD_VMASK_CFG	= 0x2004,	//��Ƶ�ڵ�
	IPNC_CMD_VMD_CFG		= 0x2005,	//�ƶ����		��Ӧ�ṹ��: IPNC_DEV_MD_CFG_S
	IPNC_CMD_VMAIN_CFG	= 0x2006,	//��Ƶ������
	IPNC_CMD_VSUB_CFG		= 0x2007,	//��Ƶ������
	IPNC_CMD_VCAP_CFG		= 0x2008,	//��Ƶץ��
	IPNC_CMD_IMA_CFG		= 0x2009,	//ͼ�����
	IPNC_CMD_3A_CFG			= 0x200a,	//3A����		��Ӧ�ṹ��: IPNC_DEV_3A_CFG_S
	IPNC_CMD_AUDIO_CFG		= 0x200b,	//��Ƶ���� 		��Ӧ�ṹ��: IPNC_AUDIO_CFG_S
	IPNC_CMD_COMM_CFG		= 0x200c,	//������Ϣ 		��Ӧ�ṹ��: IPNC_COMM_CFG_S
	IPNC_CMD_FTP_CFG		= 0x200d,	//ftp�������� 	��Ӧ�ṹ��: IPNC_FTP_CFG_S
	IPNC_CMD_EMAIL_CFG		= 0x200e,	//email�������� ��Ӧ�ṹ��: IPNC_SMTP_CFG_S
	IPNC_CMD_DDNS_CFG		= 0x200f,	//ddns�������� 	��Ӧ�ṹ��: IPNC_DDNS_CFG_S
	IPNC_CMD_UPNP_CFG		= 0x2010,	//upnp�������� 	��Ӧ�ṹ��: IPNC_UPNP_CFG_S
	IPNC_CMD_NTP_CFG		= 0x2011,	//ntp�������� 	��Ӧ�ṹ��: IPNC_NTP_CFG_S
	//IPNC_CMD_TIME_CFG		= 0x2012,	//ʱ���������
	IPNC_CMD_USR_CFG		= 0x2013,	//�û��������� 	��Ӧ�ṹ��: IPNC_USER_CFG_S
	IPNC_CMD_DI_CFG			= 0x2014,	//�����������	��Ӧ�ṹ��: IPNC_DEV_DI_CFG_S
	IPNC_CMD_REC_CFG		= 0x2015,	//¼���������	��Ӧ�ṹ��: IPNC_DEV_REC_STRC_S
	//IPNC_CMD_GET_HD_CFG	= 0x2016,	//������Ϣ
	IPNC_CMD_PTZ_CFG		= 0x2017,	//��̨���� 		��Ӧ�ṹ��: IPNC_PTZ_CFG_S 
	//IPNC_CMD_STABLE_CFG   = 0x2018,   //�豸��Ϣ
	IPNC_CMD_BALL_CFG		= 0x2019,	//��������Ϣ	��Ӧ�ṹ��: IPNC_BALL_RUN_PARAM_S
	IPNC_CMD_PPPOE_CFG		= 0x201a,	//pppoe��������	��Ӧ�ṹ��: IPNC_PPPOE_CFG_S 
	IPNC_CMD_IRCFMODE_CFG 	= 0x201b,	//�������� 		��Ӧ�ṹ��: IPNC_DEV_IRCFMODE_CFG_S
	IPNC_CMD_PP_CFG 		= 0x201c,	//Ԥ�õ�PP����	��Ӧ�ṹ��: IPNC_DEV_PP_SET_CFG_S
	IPNC_CMD_TIME_CFG		= 0x201d,	//time���� 		��Ӧ�ṹ��: IPNC_TIME_S
	
	//IPNC_CMD_DEV_CAP				= 0x2031,	//�豸����ϸ��Ϣ
	IPNC_CMD_JXJ_PLATFORM_CFG		= 0x2032,	//JXJƽ̨������Ϣ ��Ӧ�ṹ��: IPNC_DEV_JXJ_PLATFORM_CFG_S
	//IPNC_CMD_ONVIF_CFG			= 0x2033,	//ONVIF������Ϣ
	//IPNC_CMD_HXHT_PLATFORM_CFG	= 0x2034,	//HXHTƽ̨������Ϣ
	//IPNC_CMD_GB28181_PLATFORM_CFG	= 0x2035,	//GB28181ƽ̨������Ϣ
	//IPNC_CMD_IRCFMODE_CFG 		= 0x2036,	//��������
	IPNC_CMD_OSD_LABEL_CFG			= 0x2037,	//osd��չ��ע  	  ��Ӧ�ṹ��: IPNC_DEV_OSD_LABEL_CFG_S

	IPNC_CMD_REBOOT				= 0x3000,
	IPNC_CMD_HALT					= 0x3001,
	IPNC_CMD_DEFAULT				= 0x3002,
}IPNC_CMD_TYPE_E;
/***************************************************************************************************************/

#endif

