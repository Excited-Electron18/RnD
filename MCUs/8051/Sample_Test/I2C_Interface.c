#include "./Library/I2C.h"


#if I2C_INTERFACE_TEST == 1 && I2C_TEMP_SENSOR_TEST == 1

#elif I2C_INTERFACE_TEST == 1 && I2C_FLASH_MEMORY_TEST == 1
char WR_Data[4]="ABCD";
char RD_Data[4];
int i=0;
void ReadBYTE(unsigned int Addr);
void WriteBYTE(unsigned int Addr);

sbit LED=P1^0;
#endif

#if I2C_INTERFACE_TEST == 1


void I2C_Interface_Test(void)
{
	I2C_Init();
	#if I2C_TEMP_SENSOR_TEST == 1
	Setup_Temp_Sensor();
	while(1)
	{
		Read_Temp();
		Convert_Temp();
		I2C_Delay(1000);
	}
	#elif I2C_FLASH_MEMORY_TEST == 1

	  WriteBYTE(0x0000);
    I2C_Write(WR_Data[0]);        //Write Data's Here
    I2C_Write(WR_Data[1]);
    I2C_Write(WR_Data[2]);
    I2C_Write(WR_Data[3]);   
    I2C_Stop(); 
    I2C_Delay(10);
    ReadBYTE(0x0000);
    RD_Data[0] = I2C_Read();   
    RD_Data[1] = I2C_Read();   
    RD_Data[2] = I2C_Read();   
    RD_Data[3] = I2C_Read();   
		for(i=0;i<4;i++)
		{
			if(WR_Data[i]==RD_Data[i])
			{
				LED = 0;
			}
			else
			{
				LED = 1;
			}
		}
	#endif
}

#if I2C_TEMP_SENSOR_TEST == 1
char Temp_Val[2];
int Final_Val;

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

#elif I2C_FLASH_MEMORY_TEST == 1

// Read 1 byte form I2C
void ReadBYTE(unsigned int Addr)
{
    I2C_Start();
    I2C_Write(0xA0);
    I2C_Write((unsigned char)(Addr>>8)&0xFF);
    I2C_Write((unsigned char)Addr&0xFF);
}

// Write 1 byte to I2C
void WriteBYTE(unsigned int Addr)
{
    I2C_Start();
    I2C_Write(0xA0);
    I2C_Write((unsigned char)(Addr>>8)&0xFF);    // send address high
    I2C_Write((unsigned char)Addr&0xFF);             // send address low
}


#endif
#endif