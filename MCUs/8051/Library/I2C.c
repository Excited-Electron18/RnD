#include "I2C.h"

#if I2C_INTERFACE_TEST == 1
void I2C_Init(void)
{
	SDA = 1;
	SCL = 1;
}

void I2C_Start(void)
{
		SDA = 1;
		SCL = 1;
		I2C_Delay(1);
		SDA = 0;
}

void I2C_Restart(void)
{
	SCL = 0;
	SDA = 1;
	SCL = 1;
	SDA = 0;
}

void I2C_Stop(void)
{
		SDA = 0;
		SCL = 1;
		I2C_Delay(1);
		SDA = 1;
}

void I2C_Ack(void)
{
		while(SDA == 0);                  		 // wait until slave releases the SDA line
		SDA = 0;                          		 // pull down the SDA line low and acknowledge slave
		I2C_CLK();                        		 // generate clock signal
		SDA = 1;                          		 // release the SDA line
}

void I2C_Nak(void)
{
	while(SDA == 0);                  		 // wait until slave releases the SDA line
	I2C_CLK();                        		 // generate a clock signal   
}

void I2C_CLK(void)
{
		SCL = 1;
		I2C_Delay(3);
		SCL = 0;
		I2C_Delay(3);
}

void I2C_Write(unsigned char Data)
{
		unsigned char i=0;
		SCL = 0;
		for(i=0;i<8;i++)
		{
			if((Data & 0x80) == 0x80)
			{
				SDA = 1;
			}
			else
			{
				SDA = 0;
			}
			Data <<= 1;
			I2C_CLK();
		}
		// acknowledgement while writing to slave
		SDA = 1;                               	// release the SDA line
		while (SDA == 1);                      	// wait until the slave pull down SDA line low
		I2C_CLK();                       	// generate a clock signal
}


unsigned char I2C_Read(void)
{
		unsigned char i=0;
		unsigned char Rd_Val = 0;
		for(i=0;i<8;i++)
		{
			Rd_Val = Rd_Val<<1;
			if (SDA == 1)
			{
				Rd_Val++;
			}
			I2C_CLK();
		}
		return Rd_Val;
}

void I2C_Delay(unsigned int ms) //delay in milliseconds for 11.0592MHz crystal
{                                            
unsigned int i,j;
for(i=0;i<ms;i++)
	{
	for(j=0;j<110;j++);
	}
}

//	// Read 1 byte form I2C
//char * I2C_Read_Bytes(unsigned int SlaveID,unsigned char Addr,unsigned int NumBytes)
//{
//    I2C_Start();
//		I2C_Send(SlaveID);
//    I2C_Send(Addr);
//		I2C_Start();
//	
//}

//// Write multiple byte to I2C
//void I2C_Write_Bytes(unsigned int SlaveID,char *Bytes,unsigned int NumBytes)
//{
//    I2C_Start();
//    I2C_Send(SlaveID);
//		for(unsigned int i=0,i<NumBytes;i++)
//		{
//			I2C_Send(*Bytes);
//			Bytes++;
//		}
//		I2C_Delay(10);
//		I2C_Stop();
//}

#endif