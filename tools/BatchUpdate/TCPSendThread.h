//---------------------------------------------------------------------------

#ifndef TCPSendThreadH
#define TCPSendThreadH
//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Classes.hpp>
#include <winsock.h>
//---------------------------------------------------------------------------

#define HI_NET_VERSION	 0x0100
#define HI_NET_MAGIC_FLAG	 0x30404891UL

#define HI_NAME_LEN				32	//���Ƴ���
#define HI_USER_NAME_LEN			32	//�û�������	
#define HI_PASS_WORD_LEN		32	//���볤��

typedef unsigned char	HI_U8;
typedef unsigned short	HI_U16;
typedef unsigned long	HI_U32;
typedef char			HI_S8;
typedef short			HI_S16;
typedef long			HI_S32;

typedef enum _HI_NET_CMD_TYPE_E_
{
/*******************************************/
	HI_CMD_LOGON_SERVER	= 0x1001,
	HI_CMD_LOGOFF_SERVER	= 0x1002,	
	HI_CMD_OPEN_PREVIEW	= 0x1003,
	HI_CMD_CLOSE_PREVIEW	= 0x1004,
	HI_CMD_OPEN_TALK		= 0x1006,				//�򿪶Խ�
	HI_CMD_CLOSE_TALK		= 0x1007,				//�رնԽ�
	HI_CMD_START_UPGRADE= 0x1008,				//��������
	HI_CMD_STOP_UPGRADE	= 0x1009,				//ֹͣ����	
	HI_CMD_START_FIND_FILE= 0x100a,				//��ʼ����
	HI_CMD_STOP_FIND_FILE	= 0x100b,				//ֹͣ����
	HI_CMD_START_REC		= 0x100c,				//��ʼ¼�����ػ�ط�
	HI_CMD_STOP_REC		= 0x100d,				//ֹͣ¼�����ػ�ط�	
/*******************************************/
}HI_NET_CMD_TYPE_E;

typedef enum _HI_NET_ERR_CODE_E_
{
	HI_NET_ERR_SUCCESS   			= 0,
	HI_NET_ERR_USER_NO_EXIST		= -1,	
	HI_NET_ERR_PASSWORD 			= -2,
	HI_NET_ERR_NO_PERMIT			= -3,
	HI_NET_ERR_NO_INIT				= -4,
	HI_NET_ERR_CHANNEL				= -5,
	HI_NET_ERR_OVER_MAX_LINK		= -6,
	HI_NET_ERR_VERSION_NO_MATCH	= -7,
	HI_NET_ERR_CREATE_SOCKET		= -8,
	HI_NET_ERR_SET_SOCKET			= -9,
	HI_NET_ERR_LISTEN_FAIL			= -10,
	HI_NET_ERR_BIND_FAIL			= -11,
	HI_NET_ERR_CONNECT_FAIL 		= -12, 
	HI_NET_ERR_SEND_FAIL			= -13,
	HI_NET_ERR_RECV_FAIL			= -14,
	HI_NET_ERR_RECV_TIME_OUT	 	= -15,	
	HI_NET_ERR_ORDER_ERR	 		= -16,
	HI_NET_ERR_PARAMETER			= -17,
	HI_NET_ERR_NO_DISK				= -18,
	HI_NET_ERR_DISK_NUM			= -19,
	HI_NET_ERR_DISK_FULL			= -20,
	HI_NET_ERR_DISK_ERR				= -21,
	HI_NET_ERR_NO_SUPPORT			= -22,
	HI_NET_ERR_DEV_BUSY				= -23,
	HI_NET_ERR_MODIFY_FAIL			= -24,
	HI_NET_ERR_DISK_FORMATING		= -25,
	HI_NET_ERR_NO_RESOURCE		= -26,
	HI_NET_ERR_OPERATE_FAIL		= -27,
	HI_NET_ERR_VOICE_OPEN			= -28,
	HI_NET_ERR_INPUT_TIME_ERR		= -29,
	HI_NET_ERR_NO_FILE				= -30,
	HI_NET_ERR_FILE				= -31,
	HI_NET_ERR_ALLOC_RESOURCE		= -32,
	HI_NET_ERR_WRITE_FLASH			= -33,
	HI_NET_ERR_PROTACAL			= -34,
	HI_NET_ERR_MANULE_STOP			= -35,
	HI_NET_ERR_DATA_FORMAT		= -36,
	HI_NET_ERR_DATA_SIZE			= -37,			//��������ݳ���
	HI_NET_ERR_NO_MORE_FILE			= -38,			//û�и����ļ� ���ҽ���
	HI_NET_ERR_IS_FINDING			= -39,			//���ڲ���	
	HI_NET_ERR_KEEP_ALIVE			= -40
}HI_NET_ERR_CODE_E;

