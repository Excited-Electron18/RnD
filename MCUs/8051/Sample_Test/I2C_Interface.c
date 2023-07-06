#include "./Library/I2C.h"

#if I2C_INTERFACE_TEST == 1

char Temp_Val[2];
int Final_Val;
void Setup_Temp_Sensor(void);
void Read_Temp(void);
void send(char command_code);
void send_write(unsigned char command_code, unsigned char value);
void receive(char command_code);
void Convert_Temp(void);

void I2C_Interface_Test(void)
{
	I2C_Init();
	Setup_Temp_Sensor();
	while(1)
	{
		Read_Temp();
		Convert_Temp();
		I2C_Delay(1000);
	}
}

//==================================================
void Setup_Temp_Sensor(void)
{
	send_write(0xac,0x03);     						 // Setting configuration register
	I2C_Delay(2);
	send_write(0xa1,0x32);     						 // Setting higher temperature limit       
	I2C_Delay(2);
	send_write(0xa2,0x30);							// Setting lower temperature limit
	I2C_Delay(2);
	send(0xee);	             						 // Start temperature conversion
	I2C_Delay(10);
}	

void Read_Temp(void)
{
		send(0xee);								// Start temperature conversion
		I2C_Delay(2);
		receive(0xaa);							// Read converted temperature
}

void send(char command_code)
{
	I2C_Start();
	I2C_Write(0x90);                      		 // device id
	I2C_Write(command_code);
	I2C_Stop();
}

void send_write(unsigned char command_code, unsigned char value)
{
	I2C_Start();
	I2C_Write(0x90);
	I2C_Write(command_code);
	I2C_Write(value);
	I2C_Delay(10);
	I2C_Stop();
}

void receive(char command_code)
{
	I2C_Start();
	I2C_Write(0x90);
	I2C_Write(command_code);
	I2C_Start();
	I2C_Write(0x91);
	Temp_Val[1] = I2C_Read();
	I2C_Ack();
	Temp_Val[2] = I2C_Read();
	I2C_Nak();
	I2C_Stop();
}

void Convert_Temp(void)
{
	char i=2;
	unsigned char arr_disp[3];
	
	if ((Temp_Val[1] & 0x80) == 0x80) // -ve Temp Value 
	{
		Temp_Val[1] = ~(Temp_Val[1]);
		Temp_Val[1] = Temp_Val[1] + 1;       // 2's complement
	}
	else															// +ve Temp Value
	{
		Temp_Val[1] = Temp_Val[1] & 0x7F;
	}

	while (i>=0)
	{
		arr_disp[i] = Temp_Val[1]%10;
		Temp_Val[1] = Temp_Val[1]/10;
		i--;
	}
	Final_Val=arr_disp[1]*10+arr_disp[2];
}

#endif