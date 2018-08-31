#ifndef __NVR_NET_STRUCT_H__
#define __NVR_NET_STRUCT_H__

#include <stdint.h>
#include <netinet/in.h>
#include <nvr_struct.h>

typedef struct _NVR_NET_HDR_S
{
	uint32_t	u32MagicFlag;
	uint32_t   u32PacketSize;
	uint16_t	u16CmdType;
	int8_t	s8Chn;
	int8_t	s8ErrNo;
}NVR_NET_HDR_S, *LPNVR_NET_HDR_S;

#define NVR_NET_HDR_LEN	sizeof(NVR_NET_HDR_S)

/*�����¼��*/
typedef struct _NVR_NET_LOGON_S
{
	char	szUsr[NVR_USER_NAME_LEN];		/*��¼�û���*/
	char 	szPsw[NVR_PASS_WORD_LEN];		/*��¼����*/
	uint8_t	u8Res[20];						/*�����ֽ�*/
}NVR_NET_LOGON_S, *LPNVR_NET_LOGON_S;
//==============================================================
/*���������*/
typedef struct _NVR_NET_SEARCH_REQ_S_
{
	uint32_t	u32CliMultiIp;
	uint16_t	u16CliMultiPort;
    uint8_t		u8Res[10];
}NVR_NET_SEARCH_REQ_S, *LPNVR_NET_SEARCH_REQ_S;

/*������Ӧ��*/
typedef struct _NVR_NET_SEARCH_RES_S_
{
	struct sockaddr_in	addrClient;
	
	uint8_t		u8SerialId[NVR_SERIALNO_LEN];
	uint32_t	u32SoftVer;
	uint16_t	u16DevType;
	uint16_t	u16DevPort;
	uint32_t	u32DevIp;
	uint8_t		u8MacAddr[NVR_MAC_ADDR_LEN];
	uint8_t		u8Dns;
	uint8_t		u8DHCP;	
	uint32_t	u32DevIpMask;
	uint32_t	u32DevGwAddr;
	uint32_t	u32DevDns1;
	uint32_t	u32DevDns2;
	uint32_t 	u32Capability0;
	uint32_t 	u32Capability1;
	uint32_t 	u32Capability2;
	uint8_t		u8MainDevType;
	uint8_t		u8SubDevType;
	uint8_t		u8Res[6];
}NVR_NET_SEARCH_RES_S, *LPNVR_NET_SEARCH_RES_S;
//==========================================================================


//====================================================================
//�ͻ�����������ṹ��
typedef struct _NVR_NET_REQ_PARAM_S_
{
	uint32_t 	paramCmd;
	int 		dataSize;
	char		paramData[2048];
	uint8_t	u8Res[6];
	
}NVR_NET_REQ_PARAM_S, *LPNVR_NET_REQ_PARAM_S;
//====================================================================

//�������ؽṹ����Ϣ
typedef struct _NVR_NET_SEARCH_S_
{
	int devCnt;
	long lHandle;
	
}NVR_NET_SEARCH_S, *LPNVR_NET_SEARCH_S;


#endif

