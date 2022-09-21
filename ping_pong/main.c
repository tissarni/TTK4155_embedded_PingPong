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

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void)
{
	//Drivers init
	UART_Init(MYUBRR);
	SRAM_Init();
	
	//Ports setting 
	DDRE = 0b11111111;
    DDRA = 0b11111111;  
	//DDRC = DDRC | 0b00001111;
	PORTE = 0b00000010;
	PORTA = 0b00000000;
	//PORTC =0b00000000;
	
	
	
	//SRAM_test();
 	SRAM_mapping_test();
	        
    
    /*while (1)
    {
		
    }*/
}

