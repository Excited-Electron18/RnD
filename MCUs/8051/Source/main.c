#include "./Library/Global.h"

int main()
{
	#if DOT_MATRIX_LCD_TEST == 1
		Dot_Matrix_LCD_Test();
	#elif EXT_INTERRUPT_TEST == 1
		Ext_Interrupt_Test();
	#elif I2C_INTERFACE_TEST == 1
		I2C_Interface_Test();
	#elif UART_TEST == 1
		UART_Test();
	#elif POWER_MODE_TEST == 1
		POWER_Mode_Test();
	#elif TIMER_TEST == 1
		TIMER_Test(0);
	#elif SPI_INTERFACE_TEST == 1
		SPI_Interface_Test();
	#endif
	
	while(1);
}

