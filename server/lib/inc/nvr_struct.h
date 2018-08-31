#ifndef __NVR_STRUCT_H__
#define __NVR_STRUCT_H__

#include <stdint.h>
#include <sys/time.h>


#define NVR_ETHERNET_NUM		2	// eth0 and wifi
#define NVR_MAX_USR_NUM			4	
#define NVR_MAX_CHANNEL_NUM		4
#define NVR_MAX_STREAM_NUM		2

#define NVR_SERIALNO_LEN		48	//���кų���
#define NVR_DEV_NAME_LEN		32	//�豸���Ƴ���
#define NVR_NAME_LEN			32	//���Ƴ���
#define NVR_USER_NAME_LEN		32	//�û�������	
#define NVR_PASS_WORD_LEN		32	//���볤��
#define NVR_PATH_LEN			64
#define NVR_IP_ADDR_LEN			64  //ip��ַ��������
#define NVR_MAC_ADDR_LEN		6	//mac��ַ����
#define NVR_MAX_EMAIL_LEN		64
#define NVR_VERSION_LEN			64

#define NVR_MAX_SUPPORT_DI		4	//���֧�ֱ����������
#define NVR_MAX_SUPPORT_DO		1	//���֧�ֱ����������
#define NVR_MAX_SUPPORT_RS232	0	//���֧��232����
#define NVR_MAX_SUPPORT_RS485	1	//���֧��485����
#define NVR_MAX_SUPPORT_COMM_NO 1 	//���֧�ִ��ڸ��� 0--485  1--232

#define NVR_VMASK_REG_NUM		4	//��Ƶ�ڵ�����
#define NVR_VMD_REG_NUM			4	//��Ƶ���������
#define NVR_MAX_SEG_NUM			4	//���ʱ���

#define NVR_MAX_SUPPORT_DISK	1	//֧����������
#define NVR_MAX_SUPPORT_PART	4	//֧����������

#define NVR_MAX_OSD_LABEL_NUM 	5	//osd��ע�������� 

#define NVR_MAX_SYS_IPC_MSG		32	//��Ϣ����֧�������Ϣ����

typedef enum _NVR_SYS_MSG_KEY_E_
{
	NVR_SMTP_KEY		= 5,
	NVR_FTP_KEY			= 6,
	NVR_FTP_UP_KEY		= 7,
	NVR_FTP_DOWN_KEY	= 8,
	NVR_COMM_KEY		= 8,
	
}NVR_SYS_MSG_KEY_E;

typedef enum _NVR_SYS_MSG_TYPE_E_
{
	NVR_SMTP_MSG		= 5,
	NVR_FTP_UP_MSG		= 6,
	NVR_FTP_DOWN_MSG	= 7,
	NVR_COMM_MSG		= 8,
	
}NVR_SYS_MSG_TYPE_E;

typedef enum _NVR_MACHINE_TYPE_E_
{
	NVR_MACHINE_J5000 = 0x0,
    NVR_MACHINE_J6000 = 0x1,
	NVR_MACHINE_BUTT  = 0x2,
	
}NVR_MACHINE_TYPE_E;

typedef enum _NVR_LANGUAGE_TYPE_E_
{
	NVR_LANGUAGE_ENG = 0x0,
	NVR_LANGUAGE_CHS,
	NVR_LANGUAGE_BUTT,
	
}NVR_LANGUAGE_TYPE_E;

typedef enum _NVR_ALARM_TYPE_E_
{
	NVR_ALARM_IN_HAPPEN 	= 0X1,
	NVR_ALARM_IN_DISAPPEAR 	= 0X2,
	NVR_MD_HAPPEN			= 0X3,
	NVR_MD_DISAPPEAR		= 0X4,
	
}NVR_ALARM_TYPE_E;

typedef enum _NVR_SAVE_TYPE_E_
{
	NVR_SAVE_LOCAL_DISK	= 0x0,
	NVR_SAVE_FTP		= 0x1,
	NVR_SAVE_SMTP		= 0x2,
	NVR_SAVE_HXHT		= 0x4,
	NVR_SAVE_ONVIF		= 0x8,
}NVR_SAVE_TYPE_E;

typedef enum _NVR_VIDEO_RESOLUTION_TYPE_E_
{
	NVR_VIDEO_D1		= 0x1,		//704*576	n��704*480
	NVR_VIDEO_HD1		= 0x2,		//704*288	n��704*240
	NVR_VIDEO_CIF		= 0x4,		//352*288	n��352*240
	NVR_VIDEO_WCIF		= 0x8,		//320*192
	
	NVR_VIDEO_UXGA		= 0x100,	//1600*1200
	NVR_VIDEO_SVGA		= 0x200,	//800*600
	NVR_VIDEO_VGA		= 0x400,	//640*480
	NVR_VIDEO_QVGA		= 0x800,	//320*240
	NVR_VIDEO_QQVGA		= 0x1000,	//160*112
	
	NVR_VIDEO_1080P		= 0x10000,	//1920*1080
	NVR_VIDEO_960		= 0x20000,	//1280*960
	NVR_VIDEO_720P		= 0x40000,	//1280*720
}NVR_VIDEO_RESOLUTION_TYPE_E;

