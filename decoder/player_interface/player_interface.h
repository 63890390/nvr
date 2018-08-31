#ifndef PLAYER_INTERFACE_
#define PLAYER_INTERFACE_
#include<av_pool.h>
enum{
	FLU_WORK_NOMAL_RATE=0,//��������
	FLU_WORK_F2_RATE,//���
	FLU_WORK_F4_RATE,	
	FLU_WORK_F8_RATE,
	FLU_WORK_F2_IFRAME_RATE,//��IFrame���
	FLU_WORK_F4_IFRAME_RATE,
	FLU_WORK_F8_IFRAME_RATE,
	FLU_WORK_B2_RATE,//����
	FLU_WORK_B4_RATE,
	FLU_WORK_B8_RATE,
	FLU_WORK_S2_RATE,//����
	FLU_WORK_S4_RATE,
	FLU_WORK_S8_RATE,	
};
typedef enum{
	CHANNEL_PALY=0,
	CHANNEL_STANDBY,
	CHANNEL_PAUSE,
}play_status;
typedef struct _query_info
{
	RecordQueryInfo query;
	time_t set_time;
}file_info;

typedef struct _player_status{
	time_t play_time_point;//�Ѿ����ŵ�ʱ��msΪ��λ
	unsigned int query_num;//���е�query buffer  	����:���õ�buffer����0:û��buffer����
	unsigned int replay_end;//����¼���ļ��Ѿ�������1:����0:û����
	play_status channel_status;//ͨ����״̬
}player_status;
////ʵʱԤ��ģʽ�£�����ĳ��ͨ������Ƶ
char player_real_play(unsigned char ch);

//��ĳ��ͨ������Ϊʵʱ��ƵԤ��ģʽ
char player_set_real_play_mode(unsigned char ch);

///////ֹͣ����ĳ��ͨ������Ƶ
char player_stop(unsigned char ch);

////��ȡĳ��ͨ����Ԥ��״̬0:Ԥ��ֹͣ1:����Ԥ��
char player_get_preview_status(unsigned char ch);//ûһ��bit��Ӧһ��ͨ��

//��ȡ����������ͨ����״̬
char player_get_player_status(unsigned char ch,player_status *status);

//������ʾģʽ1:ȫ��0:�ķ���
char player_set_dis_mode(unsigned char mode,unsigned char ch);

//��ȡ��ʾģʽ1:ȫ��0:�ķ���
char player_get_display_mode(void);

///��Ƶ����1:��ͨ������Ƶ0:�ر�ͨ������Ƶ
char player_set_audio_function(unsigned char ch,unsigned char cmd);
//////////////replay����
/*
query:�����ļ��Ľṹ��
time:����������ļ���ĳ��ʱ��㿪ʼ���ţ�������ļ��Ŀ�ʼʱ��
flag:�����ļ����µı�ǣ�1:���̸��²����ļ���0:�ŶӸ���
*/
char player_replay_play(unsigned char ch,file_info *replay_info,unsigned char flag);

//////////�ط�ģʽ�£���ͣĳ��ͨ������Ƶ����
/*
	1:��ͣ0:�ָ�
*/
char player_replay_pause_clt(unsigned char ch,unsigned char ctl);
//���ÿ�������ˡ����ŵ��ٶ�
char player_set_speed(unsigned char ch,unsigned char speed);

//��ĳ��ͨ������Ϊ�ط�ģʽ
char player_set_replay_mode(unsigned char ch);

//��֡��ʾʱ����һ֡
char player_up_frame(unsigned char ch);

//��֡��ʾʱ����һ֡
char player_down_frame(unsigned char ch);
//���ű�������,file�Ǳ����������ļ�
char player_alarm_audio(char *file);
//ֹͣ������Ƶ�Ĳ���
char player_stop_alarm_audio(void);
//ͼ��ץ�Ĺ��ܣ�ch��ͨ����0-3,num:ץ�Ĳ���
char player_set_cap_num(unsigned char ch,unsigned char num);
//����framebuf��͸����
char player_set_fb_alpha(unsigned char alpha);
//����colorkey
char player_set_colorky(unsigned char r,unsigned char g,unsigned char b);
//ֹͣ�����ֻ���Ƶ��
char player_stop_phone_audio(void);
//�����ֻ���Ƶ��
char player_start_phone_audio(void);
//¼����ʼ
char player_start_audio_record(void);
//¼��ֹͣ
char player_stop_audio_record(void);
//����¼���ı������
char player_set_record_par(AV_AUDIO_INFO_S *par);
//����ͼ�����ʾ����
char player_set_src_rsz(unsigned short x,unsigned short y,unsigned short w,unsigned short h);
//������Ļ����ʾ����
char player_set_scn_rsz(unsigned short x,unsigned short y,unsigned short w,unsigned short h);
//���������������˳�
char player_exit(void);
//�����������쳣������˳�
char player_emergency_exit(void);
void player_msg_init(void);
char player_get_msg(unsigned char ch,void *infor);

#endif
