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
	// PORTB6
	int x = 0;
	if ((PINB & 0b01000000) == 0b01000000){
		x = 1;
		printf("Left button");
	}
	
	//printf("%d ", x);
	return x;
}

int Right_Button(){
	// PORTB7
	int x = 0;
	if ((PINB & 0b10000000) == 0b10000000){
		x=1;
		printf("Right button");
	}
	return x;
	//B6 B7
}

int Left_Slider(){
	// PORTB5
	int x = 0;
	if ((PINB & 0b00100000) == 0b00100000){
		x = 1;
		printf("Left slider");
	}
	
	//printf("%d ", x);
	return x;
}

int Right_Slider(){
	// PORTB4
	int x = 0;
	if ((PINB & 0b00010000) == 0b00010000){
		x=1;
		printf("Right slider");
	}
	return x;
	//B6 B7
}

/*
void PWM_Signal(){ // PD5
	ASSR = (1 << AS2);
	(1 << OC1A);
	//OC3A

}
*/

 
