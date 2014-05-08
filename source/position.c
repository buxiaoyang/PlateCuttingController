#include <reg52.h>
#include <position.h>
#include <parameter.h>
#include <basefunc.h>

sbit sensorPositon = P3^4; //��е�۶�λ������

uchar sensorPosiCheck = 0; //��е��Aλ�ü���־λ 
							//0��û�и�Ӧ��û�е͵�λ״̬
							//1����⵽�͵�λ�����ӳ�״̬
							//2���ȴ��͵�λ�ͷŽ�����ʱ
							//3�����͵�λȷʵ�ͷ�

void maniPosition(void) //��е�۶�λ
{
	//��е��Aλ�ü��
	if(sensorPosiCheck==0)
	{
		if(sensorPositon == 0)
		{
			sensorPosiCheck = 1;
		}
	}
	else if(sensorPosiCheck==1)
	{
		if(sensorPositon == 0)
		{
			if(drivingDirect == DGoOutfall)
			{
				//���һ�е��λ�ü�һ
				manipulator.currentPosition++;
				displayFlag = 1;
				if(manipulator.currentPosition>14)
				{
					manipulator.currentPosition = 14;
				}
			}
			else if (drivingDirect == DGoEntrance)
			{
				//���һ�е��λ�ü�һ
				manipulator.currentPosition--;
				displayFlag = 1;
				if(manipulator.currentPosition>200)
				{
					manipulator.currentPosition = 0;
				}	
			}
			sensorPosiCheck = 2;
		}
		else
		{
			//�����ź�ֱ���ͷ�
			sensorPosiCheck = 0;
		}
	}
	else if(sensorPosiCheck==2)
	{
		if(sensorPositon == 1)
		{
			sensorPosiCheck = 3;
		}	
	}
	else
	{
		if(sensorPositon == 1)
		{
			if(drivingDirect == DGoOutfall)
			{
				//���һ�е��λ�ü�һ
				manipulator.currentPosition++;
				displayFlag = 1;
				if(manipulator.currentPosition>14)
				{
					manipulator.currentPosition = 14;
				}
			}
			else if (drivingDirect == DGoEntrance)
			{
				//���һ�е��λ�ü�һ
				manipulator.currentPosition--;
				displayFlag = 1;
				if(manipulator.currentPosition>200)
				{
					manipulator.currentPosition = 0;
				}	
			}
			sensorPosiCheck = 0;
		}
	}
}
