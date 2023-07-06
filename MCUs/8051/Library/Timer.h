#ifndef __TIMER_H__
#define __TIMER_H__

#include<reg51.h>
#include "./Library/Global.h"

#if TIMER_TEST == 1
// --------------------------------------------------------------- Global variables


// ------------------------------------------------------------- Function declaration

void TIMER_Init(void);
void TIMER0_Delay(void);
void TIMER1_Delay(void);

#endif
#endif