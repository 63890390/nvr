#include <sys/socket.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/un.h>
#include <sys/time.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

/*���Ž� ��װ���纯��*/
#include <net_api.h>
/*���Ž� �ṹ�嶨��*/
#include "nvr_struct.h"
#include "nvr_param_sys.h"
#include "nvr_param_proc.h"
#include "nvr_net_common.h"
#include "nvr_ntp.h"
#include "nvr_timer.h"


#undef	G_LOG_DOMAIN
#define	G_LOG_DOMAIN "ntp"

typedef struct _NVR_NET_NTP_MNG_S_
{
	guint   timeId;
	GThreadPool *pool;
}NVR_NET_NTP_MNG_S;

NVR_NET_NTP_MNG_S gNtpServerMng;
NVR_NTP_PACKET_STR g_ntpPacketStr = {{0},{0}};//NTP���ݰ�ȫ����
static const char *gBakNtpServer[] = {NVR_NTP_SERVER_IP1, NVR_NTP_SERVER_IP2, NVR_NTP_SERVER_IP3, NULL};

/*!
  \brief  Calculates start date and end of the period of summer time.
   ******************************************************************

  \param year calculates for this year
  \param bebin the start date
  \param end the end date
  \return 0 if OK or <0 if failed

  \warning the year must be lesser than 2099 !
*/


static int EuropeanSummerTime( const int year, time_t *begin, time_t *end)
{  
  struct tm st;
  
  /* ready until 2099 ! */
  if(year > 2099) return -1;

  /* start of summer time */
  memset( &st, 0, sizeof(st));
  st.tm_hour = 1;                             // 0-23 (1 heure GMT0)
  st.tm_year = year - 1900;                   // years since 1900
  st.tm_mday = 31 - (5 * year / 4 + 4) % 7;   // 1-31
  st.tm_mon = SUMMERTIMEMONTHBEGIN - 1;       // 0-11
  *begin = mktime( &st);

  /* end of summer time */
  memset( &st, 0, sizeof(st));
  st.tm_hour = 1;                             // 0-23 (1 heure GMT0)
  st.tm_year = year - 1900;                   // years since 1900
  st.tm_mday = 31 - (5 * year / 4 + 1) % 7;
  st.tm_mon = SUMMERTIMEMONTHEND - 1;
  *end = mktime( &st);

  return 0;
}

/*
   ���ܣ���ʼ��NTP��
   */
static void nvr_ntp_packet_init(char *ntpPacketBuf)
{
	long tmp_wrd;
	time_t timer;

	memset(ntpPacketBuf, 0, sizeof(ntpPacketBuf));

	/*����16�ֽڵİ�ͷ*/
	tmp_wrd = htonl((NVR_NTP_LI << 30)|(NVR_NTP_VN << 27)|(NVR_NTP_MODE << 24)|(NVR_NTP_STRATUM << 16)|(NVR_NTP_POLL << 8)|(NVR_NTP_PREC & 0xff));
	memcpy(ntpPacketBuf, &tmp_wrd, sizeof(tmp_wrd));

	/*����Root Delay��Root Dispersion*/
	tmp_wrd = htonl(1<<16);
	memcpy(&ntpPacketBuf[4], &tmp_wrd, sizeof(tmp_wrd));
	memcpy(&ntpPacketBuf[8], &tmp_wrd, sizeof(tmp_wrd));

	/*����Timestamp����*/
	/*��ȡ��ǰʱ������*/
	time(&timer);

	/*����Transmit Timestamp coarse*/
	tmp_wrd = htonl(NVR_NTP_JAN_1970 + (long)timer);
	memcpy(&ntpPacketBuf[40], &tmp_wrd, sizeof(tmp_wrd));

	/*����Transmit Timestamp fine*/
	tmp_wrd = htonl((long)NVR_NTPFRAC(timer));
	memcpy(&ntpPacketBuf[44], &tmp_wrd, sizeof(tmp_wrd));
}

/*
   ���ܣ���ȡNTPʱ��
   ����ֵ������1�ɹ���0ʧ��
   */
