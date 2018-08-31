/******************************************************************************

                  ��Ȩ���� (C), 2011-2015, ���Žݵ���

 ******************************************************************************
  �� �� ��   : hi_rtsp_g7xx.c
  �� �� ��   : v2.0
  ��    ��   : ������
  ��������   : 2011��9��8��
  ����޸�   :
  ��������   : rtsp g711a g711u��Ƶ���ݷ���ʵ��
  �����б�   :
              rtsp_g7xx_audio_send
              rtsp_g7xx_rtp_send
  �޸���ʷ   :
  1.��    ��   : 2011��9��8��
    ��    ��   : ������
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include <string.h>
#include "hi_rtsp_debug.h"
#include "hi_rtsp_g7xx.h"
#include "hi_rtsp_rtp.h"
#include "hi_rtsp_transfer.h"

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


int rtsp_g7xx_rtp_send(RTSP_SESSION_S* pSess, const char *szBuff, int nFrameLen, 
						 unsigned long u32TimeStamp)
{
	RTP_HDR_S 			rtpHdr;
	RTP_OVER_TCP_HEADER rtpOverTcpHdr;
	char *				pSendBuf = (char *)pSess->stRtpSender.szBuff;
	
	int    nRtpOverTcpLen = sizeof(RTP_OVER_TCP_HEADER);
	int    nRtpHdrLen     = sizeof(RTP_HDR_S);
	int    nPlayLoadLen   = 0, nDataLen = 0;
	
	memset(&rtpHdr,        0, sizeof(RTP_HDR_S));
	memset(&rtpOverTcpHdr, 0, sizeof(RTP_OVER_TCP_HEADER));

	rtpOverTcpHdr.u8Dollar     = '$';
	rtpOverTcpHdr.u8ChnId      = pSess->nAudioChId;
	
	rtpHdr.version   = RTP_VERSION;
	rtpHdr.cc        = 0;
	rtpHdr.x         = 0;
	rtpHdr.p         = 0;
	rtpHdr.ts		 = htonl(u32TimeStamp);
	rtpHdr.pt        = pSess->stRtpSender.nPayLoad[1];
	rtpHdr.ssrc      = htonl(pSess->stRtpSender.nAudioSsrc);

	if (pSess->eTransType != RTP_TRANSPORT_TCP)
	{
		nRtpOverTcpLen = 0;
	}
	
	nPlayLoadLen = RTP_MAX_PACKET_BUFF - nRtpOverTcpLen - nRtpHdrLen;
	if (nFrameLen + nRtpOverTcpLen + nRtpHdrLen <= RTP_MAX_PACKET_BUFF)
	{
		rtpHdr.seqno = htons(++pSess->stRtpSender.u16LastSndSeq[1]);
		rtpHdr.marker= 1;
		
		if (nRtpOverTcpLen != 0)
		{
			rtpOverTcpHdr.u16PacketSize = htons(nFrameLen+nRtpHdrLen);
			memcpy(pSendBuf, &rtpOverTcpHdr, nRtpOverTcpLen);
		}

		memcpy(&pSendBuf[nRtpOverTcpLen], &rtpHdr, nRtpHdrLen);
		pSess->stRtpSender.nBuffLen = nRtpHdrLen+nRtpOverTcpLen;
		memcpy(&pSendBuf[pSess->stRtpSender.nBuffLen], szBuff, nFrameLen);	
		pSess->stRtpSender.nBuffLen += nFrameLen;
		
		if (send_rtp_data(pSess, pSendBuf, pSess->stRtpSender.nBuffLen, 1) < 0)
			return -1;		
	}
	else
	{
		while(nFrameLen > 0)
		{
			pSess->stRtpSender.nBuffLen = 0;	
			rtpHdr.seqno = htons(++pSess->stRtpSender.u16LastSndSeq[1]);
		
			if (nFrameLen + nRtpOverTcpLen + nRtpHdrLen <= RTP_MAX_PACKET_BUFF)
			{
				rtpHdr.marker       = 1; ////bLast
				nDataLen            = nFrameLen;
			}	
			else
			{
				rtpHdr.marker       = 0;
				nDataLen            = nPlayLoadLen;
			}

			if (nRtpOverTcpLen != 0)
			{
				rtpOverTcpHdr.u16PacketSize = htons(nDataLen+nRtpHdrLen);
				memcpy(pSendBuf, &rtpOverTcpHdr, nRtpOverTcpLen);
			}	
			
			memcpy(&pSendBuf[nRtpOverTcpLen], &rtpHdr, nRtpHdrLen);
			pSess->stRtpSender.nBuffLen = nRtpHdrLen+nRtpOverTcpLen;
			
			memcpy(&pSendBuf[pSess->stRtpSender.nBuffLen], szBuff, nDataLen);
			pSess->stRtpSender.nBuffLen += nDataLen;
			nFrameLen  -= nDataLen;
			szBuff     += nDataLen;

			if (send_rtp_data(pSess, pSendBuf, pSess->stRtpSender.nBuffLen, 1) < 0)
			{
				return -1;
			}	
		}/*end while*/
			
	}/*end else*/	
	return 0;
}

int rtsp_g7xx_audio_send(RTSP_SESSION_S* pSess, const char *szBuff, int nFrameLen, 
						 unsigned long u32TimeStamp, unsigned long u32SampleRate)
{
	unsigned long nPts = 0;
	int nRet = 0;

	if (pSess->stRtpSender.u32LastSndTs[1] == 0 || 
		u32TimeStamp < pSess->stRtpSender.u32LastSndTs[1])
		nPts = 1600;
	else
 		nPts = pSess->stRtpSender.u32LastSndPts[1] + 
 			  (u32SampleRate/1000)*(u32TimeStamp - pSess->stRtpSender.u32LastSndTs[1]);	

	nRet = rtsp_g7xx_rtp_send(pSess, szBuff, nFrameLen, nPts);
	pSess->stRtpSender.u32LastSndTs[1]  = u32TimeStamp;
	pSess->stRtpSender.u32LastSndPts[1] = nPts;	
	return nRet;
}

int rtsp_g7xx_lsit_audio_send(struct list_head* pSessHead, const char *szBuff, int nFrameLen, 
						 unsigned long u32TimeStamp, unsigned long u32SampleRate)
{
	unsigned long nPts = 0;
	int nRet = 0;
	RTSP_SESSION_S* pSess;

	list_for_each_entry(pSess, pSessHead, transList)
	{
		if (pSess->stRtpSender.u32LastSndTs[1] == 0 || 
			u32TimeStamp < pSess->stRtpSender.u32LastSndTs[1])
			nPts = 1600;
		else
	 		nPts = pSess->stRtpSender.u32LastSndPts[1] + 
	 			  (u32SampleRate/1000)*(u32TimeStamp - pSess->stRtpSender.u32LastSndTs[1]);	

		nRet = rtsp_g7xx_rtp_send(pSess, szBuff, nFrameLen, nPts);
		pSess->stRtpSender.u32LastSndTs[1]  = u32TimeStamp;
		pSess->stRtpSender.u32LastSndPts[1] = nPts;	
	}
	return nRet;
}


