/////////////////////////////////////////////////////////////
//////////////////// hi_dianxin_common.h //////////////////////
/////////////////////////////////////////////////////////////

#ifndef __HI_DIANXIN_COMMON_H__
#define __HI_DIANXIN_COMMON_H__

#include <mxml.h>

#pragma pack(push)
#pragma pack(push, 1)


typedef struct _HI_DIANXIN_MSG_HEAD_S_
{
	unsigned short	u16Head;		//��ʼ��ͷ�á�FAH F5H����ʾ
	unsigned char	u8Cmd;			//������
	unsigned short	u16Seq;			//��ˮ�� ʹ�������ֽ�˳����
	unsigned char	u8Remark;		//�����ֶ�
	unsigned short	u16Len;			//���ݳ��� ʹ�������ֽ�˳����
}HI_DIANXIN_MSG_HEAD;
#define DIANXIN_MSG_HEAD_LEN	(sizeof(HI_DIANXIN_MSG_HEAD))

#pragma pack(pop)


int dainxin_mxml_string_copy(char *pBuf, mxml_node_t *pNode);

int hi_dianxin_register_recv(int nFd, char *pRecvBuf, int nRecvLen);

mxml_node_t *dianxin_mxml_node_get(mxml_node_t *pParent, char *pNodeName);

int hi_dianxin_parse_url(char *pGroupUrl, char *pIp, char *pPort, char *pUrl);

int hi_dianxin_http_write(int fd, const char * body, int bodysize,
          const char * headers, int headerssize);

int hi_dianxin_message_send(int fd, int nCmd, int nSeq, char *pBodyBuf, int nBodyLen);



#endif

