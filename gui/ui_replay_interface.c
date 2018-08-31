#include <stdio.h>
#include<string.h>
#include <pthread.h>
#include "ui_storage_interface.h"
#include "ui_replay_interface.h"
static time_t cur_playTime=0;
static time_t ch_playtm[NVR_MAX_CHANNEL_NUM];
static unsigned char dis_mode=0;
static RecordInfo *pstRecord_back=NULL;
static unsigned char single_ch;
static unsigned char file_over=0;
static unsigned char find_dir=1;
static int g_speed = EN_NORMAL_RATE;
static int g_play_dir = EN_PLAY_FORWARD;
static time_t pre_endtm[NVR_MAX_CHANNEL_NUM];//Ҫ�г�ʼ��ֵ?????
pthread_mutex_t replay_lock = PTHREAD_MUTEX_INITIALIZER;
static void ui_replay_ctl(unsigned char flag);
static void ui_replay_update_now(void);
static void ui_replay_normal(void);
static void ui_replay_put_new_file_continue(unsigned char ch,RecordInfo*record_infor,player_status *status);
static void ui_replay_put_new_file_break(void);
static void ui_replay_get_all_ch_status(player_status *status);
static int ui_replay_check_all_over(player_status*status);
static int ui_replay_find_nearly_file(int ch, RecordInfo *pstRecordInfo, time_t time,RecordQueryInfo *pstFragement);
static void ui_replay_time_adjust(player_status *status);
static int ui_replay_find_continue_file(int ch, RecordInfo *pstRecordInfo, time_t time,unsigned char dir_ahead,RecordQueryInfo *pstFragement);
int ui_replay_find_at_current(int ch, RecordInfo *pstRecordInfo, time_t time,unsigned char dir_ahead,RecordQueryInfo *pstFragement);
static void ui_replay_update_playtime(player_status* status);
static void ui_replay_update_other_channel(void);
//playTimeƫ��ʱ�䵥λs
int ui_replay_playforward(void)
{
	find_dir=1;
	return 0;
}
int ui_replay_playback(void)
{
	find_dir=0;
	return 0;
}
int ui_replay_set_mode(int displaymode, int select_ch,int sta)
{
	pthread_mutex_lock(&replay_lock);
	if((!displaymode)&&dis_mode&&(pstRecord_back!=NULL))
	{
		unsigned char i;
		for(i=0;i<NVR_MAX_CHANNEL_NUM;i++)
		{
			ch_playtm[i]=cur_playTime;
		}	
		if(sta)
		{
			ui_replay_update_other_channel();
		}
	}	
	dis_mode=displaymode;
	single_ch=select_ch;
	pthread_mutex_unlock(&replay_lock);
	return 0;
}
int ui_replay_start(time_t playTime, RecordInfo *pstRecord, int displaymode, int select_ch)
{
	unsigned char i;
	pthread_mutex_lock(&replay_lock);
	dis_mode=displaymode;
	single_ch=select_ch;
	if(NULL!=pstRecord)
	{
		pstRecord_back=pstRecord;
		cur_playTime=playTime+pstRecord->tm_start;
		printf("offset:%ld,set time :%ld\r\n",playTime,cur_playTime);	
		for(i=0;i<NVR_MAX_CHANNEL_NUM;i++)
		{
			ch_playtm[i]=cur_playTime;
		}
		ui_replay_ctl(1);
	}
	pthread_mutex_unlock(&replay_lock);
	return 0;
}
int ui_replay_callback(void)
{
	pthread_mutex_lock(&replay_lock);
	if((pstRecord_back!=NULL)&&(!file_over))
	{
		ui_replay_ctl(0);
		pthread_mutex_unlock(&replay_lock);	
		return 0;
	}
	else
	{
		printf("pstRecord_back or file_over is false\r\n");		
		pthread_mutex_unlock(&replay_lock);	
		return -1;
	}
}
int ui_replay_stop(void)
{
	return 0;
}
int ui_replay_get_time(void)
{
	return cur_playTime-pstRecord_back->tm_start;
}
static void ui_replay_ctl(unsigned char flag)
{	
	if(flag)
	{
		ui_replay_update_now();
	}
	else
	{
		ui_replay_normal();
	}
}
static void ui_replay_update_other_channel(void)
{
	file_info replay_info[NVR_MAX_CHANNEL_NUM];
	unsigned char i;
	for(i=0;i<NVR_MAX_CHANNEL_NUM;i++)
	{
		if(i==single_ch)
		{
			continue;
		}
		if(!ui_replay_find_at_current(i,pstRecord_back,ch_playtm[i],1,&replay_info[i].query))
		{
			file_over=0;
			pre_endtm[i]=replay_info[i].query.end_time;
			replay_info[i].set_time=ch_playtm[i];			
			if(player_replay_play(i,&replay_info[i],1))
			{
				printf("player_replay_play fail\r\n");
			}
		}
		else
		{
			player_stop(i);
			pre_endtm[i]=ch_playtm[i];
			replay_info[i].query.chn=-1;
		}
	}
}
static void ui_replay_update_now(void)
{//��Ϊ����
	unsigned char i,j,play_already=0;
	file_info replay_info[NVR_MAX_CHANNEL_NUM];
	i=dis_mode?single_ch:0;
	j=dis_mode?single_ch+1:NVR_MAX_CHANNEL_NUM;
	for(;i<j;i++)
	{//��ǰʱ���Ƿ���¼���
		if(!ui_replay_find_at_current(i,pstRecord_back,ch_playtm[i],1,&replay_info[i].query))
		{
			play_already=1;
			file_over=0;
			pre_endtm[i]=replay_info[i].query.end_time;

			replay_info[i].set_time=ch_playtm[i];
		}
		else
		{
			printf("ch:%d send stop cmd\r\n",i);		//��Ҫ������ͣ����	
			pre_endtm[i]=ch_playtm[i];
			replay_info[i].query.chn=-1;
		}
	}
	if(play_already)
	{
		if(player_replay_play(dis_mode?single_ch:NVR_MAX_CHANNEL_NUM,dis_mode?&replay_info[single_ch]:replay_info,1))
		{
			printf("player_replay_play fail\r\n");
		}
	}
	else
	{
		player_stop(NVR_MAX_CHANNEL_NUM);
		ui_replay_put_new_file_break();
	}
}
static void ui_replay_normal(void)
{//��Ȼ���ŵ������
	player_status status[NVR_MAX_CHANNEL_NUM];	
	ui_replay_get_all_ch_status(status);	
	ui_replay_update_playtime(status);
	ui_replay_time_adjust(status);///  ?????
	if(!ui_replay_check_all_over(status))
	{//����ͨ���������
		ui_replay_put_new_file_break();
	}
	else
	{//��ͨ�����ڲ���
		unsigned char i,j;		
		i=dis_mode?single_ch:0;
		j=dis_mode?single_ch+1:NVR_MAX_CHANNEL_NUM;
		for(;i<j;i++)
		{
			ui_replay_put_new_file_continue(i,pstRecord_back,&status[i]);
		}
	}
}
static void ui_replay_update_playtime(player_status* status)
{
	unsigned char i,j;
	time_t min_tm=0x7fffffff;
	time_t point_t;
	i=dis_mode?single_ch:0;
	j=dis_mode?single_ch+1:NVR_MAX_CHANNEL_NUM;	
	for(;i<j;i++)
	{
		if(!status[i].replay_end)
		{
			point_t=status[i].play_time_point;///1000;
			if(point_t<min_tm)
			{
				min_tm=point_t;
				cur_playTime=min_tm;
			}
		}
	}
}
static void ui_replay_put_new_file_continue(unsigned char ch,RecordInfo*record_infor,player_status *status)
{
	file_info replay_info;
	if(status->query_num==1)
	{
		if(!ui_replay_find_continue_file(ch,record_infor,pre_endtm[ch],1,&replay_info.query))
		{
			pre_endtm[ch]=replay_info.query.end_time;
			replay_info.set_time=0;
			if(player_replay_play(ch,&replay_info,0))
			{
				printf("player_replay_play fail\r\n");
			}
		}
	}
	else if(status->query_num==2)
	{
		if(!ui_replay_find_at_current(ch,record_infor,ch_playtm[ch],1,&replay_info.query))
		{
			pre_endtm[ch]=replay_info.query.end_time;			
			replay_info.set_time=0;
			if(player_replay_play(ch,&replay_info,0))
			{
				printf("player_replay_play fail\r\n");
			}
		}
	}
}
static void ui_replay_put_new_file_break(void)
{
	unsigned char i,j;
	file_info replay_info[NVR_MAX_CHANNEL_NUM];
	time_t min_tm=0x7fffffff;
	i=dis_mode?single_ch:0;
	j=dis_mode?single_ch+1:NVR_MAX_CHANNEL_NUM;
	file_over=1;
	for(;i<j;i++)
	{
		replay_info[i].query.begin_time=0x7fffffff;
		if(ui_replay_find_nearly_file(i,pstRecord_back,ch_playtm[i],&replay_info[i].query))
		{
			printf("ch:%d ui_replay_find_nearly_file fail\r\n",i);
			continue ;
		}
		if(replay_info[i].query.begin_time<=min_tm)
		{			
			file_over=0;
			min_tm=replay_info[i].query.begin_time;
			replay_info[i].set_time=0;
		}
	}
	i=dis_mode?single_ch:0;
	j=dis_mode?single_ch+1:NVR_MAX_CHANNEL_NUM;	
	for(;i<j;i++)
	{
		if(replay_info[i].query.begin_time==min_tm)
		{
			pre_endtm[i]=replay_info[i].query.end_time;
			if(player_replay_play(i,&replay_info[i],0))
			{
				printf("player_replay_play fail\r\n");
			}
		}
	}
	
}

