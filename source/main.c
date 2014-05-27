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

//External interrupt0 service routine
void exint0() interrupt 0           //(location at 0003H)
{
	if(EncoderDirection == 0)
	{
		currentlySignalNum --;
	}
	else
	{
		currentlySignalNum ++;
	}	
}

void exterInterInit()
{
	IT0 = 1;                        //set INT0 int type (1:Falling 0:Low level)
    EX0 = 1;                        //enable INT0 interrupt
    EA = 1;                         //open global interrupt switch
	
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


	currentlySignalNum = 0;	
//	MotorForward = 0;
//	MotorBack = 1;
	sysParm1_SignalNumPerMeter = 1000;
	while(1)
	{
		currentlyBoardLength = (currentlySignalNum*1000)/sysParm1_SignalNumPerMeter;	
		SendData(0x5A);
		SendData(0xA5);
		SendData(0x05);
		SendData(0x82);
		SendData(0x00);
		SendData(0x1F);
		SendData(currentlyBoardLength>>8);
		SendData(currentlyBoardLength);
	}   
}








