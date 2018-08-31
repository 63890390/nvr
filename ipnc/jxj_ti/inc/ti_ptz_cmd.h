#ifndef _TI_PTZ_CMD_H_
#define _TI_PTZ_CMD_H_

#if 0
typedef enum _TI_PTZ_CMD_E_
{
	PTZ_CMD_UP			=	0,	//��
	PTZ_CMD_SENSE		=	1,	//

	PTZ_CMD_DOWN		=	2,	//��
	PTZ_CMD_LEFT		=	3,	//��
	PTZ_CMD_RIGHT		=	4,	//��
	PTZ_CMD_LEFT_UP		=	5,	//����
	PTZ_CMD_LEFT_DOWN	=	6,	//����
	PTZ_CMD_RIGHT_UP	=	7,	//����
	PTZ_CMD_RIGHT_DOWN	=	8,	//����
	PTZ_CMD_AUTOSCAN	=	9,	//�Զ�ɨ��
	PTZ_CMD_MANUALSCAN	=	10,	//�ֶ�ɨ��
	PTZ_CMD_FOCUS_NEAR	=	11, //�۽�+
	PTZ_CMD_FOCUS_FAR	=	12, //�۽�-
	PTZ_CMD_IRIS_CLOSE	=	13, //��Ȧ+
	PTZ_CMD_IRIS_OPEN	=	14,	//��Ȧ-
	PTZ_CMD_ZOOM_WIDE	=	15,	//�䱶+
	PTZ_CMD_ZOOM_TELE	=	16, //�䱶-
	PTZ_CMD_STOP		=	17,	//ֹͣ

	PTZ_CMD_SET_PRESET	=	18, //Ԥ��λ����
	PTZ_CMD_CLR_PRESET	=	19,	//Ԥ��λ���
	PTZ_CMD_GOTO_PRESET	=	20, //Ԥ��λ����
	PTZ_CMD_FLIP		=	21, //��ת
	PTZ_CMD_GOTO_ZEROPAN=	22, //��λ����
	PTZ_CMD_SET_AUX		=	23, //���ø�������
	PTZ_CMD_CLR_AUX		=	24, //�����������
	PTZ_CMD_REMOTE_RESET=	25, //Զ�ָ̻�
	PTZ_CMD_ZONE_START	=	26, //���û���ɨ�迪ʼ
	PTZ_CMD_ZONE_END	=	27, //���û���ɨ�����
	PTZ_CMD_WR_CHAR		=	28, //д�ַ�
	PTZ_CMD_CLR_SCR		=	29, //����ַ�
	PTZ_CMD_ALM_ACK		=	30, //����ȷ��
	PTZ_CMD_ZONE_SCAN_ON=	31, //��������ɨ��
	PTZ_CMD_ZONE_SCAN_OFF=	32, //ֹͣ����ɨ��
	PTZ_CMD_PTN_START	=	33, //
	PTZ_CMD_PTN_STOP	=	34, //
	PTZ_CMD_RUN_PTN		=	35, //
	PTZ_CMD_ZOOM_SPEED	=	36, //�䱶�ٶ�
	PTZ_CMD_FOCUS_SPEED	=	37, //�۽��ٶ�
	PTZ_CMD_RESET_CAMERA=	38, //�����λ
	PTZ_CMD_AUTO_FOCUS	=	39, //�Զ��۽�
	PTZ_CMD_AUTO_IRIS	=	40,	//�Զ���Ȧ 
	PTZ_CMD_AUTO_AGC	=	41, //�Զ�����
	PTZ_CMD_BACKLIGHT_COMP=42,	//
	PTZ_CMD_AUTO_WB		  =	43,	//�Զ���ƽ��
	PTZ_CMD_DEV_PHASE_DELAY=44,	//
	PTZ_CMD_SET_SHTTER_SPEED=45,//���ÿ����ٶ�
	PTZ_CMD_ADJ_LL_PHASE_DELAY=46,
	PTZ_CMD_ADJ_WB_RB		=47,//�����Զ���ƽ�����
	PTZ_CMD_ADJ_WB_MG		=48,//�����Զ���ƽ��
	PTZ_CMD_ADJ_GAIN		=49,//�����Զ�����
	PTZ_CMD_AUTO_IRIS_LV	=50,//�����Զ���Ȧlevel
	PTZ_CMD_AUTO_IRIS_PEAK	=51,//�����Զ���Ȧpeak
	PTZ_CMD_QUERY			=52,//��ѯ
	
	PTZ_CMD_INVALID			=53,
	
/* BEGIN: Added by xq, 2011/12/13 */
	PTZ_CMD_SET_CRUISE	= 1000,		// ����Ѳ��ɨ��
	PTZ_CMD_SET_CRUISE_START,		// �Զ�Ѳ��ɨ�� 
	PTZ_CMD_SET_GUARD_POS,			// ���ÿ���λ
	PTZ_CMD_GOTO_GUARD_POS,			// ���ÿ���λ
	PTZ_CMD_SET_AUTOSCAN_SETTING,	// �����Զ�ɨ��
	PTZ_CMD_SET_AUTOSCAN_START,		// �����Զ�ɨ�� 
	PTZ_CMD_SET_ABSCAN_SETTING,		// ����AB����ɨ��
	PTZ_CMD_SET_ABSCAN_LEFT_POS,	// ����AB��������λ 
	PTZ_CMD_SET_ABSCAN_RIGHT_POS,	// ����AB��������λ
	PTZ_CMD_SET_ABSCAN_START,		// ����AB����ɨ��
	PTZ_CMD_SET_IDLE_SETTING,		// �������ö���
	PTZ_CMD_SET_ONTIME_SETTING,		// ���ö�ʱ����
	PTZ_CMD_SET_ALARM_SETTING,		// ���ñ�������ʱ�Ķ���
	PTZ_CMD_TRIG_ALARM,				// ��������
	PTZ_CMD_CLR_ALARM,
	PTZ_CMD_SET_IR_MODE,			// ����ƹ���
	PTZ_CMD_SET_DAY_NIGHT_MODE,		// ��ҹģʽ
	PTZ_CMD_SET_180_AUTO_FLIP,		// 180�Զ���ת
	PTZ_CMD_SET_IRIS_MODE,			// ��Ȧ����ģʽ
	PTZ_CMD_SET_BLC_MODE,			// ���ⲹ��
	PTZ_CMD_SET_ZOOM_DISPLAY,		// ��λ��ʾ
	PTZ_CMD_SET_FRAME_NOISE,		// ֡����
	PTZ_CMD_SET_WB_MODE,			// ��ƽ��ģʽ
	PTZ_CMD_SET_WDR_MODE,			// ��̬
	PTZ_CMD_SET_AUTO_ZOOM,			// �Զ��䱶
	PTZ_CMD_GET_ZOOM,				// ��ȡ�䱶��С
	PTZ_CMD_QUERY_STATUS,			// ��ѯ���״̬
	PTZ_CMD_GET_VERSION_ID,			// ��ȡ������汾��
	PTZ_CMD_SET_BRIGHT,				// ��������
	PTZ_CMD_SET_CONTRAST,			// ���öԱȶ�
	PTZ_CMD_SET_SATURATION,			// ���ñ��Ͷ�
	PTZ_CMD_SET_SHARPNESS,			// �������
	PTZ_CMD_SET_RED,				// ���ú�ɫ
	PTZ_CMD_SET_BLUE,				// ������ɫ
	PTZ_CMD_GET_SOFT_ID,			// ��ȡ���ID
	PTZ_CMD_GET_FEATURE_INFO,		// ��ȡ������Ϣ
	PTZ_CMD_GET_CAMERA_INFO,		// ��ȡ��о��Ϣ
	PTZ_CMD_GET_FRAME_RATE,			// ��ȡ�����ǰ֡��
	
	PTZ_CMD_SET_DEFAULT = 1100,		// �ָ�Ĭ�ϳ�������
	PTZ_CMD_INVALID_CMD = 1200,		// ��Ч����
/* END:   Added by xq, 2011/12/13 */
} TI_PTZ_CMD_E;
#endif

#endif /*  #ifndef _TI_PTZ_CMD_H_ */
