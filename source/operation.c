#include <reg52.h>
#include <position.h>
#include <parameter.h>
#include <basefunc.h>
#include <operation.h>
#include <intrins.h>

sbit MotorLeft = P2^0; //��е��������ƶ����
sbit MotorRight = P2^1; //��е��������ƶ����
sbit ManiUp =  P1^0; //��е�������ƶ����
sbit ManiDown =  P1^1; //��е�������ƶ����
sbit MotorSpeedUp =  P1^2; //���������������٣�
sbit MotorSlowDown = P1^3; //���������������٣�

sbit SystemError = P1^4; //ϵͳ����ָʾ��

sbit sensorInput = P3^0; //����λ�ø�Ӧ
sbit sensorManiTop = P3^1; //��е���ڶ���λ�ø�Ӧ
sbit sensorManiBut = P3^2; //��е���ڵͶ�λ�ø�Ӧ
sbit sensorOutput = P3^3; //��λ�ø�Ӧ


void A_Up_Down(uchar upCisternNumber, uchar downCisternNumber); //��е������upCisternNumber�������ŵ�downCisternNumber��
uchar A_Up_Down_Steps = 100;		   	//0����е�۳�ʼ״̬
										//1����е������upCisternNumber���еĿ�
										//2����е�۷ſ�downCisternNumber����
										//100����е�ۿղ���

unsigned int timeBetweenOpeartionDry = timeBetweenOpeartion;		//��е�۵������������ʱ��


void A_Move_Entrance(void); 		//��е��A�ƶ������ڲ�λ��
uchar A_Move_Entrance_Steps = 100; 		//0����е�۳�ʼ״̬
										//1����е��A��λǰ�ȴ�
										//2����е��A��λ
										//3����е�۶�λ��ȴ�
										//100����е�ۿղ���	
										
void ManualMode_Operation(void);  //�ֶ�ģʽ																				
										
uint ManiOperationTimer = 0; //��е�۲�����ʱ��


void A_Up_Down(uchar upCisternNumber, uchar downCisternNumber)
{
	switch(A_Up_Down_Steps)
	{
		case 0: 	//0����е�۳�ʼ״̬
			ManiOperationTimer = 0;
			SystemError = 1;
			A_Up_Down_Steps ++;	
		break;
		case 1: 	//1����е��A��λǰ�ȴ�
			TargetCisternNumber =  upCisternNumber;	//���ñ��λ�е�����е�Ŀ���λ
			if(ManiOperationTimer > timeBetweenOpeartion) //��ʱʱ�䵽
			{
				if(manipulator.currentPosition > upCisternNumber) //��ǰ��е����cisternNumber�Ų��ұ�
				{
					MotorLeft = 0; //�г�����
					MotorRight = 1;
					if(MotorSpeedFlag == 1) //�������
					{
					   	MotorSpeedUp = 0;
						MotorSlowDown = 1;
					}
					else if(MotorSpeedFlag == 2) //�������
					{
						MotorSpeedUp = 1;
						MotorSlowDown = 0;
					}
					else //�����ٶ�
					{
						MotorSpeedUp = 1;
						MotorSlowDown = 1;
					}

					drivingDirect = DGoEntrance;
					manipulator.manipulaterStatus = GoEntrance;
					if(displayFlag == 0)
					{
						displayFlag = 2;
					}
				}
				else if(manipulator.currentPosition < upCisternNumber)
				{
					MotorLeft = 1;
					MotorRight = 0; //�г�����
					if(MotorSpeedFlag == 1) //�������
					{
					   	MotorSpeedUp = 0;
						MotorSlowDown = 1;
					}
					else if(MotorSpeedFlag == 2) //�������
					{
						MotorSpeedUp = 1;
						MotorSlowDown = 0;
					}
					else //�����ٶ�
					{
						MotorSpeedUp = 1;
						MotorSlowDown = 1;
					}
					drivingDirect = GoOutfall;
					manipulator.manipulaterStatus = DGoOutfall;
					if(displayFlag == 0)
					{
						displayFlag = 2;
					}
				}
				else
				{
					MotorLeft = 1;
					MotorRight = 1;
					MotorSpeedUp = 1;
					MotorSlowDown = 1;
					A_Up_Down_Steps++;	
				}	
			}
		break;
		case 2: 	//2����е��A��λ
			if(manipulator.currentPosition == upCisternNumber)
			{
				MotorLeft = 1;
				MotorRight = 1;
				MotorSpeedUp = 1;
				MotorSlowDown = 1;
				ManiOperationTimer = 0;
				manipulator.manipulaterStatus = Stop;
				if(displayFlag == 0)
				{
					displayFlag = 2;
				}
				A_Up_Down_Steps ++;
			}
		break;
		case 3: 	//1����е��A��λǰ�ȴ������屣����
			if(ManiOperationTimer > timeBetweenOpeartion) //��ʱʱ�䵽
			{
				/*
				if(manipulator.currentPosition > upCisternNumber) //��ǰ��е����cisternNumber�Ų��ұ�
				{
					MotorLeft = 0;	//�г����� 
					MotorRight = 1;
					MotorSpeedUp = 1;
					MotorSlowDown = 0; //�������
					drivingDirect = DGoEntrance;
					manipulator.manipulaterStatus = GoEntrance;
					if(displayFlag == 0)
					{
						displayFlag = 2;
					}
					A_Up_Down_Steps = 2;
				}
				else if(manipulator.currentPosition < upCisternNumber)
				{
					MotorLeft = 1;
					MotorRight = 0; //�г�����
					MotorSpeedUp = 1;
					MotorSlowDown = 0; //�������
					drivingDirect = GoOutfall;
					manipulator.manipulaterStatus = DGoOutfall;
					if(displayFlag == 0)
					{
						displayFlag = 2;
					}
					A_Up_Down_Steps = 2;
				}
				*/
				if(manipulator.currentPosition != upCisternNumber)
				{
					SystemError = 0;
				}
				else
				{
					SystemError = 1;
					MotorLeft = 1;
					MotorRight = 1;
					MotorSpeedUp = 1;
					MotorSlowDown = 1;
					if(displayFlag == 0)
					{
						displayFlag = 2;
					}
					A_Up_Down_Steps ++;	
				}	
			}
		break;
		case 4:
			ManiUp = 0;
			manipulator.manipulaterStatus = GoUp;
			if(displayFlag == 0)
			{
				displayFlag = 2;
			}
			A_Up_Down_Steps++;
		break;
		case 5:		//4����е��A���� 
			if(sensorManiTop == 0) //��е��A���˸�Ӧ����Ӧ��
			{
				ManiUp = 1;
				manipulator.manipulatorPosition = Top;
				manipulator.manipulaterStatus = Stop;	
				cistern[upCisternNumber/2].cisternStatus = Empty;//��ǵ�ǰ��Ϊ��
				cistern[upCisternNumber/2].currentTime = 0;//�����ǰ�ۼ�ʱʱ��
				displayFlag = 1;
				A_Up_Down_Steps ++;
			}
		break;
		case 6: 	//0����е�۳�ʼ״̬
			ManiOperationTimer = 0;
			A_Up_Down_Steps ++;
		break;
		case 7: 	//1����е��A��λǰ�ȴ�
			TargetCisternNumber =  downCisternNumber;	//���ñ��λ�е�����е�Ŀ���λ
			if(ManiOperationTimer > timeBetweenOpeartionDry) //��ʱʱ�䵽
			{
				if(manipulator.currentPosition > downCisternNumber) //��ǰ��е����cisternNumber�Ų��ұ�
				{
					MotorLeft = 0; //�г�����
					MotorRight = 1;
					if(MotorSpeedFlag == 1) //�������
					{
					   	MotorSpeedUp = 0;
						MotorSlowDown = 1;
					}
					else if(MotorSpeedFlag == 2) //�������
					{
						MotorSpeedUp = 1;
						MotorSlowDown = 0;
					}
					else //�����ٶ�
					{
						MotorSpeedUp = 1;
						MotorSlowDown = 1;
					}
					drivingDirect = DGoEntrance;
					manipulator.manipulaterStatus = GoEntrance;
					if(displayFlag == 0)
					{
						displayFlag = 2;
					}
				}
				else if(manipulator.currentPosition < downCisternNumber)
				{
					MotorLeft = 1;
					MotorRight = 0; //�г�����
					if(MotorSpeedFlag == 1) //�������
					{
					   	MotorSpeedUp = 0;
						MotorSlowDown = 1;
					}
					else if(MotorSpeedFlag == 2) //�������
					{
						MotorSpeedUp = 1;
						MotorSlowDown = 0;
					}
					else //�����ٶ�
					{
						MotorSpeedUp = 1;
						MotorSlowDown = 1;
					}
					drivingDirect = GoOutfall;
					manipulator.manipulaterStatus = DGoOutfall;
					if(displayFlag == 0)
					{
						displayFlag = 2;
					}
				}
				else
				{
					MotorLeft = 1;
					MotorRight = 1;
					MotorSpeedUp = 1;
					MotorSlowDown = 1;
					A_Up_Down_Steps++;	
				}	
			}
		break;
		case 8: 	//2����е��A��λ
			if(manipulator.currentPosition == downCisternNumber)
			{
				MotorLeft = 1;
				MotorRight = 1;
				MotorSpeedUp = 1;
				MotorSlowDown = 1;
				ManiOperationTimer = 0;
				manipulator.manipulaterStatus = Stop;
				if(displayFlag == 0)
				{
					displayFlag = 2;
				}
				A_Up_Down_Steps ++;
			}
		break;
		case 9: 	//1����е��A��λǰ�ȴ������屣����
			if(ManiOperationTimer > timeBetweenOpeartion) //��ʱʱ�䵽
			{
				/*
				if(manipulator.currentPosition > downCisternNumber) //��ǰ��е����cisternNumber�Ų��ұ�
				{
					MotorLeft = 0; //�г����� 
					MotorRight = 1;
					MotorSpeedUp = 1;
					MotorSlowDown = 0; //�������
					drivingDirect = DGoEntrance;
					manipulator.manipulaterStatus = GoEntrance;
					if(displayFlag == 0)
					{
						displayFlag = 2;
					}
					A_Up_Down_Steps = 8;
				}
				else if(manipulator.currentPosition < downCisternNumber)
				{
					MotorLeft = 1;
					MotorRight = 0;	 //�г�����
					MotorSpeedUp = 1;
					MotorSlowDown = 0; //�������
					drivingDirect = GoOutfall;
					manipulator.manipulaterStatus = DGoOutfall;
					if(displayFlag == 0)
					{
						displayFlag = 2;
					}
					A_Up_Down_Steps = 8;
				}
				*/
				if(manipulator.currentPosition != downCisternNumber)
				{
					SystemError = 0;
				}
				else
				{
					SystemError = 1;
					MotorLeft = 1;
					MotorRight = 1;
					MotorSpeedUp = 1;
					MotorSlowDown = 1;
					if(displayFlag == 0)
					{
						displayFlag = 2;
					}
					A_Up_Down_Steps ++;	
				}	
			}
		break;
		case 10:
			ManiDown = 0;
			manipulator.manipulaterStatus = GoDown;
			if(displayFlag == 0)
			{
				displayFlag = 2;
			}
			A_Up_Down_Steps++;
		break;
		case 11:		//4����е��A���� 
			if(sensorManiBut == 0) //��е��A�׶˸�Ӧ����Ӧ��
			{
				ManiDown = 1;
				manipulator.manipulatorPosition = Bottom;
				manipulator.manipulaterStatus = Stop;	
				cistern[downCisternNumber/2].cisternStatus = InCounting;//��ǵ�ǰ��Ϊ��
				cistern[downCisternNumber/2].currentTime = 0;//�����ǰ�ۼ�ʱʱ��
				displayFlag = 1;
				A_Up_Down_Steps = 100;
			}
		break;
		default:
			  _nop_();
	}	
}

