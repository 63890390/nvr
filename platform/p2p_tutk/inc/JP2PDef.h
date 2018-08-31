#ifndef __JP2P_DEF_H__
#define	__JP2P_DEF_H__

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#ifdef	JP2P_EXPORT
	#define JP2P_TUTK_API		extern "C" 
#else
	#define JP2P_TUTK_API
#endif
#define JP2P_PRO_VERSION	0x0100			// Э��汾��
#define JP2P_MAGIC_FLAG0	0x4a503250		// ħ����
#define JP2P_MAGIC_FLAG1	0x5032504a		// ħ��β
#define	JP2P_MAX_CHN		64				// ���64ͨ��
#define	JP2P_MAX_CODE		3				// ���������
#define	JP2P_MAX_CLIENT		4				// ����ĸ��ͻ��˽���
#define	JP2P_MAX_REQ		12				// ����������(ƽ��һ���ͻ��˶�Ӧ3·����)
#define	JP2P_BREATH_SPAN	10				// �������
#define JP2P_USER_NAME_LEN	16				// �û����Ƴ�
#define JP2P_USER_PWD_LEN	16				// �û����볤
#define	JP2P_HOST_COUNT		4				// P2P����������
#define	JP2P_HOST_NAME		64				// P2P������IP��ַ

#if (defined _WIN32) || (defined _WIN64)
#else
	typedef	int64_t			__int64;
#endif
//typedef byte				jdt_bool;
typedef char				jdt_char;
typedef char*				jdt_lpchar;
typedef const char			jdt_cchar;
typedef const char*			jdt_lpcchar;
typedef unsigned char		jdt_byte;
typedef unsigned char*		jdt_lpbyte;
typedef short				jdt_short;
typedef short*				jdt_lpshort;
typedef int					jdt_int;
typedef int*				jdt_lpint;
typedef unsigned int		jdt_uint;
typedef unsigned int*		jdt_lpuint;
typedef long				jdt_long;
typedef long*				jdt_lplong;
typedef unsigned short		jdt_word;
typedef unsigned short*		jdt_lpword;
typedef unsigned long		jdt_dword;
typedef unsigned long*		jdt_lpdword;
typedef __int64				jdt_l64;
typedef __int64*			jdt_lpl64;
typedef void*				jdt_lpvoid;

// ������������ begin
typedef enum
{
	eJP2PCmdUnknown			= 0,			// δ֪����
	eJP2PCmdBreath			= 1,			// ����,			stJP2PBreath
	eJP2PCmdLogout			= 2,			// �ǳ�����,		stJP2PLogout
	eJP2PCmdLogin			= 3,			// ��¼����,		stJP2PLogin
	eJP2PCmdGetParam		= 4,			// ��ȡ��������,	stJP2PGetParam
	eJP2PCmdSetParam		= 5,			// ���ò�������,	stJP2PSetParam
	eJP2PCmdReqStream		= 6,			// ����������,		stJP2PReqStream
	eJP2PCmdCloseStream		= 7,			// ����������,		stJP2PCloseStream
	eJP2PCmdCtrlStream		= 8,			// ����������,		stJP2PCtrlStream
	eJP2PCmdReqTalk			= 9,			// ����Խ�����,	stJP2PReqTalk
	eJP2PCmdCloseTalk		= 10,			// �����Խ�����,	stJP2PCloseTalk
	eJP2PCmdDevNotify		= 11,			// �豸֪ͨ����,	stJP2PDevNotify
	eJP2PCmdStreamData		= 100,			// ������Ϣ,		stJP2PStreamData
	eJP2PCmdStreamEnd		= 101,			// ������Ϣ��������,stJP2PStreamEnd
}eJP2PCmd;
// ������������ end

