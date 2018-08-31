#ifndef __TI_NET_LOGON_H_
#define __TI_NET_LOGON_H_

#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

#include "net_api.h"
#include "ti_type.h"

#define TI_NET_LOGON_FLAG					0x12ab34cd
#define TI_NET_SERVER_PORT 					"6080"
#define TI_NET_KEEP_ALIVE_TIME				30
#define TI_NET_IPADDR_LEN					128
/*��¼�����*/
#define TI_NET_MAX_SUPPORT_LOGONE			256
#define TI_NET_MAX_SUPPORT_PREVIEW			256

//�����ص�����
typedef void (*fAlarmCb)(long logonHandle, void* data, int dataSize);

/*��¼�û���Ϣ�ṹ��*/
typedef struct _TI_LOGON_USER_INFO
{
	int 		logonSock;	//�׽���
	int 		port;			//�˿ں�
	char 	ipAddr[TI_NET_IPADDR_LEN];//ip��ַ
	char 	userName[32];	//�û���
	char 	passWord[32];	//����
	TI_U32 	keepAliveTime;	//���������
	TI_U32	packetNo;
	
	int		sendPipe[2];
	int		recvPipe[2];

	int		alarm;
	
	volatile int 		quit;
	pthread_t thid;
	fAlarmCb cbAlarmFun;	//�����ص�����
	void *pUserData;		//�û�����
}TI_LOGON_USER_INFO;



int ti_logon_pipe_session(TI_LOGON_USER_INFO *pLogonInfo, 
							const void *sendBuf, int sendLen, 
							char *recvBuf, int recvBufLen);

/*��¼�豸
	DesIP:Ŀ��IP��ַ;
	User:�û���;
	Password:����;
	port:�˿�;
	keep_alive_time:���������.
	alarm_funcb:�����ص�������
	�ɹ������û���Ϣ���
	*/
long ti_net_logon(const char* DesIP, const char* User, const char* Password, const char* port, 
				  TI_U32 keep_alive_time, fAlarmCb cbAlarmFun, void *pUserData);
/*�˳���¼
	handle:�û���Ϣ���
	�ɹ�����TI_SUCCESS
	*/
int ti_net_logout(long handle);

#endif

