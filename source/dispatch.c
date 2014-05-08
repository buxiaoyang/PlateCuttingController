#include <reg52.h>
#include <position.h>
#include <parameter.h>
#include <basefunc.h>
#include <operation.h>
#include <intrins.h>
#include <dispatch.h>

void ManiDispatch(void); //е�۵��Ȳ���
void ManualDispatch(void); //�ֶ�״̬�»�е�ۼ��

uchar ManiDispatchSteps = 0; 	//0������״̬����е���������棬��1Ϊ�գ�
								//1����е���ƶ�������λ��
								//2�����ڿգ�����6�Ų۾���
								//3��6�Ųۿգ�����5�ž���
								//4��5�Ųۿգ�����4�ž���
								//5��4�Ųۿգ�����3�ž���
								//6��3�Ųۿգ�����2�ž���
								//7��3�Ųۿգ�����1�ž���
								//8��2�Ųۿգ�������ھ���
								//9��1�Ųۿգ�������ھ���
								//10��10����ڿգ����ҳ��ھ���
								//20�����ղ�
								//100���ղ���

uchar ManualDispatchSteps = 0;

uint ManiDispatchTimer = 0; //��е�۵��ȶ�ʱ��							
uchar ManiDispatchCurrent = 0; //��ǰ�����Ŀ�


