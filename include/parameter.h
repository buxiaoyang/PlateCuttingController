/***************************************************************************/
// ������ϴ�豸������
// ģ�飺����ͷ�ļ�
// �ļ���parameter.h
// ���ߣ������D
// �汾��V0.02
// ���ڣ�2013��11��8��
// ���ܣ�����ͷ�ļ�
// оƬ��STC12C5A60S2
// ���룺Keil uVision3 V3.90
/***************************************************************************/

#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#include <reg52.h>

/***************************************************************************/
// ���Ŷ���
/***************************************************************************/
//����
sbit EncoderCounting		= P3^2;  	// ��������������ɫ��
sbit EncoderDirection		= P2^0;  	// ���������򣨰�ɫ��
sbit HydClamInductorTop		= P0^0;  	// Һѹ�����Ϸ���Ӧ��(ϵͳ�ڹ���֮ǰ������Һѹ�����Ƿ����ϵ�λ�ã�������
										// ���ж��Ƿ������������)
sbit HydClamInductorBottom	= P0^1;  	// Һѹ�����·���Ӧ��
sbit KeyStart				= P0^2;  	// ������ť
sbit KeyStop				= P0^4;  	// ֹͣ��ť
sbit KeyHydClam				= P0^5;  	// Һѹ������ť��Һѹ�����ر��Զ�ģʽ����Ҫ�˰�ť��������


//���
sbit MotorForwardFast  		= P1^6;  //	���ǰ������
sbit MotorForwardSlow  		= P1^5;  //	���ǰ������
sbit MotorBackFast  		= P1^4;  // ������˿���
sbit MotorBackSlow  		= P1^7;  //	�����������

sbit HydClamDown  			= P1^0;  //	Һѹ�������(����)
sbit HydClamUp  			= P1^1;  //	Һѹ�����رգ����ϣ�
sbit HydMonitorOut  		= P2^4;  //	Һѹ������
sbit SystemAlarm	  		= P2^5;  //	ϵͳ����ָʾ��


sbit TestOut		  		= P2^7;  //	�������


/***************************************************************************/
// ��������
/***************************************************************************/
struct Board  //��Ľṹ��
{
	unsigned int boardLength;   //��ĳ���
	unsigned int boardDecLength;   //��ĵݼ�����
	unsigned int boardNumber;	//�������
};


/***************************************************************************/
// ��������
/***************************************************************************/
void parameter_init();
unsigned char parameter_save();

extern unsigned int powerMode; //����״̬ 0�ر� 1���� 2���� 
extern unsigned int HydClamStatus; //Һѹ����״̬ 0���ر�  1����
extern unsigned int HydMonitorStatus; //Һѹ���״̬ 0���ر�  1����
extern struct Board parameterBoard[4];	//��Ĳ���

extern unsigned int sysParm1_SignalNumPerMeter; //ϵͳ����һ��һ�׾�����������ź���
extern unsigned int sysParm2_ErrorCorrectionValue; //ϵͳ���������������ֵ���ź���
extern unsigned int sysParm3; //ϵͳ������
extern unsigned int sysParm4; //ϵͳ������
extern unsigned int sysParm5; //ϵͳ������

extern unsigned int settingBoardLength; //�趨����
extern unsigned int settingBoardNumber; //�趨����

extern unsigned int currentlyBoardLength; //��������
extern unsigned int currentlyBoardNumber; //��������

extern unsigned int errorCorrectionBoardLength; //�����İ�������

extern unsigned long currentlySignalNum; //��ǰ�������ź���
extern unsigned long maxSignalNum;	  //���������ź���

#endif
