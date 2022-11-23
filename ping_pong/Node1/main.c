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
	
	PORTE = 0b00000010;
	
	DDRE &= ~(1 << PE0);
	GICR &= 0b00000111;
	EMCUCR &= ~(1 << ISC2);
	GIFR |= (1 << INTF2);
	sei();


	//OLED_test();
	//OLED_home();
	//OLED_score();
	//OLED_scenario();
	//USB_multi_test();
	//SRAM_test();
	//SRAM_mapping_test();

  
	can_message to_send;
	can_message received;
	int i = 0;
	to_send.length=4;
	to_send.id = 54;

	
    while (1)
    {
		joystick_pos pos;
		
		pos = get_joystick_pos();
		pos.button = joystick_button();
	
		to_send.data[0] = pos.y;
		to_send.data[1] = pos.x;
		to_send.data[2] = pos.dir;
		to_send.data[3] = pos.button;
		
		printf("Vertical %d       Horizontal %d     DIRECTION : %d \r\n", to_send.data[0], to_send.data[1], to_send.data[2]);
		
		can_send(&to_send);
			
		_delay_ms(100);
    }
}

