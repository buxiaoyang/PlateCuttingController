/***************************************************************************/
// 程序：清洗设备控制器
// 模块：参数头文件
// 文件：parameter.h
// 作者：卜晓旸
// 版本：V0.02
// 日期：2013年11月8日
// 功能：参数头文件
// 芯片：STC12C5A60S2
// 编译：Keil uVision3 V3.90
/***************************************************************************/

#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#include <reg52.h>

/***************************************************************************/
// 引脚定义
/***************************************************************************/
//输入
sbit EncoderCounting		= P3^2;  	// 编码器计数（绿色）

sbit EncoderDirection		= P2^4;  	// 编码器方向（白色）

sbit HydClamInductorTop		= P0^0;  	// 液压剪刀上方感应器(系统在工作之前，根据液压剪刀是否在上的位置（常亮）
										// 来判定是否可以正常工作。)

sbit HydClamInductorBottom	= P0^1;  	// 液压剪刀下方感应器

sbit KeyStart				= P0^2;  	// 启动按钮，启动按钮只有在自动状态下才有效，启动之后，电机开始输出，
										// 单片机开始接收编码器信号。

sbit KeyAutoManual			= P0^3;  	// 手动状态下，启动按钮、系统停止按钮无效，编码器接收信号无效。
										// 自动状态下 ，液压剪刀按钮无效。（高电平自动，低电平手动）

sbit KeyStop				= P0^4;  	// 停止按钮

sbit KeyHydClam				= P0^5;  	// 液压剪刀按钮，只有下手动状态下才有效。

//输出
sbit MotorForwardFast  		= P1^5;  //	电机前进快速
sbit MotorBackFast  		= P1^6;  // 电机后退快速
sbit MotorForwardSlow  		= P1^0;  //	电机前进慢速
sbit MotorBackSlow  		= P1^1;  //	电机后退慢速
sbit HydClamOut  			= P1^4;  //	液压剪刀输出
sbit TestOut		  		= P2^7;  //	测试输出


/***************************************************************************/
// 参数定义
/***************************************************************************/
struct Board  //板材结构体
{
	unsigned int boardLength;   //板材长度
	unsigned int boardNumber;	//板材数量
};


/***************************************************************************/
// 参数声明
/***************************************************************************/
void parameter_init();
unsigned char parameter_save();

extern unsigned int powerMode; //启动
extern unsigned int runMode; //运行模式
extern struct Board parameterBoard[4];	//板材参数

extern unsigned int sysParm1_SignalNumPerMeter; //系统参数一：一米距离编码器的信号数
extern unsigned int sysParm2_ErrorCorrectionValue; //系统参数二：误差修正值，信号数
extern unsigned int sysParm3; //系统参数三
extern unsigned int sysParm4; //系统参数四
extern unsigned int sysParm5; //系统参数五

extern unsigned int settingBoardLength; //设定长度
extern unsigned int settingBoardNumber; //设定块数

extern unsigned int currentlyBoardLength; //已做长度
extern unsigned int currentlyBoardNumber; //已做块数

extern unsigned long currentlySignalNum; //当前编码器信号数
extern unsigned long maxSignalNum;	  //最大编码器信号数

#endif
