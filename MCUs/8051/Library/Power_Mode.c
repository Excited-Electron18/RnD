#include "Power_Mode.h"

#if POWER_MODE_TEST == 1
// --------------------------------------------------------------- Global variables

// --------------------------------------------------------------- Function definition
void Power_Mode_Init(void)
{
	IT0 = 1;      		
	EX0 = 1;      		    		
	EA  = 1;		
	IP = 1;	
	PCON = 0x00;
}	

void Ext_0_ISR(void) interrupt 0
{
	PCON = 0x00;
}

void Power_Mode_Delay(void)
{
	TMOD = 0x01;
	TH0 = 0x4B;			
	TL0 = 0xFD;		
	TR0 = 1;			
	while(TF0 == 0);		
	TR0 = 0;			
	TF0 = 0;			
}

void Power_Mode_Idle(void)
{
	PCON = 0x01;
}

void Power_Mode_Down(void)
{
	PCON = 0x02;
}

#endif