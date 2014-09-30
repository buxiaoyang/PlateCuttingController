#include <reg52.h>
#include <intrins.h>
#include <parameter.h>
#include <key.h>
#include <dispatch.h>
#include <uart.h>

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
				powerMode = 1;
				//恢复自动模式继续工作
				/////////
				//ManiDispatchSteps = 0;
				ManiDispatchSteps = ManiDispatchStepsBak;
				SubDispatchSteps = SubDispatchStepsBak;
				timerCountOperation = 0;
				freshDiaplay = 1;
			}
			if(KeyStop == 0)
			{
				if(powerMode == 1)
				{
					//进入停机模式
					ManiDispatchStepsBak = 	ManiDispatchSteps;
					SubDispatchStepsBak = SubDispatchSteps;
					ManiDispatchSteps = 20;
					SubDispatchSteps = 20;
					////////
					powerMode = 0;
					freshDiaplay = 1;
				}
				else if(powerMode == 2)
				{
					//恢复自动模式继续工作
					ManiDispatchSteps = ManiDispatchStepsBak;
					SubDispatchSteps = SubDispatchStepsBak;
					//////
					powerMode = 1;
					SystemAlarm = 1;
					timerCountOperation = 0;
					freshDiaplay = 1;
				}	
			}
			if(KeyHydClam == 0)
			{
				//液压钳输出
				if(SubDispatchSteps == 22 && HydClamInductorTop == 0) //自动状态，并且处于液压钳等待状态
				{
					HydClamDown = 0;
					timerCountOperation = 0;
					SubDispatchSteps = 4;
				}
				freshDiaplay = 1;	
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