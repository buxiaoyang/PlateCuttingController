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
extern unsigned int sysParm6; //ϵͳ������

extern unsigned int settingBoardLength; //�趨����
extern unsigned int settingBoardNumber; //�趨����

extern unsigned int currentlyBoardLength; //��������
extern unsigned int currentlyBoardNumber; //��������

extern unsigned long currentlySignalNum; //��ǰ�������ź���

#endif
