#ifndef __NVR_CHANNEL_H__
#define __NVR_CHANNEL_H__

#include <nvr_server_headers.h>
#include <ipnc_lib.h>


//int nvr_update_channel_info(int port, NVR_CHANNEL_CFG_S *pChannelCfg);
int nvr_channel_update_cfg(int port, NVR_CHANNEL_CFG_S *pChannelCfgInfo);

int nvr_channel_update_time(NVR_TIME_S *pTimeCfg);
//ptz����
int nvr_channel_ptz(int nChn, void *pPtz);
//������ȡ
int nvr_channel_get_param(int nChn, IPNC_CMD_TYPE_E cmd, void *data, int dataSize);
//��������
int nvr_channel_set_param(int nChn, IPNC_CMD_TYPE_E cmd, void *data, int dataSize);
//�������ӵ�ipc
int nvr_channel_reboot_all_ipc();
//�ػ����ӵ�ipc
int nvr_channel_halt_all_ipc();
//�����ӵ�ipc�ָ�Ĭ��
int nvr_channel_default_all_ipc();

int nvr_channel_init();

void nvr_channel_uninit();



#endif