typedef enum _NVR_VIDEO_REC_TYPE_E_
{
	NVR_REC_TIME_TYPE	= 0x1,
	NVR_REC_MD_TYPE		= 0x2,
	NVR_REC_DI_TYPE		= 0x4,
	NVR_REC_MANUAL_TYPE	= 0x8,
}NVR_VIDEO_REC_TYPE_E;
#if 0
typedef enum _NVR_FRAME_TYPE_E_
{
	VIDEO_FRAME_I = 0x7,
	VIDEO_FRAME_P = 0x8,
	VIDEO_FRAME_B = 0xB,
	AUDIO_FRAME_A = 0xA, 
}NVR_FRAME_TYPE_E;
#endif

#define UART_BARD_50	(1<<0)
#define UART_BARD_75	(1<<1)
#define UART_BARD_110	(1<<2)
#define UART_BARD_150	(1<<3)
#define UART_BARD_300	(1<<4)
#define UART_BARD_600	(1<<5)
#define UART_BARD_1200	(1<<6)
#define UART_BARD_2400	(1<<7)
#define UART_BARD_4800	(1<<8)
#define UART_BARD_9600	(1<<9)
#define UART_BARD_19200	(1<<10)
#define UART_BARD_38400	(1<<11)
#define UART_BARD_57600	(1<<12)
#define UART_BARD_76800	(1<<13)
#define UART_BARD_115200 (1<<14)


//============================================================
//======================1��ʱ��ṹ
typedef struct _NVR_TIME_S
{
	uint8_t		u8Year;						//��(��1900�꿪ʼ)
	uint8_t		u8Month;					//��1~12
	uint8_t		u8Day;						//��1~31
	uint8_t		u8WDay;						//������0 ����һ1.....
	uint8_t		u8Hour;						//ʱ0~23
	uint8_t		u8Minute;					//��0~59
	uint8_t		u8Second;					//��0~59
	uint8_t		u8Millisec;					//����(0~99)(�ٷ�֮һ��)
}NVR_TIME_S, *LPNVR_TIME_S;
//=======================2��ʱ��νṹ
typedef struct _NVR_SEGMENT_S
{
	uint32_t 	u8Open:8;		//����
	uint32_t	beginSec:24;	//��ʼʱ������ 3600*hour+60*min+sec
	uint32_t	u8Rsvd:8;		//����
	uint32_t	endSec:24;		//����ʱ������ 3600*hour+60*min+sec
}NVR_SEGMENT_S, *LPNVR_SEGMENT_S;

//=======================3������ṹ
typedef struct _NVR_RECT_S
{
	int32_t		s32X;							//���x����
	int32_t		s32Y;							//���y����
	uint32_t	u32Width;						//������
	uint32_t	u32Height;						//����߶�
}NVR_RECT_S, *LPNVR_RECT_S;
//=======================4����ṹ
typedef struct _NVR_POINT_S
{
	int32_t		s32X;							//���x����
	int32_t		s32Y;							//���y����
}NVR_POINT_S, *LPNVR_POINT_S;
//=======================5���澯����
typedef struct _NVR_LINKACT_S
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
}NVR_LINKACT_S, *LPNVR_LINKACT_S;

typedef struct _NVR_DEV_JXJ_PLATFORM_CFG_S_
{
	uint32_t	u32Size;
	char 		szPuId[NVR_NAME_LEN];
	char		szCmsIp[NVR_IP_ADDR_LEN];
	uint16_t	u16CmsPort;
	uint8_t		u8Enable;
	uint8_t		u8ProtocolType;
	uint8_t		u8SyncTimeEnable;
	uint8_t 	u8Res1[61];
}NVR_DEV_JXJ_PLATFORM_CFG_S;

typedef struct _NVR_LINK_INFO_S_
{	
	int	 bUsed;
	char szCamId[32];						//�豸ID
	int  nCamIP;
	int  onvifPort;
	char szOnvifAccount[32];
	char szOnvifPassword[32];
}NVR_LINK_INFO_S;

typedef struct _NVR_DEV_DIANXIN_PLATFORM_CFG_S_
{	
	uint32_t 				u32Size;
	char 					szGroupUrl[64];				//����ƽ̨URL
	char 					szProvincialUrl[64];			//ʡƽ̨URL
	char 					szDevId[32];						//�豸ID
	char 					szKey[32];							//key
	char 					szMode[16];						//�豸����
	uint16_t				localRtspPort;						// ����rtsp�˿�
	uint16_t				upnpRtspPort;							// upnp rtsp�˿�
	uint8_t 				u8Res[28];	
	NVR_LINK_INFO_S			link[NVR_MAX_CHANNEL_NUM];
}NVR_DEV_DIANXIN_PLATFORM_CFG_S;


