

#ifndef __UART_H__
#define __UART_H__

typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef unsigned long LONG;

extern bit uartReceiveOK;

void uart_init();
void SendData(BYTE dat);
void SendDataToScreen(WORD address, WORD dat);
void SendString(char *s);
void anyData();

#endif