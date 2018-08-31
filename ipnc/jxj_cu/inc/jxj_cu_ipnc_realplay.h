
#ifndef __JXJ_CU_REALPLAY_H__
#define __JXJ_CU_REALPLAY_H__

typedef struct _JXJ_CU_STREAM_S_
{
	int chn;			  //ipcͨ����
	int streamNo;		  //��������(0������, 1������)
	int poolChn;		  //avpoolͨ����
	int poolStreamNo; 	  //������
	long lRealPlayHandle; //rtsp���
	long videoId;		  //avpool���ID
	int refCount;		  //���Ӽ���
	unsigned long long lastVideoPts;	// �����Ƶʱ���
	unsigned long long lastAudioPts;	// �����Ƶʱ���
	
	void *ipncHandle;	  //ipnc ���
	pthread_t pthId;	  //ȡ�������߳�
}JXJ_CU_STREAM_S;


int jxj_cu_ipnc_start_get_stream(long handle, int chn, int streamNo, long *streamHandle);
int jxj_cu_ipnc_stop_get_stream(long handle, long streamHandle);
int jxj_cu_ipnc_request_iframe(long handle, long streamHandle);

#endif





