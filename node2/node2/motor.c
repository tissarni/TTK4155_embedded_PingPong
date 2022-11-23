/*
 * motor.c
 *
 * Created: 18.11.2022 10:38:43
 *  Author: floriaca
 */ 

#include "motor.h"
#include "sam.h"
#include "DAC.h"


void motor_init(){
	
	
	PMC->PMC_PCER0 |= PMC_PCER0_PID13;
	
	PIOC->PIO_PER |= (0xff << 1);
	PIOC->PIO_ODR |= (0xff << 1);
	
	PIOD->PIO_PER |= (0x7 << 0) | (0x3 << 9);
	PIOD->PIO_OER |= (0x7 << 0) | (0x3 << 9);
	
	PIOD->PIO_SODR = PIO_SODR_P9;
	
	/* Reset */
	PIOD->PIO_CODR = PIO_CODR_P1;
	delay(1);
	PIOD->PIO_SODR = PIO_SODR_P1;
	delay(1000);
	encoder_calibrate();
	delay(1000);
	DAC_send_voltage(0);
	
	
}

uint16_t encoder_read(){
	
	uint16_t output = 0;
	
	PIOD->PIO_CODR = PIO_CODR_P0;
	PIOD->PIO_CODR = PIO_CODR_P2;
	
	delay(1);
	output += ((PIOC->PIO_PDSR & encoder_mask) << 8);
	PIOD->PIO_SODR = PIO_CODR_P2;
	delay(1);
	output += (PIOC->PIO_PDSR & encoder_mask);
	PIOD->PIO_SODR = PIO_CODR_P0;

	return output;
	
	
}

void delay(int num){
	volatile float f = 1.0f;
	
	for (volatile int i = 0; i < 1024 * num; i++ )
		f *= 1.1f;
	
}


void set_positon(int joy_value, int dir, double* max_encoder) {
	float motor_pos;
	float middle = *max_encoder / 2;
	
	if(joy_value > 100) {
		joy_value = 100;
	}
	if (joy_value < 0) {
		joy_value = 0;
	}
	double y = encoder_read();
	
	switch (dir)
	{
	case 0: //Joystick UP -> motor right 
		
		motor_pos = middle - (middle*joy_value/100);
		PIOD->PIO_SODR |= PIO_SODR_P10;
		break;
	case 1: //Joystick DOWN -> motor left 
		
		motor_pos = middle + (middle*joy_value/100);
		PIOD->PIO_CODR |= PIO_CODR_P10;
		break;
	default:
		DAC_send_voltage(0);
		break;
	}
	
	
	
	if(y > 40000) {
		y = y - 65535;
	}
	
	
	
	if(dir < 2) {
		float e = motor_pos - y;
		float kp = 0.0005;
		float u = kp * e;
		if (u < 0) {
			u = -u;
		}
		DAC_send_voltage(&u);
	}
	
}


void set_pin(){
	//Fake PWM
	PIOC->PIO_SODR |= PIO_PC9;
	delay(1000);
	PIOC->PIO_CODR |= PIO_PC9;
	delay(1000);
}

void encoder_calibrate() {
	float volt_init = 3;
	
	PIOD->PIO_SODR |= PIO_SODR_P10;
	DAC_send_voltage(&volt_init);
	delay(900);	
	
	DAC_send_voltage(0);
	delay(1000);
	
	
}
	
	