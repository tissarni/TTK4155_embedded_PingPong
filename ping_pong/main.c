/*
 * PingPong.c
 *
 * Created: 05.09.2022 13:08:20
 * Author : floriaca
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART.h"

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






int main(void)
{
    DDRB = 0b11111111;  //set PORTB as output
	UART_Init();
        
    /* Replace with your application code */
    while (1)
    {
		//printf("\nHeLLO\n");
		test_transmit();
		
    }
}

