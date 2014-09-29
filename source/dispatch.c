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
	unsigned int temp, temp1;
	switch(SubDispatchSteps)
	{
		case 0:	//0����ʼ���������ǰ����
			MotorForwardFast = 1;
			MotorBackFast = 1;
			MotorForwardSlow = 0;
			MotorBackSlow = 1;
			HydClamDown = 1;
			HydClamUp = 1;
			SubDispatchSteps ++;
		break;
		case 1:	//1�����ӵ������ó��Ȱ˷�֮һ�����ǰ����
			temp = settingBoardLength-errorCorrectionBoardLength;
			temp1 = temp>>3;
			if( currentlyBoardLength > temp1 )
			{
				MotorForwardSlow = 1;
				MotorForwardFast = 0;
				SubDispatchSteps ++;	
			}	
		break;
		case 2:	//2���������ó��Ȱ˷�֮�ߣ������Ϊ����
			temp = settingBoardLength-errorCorrectionBoardLength;
			temp1 = temp - (temp>>3);
			if( currentlyBoardLength > temp1)
			{
				MotorForwardSlow = 0;
				MotorForwardFast = 1;
				SubDispatchSteps ++;	
			}	
		break;
		case 3:	//3���������ó���100%������������Ϸ��������������
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
		case 4:	//4�������·���������Ӧ�����ر����£��������
			//HydClamDown = 0;
			if(HydClamInductorBottom == 0)
			{
				HydClamDown = 1;
				HydClamUp = 0;
				SubDispatchSteps ++;	
			}	
		break;
		case 5:	//5�������Ϸ���Ӧ����Ӧ�����رռ�������
			if(HydClamInductorTop == 0)
			{
				HydClamUp = 1;
				SubDispatchSteps = 20;	
			}	
		break;
		case 22:	//22��Һѹ�����ر�״̬���ȴ��ֶ�����Һѹ����
			_nop_();	
		break;
		default:
			_nop_();
	}
}