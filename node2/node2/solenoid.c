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
	PIOC->PIO_PER |= PIO_PER_P9;
	PIOC->PIO_OER |= PIO_OER_P9;
	PIOC->PIO_SODR |= PIO_SODR_P9;
}

void solenoid_start(void){
	PIOC->PIO_SODR = PIO_SODR_P9;
}

void solenoid_stop(void){
	PIOC->PIO_CODR = PIO_CODR_P9;
}

void solenoid_fire(void){
	solenoid_start();
	delay(100);
	solenoid_stop();
}