static int nvr_ntp_get_time(const char *nvr_ntp_server, unsigned int port)
{
	int sockfd, recv_size = 0;
	struct addrinfo hints, *res = NULL;//res����ָ�򷵻�addrinfo����
	char portStr[32] = {'0'};
	fd_set readfds;
	struct timeval time_out;

	if(0 >=  port)
		strcpy(portStr, NVR_NTP_PORT_STR);
	else
		sprintf(portStr, "%d", port);

	
	//����getaddrinfo()��������ȡNTP��������ַ��Ϣres
	memset(&hints, 0, sizeof(hints));
	hints.ai_family   = AF_UNSPEC;	//Э���޹�
	hints.ai_socktype = SOCK_DGRAM;	//���ݱ�
	hints.ai_protocol = IPPROTO_UDP;//Ϊ17:UDP
	j_debug("ntp server %s:%s", nvr_ntp_server, portStr);
	if(0 != getaddrinfo(nvr_ntp_server, portStr, &hints, &res))
	{
		j_warning("struct getaddrinfo failed");
		return 0;
	}

	/*�����׽��� UDP*/
	sockfd = net_create_sock(2);
	if (sockfd < 0 )
	{
		j_warning("create socket failed");
		goto _OUT;
	}    

	/*��ʼ��NTP���ݰ���ʽ*/
	nvr_ntp_packet_init(g_ntpPacketStr.ntpPacketBuf);
	if (sizeof(g_ntpPacketStr.ntpPacketBuf) != NVR_NTP_PCK_LEN)
	{
		j_warning("NTP packet length failed");
		goto _OUT;
	}
 
	/*�ͻ��˸��������˷���NTPЭ�����ݰ�*/
	if(net_udp_send(sockfd, g_ntpPacketStr.ntpPacketBuf, sizeof(g_ntpPacketStr.ntpPacketBuf), res->ai_addr) < 0) 
	{
		j_warning("sendto failed");
		goto _OUT;
	}

	/*����select()���������趨��ʱʱ��Ϊ15s*/
	FD_ZERO(&readfds);
	FD_SET(sockfd, &readfds);
	time_out.tv_sec  = 15;
	time_out.tv_usec = 0;
	if (select(sockfd + 1, &readfds, NULL, NULL, &time_out) > 0)
	{
		/*���շ������˵���Ϣ*/
		if((recv_size = net_udp_recv(sockfd, g_ntpPacketStr.ntpPacketBuf,sizeof(g_ntpPacketStr.ntpPacketBuf), 0, res->ai_addr,(int *)&res->ai_addrlen)) < 0)
		{
			j_warning("recvfrom failed");
			goto _OUT;
		}

		if (recv_size < NVR_NTP_PCK_LEN)
		{	
			j_warning("recvfrom NTP packet length failed");
			goto _OUT;
		}
		/* ���ý���NTP�������ݽṹ */
		g_ntpPacketStr.ntpPacket.leap_ver_mode 				= ntohl(g_ntpPacketStr.ntpPacketBuf[0]);
		g_ntpPacketStr.ntpPacket.startum 					= ntohl(g_ntpPacketStr.ntpPacketBuf[1]);
		g_ntpPacketStr.ntpPacket.poll 						= ntohl(g_ntpPacketStr.ntpPacketBuf[2]);
		g_ntpPacketStr.ntpPacket.precision 					= ntohl(g_ntpPacketStr.ntpPacketBuf[3]);
		g_ntpPacketStr.ntpPacket.root_delay 				= ntohl(*(int*)&(g_ntpPacketStr.ntpPacketBuf[4]));
		g_ntpPacketStr.ntpPacket.root_dispersion 			= ntohl(*(int*)&(g_ntpPacketStr.ntpPacketBuf[8]));
		g_ntpPacketStr.ntpPacket.reference_identifier 		= ntohl(*(int*)&(g_ntpPacketStr.ntpPacketBuf[12]));
		g_ntpPacketStr.ntpPacket.reference_timestamp.coarse = ntohl(*(int*)&(g_ntpPacketStr.ntpPacketBuf[16]));
		g_ntpPacketStr.ntpPacket.reference_timestamp.fine 	= ntohl(*(int*)&(g_ntpPacketStr.ntpPacketBuf[20]));
		g_ntpPacketStr.ntpPacket.originage_timestamp.coarse = ntohl(*(int*)&(g_ntpPacketStr.ntpPacketBuf[24]));
		g_ntpPacketStr.ntpPacket.originage_timestamp.fine 	= ntohl(*(int*)&(g_ntpPacketStr.ntpPacketBuf[28]));
		g_ntpPacketStr.ntpPacket.receive_timestamp.coarse 	= ntohl(*(int*)&(g_ntpPacketStr.ntpPacketBuf[32]));
		g_ntpPacketStr.ntpPacket.receive_timestamp.fine 	= ntohl(*(int*)&(g_ntpPacketStr.ntpPacketBuf[36]));
		g_ntpPacketStr.ntpPacket.transmit_timestamp.coarse 	= ntohl(*(int*)&(g_ntpPacketStr.ntpPacketBuf[40]));
		g_ntpPacketStr.ntpPacket.transmit_timestamp.fine 	= ntohl(*(int*)&(g_ntpPacketStr.ntpPacketBuf[44]));

		j_debug("free address info.");
		freeaddrinfo(res);

		/*�ر��׽���*/
		net_close_socket(&sockfd);
		
		return 1;
	} /* end of if select */

_OUT:
	freeaddrinfo(res);
	/*�ر��׽���*/
	net_close_socket(&sockfd);
	
	return 0;
}