// ����ֵ���Ͷ��� begin
typedef enum
{
	eJP2PETSuccess			= 0,			// ���سɹ�
	eJP2PETOperator			= -1,			// ����ʧ��
	eJP2PETParam			= -2,			// ��������
	eJP2PETInit				= -3,			// δ��ʼ��
	eJP2PETNoMem			= -4,			// �ڴ治��
	eJP2PETDeal				= -5,			// ���ڴ�����
	eJP2PETMaxClient		= -6,			// �ͻ����Ѿ���
	eJP2PETUserNotExist		= -1000,		// �û�������
	eJP2PETUserPsw			= -1001,		// �û��������
	eJP2PETRight			= -1003,		// �û�Ȩ�޲��� 
}eJP2PErrType;
// ����ֵ���Ͷ��� end

// �����Ͷ��� begin
typedef enum
{
	eJP2PStreamUnknown		= 0,			// δ֪����
	eJP2PStreamReal			= 1,			// ʵʱ��
	eJP2PStreamHistore		= 2,			// ��ʷ��
	eJP2PStreamTalk			= 3,			// �Խ���
}eJP2PStreamType;
// �����Ͷ��� end

// ���岥���ٶ� begin
typedef enum
{
	eJP2PPlaySpeed_1_16X	= 0x1,			// ��16����
	eJP2PPlaySpeed_1_8X		= 0x2,			// ��8����
	eJP2PPlaySpeed_1_4X		= 0x3,			// ��4����
	eJP2PPlaySpeed_1_2X		= 0x4,			// ��2����
	eJP2PPlaySpeed_1X		= 0x5,			// �����ٶ�
	eJP2PPlaySpeed_2X		= 0x6,			// ��2����
	eJP2PPlaySpeed_4X		= 0x7,			// ��4����
	eJP2PPlaySpeed_8X		= 0x8,			// ��8����
	eJP2PPlaySpeed_16X		= 0x9,			// ��16����
	eJP2PPlaySpeed_32X		= 0x10,			// ��32����
	eJP2PPlaySpeed_0_1X		= 0x20,			// ��2������
	eJP2PPlaySpeed_0_2X		= 0x21,			// ��2������
	eJP2PPlaySpeed_0_4X		= 0x22,			// ��4������
	eJP2PPlaySpeed_0_8X		= 0x23,			// ��8������
	eJP2PPlaySpeed_0_16X	= 0x24,			// ��16������
	eJP2PPlaySpeed_0_32X	= 0x25,			// ��32������
}eJP2PPlaySpeed;
// ���岥���ٶ� end

// �����ƶ��� begin
typedef enum
{
	eJP2PSCUnknwn			= 0,			// δ֪����
	eJP2PSCAudioOnly		= 1,			// ֻ����Ƶ
	eJP2PSCIFrameOnly		= 2,			// ֻ��I֡
	
	eJP2PSCPBStart			= 100,			// ��ʼ�ط�
	eJP2PSCPBStop			= 101,			// ֹͣ�ط�
	eJP2PSCPBPause			= 102,			// ��ͣ�ط�
	eJP2PSCPBResume			= 103,			// �ָ��ط�
	eJP2PSCPBSetSpeed		= 104,			// ���ò����ٶ�,m_dwCtrlValue1����Ϊ�ٶ�ֵ�� eJP2PPlaySpeed
	eJP2PSCPBGetSpeed		= 105,			// ��ȡ�����ٶ�,m_dwCtrlValue1����Ϊ�ٶ�ֵ�� eJP2PPlaySpeed
	eJP2PSCPBFrame			= 106,			// ��֡��
	eJP2PSCPBSetTime		= 107,			// ���ûط�ʱ��,m_dwCtrlValue1����Ϊtime_t
	eJP2PSCPBGetTime		= 108,			// ��ȡ�ط�ʱ��,m_dwCtrlValue1����Ϊtime_t
}eJP2PStreamCtrl;
// �����ƶ��� end

