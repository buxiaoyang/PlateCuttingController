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
#include <basefunc.h>

/***************************************************************************/
// ��������	
/***************************************************************************/
unsigned int powerMode; //����ģʽ 0�ر� 1���� 2����

unsigned int HydClamStatus; //Һѹ����״̬ 0���ر�  1����
unsigned int HydMonitorStatus; //Һѹ���״̬ 0���ر�  1����

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

unsigned int errorCorrectionBoardLength; //�����İ�������

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
	if(IapReadByte(IAP_ADDRESS+200) == 0xEE)
	{
		sysParm1_SignalNumPerMeter = ((IapReadByte(IAP_ADDRESS+0) << 8) | IapReadByte(IAP_ADDRESS+1));
		sysParm2_ErrorCorrectionValue = ((IapReadByte(IAP_ADDRESS+2) << 8) | IapReadByte(IAP_ADDRESS+3));		
	}
	else
	{
	   	result = 0;
	}
	return result;	
}

/***************************************************************************/
// ������ʼ������
// ��������
// ����ֵ����	
/***************************************************************************/
void parameter_init()
{
	powerMode = 0;	//����״̬ 0�ر� 1���� 2����
	HydClamStatus = 0;
	HydMonitorStatus = 0;
	if(!parameter_read())
	{
		sysParm1_SignalNumPerMeter =  1000;
		sysParm2_ErrorCorrectionValue = 100;
	}
	sysParm3 = 0;
	sysParm4 = 0;
	sysParm5 = 0;
	parameterBoard[0].boardLength = 0;
	parameterBoard[0].boardDecLength = 0;
	parameterBoard[0].boardNumber = 0;
	parameterBoard[1].boardLength = 0;
	parameterBoard[1].boardDecLength = 0;
	parameterBoard[1].boardNumber = 0;
	parameterBoard[2].boardLength = 0;
	parameterBoard[2].boardDecLength = 0;
	parameterBoard[2].boardNumber = 0;
	parameterBoard[3].boardLength = 0;
	parameterBoard[3].boardDecLength = 0;
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
    delay_ms(10);                      //Delay
	IapEraseSector(IAP_ADDRESS); //����EEPROM
   	IapProgramByte(IAP_ADDRESS+0, (BYTE)(sysParm1_SignalNumPerMeter>>8));
	IapProgramByte(IAP_ADDRESS+1, (BYTE)sysParm1_SignalNumPerMeter);
	IapProgramByte(IAP_ADDRESS+2, (BYTE)(sysParm2_ErrorCorrectionValue>>8));
	IapProgramByte(IAP_ADDRESS+3, (BYTE)sysParm2_ErrorCorrectionValue);
	/*
	IapProgramByte(IAP_ADDRESS+4, (BYTE)(motorStepAngle>>8));
	IapProgramByte(IAP_ADDRESS+5, (BYTE)motorStepAngle);
	IapProgramByte(IAP_ADDRESS+6, (BYTE)(screwPitch>>8));
	IapProgramByte(IAP_ADDRESS+7, (BYTE)screwPitch);
	IapProgramByte(IAP_ADDRESS+8, (BYTE)(motorReducGearRatio>>8));
	IapProgramByte(IAP_ADDRESS+9, (BYTE)motorReducGearRatio);
	IapProgramByte(IAP_ADDRESS+10, (BYTE)(ballScrew>>8));
	IapProgramByte(IAP_ADDRESS+11, (BYTE)ballScrew);
	IapProgramByte(IAP_ADDRESS+12, (BYTE)(motorRotationAngle>>8));
	IapProgramByte(IAP_ADDRESS+13, (BYTE)motorRotationAngle);
	
	//refreshDisplay = 0;
	*/
	IapProgramByte(IAP_ADDRESS+200, 0xEE); //д���־λ
	return result;
}


