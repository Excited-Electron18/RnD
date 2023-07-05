#ifndef __SERIAL_H__
#define __SERIAL_H__

#include<reg51.h>
// --------------------------------------------------------------- Global variables
#define MAX_BUF_SIZE 32

// ------------------------------------------------------------- Function declaration

void UART_Init(void);
void UART_Transmit_Byte(char ch);
void UART_Transmit_String(char *str);
char UART_Receive_Byte(void);
void UART_Receive_String(void);

#endif