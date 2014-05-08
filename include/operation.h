#ifndef 		_OPERATION_H__
#define 		_OPERATION_H__

extern void A_Move(unsigned char move_cisternNumber);
extern unsigned char A_Move_Steps;
extern void A_Down(unsigned char down_cisternNumber); 
extern unsigned char A_Down_Steps;
extern void A_Up(unsigned char up_cisternNumber); 
extern unsigned char A_Up_Steps;
extern void A_Up_Down(unsigned char upCisternNumber, unsigned char downCisternNumber);
extern unsigned char A_Up_Down_Steps;

extern void A_Move_Entrance(void); 
extern unsigned char A_Move_Entrance_Steps;

extern void ManualMode_Operation(void); 

extern unsigned int ManiOperationTimer;
extern unsigned int timeBetweenOpeartionDry;

#define timeBetweenOpeartion 2  //������е��ֱ�ӵ��л������ȴ�ʱ��

#endif
