/*
 * SLIDER.c
 *
 * Created: 22.09.2022 15:00:36
 *  Author: titouani
 */ 


#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

#include "SLIDER.h"

int Left_Button(){
	// PORTB6 -> PORTD2
	int x = 0;
	if ((PIND & 0b0000100) == 0b00000100){
		x = 1;
		printf("Left button \r\n");
	}
	
	//printf("%d ", x);
	return x;
}

int Right_Button(){
	// PORTB7  -> PORTD3
	int x = 0;
	if ((PIND & 0b0001000) == 0b00001000){
		x=1;
		printf("Right button \r\n");
	}
	return x;
	//B6 B7
}



int Left_Slider(){
	return ADC_Read(2);
}

int Right_Slider(){
	return ADC_Read(3);
	
}


 
