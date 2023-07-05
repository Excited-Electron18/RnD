#include "Dot_Matrix_LCD_4bit_Mode.h"

// --------------------------------------------------------------- Function definition
void LCD_Init(void)
{
	LCD_Port=0x00;
	LCD_Write(WR_CMD,SET_4BIT_MODE);
	LCD_Write(WR_CMD,EN_5x7_MODE);
	LCD_Write(WR_CMD,DISP_ON_CUR_OFF);
	LCD_Write(WR_CMD,INC_CURSOR);
	LCD_Write(WR_CMD,CURS_LINE_1);
}
 
void LCD_Write(unsigned char Wr_Type, unsigned char Wr_Val)
{
	char Temp_Val;
	LCD_Busy_Check();
	LCD_Port &= 0x0F;
	LCD_RS = Wr_Type;
	LCD_RW=0;
	Temp_Val=(Wr_Val & 0xF0);
	LCD_Port |= Temp_Val;	  //mask lower nibble because PA4-PA7 pins are used
	LCD_EN = 1;
	LCD_Delay(5);
	LCD_EN = 0;
 
	LCD_Port &= 0x0F;
	Temp_Val =((Wr_Val<<4) & 0xF0);
	LCD_Port |= Temp_Val;	 //shift 4-bit and mask
	LCD_EN = 1;
	LCD_Delay(5);
	LCD_EN = 0;
}

void LCD_Delay(unsigned int count)
{
	unsigned int i,j;
	for(i=0;i<count;i++)
	{
		for(j=0;j<1200;j++);
	}
}

void LCD_Write_String(unsigned char *str)
{
	while(*str!='\0')
	{
		LCD_Write(WR_DATA,*str);
		str++; 
	}
}

void LCD_Busy_Check(void)
{
	LCD_D7=1;
	LCD_RS=0;
	LCD_RW=1;
	while(LCD_D7!=0)
	{
		LCD_EN=0;
		LCD_EN=1;
	}
}