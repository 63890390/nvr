/***************************************
*���Բ�����Ƶ�ļ�
*����:./play_test inputfile
***************************************/

#include "audio_params.h"
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/*����ʱ��*/
#if 0
int tim_subtract(struct timeval *result, struct timeval *x, struct timeval *y)
{
	if ( x->tv_sec > y->tv_sec )
		return   -1;
	if ((x->tv_sec==y->tv_sec) && (x->tv_usec>y->tv_usec))
		return -1;
		result->tv_sec = ( y->tv_sec-x->tv_sec );
		result->tv_usec = ( y->tv_usec-x->tv_usec );
	if (result->tv_usec<0)
	{
		result->tv_sec--;
		result->tv_usec+=1000000;
	}
	return 0;
}
#endif

int main(int argc, char *argv[])
{
	char *name;
	nvr_pcm_stream_t stream = NVR_PCM_STREAM_PLAYBACK;
	set_audioparams *sparam;	
	get_audioparams gparam = {0};
	alsa_handle phandle = 0;
	//struct  timeval  start,stop,diff;
	FILE *fd;
	unsigned int buf_size = 160;  //ÿ������Ƶ������д���ݴ�С
	u_char *buffer;
	int pipeFd;
	int wlen;
	long i;

	if(argc != 2)
	{
		printf("USAGE:%s outputfile\n",argv[0]);
		exit(1);
	}
	if((fd = fopen(argv[1],"r")) == NULL)
	{
		printf("open file error\n");
		return -1;
	}
	/*Ϊ��������ռ䲢��ʼ��*/
	sparam = (set_audioparams *)malloc(sizeof(set_audioparams));
	if(NULL == sparam)
	{
		printf("<<<<<malloc mem failed>>>>\n");
		return (-1);
	}
	memset(sparam, 0, sizeof(set_audioparams));
	sparam->channels = 2;
	sparam->rate = 44100;
	sparam->audioFormat = ALSA_PCM_FORMAT_S16_LE;
	sparam->periodFrames = 256;		//�˲����п�������ʧ�ܣ�����ϵͳĬ�ϵ����ڴ�С

	buffer = (u_char *)malloc(buf_size);
	if(NULL == buffer)
	{
		printf("malloc mem failed %d bytes\n",buf_size);
		return (-1);
	}	

	name = strdup("default");

	/*������*/
	open_audio_volume(name);
	
	/*����Ƶ�豸�����ñ�׼ģʽ*/
	if(open_audio_dev(&phandle, name, stream) < 0)
	{
		fprintf(stderr,"%s :%d :error\n",__func__,__LINE__);
		return(-1);
	}
	
	/*������Ƶ����*/
	if(set_audio_params(phandle, sparam) < 0)
	{
		fprintf(stderr,"%s :%d :error\n",__func__,__LINE__);
		return(-1);
	}
		
	/*��ȡ��Ƶ����*/
	if(get_audio_params(phandle, &gparam) < 0)
	{
		fprintf(stderr,"%s :%d :error\n",__func__,__LINE__);
		return(-1);
	}

	/*����Ƶ����׼��������Ƶ*/
	if(open_audio_stream(phandle, buf_size, &pipeFd) < 0)
	{
		fprintf(stderr,"%s :%d :error\n",__func__,__LINE__);
		return (-1);
	}
	
	for(i=0; i< 100000; i++)
	{
		bzero(buffer, buf_size);
		//usleep(100);
		wlen = fread(buffer, 1, buf_size, fd);
		if (wlen != buf_size)
	      fprintf(stderr, "short write: wrote %d bytes\n", wlen);
		//gettimeofday(&start,0);
		
		start_play_audio(pipeFd, buffer, wlen);//��ʼ���ţ�д����
		
		//gettimeofday(&stop,0);
		//tim_subtract(&diff,&start,&stop);
		//printf("----------->>:%ld\n",diff.tv_usec);
	}
	stop_play_audio(phandle);	//ֹͣ����
	
	/*�ر���Ƶ�豸*/
	if(close_audio_dev(phandle) < 0)
	{
		fprintf(stderr,"%s :%d :error\n",__func__,__LINE__);
		return(-1);
	}

	fclose(fd);
	close(pipeFd);
	free(buffer);
	free(sparam);
	sparam = NULL;
		
	return 0;
}

