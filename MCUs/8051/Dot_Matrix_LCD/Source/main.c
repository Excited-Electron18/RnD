#include "./Header/Dot_Matrix_LCD_4bit_Mode.h"

int main()
{
	LCD_Init();
	while(1)
	{
		LCD_Write_String("Hello World");
	}
}