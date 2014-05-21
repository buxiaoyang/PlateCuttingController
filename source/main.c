/***************************************************************************/
// 程序：清洗设备控制器
// 模块：主函数	
// 文件：main.c
// 作者：卜晓旸
// 版本：V0.02
// 日期：2013年11月8日
// 功能：主函数
// 芯片：STC12C5A60S2
// 编译：Keil uVision3 V3.90
/***************************************************************************/

#include <reg52.h>

sbit MotorForward  		= P1^5;  //	电机前进
sbit MotorBack  		= P1^6;  // 电机后退
sbit EncoderCounting	= P3^2;  // 编码器计数（绿色）
sbit EncoderDirection	= P2^4;  // 编码器方向（白色）
sbit TestOut = 	P2^7; //T0


//External interrupt0 service routine
void exint0() interrupt 0           //(location at 0003H)
{
	TestOut = 0;
	TestOut = 1;	
}


/***************************************************************************/
// 主函数
// 参数：无
// 返回值：无	
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








