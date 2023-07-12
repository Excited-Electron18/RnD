#ifndef __UART_H__
#define __UART_H__

#include<reg51.h>
#include "./Library/Global.h"

#if UART_TEST == 1
// --------------------------------------------------------------- Global variables
#define MAX_BUF_SIZE 32

// ------------------------------------------------------------- Function declaration

void UART_Init(void);
void UART_Transmit_Byte(char ch);
void UART_Transmit_String(char *str);
char UART_Receive_Byte(void);
void UART_Receive_String(void);
void UART_Delay(unsigned int count);

#endif
#endif