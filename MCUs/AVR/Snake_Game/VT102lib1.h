#ifndef VT102LIB1_H

#define VT102LIB1_H

#include<myUART.h>

#define  COLOR_BLACK     0                       /* VT102 Color Codes                                  */
#define  COLOR_RED       1
#define  COLOR_GREEN     2
#define  COLOR_BROWN     3
#define  COLOR_BLUE      4
#define  COLOR_MAGENTA   5
#define  COLOR_CYAN      6
#define  COLOR_WHITE     7

//OS_EVENT       *pSem; //This semaphore is meant to guard UART related VT library 

void VT102Attribute (unsigned char fgcolor, unsigned char bgcolor)
{
    UART_Transmit_char(0x1b);
    UART_Transmit_char('[');
    UART_Transmit_num(30 + fgcolor);
    UART_Transmit_char(';');
    UART_Transmit_num(40 + bgcolor);
    UART_Transmit_char('m');
}


void VT102DispStr (unsigned char x, unsigned char y, unsigned char *s, unsigned char fgcolor, unsigned char bgcolor)
{
//    unsigned char err;
//    OSSemPend(pSem, 0, &err);
    VT102Attribute(fgcolor, bgcolor);
    UART_Transmit_char(0x1B);
    UART_Transmit_char('[');
    UART_Transmit_num(y);
    UART_Transmit_char(';');
    UART_Transmit_num(x);
    UART_Transmit_char('H');
    UART_Transmit_string(s);
//    OSSemPost(pSem);
}


void VT102DispClrScr (void)
{
//    unsigned char err;
//    OSSemPend(pSem, 0, &err);
    VT102Attribute(COLOR_RED,COLOR_BLUE);
    UART_Transmit_string("\x1B[2J");
//    OSSemPost(pSem);
}

void VT102DispChar (unsigned char x, unsigned char y, unsigned char c, unsigned char fgcolor, unsigned char bgcolor)
{
//    unsigned char err;
//    OSSemPend(pSem, 0, &err);
    VT102Attribute(fgcolor, bgcolor);
    UART_Transmit_char(0x1B);
    UART_Transmit_char('[');
    UART_Transmit_num(y);
    UART_Transmit_char(';');
    UART_Transmit_num(x);
    UART_Transmit_char('H');
    UART_Transmit_char(c);
//    OSSemPost(pSem);
}

#endif
