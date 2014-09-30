

#ifndef __UART_H__
#define __UART_H__

typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef unsigned long LONG;

extern bit freshDiaplay;
extern bit saveSetting;
extern BYTE manualOperation; //1, ǰ��  2������ 3������  4���ж���  5���ж���

void uart_init();
void SendData(BYTE dat);
void SendDataToScreen(WORD address, WORD dat);
void SendString(char *s);
void anyData();

#endif