/* 
   ���ܣ��޸ı���ʱ��
   nvr_ntp_server: NTP������
   port			 : �˿�
   timeZone		 : ʱ��
   enableEuro    : ����ʱ����
   ����ֵ��1��ɹ�,0ʧ��
   */
static int nvr_ntp_set_local_time(char *nvr_ntp_server, unsigned int port, int timeZone, int enableEuro)
{
	struct timeval tv;
	time_t tmit = -1; 
	int i = 0;

	j_debug("update local time from %s ...", nvr_ntp_server);
	
	/*��ȡNTPʱ���*/
#ifdef AUTO
	if(!nvr_ntp_get_time(NVR_NTP_SERVER_IP, port))
#else
	if(!nvr_ntp_get_time(nvr_ntp_server, port))
#endif
	{
		const char *pNtpServer;
		for(i = 0; i < sizeof(gBakNtpServer) / sizeof(gBakNtpServer[0]); i++)
		{
			pNtpServer = gBakNtpServer[i];
			if(pNtpServer == NULL)
				break;
			j_message("sync time from %s.", pNtpServer);
			if(nvr_ntp_get_time(pNtpServer, NVR_NTP_PORT))
			{
				j_message("sync time form %s successfully.", pNtpServer);
				break;
			}
		}
		if(pNtpServer == NULL)
		{
			j_warning("get ntp packet failed");
			return -1;
		}
	}
	/*���±���ʱ��*/
	tv.tv_sec  = g_ntpPacketStr.ntpPacket.transmit_timestamp.coarse - NVR_NTP_JAN_1970;
	tv.tv_usec = NVR_NTPUSEC(g_ntpPacketStr.ntpPacket.transmit_timestamp.fine);
	tmit = tv.tv_sec;
	/* use unix library function to show me the local time (it takes care
	* of timezone issues for both north and south of the equator and places
	* that do Summer time/ Daylight savings time.
	*/  
	/*
	* add European Summer Time adjust if option -E is enabled
	* WARNING: we must do this check before set offset !
	***************************************************************************
	*/
	if(enableEuro) 
	{
		time_t begin, end;
		struct tm tmTime;
		struct tm *ltime = localtime_r( &tmit, &tmTime); 
		if(EuropeanSummerTime(ltime->tm_year + 1900, &begin, &end)) 
		{
		  ;
		}
		else 
		{ 
			if( tmit >= begin && tmit < end) 
			{
				tmit += 3600;
			}
		}
	}
	/*  
	* add offset before set time of day
	***************************************************************************
	*/
	tmit += (int)timeZone;
	/*
	* calculate new time and delta
	***************************************************************************
	*/
	i = time(0);	
	/*
	* set time of day if it's necessary
	***************************************************************************
	*/
	//if( 0 != i - tmit) 
		tv.tv_sec  = tmit;
/*	
	if (settimeofday(&tv, NULL) == 0)
	{
		system("hwclock -w");		
		return 1;
	}
*/	
	NVR_TIME_S stTimeCfg;
	struct tm tmTime, *ptm;
	ptm = localtime_r(&tv.tv_sec, &tmTime);
	nvr_timer_tm_2_nvr(ptm, &stTimeCfg);
	if(0 > nvr_set_time_cfg(0, &stTimeCfg))
	{
		j_warning("ntp set time cfg failed.");
		return -1;
	}
	
	return 0;
}

