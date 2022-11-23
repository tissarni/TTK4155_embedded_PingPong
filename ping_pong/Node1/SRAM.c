/*
 * SRAM.c
 *
 * Created: 15.09.2022 13:53:04
 *  Author: titouani
 */ 

#include <avr/io.h>

#include "SRAM.h"

void SRAM_Init()
{
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM0 );
}

void xmem_write ( uint8_t data , uint16_t addr ) {
	volatile char * ext_mem = ( char *) 0x1000 ;
	ext_mem [ addr ]= data;
}

uint8_t xmem_read ( uint16_t addr ) {
	volatile char * ext_mem = ( char *) 0x0000 ;
	uint8_t ret_val = ext_mem [ addr ];
	return ret_val;
}

