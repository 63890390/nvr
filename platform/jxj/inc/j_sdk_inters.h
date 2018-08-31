#ifndef __SDK_INTERFACES_H__
#define __SDK_INTERFACES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "j_sdk.h"
#include "media_structs.h"

#define CTL_CMD_IFRAME          1


enum
{
	NOTYPE  = 0x0,
	UPGRADE = 0x10,
	AUDIO   = 0x20,
};
enum
{
	UPGRADE_ERROR  = -1,
	UPGRADE_NORMAL = 0,
	UPGRADE_START  = 1,
	UPGRADE_END    = 2
};
enum
{
	FORBID_CONNECT = 0,            //��ֹ����
	PERMIT_CONNECT = 1,            //��������
};

typedef struct _user
{
	char ip[J_SDK_MAX_IP_LEN];
	char name[J_SDK_MAX_NAME_LEN];
    char local[J_SDK_MAX_IP_LEN];
}user_t;

typedef struct __avs_media avs_media;

/* ʵʱ���ӿ� */
typedef struct __ls_avs_ops ls_avs_ops;
struct __ls_avs_ops
{
    int32_t (*probe)(int32_t channel, int32_t level, media_info_t *mi);     /* ��ȡý����Ϣ,���ܱ��������� */
    int32_t (*open)(avs_media *m, int32_t channel, int32_t level);          /* ��ʼ�� */
    int32_t (*play)(avs_media *m);                                          /* ������֮�����ʹ��avs_media_fill()����ʵʱ�� */
    int32_t (*ctrl)(avs_media *m, uint32_t cmd, void *data);                /* ���ƣ�cmd=1,data=NULL ǿ��I֡; */
    void    (*close)(avs_media *m);                                         /* �ر� */
};

/* ��ʷ���ӿ� */
typedef struct __hs_avs_ops hs_avs_ops;
struct __hs_avs_ops
{
    int32_t (*probe)(int32_t channel, int32_t level, int32_t type,       
        uint8_t *start_time, uint8_t *end_time, uint8_t *property,          /* ʱ���ʽ:YYYYMMDDHHMMSS */
        media_info_t *mi);                                                  /* ��ȡý����Ϣ,���ܱ��������� */
    int32_t (*open)(avs_media *m, int32_t channel, int32_t level,
        int32_t type, uint8_t *start_time, uint8_t *end_time, uint8_t *property); /* ��ʼ�� */
    int32_t (*play)(avs_media *m);                                          /* SDK������ʼ�ص�.pull(), ����userʵ����ز��ԣ���Ԥ���ȣ�����ΪNULL */
    int32_t (*pause)(avs_media *m);                                         /* SDK������ͣ�ص�.pull(), ����userʵ����ز��ԣ���Ԥ���ȣ�����ΪNULL */
    int32_t (*lseek)(avs_media *m, uint32_t ts);                            /* ��λ */
    void    (*close)(avs_media *m);                                         /* �ر� */
    int32_t (*pull)(avs_media *m, frame_t **frm);                           /* SDK��ȡ��ʷ��Ƶ��HOOK */
};

/* ����������ӿ� */
void avs_media_set_u(avs_media *m, void *u);                 /* �����û����� */
void *avs_media_get_u(avs_media *m);                         /* ��ȡ�û����� */
int avs_media_fill(avs_media *m, frame_t *frm);                 /* ʵʱ������ */
void avs_media_kill(avs_media *m);                             /* ����ͨ��AVS */
avs_media *avs_media_ref(avs_media *m);                       /* ���ԶԾ�������� */
void avs_media_unref(avs_media *m);                          /* ���ٶԾ�������� */

/* ֡����ӿڣ�������ʷ��pull */
frame_t *avs_alloc_frame(uint32_t data_size, uint32_t nal_count);   /* ����һ֡�Ŀռ� */
void avs_free_frame(frame_t *frame);                                /* �ͷ�һ֡�ռ䣬�����֡����ʧ��ʱʹ�� */


/* �豸�����ӿ� */
struct device_ops
{
	int (*get_device_param)(int param_id, int channel, void *param, user_t *u);    /* ��ȡ�豸���� */
	int (*set_device_param)(int param_id, int channel, void *param, user_t *u);    /* �����豸���� */
	
	void (*log)(const char *msg);                                                  /* ��־����ӿ� */
};

struct platfrom_param
{
	char pu_id[J_SDK_MAX_ID_LEN];     //�豸PUID
	char cms_host[J_SDK_MAX_IP_LEN];  //ƽ̨������ַ
	int pu_type;                      //�豸����
	int cms_port;                     //ƽ̨�����˿�
	int data_port;                    //��ý��˿�
	int protocol;                     //1-UDP, 0-TCP
	int conn_cms;                     //1-���� 0-������
};

struct cloud_param
{
    char dev_code[J_SDK_MAX_ID_LEN];        //�豸�������
    char software[J_SDK_MAX_VERSION_LEN];   //�豸����汾
    char dispense_host[J_SDK_MAX_IP_LEN];   //���ɷ�������ַ
    int dispense_port;                      //���ɷ������˿�
	int conn_cloud;                         //1-���� 0-������
};

/* SDK ���������ӿ� */
int  j_dev_sdk_init(int listen_port);                                      /* ��ʼ��SDK */
int  j_dev_sdk_register_device_ops(struct device_ops *ops);          /* ע���豸�����ӿ� */
int  j_dev_sdk_register_avs_ops(ls_avs_ops *lso, hs_avs_ops *hso);    /* ע����ý��ӿ� */
int  j_dev_sdk_set_platfrom_param(struct platfrom_param *plt_pm);    /* ����ƽ̨��Ϣ */
int  j_dev_sdk_set_cloud_param(struct cloud_param *cld_pm);          /* ������ƽ̨��Ϣ */
int  j_dev_sdk_run_server();                                           /* ������ط��� */
void j_dev_sdk_stop_server();                                          /* ֹͣ���� */
void j_dev_sdk_cleanup();                                               /* ����SDK */

int j_dev_sdk_submit_param(int parm_id, int channel, void *parm);     /* �ϱ���Ϣ�ӿ� */

#ifdef __cplusplus
}
#endif

#endif	/* __SDK_INTERFACES_H__ */

