/*
 * UART1.C
 *
 * Created: 07.09.2022 17:47:35
 *  Author: titouani
 */ 

#include <avr/io.h>
#include "UART.h"


#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void UART_Init()
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(MYUBRR);
	UBRR0L = (unsigned char)MYUBRR;
	/* Enable receiver and transmitter */
	UCSR0C = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}

void UART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}


unsigned char UART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}