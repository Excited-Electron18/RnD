#ifndef __SERIAL_H__
#define __SERIAL_H__

void UART_init(void);
void UART_TX(unsigned int x);
unsigned int UART_RX(void);
void UART_TX_string(char *x);
void UART_4digit(unsigned int x);
 
unsigned char si,j;
char arr[120];

void UART_init(void)
{
	PINSEL0=(1<<0)|(1<<2);
	U0LCR=(1<<0)|(1<<1)|(1<<7);
	U0DLL=97;
	U0LCR=(1<<0)|(1<<1);
	U0IER=(1<<0)|(1<<1);
	U0FCR=(1<<0);
}
void UART_TX(unsigned int x)
{
	U0TER=(1<<7);
	U0THR=x;
	while(!(U0LSR&(1<<5)));
	U0LSR=(1<<5);
}
unsigned int UART_RX(void)
{
	unsigned int x;
	while(!(U0LSR&(1<<0)));
	x=U0RBR;
	U0LSR=(1<<0);
	return x;
}
void UART_TX_string(char *x)
{
	while(*x!='\0')
	{
		UART_TX(*x);
		x++;
	}
}

void UART0_RX_string(void)
{
		j=0;
	while(1)
		{		
			si=UART_RX();
			if(si!='\r')
				{
					arr[j]=si;
				}
			else
				{
					arr[j]='\0';
					break;
				}
			j++;
		} 
}

void UART_4digit(unsigned int x)
{
	unsigned int i1,i2,i3,i4,i5,i6;
	i1=   x/1000;
	i2=   x%1000;
	i3=  i2/100;
	i4=  i2%100;
	i5=  i4/10;
	i6=  i4%10;
	UART_TX(i1+48);
	UART_TX(i3+48);
	UART_TX(i5+48);
	UART_TX(i6+48);
}
#endif
