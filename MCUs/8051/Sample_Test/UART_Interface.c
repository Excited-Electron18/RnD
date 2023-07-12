#include "./Library/Global.h"
#include "./Library/UART.h"

#if UART_TEST == 1
extern char Rx_Buf[MAX_BUF_SIZE];

//====================================== GSM Module Interface
int Check_OK(void)
{
		UART_Receive_String();
		if((Rx_Buf[0]=='O')&&(Rx_Buf[1]=='K'))
			{
				Rx_Buf[0]='\0';
				return 1;
			}
		else
			{
				Rx_Buf[0]='\0';
	 			return 0;
			}
}

void SMS_send(void)
{	
			int Check_Count=0;
			do
			{
					UART_Transmit_String("AT\r\0"); 												// connection check
					UART_Delay(1000);
					Check_Count++;
					if(Check_Count>=5)
						goto EXIT;
			}while(Check_OK()!=1);
			Check_Count=0;
			do
			{
					UART_Transmit_String("AT+CMGF=1\r\0");  								// check modem is working or not
					UART_Delay(1000);
					Check_Count++;
					if(Check_Count>=5)
						goto EXIT;
			}while(Check_OK()!=1);
			
			UART_Transmit_String("AT+CMGS=XXXXXXXXXX\r\0"); 						// Change XXXXXXXXXX to Mobile Number on which you want to send sms
			UART_Transmit_String("Hello! Richard Parker. \r\0"); 				// sms 
			UART_Transmit_Byte(0x1A);
		EXIT:
			UART_Delay(1000);
}


void UART_Test(void)
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



#endif