typedef struct _NVR_DEV_VAR_INFO_S
{
	char		szDevName[NVR_DEV_NAME_LEN];  		//�豸����
	uint8_t		u8Language;							//����0 ����1Ӣ��
	uint8_t		u8DevNo;							// �������
	uint8_t		u8VideoFormat;						// 0: pal, 1:ntsc
	uint8_t		u8Res[33];
}NVR_DEV_VAR_INFO_S;

typedef struct _NVR_DEV_STABLE_INFO_S_
{
	uint32_t				u32Size;
	char					szSerialId[NVR_SERIALNO_LEN];  		//�豸Id				
	char					szHwVer[NVR_VERSION_LEN];			//Ӳ���汾��
	char					szSoftVer[NVR_VERSION_LEN];			// ����汾��
	uint8_t					u8MacAddr[NVR_ETHERNET_NUM][6];
	uint32_t				u32IPAddr[NVR_ETHERNET_NUM];
	uint32_t				u32NetMask[NVR_ETHERNET_NUM];
	uint32_t				u32GateWay[NVR_ETHERNET_NUM];
	uint32_t				u32DevCap[4];
	uint8_t					u8SupportAudio;		// �Ƿ�֧����Ƶ
	uint8_t					u8SupportHDMI;		// �Ƿ�֧��HDMI
	uint8_t					u8supportVGA;		// �Ƿ�֧��VGA
	uint8_t					u8ChnNum;			// ֧��ͨ����
	uint8_t					u8SataNum;			// sata�ӿڸ���
	uint8_t					u8NetNum;			// ��������
	uint8_t					u8RS232Num;			// rs232 ����
	uint8_t					u8RS485Num;			// rs485����
	uint8_t					u8AlarmInputNum;	// �����������
	uint8_t					u8AlarmOutputNum;	// �����������
	uint8_t					u8Res[254];
}NVR_DEV_STABLE_INFO_S, *LPNVR_DEV_STABLE_INFO_S;

typedef struct _NVR_DEV_INFO_S_
{
	uint32_t		u32Size;
	NVR_DEV_STABLE_INFO_S stStableInfo;	//ϵͳ�豸�����޸���Ϣ
	NVR_DEV_VAR_INFO_S	  stVarInfo;	//ϵͳ�豸���޸���Ϣ
}NVR_DEV_INFO_S, *LPNVR_DEV_INFO_S;

typedef struct _NVR_DEV_ETHERNET_CFG_S_
{
	uint32_t	u32IpAddr;						//ip��ַ
	uint32_t	u32SubMask;						//���������ַ
	uint32_t	u32GateWay;						//���ص�ַ
	uint8_t		u8MacAddr[NVR_MAC_ADDR_LEN];	//mac��ַ
	uint8_t		u8DhcpOn;						//dhcp����		1--���� 0--������
	uint8_t		u8DhcpStatus;					//dhcp״̬(ֻ��) 0-û���� 1--���ڻ�ȡ 2--��ȡ�ɹ� 3--��ȡʧ��
	uint8_t		u8EtherStatus;					//����״̬(ֻ��) 0-���ڵ� 1--��������(ֻ�ܼ����������)
	uint8_t		u8NetcardSpeed;					//��������		0-�Զ� 1-100M 2-10M
	uint8_t		u8Res[2];
	uint32_t		u32IpAddr1;					// eth0:1 ip��ַ
	uint32_t		u32SubMask1;				// eth0:1 ���������ַ
}NVR_DEV_ETHERNET_CFG_S, *LPNVR_DEV_ETHERNET_CFG_S;


//pppoe������Ϣ
//
typedef struct _NVR_DEV_PPPOE_CFG_S_
{
	uint8_t		u8PppoeOn;							//pppoe����
	uint8_t		u8PppoeStatus;						//pppoe ����״̬0 û�в���1 ������2���ųɹ�
	uint8_t		u8PppoeEth;							//�������� 0-eth0 1-ra0
	uint8_t		u8PppNum;							//0- ppp0 1-ppp 1
	uint8_t		u8Res[4];
	char		szPppoeUsr[NVR_USER_NAME_LEN];		//pppoe�û���
	char		szPppoePsw[NVR_USER_NAME_LEN];		//pppoe����
	uint32_t	u32PppoeIp;							//pppoe��ȡ��ip
	uint32_t	u32PppoeTimes;						//pppoe����ʱ��
	
}NVR_DEV_PPPOE_CFG_S, *LPNVR_DEV_PPPOE_CFG_S;
//====================================================================

