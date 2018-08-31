/////////////////////////////////////////////////////////////
//////////////////// hi_dianxin_proc.h //////////////////////
/////////////////////////////////////////////////////////////

#ifndef __HI_DIANXIN_PROC_H__
#define __HI_DIANXIN_PROC_H__

#include "hi_platform_dianxin.h"

#define MANUFACTURER_JXJ  "850"		//���̱��


typedef enum _DIANXIN_DEVTYPE_E_
{
	DIANXIN_IPCAM 	= 1,
	DIANXIN_DVR		= 2,
	DIANXIN_NVR		= 3,
}DIANXIN_DEVTYPE;


typedef enum _DIANXIN_CMD_TYPE_E_
{
	CMD_LOGIN				= 0x31,			//��½��֤����/ȷ��
	CMD_ABILITYUP			= 0x32,			//�����ϱ�����/ȷ��
	CMD_HEARTBEAT			= 0x33,			//��·�������/ȷ��
	CMD_EXCEPTION_NOTIFY	= 0x34,			//�쳣�����ϱ�/ȷ��
	CMD_VIDEO_PLAY			= 0x35,			//��Ƶ���Token��֤����/ȷ��
	CMD_NOTIFY_PICTURE		= 0x36,			//FTPͼƬץ��֪ͨ 
	CMD_ALARM_NOTIFY		= 0x37,			//�豸�澯�����ϱ�
	
	CMD_SET_CHANNEL			= 0x60,			//��Ƶ������������/ȷ��
	CMD_GET_CHANNEL			= 0x61, 		//��Ƶ������ѯ����/ȷ�� 
	CMD_GET_WIFI			= 0x62,			//���������ѯ/ȷ��	
	CMD_SET_WIFI			= 0x63,			//���������ѯ/ȷ��
	CMD_VIDEO_PTZ			= 0x64,			//��̨��������/ȷ��
	CMD_SET_ESTORE			= 0x65,			//�����ƴ洢�ʺ���������/ȷ��
	CMD_GET_ESTORE			= 0x66, 		//�����ƴ洢�ʺŲ�ѯ����/ȷ�� 
	CMD_ADD_RECORD_POLICY	= 0x67,			//�洢¼��������/ȷ�� 
	CMD_QUERY_RECORD_POLICY	= 0x68, 		//�洢¼����Բ�ѯ/ȷ�� 
	CMD_DEL_RECORD_POLICY	= 0x69,			//�洢¼�����ɾ��/ȷ�� 
	CMD_REBOOT				= 0x6c,			//�����Զ������
	CMD_UPGRADE				= 0x6d,			//Զ������֪ͨ 
	CMD_NVR_BIND_CAMERA		= 0x6e,			//NVR �����������
	CMD_NVR_MODIFY_CAMERA	= 0x6f,			//NVR �޸��������������Ϣ
	CMD_NVR_REMOVE_CAMERA	= 0x70,			//NVR ��������������
	CMD_NVR_QUERY_CAMERA	= 0x71,			//NVR ��ѯ�����������
	CMD_FILE_QUERY			= 0x72,			//��Ƶ¼�����
	CMD_RECORD_PLAY			= 0x74,			//��Ƶ¼��ط���֤
	CMD_ADD_PICTURE_POLICY	= 0x75,			//�洢ͼƬ������� 
	CMD_QUERY_PICTURE_POLICY= 0x76,			//�洢ͼƬ���Բ�ѯ 
	CMD_DEL_PICTURE_POLICY	= 0x77,			//�洢ͼƬ����ɾ�� 
	CMD_SET_RECORD_FULL		= 0x78,   		//һ��ȫ��¼������
	CMD_GET_RECORD_FULL		= 0x79, 		//һ��ȫ��¼���ѯ 
	CMD_SET_RECORD_LOOP		= 0x7a,			//ѭ��¼���ʶ���� 
	CMD_GET_RECORD_LOOP		= 0x7b,			//ѭ��¼���ʶ��ѯ 
	CMD_SET_ALARM			= 0x7c,			//�豸������������
	CMD_GET_ALARM			= 0x7d,			//�豸�������ز�ѯ
	CMD_LOG_UPDATE			= 0x7e,			//�豸��־�ϴ�֪ͨ 
	CMD_QUERY_STORAGE		= 0x7f,			//���ش洢״̬��ѯ
	CMD_STORAGE_FORMAT		= 0x80,			//���ش洢��ʽ��
	CMD_SET_FORMAT			= 0x91,			//һ����ʽ��
}DIANXIN_CMD_TYPE;

typedef enum _DIANXIN_ALARM_TYPE_E
{
	ALARM_MD			= 1,	//�ƶ����
	ALARM_BODY_IRC 		= 2,	//�������
	ALARM_MANUAL		= 3, 	//�ֶ�����
	ALARM_DI			= 4,	//����������
}DIANXIN_ALARM_TYPE;

typedef struct _DINAXIN_FILE_QUERY_S_
{
	int chn;
	int nStartTime;
	int nEndTime;
	int PageNo;
}DIANXIN_FILE_QUERY;

#define MXMLGETTEXT(node, whitespace) ((mxmlGetText(node, whitespace) == NULL)? (""):(mxmlGetText(node, whitespace)))


int hi_dianxin_group_register(DIANXIN_CTRL *pDianxinCtrl);

int hi_dianxin_lcms_register(DIANXIN_CTRL *pDianxinCtrl);

int hi_dianxin_login_req(DIANXIN_CTRL *pDianxinCtrl);

int hi_dianxin_abilityup_req(DIANXIN_CTRL *pDianxinCtrl);

int hi_dianxin_heart_beat_req(DIANXIN_CTRL *pDianxinCtrl);

int hi_dianxin_exception_notify_proc(DIANXIN_CTRL *pDianxinCtrl);

//int hi_dianxin_alarm_notify_req(DIANXIN_CTRL *pDianxinCtrl, LPHI_ALARM_INFO_S pAlarmInfo);

int hi_dianxin_recv(DIANXIN_CTRL *pDianxinCtrl);

int hi_dianxin_video_play_req(DIANXIN_VIDEO_PLAY *pVideoPlay);

int hi_dianxin_record_play_req(DIANXIN_VOD_PLAY *pVodPlay);







#endif
