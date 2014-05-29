#include <reg52.h>
#include <intrins.h>
#include <parameter.h>
#include <key.h>
#include <dispatch.h>


void Key_Scan(void);

unsigned char Key_Scan_Steps = 0; 		//0：初始状态 如果有按键按下则进入1
										//1：延迟10ms
										//2：如果按键确实按下则进入3
										//3：确定按键
										//4：如果按键释放则进入0

void Key_Scan(void)
{
	switch(Key_Scan_Steps)
	{
		case 0:
			if(KeyStart == 0 || KeyStop == 0 || KeyHydClam == 0)
			{
			   	Key_Scan_Steps = 1;
			}
		break;
		case 1:
			if(KeyStart == 0 || KeyStop == 0 || KeyHydClam == 0)
			{
			   	Key_Scan_Steps = 2;
			}
			else
			{
				Key_Scan_Steps = 0;
			}
		break;
		case 2:
			if(KeyStart == 0)
			{
				if(runMode)
				{
					powerMode = 1;
					ManiDispatchSteps = 0;
				}
			   	//cistern[7].cisternStatus = Ready;
				//displayFlag = 1;
			}
			if(KeyStop == 0)
			{
				powerMode = 0;	
			}
			if(KeyHydClam == 0)
			{
				//液压钳输出
				if(!runMode) //手动状态
				{
					
				}	
			}
			Key_Scan_Steps = 3;
		break;
		case 3:
			if(KeyStart == 1 && KeyStop == 1 && KeyHydClam == 1)
			{
			   	Key_Scan_Steps = 0;
			}
		break;
		default:
			 _nop_();
	}
}