typedef struct _NVR_DEV_NET_CFG_S_
{
	uint32_t					u32Size;
	NVR_DEV_ETHERNET_CFG_S 		struEtherCfg[NVR_ETHERNET_NUM];	//������Ϣ	
	uint32_t					u32AlarmHostIp;					//��������ip(Ԥ��)
	uint16_t					u16AlarmHostPort;				//���������˿�(Ԥ��)
	uint8_t						u8DnsDhcp;						//dns�Ƿ��Զ���ȡ
	uint8_t						u8Res1;
	uint32_t					u32DnsIp1;						//dns1
	uint32_t					u32DnsIp2;						//dns2
	uint16_t					u16HttpPort;					//http����˿�
	uint16_t					u16NetPort;						//�������˿�
	uint32_t					u32MultiCastIp;					//�ಥ��ַ
	uint16_t					u16MultiCastPort;				//�ಥ�˿�
	uint16_t					u16RtspPort;					// RTSP�˿�
	NVR_DEV_PPPOE_CFG_S			struPppoeCfg;					//pppoe����
	uint16_t					u16JXJDataPort;				//JXJƽ̨���ݶ˿�
  	uint16_t					u16CmdPort;					//����˿�
  	uint16_t					u16TalkPort;				//�Խ��˿�
	uint8_t                 	u8Res2[26];
}NVR_DEV_NET_CFG_S,*LPNVR_DEV_NET_CFG_S;

typedef struct _NVR_TIME_CFG_S_
{
	uint32_t			u32Size;
	struct timeval		struTv;			// ��ǰʱ��
	uint8_t				u8DateFormat;	// ���ڸ�ʽ0:������, 1:������, 2:������
	uint8_t				u8TimeFormat;	// ʱ���ʽ, 0:24Сʱ��, 1:12Сʱ��
	char				cSeparatorChar;	// -, /, .
	uint8_t				u8Res[33];
}NVR_TIME_CFG_S,*LPNVR_TIME_CFG_S;

typedef struct _NVR_DEV_PTZ_CFG_S_
{
	uint32_t	u32Size;
	uint8_t		u8ProtocalType;	// 0 pelco-d 1 pelco-p
	uint8_t		u8PtzAddr;		//0-255
	uint8_t		u8Res[6];
}NVR_DEV_PTZ_CFG_S, *LPNVR_DEV_PTZ_CFG_S;

typedef struct _NVR_DEV_COMM_CFG_S_
{
	uint32_t		u32Size;
	uint32_t		u32BaudRate;//������(bps)��0-50��1-75��2-110��3-150��4-300��
								//s5-600��6-1200��7-2400��8-4800��9-9600��
								//10-19200��11-38400��12-57600��13-76800��14-115.2k 
 	uint8_t     	u8DataBit;	//����λ��0-5λ��1-6λ��2-7λ��3-8λ
 	uint8_t     	u8StopBit;	//ֹͣλ��0-1λ��1-2λ
  	uint8_t     	u8Parity;	//�Ƿ�У�飺0-��У�飬1-��У�飬2-żУ��
  	uint8_t     	u8Flowcontrol;//�Ƿ����أ�0-�ޣ�1-������,2-Ӳ����
  	uint32_t		u32BaudMask;
  	uint8_t			u8Res[16];
}NVR_DEV_COMM_CFG_S, *LPNVR_DEV_COMM_CFG_S;

//=====================================================================
//ddns ������Ϣ
typedef struct _NVR_DDNS_CFG_S
{
	uint32_t	u32Size;
	uint8_t		u8DDNSOpen;						//DDNS����
	uint8_t		u8DDNSType;						//0-dyndns 1-3322
	uint16_t	u16DDNSPort;					//DDNS�������˿�
	char		szDDNSAccount[NVR_NAME_LEN];	//DDNS ע����
	char		szDDNSUsr[NVR_USER_NAME_LEN];	//�û�����
	char		szDDNSPsw[NVR_PASS_WORD_LEN];	//�û�����	
	uint32_t	u32DDNSTimes;					//����ʱ��
	uint8_t		u8Res[32];
}NVR_DDNS_CFG_S,*LPNVR_DDNS_CFG_S;

//======================================================================
//ftp��������
//
typedef struct _NVR_FTP_CFG_S
{
	uint32_t		u32Size;
	char 			szFtpSvr[NVR_IP_ADDR_LEN]; 	//��ftp������ip
	char        	szFtpUsr[NVR_USER_NAME_LEN];//��½�û���
	char        	szFtpPsw[NVR_PASS_WORD_LEN];//��½����
	char        	szFtpPath[NVR_PATH_LEN];   	//Ftp�ϴ�·��
	uint16_t		u16FtpPort;
	uint8_t			u8Rsvd[30];
}NVR_FTP_CFG_S, *LPNVR_FTP_CFG_S;

