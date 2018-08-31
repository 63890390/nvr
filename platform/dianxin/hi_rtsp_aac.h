#ifndef _HI_RTSP_AAC_H_
#define _HI_RTSP_AAC_H_

#include "hi_rtsp_struct.h"

/*
* Copyright (c) 2010
* All rights reserved.
* 
* filename:hi_rtsp_aac.h
* 
* func:���ļ�ʵ���˶�rtsp aac��Ƶ�ķ�װ
* 
* author : hi
* createdate: 2011-01-27
*
* modify list: 
* 
*/
#ifdef __cplusplus
extern "C" {
#endif 

int rtsp_aac_audio_send(RTSP_SESSION_S* pSess, const char *szBuff, int nFrameLen, 
						 unsigned long u32TimeStamp, unsigned long u32SampleRate);



#ifdef __cplusplus
}
#endif 

#endif