// ����֡���Ͷ��� begin
typedef enum
{
	eJP2PFrameUnknown		= 0,			// δ֪����
	eJP2PFrameIFrame		= 0x1,			// I֡
	eJP2PFramePFrame		= 0x2,			// P֡
	eJP2PFrameBFrame		= 0x3,			// B֡
	eJP2PFrameAudio			= 0x4,			// ��Ƶ֡
	eJP2PFrameString		= 0x5,			// ��Ļ֡
	eJP2PFrameShape			= 0x6,			// ��״֡
	eJP2PFrameUser			= 0xF,			// �û��Զ���֡
}eJP2PFrameType;
// ����֡���Ͷ��� end

// �������Ͷ��� begin
typedef enum 
{ 
	eJP2PCodecH264			= 0,			// H264
	eJP2PCodecMJPEG			= 1,			// MJPEG
}eJP2PCodecVideo;
typedef enum 
{ 
	eJP2PCodecPCM			= 0,			// PCM
	eJP2PCodecG711A			= 1,			// G711A
	eJP2PCodecG711U			= 2,			// G711U
	eJP2PCodecG726			= 3,			// G726
}eJP2PCodecAudio;
// �������Ͷ��� end


// ʱ��ṹ�� begin
typedef enum
{
	eJP2PSunday				= 0,			// ����
	eJP2PMonday				= 1,			// ��һ
	eJP2PTuesday			= 2,			// �ܶ�
	eJP2PWednesday			= 3,			// ����
	eJP2PHursday			= 4,			// ����
	eJP2PFriday				= 5,			// ����
	eJP2PSaturday			= 6,			// ����
	eJP2PEveryday			= 7,			// ÿ��
}eJP2PWeekDay;
typedef struct stJP2PTime
{
	jdt_short	m_sYear;			// ��,��2014
	jdt_short	m_sMonth;			// ��,��0��ʼ,��0~11
	jdt_short	m_sDay;				// ��,��0��ʼ
	jdt_short	m_sHour;			// ʱ,24Сʱ��,��0~23
	jdt_short	m_sMinute;			// ��,0~59
	jdt_short	m_sSecond;			// ��,0~59
	jdt_short	m_sWeek;			// ����,�� eJP2PWeekDay
}* PSTJP2PTime;
// ʱ��ṹ�� end

// Э��ͷ begin
typedef struct stJP2PProHead
{
	jdt_dword	m_dwMagicFlag0;		// ��ħ����
	jdt_word	m_wVersion;			// �汾��
	jdt_short	m_sCmdType;			// ��������,�� eJP2PCmd
	jdt_int		m_iDataSize;		// �����ݴ�С
	jdt_long	m_lSeq;				// ���к�
	jdt_long	m_lErrNo;			// ������,�� eJP2PErr
	jdt_dword	m_dwSession;		// �Ự
	jdt_dword	m_dwSubSession;		// �ӻỰ
	jdt_dword	m_dwRes[4];			// ����λ
	jdt_dword	m_dwMagicFlag1;		// βħ����
	#ifdef __cplusplus
	void Reset()
	{
		m_dwMagicFlag0	= JP2P_MAGIC_FLAG0;
		m_wVersion		= JP2P_PRO_VERSION;
		m_sCmdType		= (jdt_short)0;
		m_iDataSize		= 0;
		m_lSeq			= 0;
		m_lErrNo		= 0;
		m_dwSession		= 0;		// �Ự
		m_dwSubSession	= 0;		// �ӻỰ
		memset(m_dwRes,0,sizeof(jdt_dword)*4);
		m_dwMagicFlag1	= JP2P_MAGIC_FLAG1;
	}
	stJP2PProHead()
	{
		Reset();
	}
	jdt_int CheckPacket()
	{
		if (m_dwMagicFlag0==JP2P_MAGIC_FLAG0 && m_dwMagicFlag1==JP2P_MAGIC_FLAG1) return 1;
		else return 0;
	}
	jdt_int SetNetHdr(jdt_dword dwSession,jdt_dword dwSubSession,jdt_int iDataSize, jdt_short sCmdType, jdt_long lErrNo)
	{
		Reset();
		m_dwSession		= dwSession;
		m_dwSubSession	= dwSubSession;
		m_iDataSize		= iDataSize;
		m_sCmdType		= sCmdType;
		m_lErrNo		= lErrNo;
		m_lSeq			= GetSeq();
		return m_lSeq;
	}
	static jdt_long GetSeq()
	{
		jdt_long	lSeq	= s_lSeq;
		s_lSeq++;
		if (s_lSeq>100000) s_lSeq	= 1;
		return lSeq;
	}
	static jdt_int		s_iSize;
	static jdt_long		s_lSeq;
	#endif	// __cplusplus
}* PSTJP2PProHead;
// Э��ͷ end

