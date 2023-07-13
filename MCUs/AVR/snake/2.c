//convert X-axis of joystick and send its respective voltage using UART


#include<avr/io.h>
#include<util/delay.h>
#include<LCD_mega128.h>
#include<myUART.h>

void VT102Attribute (unsigned char fgcolor, unsigned char bgcolor);
void VT102DispStr (unsigned char x, unsigned char y, unsigned char *s, unsigned char fgcolor, unsigned char bgcolor);
void VT102DispClrScr (void);
void VT102DispChar (unsigned char x, unsigned char y, unsigned char c, unsigned char fgcolor, unsigned char bgcolor);


#define  COLOR_BLACK     0                       /* VT102 Color Codes */
#define  COLOR_RED       1
#define  COLOR_GREEN     2
#define  COLOR_BROWN     3
#define  COLOR_BLUE      4
#define  COLOR_MAGENTA   5
#define  COLOR_CYAN      6
#define  COLOR_WHITE     7


int main(void)
{

	unsigned int adcRead=0; 
  
	unsigned char arr[4]={},i=40,j=20,x;
	int count=4;  

 	UART_config(9600); 

	VT102DispClrScr ();                                      

	ADCSRA=0x87;        					//selecting reference voltage,result right aligned,ADC! selected

	ADCSRA |=(1<<ADSC);  					//ADCEN,prescaler:128 adcclk=(16M/128)= 12kHz
	ADCSRA |=(1<<ADFR);

 
	while(1)
		{

			ADMUX=0xC1;         					//initialize ADC for channel X
         	
			ADCSRA |=(1<<ADSC);    
			
			while(!(ADCSRA & (1<<ADIF)));     		//wait till conversion is completed

			adcRead=ADCL;  

			adcRead+=(ADCH<<8);

			x=adcRead+0x30;

			if(x=5)
				{
 					VT102DispStr (i,j,"*", 0, 7);
 				}
			else if(x>5)
				{
					VT102DispStr (i,j,"*", 0, 7);
					i--;
				}
			else
				{
					VT102DispStr (i,j,"*", 0, 7);
					i++;
				}
			_delay_ms(500);					
		
		}	

}


void VT102Attribute (unsigned char fgcolor, unsigned char bgcolor)
{
    UART_Transmit_char(0x1b);
    UART_Transmit_char('[');
    UART_Transmit_num(30 + fgcolor);
    UART_Transmit_char(';');
    UART_Transmit_num(40 + bgcolor);
    UART_Transmit_char('m');
}


void VT102DispStr (unsigned char x, unsigned char y, unsigned char *s, unsigned char fgcolor, unsigned char bgcolor)
{
    VT102Attribute(fgcolor, bgcolor);
    UART_Transmit_char(0x1B);
    UART_Transmit_char('[');
    UART_Transmit_num(y);
    UART_Transmit_char(';');
    UART_Transmit_num(x);
    UART_Transmit_char('H');
    UART_Transmit_string(s);
}


void VT102DispClrScr (void)
{
    VT102Attribute(COLOR_RED,COLOR_BLUE);
    UART_Transmit_string("\x1B[2J");
}

void VT102DispChar (unsigned char x, unsigned char y, unsigned char c, unsigned char fgcolor, unsigned char bgcolor)
{	
	VT102DispClrScr ();
    VT102Attribute(fgcolor, bgcolor);
    UART_Transmit_char(0x1B);
    UART_Transmit_char('[');
    UART_Transmit_num(y);
    UART_Transmit_char(';');
    UART_Transmit_num(x);
    UART_Transmit_char('H');
    UART_Transmit_char(c);
}

