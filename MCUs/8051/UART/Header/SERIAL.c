#include "SERIAL.h"

// --------------------------------------------------------------- Global variables
char Rx_Buf[MAX_BUF_SIZE];
unsigned int Rx_Len=0;

// --------------------------------------------------------------- Function definition
void UART_Init(void)
{
	TMOD=0x20; // settings for 9600 Baudrate with 11.0592 MHz Crystal Oscillator 
	SCON=0x50;
	TL1=0xFD;
	TH1=0xFD;
	TR1=1;
}

void UART_Transmit_Byte(char ch)
{
	SBUF=ch;
	while(!TI);
	TI=0;
}

void UART_Transmit_String(char *str)
{
	while(*str!='\0')
	{
		UART_Transmit_Byte(*str);
		str++; 
	}
}	

char UART_Receive_Byte(void)
{
	unsigned char ch;
	while(RI!=1);
	ch=SBUF;
	RI=0;
	return ch;
}

void UART_Receive_String(void)
{
	char ch;
	Rx_Len=0;
	while(1)
		{		
			ch=UART_Receive_Byte();
			if((ch!='\r') && (ch!='\n'))
				{
					Rx_Buf[Rx_Len]=ch;
				}
			else
				{
					Rx_Buf[Rx_Len]='\0';
					break;
				}
			Rx_Len++;
			if(Rx_Len>=MAX_BUF_SIZE)
					break;
		}
}