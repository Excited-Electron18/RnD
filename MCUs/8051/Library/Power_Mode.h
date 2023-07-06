#ifndef __POWER_MODE_H__
#define __POWER_MODE_H__

#include<reg51.h>
#include "./Library/Global.h"

#if POWER_MODE_TEST == 1
// --------------------------------------------------------------- Global variables


// ------------------------------------------------------------- Function declaration

void Power_Mode_Init(void);
void Ext_0_ISR(void);
void Power_Mode_Delay(void);
void Power_Mode_Idle(void);
void Power_Mode_Down(void);

#endif
#endif