static void ui_replay_get_all_ch_status(player_status *status)
{	
	if(player_get_player_status(NVR_MAX_CHANNEL_NUM,status))
	{
		printf("player_get_player_status fail\r\n ");
	}
}
static void ui_replay_time_adjust(player_status *status)
{
	unsigned char i;
	for(i=0;i<NVR_MAX_CHANNEL_NUM;i++)
	{
		if(status[i].replay_end)
		{//ͨ���Ѿ�������ϣ�ʱ��У��
			ch_playtm[i]=pre_endtm[i];
			if(cur_playTime>ch_playtm[i])
			{//��ͨ�����ڷţ�ʱ�����ֹͣͨ����ʱ��
				ch_playtm[i]=cur_playTime;
			}
		}
	}
}
static int ui_replay_check_all_over(player_status*status)
{
	unsigned char i,j;
	i=dis_mode?single_ch:0;
	j=dis_mode?single_ch+1:NVR_MAX_CHANNEL_NUM;	
	for(;i<j;i++)
	{
		if(!status[i].replay_end)
		{//��ͨ�����ڲ���
			return -1;
		}
	}
	return 0;
}
static int ui_replay_find_nearly_file(int ch, RecordInfo *pstRecordInfo, time_t time,RecordQueryInfo *pstFragement)
{
	int i = 0;
	int fragementNo = 0;
	RecordQueryInfo *pstQuery = NULL,*pstquery_back=NULL;
	ChRecordInfo *pstChRecord = NULL;
	time_t min_tm=0x7fffffff;
	if (pstFragement == NULL)
		goto err;
	
	pstChRecord = &pstRecordInfo->stChRecord[ch];
	fragementNo = pstChRecord->fragement;
	if (fragementNo == 0) 
		goto err;

	for (i = 0; i < fragementNo; i++)
	{
		pstQuery = &pstChRecord->pstRecordHead[i];
	//	printf("ch:%d,begain time:%d,end_time:%d\r\n",ch,pstQuery->begin_time,pstQuery->end_time);		
		if(pstQuery->begin_time>=time)
		{
			if((pstQuery->begin_time-time)<=min_tm)
			{
				min_tm=pstQuery->begin_time-time;
				pstquery_back=pstQuery;
			}
		}
	}

	if (NULL== pstquery_back)
		goto err;
	
	memcpy(pstFragement, pstquery_back, sizeof(RecordQueryInfo));
	return 0;

err:
	memset(pstFragement, 0, sizeof(RecordQueryInfo));
	return -1;
}
static int ui_replay_find_continue_file(int ch, RecordInfo *pstRecordInfo, time_t time,unsigned char dir_ahead,RecordQueryInfo *pstFragement)
{
	int i = 0 ;
	int fragementNo = 0;
	RecordQueryInfo *pstQuery = NULL;
	ChRecordInfo *pstChRecord = NULL;
	if (pstFragement == NULL)
		goto err;
	
	pstChRecord = &pstRecordInfo->stChRecord[ch];
	fragementNo = pstChRecord->fragement;
	if (fragementNo == 0) 
		goto err;

	for (i = 0; i < fragementNo; i++)
	{
		pstQuery = &pstChRecord->pstRecordHead[i];
		if(dir_ahead)
		{//��ǰ��
			if(pstQuery->begin_time==time)
			{
				memcpy(pstFragement, pstQuery, sizeof(RecordQueryInfo));
				return 0;
			}
		}
		else
		{//�����
			if(pstQuery->end_time==time)
			{
				memcpy(pstFragement, pstQuery, sizeof(RecordQueryInfo));
				return 0;
			}
		}
	}
err:
	memset(pstFragement, 0, sizeof(RecordQueryInfo));
	return -1;
}
int ui_replay_find_at_current(int ch, RecordInfo *pstRecordInfo, time_t time,unsigned char dir_ahead,RecordQueryInfo *pstFragement)
{
	int i = 0 ;
	int fragementNo = 0;
	RecordQueryInfo *pstQuery = NULL;
	ChRecordInfo *pstChRecord = NULL;

	if (pstFragement == NULL)
		goto err;
	
	pstChRecord = &pstRecordInfo->stChRecord[ch];
	fragementNo = pstChRecord->fragement;
	if (fragementNo == 0) 
		goto err;

	for (i = 0; i < fragementNo; i++)
	{
		pstQuery = &pstChRecord->pstRecordHead[i];
		//printf("ch:%d,begain time:%d,end_time:%d\r\n",ch,pstQuery->begin_time,pstQuery->end_time);
		if((pstQuery->begin_time <time)&&(pstQuery->end_time >time))
		{//���ܼ���=��������ֹͨ���ղ����꣬Ȼ���ּ������ң��鵽�ľ��ǸղŲ�������ļ�
			break;
		}
		else if((pstQuery->begin_time == time)||(pstQuery->end_time == time))
		{
			if((dir_ahead)&&(pstQuery->begin_time == time))
			{//��ǰ����
				break;
			}
			else if((!dir_ahead)&&(pstQuery->end_time == time))
			{//��󲥷�
				break;
			}
		}
	}

	if (i == fragementNo)
		goto err;
	
	memcpy(pstFragement, pstQuery, sizeof(RecordQueryInfo));
	return 0;

err:
	memset(pstFragement, 0, sizeof(RecordQueryInfo));
	return -1;
}

