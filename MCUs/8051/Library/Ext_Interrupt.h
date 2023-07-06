#ifndef __EXT_INTERRUPT_H__
#define __EXT_INTERRUPT_H__

#include "./Library/Global.h"
#include<reg51.h>


#if EXT_INTERRUPT_TEST == 1
	void Ext_Interrupt_Init();
	void Ext_Interrupt_1(void);
	void Ext_Interrupt_2(void);
#endif


#endif