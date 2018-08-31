/***************************************
*����¼����Ƶ�ļ�
*����:./capture_test outputfile
***************************************/

#include "audio_params.h"


int main(int argc, char *argv[])
{
	char *name;
	nvr_pcm_stream_t mode = NVR_PCM_STREAM_CAPTURE;
	set_audioparams *sparam;
	get_audioparams gparam={0};
	u_char * buffer = NULL;
	unsigned long buf_size = 0;
	unsigned long rlen;
	alsa_handle phandle = 0;

	sparam = (set_audioparams *)malloc(sizeof(set_audioparams));
	if(sparam == NULL)
	{
		printf("<<<<<malloc mem failed>>>>\n");
		return (-1);
	}
	memset(sparam, 0, sizeof(set_audioparams));
	sparam->channels = 2;
	sparam->rate = 44100;
	sparam->audioFormat = ALSA_PCM_FORMAT_S16_LE;


	FILE *fd;
	if(argc != 2)
	{
		printf("USAGE:%s outputfile\n",argv[0]);
		exit(1);
	}
	if((fd = fopen(argv[1],"w")) == NULL)
	{
		printf("open file error\n");
		return -1;
	}

	
	name = strdup("default");
	/*������*/
	open_audio_volume(name);
	
	/*����Ƶ�豸*/
	if(open_audio_dev(&phandle, name, mode) < 0)
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
#if 0	
	buf_size = gparam.period_size*(16*sparam.channels)/8;
	buffer = (char *)malloc(buf_size);
	if(NULL == buffer)
	{
		printf("malloc mem failed %lu bytes\n",buf_size);
		return (-1);
	}
		
	int time = 10;//¼�Ƶ�ʱ��
	unsigned long count = time*1000*1000 / gparam.period_time;
	int i;
	printf("count = %lu,buf_size = %ld\n",count,buf_size);
	for(i=0; i< count; i++)
	{
		bzero(buffer, buf_size);
#endif
	while(1)
	{
		/*��ʼ¼��*/
		if((rlen = capture_audio_stream(phandle, buffer, buf_size)) < 0)
		{
			fprintf(stderr,"%s :%d :error\n",__func__,__LINE__);
			return(-1);
		}

		fwrite(buffer, 1, rlen, fd);
	}
	
	/*�ر���Ƶ�豸*/
	if(close_audio_dev(phandle) < 0)
	{
		fprintf(stderr,"%s :%d :error\n",__func__,__LINE__);
		return(-1);
	}

	fclose(fd);
	free(sparam);
	sparam = NULL;
		
	return 0;
}

