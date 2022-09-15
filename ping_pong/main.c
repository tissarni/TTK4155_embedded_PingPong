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

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1




void test_blinking()
{
	PORTB = 0b00000010;
	_delay_ms(1000);
	PORTB = 0b00000000;
	_delay_ms(1000);
	
}

void test_transmit()
{
	UART_Transmit('c');
	_delay_ms(1000);
}

void test_Receive()
{
	UART_Receive();
	_delay_ms(1000);
}

void test_printf() 
{
	printf("Finally\n\r");
}




int main(void)
{
    //DDRB = 0b11111111;  //set PORTB as output
	UART_Init(MYUBRR);
	
	        
    /* Replace with your application code*/
    while (1)
    {
		

		
		
    }
}

