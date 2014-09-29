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


void ManiDispatch(void)
{
	switch(ManiDispatchSteps)
	{
		case 0: 
			currentSettingIndex = 0;
			currentSettingBoardNum =  parameterBoard[currentSettingIndex].boardNumber;
			currentlyBoardNumber = 0;
			settingBoardNumber = currentSettingBoardNum;
			ManiDispatchSteps ++;
		break;
		case 1:
			if(parameterBoard[currentSettingIndex].boardNumber != 0 && parameterBoard[currentSettingIndex].boardLength != 0)
			{
				ManiDispatchSteps ++;
			}
			else
			{
				ManiDispatchSteps = 4;
			}
		break;
		case 2:
			settingBoardLength =  parameterBoard[currentSettingIndex].boardLength - (currentlyBoardNumber*parameterBoard[currentSettingIndex].boardDecLength);
			SubDispatchSteps = 0;
			currentlySignalNum = 0;
			ManiDispatchSteps ++;
		break;
		case 3:
			if(SubDispatchSteps == 20)
			{
				currentSettingBoardNum --;
				currentlyBoardNumber ++;
				if(currentSettingBoardNum > 0)
				{
					ManiDispatchSteps = 2;
				}
				else
				{
					ManiDispatchSteps ++;
				}
			}
		break;
		case 4:
			currentSettingIndex ++;
			if(currentSettingIndex < 4)
			{
				currentSettingBoardNum =  parameterBoard[currentSettingIndex].boardNumber;
				currentlyBoardNumber = 0;
				settingBoardNumber = currentSettingBoardNum;
				ManiDispatchSteps = 1;
			}
			else
			{
				ManiDispatchSteps = 20;
				powerMode = 0;
			}		
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
	unsigned int temp, temp1;
	switch(SubDispatchSteps)
	{
		case 0:	//0：开始工作，电机前进慢
			MotorForwardFast = 1;
			MotorBackFast = 1;
			MotorForwardSlow = 0;
			MotorBackSlow = 1;
			HydClamDown = 1;
			HydClamUp = 1;
			SubDispatchSteps ++;
		break;
		case 1:	//1：板子到达设置长度八分之一，电机前进快
			temp = settingBoardLength-errorCorrectionBoardLength;
			temp1 = temp>>3;
			if( currentlyBoardLength > temp1 )
			{
				MotorForwardSlow = 1;
				MotorForwardFast = 0;
				SubDispatchSteps ++;	
			}	
		break;
		case 2:	//2：到达设置长度八分之七，电机变为慢速
			temp = settingBoardLength-errorCorrectionBoardLength;
			temp1 = temp - (temp>>3);
			if( currentlyBoardLength > temp1)
			{
				MotorForwardSlow = 0;
				MotorForwardFast = 1;
				SubDispatchSteps ++;	
			}	
		break;
		case 3:	//3：到达设置长度100%，如果剪刀在上方则输出剪刀向下
			temp = settingBoardLength-errorCorrectionBoardLength;
			if( currentlyBoardLength > temp)
			{
				MotorForwardSlow = 1;
				if(HydClamInductorTop == 0)
				{
					if(HydClamStatus == 1)
					{
						HydClamDown = 0;
						SubDispatchSteps ++;
					}
					else
					{
						SubDispatchSteps = 22;
					}
				}
					
			}	
		break;
		case 4:	//4：剪刀下方传感器感应到，关闭向下，输出向上
			//HydClamDown = 0;
			if(HydClamInductorBottom == 0)
			{
				HydClamDown = 1;
				HydClamUp = 0;
				SubDispatchSteps ++;	
			}	
		break;
		case 5:	//5：剪刀上方感应器感应到，关闭剪刀向上
			if(HydClamInductorTop == 0)
			{
				HydClamUp = 1;
				SubDispatchSteps = 20;	
			}	
		break;
		case 22:	//22：液压剪刀关闭状态，等待手动开启液压剪刀
			_nop_();	
		break;
		default:
			_nop_();
	}
}