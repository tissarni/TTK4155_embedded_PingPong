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
}


