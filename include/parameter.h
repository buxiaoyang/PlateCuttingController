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

/***************************************************************************/
// 参数定义
/***************************************************************************/
enum PowerMode {PowerOn, PowerOff}; //启动状态 0关闭 1启动
enum RunMode {AutoMode, ManualMode}; //运行模式 0自动模式 1手动模式

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

extern enum PowerMode powerMode; //启动
extern enum RunMode runMode; //运行模式
extern struct Board parameterBoard[4];	//板材参数

extern unsigned int parameterSignalNumPerMeter; //系统参数一：一米距离编码器的信号数
extern unsigned int parameterErrorCorrectionValue ; //系统参数二：误差修正值，信号数

extern unsigned int settingBoardLength; //设定长度
extern unsigned int settingBoardNumber; //设定块数

extern unsigned int currentlyBoardLength; //已做长度
extern unsigned int currentlyBoardNumber; //已做块数

extern unsigned long currentlySignalNum; //当前编码器信号数

#endif