typedef struct _HI_NET_HDR_S
{
	HI_U16	u16Version;
	HI_U16	u16CmdType;
	HI_U32   u32PacketSize;
	HI_U32	u32MagicFlag;
	HI_U32	u32PacketNo;
	HI_S32	s32ErrNo;
	HI_U8	u8Chn;
	HI_U8	u8Res[3];
}HI_NET_HDR_S, *LPHI_NET_HDR_S;

typedef struct _HI_NET_UPGRADE_S
{
	char		szUsr[HI_USER_NAME_LEN];	/*��¼�û���*/
	char		szPsw[HI_PASS_WORD_LEN];	/*��¼����*/
	HI_U8	u8Res[20];					/*�����ֽ�*/
}HI_NET_UPGRADE_S, *LPHI_NET_UPGRADE_S;

typedef struct _HI_NET_UPDATE_INFO_S
{
	HI_U32		u32UpdateInfoLen;
	HI_U8		u8Res[32];
}HI_NET_UPDATE_INFO_S, *LPHI_NET_UPDATE_INFO_S;
typedef struct _HI_NET_UPDATE_PRECENT_RES_S_
{
	HI_U8	u8Percent;
	HI_U8	u8Res[31];
}HI_NET_UPDATE_PRECENT_RES_S, *LPHI_NET_UPDATE_PRECENT_RES_S;

//---------------------------------------------------------------------------
class TTCPSendThread : public TThread
{            
private:
    SOCKET sendSock;
    FILE *kernel;
    FILE *cfg;
    int kernelSize;
    int filesysSize;
    int cfgSize;
    int totalSendLen;
    int devNo;
    int progress;
    SOCKET tcpSock;
    HI_U32 u32PackNo;
    SOCKADDR_IN clientSockAddr;
    char updateFilePath[1024];
protected:
    void __fastcall Execute();
public:
    __fastcall TTCPSendThread(bool CreateSuspended);
    __fastcall TTCPSendThread(bool CreateSuspended, SOCKET sock, int devNo, SOCKADDR_IN *pClientSockAddr);
    void __fastcall UpdateLable();
    void __fastcall EnableButton();
    void __fastcall UpdateMac();
    void __fastcall UpdateLabelAndProgressColor();
    void __fastcall UpdateProgress();
    void __fastcall GetUpdateFilePath();
    void __fastcall MakeTcpHeader(HI_NET_HDR_S *pNetHdr, HI_U32 u32PackLen, 
				HI_U32 u32PackCmd, HI_U32 u32PackNo, HI_S32 s32ErrNo );
    int __fastcall ConnectToDevice();
    int __fastcall SendTcpData(unsigned char *data, int sendlen);
    int __fastcall RecvTcpData(unsigned char *data, int datalen, int recvlen);
    int __fastcall SendUpdateHeader();
    int __fastcall SendUpdateFileInfo(const char *szUpdateFileName);
    int __fastcall SendUpdateFile(const char *szUpdateFileName);
    int __fastcall RecvUpdateProgress();
};
//---------------------------------------------------------------------------
#endif
