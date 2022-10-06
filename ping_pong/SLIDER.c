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
		printf("Left button \r\n");
	}
	
	//printf("%d ", x);
	return x;
}

int Right_Button(){
	// PORTB7
	int x = 0;
	if ((PINB & 0b10000000) == 0b10000000){
		x=1;
		printf("Right button \r\n");
	}
	return x;
	//B6 B7
}

int Left_Slider(){
	
	
	//printf("Left slider : %d \r\n", left_slider );
	
	
	return ADC_Read(2);
}

int Right_Slider(){
	
	return ADC_Read(3);
	
}

/*
void PWM_Signal(){ // PD5
	ASSR = (1 << AS2);
	(1 << OC1A);
	//OC3A

}
*/

 
