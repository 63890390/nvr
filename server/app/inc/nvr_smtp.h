#ifndef __NVR_SMTP_H__
#define __NVR_SMTP_H__

#include "nvr_struct.h"

/*�����ʼ�
	pSubJect�������ʼ�����
	pBody����������
*/
void nvr_stmp_send_mail(const char* pSubJect, const char* pBody);

#endif

