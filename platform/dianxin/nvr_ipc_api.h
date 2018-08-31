#ifndef _NVR_IPC_API_H
#define _NVR_IPC_API_H
/*
* Copyright (c) 2010
* All rights reserved.
* 
* filename:nvr_ipc_api.h
* 
* func:���ļ�ʵ���˶�linux �µ�Posix��Ϣ���еķ�װ
* 
* author : hi
* createdate: 2010-10-10
*
* modify list: 
* 
*/
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct _NVR_MSG_S
{
	unsigned long ulMsgType; /* ��Ϣ���ͣ����� > 0 */
	char          szMsg[1024];/* ��Ϣ�ı� */
}NVR_MSG_S, *LPNVR_MSG_S;

typedef enum _IPC_ERR_E
{
	NVR_IPC_SUCCESS       = 0,
	NVR_IPC_INIT_FTOK_ERR = -1,
	NVR_IPC_MSG_Get_ERR   = -2,
}IPC_ERR_E;
//=================================================================
//����: nvr_ipc_msg_init 
//
//����: ��ʼ��һ����Ϣ����
//
//����:nId ����:��ʼ����Ϣ����ʱ�õ�һ�������
//				(��ͬ����Ϣ����Ӧ���ò�ͬ�������)
//
//
//����: �ɹ����ط�����Ϣ���б�ʶֵ > 0 ʧ�ܷ��� _IPC_ERR_E�еĴ�����			
//=================================================================
int nvr_ipc_msg_init(int nId);

int nvr_ipc_msg_init2(char *pName, int nId);

//=================================================================
//����: nvr_ipc_msg_init 
//
//����: ����һ����Ϣ
//
//����:nMsqId  ����:��Ϣ���б�ʶֵ
//	   lpStMsg ����:��Ϣ�� 		   
//	   nWait   ����:0 ��Ϣ������ʱ����Ҫ���� 1 ��Ϣ������ʱ���� 
//
//����: �ɹ�����NVR_IPC_SUCCESS	ʧ�ܷ���-1		
//=================================================================
int nvr_ipc_msg_send(int nMsqId, LPNVR_MSG_S lpStMsg, int nMsgBodyLen,int nWait);

//=================================================================
//����: nvr_ipc_msg_recv 
//
//����: ����һ����Ϣ
//
//����:nMsqId  ����:��Ϣ���б�ʶֵ
//	   lpStMsg ����:��Ϣ�� 		   
//	   nWait   ����:0 ��Ϣ���гʿ�ʱ�������ȴ����Ϸ���-1
//					1 �ڶ��гʿյ�����ʱ����ȡ�����ȴ�
//
//����: �ɹ�����szMsg��ʵ�����ݳ��� ʧ�ܷ���-1	
//=================================================================
int nvr_ipc_msg_recv(int nMsgId, LPNVR_MSG_S lpStMsg, int nMsgBodyLen, int nWait);

//=================================================================
//����: nvr_ipc_clear_msg 
//
//����: �����Ϣ����
//
//����:nMsqId  ����:��Ϣ���б�ʶֵ
//	   lpStMsg ����:ֻ�����һ��NVR_MSG_S����
//
//����: �ɹ�����NVR_IPC_SUCCESS ʧ�ܷ���-1	
//=================================================================
int nvr_ipc_clear_msg(int nMsgId, LPNVR_MSG_S lpStMsg, int nMsgBodyLen);

//=================================================================
//����: nvr_ipc_del_msq 
//
//����: ɾ����Ϣ����
//
//����:nMsqId  ����:��Ϣ���б�ʶֵ
//
//����: �ɹ�����NVR_IPC_SUCCESS ʧ�ܷ���-1	
//=================================================================
int nvr_ipc_del_msq(int nMsqId);

//=================================================================
//����: nvr_fifo_init 
//
//����: ���������ܵ�
//
//����:name  �����ܵ�·��
//
//����: �ɹ�����NVR_IPC_SUCCESS ʧ�ܷ���-1	
//=================================================================
int nvr_fifo_init(char *name);

//=================================================================
//����: nvr_fifo_init 
//
//����: ɾ�������ܵ�
//
//����:name  �����ܵ�·��
//
//����: �ɹ�����NVR_IPC_SUCCESS ʧ�ܷ���-1	
//=================================================================
int nvr_del_fifo(char *name);
//=================================================================
//����: nvr_fifo_init 
//
//����: ͨ��pthread_mutex_t pthread_cond_t ��ģ���¼��ȴ�
//
//����:nTimeOut  :�ȴ���ʱʱ��
//
//����: �ɹ�����NVR_IPC_SUCCESS ʧ�ܷ���-1	
//=================================================================
int nvr_pthread_wait(pthread_mutex_t *pMutex, pthread_cond_t *pCond, int nTimeOut);

#ifdef __cplusplus
}
#endif 

#endif