// ��¼���� begin
// eJP2PCmdLogin
typedef struct stJP2PLogin
{
	jdt_char	m_szUserName[JP2P_USER_NAME_LEN];	// �û���
	jdt_char	m_szUserPwd[JP2P_USER_PWD_LEN];		// ����
	jdt_int		m_iBreath;							// ����ʱ��
}* PSTJP2PLogin;
// ��¼���� end

// �ǳ����� begin
// eJP2PCmdLogout
typedef struct stJP2PLogout
{
	jdt_dword	m_dwRes;							// ����ֵ
}* PSTJP2PLogout;
// �ǳ����� end

// ���� begin
// eJP2PCmdLogout
typedef struct stJP2PBreath
{
	jdt_dword	m_dwSendTick;						// ����ʱ��Tick
	jdt_dword	m_dwRecvTick;						// ����ʱ��Tick
}* PSTJP2PBreath;
// ���� end

// ��ȡ�������� begin
// eJP2PCmdGetParam
typedef struct stJP2PGetParam
{
	jdt_int		m_iParamID;							// ����ID
	jdt_int		m_iChn;								// ͨ����
	jdt_int		m_iDataSize;						// ���ݴ�С
}* PSTJP2PGetParam;
// ��ȡ�������� end

// ���ò������� begin
// eJP2PCmdSetParam
typedef struct stJP2PSetParam
{
	jdt_int		m_iParamID;							// ����ID
	jdt_int		m_iChn;								// ͨ����
	jdt_int		m_iDataSize;						// ���ݴ�С
}* PSTJP2PSetParam;
// ���ò������� end

// ���������� begin
//eJP2PCmdReqStream
typedef struct stJP2PReqStream
{
	jdt_int		m_iChn;								// ͨ����
	jdt_int		m_iCode;							// ����,0 ������,1 ������,2 ������...
	jdt_int		m_iStreamType;						// ������,�� eJP2PStreamType
	struct stJP2PTime	m_stStartTime;						// ��ʷ���Ŀ�ʼʱ��,ʵʱ��ʱ����
	struct stJP2PTime	m_stStopTime;						// ��ʷ���Ľ���ʱ��,ʵʱ��ʱ����
	jdt_dword	m_dwRecType;						// ��ʷ��������,��Э���Զ���,ʵʱ��ʱ����
	jdt_dword	m_dwSession;						// �ỰSESSION,�ɷ���������
}* PSTJP2PReqStream;
// ���������� end

// ���������� begin
// eJP2PCmdCloseStream
typedef struct stJP2PCloseStream
{
	jdt_dword	m_dwSession;						// �ỰSESSION,�ɷ���������
}* PSTJP2PCloseStream;
// ���������� end

// ���������� begin
// eJP2PCmdCtrlStream
typedef struct stJP2PCtrlStream
{
	jdt_dword	m_dwSession;						// �ỰSESSION,����������У��
	jdt_int		m_iCtrlCode;						// ������,�� eJP2PStreamCtrl
	jdt_dword	m_dwCtrlValue1;						// ����ֵ1
	jdt_dword	m_dwCtrlValue2;						// ����ֵ2
	jdt_dword	m_dwCtrlValue3;						// ����ֵ3
	jdt_dword	m_dwCtrlValue4;						// ����ֵ4
}* PSTJP2PCtrlStream;
// ���������� end

