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
enum RunMode runMode;
enum DisplayMode displayMode; 
enum DrivingDirect drivingDirect; 

struct Cistern cistern[8];
struct Manipulator manipulator;

unsigned char displayFlag; //ˢ����ʾ��־λ  0��ˢ�� 1ˢ����ҳ�� 2ˢ�»�е�۶���ˢ��  3��λҺ������ʼ����ʾ
unsigned char MotorSpeedFlag; //���ٱ�־λ	 0�����ٶ� 1������� 2�������
unsigned char TargetCisternNumber; //��е������Ŀ���λ

/***************************************************************************/
// ��ȡ����
// ��������
// ����ֵ��0ʧ�� 1�ɹ�	
/***************************************************************************/
unsigned char parameter_read()
{
	WORD i, result = 1;
	Delay(10); 
	if(IapReadByte(IAP_ADDRESS+256) == 0xEE)
	{
		for(i=0; i<8; i++)
		{
			cistern[i].settingTime = ((IapReadByte(IAP_ADDRESS+(i*2)) << 8) | IapReadByte(IAP_ADDRESS+(i*2+1)));
		}
		result = 1;
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
	unsigned char i;
	runMode = AutoMode;
	displayMode = MainDisplayMode;
	for(i=0; i<8; i++)
	{
		cistern[i].cisternStatus = InCounting;
		cistern[i].currentTime = 0;
	}
	cistern[1].cisternStatus = Empty; //��ʼ״̬һ�Ųۿ�
	cistern[2].cisternStatus = Empty; //��ʼ״̬���Ųۿ�
	if(!parameter_read())
	{
		cistern[0].settingTime = 1800;
		cistern[1].settingTime = 720;
		cistern[2].settingTime = 720;
		cistern[3].settingTime = 300;
		cistern[4].settingTime = 300;
		cistern[5].settingTime = 300;
		cistern[6].settingTime = 300;
		cistern[7].settingTime = 1800;
	}
	manipulator.manipulaterStatus = Stop;
	manipulator.manipulatorPosition = Bottom;
	manipulator.currentPosition = 0;
	drivingDirect = DStop;
	displayFlag = 0;
	MotorSpeedFlag = 0;
	TargetCisternNumber = 0;
}

/***************************************************************************/
// �������浽eeprom
// ��������
// ����ֵ��0ʧ�� 1�ɹ�	
/***************************************************************************/
unsigned char parameter_save()
{
	WORD i, result = 1;
	Delay(10);
    IapEraseSector(IAP_ADDRESS); //���EEPROM
    for (i=0; i<512; i++)           //����Ƿ�����ɹ�
    {
        if (IapReadByte(IAP_ADDRESS+i) != 0xff)
            result = 0;
    }
    Delay(10);                      //Delay
	for(i=0; i<8; i++) //д��EEPROM
	{
		IapProgramByte(IAP_ADDRESS+(i*2), (BYTE)(cistern[i].perSettingTime>>8));
		IapProgramByte(IAP_ADDRESS+(i*2+1), (BYTE)cistern[i].perSettingTime);
	}
	IapProgramByte(IAP_ADDRESS+256, 0xEE); //д���־λ
    Delay(10);
	for(i=0; i<8; i++)  //У�鱣��ֵ
	{
		if(IapReadByte(IAP_ADDRESS+(i*2)) != (BYTE)(cistern[i].perSettingTime>>8))
		{
			result = 0;
		}
		if(IapReadByte(IAP_ADDRESS+(i*2+1)) != (BYTE)cistern[i].perSettingTime)
		{
			result = 0;
		}
	}
	for(i=0; i<8; i++) //����ֵΪ����ֵ
	{
		cistern[i].settingTime = cistern[i].perSettingTime;
	}
	return result;
}


