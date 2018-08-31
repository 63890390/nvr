
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include "nvr_rtsp_debug.h"
#include "nvr_rtsp_global.h"
#include "nvr_rtsp_session.h"
#include "nvr_rtsp_h264.h"
#include "nvr_rtsp_mjpeg.h"
#include "nvr_rtsp_transfer.h"
#include <net_api.h>



NVR_RTSP_SVR	         gRtspSvr;
pthread_mutex_t		 gRtspMutex;

CheckUserCallback    gCheckUserCb = NULL;
RequestIDRCallback	 gRequestIdrCb = NULL;
GetVideoCallback     gGetVideoCb  = NULL;
GetAudioCallback     gGetAudioCb  = NULL;
MsgCallback		    gMsgCb        = NULL;
AllocMemCallback     gAllocMemCb	= NULL;
FreeMemCallback     gFreeMemCb 	= NULL;


int     nvr_rtsp_set_cb(CheckUserCallback checkUserCb,
                        RequestIDRCallback reqIdrCb,
                        GetVideoCallback  getVideoCb,
                        GetAudioCallback  getAudioCb,
                        MsgCallback	  msgCb,
                        AllocMemCallback allocMemCb,
                        FreeMemCallback freeMemCb)
{
	gCheckUserCb = checkUserCb;
	gRequestIdrCb = reqIdrCb;
	gGetVideoCb  = getVideoCb;
	gGetAudioCb  = getAudioCb;
	gMsgCb	 	=  msgCb;
	gAllocMemCb		= allocMemCb;
	gFreeMemCb		= freeMemCb;
	return 0;
}

void   rtsp_socket_build(int *pSockArray, int *pSockNum)
{
	struct list_head *pos, *q;
	RTSP_SESSION_S *pSess = NULL;
	*pSockNum     = 1;
	pSockArray[0] = gRtspSvr.nSvrSocket;
	list_for_each_safe(pos, q, &(gRtspSvr.sessList.list))
	{
		pSess = list_entry(pos, RTSP_SESSION_S , list);
		if(NULL != pSess && pSess->nRtspSocket > 0)
		{
			pSockArray[*pSockNum] = pSess->nRtspSocket;
			*pSockNum += 1;
		}
	}
}

int    rtsp_new_conn_proc()
{
	int  nLen = 0, nClientSock = 0, nRecvLen = 0;
	struct sockaddr_in adrrClient;
	char szBuff[RTSP_MAX_PROTOCOL_BUFFER] = {0};
	RTSP_SESSION_S *pSess = NULL;
	nLen = sizeof(adrrClient);
	if((nClientSock = net_tcp_block_accept(gRtspSvr.nSvrSocket,
	                                       (struct sockaddr *)&adrrClient, &nLen)) < 0)
	{
		RTSP_PRINT("rtsp_new_conn_proc accept error\n");
		return -1 ;
	}
	RTSP_PRINT("recv a new rtsp connect \n");
	net_set_sock_noblock(nClientSock);
	net_set_sock_attr(nClientSock, 1, 0, 0, 0, 0);
	net_sock_set_linger(nClientSock);
	net_set_sock_nodelay(nClientSock);
	if(net_select(&nClientSock, 0x1, 0x1, 15000) != (0x10000 | nClientSock))
	{
		RTSP_PRINT("rtsp_new_conn_proc client select error\n");
		net_close_socket(&nClientSock);
		return -1 ;
	}
	if((nRecvLen = net_tcp_noblock_recv(nClientSock, szBuff, sizeof(szBuff),
	                                    0, 5000)) <= 0)
	{
		RTSP_PRINT("rtsp_new_conn_proc client recv error\n");
		net_close_socket(&nClientSock);
		return -1 ;
	}
	RTSP_PRINT("rtsp_new_conn_proc recv:%s\n",
	           szBuff);
	/*����rtsp�Ự������������rtsp�Ự����֮��*/
	if((pSess = rtsp_session_create(nClientSock)) == NULL)
	{
		/*�����µ�rtsp session ʧ��*/
		net_close_socket(&nClientSock);
		return -1 ;
	}
	memcpy(pSess->szBuffRecv, szBuff, RTSP_MAX_PROTOCOL_BUFFER);
	pSess->nMsgSize = nRecvLen;
	/*����rtsp�Ự��Ϣ*/
	if((nRecvLen = rtsp_session_process(pSess)) != 0)
	{
		RTSP_PRINT("close rtsp sid %s  chn %d \n", pSess->szId, pSess->nChId);
		rtsp_session_close(pSess);
		rtsp_list_client();
		return -1 ;
	}
	return 0;
}