//===================================================================
//ntp �����ṹ����
typedef struct _NVR_NTP_CFG_S
{
	uint32_t	u32Size;
	uint8_t		u8NtpOpen;				//ntp����
	uint8_t		u8Resv;
	uint16_t	u16NtpPort;				//�˿�
	uint8_t		u8EuroTime;				//==1:��������ʱ 0:����������ʱ
	uint8_t		u8NtpRefTime;			//ntp ��ʱ��ʱʱ��(��λСʱ)
	int32_t		nTimeZone;				//ʱ�� ��λs(-12*3600~11*3600)
	char        szNtpServer[NVR_IP_ADDR_LEN];
	uint8_t		u8Res[32];
}NVR_NTP_CFG_S, *LPNVR_NTP_CFG_S;

//===========================================================================
//upnp �����ṹ
//
typedef struct _NVR_UPNP_CFG_S
{
	uint32_t	u32Size;
	uint8_t		u8UpnpOpen;			//upnp ����
	uint8_t		u8UpnpEthNo;		//0ʹ�ñ�������ӳ�� 1 ʹ����������ӳ��
	uint8_t		u8UpnpModel;    	//0�̶�ӳ�� 1�Զ�ӳ��
	uint8_t		u8UpnpRefTime;  	//upnp ˢ��ʱ��(��λСʱ)
	char        szUpnpSvr[32];
	char		szExternalIp[32];
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
}NVR_UPNP_CFG_S, *LPNVR_UPNP_CFG_S;

//smtp����
typedef struct _NVR_SMTP_CFG_S
{
	uint32_t	u32Size;
	char        szMailHub[NVR_IP_ADDR_LEN]; 	//smtp ��������ַ
	char        szMailAddr[NVR_MAX_EMAIL_LEN];	//�����ʼ� ��ַ
	char        szMailUsr[NVR_MAX_EMAIL_LEN]; 	//�����ʼ� �˺�
	char        szMailPsw[NVR_PASS_WORD_LEN];   //�����ʼ� ����
	char        szMailRctp1[NVR_MAX_EMAIL_LEN];	//�����ʼ� ��ַ1
	char        szMailRctp2[NVR_MAX_EMAIL_LEN];	//�����ʼ� ��ַ2
	char       	szMailRctp3[NVR_MAX_EMAIL_LEN];	//�����ʼ� ��ַ3
	uint8_t		u8EnableSSL;					//����SSL
	uint8_t		u8Rsvd;
	uint16_t	u16MailPort;					//smtp �������˿�
	uint8_t     u8Rsvd2[32];
}NVR_SMTP_CFG_S, *LPNVR_SMTP_CFG_S;

//user����
typedef struct _NVR_DEV_USER_CFG_S_
{
	uint32_t		u32Size;
	char			szUsrName[NVR_USER_NAME_LEN];	//�û���
	char			szPsw[NVR_PASS_WORD_LEN];		//����
	uint64_t		u64LocalRight;					//���ز���Ȩ��
	uint64_t		u64RemoteRight;					//Զ�̲���Ȩ��
	uint8_t			u8Res[32];
}NVR_DEV_USER_CFG_S, *LPNVR_DEV_USER_CFG_S;

//ͨ������
typedef struct _NVR_CHANNEL_CFG_S_
{
	uint32_t		u32Size;
	char			szFactoryName[NVR_NAME_LEN];	// ��������, utf8
	char			szProtocolName[NVR_NAME_LEN];	// jxj, onvif, hxht, zsyh, etc.
	char			szDevName[NVR_NAME_LEN];		// Զ���豸����, utf8
	char			szUser[NVR_NAME_LEN];			// �û���
	char			szPasswd[NVR_PASS_WORD_LEN];	// ����
	uint32_t		u32IpAddr;
	uint16_t		u16DataPort;
	uint16_t		u16WebPort;
	uint16_t		u16RtspPort;
	uint8_t			u8RemoteChn;					// Զ��ͨ����
	uint8_t			u8UseChn;						// ʹ����һ��Զ��ͨ��
	uint8_t			u8Enable;						// �Ƿ���������
	uint8_t			u8SearchA;						// �����������
	uint8_t			u8Res[30];
}NVR_CHANNEL_CFG_S, *LPNVR_CHANNEL_CFG_S;

typedef struct _NVR_CHNNL_INFO_
{
	NVR_CHANNEL_CFG_S struChannelCfg;
	long 	lHandle;
	long 	lIpncHandle;
	long 	logonHandle;
	long 	lStreamHandle[2];
	
}NVR_CHANNEL_CFG_INFO_S;

