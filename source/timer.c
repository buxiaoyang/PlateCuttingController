#include <timer.h>
#include <reg52.h>
#include <intrins.h>
#include <parameter.h>
#include <key.h>
#include <dispatch.h>
#include <uart.h>

//-----------------------------------------------

/* define constants */
#define FOSC 11059200L
#define MODE1T                      //Timer clock mode, comment this line is 12T mode, uncomment is 1T mode

#ifdef MODE1T
#define T1MS (65536-FOSC/1000)      //1ms timer calculation method in 1T mode
#else
#define T1MS (65536-FOSC/12/1000)   //1ms timer calculation method in 12T mode
#endif

/* define SFR */
sfr AUXR = 0x8e;                    //Auxiliary register

/* define variables */
unsigned char count10ms;

//-----------------------------------------------

/* Timer0 interrupt routine */
void tm0_isr() interrupt 1 using 1
{
    TL0 = T1MS;                     //reload timer0 low byte
    TH0 = T1MS >> 8;                //reload timer0 high byte
    if (count10ms-- == 0)               //1ms * 1000 -> 1s
    {
		timerCountOperation ++;
        TestOut = !TestOut;  
		/////////////////////////////// 
		if(KeyAutoManual == 1)
		{
			runMode = 1;
			freshDiaplay = 1;
		}
		else
		{
			//切到手动模式和复位效果一样
			ManiDispatchSteps = 20;
			SubDispatchSteps = 20;
			settingBoardLength = 0;
			settingBoardNumber = 0;
			currentlySignalNum = 0;
			currentlyBoardNumber = 0;
			ManiDispatchStepsBak = 0;
			SubDispatchStepsBak = 20;
			runMode = 0;
			powerMode = 0;
		} 
		Key_Scan();
		ManiDispatch();
		SubDispatch();	
		/////////////////////////////// 
		count10ms = 9;               //reset counter
    }
}

//-----------------------------------------------

/* main program */
void timer_init()
{
#ifdef MODE1T
    AUXR |= 0x80;                    //timer0 work in 1T mode
#endif
    TMOD = 0x01;                    //set timer0 as mode1 (16-bit)
    TL0 = T1MS;                     //initial timer0 low byte
    TH0 = T1MS >> 8;                //initial timer0 high byte
    TR0 = 1;                        //timer0 start running
    ET0 = 1;                        //enable timer0 interrupt
    EA = 1;                         //open global interrupt switch
    count10ms = 9;                      //initial counter
}

