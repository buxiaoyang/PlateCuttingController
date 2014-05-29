#include <reg52.h>
#include <parameter.h>
#include <intrins.h>
#include <dispatch.h>

unsigned char ManiDispatchSteps = 20;

unsigned char SubDispatchSteps = 20; 	
								//0����ʼ״̬
								//1��������ǰ����
								//2���������ó���15%��������ǰ����
								//3���������ó���85%��������ǰ����
								//4���������ó���100%���а����
								//5���а��·���Ӧ
								//6���а��Ϸ���Ӧ�����̽���
								//20������״̬

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

//0����ʼ״̬
//1��������ǰ����
//2���������ó���15%��������ǰ����
//3���������ó���85%��������ǰ����
//4���������ó���100%���а����
//5���а��·���Ӧ
//6���а��Ϸ���Ӧ�����̽���
//20������״̬
void SubDispatch(void)
{
	switch(SubDispatchSteps)
	{
		case 0:	//0����ʼ״̬
			MotorForwardFast = 1;
			MotorBackFast = 1;
			MotorForwardSlow = 0;
			MotorBackSlow = 1;
			HydClamOut = 1;
			SubDispatchSteps ++;
		break;
		case 1:	//1��������ǰ����
			temp = parameterBoard[currentSettingIndex].boardLength>>3;
			if( currentlyBoardLength > temp )
			{
				MotorForwardSlow = 1;
				MotorForwardFast = 0;
				SubDispatchSteps ++;	
			}	
		break;
		case 2:	//2���������ó���15%��������ǰ����
			temp = parameterBoard[currentSettingIndex].boardLength - (parameterBoard[currentSettingIndex].boardLength>>3);
			if( currentlyBoardLength > temp)
			{
				MotorForwardSlow = 0;
				MotorForwardFast = 1;
				SubDispatchSteps ++;	
			}	
		break;
		case 3:	//3���������ó���85%��������ǰ����
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
		case 4:	//4���������ó���100%���а����
			if(HydClamInductorBottom == 0)
			{
				HydClamOut = 1;
				SubDispatchSteps ++;	
			}	
		break;
		case 5:	//5���а��·���Ӧ
			if(HydClamInductorTop == 0)
			{
				SubDispatchSteps = 20;	
			}	
		break;
		default:
			 _nop_();
	}
}