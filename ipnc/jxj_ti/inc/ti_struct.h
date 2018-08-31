#ifndef _TI_STRUCT_H
#define _TI_STRUCT_H
#include "ti_type.h"

                                                  
#ifdef __cplusplus
extern "C" {
#endif

#define TI_SOFT_VERSION			0x022A0000

#define TI_MAX_SUPPORT_CHN		1	//���֧��ͨ����
#define TI_MAX_SUPPORT_STREAM	2	//���֧�������� 0--������ 1--������

#ifdef TI_ARCH
#define TI_MAX_SUPPORT_DI		2	//���֧�ֱ����������
#else
#define TI_MAX_SUPPORT_DI		1	//���֧�ֱ����������
#endif

#define TI_MAX_SUPPORT_DO		1	//���֧�ֱ����������
#define TI_MAX_SUPPORT_RS232	0	//���֧��232����
#define TI_MAX_SUPPORT_RS485	1	//���֧��485����
#define TI_MAX_SUPPORT_COMM_NO 	1 	//���֧�ִ��ڸ��� 0--485  1--232
#define TI_MAX_SUPPORT_DISK		1	//֧����������
#define TI_MAX_SUPPORT_PART		4	//֧����������

#define TI_SERIALNO_LEN			48	//���кų���
#define TI_DEV_NAME_LEN			32	//�豸���Ƴ���
#define TI_NAME_LEN				32	//���Ƴ���
#define TI_USER_NAME_LEN		32	//�û�������	
#define TI_PASS_WORD_LEN		32	//���볤��
#define TI_PATH_LEN				64
#define TI_IP_ADDR_LEN			64  //ip��ַ��������
#define TI_MAC_ADDR_LEN			6	//mac��ַ����
#define TI_ETHERNET_NUM			2	//֧����������
#define TI_VMASK_REG_NUM		4	//��Ƶ�ڵ�����
#define TI_VMD_REG_NUM			4	//��Ƶ���������
#define TI_MAX_SEG_NUM			4	//���ʱ���
#define TI_MAX_EMAIL_LEN		64
#define TI_MAX_USR_NUM			3
#define TI_MAX_IRCF_SEG_NUM		4	//���ⶨʱ���ʱ���
#define TI_MAX_WIF_ESSID_NUM	10 	//���֧��wifi�ڵ����

#define TI_MAX_SYS_IPC_MSG		32	//��Ϣ����֧�������Ϣ����

#define TI_MAX_OSD_LABEL_NUM 	5	//osd��ע�������� 


// define in the main Makefile
#ifndef TI_SUPPORT_PLATFORM
#define TI_SUPPORT_PLATFORM     0   //֧��ƽ̨����
#endif
#define JXJ_BALL 1

typedef enum _TI_SYS_MSG_KEY_E_
{
	TI_SMTP_KEY		= 5,
	TI_FTP_KEY		= 6,
	TI_FTP_UP_KEY	= 7,
	TI_FTP_DOWN_KEY	= 8,
	TI_COMM_KEY		= 8,
	
}TI_SYS_MSG_KEY_E;

typedef enum _TI_SYS_MSG_TYPE_E_
{
	TI_SMTP_MSG		= 5,
	TI_FTP_UP_MSG	= 6,
	TI_FTP_DOWN_MSG	= 7,
	TI_COMM_MSG		= 8,
	
}TI_SYS_MSG_TYPE_E;

typedef enum _TI_MACHINE_TYPE_E_
{
	TI_MACHINE_J5000 = 0x0,
    TI_MACHINE_J6000 = 0x1,
	TI_MACHINE_BUTT  = 0x2,
	
}TI_MACHINE_TYPE_E;

typedef enum _TI_LANGUAGE_TYPE_E_
{
	TI_LANGUAGE_ENG = 0x0,
	TI_LANGUAGE_CHS,
	TI_LANGUAGE_BUTT,
	
}TI_LANGUAGE_TYPE_E;

typedef enum _TI_ALARM_TYPE_E_
{
	TI_ALARM_IN_HAPPEN 		= 0X1,
	TI_ALARM_IN_DISAPPEAR 	= 0X2,
	TI_MD_HAPPEN			= 0X3,
	TI_MD_DISAPPEAR			= 0X4,
	
}TI_ALARM_TYPE_E;

typedef enum _TI_SAVE_TYPE_E_
{
	TI_SAVE_LOCAL_DISK	= 0x0,
	TI_SAVE_FTP			= 0x1,
	TI_SAVE_SMTP		= 0x2,
	TI_SAVE_HXHT		= 0x4,
	TI_SAVE_ONVIF		= 0x8,
}TI_SAVE_TYPE_E;

typedef enum _TI_VIDEO_RESOLUTION_TYPE_E_
{
	TI_VIDEO_D1			= 0x1,		//704*576	n��704*480
	TI_VIDEO_HD1		= 0x2,		//704*288	n��704*240
	TI_VIDEO_CIF		= 0x4,		//352*288	n��352*240
	TI_VIDEO_WCIF		= 0x8,		//320*192
	
	TI_VIDEO_UXGA		= 0x100,	//1600*1200
	TI_VIDEO_SVGA		= 0x200,	//800*600
	TI_VIDEO_VGA		= 0x400,	//640*480
	TI_VIDEO_QVGA		= 0x800,	//320*240
	TI_VIDEO_QQVGA		= 0x1000,	//160*112
	
	TI_VIDEO_1080P		= 0x10000,	//1920*1080
	TI_VIDEO_960		= 0x20000,	//1280*960
	TI_VIDEO_720P		= 0x40000,	//1280*720
}TI_VIDEO_RESOLUTION_TYPE_E;

typedef enum _TI_VIDEO_REC_TYPE_E_
{
	TI_REC_TIME_TYPE	= 0x1,
	TI_REC_MD_TYPE		= 0x2,
	TI_REC_DI_TYPE		= 0x4,
	TI_REC_MANUAL_TYPE	= 0x8,
}TI_VIDEO_REC_TYPE_E;

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

#ifndef PACKED
#define PACKED	__attribute__((packed, aligned(1)))
#endif

//================================================================
//����֡��ʽ
//================================================================
typedef struct _TI_VIDEO_INFO_S
{
	TI_U16		u16ImageWidth;	//ͼ����
	TI_U16		u16ImageHeight;	//ͼ��߶�
	TI_U8		u8EncodeType;	//��Ƶ�����ʽ0-h264 1-mjpeg 2-jpeg
	TI_U8		u8FrameRate;	//֡��(����)
	TI_U8		u8Pal;			//��ʽ0-n��1-pal��
	TI_U8		u8Res[1];
}TI_VIDEO_INFO_S,*LPTI_VIDEO_INFO_S;

typedef struct _TI_AUDIO_INFO_S
{
	TI_U8		u8AudioSamples;		//������ 0--8k 1--16k 2-32k
	TI_U8		u16EncodeType;		//��Ƶ�����ʽ0--pcm 1-g711a 2-g711u 3--g726
	TI_U8		u8AudioChannels;	//ͨ���� ��ֻ֧��1	
	TI_U8		u8AudioBits;		//λ�� 16bit
	TI_U8		u8Res[4];
}TI_AUDIO_INFO_S, *LPTI_AUDIO_INFO_S;

typedef struct _TI_FRAME_HEAD_S
{
	TI_U16		u16FrameFlag;		//0x3448 magic data
	TI_U8		u8FrameType;		//I-0x7 p--0x8 b--0xb A--0xa
	TI_U8		u8Res[1];			//����
	TI_U32		u32FrameNo;			//֡��
	TI_U32		u32Time;			//ϵͳʱ��
	TI_U32		u32FrameSize;		//����������
	TI_U64		u64TimeStamp;		//ʱ���
	union
	{
		TI_VIDEO_INFO_S	unVidoeInfo;
		TI_AUDIO_INFO_S	unAudioInfo;
	};	
}TI_FRAME_HEAD_S, *LPTI_FRAME_HEAD_S;
//============================================================
//======================1��ʱ��ṹ
typedef struct _TI_TIME_S
{
	TI_U8		u8Year;							//��(��1900�꿪ʼ)
	TI_U8		u8Month;						//��1~12
	TI_U8		u8Day;							//��1~31
	TI_U8		u8WDay;							//������0 ����һ1.....
	TI_U8		u8Hour;							//ʱ0~23
	TI_U8		u8Minute;						//��0~59
	TI_U8		u8Second;						//��0~59
	TI_U8		u8Millisec;						//����(0~99)(�ٷ�֮һ��)
}TI_TIME_S, *LPTI_TIME_S;
//=======================2��ʱ��νṹ
typedef struct _TI_SEGMENT_S
{
	TI_U32 		u8Open:8;		//����
	TI_U32		beginSec:24;	//��ʼʱ������ 3600*hour+60*min+sec
	TI_U32		u8Rsvd:8;		//����
	TI_U32		endSec:24;		//����ʱ������ 3600*hour+60*min+sec
}TI_SEGMENT_S, *LPTI_SEGMENT_S;

//=======================3������ṹ
typedef struct _TI_RECT_S
{
	TI_S32		s32X;							//���x����
	TI_S32		s32Y;							//���y����
	TI_U32		u32Width;						//������
	TI_U32		u32Height;						//����߶�
}TI_RECT_S, *LPTI_RECT_S;
//=======================4����ṹ
typedef struct _TI_POINT_S
{
	TI_S32		s32X;							//���x����
	TI_S32		s32Y;							//���y����
}TI_POINT_S, *LPTI_POINT_S;
//=======================5���澯����
typedef struct _TI_LINKACT_S
{
	TI_U32		u32ShootChannel;	//ץ��ͨ��(bit)(0 ��ץ�� 1��һͨ��ץ��)
	TI_U32		u32ShootInterval;	//ץ�ļ��(����),0:����ץ��
	TI_U32		u32RecTime;			//¼��ʱ��(��)
	TI_U32		u32RecChannel;		//¼��ͨ��(bit) (0 ��¼�� 1��һͨ��¼��)
	TI_U32		u32PCRecChannel;	//����PC¼��ͨ��	
	TI_U32		u32OutPut;			//�������(bit)
	TI_U32		u32OutPersist;		//�������ʱ��
	TI_U8		u8ShootMode;		//����ץ��ģʽ,0���ش洢��1ftp�ϴ���2email
	TI_U8		u8ShootNum;			//ץ������	
	TI_U8		u8RecMode;			//����¼��ģʽ��0���ش洢��1ftp�ϴ�	
	TI_U8		u8RecPreTime;		//Ԥ¼ʱ��(��)
	TI_U8		u8Email;			//����email
	TI_U8		u8Rsvd[15];
}TI_LINKACT_S, *LPTI_LINKACT_S;
//==========================================================
//================================================
//������Ϣ�ص��ṹ��Ϣ
//
typedef struct _TI_ALARM_INFO_S
{
	TI_TIME_S	struAlarmTime;			//��������ʱ��
	TI_U8		u8AlarmType;			//�����¼�����
	TI_U8		u8Channel;				//����ͨ����
	TI_U8		u8AlarmInPutCh;			//��������ͨ����
	TI_U8		u8DiskNum;				//����Ӳ�̺�
	TI_U32		u32AlarmOutPutStatus;	//�����������״̬
	TI_U32		u32AlarmRecStatus;		//��������¼��״̬
	TI_U32		u32PcRecStatus;			//����pc¼��״̬
	TI_U32		u32SeqNo;
	TI_U8		u8Res[12];
}TI_ALARM_INFO_S, *LPTI_ALARM_INFO_S; 
//==================================================
//������Ϣ�ص��ṹ��Ϣ
typedef struct _TI_COMM_INFO_S_
{
	TI_U8		u8CommNo;				//���ں�
	TI_U8		u8DataLen;				//������Ϣ����
	TI_U8		u8Data[254];			//������Ϣ
}TI_COMM_INFO_S, *LPTI_COMM_INFO_S;
//==============================================================
//
typedef struct _TI_DEV_STABLE_INFO_S_
{
	TI_U8		u8SerialId[TI_SERIALNO_LEN];  	//�豸Id
	TI_U8		u8DiNum;						//��������·��
	TI_U8		u8DoNum;						//�������·��
	TI_U8		u8ChnNum  ;						//�豸·��
	TI_U8		u8Rs232Num;						//�豸232 ���ڸ���
	TI_U8		u8Rs485Num;						//�豸485 ���ڸ���
	TI_U8		u8NetCardNum;					//��������
	TI_U16		u16DevType ;					//�豸����						
	TI_U32		u32HwVer;						//Ӳ���汾��
	TI_U32		u32CoreVer;						//�ں˰汾��
	TI_U32		u32SoftVer;						//����汾��
	TI_U32		u32ResolutionM;					//֧�ֵ��������ֱ��ʴ�С
	TI_U32		u32ResolutionS;					//֧�ֵĴ������ֱ��ʴ�С	
	TI_U32		u32SensorType;					//ǰ��sensor ����
	TI_U8		u8Res2[12];	
}TI_DEV_STABLE_INFO_S, *LPTI_DEV_STABLE_INFO_S;

typedef struct _TI_DEV_VAR_INFO_S
{
	TI_CHAR		szDevName[TI_DEV_NAME_LEN];  	//�豸����
	TI_U8		u8Language;						//����0 ����1Ӣ��
	TI_U8		u8PalStand;						//��ʽ1 pal 0 ntfc
	TI_U8		u8Hz;							//��ԴƵ��0 50Hz 1 60HZ
	TI_U8		u8Res[17];
}TI_DEV_VAR_INFO_S;

typedef struct _TI_DEV_INFO_S_
{
	TI_U32		u32Size;
	TI_DEV_STABLE_INFO_S stStableInfo;	//ϵͳ�豸�����޸���Ϣ
	TI_DEV_VAR_INFO_S	  stVarInfo;	//ϵͳ�豸���޸���Ϣ
}TI_DEV_INFO_S, *LPTI_DEV_INFO_S;

typedef struct _TI_DEV_ETHERNET_CFG_S_
{
	TI_U32		u32IpAddr;						//ip��ַ
	TI_U32		u32SubMask;						//���������ַ
	TI_U32		u32GateWay;						//���ص�ַ
	TI_U8		u8MacAddr[TI_MAC_ADDR_LEN];		//mac��ַ
	TI_U8		u8DhcpOn;						//dhcp����		1--���� 0--������
	TI_U8		u8DhcpStatus;					//dhcp״̬(ֻ��) 0-û���� 1--���ڻ�ȡ 2--��ȡ�ɹ� 3--��ȡʧ��
	TI_U8		u8EtherStatus;					//����״̬(ֻ��) 0-���ڵ� 1--��������(ֻ�ܼ����������)
	TI_U8		u8NetcardSpeed;					//��������		0-�Զ� 1-100M 2-10M
	TI_U8		u8Res[10];
}TI_DEV_ETHERNET_CFG_S, *LPTI_DEV_ETHERNET_CFG_S;
//============================================================
//pppoe������Ϣ
//
typedef struct _TI_DEV_PPPOE_CFG_S_
{
	TI_U8		u8PppoeOn;							//pppoe����
	TI_U8		u8PppoeStatus;						//pppoe ����״̬0 û�в���1 ������2���ųɹ�
	TI_U8		u8Res[6];
	TI_CHAR		szPppoeUsr[TI_USER_NAME_LEN];		//pppoe�û���
	TI_CHAR		szPppoePsw[TI_USER_NAME_LEN];		//pppoe����
	TI_U32		u32PppoeIp;							//pppoe��ȡ��ip
	TI_U32		u32PppoeTimes;						//pppoe����ʱ��
	
}TI_DEV_PPPOE_CFG_S, *LPTI_DEV_PPPOE_CFG_S;

typedef struct _TI_DEV_NET_CFG_S_
{
  TI_U32				u32Size;
  TI_DEV_ETHERNET_CFG_S struEtherCfg[TI_ETHERNET_NUM];//������Ϣ	
  TI_U32				u32AlarmHostIp;				//��������ip(Ԥ��)
  TI_U16				u16AlarmHostPort;			//���������˿�(Ԥ��)
  TI_U8					u8DnsDhcp;					//dns�Ƿ��Զ���ȡ
  TI_U8					u8Res1;
  TI_U32				u32DnsIp1;					//dns1
  TI_U32				u32DnsIp2;					//dns2
  TI_U16				u16HttpPort;				//http����˿�
  TI_U16				u16NetPort;					//�������˿�
  TI_U32				u32MultiCastIp;				//�ಥ��ַ
  TI_U16				u16MultiCastPort;			//�ಥ�˿�
  TI_U16				u16Res;
  TI_DEV_PPPOE_CFG_S	struPppoeCfg;				//pppoe����
  TI_U8                 u8Res2[32];
  
}TI_DEV_NET_CFG_S,*LPTI_DEV_NET_CFG_S;

typedef struct _TI_DEV_CAPTURE_CFG_S_
{
  TI_U16	u16Width;		//ץ��ͼƬ���
  TI_U16	u16Height;		//ץ��ͼƬ�߶�
  TI_U8		u8VideoEncType;	//��Ƶ�����ʽ 2--JPEG �̶�ֵ
  TI_U8		u8Quilty;		//ץ������ 
  TI_U8		u8Res[14];	
  
}TI_DEV_CAPTURE_CFG_S, *LPTI_DEV_CAPTURE_CFG_S;
//=======================================================================
//��Ƶ�������	
typedef struct _TI_DEV_VENC_CFG_S_
{
  TI_U16	u16Width;		//��Ƶ������
  TI_U16	u16Height;		//��Ƶ����߶�

  TI_U8		u8VideoEncType;	//��Ƶ�����ʽ0--h264 1--MJPEG 2--JPEG	
  TI_U8		u8PicQuilty;	//��������0-��ã�1-�κã�2-�Ϻã�3-һ�㣬4-�ϲ5-��	
  TI_U8		u8Gop;			//I ֡���1-200
  TI_U8		u8FlowType;		//�������� 0--������1--������
  TI_U32	u32BitrateRate;	//�������� 32kbps-16Mkbps
  TI_U8		u8FrameRate;	//����֡��1-25/30
  TI_U8		u8Res[7];
  
}TI_DEV_VENC_CFG_S, *LPTI_DEV_VENC_CFG_S;
//=======================================================================
//��Ƶ�ڵ�����
typedef struct _TI_DEV_VMASK_CFG_S_
{
  TI_U8		u8Open;			//--1.������Ƶ�ڵ�0--������Ƶ�ڵ�
  TI_U8		u8Res1[3];
  TI_RECT_S	struArea[TI_VMASK_REG_NUM];	//��Ƶ�ڵ�����
  TI_U8		u8Res2[8];
}TI_DEV_VMASK_CFG_S, *LPTI_DEV_VMASK_CFG_S;
//=====================================================================
//osd�˵�����
//����5����Ϣ��ע
typedef struct _TI_DEV_OSD_LABEL_CFG_S_
{
	TI_U32		u32EnableLabel[TI_MAX_OSD_LABEL_NUM];					//--1 ��ʾ����osd 0--���ر���osd
	TI_CHAR		szLabelName[TI_MAX_OSD_LABEL_NUM][TI_NAME_LEN];			//��ע����
	TI_U32		u32ColorValidFlag[TI_MAX_OSD_LABEL_NUM];				// 0:ʹ��u3Osdcolor,ʹ��u32LabelColor
  	TI_U32		u32OsdColor[TI_MAX_OSD_LABEL_NUM];						//----0 ---black
  																		//---1---white
  																		//---2---blue
  																		//---3---red
  																		//---4---inv
	TI_POINT_S 	struLabelOrg[TI_MAX_OSD_LABEL_NUM];						//��עosdλ��
	TI_U32		u32LabelColor[TI_MAX_OSD_LABEL_NUM];					// ��ע��ɫ,��ɫ:0-7bit, ��ɫ:8-15bit,��ɫ:16-23bit
}TI_DEV_OSD_LABEL_CFG_S, *LPTI_DEV_OSD_LABEL_CFG_S;


//�ݲ�֧���û��Զ���osd �˵�
typedef struct _TI_DEV_OSD_CFG_S_
{
  TI_U8		u8EnableTitleOsd;		//--1 ��ʾ����osd 0--���ر���osd
  TI_U8		u8EnableTimeOsd;		//--1 ��ʾʱ��osd 0--����ʱ��osd
  TI_U8		u8DispWeek;				//--1 ��ʾ����0--��������
  TI_U8		u8EnableBitrateOsd;		//--1��ʾ����osd  0--��������osd
  TI_U8		u8TimeOsdType;			//--ʱ����ʾ����
  									//--0 YYYY-MM-DD HH:MM:SS
  									//--1 MM-DD-YYYY HH:MM:SS
  									//--2 DD-MM-YYYY HH:MM:SS
									//--3 YYYY/MM/DD HH:MM:SS
									//--4 MM/DD/YYYY HH:MM:SS
									//--5 DD/MM/YYYY HH:MM:SS
									
  TI_U8		u8HourOsdType;			//--0 24 hour --1 12 hour
  TI_U8		u8OsdColor;				//----0 ---black
  									//---1---white
  									//---2---blue
  									//---3---red
  TI_U8		u8EnableUsrOsd; //bit0 ʹ�ܵ�һ���û��˵�
  							//bit1 ʹ�ܵڶ����û��˵�

  TI_POINT_S struTimeOrg;	//ʱ��osdλ��
  TI_POINT_S struTitleOrg;	//����osdλ��
  TI_POINT_S struUsrOrg[2];	//�û��Զ���osdλ��
  TI_CHAR	szChnName[TI_NAME_LEN];		 //ͨ������
  TI_CHAR	szUsrOsdInfo[2][TI_NAME_LEN];//�û��Զ���osd��Ϣ
  TI_U32	u32TimeColor;		// ʱ����ɫ,��ɫ:0-7bit, ��ɫ:8-15bit,��ɫ:16-23bit
  TI_U32	u32ChnColor;		// ͨ����ɫ,��ɫ:0-7bit, ��ɫ:8-15bit,��ɫ:16-23bit
  TI_U8		u8ColorValidFlag;	// 0:ʹ��u8Osdcolor��ʼ��u32TimeColor��u32ChnColorֵ, 1:ֱ��ʹ��u32TimeColor��u32ChnColorֵ
  TI_U8		u8Res[7];
}TI_DEV_OSD_CFG_S, *LPTI_DEV_OSD_CFG_S;

typedef enum _TI_DEV_H264_ENCODE_LEVEL_E_
{
	H264_HIGH = 0,
	H264_MAIN,
	H264_BASELINE,
}TI_DEV_H264_ENCODE_LEVEL_E;

//====================================
//ͼ���������

typedef struct _TI_DEV_IMA_PARA_S_
{
	TI_U8	u8Value;			//����ֵ
	TI_U8	u8Default;			//ȱʡ����ֵ
	TI_U8	u8Step;				//����ֵ����ֵ
	TI_U8	u8Res;
}TI_DEV_IMA_PARA_S;
//��Ƶ�����������Ͷ���
typedef enum _TI_DEV_IMA_MASK_E_
{
	VCT_IMA_BRIGHTNESS 	= 0x00000001,
	VCT_IMA_CONTRAST	  	= 0x00000002,
	VCT_IMA_SATURATION 	= 0x00000004,
	VCT_IMA_HUE		  	= 0x00000008,
	VCT_IMA_GAMMA		= 0x00000010,
	VCT_IMA_SHARPNESS	= 0x00000020,
	VCT_IMA_BLUE			= 0x00000040,
	VCT_IMA_RED			= 0x00000080,
	VCT_IMA_ALL			= 0xFFFFFFFF,
}TI_DEV_IMA_MASK_E;


typedef struct _TI_DEV_IMA_CFG_S_
{	
/*��Ч֧�ֵĲ������ò�������ʱ����Ч
�ڻ�ȡ��ʱ����Ч�������ж��豸�Ƿ�֧�ָò���*/	
	TI_DEV_IMA_MASK_E	eSuppMask;
/*������Ч�Ĳ������ò�����ȡʱ����Ч
   �����õ�ʱ����Ч������ָ���������õĲ���*/	
	TI_DEV_IMA_MASK_E	eSetMask;	

	TI_DEV_IMA_PARA_S	struBrightness;	//����
	TI_DEV_IMA_PARA_S	struContrast;	//�Աȶ�
	TI_DEV_IMA_PARA_S	struSaturation;//���Ͷ�
	TI_DEV_IMA_PARA_S	struHue;		//ɫ��
	TI_DEV_IMA_PARA_S	struGamma;		//gamma
	TI_DEV_IMA_PARA_S	struSharpness;	//sharpness
	TI_DEV_IMA_PARA_S	struRed;		//red
	TI_DEV_IMA_PARA_S	struBlue;	//blue	
	TI_DEV_IMA_PARA_S	struRes[24];
}TI_DEV_IMA_CFG_S, *LPTI_DEV_IMA_CFG_S;


typedef struct _TI_DEV_VIDEO_CFG_S_
{
	TI_U32					u32Size;	
	TI_DEV_OSD_CFG_S 		struOsd;
	TI_DEV_VMASK_CFG_S		struVMask;
	TI_DEV_VENC_CFG_S 		struMainVenc;
	TI_DEV_VENC_CFG_S 		struSubVenc;
	TI_DEV_CAPTURE_CFG_S   	struCapture;
	TI_DEV_IMA_CFG_S		struIma;
	TI_DEV_H264_ENCODE_LEVEL_E	eEncodeLevel;	// 0:high profile, 1:main profile, 2:baseline
	TI_U8					u8Res[28];
}TI_DEV_VIDEO_CFG_S, *LPTI_DEV_VIDEO_CFG_S;

typedef struct _TI_DEV_AUDIO_CFG_S_
{
	TI_U32		u32Size;
	TI_U32		u32SampleRate;		//������ 8k 80000
	TI_U8		u8Open;				//�Ƿ�����Ƶ
	TI_U8		u8AEncType;			//0--PCM 1--G711A 2-G711U 3--G726
	TI_U8		u8Type;      			// 0--mic���� 1--������
	TI_U8		u8Res[5];
}TI_DEV_AUDIO_CFG_S, *LPTI_DEV_AUDIO_CFG_S;

typedef struct _TI_DEV_PTZ_CFG_S_
{
	TI_U32		u32Size;
	TI_U8		u8ProtocalType;	// 0 pelco-d 1 pelco-p
	TI_U8		u8PtzAddr;		//0-255
	TI_U8		u8Res[6];
}TI_DEV_PTZ_CFG_S, *LPTI_DEV_PTZ_CFG_S;

typedef struct _TI_DEV_COMM_CFG_S_
{
	TI_U32		u32Size;
	TI_U32		u32BaudRate;//������(bps)��0-50��1-75��2-110��3-150��4-300��
						//s5-600��6-1200��7-2400��8-4800��9-9600��
						//10-19200��11-38400��12-57600��13-76800��14-115.2k 
 	TI_U8     	u8DataBit;	//����λ��0-5λ��1-6λ��2-7λ��3-8λ
 	TI_U8     	u8StopBit;	//ֹͣλ��0-1λ��1-2λ
  	TI_U8     	u8Parity;	//�Ƿ�У�飺0-��У�飬1-��У�飬2-żУ��
  	TI_U8     	u8Flowcontrol;//�Ƿ����أ�0-�ޣ�1-������,2-Ӳ����
  	TI_U32		u32BaudMask;
  	TI_U8		u8Res[4];
}TI_DEV_COMM_CFG_S, *LPTI_DEV_COMM_CFG_S;

typedef struct _TI_DEV_MD_CFG_S_
{
  TI_U32			u32Size;
  TI_U8				u8Enable;	//�Ƿ����ƶ���� 0--�ر� 1--����			
  TI_U8				u8Level;	//��������� 0--�ܸ� 1--�� 2--�� 3--�� 4--�ܵ�	
  TI_U8				u8Res1[2];
  TI_RECT_S			struRect[TI_VMD_REG_NUM];	//�������
  TI_SEGMENT_S		struSeg[TI_MAX_SEG_NUM][8];  //0--ÿ��1--������ 2--����һ7--������	
  TI_LINKACT_S		struLinkAct;				//�ƶ����������Ϣ
  TI_U32			u32DetectInterval;			// �����ʱ��
  TI_U8				u8Res2[12];
}TI_DEV_MD_CFG_S, *LPTI_DEV_MD_CFG_S;

typedef struct _TI_DEV_DI_CFG_S_
{
  TI_U32			u32Size;
  TI_CHAR			chDiName[TI_NAME_LEN];	//di̽ͷ����
  TI_U8				u8Enable;				//�Ƿ���di������� 0--������ 1--����
  TI_U8				u8DiType;				//0--����̽ͷ1--����̽ͷ
  TI_U8				u8Res1[2];
  TI_SEGMENT_S		struSeg[TI_MAX_SEG_NUM][8];  //0--ÿ��1--������ 2--����һ7--������	
  TI_LINKACT_S		struLinkAct;				//di����������Ϣ
  TI_U32			u32DetectInterval;			// �����ʱ��
  TI_U8				u8Res2[12];
}TI_DEV_DI_CFG_S, *LPTI_DEV_DI_CFG_S;
//==========================================================
//��Ƶ��ʧ�����ṹ
//
typedef struct _TI_DEV_VLOST_CFG_S_
{
  TI_U32			u32Size;
  TI_U8				u8Enable;					//�Ƿ�����Ƶ��ʧ������� 0--������ 1--����		
  TI_U8				u8Res1[3];
  TI_SEGMENT_S		struSeg[TI_MAX_SEG_NUM][8];  //0--ÿ��1--������ 2--����һ7--������	
  TI_LINKACT_S		struLinkAct;				//��Ƶ��ʧ��������
  TI_U8				u8Res2[16];
}TI_DEV_VLOST_CFG_S, *LPTI_DEV_VLOST_CFG_S;
//========================================================
//�û���Ϣ�ṹ���� 
//
typedef struct _TI_DEV_USER_CFG_S_
{
	TI_U32		u32Size;
	TI_CHAR		szUsrName[TI_USER_NAME_LEN];		//�û���
	TI_CHAR		szPsw[TI_PASS_WORD_LEN];			//����
	TI_U64		u64LocalRight;						//���ز���Ȩ��
	TI_U64		u64RemoteRight;						//Զ�̲���Ȩ��
	TI_U8		u8Res[28];
}TI_DEV_USER_CFG_S, *LPTI_DEV_USER_CFG_S;

//ddns ������Ϣ
typedef struct _TI_DDNS_CFG_S
{
	TI_U32		u32Size;
	TI_U8		u8DDNSOpen;						//DDNS����
	TI_U8		u8DDNSType;						//0-dyndns 1-3322
	TI_U16		u16DDNSPort;					//DDNS�������˿�
	TI_CHAR		szDDNSAccount[TI_NAME_LEN];		//DDNS ע����
	TI_CHAR		szDDNSUsr[TI_USER_NAME_LEN];	//�û�����
	TI_CHAR		szDDNSPsw[TI_PASS_WORD_LEN];	//�û�����	
	TI_U32		u32DDNSTimes;					//����ʱ��
	TI_U8		u8Res[16];
}TI_DDNS_CFG_S,*LPTI_DDNS_CFG_S;

//======================================================================
//ftp��������
//
typedef struct _TI_FTP_CFG_S
{
	TI_U32		u32Size;
	TI_CHAR 	szFtpSvr[TI_IP_ADDR_LEN]; //��ftp������ip
	TI_CHAR     szFtpUsr[TI_USER_NAME_LEN];//��½�û���
	TI_CHAR     szFtpPsw[TI_PASS_WORD_LEN];//��½����
	TI_CHAR     szFtpPath[TI_PATH_LEN];   //Ftp�ϴ�·��
	TI_U16		u16FtpPort;
	TI_U8		u8Rsvd[30];
}TI_FTP_CFG_S, *LPTI_FTP_CFG_S;

//===================================================================
//ntp �����ṹ����
typedef struct _TI_NTP_CFG_S
{
	TI_U32		u32Size;
	TI_U8		u8NtpOpen;				//ntp����
	TI_U8		u8Resv;
	TI_U8		u8EuroTime;				//==1:��������ʱ 0:����������ʱ
	TI_U8		u8NtpRefTime;			//ntp ��ʱ��ʱʱ��(��λСʱ)
	int			nTimeZone;				//ʱ�� ��λs(-12*3600~11*3600)
	TI_CHAR     szNtpServer[TI_IP_ADDR_LEN];
	TI_U8		u8Res[16];
}TI_NTP_CFG_S, *LPTI_NTP_CFG_S;

//===========================================================================
//upnp �����ṹ
//
typedef struct _TI_UPNP_CFG_S
{
	TI_U32		u32Size;
	TI_U8		u8UpnpOpen;		//upnp ����
	TI_U8		u8UpnpEthNo;	//0ʹ�ñ�������ӳ�� 1 ʹ����������ӳ��
	TI_U8		u8UpnpModel;    //0�̶�ӳ�� 1�Զ�ӳ��
	TI_U8		u8UpnpRefTime;  //upnp ˢ��ʱ��(��λСʱ)
	TI_U32		u32UpnpSvr;		//upnp ������IP
	TI_U16		u16UpnpDataPort;//�̶�ӳ��ģʽ��, ���ݶ˿ڵ������˿�
	TI_U16		u16UpnpWebPort; //�̶�ӳ��ģʽ��, Web�˿ڵ������˿�
	TI_U16		u16UpnpDataPortS;//���ݶ˿ڵ������˿� 0����û��ӳ��򲻳ɹ�
	TI_U16		u16UpnpWebPortS;//Web�˿ڵ������˿� 0����û��ӳ��򲻳ɹ�
	TI_U8		u8Res[16];
}TI_UPNP_CFG_S, *LPTI_UPNP_CFG_S;

//smtp����
typedef struct _TI_SMTP_CFG_S
{
	TI_U32		u32Size;
	char        szMailHub[TI_IP_ADDR_LEN]; 		//smtp ��������ַ
	char        szMailAddr[TI_MAX_EMAIL_LEN];	//�����ʼ� ��ַ
	char        szMailUsr[TI_MAX_EMAIL_LEN]; 	//�����ʼ� �˺�
	char        szMailPsw[TI_PASS_WORD_LEN];  	//�����ʼ� ����
	char        szMailRctp1[TI_MAX_EMAIL_LEN];	//�����ʼ� ��ַ1
	char        szMailRctp2[TI_MAX_EMAIL_LEN];	//�����ʼ� ��ַ2
	char       	szMailRctp3[TI_MAX_EMAIL_LEN];	//�����ʼ� ��ַ3
	TI_U8		u8EnableSSL;						//����SSL
	TI_U8		u8Rsvd;
	TI_U16		u16MailPort;						//smtp �������˿�
	TI_U8       u8Rsvd2[32];
}TI_SMTP_CFG_S, *LPTI_SMTP_CFG_S;

//��ʱ����ģʽ����
typedef struct _TI_DEV_IRCFMODE_S_
{
	TI_U32 				u32Size;
	TI_U8				u8Enable;							//�Ƿ�����ʱ����ģʽ 0-�رգ�1-����
	TI_SEGMENT_S		struSeg[TI_MAX_IRCF_SEG_NUM][8];  	//0--ÿ��1--������ 2--����һ7--������	
	TI_U8				u8Res1[32];
}TI_DEV_IRCFMODE_S;


typedef struct _TI_DEV_JXJ_PLATFORM_CFG_S_
{
	TI_U32	u32Size;
	char 	szPuId[TI_NAME_LEN];
	char	szCmsIp[TI_IP_ADDR_LEN];
	TI_U16	u16CmsPort;
	TI_U8	u8Enable;
	TI_U8	u8ProtocolType;
	TI_U8	u8SyncTimeEnable;
	TI_U8 	u8Res1[61];
}TI_DEV_JXJ_PLATFORM_CFG_S;

#define HXHT_PRESET_NUM 32
typedef struct _TI_DEV_HXHT_PLATFORM_CFG_S_
{
	TI_U32 u32Size;
	char szPuId[TI_NAME_LEN];
	char szCmsIp[TI_IP_ADDR_LEN];
	char szFtpIp[TI_IP_ADDR_LEN];
	char szFtpUser[TI_NAME_LEN];
	char szFtpPsw[TI_NAME_LEN];
	TI_U8 u8MaxConnectNum;
	char szPresetName[HXHT_PRESET_NUM][16];
	TI_U8 u8Res1[64];
}TI_DEV_HXHT_PLATFORM_CFG_S;

#define GB28181_ID_LEN			24
#define GB28181_IP_LEN			16
#define GB28181_PSW_LEN			32
typedef struct _TI_DEV_GB28181_PLATFORM_CFG_S
{
	TI_U32 			u32Size;
	char  			szServerId[GB28181_ID_LEN];
	char  			szServerIp[GB28181_IP_LEN];
	unsigned short 	ServerPort;
	char            szPuId[GB28181_ID_LEN];
	char            szPassword[GB28181_PSW_LEN];
	int             expire;
	TI_U8 			u8Res1[128];
}TI_DEV_GB28181_PLATFORM_CFG_S;
/* begin:	add by hjl	2013/1/7*/
#define J_SDK_MAX_PRESET_PORT_SIZE 			255
#define J_SDK_MAX_NAME_LEN					64

typedef struct _TI_PRESET_POINT_S
{
	TI_U8	name[J_SDK_MAX_NAME_LEN];	//Ԥ�õ�����
	TI_U32	preset;						//Ԥ�õ�ţ�
}TI_PRESET_POINT_S, *LPTI_PRESET_POINT_S;

typedef struct _TI_DEV_PP_SET_CFG_S
{
	TI_U32	u32Size;
	TI_U32	pp_count;								//Ԥ�õ�����
	TI_PRESET_POINT_S pp[J_SDK_MAX_PRESET_PORT_SIZE];//Ԥ�õ㼯��
}TI_DEV_PP_SET_CFG_S;
/* end:	add by hjl	2013/1/7*/
typedef struct _TI_DEV_ONVIF_CFG_S_
{
	TI_U32	u32Size;
	TI_U8	u8Disconvery;
	char 	szDomain[32];
	TI_U8 	u8Res1[64];
}TI_DEV_ONVIF_CFG_S;

typedef struct _TI_WIFI_STR_CFG_S
{
	TI_U32	u32Size;
	char					szEssid[TI_NAME_LEN];   //�˺�
	char					szPsw[TI_PASS_WORD_LEN];//����
	TI_U8 	u8Res1[64];
}TI_WIFI_STR_CFG_S;

typedef struct _TI_WIFI_CFG_S
{
	char		szEssid[TI_NAME_LEN];   		//�˺�
	char		szPsw[TI_PASS_WORD_LEN];		//����
	char 		szAp_macaddr[TI_NAME_LEN];		//Mac��ַ
	char 		szAuthMode[TI_NAME_LEN];		//���ģʽ
	char 		szEncryption[TI_NAME_LEN];		//����ģʽ
	int 		nSignal;						//�ź�ǿ��:0-100
	int 		nStatus;						//0-δ���ӣ�1-������
	TI_U8		u8Res[4];		
}TI_WIFI_CFG_S;

typedef struct _TI_WIFI_ESSIDCFG_S
{
	TI_U32	u32Size;
	TI_U8	u8ScanResult;	//0-�ɹ���1-ʧ��
	TI_U8	u8WifiConStatus;//wifi����״̬:1--�����ӣ�0-δ����
	TI_U8	u8Count;		//ɨ��ڵ����
	TI_U8 	u8Res1;
	TI_WIFI_CFG_S Essid[TI_MAX_WIF_ESSID_NUM]; //���֧�ֽڵ�ɨ��ڵ����:10��
	TI_U8 	u8Res2[64];
}TI_WIFI_ESSID_CFG_S;


typedef struct _TI_DEV_PART_INFO_S_
{
	TI_U8	u8Mount;		//0��δ���أ�  1���ѹ���
	TI_U8	u8Format;		//0: δ��ʽ����1���Ѹ�ʽ��
	TI_U8	u8PartType;		//0��¼�����  1�����ݷ���
	TI_U8	u8Use;			//0��δʹ�ã�  1������ʹ��
	TI_U8	u8Res[4];
	TI_U64	u64TotalSize;	//��������
	TI_U64	u64FreeSize;	//����ʣ������	
}TI_DEV_PART_INFO_S, *LPTI_DEV_PART_INFO_S;

typedef struct _TI_DISK_INFO_S_
{
	TI_U8	u8Parted;		//�Ƿ��Ѿ�������0��δ������1���Ѿ�����
	TI_U8	u8FsType;		//�ļ�ϵͳ���ͣ�0��EXT2 �� 1��EXT3��2��FAT32��3��NFS
	TI_U8	u8PartNum;		//��������
	TI_U8	u8RecStatus;	// === 1 ����¼��0 û��¼�� 
	TI_U8	u8Res[4];		//res
	TI_U64	u64TotalSize;	//Ӳ������
	TI_U64	u64FreeSize;	//ʣ������
	TI_DEV_PART_INFO_S stPart[TI_MAX_SUPPORT_PART];//������Ϣ	
}TI_DEV_DISK_INFO_S, *LPTI_DEV_DISK_INFO_S;

typedef struct _TI_DEV_HD_INFO_S_
{
	TI_U32				u32Size;
	TI_U8				u8DiskNum;
	TI_U8				u8Res[3];
	TI_DEV_DISK_INFO_S	stDiskInfo[TI_MAX_SUPPORT_DISK];
}TI_DEV_HD_INFO_S, *LPTI_DEV_HD_INFO_S;

typedef struct _TI_DEV_REC_STRC_S_
{
	TI_U32		u32Size;		
	TI_U8		u8OverWrite;		//0 ������1 ����
	TI_U8		u8RecStream;		//0 ������¼��1 ������¼��
	TI_U8		u8PreRecSecs;		//Ԥ¼ʱ��(��)
	TI_U8		u8SaveMode;			//����ģʽ

	//��ʱ¼�����
	TI_SEGMENT_S	struTimerSeg[TI_MAX_SEG_NUM][8]; //0--ÿ��1--������ 2--����һ7--������	
}TI_DEV_REC_STRC_S, *LPTI_DEV_REC_STRC_S;
// ==========================================================
// ����������
//
#define TI_BALL_ONTIME_NUM 8
// ��������
typedef struct _TI_BALL_ALARM_PARAM_S_
{
	int nAlarmActionIndex;		// ��������
	int nDurationSec;			// ��������ʱ��
	TI_U8 byRes[32];
}TI_BALL_ALARM_PARAM_S, *LPTI_BALL_ALARM_PARAM_S;
// ��ʱ����
typedef struct _TI_BALL_ONTIME_ACTION_S_
{
	TI_U8 byBeginHour;					// ��ʼСʱ
	TI_U8 byBeginMin;					// ��ʼ����
	TI_U8 byEndHour;					// ����Сʱ
	TI_U8 byEndMin;						// ��������
	int nActionIndex;
	TI_U8 byRes[12];
}TI_BALL_ONTIME_ACTION_S, *LPTI_BALL_ONTIME_ACTION_S;
// ��ʱ����
typedef struct _TI_BALL_ONTIME_PARAM_S_
{
	TI_BALL_ONTIME_ACTION_S struOntimeAction[TI_BALL_ONTIME_NUM];
	TI_U8 byRes[32];
}TI_BALL_ONTIME_PARAM_S, *LPTI_BALL_ONTIME_PARAM_S;
// Ѳ����
typedef struct _TI_BALL_CRUISE_NODE_S_
{
	TI_U8 byCruisePresetEnable;		// �Ƿ�ʹ�����Ԥ�õ� 
	TI_U8 byCruisePresetSec;		// ͣ��ʱ��(��)
	TI_U8 byCruisePresetSpeed;		// �ƶ��ٶ�
	TI_U8 byRes[8];
}TI_BALL_CRUISE_NODE_S, *LPTI_BALL_CRUISE_NODE_S;
// Ѳ������
#define TI_BALL_CRUISE_NUM 16
#define TI_BALL_CRUISE_NAME_LEN 32
typedef struct _TI_BALL_CRUISE_PARAM_S_
{
	TI_BALL_CRUISE_NODE_S struCruiseNode[TI_BALL_CRUISE_NUM];
	TI_BALL_CRUISE_NODE_S struCruiseResNode[8];
	/* begin:	add by hjl	2013/1/7*/
	char  crz_name[TI_BALL_CRUISE_NAME_LEN];	//Ѳ��·����
	unsigned int crz_no;						//Ѳ��·����
	unsigned int crz_enable;					//�Ƿ�ʹ������·��
	/* end:	add by hjl	2013/1/7*/
	unsigned char byRes[64-40];
}TI_BALL_CRUISE_PARAM_S, *LPTI_BALL_CRUISE_PARAM_S;
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
typedef struct _TI_BALL_SETTING_PARAM_S_
{
	TI_U32 dwMask;				// 0: ��֧��,1:֧��
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
	TI_BALL_CRUISE_PARAM_S struCruiseParam;
	TI_U8 byAutoScanSpeed;			// �Զ�ɨ���ٶ�
	TI_U8 byABScanSpeed;			// ABɨ���ٶ�
	int nIdleActionIndex;			// ���ö���
	TI_U8 byIdleSec;				// ��������
	TI_U8 byIRISMode;				// ��Ȧģʽ:0:�ֶ�,1:�Զ�
	TI_U8 byAutoFlip;				// �Զ���ת:0:�ر�,1:��
	TI_U8 byDayNightMode;			//0:����ģʽ,1:ҹ��ģʽ,2:�Զ�ģʽ,3:��ʱģʽ
	TI_U8 byIRMode;					// Զ�����л�ģʽ:0:�Զ��л�Զ����,1:ͬʱ����Զ����
	TI_U8 byBLCMode;				// ���ⲹ��:0:�ر�,1:��
	TI_U8 byFrameNoise;				// ����:0:�ر�,1:��
	TI_U8 byZoomDisplay;			// �䱶��ʾ:0:�ر�,1:��
	TI_U8 byZoomSpeed;				// �䱶�ٶ�:0:����,1:����,2:����
	TI_U8 byWBMode;					// ��ƽ��:0:����,1:���� ,2:�Զ�,3:�ֶ�
	TI_U8 byWDRMode;				// ��̬:0:�ر�,1:��
	TI_U8 byAutoFocus;				// �Զ��۽�:0:�ر�,1:��
	TI_U8 byRes[32];
}TI_BALL_SETTING_PARAM_S, *LPTI_BALL_SETTING_PARAM_S;
// ����������
typedef struct _TI_BALL_RUN_PARAM_
{
	TI_U32 dwSize;
	TI_BALL_ALARM_PARAM_S struAlarmParam;
	TI_BALL_ONTIME_PARAM_S struOntimeParam;
	TI_BALL_SETTING_PARAM_S struSettingParam;
	TI_U8 byRes[64];
}TI_BALL_RUN_PARAM_S, *LPTI_BALL_RUN_PARAM_S;

//3A����
//--3A�����������Ͷ���
typedef enum _TI_DEV_3A_MASK_E_
{	//��Ȧ
	VCT_3A_AUTOIRIS		= 0x00000001,//�Զ���Ȧ
	VCT_3A_IRISLEVEL	= 0X00000002,//��Ȧ��ƽ
	//�۽�
	VCT_3A_AUTOFOCUS	= 0X00000004,//�Զ��۽�
	VCT_3A_FOCUSLEVEL	= 0X00000008,//����
	VCT_3A_MINFOCUSLEN 	= 0X00000010,//������С�۽�����		
	//�䱶
	VCT_3A_ZOOMSPEED	 = 0X00000020,//�䱶�ٶ�
	VCT_3A_AUTOPTZSPEED  = 0X00000040,//�����������
	//��ƽ����
	VCT_3A_AUTOALC		= 0X00000080,//�Զ���ƽ����
	VCT_3A_ALCLEVEL		= 0X00000100, //��ƽ����ֵ
	//��ת��
	VCT_3A_CTB			= 0X00000200,//��ת��
	VCT_3A_CTBLEVEL		= 0X00000400,//��ת�ڷ�ֵ������ת��Ϊ�Զ�ʱ��Ч
	//����
	VCT_3A_MIRROR		= 0X00000800,//����
	VCT_3A_FLIP			= 0X00001000,//��ת
	VCT_3A_AUTOFLIP		= 0X00002000,//�Զ���ת
	VCT_3A_PWDFREQ		= 0X00004000,//����Ƶ��1
	//����
	VCT_3A_IREXIST		= 0X00008000,//�Ƿ��к���
	VCT_3A_IRCFMODE		= 0X00010000,//IRCFģʽ
	VCT_3A_IRLIGHTTYPE	= 0X00020000,//���������
	//
	VCT_3A_WDR 			= 0X00040000,//�Ƿ��п�̬
	VCT_3A_WDRLEVEL		= 0X00080000,//��̬��ֵ
	VCT_3A_LOWILLUM		= 0X00100000,//���ն�
	VCT_3A_IMAGEMODE	= 0X00200000,//ͼ��ģʽ
	//����
	VCT_3A_SCENE		=  0X00400000,//����
	
	VCT_3A_ALL		  	= 0xFFFFFFFF,
}TI_DEV_3A_MASK_E;
typedef struct _TI_DEV_3A_PARA_S_
{
	TI_U8	u8Value;		//����ֵ
	TI_U8	u8Default;		//ȱʡ����ֵ
	TI_U8	u8Step;			//����ֵ����ֵ
	TI_U8	u8Res;
}TI_DEV_3A_PARA_S;

typedef struct _TI_DEV_3A_CFG_S_
{
	TI_U32				u32Size;
/*��Ч֧�ֵĲ������ò�������ʱ����Ч
�ڻ�ȡ��ʱ����Ч�������ж��豸�Ƿ�֧�ָò���*/	
	TI_DEV_3A_MASK_E	eSuppMask;
/*������Ч�Ĳ������ò�����ȡʱ����Ч
   �����õ�ʱ����Ч������ָ���������õĲ���*/	
	TI_DEV_3A_MASK_E	eSetMask;	
	TI_DEV_3A_PARA_S	struFlip;			//��תͼ�����·�ת
	TI_DEV_3A_PARA_S	struMirror;			//����ͼ�����ҷ�ת
	TI_DEV_3A_PARA_S	struPwdFreq;		//��ԴƵ��
	TI_DEV_3A_PARA_S	struScene;			//����,0:�Զ� 1:����2:����
	TI_DEV_3A_PARA_S	struIrcfMode;		//����ģʽ��0:�Զ���1:���죬2:����,3:��ʱģʽ
	TI_DEV_3A_PARA_S	struShutterSpeed;	//���ӿ��� 0-8  0���Զ����� 1��
											//1/25S�� 2��1/50S�� 3��1/100S�� 4��1/500S�� 5��1/1000S�� 
											//6��1/2000S�� 7��1/5000S�� 8��1/10000S
	TI_DEV_3A_PARA_S	struRes[26];
}TI_DEV_3A_CFG_S, *LPTI_DEV_3A_CFG_S;

//��ʱ����ģʽ����
typedef struct _TI_DEV_IRCFMODE_CFG_S_
{
	TI_U32 				u32Size;
	TI_U8				u8Enable;						//�Ƿ�����ʱ����ģʽ 0-�رգ�1-����
	TI_SEGMENT_S		struSeg[TI_MAX_IRCF_SEG_NUM][8];  //0--ÿ��1--������ 2--����һ7--������	
	TI_U8				u8Res1[32];
}TI_DEV_IRCFMODE_CFG_S;

#define DBG_LINE	printf("run line [%s %d]\n", __FILE__, __LINE__);

#ifdef __cplusplus
}
#endif



#endif
