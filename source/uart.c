#include <uart.h>
#include <reg52.h>
#include <intrins.h>
#include <parameter.h>


#define FOSC 11059200L      //System frequency
#define BAUD 115200         //UART baudrate

/*Define UART parity mode*/
#define NONE_PARITY     0   //None parity
#define ODD_PARITY      1   //Odd parity
#define EVEN_PARITY     2   //Even parity
#define MARK_PARITY     3   //Mark parity
#define SPACE_PARITY    4   //Space parity

#define PARITYBIT NONE_PARITY   //Testing even parity

/*Declare SFR associated with the UART2 */
sfr AUXR  = 0x8e;           //Auxiliary register
sfr S2CON = 0x9a;           //UART2 control register
sfr S2BUF = 0x9b;           //UART2 data buffer
sfr BRT   = 0x9c;           //Baudrate generator
sfr IE2   = 0xaf;           //Interrupt control 2

#define S2RI  0x01          //S2CON.0
#define S2TI  0x02          //S2CON.1
#define S2RB8 0x04          //S2CON.2
#define S2TB8 0x08          //S2CON.3

bit busy;
bit uartReceiveOK = 0;

BYTE uartBuffer[15] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

BYTE receiveSteps = 0; 	// 0: 没有数据接收
						// 1: 接收到5A
						// 2：接收到A5
						// 3：接收到数据长度
						// 4: 接收数据
						// 5：确定指令动作
BYTE dataIndex = 0;
BYTE dataLength = 0;
  
void SendData(BYTE dat);
void SendString(char *s);
void ReceiveData(BYTE dat);
void anyData();

void uart_init()
{
#if (PARITYBIT == NONE_PARITY)
    S2CON = 0x50;           //8-bit variable UART
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    S2CON = 0xda;           //9-bit variable UART, parity bit initial to 1
#elif (PARITYBIT == SPACE_PARITY)
    S2CON = 0xd2;           //9-bit variable UART, parity bit initial to 0
#endif

    BRT = -(FOSC/32/BAUD);  //Set auto-reload vaule of baudrate generator
    AUXR = 0x14;            //Baudrate generator work in 1T mode
    IE2 = 0x01;             //Enable UART2 interrupt
    EA = 1;                 //Open master interrupt switch

    //SendString("STC12C5A60S2\r\nUart2 Test !\r\n");
    //while(1);
}

/*----------------------------
UART2 interrupt service routine
----------------------------*/
void Uart2() interrupt 8 using 1
{
    if (S2CON & S2RI)
    {
        S2CON &= ~S2RI;     //Clear receive interrupt flag
        ReceiveData(S2BUF);
		//P0 = S2BUF;         //P0 show UART data
        //P2 = (S2CON & S2RB8);//P2.2 show parity bit
    }
    if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;     //Clear transmit interrupt flag
        busy = 0;           //Clear transmit busy flag
    }
}

/*----------------------------
Send a byte data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void SendData(BYTE dat)
{
    while (busy);           //Wait for the completion of the previous data is sent
    ACC = dat;              //Calculate the even parity bit P (PSW.0)
    if (P)                  //Set the parity bit according to P
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON &= ~S2TB8;    //Set parity bit to 0
#elif (PARITYBIT == EVEN_PARITY)
        S2CON |= S2TB8;     //Set parity bit to 1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON |= S2TB8;     //Set parity bit to 1
#elif (PARITYBIT == EVEN_PARITY)
        S2CON &= ~S2TB8;    //Set parity bit to 0
#endif
    }
    busy = 1;
    S2BUF = ACC;            //Send data to UART2 buffer
}

/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
void SendString(char *s)
{
    while (*s)              //Check the end of the string
    {
        SendData(*s++);     //Send current char and increment string ptr
    }
}

void SendDataToScreen(WORD address, WORD dat)
{
	SendData(0x5A);
	SendData(0xA5);
	SendData(0x05);
	SendData(0x82);
	SendData(address>>8);
	SendData(address);
	SendData(dat>>8);
	SendData(dat);
}

void ReceiveData(BYTE dat)
{
	// 0: 接收到5A
	// 1：接收到A5
	// 2：接收到数据长度
	// 3: 接收数据
	// 4：确定指令动作
	switch(receiveSteps)
	{
		case 0:
			if(dat == 0x5A)
			{
				receiveSteps ++;
			}
		break;
		case 1:
			if(dat == 0xA5)
			{
				receiveSteps ++;
			}
			else
			{
			  	receiveSteps = 0;
			}
		break;
		case 2:
			dataLength = dat;
			dataIndex = 0;
			receiveSteps ++;
		break;
		case 3:
			uartBuffer[dataIndex] = dat;
			dataIndex ++;
			if(dataIndex >= dataLength)
			{
				anyData();
				receiveSteps = 0;
			}
		break;
		default:
			_nop_();
			receiveSteps = 0;
	}
}

void anyData()
{
	WORD dat = ((uartBuffer[4]<<8) | uartBuffer[5]);
	if(uartBuffer[2] == 0x01)		//系统参数1
	{
		sysParm1_SignalNumPerMeter = dat;
		maxSignalNum = (65535 * sysParm1_SignalNumPerMeter)/1000-2000;
	}
	else if(uartBuffer[2] == 0x03)	//系统参数2
	{
		sysParm2_ErrorCorrectionValue = dat;
	}
	else if(uartBuffer[2] == 0x05) 	//系统参数3
	{
		sysParm3 = dat;
	}
	else if(uartBuffer[2] == 0x07)	//系统参数4
	{
		sysParm4 = dat;
	}
	else if(uartBuffer[2] == 0x09)	//系统参数5
	{
		sysParm5 = dat;	
	}
	else if(uartBuffer[2] == 0x0B)	//板材参数_板长1
	{
		parameterBoard[0].boardLength = dat;
	}
	else if(uartBuffer[2] == 0x0D)	//板材参数_块数1	
	{
		parameterBoard[0].boardNumber = dat;
	}
	else if(uartBuffer[2] == 0x0F)	//板材参数_板长2
	{
		parameterBoard[1].boardLength = dat;
	}
	else if(uartBuffer[2] == 0x11)	//板材参数_块数2
	{
		parameterBoard[1].boardNumber = dat;
	}
	else if(uartBuffer[2] == 0x13)	//板材参数_板长3
	{
		parameterBoard[2].boardLength = dat;
	}
	else if(uartBuffer[2] == 0x15) 	//板材参数_块数3
	{
		parameterBoard[2].boardNumber = dat;
	}
	else if(uartBuffer[2] == 0x17)	//板材参数_板长4
	{
		parameterBoard[3].boardLength = dat;
	}
	else if(uartBuffer[2] == 0x19)	//板材参数_块数4
	{
		parameterBoard[3].boardNumber = dat;
	}
	else if(uartBuffer[2] == 0x23)	//手动操作_前进
	{

	}
	else if(uartBuffer[2] == 0x24)	//手动操作_后退
	{
		
	}
	else if(uartBuffer[2] == 0x25)	//手动操作_慢进
	{
		
	}
	else if(uartBuffer[2] == 0x26)	//手动操作_切断上
	{
		
	}
	else if(uartBuffer[2] == 0x27)	//手动操作_切断下
	{
		
	}
	else if(uartBuffer[2] == 0x28)	//运行画面_复位按钮
	{
		
	}
	uartReceiveOK = 1;	
}
