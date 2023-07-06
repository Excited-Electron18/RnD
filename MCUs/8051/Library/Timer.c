#include "TIMER.h"

#if TIMER_TEST == 1
// --------------------------------------------------------------- Global variables
sbit LED = P1^7;
// --------------------------------------------------------------- Function definition
void TIMER_Init(void)
{
  TMOD=0x11; 
}

void TIMER0_Delay(void)
{
  TH0=0x4B; // for 50 Ms at 11.0592 MHz
  TL0=0xFD;
	TR0=1;
	ET0= 1;           
	EA = 1;          
}	

void TIMER1_Delay(void)
{
	TH1=0x3C; // for 50 Ms at 12 MHz
	TL1=0xB0;
	TR1=1;
	ET1= 1;           
	EA = 1;  
}

void TIMER0_ISR() interrupt 1
{
    TH0 = 0X4B;       
    TL0 = 0XFD;
		LED=~LED;	
}

void TIMER1_ISR() interrupt 3
{
    TH1 = 0X3C;       
    TL1 = 0XB0;
		LED=~LED;	
}


#endif