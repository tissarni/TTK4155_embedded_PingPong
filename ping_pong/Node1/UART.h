/*
 * UART1.h
 *
 * Created: 07.09.2022 17:48:28
 *  Author: titouani
 */ 


#ifndef UART_H_
#define UART_H_

void UART_Init(unsigned int my_ubrr);
void UART_Transmit( unsigned char data );
unsigned char UART_Receive( void );

#endif /* UART_H_ */