

#ifndef __UART_H__
#define __UART_H__

typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef unsigned long LONG;

extern bit freshDiaplay;
extern bit saveSetting;
extern BYTE manualOperation; //1, 前进  2，后退 3，慢进  4，切断上  5，切断下

void uart_init();
void SendData(BYTE dat);
void SendDataToScreen(WORD address, WORD dat);
void SendString(char *s);
void anyData();

#endif