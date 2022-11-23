/*
 * ADC.c
 *
 * Created: 22.09.2022 14:59:29
 *  Author: titouani
 */ 
#include <avr/io.h>
#include <util/delay.h>

#include "ADC.h"

void ADC_Init() {
	DDRB = (1 << DDB1);
	OCR2 = 128;
	TCCR2 |= (1 << COM21);
	TCCR2 |= (1 << WGM21) | (1 << WGM20);
	TCCR2 |= (1 << CS20);
}

int ADC_Read (int channel) {
	volatile char * ext_mem = ( char *) 0x0000 ;
	ext_mem [ 0x1400 ]= 1;
	int Tconv = (9*4*2)/4912000;
	_delay_ms(Tconv);

	int  value=0;
	
	for (int i=0;i<4;i++){
		uint8_t  read = ext_mem[0x1400];
		_delay_ms(0.18);
		if (i == channel){
			 value = read;
		}
	}
	return value;
}
