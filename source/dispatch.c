#include <reg52.h>
#include <parameter.h>
#include <intrins.h>
#include <dispatch.h>


unsigned char ManiDispatchSteps = 0; 	//0：开机状态（机械臂在最下面，槽1为空）
								//1：机械臂移动到进口位置
								//2：出口空，并且6号槽就绪
								//3：6号槽空，并且5号就绪
								//4：5号槽空，并且4号就绪
								//5：4号槽空，并且3号就绪
								//6：3号槽空，并且2号就绪
								//7：3号槽空，并且1号就绪
								//8：2号槽空，并且入口就绪
								//9：1号槽空，并且入口就绪
								//10：10：入口空，并且出口就绪
								//20：检测空槽
								//100：空操作


void ManiDispatch(void)
{
	//机械臂调度状态机
	switch(ManiDispatchSteps)
	{
		case 0:	//0：开机状态（机械臂在最下面，槽1为空）
			
		break;
		default:
			 _nop_();
	}
}