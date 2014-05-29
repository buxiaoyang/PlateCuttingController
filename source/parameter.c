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

unsigned int settingBoardLength; //�趨����
unsigned int settingBoardNumber; //�趨����

unsigned int currentlyBoardLength; //��������
unsigned int currentlyBoardNumber; //��������

unsigned long currentlySignalNum; //��ǰ�������ź���
unsigned long maxSignalNum;	  //���������ź���

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
	runMode = 0;

	sysParm1_SignalNumPerMeter =  1000;
	sysParm2_ErrorCorrectionValue = 100;
	sysParm3 = 0;
	sysParm4 = 0;
	sysParm5 = 0;
	parameterBoard[0].boardLength = 0;
	parameterBoard[0].boardNumber = 0;
	parameterBoard[1].boardLength = 0;
	parameterBoard[1].boardNumber = 0;
	parameterBoard[2].boardLength = 0;
	parameterBoard[2].boardNumber = 0;
	parameterBoard[3].boardLength = 0;
	parameterBoard[3].boardNumber = 0;
	settingBoardLength = 0;
	settingBoardNumber = 0;
	currentlyBoardLength = 0;
	currentlyBoardNumber = 0;
	currentlySignalNum = 0;
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