//�Զ���������
typedef struct _NVR_AUTO_MAINTAIN_CFG_S_
{	
	uint32_t		u32Size;
	uint8_t		u8Enable;
	uint8_t		u8WeekDay;		// 0, ÿ��,1 ������2,����һ...
	uint8_t		u8Hour;			// 0-23
	uint8_t		u8Min;			// 0-59
	uint8_t		u8Res[28];
}NVR_AUTO_MAINTAIN_CFG_S, *PLNVR_AUTO_MAINTAIN_CFG_S;

//��������
typedef struct _NVR_DEV_PART_INFO_S_
{
	uint8_t	u8Mount;		//0��δ���أ�  1���ѹ���
	uint8_t	u8Format;		//0: δ��ʽ����1���Ѹ�ʽ��
	uint8_t	u8PartType;		//0��¼�����  1�����ݷ���
	uint8_t	u8Use;			//0��δʹ�ã�  1������ʹ��
	uint8_t	u8Res[4];
	uint64_t	u64TotalSize;	//��������
	uint64_t	u64FreeSize;	//����ʣ������	
}NVR_DEV_PART_INFO_S, *LPNVR_DEV_PART_INFO_S;

typedef struct _NVR_DISK_INFO_S_
{
	uint8_t	u8Parted;		//�Ƿ��Ѿ�������0��δ������1���Ѿ�����
	uint8_t	u8FsType;		//�ļ�ϵͳ���ͣ�0��EXT2 �� 1��EXT3��2��FAT32��3��NFS
	uint8_t	u8PartNum;		//��������
	uint8_t	u8RecStatus;	// === 1 ����¼��0 û��¼�� 
	uint8_t	u8Res[4];		//res
	uint64_t	u64TotalSize;	//Ӳ������
	uint64_t	u64FreeSize;	//ʣ������
	NVR_DEV_PART_INFO_S stPart[NVR_MAX_SUPPORT_PART];//������Ϣ	
}NVR_DEV_DISK_INFO_S, *LPNVR_DEV_DISK_INFO_S;
typedef struct _NVR_DEV_HD_INFO_S_
{
	uint32_t			u32Size;
	uint8_t				u8DiskNum;
	uint8_t				u8Res[3];
	NVR_DEV_DISK_INFO_S	stDiskInfo[NVR_MAX_SUPPORT_DISK];
}NVR_DEV_HD_INFO_S, *LPNVR_DEV_HD_INFO_S;

//==================================================================================
typedef struct _NVR_DEV_IMA_PARA_S_
{
	uint8_t	u8Value;		//����ֵ
	uint8_t	u8Default;		//ȱʡ����ֵ
	uint8_t	u8Step;			//����ֵ����ֵ
	uint8_t	u8Res;
}NVR_DEV_IMA_PARA_S;

//��Ƶ�����������Ͷ���

typedef enum _NVR_DEV_IMA_MASK_E_
{
	VCT_IMA_BRIGHTNESS 	= 0x00000001,
	VCT_IMA_CONTRAST	= 0x00000002,
	VCT_IMA_SATURATION 	= 0x00000004,
	VCT_IMA_HUE		  	= 0x00000008,
	VCT_IMA_GAMMA		= 0x00000010,
	VCT_IMA_SHARPNESS	= 0x00000020,
	VCT_IMA_BLUE		= 0x00000040,
	VCT_IMA_RED			= 0x00000080,
	VCT_IMA_ALL			= 0xFFFFFFFF,
}NVR_DEV_IMA_MASK_E;

typedef struct _NVR_DEV_IMA_CFG_S_
{	
//��Ч֧�ֵĲ������ò�������ʱ����Ч
//�ڻ�ȡ��ʱ����Ч�������ж��豸�Ƿ�֧�ָò���
	NVR_DEV_IMA_MASK_E	eSuppMask;
//������Ч�Ĳ������ò�����ȡʱ����Ч
//�����õ�ʱ����Ч������ָ���������õĲ���
	NVR_DEV_IMA_MASK_E	eSetMask;	

	NVR_DEV_IMA_PARA_S	struBrightness;	//����
	NVR_DEV_IMA_PARA_S	struContrast;	//�Աȶ�
	NVR_DEV_IMA_PARA_S	struSaturation;	//���Ͷ�
	NVR_DEV_IMA_PARA_S	struHue;		//ɫ��
	NVR_DEV_IMA_PARA_S	struGamma;		//gamma
	NVR_DEV_IMA_PARA_S	struSharpness;	//sharpness
	NVR_DEV_IMA_PARA_S	struRed;		//red
	NVR_DEV_IMA_PARA_S	struBlue;		//blue	
	NVR_DEV_IMA_PARA_S	struRes[24];
}NVR_DEV_IMA_CFG_S, *LPNVR_DEV_IMA_CFG_S;

