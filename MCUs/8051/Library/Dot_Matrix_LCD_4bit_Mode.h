#ifndef __DOT_MATRIX_LCD_4BIT_MODE_H__
#define __DOT_MATRIX_LCD_4BIT_MODE_H__
#include "./Library/Global.h"
#include<reg51.h>

#if DOT_MATRIX_LCD_TEST == 1
// --------------------------------------------------------------- Define Pin Interface
#define LCD_Port P2 // LCD Data Port -- Pin 2.4 to 2.7 for data	

sbit LCD_RS=P2^0; 			// LCD Register Select
sbit LCD_RW=P2^1; 			// LCD Read/Write
sbit LCD_EN=P2^2; 			// LCD Read/Write Enable
sbit LCD_D7=P2^7;				// LCD Busy Check Pin

// --------------------------------------------------------------- Global variables
#define WR_CMD 0
#define WR_DATA 1

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	LCD Command MACROS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define LCD_CLEAR 					0x01
#define	SET_4BIT_MODE				0x02
#define DEC_CURSOR 					0x04
#define INC_CURSOR 					0x06
#define DISP_OFF_CUR_OFF 		0x08
#define DISP_OFF_CUR_ON 		0x0A
#define DISP_ON_CUR_OFF 		0x0C
#define DISP_ON_CUR_BLINK 	0x0E
#define SHIFT_CUR_LEFT 			0x10
#define SHIFT_CUR_RIGHT 		0x14
#define SHIFT_DISP_LEFT 		0x18
#define SHIFT_DISP_RIGHT 		0x1C
#define EN_5x7_MODE					0x28
#define RETURN_HOME 				0x80
#define CURS_LINE_1					0x80
#define CURS_LINE_2					0xC0

// --------------------------------------------------------------- Function declaration
void LCD_Init(void);
void LCD_Delay(unsigned int count);
void LCD_Write(unsigned char Wr_Type, unsigned char Wr_Val);
void LCD_Write_String(unsigned char *str);		
void LCD_Busy_Check(void);

#endif

#endif