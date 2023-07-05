#include "./Header/SERIAL.h"

extern char Rx_Buf[MAX_BUF_SIZE];

int main()
{
	char Rx_Val;
	UART_Init();
	UART_Transmit_String("Hello World");
	while(1)
	{
		UART_Transmit_String("\r\n");
		UART_Transmit_String("1. Char Test\r\n");
		UART_Transmit_String("2. String Test\r\n");
		UART_Transmit_String("Enter Your Choice..\r\n");
		Rx_Val = UART_Receive_Byte();
		switch(Rx_Val)
		{
			case '1':
				UART_Transmit_String("Enter Char..\r\n");
				Rx_Val = UART_Receive_Byte();
				UART_Transmit_String("Entered Char : ");
				UART_Transmit_Byte(Rx_Val);
			break;	
			case '2':
				UART_Transmit_String("Enter String (Max 32 Byte)\r\n");
				UART_Receive_String();
				UART_Transmit_String("Entered String : ");
				UART_Transmit_String(Rx_Buf);
			break;
			default:
				UART_Transmit_String("Invalid Choice\r\n");
			break;			
		}
	}
}