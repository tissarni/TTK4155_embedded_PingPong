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
#include <avr/interrupt.h>

#include "UART.h"
#include "SRAM.h"
#include "tests.h"
#include "SLIDER.h"
#include "ADC.h"
#include "JOYSTICK.h"
#include "OLED.h"
#include "SPI.h"
#include "CAN.h"
#include "mcp2515.h"


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
	//DDRE = 0b11111111;
    //DDRA = 0b11111111; 
	//DDRD |= 0b11000000;
	//DDRC = DDRC | 0b00001111;
	PORTE = 0b00000010;
	//PORTA = 0b00000000;
	//PORTB = (0<<PB1)|(0<<PB0);	//PORTD = (1<<PD6)|(1<<PD7);
	//PORTC =0b00000000;
	
	DDRE &= ~(1 << PE0);
	GICR &= 0b00000111;
	EMCUCR &= ~(1 << ISC2);
	GIFR |= (1 << INTF2);
	//GICR |= (1 << INT2);
	sei();

	
	
	
	//USB_multi_test();
	
	
	//SRAM_test();
	//SRAM_mapping_test();
  
  
	can_message to_send;
	can_message received;
	int i = 0;
	to_send.length=3;
	to_send.id = 54;

	
    while (1)
    {
		 //printf("TRANSMIT => length :  %d \n\rid : %d \n\rdata : %s \n\r", to_send.length, to_send.id, to_send.data);
		 //can_send(&to_send);
		 //printf("----------------------------------------------------------------------------------------------------------------------\n\r");
		 //receive = can_receive();
		 //printf("RECEIVE => length:  %d \n\rid: %d \n\rdata: %s \n\r", receive.length, receive.id, receive.data);
		 
		 //printf("----------------------------------------------------------------------------------------------------------------------\n\r");
		joystick_pos pos;
		i++;
		pos = get_joystick_pos();
		//to_send.id = 12;
		//to_send.length = 1;
		to_send.data[0] = pos.y;
		//to_send.data[0] = pos.x;
		//to_send.data[0] = pos.y;
		to_send.data[1] = pos.x;
		to_send.data[2] = pos.dir;
		
		can_send(&to_send);
		//send_joystick_pos(&to_send);
			
		printf("Vertical : %d      Horizontal  %d   DIR : %s \r\n LENGHT : %d     ID : %d \r\n", to_send.data[0], to_send.data[1], (to_send.data[2] == RIGHT) ? "rigth" : "de lamerde", to_send.length, to_send.id);
		_delay_ms(100);
		
		//received = can_receive();
		
		
		
		
		/*to_send.data[1] = 1;
		can_send(&to_send);
		printf("Vertical 1 : %d  \n\r", to_send.data[1]);
		_delay_ms(1000);
		printf("RECEIVE 1 : %d \n\r", can_receive().data[1]);
		_delay_ms(1000);
		
		to_send.data[1] = 2;
		printf("Vertical 2 : %d  \n\r", to_send.data[1]);
		can_send(&to_send);
		_delay_ms(1000);
		printf("RECEIVE 2 : %d \n\r", can_receive().data[1]);
		_delay_ms(1000);
		
		to_send.data[1] = 3;
		printf("Vertical 3 : %d  \n\r", to_send.data[1]);
		can_send(&to_send);
		_delay_ms(1000);
		printf("RECEIVE 3 : %d \n\r", can_receive().data[1]);
		_delay_ms(1000);
		
		to_send.data[1] =4;
		printf("Vertical 4 : %d  \n\r", to_send.data[1]);
		can_send(&to_send);
		_delay_ms(1000);
		printf("RECEIVE 4 : %d \n\r", can_receive().data[1]);
		_delay_ms(1000);*/
		
		
		
		//_delay_ms(5000);
    }
}