void A_Move_Entrance(void)
{
	switch(A_Move_Entrance_Steps)
	{
		case 0: 	//0����е�۳�ʼ״̬
			ManiOperationTimer = 0;
			A_Move_Entrance_Steps ++;
		break;
		case 1: 	//1����е��A��λǰ�ȴ�
			if(ManiOperationTimer > timeBetweenOpeartion) //��ʱʱ�䵽
			{
				MotorLeft = 0; //�г�����
				drivingDirect = DGoEntrance;
				manipulator.manipulaterStatus = GoEntrance;
				if(displayFlag == 0)
				{
					displayFlag = 2;
				}
				A_Move_Entrance_Steps++;
			}
		break;
		case 2: 	//2����е��A��λ
			if(sensorInput == 0)
			{
				ManiOperationTimer = 0;
				MotorLeft = 1;
				MotorRight = 1;
				drivingDirect = DStop;
				manipulator.manipulaterStatus = Stop;
				if(displayFlag == 0)
				{
					displayFlag = 2;
				}
				manipulator.currentPosition = 0;
				A_Move_Entrance_Steps ++;
			}
		break;
		case 3: 	//2����е��A��λ
			if(ManiOperationTimer > timeBetweenOpeartion) //��ʱʱ�䵽
			{
				ManiOperationTimer = 0;
				manipulator.currentPosition = 0;
				A_Move_Entrance_Steps = 100;
			}
		break;
		default:
			  _nop_();
	}
}

void ManualMode_Operation(void)
{
 	MotorLeft = 1;
 	MotorRight = 1;
 	ManiUp =  1;
 	ManiDown =  1;
 	MotorSpeedUp =  1;	
}
