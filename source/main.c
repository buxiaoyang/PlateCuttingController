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

sbit MotorForward  		= P1^5;  //	���ǰ��
sbit MotorBack  		= P1^6;  // �������
sbit EncoderCounting	= P3^2;  // ��������������ɫ��
sbit EncoderDirection	= P2^4;  // ���������򣨰�ɫ��
sbit TestOut = 	P2^7; //T0


//External interrupt0 service routine
void exint0() interrupt 0           //(location at 0003H)
{
	TestOut = 0;
	TestOut = 1;	
}


/***************************************************************************/
// ������
// ��������
// ����ֵ����	
/***************************************************************************/
void main()
{
	IT0 = 1;                        //set INT0 int type (1:Falling 0:Low level)
    EX0 = 1;                        //enable INT0 interrupt
    EA = 1;                         //open global interrupt switch

	MotorForward = 0;
	MotorBack = 1;
	TestOut = 0;
	while(1)
	{
		
		
	}   
}








