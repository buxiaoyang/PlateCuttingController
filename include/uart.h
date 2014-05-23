

#ifndef __UART_H__
#define __UART_H__

typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef unsigned long LONG;

void uart_init();
void SendData(BYTE dat);
void SendWord(WORD dat);
void SendString(char *s);

#endif