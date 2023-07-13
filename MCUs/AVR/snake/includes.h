/*
*********************************************************************************************************
*                                               uC/OS-II
*                                        The Real-Time Kernel
*
*                                          AVR Specific code
*
* File         : INCLUDES.H
* By           : Ole Saether
* Port Version : V1.01
*
* Modifications by Julius Luukko 07-21-2003 (Julius.Luukko@lut.fi) to get this compiled with 
* uC/OS-II 2.52 and 2.70.
*
*********************************************************************************************************
*/
#include <avr/io.h>
#include <avr/signal.h>
#include <avr/interrupt.h>

/* If you have uC/OS-II version below 2.70 uncomment the includes for os_cpu.h and os_cfg.h */
#include  "os_cpu.h"
#include  "os_cfg.h"
#include  <ucos_ii.h>

/* ISR support macros */
#include <avr_isr.h>


