
#ifndef __AV_POOL_MNG_H__
#define __AV_POOL_MNG_H__

#include <linux/mutex.h>

#include "av_pool_module.h"

// ���֧��ͨ����, Զ��ipncͨ����һ������ͨ��
#define AV_POOL_MAX_SUPPORT_CHN		5
// ÿ��ͨ�������������������������������Ƶ
#define AV_POOL_MAX_SUPPORT_STREAM	2

#define AV_POOL_MAX_SUPPORT_POOL (AV_POOL_MAX_SUPPORT_CHN * AV_POOL_MAX_SUPPORT_STREAM)

typedef enum _JPOOL_ERR_E_
{
	JPOOL_SUCCESS   		= 0,
	JPOOL_FAILED			= -1,
}JPOOL_ERR_E;

//��Ϊ���֡ռ�ռ��СΪ64�ֽڶ���
//�����ڻ������֡��ʶͷֻ֧�����11 ��NAL����֡
#define JPOOL_HDR_LEN 64
typedef struct _JPOOL_FRAME_HDR_
{
	unsigned long	u32FlagStart;		//֡ͷħ��
	unsigned long	u32FrameNo;//��Ƶ֡���
	unsigned long	u32DataLen; //��Ƶ֡���ݴ�С
	unsigned char	u8FrameType;
	unsigned char	u8Res[2];
	unsigned char	u8NalNum;
	unsigned long long	u64Pts;
	unsigned long	u32ArrNalLen[9];
	unsigned long	u32FlagEnd;
}JPOOL_FRAME_HDR, *LPJPOOL_FRAME_HDR; 


typedef struct _JPOOL_MAN_
{
	unsigned char		u8Init;
	unsigned char		u8VideoPool;//--1 ��ʾΪ��Ƶ����--0 ��ʾΪ��Ƶ����
	unsigned char		u8PoolNo;
	unsigned char		u8Res;
	unsigned long		u32FrameNo;		//���������֡��
	unsigned long		u32BuffSize;			//�����С
	unsigned long		u32MaxSize;			//����������֡��С
	unsigned long		u32OldestFrameNo;
	unsigned long		u32OldestIFrameNo;
	
	unsigned long		u32OldestFramePos;	//����������֡��λ��	
	unsigned long		u32OldestIFramePos;
	unsigned long		u32NewestIPos;		//����������I ֡��λ��
	unsigned long		u32NewestIFrameNo;	// ����������I֡��֡��
	unsigned long		u32NewestFramePos;//����������֡��λ��

	unsigned long long		u64OldestFramePts;	//����������֡��pts	
	unsigned long long		u64OldestIFramePts;	//����������֡I ֡��pts	
	unsigned long long		u64NewestIPts;		//����������I ֡��pts	
	
	unsigned long long		u64NewestFramePts;//����������֡��pts
	
	unsigned long		u32WritePos;

	unsigned long		u32NewestFrameNo;		// ����֡��
	unsigned long		u32PhysAddr;
	unsigned long		u32MaxHdrLen;
	char 		*pDataBuff;

	// pool infomation
	char ipAddr[32];		// ipc ip address of the stream
	char protocol[32];		// ipc protocol name
	int port;				// port of the stream
	int type;				// tcp or udp of the stream

	// handle
	long ipncHandle;
	long streamHandle;
	
	// pool status
	AvPoolWorkStatus status;
	atomic_t readCnt;
	atomic_t writeCnt;

	unsigned int readFrameCnt;
	unsigned int writeFrameCnt;
	
	//int dmaChid;
	//struct completion dmaComplete;
	struct completion frameComplete;
	wait_queue_head_t wait;
	
//	struct mutex	lock;
	struct rw_semaphore sem;
}JPOOL_MAN, *LPJPOOL_MAN;

typedef struct _JPOOL_ATTR_
{
	int 	nMsPoolSize;	//��������������С
	int	nSsPoolSize;//��������������С
	int	nAsPoolSize;//��Ƶ��������С
}JPOOL_ATTR, *LPJPOOL_ATTR;


int av_pool_init(int nTotalCh, int nTotalStreamNo);

int av_pool_uninit(void);

int av_pool_write_frame(int nCh, int nStreamNo, char *pHdrData, int nHdrLen, 
					int nPics, char **ppPicsData, int *pPicsLen,  int nLen, int nFrameType,
					unsigned long long u64Pts, unsigned long u32CurFrameNo);

int av_pool_read_frame(int nCh, int nStreamNo, char *pBuf, int nBufLen, unsigned long *pU32IFrame,
			unsigned long u32NeedFrameNo, unsigned long *pU32FrameNo, unsigned long *pLastPos, unsigned long long *pU64Pts, 
			unsigned long	u32MaxDelay, unsigned long *pU32NewestFrameNo, int timeout);

int av_pool_get_max_frame_size(int nCh, int nStreamNo);

int av_pool_reset_pool(int nCh, int nStreamNo);

int av_pool_set_pool_info(int nCh, 
			const char *ipAddr, const char *protocol, 
			int type, int port);

int av_pool_get_pool_info(int nCh, 
			char *ipAddr, char *protocol, 
			int *type, int *port);
			
int av_pool_get_frame_info(int nCh, int nStreamNo, 
			unsigned int *writeFrameCnt, unsigned int *readFrameCnt);

int av_pool_set_pool_status(int nCh, int nStreamNo, AvPoolWorkStatus status);

int av_pool_get_pool_status(int nCh, int nStreamNo, AvPoolWorkStatus *status);


int av_pool_inc_pool_reading_cnt(int nCh, int nStreamNo);

int av_pool_dec_pool_reading_cnt(int nCh, int nStreamNo);

int av_pool_get_pool_reading_cnt(int nCh, int nStreamNo);

int av_pool_inc_pool_writing_cnt(int nCh, int nStreamNo);

int av_pool_dec_pool_writing_cnt(int nCh, int nStreamNo);

int av_pool_get_pool_writing_cnt(int nCh, int nStreamNo);

int av_pool_set_pool_ipnc_handle(int nCh, long ipncHandle);
	
int av_pool_get_pool_ipnc_handle(int nCh, long *ipncHandle);

int av_pool_set_pool_stream_handle(int nCh, int nStreamNo, long streamHandle);

int av_pool_get_pool_stream_handle(int nCh, int nStreamNo, long *streamHandle);

#endif

