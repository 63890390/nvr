#ifndef _NVR_RTSP_GLOBAL_H_
#define _NVR_RTSP_GLOBAL_H_

/*
* Copyright (c) 2010
* All rights reserved.
*
* filename:nvr_rtsp_global.h
*
* func:���ļ�ʵ���˶�rtsp �ĳ�ʼ����rtsp �ص���������
*
* author : nvr
* createdate: 2011-01-27
*
* modify list:
*
*/

#include "nvr_rtsp_struct.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*RTP Payload type define*/
	typedef enum _RTP_PT_E_
	{
		RTP_PT_ULAW             = 0,        /* mu-law  PCMU*/
		RTP_PT_GSM              = 3,        /* GSM */
		RTP_PT_G723             = 4,        /* G.723 */
		RTP_PT_ALAW             = 8,        /* a-law  PCMA*/
		RTP_PT_G722             = 9,        /* G.722 */
		RTP_PT_S16BE_STEREO     = 10,       /* linear 16, 44.1khz, 2 channel */
		RTP_PT_S16BE_MONO       = 11,       /* linear 16, 44.1khz, 1 channel */
		RTP_PT_MPEGAUDIO        = 14,       /* mpeg audio */
		RTP_PT_JPEG             = 26,       /* jpeg */
		RTP_PT_H261             = 31,       /* h.261 */
		RTP_PT_MPEGVIDEO        = 32,       /* mpeg video */
		RTP_PT_MPEG2TS          = 33,       /* mpeg2 TS stream */
		RTP_PT_H263             = 34,       /* old H263 encapsulation */


		RTP_PT_H264             = 96,       /* */
		RTP_PT_G726             = 97,       /* */
		RTP_PT_AAC              = 96,
		RTP_PT_ADPCM			= 99,

		         RTP_PT_INVALID          = 127
	}
	                                   RTP_PT_E;

	typedef enum _RTSP_MSG_NOTIFY_
	{
	    RTSP_MSG_PREVIEW_LINK		= 0x1,
	    RTSP_MSG_PREVIEW_UNLINK  	= 0x2,
	} RTSP_MSG_NOTIFY;

	//�û����ص�
	typedef int (*CheckUserCallback)(char *szUser, char *szPsw, int nGetPsw);

	typedef int (*RequestIDRCallback)(int nCh, int nSub, long lPriData);

	typedef int (*GetAudioCallback)(int nCh, char *lpFrameBuf,
	                                unsigned long *pU32Pts,
	                                unsigned long *pU32Playload,
	                                unsigned long *pU32Bits,
	                                unsigned long *pU32Sample,
	                                int nTimeOut,
	                                long lPriData);

	typedef int (*GetVideoCallback)(int nCh, int nStream,
		                       char **lpFrameBuf,
		                       unsigned long *pU32Pts,
		                       unsigned long *pU32PlayLoad,
		                       unsigned long *pU32FrameType,
		                       int nTimeOut,
		                       long lPriData);

	typedef int (*MsgCallback)(RTSP_MSG_NOTIFY eMsgNotify, int nCh, int nStream, long *lPriData);

	typedef void *(*AllocMemCallback)(int size);

	typedef void (*FreeMemCallback)(void *mem);

	//============================================================================
	//����:nvr_rtsp_set_cb
	//
	//����:����rtsp����ص�����
	//
	//=============================================================================

	int     nvr_rtsp_set_cb(CheckUserCallback checkUserCb,
	                        RequestIDRCallback reqIdrCb,
	                        GetVideoCallback  getVideoCb,
	                        GetAudioCallback  getAudioCb,
	                        MsgCallback	  msgCb,
	                        AllocMemCallback allocMemCb,
	                        FreeMemCallback freeMemCb);

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
	int		nvr_rtsp_start(int nMaxCh, int nStreamNum, int nRtspPort, int bUseAuth, int bRtspMode);

	//============================================================================
	//����:nvr_rtsp_stop
	//
	//����:ֹͣrtsp ����
	//
	//=============================================================================
	int		nvr_rtsp_stop();


	extern NVR_RTSP_SVR	         gRtspSvr;
	extern pthread_mutex_t		 gRtspMutex;

	extern CheckUserCallback    gCheckUserCb;
	extern RequestIDRCallback	gRequestIdrCb;
	extern GetVideoCallback     gGetVideoCb ;
	extern GetAudioCallback     gGetAudioCb ;
	extern MsgCallback     		gMsgCb ;
	extern AllocMemCallback     	gAllocMemCb ;
	extern FreeMemCallback     	gFreeMemCb ;

#ifdef __cplusplus
}
#endif

#endif
