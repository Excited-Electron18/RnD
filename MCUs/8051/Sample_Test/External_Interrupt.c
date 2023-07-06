#include "./Library/Global.h"
#if EXT_INTERRUPT_TEST == 1
#include "./Library/Ext_Interrupt.h"

extern unsigned char count;

void Ext_Interrupt_Test(void)
{
	Ext_Interrupt_Init();
	while(1)
	{
		P2 = count;
	}
}
#endif