// ����Խ����� begin
// eJP2PCmdReqTalk
typedef struct stJP2PReqTalk
{
	jdt_int		m_iSamples;							// ������	: 0--8k 1--16k 2-32k
	jdt_int		m_iEncodeType;						// ��������	: 0--pcm 1-g711a 2-g711u 3--g726
	jdt_int		m_iChannels;						// ͨ����	: 1
	jdt_int		m_iBits;							// λ��		: 16bit
	jdt_dword	m_dwSession;						// �ỰSESSION,�ɷ���������
}* PSTJP2PReqTalk;
// ����Խ����� end

// �����Խ����� begin
// eJP2PCmdCloseTalk
typedef struct stJP2PCloseTalk
{
	jdt_dword	m_dwSession;						// �ỰSESSION,�ɷ���������
}* PSTJP2PCloseTalk;
// �����Խ����� end

// �豸֪ͨ���� begin
// eJP2PCmdDevNotify
typedef struct stJP2PDevNotify
{
	jdt_int		m_iParamID;							// ����ID
	jdt_int		m_iChn;								// ͨ����
	jdt_int		m_iDataSize;						// ���ݴ�С
}* PSTJP2PDevNotify;
// �豸֪ͨ���� end

// ������Ϣ���� begin
// eJP2PCmdStreamData
// ����֡���ݵ���Ϣ begin
// ��Ƶ����
typedef struct stJP2PVideoInfo
{
	jdt_word		m_wImageWidth;		// ͼ����
	jdt_word		m_wImageHeight;		// ͼ��߶�
	jdt_byte		m_byEncodeType;		// ��Ƶ�����ʽ,�� eJP2PCodecVideo
	jdt_byte		m_byFrameRate;		// ֡��(����)
	jdt_byte		m_byPal;			// ��ʽ 0-n��1-pal��
	jdt_byte		m_byRes[1];	
}* PSTJP2PVideoInfo;
// ��Ƶ����
typedef struct stJP2PAudioInfo
{
	jdt_byte		m_byAudioSamples;	// ������		0--8k 1--16k 2-32k
	jdt_byte		m_byEncodeType;		// ��Ƶ�����ʽ,�� eJP2PCodecAudio
	jdt_byte		m_byAudioChannels;	// ͨ����		��ֻ֧��1	
	jdt_byte		m_byAudioBits;		// λ��			16bit
	jdt_byte		m_byRes[4];
}* PSTJP2PAudioInfo;
typedef struct stJP2PStreamData
{
	jdt_word		m_wFrameFlag;		// 0x3448 magic data
	jdt_byte		m_byFrameType;		// I-0x7 p--0x8 b--0xb A--0xa
	jdt_byte		m_byRes[1];			// ����
	jdt_dword		m_dwFrameNo;		// ֡��
	jdt_dword		m_dwTime;			// ϵͳʱ��
	jdt_dword		m_dwFrameSize;		// ����������
	jdt_l64			m_dwTimeStamp;		// ʱ���
	union
	{
		struct stJP2PVideoInfo	m_stVideo;
		struct stJP2PAudioInfo	m_stAudio;
	};
}* PSTJP2PStreamData;
typedef struct stJP2PStreamEnd
{
	jdt_dword	m_dwSession;			// �ỰSESSION,�ɷ���������,�������ʾ�ɷ����������Ͽ�����
}* PSTJP2PStreamEnd;
// ����֡���ݵ���Ϣ end
// ������Ϣ���� end







