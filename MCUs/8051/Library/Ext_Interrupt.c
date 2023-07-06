#include "Ext_Interrupt.h"

#if EXT_INTERRUPT_TEST == 1
unsigned char count=0;

void Ext_Interrupt_Init()
{
	EA=1;
	EX0=1;
	IT0=1;
	EX1=1;
	IT1=1;
}

void Ext_0_ISR(void) interrupt 0
{
	count++;
}

void Ext_1_ISR(void) interrupt 2
{ 
	count--;
}
#endif