#include "./Library/Global.h"
#if TIMER_TEST == 1

#include "./Library/Timer.h"
void TIMER_Test(int Timer_Num)
{
	TIMER_Init();
	if(Timer_Num == 0)
		{
			TIMER0_Delay();	
		}
	else
		{	
			TIMER1_Delay();
		}
}

#endif 