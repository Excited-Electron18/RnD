#ifndef __I2C_H__
#define __I2C_H__

#include<reg51.h>
#include "./Library/Global.h"

#if I2C_INTERFACE_TEST == 1

sbit SDA=P1^2;
sbit SCL=P1^3;

void I2C_Init(void);
void I2C_Start(void);
void I2C_Restart(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_Nak(void);
void I2C_CLK(void);
void I2C_Write(unsigned char Data);
unsigned char I2C_Read(void);
void I2C_Delay(unsigned int ms);

#endif

#endif