void ManiDispatch(void)
{
	//���û�е���ٶȵȼ�
	uchar distanceBetweenManiAndTarget = 0;
	if(TargetCisternNumber > manipulator.currentPosition)
	{
		distanceBetweenManiAndTarget = 	TargetCisternNumber - manipulator.currentPosition;
	}
	else
	{
		distanceBetweenManiAndTarget = 	manipulator.currentPosition - TargetCisternNumber;
	}
	if(distanceBetweenManiAndTarget > 2)
	{
		MotorSpeedFlag = 1;
	}
	else
	{
		MotorSpeedFlag = 0;
	}
	//��е�۵���״̬��
	switch(ManiDispatchSteps)
	{
		case 0:	//0������״̬����е���������棬��1Ϊ�գ�
			A_Move_Entrance_Steps = 0;
			ManiDispatchSteps = 1;
		break;
		case 1:	//1����е���ƶ�������λ��
			A_Move_Entrance();
			if(A_Move_Entrance_Steps == 100)
			{
				ManiDispatchSteps = 20;
			}
		break;
		case 2:	 //2�����ڿգ�����6�Ų۾���
			A_Up_Down(12,14);
			if(A_Up_Down_Steps == 100)
			{
				ManiDispatchSteps = 20;
			} 
		break;
		case 3:	 //3��6�Ųۿգ�����5�ž���
			A_Up_Down(10,12);
			if(A_Up_Down_Steps == 100)
			{
				ManiDispatchSteps = 20;
			}
		break;
		case 4:	 //4��5�Ųۿգ�����4�ž���
			A_Up_Down(8,10);
			if(A_Up_Down_Steps == 100)
			{
				ManiDispatchSteps = 20;
			}
		break;
		case 5:	 //5��4�Ųۿգ�����3�ž���
			A_Up_Down(6,8);
			if(A_Up_Down_Steps == 100)
			{
				ManiDispatchSteps = 20;
			}
		break;
		case 6:	 //6��3�Ųۿգ�����2�ž���
			A_Up_Down(4,6);
			if(A_Up_Down_Steps == 100)
			{
				ManiDispatchSteps = 20;
			}
		break;
		case 7:	 //7��3�Ųۿգ�����1�ž���
			A_Up_Down(2,6);
			if(A_Up_Down_Steps == 100)
			{
				ManiDispatchSteps = 20;
				//�°���
				if(displayMode == PowerOffing)
				{
					displayMode = PowerOffed;
				}
			}
		break;
		case 8:	 //8��2�Ųۿգ�������ھ���
			A_Up_Down(0,4);
			if(A_Up_Down_Steps == 100)
			{
				ManiDispatchSteps = 20;
			}
		break;
		case 9:	 //9��1�Ųۿգ�������ھ���
			A_Up_Down(0,2);
			if(A_Up_Down_Steps == 100)
			{
				ManiDispatchSteps = 20;
			}
		break;
		case 10: //10����ڿգ����ҳ��ھ���
			A_Up_Down(14,0);
			if(A_Up_Down_Steps == 100)
			{
				ManiDispatchSteps = 20;
			}
		break;
		case 20:
			if(cistern[2].cisternStatus == Empty && cistern[0].cisternStatus == Ready)	 //8��2�Ųۿգ�������ھ���
			{
				A_Up_Down_Steps = 0;
				timeBetweenOpeartionDry = timeBetweenOpeartion;
				ManiDispatchSteps = 8;
			}
			else if(cistern[1].cisternStatus == Empty && cistern[0].cisternStatus == Ready)	 //9��1�Ųۿգ�������ھ���
			{
				A_Up_Down_Steps = 0;
				timeBetweenOpeartionDry = timeBetweenOpeartion;
				ManiDispatchSteps = 9;
			}
			else if(cistern[0].cisternStatus == Empty && cistern[7].cisternStatus == Ready)	 //10����ڿգ����ҳ��ھ���
			{
				A_Up_Down_Steps = 0;
				timeBetweenOpeartionDry = timeBetweenOpeartion;
				ManiDispatchSteps = 10;
			}
			else if(cistern[7].cisternStatus == Empty && cistern[6].cisternStatus == Ready) //2�����ڿգ�����6�Ų۾���
			{
				A_Up_Down_Steps = 0;
				timeBetweenOpeartionDry = timeBetweenOpeartion;
				ManiDispatchSteps = 2;	 
			}
			else if(cistern[6].cisternStatus == Empty && cistern[5].cisternStatus == Ready)	  //3��6�Ųۿգ�����5�ž���
			{
				A_Up_Down_Steps = 0;
				timeBetweenOpeartionDry = timeBetweenOpeartion;
				ManiDispatchSteps = 3;
			}
			else if(cistern[5].cisternStatus == Empty && cistern[4].cisternStatus == Ready)	//4��5�Ųۿգ�����4�ž���
			{
				A_Up_Down_Steps = 0;
				timeBetweenOpeartionDry = 60;
				ManiDispatchSteps = 4;
			}
			else if(cistern[4].cisternStatus == Empty && cistern[3].cisternStatus == Ready)	  //5��4�Ųۿգ�����3�ž���
			{
				A_Up_Down_Steps = 0;
				timeBetweenOpeartionDry = timeBetweenOpeartion;
				ManiDispatchSteps = 5;
			}
			else if(cistern[3].cisternStatus == Empty)	  //3�Ųۿգ�����1�Ż���2�ž���
			{
				if(cistern[2].cisternStatus == Ready && cistern[1].cisternStatus == InCounting)	//���Ų۾���
				{
					A_Up_Down_Steps = 0;
					timeBetweenOpeartionDry = 60;
					ManiDispatchSteps = 6;
				}
				else if(cistern[1].cisternStatus == Ready && cistern[2].cisternStatus == InCounting) //һ�Ų۾���
				{
					A_Up_Down_Steps = 0;
					timeBetweenOpeartionDry = 60;
					ManiDispatchSteps = 7;
				}
				else if(cistern[1].cisternStatus == Ready && cistern[2].cisternStatus == Ready) //һ�Ŷ��Ŷ�����
				{
					if(cistern[1].currentTime > cistern[2].currentTime)
					{
						A_Up_Down_Steps = 0;
						timeBetweenOpeartionDry = 60;
						ManiDispatchSteps = 7;	
					}
					else
					{
						A_Up_Down_Steps = 0;
						timeBetweenOpeartionDry = 60;
						ManiDispatchSteps = 6;	
					}
				}
				else
				{
					if(cistern[1].cisternStatus == Ready)
					{
						A_Up_Down_Steps = 0;
						timeBetweenOpeartionDry = 60;
						ManiDispatchSteps = 7;
					}
					else if(cistern[2].cisternStatus == Ready)
					{
						A_Up_Down_Steps = 0;
						timeBetweenOpeartionDry = 60;
						ManiDispatchSteps = 6;
					}
				}
			}
		break;
		default:
			 _nop_();
	}
}

void ManualDispatch(void)
{
	ManiDispatchSteps = 20;
	ManualMode_Operation();
}