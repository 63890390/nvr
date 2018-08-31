/******************************************************************************

                  ��Ȩ���� (C), 2011-2015, ���Žݵ���

 ******************************************************************************
  �� �� ��   : nvr_ipc_api.c
  �� �� ��   : v2.0
  ��    ��   : ������
  ��������   : 2011��9��8��
  ����޸�   :
  ��������   : ���̼�ͨѶ ��Ϣ��fifo�ķ�װ
  �����б�   :
              nvr_del_fifo
              nvr_fifo_init
              nvr_ipc_clear_msg
              nvr_ipc_del_msq
              nvr_ipc_msg_init
              nvr_ipc_msg_init2
              nvr_ipc_msg_recv
              nvr_ipc_msg_send
              nvr_pthread_wait
  �޸���ʷ   :
  1.��    ��   : 2011��9��8��
    ��    ��   : ������
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "nvr_ipc_api.h"
#include <sys/time.h>
/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ����ʵ��                                     *
 *----------------------------------------------*/
int nvr_ipc_msg_init2(char *pName, int nId)
{
	int	    nMsqId  = 0;
	key_t	nKeyMsg = 0;

	/* ��Ϣ���г�ʼ�� */
	if ((nKeyMsg = ftok(pName, nId)) == -1)
	{
		return NVR_IPC_INIT_FTOK_ERR;
	}

	if ((nMsqId  = msgget(nKeyMsg, IPC_CREAT | 0666)) == -1)
	{
		return NVR_IPC_MSG_Get_ERR;
	}
	return nMsqId;	 
}


int nvr_ipc_msg_init(int nId)
{
	int	    nMsqId  = 0;
	key_t	nKeyMsg = 0;

	/* ��Ϣ���г�ʼ�� */
	if ((nKeyMsg = ftok(".", nId)) == -1)
	{
		return NVR_IPC_INIT_FTOK_ERR;
	}

	if ((nMsqId  = msgget(nKeyMsg, IPC_CREAT | 0666)) == -1)
	{
		return NVR_IPC_MSG_Get_ERR;
	}
	return nMsqId;	 
}

int nvr_ipc_msg_send(int nMsqId, LPNVR_MSG_S lpStMsg, int nMsgBodyLen, int nWait)
{
	int nRet = 0;

	nRet = msgsnd(nMsqId, lpStMsg, nMsgBodyLen,  nWait ? 0 : IPC_NOWAIT);
	return nRet;	
}

int nvr_ipc_msg_recv(int nMsqId, LPNVR_MSG_S lpStMsg, int nMsgBodyLen, int nWait)
{
	int nRet = 0;

	nRet = msgrcv(nMsqId, lpStMsg, nMsgBodyLen, 0,  nWait ? 0 : IPC_NOWAIT);
	return nRet;
}

int nvr_ipc_clear_msg(int nMsqId, LPNVR_MSG_S lpStMsg, int nMsgBodyLen)
{
	int nCount = 0;
	int nRet   = 0;
	
    for (nCount = 0; nCount < 1024; nCount++)
    {
        if ((nRet = msgrcv(nMsqId, lpStMsg, nMsgBodyLen, 0, IPC_NOWAIT)) < 1)
        {
            break;
        }
    }
	return 0;
}

int nvr_ipc_del_msq(int nMsqId)
{
	if (msgctl(nMsqId, IPC_RMID, 0) == -1)
	{
		return(-1);
	}
	return(0);
}

int nvr_fifo_init(char *name)
{
	return mkfifo(name, 0777);
}

int nvr_del_fifo(char *name)
{
	return unlink(name);
}

int nvr_pthread_wait(pthread_mutex_t *pMutex, pthread_cond_t *pCond, int nTimeOut)
{
	struct timeval now;
	struct timespec timeout;

	if (nTimeOut != 0)
	{
		gettimeofday(&now, NULL);
		timeout.tv_sec  = now.tv_sec + nTimeOut/1000;
		timeout.tv_nsec= (now.tv_usec + (nTimeOut%1000) * 1000) * 1000;
	}	

    	pthread_mutex_lock(pMutex);
	if (nTimeOut == 0)
		pthread_cond_wait(pCond, pMutex);
	else
    		pthread_cond_timedwait(pCond, pMutex, &timeout);
    	pthread_mutex_unlock(pMutex);

	return NVR_IPC_SUCCESS;
}