int speedModeTable[EN_PLAY_BACKWORD+1][EN_SPEED_RATE8+1] =
{
	//ǰ��
	///////////////////////////////
	{FLU_WORK_S8_RATE,   //����3
	FLU_WORK_S4_RATE,	//����2
	FLU_WORK_S2_RATE,	//����1
	FLU_WORK_NOMAL_RATE,//����
	FLU_WORK_F2_RATE,	//����1
	FLU_WORK_F4_RATE,	//����2
	FLU_WORK_F8_RATE,},	//����3
	//����
	////////////////////////////////////
	{FLU_WORK_NOMAL_RATE,//����3,�ݲ�֧��
	FLU_WORK_NOMAL_RATE,//����2,�ݲ�֧��
	FLU_WORK_NOMAL_RATE,//����1,�ݲ�֧��
	FLU_WORK_NOMAL_RATE,//���ٺ���,�ݲ�֧��
	FLU_WORK_B2_RATE,	//���ٺ���1
	FLU_WORK_B4_RATE,	//���ٺ���2
	FLU_WORK_B8_RATE,	}//���ٺ���3
};


int ui_replay_clear_stream(EN_PLAY_SPEED speed)
{
	player_set_speed(NVR_MAX_CHANNEL_NUM, speed);
	return 0;
}

int ui_set_speed_dir(int speed, int dir)
{	
	int mode;
	
	if ((speed < 0)&&(dir < 0))
		return -1;

	if ((speed > EN_SPEED_RATE8)||(dir > EN_PLAY_BACKWORD))
	{		
		return -1;
	}

	if (dir < 0)
	{
		//dir < 0 ֻ�����ٶ�	
		mode = speedModeTable[g_play_dir][speed];		
		g_speed = speed;
	}
	else if (speed < 0)
	{		
		//speed < 0 ֻ���÷���	
		mode = speedModeTable[dir][g_speed];		
		g_play_dir = dir;		
	}
	else
	{
		mode = speedModeTable[dir][speed];		
		g_speed = speed;		
		g_play_dir = dir;		
	}
	//�����ȫ��ģʽ�¿������ֱ���޸�Ϊ���IFrame����
	if(dis_mode==0&&mode>=FLU_WORK_F2_RATE&&mode<=FLU_WORK_F8_RATE)
		mode = mode - FLU_WORK_F2_RATE + FLU_WORK_F2_IFRAME_RATE;
	player_set_speed(NVR_MAX_CHANNEL_NUM, mode);

	return 0;
}
		

