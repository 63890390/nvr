#ifndef __AUDIO_PARAM_H__
#define __AUDIO_PARAM_H__

#include <stdio.h>
#include <alsa/asoundlib.h>

typedef unsigned long alsa_handle;//�ϲ�Ӧ�ù�����豸���

/** PCM sample format */
typedef enum _alsa_pcm_format {
	/** Unknown */
	ALSA_PCM_FORMAT_UNKNOWN = -1,
	/** Signed 8 bit */
	ALSA_PCM_FORMAT_S8 = 0,
	/** Unsigned 8 bit */
	ALSA_PCM_FORMAT_U8,
	/** Signed 16 bit Little Endian */
	ALSA_PCM_FORMAT_S16_LE,
	/** Signed 16 bit Big Endian */
	ALSA_PCM_FORMAT_S16_BE,
	/** Unsigned 16 bit Little Endian */
	ALSA_PCM_FORMAT_U16_LE,
	/** Unsigned 16 bit Big Endian */
	ALSA_PCM_FORMAT_U16_BE,
	/** Signed 24 bit Little Endian using low three bytes in 32-bit word */
	ALSA_PCM_FORMAT_S24_LE,
	/** Signed 24 bit Big Endian using low three bytes in 32-bit word */
	ALSA_PCM_FORMAT_S24_BE,
	/** Unsigned 24 bit Little Endian using low three bytes in 32-bit word */
	ALSA_PCM_FORMAT_U24_LE,
	/** Unsigned 24 bit Big Endian using low three bytes in 32-bit word */
	ALSA_PCM_FORMAT_U24_BE,
	/** Signed 32 bit Little Endian */
	ALSA_PCM_FORMAT_S32_LE,
	/** Signed 32 bit Big Endian */
	ALSA_PCM_FORMAT_S32_BE,
	/** Unsigned 32 bit Little Endian */
	ALSA_PCM_FORMAT_U32_LE,
	/** Unsigned 32 bit Big Endian */
	ALSA_PCM_FORMAT_U32_BE
}alsa_pcm_format;

/*������Ƶ�����Ľṹ��*/
typedef struct set_audio_param
{
	unsigned int channels; //����ͨ����
	unsigned int rate;   //���ò���Ƶ��
	alsa_pcm_format audioFormat; //���ò��ø�ʽ
	unsigned long  periodFrames; //һ�����ڵ�֡��
	unsigned char bits;
}set_audioparams;

/*��ȡ��Ƶ�����Ľṹ��*/
typedef struct get_audio_param
{
	unsigned long period_size; //һ����Ƶ�������ڵĳ��ȣ�����Ϊ��λ
	unsigned int period_time;  //һ����Ƶ�������ڵ�ʱ�䣬��usΪ��λ
	unsigned int periods_buffer;//һ��buffer�������ٸ���Ƶ����
	
}get_audioparams;

/** PCM stream (direction) */
typedef enum nvr_pcm_stream {
	/** ������Ƶ */
	NVR_PCM_STREAM_PLAYBACK = 0,
	/** ¼����Ƶ */
	NVR_PCM_STREAM_CAPTURE,
	NVR_PCM_STREAM_LAST = NVR_PCM_STREAM_CAPTURE
} nvr_pcm_stream_t;
typedef struct {
	alsa_handle phandle;
	unsigned long wlen; 
	int pipeFd;
}play_params,*pplay_params;

typedef struct capture_play
{
	snd_pcm_t *pcmhandle;
	snd_pcm_hw_params_t *hwparams;
	alsa_handle uhandle;
	size_t  chunk_bytes;	  //һ�����ڵ��ֽ���
	char  *audiobuf;		  //����һ����Ƶ������ʼ��ַ
	size_t  bits_per_frame;   //ÿһ֡��Ƶ���ݵ�bit��
	pthread_t pid;			  //�����̵߳�pid
	pplay_params param;

}pcapture_play;
extern pcapture_play parray_handle[4];
int audio_playback_init(set_audioparams *param);
int audio_playback_put_stram(char*buf,unsigned int len);
int audio_playback_exit(void);
int audio_record_init(set_audioparams *param);
int audio_record_exit(void);
int audio_record_get_stram(char*buf,unsigned int len);
int audio_get_playback_state(void);
#endif

