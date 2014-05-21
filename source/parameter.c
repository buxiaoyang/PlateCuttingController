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

/***************************************************************************/
// 参数定义	
/***************************************************************************/
enum PowerMode powerMode; //启动
enum RunMode runMode; //运行模式
struct Board parameterBoard[4];	//板材参数

unsigned int parameterSignalNumPerMeter; //系统参数一：一米距离编码器的信号数
unsigned int parameterErrorCorrectionValue ; //系统参数二：误差修正值，信号数

unsigned int settingBoardLength; //设定长度
unsigned int settingBoardNumber; //设定块数

unsigned int currentlyBoardLength; //已做长度
unsigned int currentlyBoardNumber; //已做块数

unsigned long currentlySignalNum; //当前编码器信号数

/***************************************************************************/
// 读取参数
// 参数：无
// 返回值：0失败 1成功	
/***************************************************************************/
unsigned char parameter_read()
{
	unsigned char result = 1;
	return result;
}

/***************************************************************************/
// 参数初始化函数
// 参数：无
// 返回值：无	
/***************************************************************************/
void parameter_init()
{

}

/***************************************************************************/
// 参数保存到eeprom
// 参数：无
// 返回值：0失败 1成功	
/***************************************************************************/
unsigned char parameter_save()
{
	unsigned char result = 1;
	return result;
}


