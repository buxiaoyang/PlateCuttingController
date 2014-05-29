/***************************************************************************/
// ������ϴ�豸������
// ģ�飺������	
// �ļ���main.c
// ���ߣ������D
// �汾��V0.02
// ���ڣ�2013��11��8��
// ���ܣ�������
// оƬ��STC12C5A60S2
// ���룺Keil uVision3 V3.90
/***************************************************************************/

#include <reg52.h>
#include <basefunc.h>
#include <parameter.h>
#include <uart.h>
#include <timer.h>
#include <key.h>
#include <dispatch.h>

//External interrupt0 service routine
void exint0() interrupt 0           //(location at 0003H)
{
	if(EncoderDirection == 0)
	{
		if(currentlySignalNum>0)
		{
			currentlySignalNum --;
		}
	}
	else
	{		
		if(currentlySignalNum <= maxSignalNum)
		{
		   	currentlySignalNum ++;
		}
	}	
}

void exterInterInit()
{
	IT0 = 1;                        //set INT0 int type (1:Falling 0:Low level)
    EX0 = 1;                        //enable INT0 interrupt
    EA = 1;                         //open global interrupt switch
	
}

void parameter_send_screen()
{
	SendDataToScreen(0x0001, sysParm1_SignalNumPerMeter);
	SendDataToScreen(0x0003, sysParm2_ErrorCorrectionValue);
	SendDataToScreen(0x0005, sysParm3);
	SendDataToScreen(0x0007, sysParm4);
	SendDataToScreen(0x0009, sysParm5);
	SendDataToScreen(0x000B, parameterBoard[0].boardLength);
	SendDataToScreen(0x000D, parameterBoard[0].boardNumber);
	SendDataToScreen(0x000F, parameterBoard[1].boardLength);
	SendDataToScreen(0x0011, parameterBoard[1].boardNumber);
	SendDataToScreen(0x0013, parameterBoard[2].boardLength);
	SendDataToScreen(0x0015, parameterBoard[2].boardNumber);
	SendDataToScreen(0x0017, parameterBoard[3].boardLength);
	SendDataToScreen(0x0019, parameterBoard[3].boardNumber);
	if(!powerMode && !runMode)
	{
	   	SendDataToScreen(0x0000, 0x0000);
	}
	else if(!powerMode && runMode)
	{
	   	SendDataToScreen(0x0000, 0x0001);
	}
	else if(powerMode && !runMode)
	{
		SendDataToScreen(0x0000, 0x0002);
	}
	else
	{
		SendDataToScreen(0x0000, 0x0003);
	}
	SendDataToScreen(0x001B, settingBoardLength);
	SendDataToScreen(0x001D, settingBoardNumber);
	SendDataToScreen(0x001F, currentlyBoardLength);
	SendDataToScreen(0x0021, currentlyBoardNumber);
}

/***************************************************************************/
// ������
// ��������
// ����ֵ����	
/***************************************************************************/
void main()
{
	exterInterInit();
	uart_init();
	//timer_init();
	parameter_init();
	maxSignalNum = (65535 * sysParm1_SignalNumPerMeter)/1000-2000;
	while(1)
	{
		currentlyBoardLength = (currentlySignalNum*1000)/sysParm1_SignalNumPerMeter;	
		parameter_send_screen();
		//SendDataToScreen(0x001F, currentlyBoardLength);
		if(uartReceiveOK)
		{
			uartReceiveOK = 0;
			//anyData();
		}
		TestOut = ! TestOut;   
		if(KeyAutoManual == 1)
		{
			runMode = 1;
		}
		else
		{
			runMode = 0;
		} 
		Key_Scan();
		ManiDispatch();
		SubDispatch();
	}   
}








