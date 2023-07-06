#ifndef __EXT_INTERRUPT_H__
#define __EXT_INTERRUPT_H__

#include "./Library/Global.h"
#include<reg51.h>


#if EXT_INTERRUPT_TEST == 1
	void Ext_Interrupt_Init();
	void Ext_0_ISR(void);
	void Ext_1_ISR(void);
#endif


#endif