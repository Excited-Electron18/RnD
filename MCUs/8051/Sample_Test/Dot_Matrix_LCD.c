#include "./Library/Global.h"
#if DOT_MATRIX_LCD_TEST == 1

#include "./Library/Dot_Matrix_LCD_4bit_Mode.h"

void Dot_Matrix_LCD_Test(void)
{
	LCD_Init();
	while(1)
	{
		LCD_Write_String("Hello World");
	}
}

#endif 