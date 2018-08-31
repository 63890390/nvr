#ifndef _NVR_RTSP_G7XX_H_
#define _NVR_RTSP_G7XX_H_

#include "nvr_rtsp_struct.h"
/*
* Copyright (c) 2010
* All rights reserved.
*
* filename:nvr_rtsp_g7XX.h
*
* func:���ļ�ʵ���˶�rtsp g726 g711a g711u��Ƶ�ķ�װ
*
* author : nvr
* createdate: 2011-01-27
*
* modify list:
*
*/
#ifdef __cplusplus
extern "C" {
#endif

	int rtsp_g7xx_audio_send(RTSP_SESSION_S *pSess, const char *szBuff, int nFrameLen,
	                         unsigned long u32TimeStamp, unsigned long u32SampleRate);
	int rtsp_g7xx_lsit_audio_send(struct list_head *pSessHead, const char *szBuff, int nFrameLen,
	                              unsigned long u32TimeStamp, unsigned long u32SampleRate);

#ifdef __cplusplus
}
#endif


#endif
