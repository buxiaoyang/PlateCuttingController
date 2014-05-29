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

sbit EncoderDirection		= P2^4;  	// ���������򣨰�ɫ��

sbit HydClamInductorTop		= P0^0;  	// Һѹ�����Ϸ���Ӧ��(ϵͳ�ڹ���֮ǰ������Һѹ�����Ƿ����ϵ�λ�ã�������
										// ���ж��Ƿ��������������)

sbit HydClamInductorBottom	= P0^1;  	// Һѹ�����·���Ӧ��

sbit KeyStart				= P0^2;  	// ������ť��������ťֻ�����Զ�״̬�²���Ч������֮�󣬵����ʼ�����
										// ��Ƭ����ʼ���ձ������źš�

sbit KeyAutoManual			= P0^3;  	// �ֶ�״̬�£�������ť��ϵͳֹͣ��ť��Ч�������������ź���Ч��
										// �Զ�״̬�� ��Һѹ������ť��Ч�����ߵ�ƽ�Զ����͵�ƽ�ֶ���

sbit KeyStop				= P0^4;  	// ֹͣ��ť

sbit KeyHydClam				= P0^5;  	// Һѹ������ť��ֻ�����ֶ�״̬�²���Ч��

//���
sbit MotorForwardFast  		= P1^5;  //	���ǰ������
sbit MotorBackFast  		= P1^6;  // ������˿���
sbit MotorForwardSlow  		= P1^0;  //	���ǰ������
sbit MotorBackSlow  		= P1^1;  //	�����������
sbit HydClamOut  			= P1^4;  //	Һѹ�������
sbit TestOut		  		= P2^7;  //	�������


/***************************************************************************/
// ��������
/***************************************************************************/
struct Board  //��Ľṹ��
{
	unsigned int boardLength;   //��ĳ���
	unsigned int boardNumber;	//�������
};


/***************************************************************************/
// ��������
/***************************************************************************/
void parameter_init();
unsigned char parameter_save();

extern unsigned int powerMode; //����
extern unsigned int runMode; //����ģʽ
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

extern unsigned long currentlySignalNum; //��ǰ�������ź���
extern unsigned long maxSignalNum;	  //���������ź���

#endif