typedef struct _NVR_DEV_CAPTURE_CFG_S_
{
  uint16_t		u16Width;		//ץ��ͼƬ���
  uint16_t		u16Height;		//ץ��ͼƬ�߶�

  uint8_t		u8VideoEncType;	//��Ƶ�����ʽ 2--JPEG �̶�ֵ
  uint8_t		u8Quilty;		//ץ������ 
   
  uint8_t		u8Res[14];	
}NVR_DEV_CAPTURE_CFG_S, *LPNVR_DEV_CAPTURE_CFG_S;

//=======================================================================
//��Ƶ�������	
typedef struct _NVR_DEV_VENC_CFG_S_
{
  uint16_t		u16Width;		//��Ƶ������
  uint16_t		u16Height;		//��Ƶ����߶�

  uint8_t		u8VideoEncType;	//��Ƶ�����ʽ0--h264 1--MJPEG 2--JPEG	
  uint8_t		u8PicQuilty;	//��������0-��ã�1-�κã�2-�Ϻã�3-һ�㣬4-�ϲ5-��	
  uint8_t		u8Gop;			//I ֡���1-200
  uint8_t		u8FlowType;		//�������� 0--������1--������
  uint32_t		u32BitrateRate;	//�������� 32kbps-16Mkbps
  uint8_t		u8FrameRate;	//����֡��1-25/30
  uint8_t		u8Res[7];
}NVR_DEV_VENC_CFG_S, *LPNVR_DEV_VENC_CFG_S;

//=======================================================================
//��Ƶ�ڵ�����
typedef struct _NVR_DEV_VMASK_CFG_S_
{
  uint8_t		u8Open;			//--1.������Ƶ�ڵ�0--������Ƶ�ڵ�
  uint8_t		u8Res1[3];
  NVR_RECT_S	struArea[NVR_VMASK_REG_NUM];	//��Ƶ�ڵ�����
  uint8_t		u8Res2[8];
}NVR_DEV_VMASK_CFG_S, *LPNVR_DEV_VMASK_CFG_S;

//osd�˵�����
//����5����Ϣ��ע
typedef struct _NVR_DEV_OSD_LABEL_CFG_S_
{
	uint32_t	u32EnableLabel[NVR_MAX_OSD_LABEL_NUM];				//--1 ��ʾ����osd 0--���ر���osd
	char		szLabelName[NVR_MAX_OSD_LABEL_NUM][NVR_NAME_LEN];	//��ע����
	uint32_t	u32ColorValidFlag[NVR_MAX_OSD_LABEL_NUM];			// 0:ʹ��u3Osdcolor,ʹ��u32LabelColor
  	uint32_t	u32OsdColor[NVR_MAX_OSD_LABEL_NUM];					//----0 ---black
  																	//---1---white
  																	//---2---blue																																	//---3---red
  																	//---4---inv
	NVR_POINT_S struLabelOrg[NVR_MAX_OSD_LABEL_NUM];				//��עosdλ��
	uint32_t	u32LabelColor[NVR_MAX_OSD_LABEL_NUM];				// ��ע��ɫ,��ɫ:0-7bit, ��ɫ:8-15bit,��ɫ:16-23bit
}NVR_DEV_OSD_LABEL_CFG_S, *LPNVR_DEV_OSD_LABEL_CFG_S;

//�ݲ�֧���û��Զ���osd �˵�
typedef struct _NVR_DEV_OSD_CFG_S_
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
  									//---3---red
  									//---4---inv
  uint8_t		u8EnableUsrOsd; 	//bit0 ʹ�ܵ�һ���û��˵�
  									//bit1 ʹ�ܵڶ����û��˵�

  NVR_POINT_S 	struTimeOrg;		//ʱ��osdλ��
  NVR_POINT_S 	struTitleOrg;		//����osdλ��
  NVR_POINT_S 	struUsrOrg[2];		//�û��Զ���osdλ��
  char			szChnName[NVR_NAME_LEN];		//ͨ������
  char			szUsrOsdInfo[2][NVR_NAME_LEN];	//�û��Զ���osd��Ϣ
  uint32_t		u32TimeColor;		//ʱ����ɫ,��ɫ:0-7bit, ��ɫ:8-15bit,��ɫ:16-23bit
  uint32_t		u32ChnColor;		//ͨ����ɫ,��ɫ:0-7bit, ��ɫ:8-15bit,��ɫ:16-23bit
  uint8_t		u8ColorValidFlag;	// 0:ʹ��u8Osdcolor��ʼ��u32TimeColor��u32ChnColorֵ, 1:ֱ��ʹ��u32TimeColor��u32ChnColorֵ
  uint8_t		u8Res[7];
}NVR_DEV_OSD_CFG_S, *LPNVR_DEV_OSD_CFG_S;

typedef enum _NVR_DEV_H264_ENCODE_LEVEL_E_
{
	H264_HIGH = 0,
	H264_MAIN,
	H264_BASELINE,
}NVR_DEV_H264_ENCODE_LEVEL_E;

