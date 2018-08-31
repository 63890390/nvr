#ifndef _TI_NET_STRUCT_H_
#define _TI_NET_STRUCT_H_
#include "ti_type.h"
#include <netinet/in.h>

#define TI_USER_NAME_LEN		32	//�û�������	
#define TI_PASS_WORD_LEN		32	//���볤��	
#define TI_MAX_SUPPORT_CHN		1	//���֧��ͨ����
#define TI_MAC_ADDR_LEN			6	//mac��ַ����
#define TI_SERIALNO_LEN			48	//���кų���
#define TI_DEV_NAME_LEN			32	//�豸���Ƴ���


/*����Ƶ����ͷ*/
#define	TI_NET_STREAM_DATA_LEN	1360



typedef struct _TI_NET_HDR_S
{
	TI_U16	u16Version;
	TI_U16	u16CmdType;
	TI_U32   u32PacketSize;
	TI_U32	u32MagicFlag;
	TI_U32	u32PacketNo;
	TI_S32	s32ErrNo;
	TI_U8	u8Chn;
	TI_U8	u8Res[3];
}TI_NET_HDR_S, *LPTI_NET_HDR_S;
#define TI_NET_HDR_LEN (sizeof(TI_NET_HDR_S))

/* ��Ϊ��Ҫ��ǹ����PTZ���������,���Խṹ��Ĵ�С������֮ǰ�Ĵ�С����һ��*/
#pragma pack(2)
typedef struct _TI_NET_CTRL_PTZ_S_
{
	TI_U16	u16PtzCmd;		//��̨��������

	union
	{
		struct
		{
			TI_U8	u8Chn;			//��̨ͨ����
			TI_U8	u8Speed;		//�ٶ�
			TI_U8	u8PresetNo;
			TI_U8	u8Res[3];
		}struPreset;
		struct 
		{
			TI_U8	u8CruisePresetNo;
			TI_U8 	u8CruisePresetEnable;
			TI_U8	u8CruisePresetSec;
			TI_U8	u8CruisePresetSpeed;
		}struCruise;
		struct
		{
			TI_U8 u8SetVerticalPos;	// �Ƿ����ô�ֱλ��
			TI_U8	u8Speed;
		}struAutoScan;
		struct
		{
			TI_U8 u8SetVerticalPos;	// �Ƿ����ô�ֱλ��
			TI_U8	u8Speed;
		}struABScan;
		struct
		{
			TI_U8	u8IdleActionIndex;
			TI_U8	u8IdleSec;
		}struIdleAction;
		struct
		{
			TI_U8	u8OntimeIndex;			// 1-8��ĳ����ʱ��
			TI_U8	u8OntimeActionIndex;	// ��ʱ����������
			TI_U8	u8BeginHour;
			TI_U8	u8BeginMin;			
			TI_U8	u8EndHour;
			TI_U8	u8EndMin;
		}struOntimeAction;
		struct
		{
			TI_U8	u8AlarmTypeIndex;		// ��һ�ֱ���
			TI_U8	u8AlarmActionIndex;		// ��������������
			TI_U8 	u8AlarmDurationSec;
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
		TI_U8 u8OpenOrClose;	// 0:close, 1:open
		TI_U8 u8WorkMode;		// 0:�ֶ�,1:�Զ�
		TI_U8 u8IRMode;			// 0:Զ�����Զ��л�,1:Զ����ͬʱ����
		TI_U8 u8DayNightMode;	// 0:����ģʽ,1:ҹ��ģʽ,2:�Զ�ģʽ
		TI_U8 u8WBMode;			// 0 ����,1 ���� ,2 �Զ�,3 �ֶ�
		TI_U8 u8ZoomSpeed;		// 0 ����, 1 ����, 2 ����
		TI_U8 u8Bright;			// ����
		TI_U8 u8Contrast;		// �Աȶ�
		TI_U8 u8Saturation;		// ���Ͷ�
		TI_U8 u8Sharpness;		// ���
		TI_U8 u8Red;			// ��ɫ
		TI_U8 u8Blue;			// ��ɫ
		unsigned char u8Shutter;			// ���ӿ����ٶ�
	};

}TI_NET_CTRL_PTZ_S, *LPTI_NET_CTRL_PTZ_S;
#pragma pack()


/*�����¼��*/
typedef struct _TI_NET_LOGON_S
{
	TI_CHAR	szUsr[TI_USER_NAME_LEN];	/*��¼�û���*/
	TI_CHAR szPsw[TI_PASS_WORD_LEN];	/*��¼����*/
//	TI_U8	u8RecvAlarm;				/*�Ƿ���ܱ�����Ϣ*/
//	TI_U8	u8RecvCommData;				/*�Ƿ���ܴ��ڲɼ���Ϣ*/
	TI_U8	u8Res[20];					/*�����ֽ�*/
}TI_NET_LOGON_S, *LPTI_NET_LOGON_S;


/*���������*/
typedef struct _TI_NET_SEARCH_REQ_S_
{
	TI_U32	u32CliMultiIp;
	TI_U16	u16CliMultiPort;
    TI_U8	u8Res[10];
}TI_NET_SEARCH_REQ_S, *LPTI_NET_SEARCH_REQ_S;
	
/*������Ӧ��*/
typedef struct _TI_NET_SEARCH_RES_S_
{
	struct sockaddr_in	addrClient;
	
	TI_U8	u8SerialId[TI_SERIALNO_LEN];
	TI_U32	u32SoftVer;
	TI_U16	u16DevType;
	TI_U16	u16DevPort;
	TI_U32	u32DevIp;
	TI_U8	u8MacAddr[TI_MAC_ADDR_LEN];
	TI_U8	u8Dns;
	TI_U8	u8DHCP;	
	TI_U32	u32DevIpMask;
	TI_U32	u32DevGwAddr;
	TI_U32	u32DevDns1;
	TI_U32	u32DevDns2;
	TI_U32 	u32Capability0;
	TI_U32 	u32Capability1;
	TI_U32 	u32Capability2;
	TI_U8	u8MainDevType;
	TI_U8	u8SubDevType;
	TI_U16  u16PlateformCap;  //֧��ƽ̨
	TI_U32  u32UpTime;        //����ʱ��
}TI_NET_SEARCH_RES_S, *LPTI_NET_SEARCH_RES_S;

/*�������ð�*/
typedef struct _TI_NET_SEARCH_CFG_REQ_S
{	
	TI_U32	u32CliMultiIp;
	TI_U16	u16CliMultiPort;
	TI_U8	u8Res[2];
	TI_CHAR szUsrName[TI_USER_NAME_LEN];
	TI_CHAR szPsw[TI_PASS_WORD_LEN];
	TI_U8	u8SerialId[TI_SERIALNO_LEN];
	TI_U32	u32SoftVer;
	TI_U16	u16DevType;
	TI_U16	u16DevPort;
	TI_U32	u32DevIp;
	TI_U8	u8MacAddr[TI_MAC_ADDR_LEN];
	TI_U8	u8Dns;
	TI_U8	u8DHCP;	
	TI_U32	u32DevIpMask;
	TI_U32	u32DevGwAddr;
	TI_U32	u32DevDns1;
	TI_U32	u32DevDns2;
	TI_U32 	u32Capability0;
	TI_U32 	u32Capability1;
	TI_U32 	u32Capability2;	  //ʵ�ʿ���ƽ̨,syscfg��ȡ
	TI_U8	u8MainDevType;
	TI_U8	u8SubDevType;
	TI_U16  u16PlateformCap;  //�ܹ�֧��ƽ̨��Ӧ�ò����
	TI_U32  u32UpTime;        //����ʱ��
	
}TI_NET_SEARCH_CFG_REQ_S, *LPTI_NET_SEARCH_CFG_REQ_S; 

/*����������Ӧ��*/
typedef struct _TI_NET_SEARCH_CFG_RES_S_
{
	struct sockaddr_in	addrClient;
}TI_NET_SEARCH_CFG_RES_S, *LPTI_NET_SEARCH_CFG_RES_S;
/**�����ٷֱ���Ӧ��*/
typedef struct _TI_NET_UPDATE_PRECENT_RES_S_
{
	TI_U8	u8Percent;
	TI_U8	u8Res[31];
}TI_NET_UPDATE_PRECENT_RES_S, *LPTI_NET_UPDATE_PRECENT_RES_S;

/*����Ԥ����*/
typedef struct _TI_NET_PREV_REQ_S
{
	TI_CHAR	szUsr[TI_USER_NAME_LEN];		/*Ԥ���û���*/
	TI_CHAR szPsw[TI_PASS_WORD_LEN];		/*Ԥ������*/
	TI_U8	u8Ch;							/*Ԥ����Ƶͨ����*/
	TI_U8	u8StreamType;					/*Ԥ����������*/
	TI_U8	u8ProtocalType;					/*Ԥ��Э������*/
	TI_U8	u8Res1[1];						/*�����ֽ�*/
	TI_U32	u32DstIp;						/*Ԥ��Ŀ��ip ��ַ*/
	TI_U16  u16DstPort;						/*Ԥ��Ŀ�Ķ˿�*/
	TI_U8	u8Res2[18];						/*�����ֽ�*/
}TI_NET_PREV_REQ_S, *LPTI_NET_PREV_REQ_S;

//���ݰ�ͷ��ʽ
//========================================
//��������Ƶ�ְ�ͷ
typedef struct _TI_NET_STREAM_HDR_S
{
	TI_U32		u32MagicFlag;	//ħ����
	TI_U32		u32FrameNo;
	TI_U16		u16Version;		//�汾��Ϣ
	TI_U16		u16PacketSum;	//��Ƭͷ
	TI_U32		u32FrameLen;	//֡����
	TI_U8		u8FrameType;	//VIDEO_FRAME_I = 0x7,
								//VIDEO_FRAME_P = 0x8,
								//VIDEO_FRAME_B = 0xB,
								//AUDIO_FRAME_A = 0xA, 
	TI_U8		u8Res[3];	
}TI_NET_STREAM_HDR_S, *LPTI_NET_STREAM_HDR_S;

//��Ƭͷ//����Ƶ����
//========================================
//========================================
//��Ƭͷ//����Ƶ����
//========================================
typedef struct _TI_NET_STREAM_PIS_HDR_S
{
	TI_U32		u32MagicFlag;	//ħ����
	TI_U32		u32FrameNo;
	TI_U32		u32FrameOff;
	TI_U16		u16PacketNo;
	TI_U16		u16PacketLen;
	TI_U8		u8Res[4];
}TI_NET_STREAM_PIS_HDR_S, *LPTI_NET_STREAM_PIS_HDR_S;



/* ϵͳ������� */
typedef enum _TI_ERR_CODE_
{
	TI_ERR_SUCCESS   			= 0,			//�ɹ�
	TI_ERR_USER_NO_EXIST		= -1,			//�û���������
	TI_ERR_PASSWORD 			= -2,			//�������
	TI_ERR_NO_PERMIT			= -3,			//��Ȩ��
	TI_ERR_NO_INIT				= -4,			//û�г�ʼ��
	TI_ERR_CHANNEL				= -5,			//ͨ���Ŵ���
	TI_ERR_OVER_MAX_LINK		= -6,			//�������������
	TI_ERR_VERSION_NO_MATCH		= -7,			//Э��汾����
	TI_ERR_CREATE_SOCKET		= -8,			//�����׽��ִ���
	TI_ERR_SET_SOCKET			= -9,			//�����׽������Դ���
	TI_ERR_LISTEN_FAIL			= -10,			//��������
	TI_ERR_BIND_FAIL			= -11,			//�󶨴���
	TI_ERR_CONNECT_FAIL 		= -12,			//����ʧ��
	TI_ERR_SEND_FAIL			= -13,			//����ʧ��
	TI_ERR_RECV_FAIL			= -14,			//����ʧ��
	TI_ERR_RECV_TIME_OUT	 	= -15,			//���ճ�ʱ
	TI_ERR_ORDER_ERR	 		= -16,			//����˳�����
	TI_ERR_PARAMETER			= -17,			//��������
	TI_ERR_NO_DISK				= -18,			//�޴���
	TI_ERR_DISK_NUM				= -19,			//����������
	TI_ERR_DISK_FULL			= -20,			//����������
	TI_ERR_DISK_ERR				= -21,			//���̳���
	TI_ERR_NO_SUPPORT			= -22,			//���������֧��
	TI_ERR_DEV_BUSY				= -23,			//�豸æ����
	TI_ERR_MODIFY_FAIL			= -24,			//�޸�ʧ��
	TI_ERR_DISK_FORMATING		= -25,			//�������ڸ�ʽ��
	TI_ERR_NO_RESOURCE			= -26,			//����Դ����
	TI_ERR_OPERATE_FAIL			= -27,			//����ʧ��
	TI_ERR_VOICE_OPEN			= -28,			//����Ƶʧ��
	TI_ERR_INPUT_TIME_ERR		= -29,			//���������ʱ��
	TI_ERR_NO_FILE				= -30,			//���ļ�
	TI_ERR_FILE					= -31,			//������ļ���Ϣ
	TI_ERR_ALLOC_RESOURCE		= -32,			//������Դʧ��
	TI_ERR_WRITE_FLASH			= -33,			//дFlash ʧ��
	TI_ERR_PROTACAL				= -34,			//�����Э��
	TI_ERR_MANULE_STOP			= -35,			//�ֶ�ֹͣ
	TI_ERR_DATA_FORMAT			= -36,			//��������ݸ�ʽ
	TI_ERR_DATA_SIZE			= -37,			//��������ݳ���
	TI_ERR_NO_MORE_FILE			= -38,			//û�и����ļ� ���ҽ���
	TI_ERR_IS_FINDING			= -39,			//���ڲ���
}TI_ERR_CODE;


#endif /*  #ifndef _TI_NET_STRUCT_H_ */
