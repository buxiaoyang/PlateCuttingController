#include <reg52.h>
#include <position.h>
#include <parameter.h>
#include <basefunc.h>
#include <key.h>

sbit Key_Out = P1^5;  //���ھ�������
sbit Key_In = P1^6;	  //���ھ�������

void Key_Scan(void);

uchar Key_Scan_Steps = 0; 		//0����ʼ״̬ ����а������������1
								//1���ӳ�10ms
								//2���������ȷʵ���������3
								//3��ȷ������
								//4����������ͷ������0

void Key_Scan(void)
{
	switch(Key_Scan_Steps)
	{
		case 0:
			if(Key_Out == 0 || Key_In == 0)
			{
			   	Key_Scan_Steps = 1;
			}
		break;
		case 1:
			if(Key_Out == 0 || Key_In == 0)
			{
			   	Key_Scan_Steps = 2;
			}
			else
			{
				Key_Scan_Steps = 0;
			}
		break;
		case 2:
			if(Key_Out == 0 && cistern[7].cisternStatus == InCounting)
			{
			   	cistern[7].cisternStatus = Ready;
				displayFlag = 1;
			}
			if(Key_In == 0  && cistern[0].cisternStatus == InCounting)
			{
				cistern[0].cisternStatus = Ready;
				displayFlag = 1;	
			}
			Key_Scan_Steps = 3;
		break;
		case 3:
			if(Key_Out == 1 && Key_In == 1)
			{
			   	Key_Scan_Steps = 0;
			}
		break;
		default:
			 _nop_();
	}
}