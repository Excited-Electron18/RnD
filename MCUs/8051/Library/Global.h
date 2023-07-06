#ifndef __GLOBAL_H__
#define __GLOBAL_H__

//======================= Features
#define EXT_INTERRUPT_TEST 0
#define UART_TEST 0
#define TIMER_TEST 0 			// TBD
#define POWER_MODE_TEST 0 // TBD


//======================= HW Interface
#define DOT_MATRIX_LCD_TEST 0
#define I2C_INTERFACE_TEST 0
#define SPI_INTERFACE_TEST 0


//======================= Test Functions
void Ext_Interrupt_Test(void);
void UART_Test(void);
void TIMER_Test(void);
void POWER_Mode_Test(void);

void Dot_Matrix_LCD_Test(void);
void I2C_Interface_Test(void);
void SPI_Interface_Test(void);


#endif