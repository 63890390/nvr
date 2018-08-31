#ifndef __NVR_XML_H__
#define __NVR_XML_H__

#include <semaphore.h>

extern sem_t g_xmlLock;

//��ȡ�豸����
int nvr_web_get_dev_cfg(int sock);
//���nvr����������Ϣ
int nvr_web_get_net_cfg(int sock);
//��ȡftp����
int nvr_web_get_ftp_cfg(int sock);
//��ȡsmtp����
int nvr_web_get_smtp_cfg(int sock);
//��ȡddns����
int nvr_web_get_ddns_cfg(int sock);
//��ȡupnp����
int nvr_web_get_upnp_cfg(int sock);
//��ȡNTP����
int nvr_web_get_ntp_cfg(int sock);
//��ȡ�û�����
int nvr_web_get_user_cfg(int sock);
//��ȡTIME����
int nvr_web_get_time_cfg(int sock);
//��ȡ�Զ��������
int nvr_web_get_auto_cfg(int sock);
//��ȡͨ����Ϣ����
int nvr_web_get_channel_cfg(int sock);
//��ȡcomm��Ϣ����
int nvr_web_get_comm_cfg(int sock);
//��ȡrec��Ϣ����
int nvr_web_get_rec_cfg(int sock);
//��ȡ����ƽ̨��Ϣ����
int nvr_web_get_dianxin_platform_cfg(int sock);
//��ʼ����
int nvr_web_get_search_start(int sock);
//�������
int nvr_web_get_search_get(int sock, long lHandle);
//ֹͣ����
int nvr_web_get_search_stop(int sock, long lHandle);



//��xml�ļ�
int nvr_web_read_xml(const char* xmlData, long lHandle);


#endif


