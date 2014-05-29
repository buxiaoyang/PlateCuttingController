#include <reg52.h>
#include <parameter.h>
#include <intrins.h>
#include <dispatch.h>

unsigned char ManiDispatchSteps = 20;

unsigned char SubDispatchSteps = 20; 	
								//0：初始状态
								//1：电机输出前进慢
								//2：到达设置长度15%，电机输出前进快
								//3：到达设置长度85%，点击输出前进慢
								//4：到达设置长度100%，切板输出
								//5：切板下方感应
								//6：切板上方感应，过程结束
								//20：结束状态

unsigned char currentSettingIndex = 20;
unsigned char currentSettingBoardNum = 20;
unsigned int temp;

void ManiDispatch(void)
{
	switch(ManiDispatchSteps)
	{
		case 0:
			currentSettingIndex = 0;
			if(parameterBoard[currentSettingIndex].boardLength != 0 && parameterBoard[currentSettingIndex].boardNumber != 0)
			{
				
			}
		break;
		case 1:
			
		break;
		default:
			 _nop_();
	}
}

//0：初始状态
//1：电机输出前进慢
//2：到达设置长度15%，电机输出前进快
//3：到达设置长度85%，点击输出前进慢
//4：到达设置长度100%，切板输出
//5：切板下方感应
//6：切板上方感应，过程结束
//20：结束状态
void SubDispatch(void)
{
	switch(SubDispatchSteps)
	{
		case 0:	//0：初始状态
			MotorForwardFast = 1;
			MotorBackFast = 1;
			MotorForwardSlow = 0;
			MotorBackSlow = 1;
			HydClamOut = 1;
			SubDispatchSteps ++;
		break;
		case 1:	//1：电机输出前进慢
			temp = parameterBoard[currentSettingIndex].boardLength>>3;
			if( currentlyBoardLength > temp )
			{
				MotorForwardSlow = 1;
				MotorForwardFast = 0;
				SubDispatchSteps ++;	
			}	
		break;
		case 2:	//2：到达设置长度15%，电机输出前进快
			temp = parameterBoard[currentSettingIndex].boardLength - (parameterBoard[currentSettingIndex].boardLength>>3);
			if( currentlyBoardLength > temp)
			{
				MotorForwardSlow = 0;
				MotorForwardFast = 1;
				SubDispatchSteps ++;	
			}	
		break;
		case 3:	//3：到达设置长度85%，点击输出前进慢
			if( currentlyBoardLength > parameterBoard[currentSettingIndex].boardLength)
			{
				MotorForwardSlow = 1;
				if(HydClamInductorTop == 0)
				{
					HydClamOut = 0;
					SubDispatchSteps ++;
				}
					
			}	
		break;
		case 4:	//4：到达设置长度100%，切板输出
			if(HydClamInductorBottom == 0)
			{
				HydClamOut = 1;
				SubDispatchSteps ++;	
			}	
		break;
		case 5:	//5：切板下方感应
			if(HydClamInductorTop == 0)
			{
				SubDispatchSteps = 20;	
			}	
		break;
		default:
			 _nop_();
	}
}