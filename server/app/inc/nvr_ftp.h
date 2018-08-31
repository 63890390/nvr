#ifndef __NVR_FTP_H__
#define __NVR_FTP_H__

#include "nvr_struct.h"

#define NVR_FTP_PORT_STR		"21"


/*�ϴ��ļ�
	pftpcfg:FTP��Ϣ���ýṹ��ָ��
	pfilename���ļ���(����·��)
	pfilepath���ļ�����Ŀ¼ȫ·��(ĩβ������/��)
�ɹ�����:226
*/
int nvt_ftp_upload(NVR_FTP_CFG_S* pftpcfg ,char* pfilename, char* pfilepath);

/*
	�ļ��ϴ����ƺ���
*/
void nvr_ftp_upload_ctrl(char* data[]);
#endif