void *rtsp_svr_proc(void *arg)
{
	char szPort[32] = {0};
	int  nSocket[32] = {0};
	int  nAddrLen = 0, nSocketNum = 0, nRet = 0, nRecvLen = 0;
	struct list_head *pSessPoss = NULL, *pSessN = NULL;
	RTSP_SESSION_S   *pSess = NULL;
	prctl(PR_SET_NAME, "RTSPSVR");
	sprintf(szPort, "%d", gRtspSvr.nSvrPort);
	if((gRtspSvr.nSvrSocket = net_tcp_listen(NULL, szPort, &nAddrLen)) < 0)
	{
		RTSP_PRINT("rtsp_svr_proc  net_tcp_listen %s error %s\n", szPort, strerror(errno));
		return (void *)NULL;
	}
	gRtspSvr.nSvrExits = 0;
	while(gRtspSvr.nSvrExits == 0)
	{
		/*���rtsp�Ự״̬*/
		check_rtsp_session_state();
		/**/
		rtsp_socket_build(nSocket, &nSocketNum);
		if((nRet = net_select(nSocket, nSocketNum, 0x1, 5000/*15000*/)) < 0)
		{
			sleep(1);
			RTSP_PRINT("rtsp_svr_proc select error\n");
			continue ;
		}
		/*time out*/
		if(nRet == 0)
			continue;
		if(nRet == (gRtspSvr.nSvrSocket | 0x10000))
		{
			/* Check if a connect has occured  */
			rtsp_new_conn_proc();
			continue;
		}
		list_for_each_safe(pSessPoss, pSessN, &(gRtspSvr.sessList.list))
		{
			pSess = list_entry(pSessPoss, RTSP_SESSION_S, list);
			if(NULL != pSess && nRet == (pSess->nRtspSocket | 0x10000))
			{
				nRet = -1;
				/*����rtsp�Ự��Ϣ*/
				memset(pSess->szBuffRecv, 0, RTSP_MAX_PROTOCOL_BUFFER);
				if((nRecvLen = net_tcp_noblock_recv(pSess->nRtspSocket,
				                                    pSess->szBuffRecv, RTSP_MAX_PROTOCOL_BUFFER,
				                                    0, 5000)) <= 0)
					goto __rtsp_session_error_handle;
				//RTSP_PRINT("Recive C(%s) --> S >>>>>>\n %s\n <<<<<<" ,pSess->szRemoteIP, pSess->szBuffRecv);
				/*����rtsp�Ự��Ϣ*/
				pSess->nMsgSize = nRecvLen;
				nRet = rtsp_session_process(pSess);
__rtsp_session_error_handle:
				if(nRet != 0)
				{
					RTSP_PRINT("close rtsp sid %s  chn %d \n", pSess->szId, pSess->nChId);
					rtsp_session_close(pSess);
					rtsp_list_client();
				}
				break;
			} /* end of if (NULL != pSess) */
		} /* end of list_for_each_safe */
	}
	list_for_each_safe(pSessPoss, pSessN, &(gRtspSvr.sessList.list))
	{
		if(NULL != (pSess = list_entry(pSessPoss, RTSP_SESSION_S, list)))
		{
			rtsp_session_close(pSess);
		}
	}
	net_close_socket(&gRtspSvr.nSvrSocket);
	RTSP_PRINT("rtsp_svr_proc exits\n");
	gRtspSvr.thd = 0;
	return NULL;
}

//============================================================================
//����:nvr_rtsp_start
//
//����:����rtsp ����
//
//nMaxCh:�豸֧�ֵ���Ƶ���ͨ����
//
//nStreamNum:�豸һ��ͨ��֧�ֵ��������� (1.������ 2.˫���� 3.������ �Դ�����)
//
//nRtspPort:rtsp ����˿�Ĭ��Ϊ554
//
//bUseAuth: �Ƿ�����У�� 0 ������ 1����
//
//bRtspMode: rtsp����ģʽ 0 �����ϴ���Ƶ 1 �����ϴ���Ƶ
//
//=============================================================================
int	nvr_rtsp_start(int nMaxCh, int nStreamNum, int nRtspPort, int bUseAuth, int bRtspMode)
{
	int nRet = 0;
	memset(&gRtspSvr, 0, sizeof(NVR_RTSP_SVR));
	gRtspSvr.eState  = VOD_SVR_STATE_INIT;
	gRtspSvr.nSvrPort = nRtspPort;
	gRtspSvr.nUseAuth = bUseAuth;
	/*�ж���������ͨ���ţ� ��������趨�����ֵ�� ��λΪ���ֵ*/
	if(nMaxCh <= 0 || nMaxCh > RTSP_MAX_CHN)
	{
		nMaxCh = RTSP_MAX_CHN;
	}
	gRtspSvr.nMaxCh = nMaxCh;
	pthread_mutex_init(&gRtspMutex, NULL);
	INIT_LIST_HEAD(&(gRtspSvr.sessList.list));
	if((nRet = pthread_create(&(gRtspSvr.thd), NULL, rtsp_svr_proc, NULL)) != 0)
	{
		return -1;
	}
	gRtspSvr.nInitOk = 1;
	return 0;
}

int nvr_rtsp_stop()
{
	pthread_t tnvrd = gRtspSvr.thd;
	int nTimes = 0;
	if(gRtspSvr.nInitOk)
	{
		gRtspSvr.nSvrExits = 1;
		while(gRtspSvr.thd != 0 && nTimes++ < 500)
		{
			usleep(10000);
			continue ;
		}
		pthread_join(tnvrd, NULL);
	}
	pthread_mutex_destroy(&gRtspMutex);
	return 0;
}

int rtsp_get_video_media_info(int nCh, int nStream, int *pPt, char *profileLevelId, char *sps_pps, long lPriData)
{
	int     nFrameLen = 0, nTryTime = 0;
	unsigned long u32PlayLoad = 0;
	unsigned long u32Pts = 0, u32FrameType = 0;
	char   *pFrameBuf = NULL;
	
	while(nTryTime++ < 200)
	{
		if((nFrameLen = gGetVideoCb(nCh, nStream,
		                            &pFrameBuf, &u32Pts,
		                            &u32PlayLoad, &u32FrameType, -1,
		                            lPriData)) > 0)
			break;
		usleep(10000);
	}
	if(nFrameLen > 0)
	{
		*pPt = u32PlayLoad;
		if(RTP_PT_H264 == u32PlayLoad)  //VENC_H264
		{
			rtsp_h264_get_media_info(pFrameBuf, nFrameLen, profileLevelId, sps_pps);
		}
	}
	return 0;
}

#define AUDIO_BUF_SIZE	8192
int rtsp_get_audio_media_info(int nCh, int *pPt, int *pBits, int *pSample, char *pInfo, long lPriData)
{
	return -1;
}