/*����ʱ��*/
static int nvr_ntp_time_update(void)
{
	NVR_NTP_CFG_S ntpCfg;
	
	/*��ȡNTP ����*/
	nvr_get_ntp_cfg(NVR_NTP_PORT, &ntpCfg);
	
	//���±���ʱ��
	j_debug("ntpCfg.szNtpServer : %s", ntpCfg.szNtpServer);
	j_debug("ntpCfg.nTimeZone : %d", ntpCfg.nTimeZone);
	j_debug("ntpCfg.u8EuroTime: %d", ntpCfg.u8EuroTime);

	if(ntpCfg.u8NtpOpen)
	{
		if (nvr_ntp_set_local_time(ntpCfg.szNtpServer, ntpCfg.u16NtpPort,
							   ntpCfg.nTimeZone, ntpCfg.u8EuroTime) == 0)
		{
			j_debug("NTP client success!");
			return 0;
		}
		else
		{
			j_warning("NTP client failed!");
			return -1;
		}
	}
	return -1;
}


//ntp�̴߳�����
static void nvr_ntp_server_func (gpointer data, gpointer user_data)
{
	time_t cur_time;
	static time_t last_time = 0;
	NVR_NTP_CTRL_CMD_E val = GPOINTER_TO_INT(data);

	j_debug("val: %x", val);
	switch(val)
	{
		case NVR_NTP_START_UPDATE:
			cur_time = time(NULL);
			if(cur_time - last_time >= 0 && cur_time - last_time <= 60)
				break;
			if(nvr_ntp_time_update() < 0)
				break;
			last_time = cur_time;			
			break;
		default:
			g_assert_not_reached();
			break;
	}
}

//ntp�߳̿���
static int nvr_ntp_send_cmd(NVR_NTP_CTRL_CMD_E cmdVal)
{
	g_thread_pool_push(gNtpServerMng.pool, GINT_TO_POINTER(cmdVal), NULL);
	return 0;
}

/*��ʱ����ʱ�����*/
static gboolean nvr_ntp_update_timeout(gpointer user_data)
{
	nvr_ntp_send_cmd(NVR_NTP_START_UPDATE);
	return G_SOURCE_CONTINUE;
}

//����ʱ��ʱ��
void nvr_ntp_update()
{
	NVR_NTP_CFG_S ntpCfg;

	//��ò�����Ϣ
	nvr_get_ntp_cfg(0, &ntpCfg);
	
	//ʹ���ж�
	if(ntpCfg.u8NtpOpen)
	{
		//��ʱ���´���
		if(0 < (ntpCfg.u8NtpRefTime * 3600))
		{
			if(gNtpServerMng.timeId == 0)
				gNtpServerMng.timeId = 
					g_timeout_add_seconds((ntpCfg.u8NtpRefTime * 3600), 
								nvr_ntp_update_timeout, NULL);
		}
		else
		{
			if(0 < gNtpServerMng.timeId)
			{
				g_source_remove(gNtpServerMng.timeId);
				gNtpServerMng.timeId = 0;
			}
		}
		//ʱ�����
		nvr_ntp_send_cmd(NVR_NTP_START_UPDATE);
	}
	else
	{
		if(0 < gNtpServerMng.timeId)
		{
			g_source_remove(gNtpServerMng.timeId);
			gNtpServerMng.timeId = 0;
		}
	}
}

//��ʼ������
int nvr_ntp_init(void)
{
	memset(&gNtpServerMng, 0, sizeof(gNtpServerMng));	
	gNtpServerMng.pool = g_thread_pool_new(nvr_ntp_server_func, NULL, 1, FALSE, NULL);
	if(gNtpServerMng.pool == NULL)
	{
		j_warning("New thread pool for ntp failed.");
		return -1;
	}
	//NTP ����
	nvr_ntp_update();

	return 0;
}

void nvr_ntp_uninit(void)
{
	j_warning("ntp uninit.");
	g_thread_pool_free(gNtpServerMng.pool, TRUE, FALSE);
	
	j_warning("ntp uninit finish.");
}

