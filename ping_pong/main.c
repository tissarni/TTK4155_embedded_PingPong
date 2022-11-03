/*
 * PingPong.c
 *
 * Created: 05.09.2022 13:08:20
 * Author : floriaca
 */
#define F_CPU 4915200

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "UART.h"
#include "SRAM.h"
#include "tests.h"
#include "SLIDER.h"
#include "ADC.h"
#include "JOYSTICK.h"
#include "OLED.h"
#include "SPI.h"
#include "CAN.h"


#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void)
{
			

	//Drivers init
	UART_Init(MYUBRR);
	SRAM_Init();
	ADC_Init();
	joystick_calibrate();
	OLED_init();
	can_init();
		
	
	//OLED_test();
	//OLED_home();
	//OLED_score();
	//OLED_scenario();
	////Ports setting 
	DDRE = 0b11111111;
    //DDRA = 0b11111111; 
	//DDRD |= 0b11000000;
	//DDRC = DDRC | 0b00001111;
	PORTE = 0b00000010;
	//PORTA = 0b00000000;
	//PORTB = (0<<PB1)|(0<<PB0);	//PORTD = (1<<PD6)|(1<<PD7);
	//PORTC =0b00000000;
	
	//USB_multi_test();
	
	
	//SRAM_test();
	//SRAM_mapping_test();
  
  
	can_message to_send;
	can_message receive;
	to_send.id = 43;
	to_send.length = 8;
	to_send.data[0] = 'B';
	to_send.data[1] = 'I';
	to_send.data[2] = 'E';
	to_send.data[3] = 'R';
	to_send.data[4] = 'E';
	to_send.data[5] = ' ';
	to_send.data[6] = '!';
 	
	 
	
    while (1)
    {
		 printf("TRANSMIT => length :  %d \n\rid : %d \n\rdata : %s \n\r", to_send.length, to_send.id, to_send.data);
		 can_send(&to_send);
		 printf("----------------------------------------------------------------------------------------------------------------------\n\r");
		 receive = can_receive();
		 printf("RECEIVE => length:  %d \n\rid: %d \n\rdata: %s \n\r", receive.length, receive.id, receive.data);
		 
		 printf("----------------------------------------------------------------------------------------------------------------------\n\r");

		
			
		
		
		
		_delay_ms(1000);
    }
}

