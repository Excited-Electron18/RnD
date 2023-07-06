#include "./Library/Global.h"
#if POWER_MODE_TEST == 1

#include "./Library/Power_Mode.h"

void POWER_Mode_Test(void)
{
	int count = 0;
	Power_Mode_Init();
	while(1)
	{
	count++;
	P2 = count;
	Power_Mode_Delay();
		if(count==100)
		{
			Power_Mode_Idle(); // Idle Mode triggered , External Interrupt 0 required to move out of Idle Mode 
		}
		if(count==200)
		{
			Power_Mode_Down(); // Power Down Mode triggered , Reset required to move out of Power Down Mode
		}
	}
}

#endif 