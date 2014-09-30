/***************************************************************************/
// 程序：清洗设备控制器
// 模块：参数
// 文件：parameter.c
// 作者：卜晓旸
// 版本：V0.02
// 日期：2013年11月8日
// 功能：参数
// 芯片：STC12C5A60S2
// 编译：Keil uVision3 V3.90
/***************************************************************************/

#include <parameter.h>
#include <eeprom.h>
#include <basefunc.h>

/***************************************************************************/
// 参数定义	
/***************************************************************************/
unsigned int powerMode; //运行模式 0关闭 1启动 2报警

unsigned int HydClamStatus; //液压剪刀状态 0：关闭  1：打开
unsigned int HydMonitorStatus; //液压电机状态 0：关闭  1：打开

struct Board parameterBoard[4];	//板材参数

unsigned int sysParm1_SignalNumPerMeter; //系统参数一：一米距离编码器的信号数
unsigned int sysParm2_ErrorCorrectionValue; //系统参数二：误差修正值，信号数
unsigned int sysParm3; //系统参数三
unsigned int sysParm4; //系统参数四
unsigned int sysParm5; //系统参数五

unsigned int settingBoardLength; //设定长度
unsigned int settingBoardNumber; //设定块数

unsigned int currentlyBoardLength; //已做长度
unsigned int currentlyBoardNumber; //已做块数

unsigned int errorCorrectionBoardLength; //修正的板子误差长度

unsigned long currentlySignalNum; //当前编码器信号数
unsigned long maxSignalNum;	  //最大编码器信号数

/***************************************************************************/
// 读取参数
// 参数：无
// 返回值：0失败 1成功	
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
// 参数初始化函数
// 参数：无
// 返回值：无	
/***************************************************************************/
void parameter_init()
{
	powerMode = 0;	//启动状态 0关闭 1启动 2报警
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
// 参数保存到eeprom
// 参数：无
// 返回值：0失败 1成功	
/***************************************************************************/
unsigned char parameter_save()
{
	unsigned char result = 1;
    delay_ms(10);                      //Delay
	IapEraseSector(IAP_ADDRESS); //擦除EEPROM
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
	IapProgramByte(IAP_ADDRESS+200, 0xEE); //写入标志位
	return result;
}


