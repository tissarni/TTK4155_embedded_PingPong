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
	SPI_MasterInit();
	
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
  
    while (1)
    {
		SPI_MasterTransmit('c');
		//_delay_ms(1000);
    }
}