// �ӿڶ��� begin
#ifdef __cplusplus
extern "C" {
#endif
typedef jdt_int fcbJP2PLogTrace(jdt_lpchar lpszLog);																		// ��־�ص�
typedef jdt_int fcbJP2PLoginAuth(jdt_long lHandle, jdt_lpchar lpszName,jdt_lpchar lpszPwd);									// ��¼��֤�ص�
typedef jdt_int fcbJP2PGetParam(jdt_long lHandle, jdt_int iChn, jdt_int iParamID, jdt_lpvoid lpData, jdt_int iDataSize);	// ��ȡ�豸�����ص�
typedef jdt_int fcbJP2PSetParam(jdt_long lHandle, jdt_int iChn, jdt_int iParamID, jdt_lpvoid lpData, jdt_int iDataSize);	// �����豸�����ص�
typedef jdt_int fcbJP2POpenStream(jdt_long lHandle, PSTJP2PReqStream pstReqParam);											// ��������ص�
typedef jdt_int fcbJP2PCloseStream(jdt_long lHandle);																		// ����ر����ص�
typedef jdt_int fcbJP2PCtrlStream(jdt_long lHandle,PSTJP2PCtrlStream pstCtrlStream);										// ����������ص�
typedef jdt_int fcbJP2PSendFrame(jdt_long lHandle, jdt_lpvoid lpData, jdt_int iDataSize);									// ���豸����֡���ݻص�
typedef jdt_int fcbJP2POpenTalk(jdt_long lHandle, PSTJP2PReqTalk pstReqParam);												// ����򿪶Խ��ص�
typedef jdt_int fcbJP2PCloseTalk(jdt_long lHandle);																			// ����رնԽ��ص�
#ifdef __cplusplus
}
#endif

typedef	struct stJP2PInit
{
	fcbJP2PLogTrace*		m_fcbLogTrace;					// ��־�ص�
	fcbJP2PLoginAuth*		m_fcbLoginAuth;					// ��¼��֤�ص�
	fcbJP2PGetParam*		m_fcbGetParam;					// ��ȡ�豸�����ص�
	fcbJP2PSetParam*		m_fcbSetParam;					// �����豸�����ص�
	fcbJP2POpenStream*		m_fcbOpenStream;				// ��������ص�
	fcbJP2PCloseStream*		m_fcbCloseStream;				// ����ر����ص�
	fcbJP2PCtrlStream*		m_fcbCtrlStream;				// ����������ص�
	fcbJP2PSendFrame*		m_fcbSendFrame;					// ���豸����֡���ݻص�
	fcbJP2POpenTalk*		m_fcbOpenTalk;					// ����򿪶Խ��ص�
	fcbJP2PCloseTalk*		m_fcbCloseTalk;					// ����رնԽ��ص�
	jdt_int					m_iMaxChn;						// ���ͨ����
	jdt_int					m_iMaxCode;						// ���������
	#ifdef __cplusplus
	stJP2PInit()
	{
		m_fcbLogTrace		= NULL;							// ��־�ص�
		m_fcbLoginAuth		= NULL;							// ��¼��֤�ص�
		m_fcbGetParam		= NULL;							// ��ȡ�豸�����ص�
		m_fcbSetParam		= NULL;							// �����豸�����ص�
		m_fcbOpenStream		= NULL;							// ��������ص�
		m_fcbCloseStream	= NULL;							// ��������ص�
		m_fcbCtrlStream		= NULL;							// ����������ص�
		m_fcbSendFrame		= NULL;							// ���豸����֡���ݻص�
		m_fcbOpenTalk		= NULL;							// ����򿪶Խ��ص�
		m_fcbCloseTalk		= NULL;							// ����رնԽ��ص�
		m_iMaxChn			= 0;							// ���ͨ����
		m_iMaxCode			= 0;							// ���������
	}
	#endif	// __cplusplus
}* PSTJP2PInit;
JP2P_TUTK_API jdt_int JP2P_StartSvr(PSTJP2PInit pstInit,jdt_lpcchar szUID,jdt_lpcchar szSvrAddr,jdt_int iSvrPort);
JP2P_TUTK_API jdt_int JP2P_StopSvr();
JP2P_TUTK_API jdt_int JP2P_OnSendFrame(jdt_lpvoid lpData,jdt_int iDataLen,jdt_long lHandle);
JP2P_TUTK_API jdt_int JP2P_OnSendNotify(jdt_int iParamID, jdt_lpvoid lpData,jdt_int iDataLen);
// �ӿڶ��� end

#endif	// __JP2P_DEF_H__

