#ifndef _HI_RTSP_GLOBAL_H_
#define _HI_RTSP_GLOBAL_H_

/*
* Copyright (c) 2010
* All rights reserved.
* 
* filename:hi_rtsp_global.h
* 
* func:���ļ�ʵ���˶�rtsp �ĳ�ʼ����rtsp �ص���������
* 
* author : hi
* createdate: 2011-01-27
*
* modify list: 
* 
*/

#include "hi_rtsp_struct.h"

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
}RTP_PT_E;

typedef struct _RTSP_MAP_ADDRESS_
{
	char 	szTurnServerIp[64];
	int 		nTurnServerPort;
	int 		sock;
	char 	innerIp[16];		// �豸�ڲ�IP
	int 		innerPort;		// �豸�� ���˿�
	char 	natIp[16];		// ����ӳ��IP
	int 		natPort;			// ����IP
}RTSP_MAP_ADDRESS;

typedef enum _RTSP_MSG_NOTIFY_
{
	RTSP_MSG_PREVIEW_LINK		= 0x1,
	RTSP_MSG_PREVIEW_UNLINK  	= 0x2,
	/* for turn */
	RTSP_MSG_GET_MAP_ADDRESS	= 0X10,
}RTSP_MSG_NOTIFY;

//�û����ص�
typedef int (*CheckUserCallback)(char *szUser, char *szPsw, int nGetPsw);

	typedef int (*RequestIDRCallback)(int nCh, int nSub, long lPriData);

	typedef int (*GetAudioCallback)(int nCh, char **lpFrameBuf,
	                                unsigned long *pU32Pts,
	                                unsigned long *pU32Playload,
	                                unsigned long *pU32Bits,
	                                unsigned long *pU32Sample,
	                                long lPriData);
	                                

	typedef int (*GetVideoCallback)(int nCh, int nStream,
		                       char **lpFrameBuf,
		                       unsigned long *pU32Pts,
		                       unsigned long *pU32PlayLoad,
		                       unsigned long *pU32FrameType,
		                       int nTimeOut,
		                       long lPriData);

	typedef int (*GetFrameCallback)(int nCh, int nStream,
		                       char **lpFrameBuf,
		                       unsigned long *pU32Pts,
		                       unsigned long *pU32PlayLoad,
		                       unsigned long *pU32FrameType,
		                       int nTimeOut,
		                       long lPriData);

	typedef int (*MsgCallback)(RTSP_MSG_NOTIFY eMsgNotify, int nCh, int nStream, long *lPriData);

// ??��?????
typedef int (*GetVodStart)(const char *pFileName, void **handle);
typedef int (*GetVodStop)(void *handle);
typedef int (*GetVodFrame)(void *handle, 
							char ** lpFrameBuf, unsigned long u32FrameBufSize,
							unsigned long *pFrameType,
							unsigned long *pU32Pts, unsigned long *pU32PlayLoad,
							unsigned long *pU32Sample, unsigned long *pU32Bits, unsigned long * pU32Offset);

typedef int (*SetVodSeek)(void *handle, int sec);
typedef int (*GetVodProperty)(void *handle);

//add by hjl////////////////////////////////////////////////////
typedef int (*GetVideoVarify)(char *pDevId, char *pChannelNo, 
			char *pStreamType, char *pHashToken);
typedef int (*GetVodVarify)(char *pDevId, char *pChannelNo, 
			char *pFileName, char *pHashToken);
typedef int (*GetVideoFlag)();
typedef int (*GetVodFlag)();



//============================================================================
//����:hi_rtsp_set_cb 
//
//����:����rtsp����ص�����
//
//=============================================================================

int     hi_rtsp_set_cb(CheckUserCallback checkUserCb,
					   RequestIDRCallback reqIdrCb,
					   GetVideoCallback  getVideoCb,
					   GetAudioCallback  getAudioCb,
					   GetFrameCallback getFrameCb,
					   MsgCallback	  msgCb);

// ����??��������??��?����?��?��
int	hi_rtsp_set_vod_cb(GetVodStart getVodStartCb,
							GetVodStop getVodStopCb,
							GetVodFrame getVodFrameCb,
							SetVodSeek setVodSeek,
							GetVodProperty getVodProperty);


int	hi_rtsp_set_varify_cb(GetVideoVarify getVideoVarifyCb,
							GetVodVarify getVodVarifyCb,
							GetVideoFlag getVideoFlagCb,
							GetVodFlag getVodFlagCb);

//============================================================================
//����:hi_rtsp_start 
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
int		hi_rtsp_start(int nMaxCh, int nStreamNum, int nRtspPort, int bUseAuth, int bRtspMode);

//============================================================================
//����:hi_rtsp_stop 
//
//����:ֹͣrtsp ����
//
//=============================================================================
int		hi_rtsp_stop();

int rtsp_get_client_cnt();

extern HI_RTSP_SVR	         gRtspSvr;
extern pthread_mutex_t		 gRtspMutex;

extern CheckUserCallback    gCheckUserCb;
extern RequestIDRCallback	gRequestIdrCb;
extern GetVideoCallback     gGetVideoCb ;
extern GetAudioCallback     gGetAudioCb ;
extern GetFrameCallback    gGetFrameCb ;
extern MsgCallback     		gMsgCb ;


// ��������????
extern GetVodStart gGetVodStartCb;
extern GetVodStop gGetVodStopCb;
extern GetVodFrame gGetVodFrameCb;

extern SetVodSeek gSetVodSeek;
extern GetVodProperty gGetVodProperty;


//add by hjl/////////////////////////
extern GetVideoVarify gGetVideoVarify;
extern GetVodVarify gGetVodVarify;
extern GetVideoFlag gGetVideoFlag;
extern GetVodFlag gGetVodFlag;


#ifdef __cplusplus
}
#endif 

#endif
