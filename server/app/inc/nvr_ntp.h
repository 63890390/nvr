#ifndef __NVR_NTP_H__
#define __NVR_NTP_H__
#include <nvr_server_headers.h>
/*NTP������\�˿ں�*/
#define NVR_NTP_SERVER_IP1       "cn.pool.ntp.org"	/*������ʱ����*/
#define NVR_NTP_SERVER_IP2       "time.windows.com"
#define NVR_NTP_SERVER_IP3	"time.nist.gov"
#define NVR_NTP_PORT_STR        "123"          		/*NTPר�ö˿ں��ַ���*/
#define NVR_NTP_PORT            123          		/*NTPר�ö˿ں�*/

/*NTP��ͷ����*/
#define NVR_NTP_PCK_LEN				48
#define NVR_NTP_LI 					0
#define NVR_NTP_VN 					3
#define NVR_NTP_MODE 				3
#define NVR_NTP_STRATUM 			0
#define NVR_NTP_POLL 				4
#define NVR_NTP_PREC 				-6

/*ʱ�����*/
#define NVR_NTP_JAN_1970 	  	0x83aa7e80/* 1900�ꡫ1970��֮���ʱ������ */
#define NVR_NTPFRAC(x)			(4294 * (x) + ((1981 * (x)) >> 11))/*NTPFRAC�������ڼ���x*4294.967296�ķǾ�ȷд���������ͱ����˸������*/
#define NVR_NTPUSEC(x)			(((x) >> 12) - 759 * ((((x) >> 10) + 32768) >> 16))/*USEC��������̵ķ����̣���ʾx/4294.967296*/

#define SUMMERTIMEMONTHBEGIN    3  //!< European Summer Time begin at March     */
#define SUMMERTIMEMONTHEND     10  //!< European Summer Time end at October     */

/*NTPʱ���ʽ*/
typedef struct _NVR_NTP_TIME
{
	unsigned int coarse;	//1900��1��1��0ʱ0������������
	unsigned int fine;		//΢���4294.967296(=2^32/10^6)��
} NVR_NTP_TIME;

/*NTP���ݸ�ʽ����СΪ48�ֽ�,8λ���룬���������ַ������ȡ����*/
typedef struct _NVR_NTP_PACKET
{
	unsigned char leap_ver_mode;/*��Ϊ����:ǰ2λΪ����ָʾ��һ����0;
								  �м�3λΪNTPЭ��汾�ţ�Ϊ3;		
								  ���3λΪͨ��ģʽ��Ϊ3����ʾ��client.*/

	unsigned char startum;		//NTP�������׼���0��ʾ��ָ����1��ʾУ׼��ԭ���ӡ�Ϊ0��
	char poll;					//��ʾ���Լ��Ϊ2^poll_intervals��,Ϊ4��
	char precision;				//��ʾ����ʱ�Ӿ���Ϊ2^local_precision�롣local_precisionͨ��Ϊ������Ϊ-6��

	int root_delay;				//�����ɸ���2^16��ʾһ�롣���庬��μ�RFC1305��4~7
	int root_dispersion;		//ֻ��Ϊ����2^16��ʾһ�롣���庬��μ�RFC1305��8~11
	int reference_identifier;	//���庬��μ�RFC1305��һ����0��12~15

	/*����ʱ��*/
	NVR_NTP_TIME reference_timestamp;//���庬��μ�RFC1305��һ����0��16~19:20~23
	NVR_NTP_TIME originage_timestamp;//�ϴη���ʱ�� 24~27:28~31
	NVR_NTP_TIME receive_timestamp;	 //����ʱ�� 32~35:36~39
	NVR_NTP_TIME transmit_timestamp; //����ʱ�� 40~43:44~47

}NVR_NTP_PACKET;

/*NTP����Žṹ��*/
typedef struct _NVR_NTP_PACKET_STR
{
	NVR_NTP_PACKET ntpPacket;			//NTP���ݰ�
	char ntpPacketBuf[NVR_NTP_PCK_LEN];	//NTP���ݰ�������

}NVR_NTP_PACKET_STR;

//ntpʱ��ͬ������
typedef enum _NVR_NTP_CTRL_CMD_E_
{
	NVR_NTP_START_UPDATE = 0x01,//��ʼ����
	
}NVR_NTP_CTRL_CMD_E;

//��ʼ������
int  nvr_ntp_init(void);
void nvr_ntp_uninit(void);
//ntpʱ��ͬ������
void nvr_ntp_update();



#endif
