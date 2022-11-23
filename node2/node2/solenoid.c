/*
 * solenoid.c
 *
 * Created: 18.11.2022 16:28:29
 *  Author: titouani
 */ 

#include "solenoid.h"
#include "sam.h"
#include "motor.h"

void solenoid_init(void){
	PIOC->PIO_PER |= PIO_PC9;
	PIOC->PIO_OER |= PIO_PC9;
	PIOC->PIO_SODR |= PIO_PC9;
}

void solenoid_start(void){
	PIOC->PIO_CODR |= PIO_PC9;
}

void solenoid_stop(void){
	PIOC->PIO_SODR |= PIO_PC9;
}

void solenoid_fire(int button){
	if (button == 1 ) {
		solenoid_start();
		delay(200);
		solenoid_stop();
		
	}
}