//ͼ���������
typedef struct _NVR_DEV_VIDEO_CFG_S_
{
	uint32_t				u32Size;	
	NVR_DEV_OSD_CFG_S 		struOsd;
	NVR_DEV_VMASK_CFG_S		struVMask;
	NVR_DEV_VENC_CFG_S 		struMainVenc;
	NVR_DEV_VENC_CFG_S 		struSubVenc;
	NVR_DEV_CAPTURE_CFG_S   struCapture;
	NVR_DEV_IMA_CFG_S		struIma;
	NVR_DEV_H264_ENCODE_LEVEL_E	eEncodeLevel;	// 0:high profile, 1:main profile, 2:baseline
	uint8_t					u8Res[28];
}NVR_DEV_VIDEO_CFG_S, *LPNVR_DEV_VIDEO_CFG_S;

typedef struct _NVR_DEV_AUDIO_CFG_S_
{
	uint32_t	u32Size;
	uint32_t	u32SampleRate;		//������ 8k 80000
	uint8_t		u8Open;				//�Ƿ�����Ƶ
	uint8_t		u8AEncType;			//0--PCM 1--G711A 2-G711U 3--G726
	uint8_t		u8Type;      		// 0--mic���� 1--������
	uint8_t		u8Res[5];
}NVR_DEV_AUDIO_CFG_S, *LPNVR_DEV_AUDIO_CFG_S;

//===========================================================================
typedef struct _NVR_DEV_REC_STRC_S_
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
	NVR_SEGMENT_S	struTimerSeg[NVR_MAX_SEG_NUM][8]; //0--ÿ��1--������ 2--����һ7--������	

	uint8_t		u8Rec[32];
}NVR_DEV_REC_STRC_S, *LPNVR_DEV_REC_STRC_S;

//===========================================================================
//��̨���Ʋ����ṹ��
/* ��Ϊ��Ҫ��ǹ����PTZ���������,���Խṹ��Ĵ�С������֮ǰ�Ĵ�С����һ��*/
#pragma pack(2)
typedef struct _NVR_CTRL_PTZ_S_
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

}NVR_CTRL_PTZ_S, *LPNVR_NET_CTRL_PTZ_S;
#pragma pack()

//�ƶ������Ϣ
typedef struct _NVR_DEV_MD_CFG_S_
{
	uint32_t			u32Size;
	uint8_t			u8Enable;	//�Ƿ����ƶ���� 0--�ر� 1--����			
	uint8_t			u8Level;	//��������� 0--�ܸ� 1--�� 2--�� 3--�� 4--�ܵ�	
	uint8_t			u8Res1[2];
	NVR_RECT_S		struRect[NVR_VMD_REG_NUM];	//�������
	NVR_SEGMENT_S	struSeg[NVR_MAX_SEG_NUM][8];  	//0--ÿ��1--������ 2--����һ7--������	
	NVR_LINKACT_S	struLinkAct;					//�ƶ����������Ϣ
	uint32_t		u32DetectInterval;			//�����ʱ��
	uint8_t			u8Res2[12];
}NVR_DEV_MD_CFG_S, *LPNVR_DEV_MD_CFG_S;

//̽ͷ������Ϣ
typedef struct _NVR_DEV_DI_CFG_S_
{
	uint32_t		u32Size;
	char			chDiName[NVR_USER_NAME_LEN]; //di̽ͷ����
	uint8_t			u8Enable;					 //�Ƿ���di������� 0--������ 1--����
	uint8_t			u8DiType;					 //0--����̽ͷ1--����̽ͷ
	uint8_t			u8Res1[2];
	NVR_SEGMENT_S	struSeg[NVR_MAX_SEG_NUM][8]; 	 //0--ÿ��1--������ 2--����һ7--������	
	NVR_LINKACT_S	struLinkAct;					 //di����������Ϣ
	uint32_t		u32DetectInterval;			 //�����ʱ��
	uint8_t			u8Res2[12];
}NVR_DEV_DI_CFG_S, *LPNVR_DEV_DI_CFG_S;

// Զ��ipnc����
typedef struct _NVR_DEV_IPNC_ALARM_CFG_S_
{
	uint32_t		u32Size;
	uint8_t			u8Enable;  
	uint8_t			u8Res1[3];
	NVR_LINKACT_S	struLinkAct;					 //di����������Ϣ
	uint8_t			u8Res2[32];
}NVR_DEV_IPNC_ALARM_CFG_S;

// ȫ�Զ�����
typedef struct _NVR_DEV_AUTO_CTRL_CFG_S_
{
	uint32_t		u32Size;
	uint8_t 		u8Enable;
	uint8_t 		u8Res1[3];
	uint8_t		u8Res2[64];
}NVR_DEV_AUTO_CTRL_CFG_S;

#endif

