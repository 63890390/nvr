
#ifndef __JXJ_CU_LOGON_H__
#define __JXJ_CU_LOGON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ipnc_lib.h"
#include "j_sdk.h"

// Э��ͷ
#define JPF_PROTO_HEAD_MAGIC		0x6a786a2d		/*"jxj-"*/

#define SET_PROTO_HEAD_M(head) \
	((head)->magic = htonl(JPF_PROTO_HEAD_MAGIC))
#define SET_PROTO_HEAD_S(head, seq) \
	(head)->seq = htonl(seq)
#define SET_PROTO_HEAD_L(head, len) \
	(head)->payload_len = htonl(len)
#define SET_PROTO_HEAD_P(head, packets) \
	(head)->tot_packets = packets
#define SET_PROTO_HEAD_N(head, no) \
	(head)->packet_no = no

#define VALID_PROTO_HEAD(head)	\
	(ntohl((head)->magic) == JPF_PROTO_HEAD_MAGIC)
#define GET_PROTO_HEAD_S(head) \
	ntohl((head)->seq)
#define GET_PROTO_HEAD_L(head) \
	ntohl((head)->payload_len)
#define GET_PROTO_PACKETS(head) \
	((head)->tot_packets)
#define GET_PROTO_PACKNO(head) \
	((head)->packet_no)

typedef struct jpf_proto_head
{
	uint32_t        magic;
	uint32_t   		seq;
	uint32_t        payload_len;
	uint8_t			tot_packets;
	uint8_t			packet_no;
	uint16_t		reserve;
}jpf_proto_head_t;

//�����ص�����
typedef void (*fAlarmCb)(long logonHandle, void* data, int dataSize);
typedef struct _JXJ_CU_LOGON_S_
{
	volatile int  quit;		//�߳��˳����
	
	int 	sock;			//�׽���
	int		sendPipe[2];	//���͹ܵ�
	int		recvPipe[2];	//���չܵ�

	int 	port;			//�˿ں�
	char 	userName[32];	//�û���
	char 	passWord[32];	//����
	int 	keepAliveTime;	//���������
	
	char 	ipAddr[64];		//ip��ַ
	
	pthread_t pid;			//�߳�ID
	pthread_mutex_t lock;	//������
	int		alarm;
	fAlarmCb cbAlarmFun;	//�����ص�����
	void *pUserData;		//�û����� 

	JIrcutControl ircutCfg;
	int recvIrcutCfg;
	JPictureInfo picCfg;
	int recvPicCfg;
	JPictureInfo defPicCfg;
	int recvDefPicCfg;
}JXJ_CU_LOGON_S;


/*BUG����*/
#define DEBUG_CLIENT
#ifdef DEBUG_CLIENT
	#define __DBUG(fmt, args...) fprintf(stderr, "DEBUG(%s:%d):" fmt, __func__, __LINE__, ## args)
#else
	#define __DBUG(fmt, args...) 
#endif

#define __ERR(fmt, args...) fprintf(stderr, "ERROR(%s:%d):" fmt, __func__, __LINE__, ## args)

/*
	pIpAddr: ip��ַ.
	pUsr   : �û���.
	pPwd   : ����.
	pPort  : �˿�.
	cbAlarmFun: �����ص�����.
	pUserData:  �û�����.
	
�ɹ����ط���ռ���, ʧ�ܷ�����.
*/
long jxj_cu_logon(const char* pIpAddr, const char* pUsr, 
					  const char* pPwd, const char* pPort, 
				      fAlarmCb cbAlarmFun, void* pUserData);

/*
	logonHandle: ��¼���.
*/
int jxj_cu_logout(long logonHandle);

/*��Ӧxml���ݽ���:
	chn: ͨ����.
	type: ������.
	xmlData: xml����.
	pCfg: �����Ӧ��������.
	cfgSize: ���ò�����С.
�ɹ�����0, ʧ�ܷ���-1.
*/
/*int jxj_cu_get_xml_parse(int chn, JParamId type, 
							 char *xmlData, void * pCfg, int cfgSize);*/
/*��ȡ������Ϣ:
	logonHandle: ��¼���.
	type: ������.
	pCfg: �����Ӧ��������.
	cfgSize: ���ò�����С.
�ɹ�����0, ʧ�ܷ���-1.
*/
int jxj_cu_cfg_get(long logonHandle, JParamId type, 
					   void * pCfg, int cfgSize);
/*���ò�����Ϣ:
	logonHandle: ��¼���.
	type: ������.
	pCfg: ���ò�������.
	cfgSize: ���ò�����С.
�ɹ�����0, ʧ�ܷ���-1.
*/
int jxj_cu_cfg_set(long logonHandle, JParamId type, 
					   void * pCfg, int cfgSize);

/*���Ե�¼: �ɹ�����0, ʧ�ܷ���-1;
*/
int jxj_cu_logon_test(const char* pDstIP, const char* pUsr, 
					  const char* pPwd, const char* pPrt);

#endif


