#include "./Header/Ext_Interrupt.h"

extern unsigned char count;

int main()
{
	Ext_Interrupt_Init();
	while(1)
	{
		P2 = count;
	}
}