/////////////////////////////////////////////////////////////////////////////////////
///////////////////////// hi_platform_dianxin.h /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#ifndef __HI_PLATFORM_DIANXIN_H__
#define __HI_PLATFORM_DIANXIN_H__

#include <stdio.h>
#include <nvr_struct.h>
#include <upnp_api.h>
#include <pthread.h>
#include <nvr_lib_interface.h>

//#define DIANXIN_DEBUG

#ifdef DIANXIN_DEBUG
#define __D(fmt, args...) fprintf(stdout, "DIANXIN DEBUG(%s:%d):" fmt, __func__, __LINE__, ## args)
#else
#define __D(fmt, args...) 
#endif

#define __E(fmt, args...) fprintf(stderr, "DIANXIN DEBUG(%s:%d):" fmt, __func__, __LINE__, ## args)


typedef enum _DIANXIN_NETTYPE_E_
{
	DIANXIN_ETH		= 0,
	DIANXIN_WIFI	= 1,
	DIANXIN_3G	 	= 2,
	DIANXIN_INIT	= 3,
}DIANXIN_NETTYPE;

typedef enum _DIANXIN_LOGIN_TYPE_E_
{
	DIANXIN_LOGIN_ERR = -1,
	DIANXIN_NO_LOGIN = 0,
	DIANXIN_FIRST_LOGIN = 1,
	DIANXIN_LOGIN = 3,
}DIANXIN_LOGIN_TYPE;


typedef struct _HI_DIANXIN_REGISTER_RES_S_
{
	char szNatIP[32];				//�豸�������������ַ
	char szNatPort[8];				//�豸������������˿�
	char szBackupNatIP[32];			//�豸���÷����������ַ
	char szBackupNatPort[8];		//�豸���÷���������˿�
	char szTurnIP[32];				//��������ַ
	char szTurnPort[8];				//�������˿�
	char szBackupTurnIP[32];		//���ݷ�������ַ
	char szBackupTurnPort[8];		//���ݷ������˿�	
	char szFtpIP[32];				//ͼƬ�ϴ� FTP ��������ַ
	char szFtpPort[8];				//ͼƬ�ϴ� FTP �������˿�	
	char szFtpAccount[32];			//ͼƬ�ϴ� FTP �������ʺ�
	char szFtpPassword[32];			//ͼƬ�ϴ� FTP ����������
	char szTime[32];				//ʱ���
}HI_DIANXIN_REGISTER_RES, LPHI_DIANXIN_REGISTER_RES;


typedef struct _HI_DIANXIN_PLATFORM_CFG_S_
{	
	uint32_t u32Size;
	char szGroupUrl[64];				//����ƽ̨URL
	char szProvincialUrl[64];			//ʡƽ̨URL
	char szDevId[32];						//�豸ID
	char szKey[32];							//key
	char szMode[16];						//�豸����
	int 	localRtspPort;
}HI_DIANXIN_PLATRORM_CFG, *LPHI_DIANXIN_PLATFORM_CFG;

typedef struct _HI_DIANXIN_ESTORE_CFG_S_
{
	char szEURL[64];		//�����ƴ洢��֤URL
	char szEAccount[32];	//�����ƴ洢�ʺ�
	char szEPassword[32];	//�����ƴ洢����
	int  nEStorgeSpace;		//�����ƴ洢�ռ��С��0 ��ʾ��֧��
	char szERecordBucket[32];	//�����ƴ洢¼�� Bucket ����
	char szEPictureBucket[32];	//�����ƴ洢ͼƬ Bucket ����
}HI_DIANXIN_ESTORE_CFG;

typedef struct _DIANXIN_VIDEO_PLAY_
{
	char szDevId[32];
	char szChannelNo[32];
	char szStreamType[32];
	char szHashToken[64];
}DIANXIN_VIDEO_PLAY;

typedef struct _DIANXIN_VOD_PLAY_
{
	char szDevId[32];
	char szChannelNo[32];
	char szFileName[32];
	char szHashToken[64];
}DIANXIN_VOD_PLAY;


typedef struct Tag_DIANXIN_CTRL
{
	int nExit;
	int nRegisterFlag;
	int nLoginStatus;
	int nSocketFd;
	int nExceptionNeedSend;
	int nExceptionType;
	int nCurVideoNum;
	int nSeq;
	int nVideoRes;
	int nVodRes;
	char szNewDevVer[32];
	char szRelayIp[32];
	int nRelayPort;
	
	HI_DIANXIN_PLATRORM_CFG stPlatformCfg;
	HI_DIANXIN_REGISTER_RES stRegister;
	HI_DIANXIN_ESTORE_CFG	stEstoreCfg;
	
	unsigned int u32LastActiveTime;
	unsigned int u32NoActiveTime;
	pthread_t 	pthreadId;
}DIANXIN_CTRL, *LPDIANXIN_CTRL;

extern DIANXIN_CTRL stDianxinCtrl;

enum
{
	EN_YPE_IPCAM = 1,
	EN_TYPE_DVR = 2,
	EN_TYPE_NVR = 3
};

#define GROUPURL 

#define LCMSURL 		"http://202.102.101.25:8098/tykd/DeviceRegisterServlet"
#define MANUFACTURER 	"112"
#define DEVICEID 		"112X1234590"
#define KEY				"12345678"
#define MODE 			"LK-NVR1604-H"
#define LOCAL_RTSP_PORT 	1554
#define UPNP_RTSP_PORT 	18588


DIANXIN_CTRL *hi_dianxin_get_ctrl();

int hi_dianxin_check_shoot();

int dianxin_video_varify_proc(char *pDevId, char *pChannelNo, 
			char *pStreamType, char *pHashToken);

int dianxin_get_video_flag();

int dianxin_vod_varify_proc(char *pDevId, char *pChannelNo, 
			char *pFileName, char *pHashToken);

int dianxin_get_vod_flag();

//int hi_dianxin_send_alarm(LPHI_ALARM_INFO_S pAlarmInfo);

int hi_dianxin_pf_init(NVR_DEV_DIANXIN_PLATFORM_CFG_S *pDevPlatformCfg);

int hi_dianxin_pf_uninit();




















#endif
