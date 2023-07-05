#ifndef __DOT_MATRIX_LCD_4BIT_MODE__
#define __DOT_MATRIX_LCD_4BIT_MODE__

// --------------------------------------------------------------- Define Pin Interface
#define LCD_Port P2 // LCD Data Port -- Pin 2.4 to 2.7 for data	

sbit LCD_RS=P2^0; 			// LCD Register Select
sbit LCD_RW=P2^1; 			// LCD Read/Write
sbit LCD_EN=P2^2; 			// LCD Read/Write Enable

// --------------------------------------------------------------- Global variables
#define WR_CMD 0
#define WR_DATA 1

#define CMD_SET_4BIT_MODE			0x02
#define CMD_EN_5x7_MODE				0x28
#define CMD_DISP_ON_CURS_OFF	0x0C
#define CMD_CURS_POS_INC			0x06
#define CMD_CURS_LINE_1				0x80
#define CMD_CURS_LINE_2				0xC0

// --------------------------------------------------------------- Function declaration
void LCD_Init(void);
void LCD_Delay(unsigned int count);
void LCD_Write(unsigned char Wr_Type, unsigned char Wr_Val);
void LCD_Write_String(unsigned char *str);								   

// --------------------------------------------------------------- Function definition
void LCD_Init(void)
{
	LCD_Port=0x00;
	LCD_Write(WR_CMD,CMD_SET_4BIT_MODE);
	LCD_Write(WR_CMD,CMD_EN_5x7_MODE);
	LCD_Write(WR_CMD,CMD_DISP_ON_CURS_OFF);
	LCD_Write(WR_CMD,CMD_CURS_POS_INC);
	LCD_Write(WR_CMD,CMD_CURS_LINE_1);
}
 
void LCD_Write(unsigned char Wr_Type, unsigned char Wr_Val)
{
	char Temp_Val;
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

#endif