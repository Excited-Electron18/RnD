

// Snake game........



#include<avr/io.h>
#include<includes.h>
#include<VT102lib1.h>
#include<util/delay.h>
#include<LCD_mega128.h>

/***********************************************************************************************************
* - If the selected MCU does not have enough internal SRAM and no external memory interface,
* notify the user.
* - Define the value of TCCR0, which sets the clock divider to 1024 for timer0
***********************************************************************************************************/

#if defined(__AVR_AT90S2313__) || defined(__AVR_AT90S2333__) || defined(__AVR_AT90S4433__) || \
        defined(__AVR_AT90S4434__) || defined(__AVR_AT90S8535__) || defined(___AVR_ATmega8535__)
# error "Your MCU probably does not have enough SRAM to run this program"
#elif defined(__AVR_AT90S4414__) 
# error "Your MCU probably does not have enough program memory to run this program"
#elif defined(__AVR_AT90S8515__) || \
       defined(__AVR_ATmega161__) || defined(__AVR_ATmega162__) || defined(__AVR_ATmega163__) || \
       defined(___AVR_ATmega8515__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) || \
       defined(__AVR_ATmega8__)
#   define TCCR0VAL (_BV(CS02) | _BV(CS00))
#elif defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__) || defined(__AVR_ATmega103__)
#   define TCCR0VAL (_BV(CS02) | _BV(CS01) | _BV(CS00))
#else
#  error "Don't know what kind of MCU you are compiling for"
#endif
/************************************************************************************************************/
    


#define STACKSIZE 100														// CONSTANTS

void movement( void *Data1);

void food( void *Data2);

void score( void *Data3);
	OS_STK task_stack1[STACKSIZE];   											// GLOBAL VARIABLES

OS_STK task_stack2[STACKSIZE]; 

OS_STK task_stack3[STACKSIZE]; 

int main()
{

	UART_config(9600);

	VT102DispClrScr ();

	OSInit(); 																// initializes the idle and statistical task
		
	OSTaskCreate( movement, (void *)0, &task_stack1[STACKSIZE - 1 ], 0);

	OSTaskCreate( food, (void *)0, &task_stack1[STACKSIZE - 1 ], 0);

	OSTaskCreate( score, (void *)0, &task_stack1[STACKSIZE - 1 ], 0);

	OSStart(); 																// start the scheduler	

}



void movement( void *Data1)
{

	unsigned int adcRead=0;   
	char arr[4]={};
	int count=4,i;                                         

	ADCSRA=0x87;        					//selecting reference voltage,result right aligned,ADC! selected

	ADCSRA |=(1<<ADSC);  					//ADCEN,prescaler:128 adcclk=(16M/128)= 12kHz
	ADCSRA |=(1<<ADFR);

 
	while(1)
		{

			ADMUX=0xC1;         					//initialize ADC for channel 0
         	
			ADCSRA |=(1<<ADSC);    
			
			while(!(ADCSRA & (1<<ADIF)));     		//wait till conversion is completed

			adcRead=ADCL;  

			adcRead+=(ADCH<<8);

				while(count)
					{
	 				arr[count-1]=adcRead%10;
	  	 			adcRead=adcRead/10;
	   				count--;
					}
				count=4;

						UART_Transmit_string("X >> " );

				for(i=0;i<count;i++)

					{

						UART_Transmit_num(arr[i]+0x30);
		
					}  
					_delay_ms(500);		
					UART_Transmit_string("\n");



			ADMUX=0xC2;         					//initialize ADC for channel 1

			ADCSRA |=(1<<ADSC);    
			
			while(!(ADCSRA & (1<<ADIF)));     		//wait till conversion is completed

			adcRead=ADCL; 

			adcRead+=(ADCH<<8);

				while(count)
					{
	 					arr[count-1]=adcRead%10;
	  	 				adcRead=adcRead/10;
	   					count--;
					}
				count=4;

						UART_Transmit_string("Y >> " );

				for(i=0;i<count;i++)

					{

						UART_Transmit_num(arr[i]+0x30);

					} 
					_delay_ms(500);		
					UART_Transmit_string("\n");
		
		}		
		
}




