/***************************************************************************/
// ������ϴ�豸������
// ģ�飺����
// �ļ���parameter.c
// ���ߣ������D
// �汾��V0.02
// ���ڣ�2013��11��8��
// ���ܣ�����
// оƬ��STC12C5A60S2
// ���룺Keil uVision3 V3.90
/***************************************************************************/

#include <parameter.h>
#include <eeprom.h>

/***************************************************************************/
// ��������	
/***************************************************************************/
unsigned int powerMode; //����״̬ 0�ر� 1����
unsigned int runMode; //����ģʽ 0�ֶ�ģʽ 1�Զ�ģʽ
struct Board parameterBoard[4];	//��Ĳ���

unsigned int sysParm1_SignalNumPerMeter; //ϵͳ����һ��һ�׾�����������ź���
unsigned int sysParm2_ErrorCorrectionValue; //ϵͳ���������������ֵ���ź���
unsigned int sysParm3; //ϵͳ������
unsigned int sysParm4; //ϵͳ������
unsigned int sysParm5; //ϵͳ������
unsigned int sysParm6; //ϵͳ������

unsigned int settingBoardLength; //�趨����
unsigned int settingBoardNumber; //�趨����

unsigned int currentlyBoardLength; //��������
unsigned int currentlyBoardNumber; //��������

unsigned long currentlySignalNum; //��ǰ�������ź���

/***************************************************************************/
// ��ȡ����
// ��������
// ����ֵ��0ʧ�� 1�ɹ�	
/***************************************************************************/
unsigned char parameter_read()
{
	unsigned char result = 1;
	return result;
}

/***************************************************************************/
// ������ʼ������
// ��������
// ����ֵ����	
/***************************************************************************/
void parameter_init()
{
	powerMode = 0;	//����״̬ 0�ر� 1����
	
}

/***************************************************************************/
// �������浽eeprom
// ��������
// ����ֵ��0ʧ�� 1�ɹ�	
/***************************************************************************/
unsigned char parameter_save()
{
	unsigned char result = 1;
	return result;
}


