
#include "serial.h"
#define trig1 	(1<<2)
#define echo1 	(1<<3)


unsigned int sense_0;
unsigned int RX1,count1,distance1;
void timer0(void);
void timer1(unsigned int x);
unsigned int ultrasonic1(void);

int main()
{	
	UART_init();
	IO0DIR|=trig1;
	timer0();

	while(1)
	{
			sense_0=ultrasonic1();
			UART_TX_string("Distance : ");
			LCD_digit(sense_0);
			UART_TX_string(" Meter");
	}
}

void timer0(void)
{
  T0TCR=(1<<1); 					
  T0MR0=15000000;
  T0CTCR=0X00; 						
  T0MCR|=(1<<0)|(1<<1); 						
}

void timer1(unsigned int x)
{
  T1TCR=(1<<1); 					
  T1MR0=x;
  T1CTCR=0X00; 						
  T1MCR|=(1<<0)|(1<<1); 		
  T1TCR=(1<<0);
  while(!(T1IR&(1<<0)));	
  T1IR|=(1<<0); 						
  T1TCR&=~(1<<0); 				
}

unsigned int ultrasonic1(void)
{
 	IOSET0|=trig1;				// send trigger pulse
	timer1(150);
	IOCLR0|=trig1;	
	T0TC=0;
	IO0PIN&=~echo1;
	do 							// wait till echo
	{
		RX1=IO0PIN&echo1;
	}while(RX1!=echo1);
	
	T0TCR=(1<<0);		   		// start timer at echo
	
	do					   		// wait till echo off
	{
		RX1=IO0PIN&echo1;
	}while(RX1==echo1);
		
	count1=T0TC;			   		// get timer value
	T0TCR&=~((1<<0)|(1<<1));	// reset timer
	if(count1<15000*40)
	 	{		
	 		distance1=count1*1105*0.000001;
 		}
return distance1;
}	
