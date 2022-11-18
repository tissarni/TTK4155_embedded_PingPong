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
	
	//printf("output : %d  \r\n", (int)output);

	return output;
	
	
}

void delay(int num){
	volatile float f = 1.0f;
	
	for (volatile int i = 0; i < 1024 * num; i++ )
		f *= 1.1f;
	
}

//17584

void set_positon(int joy_value, int dir) {
	int motor_pos;
	int middle = 17584 / 2;
	
	if(joy_value > 100) {
		joy_value = 100;
	}
	if (joy_value < 0) {
		joy_value = 0;
	}
	
	
	switch (dir)
	{
	case 1: //droite
		motor_pos = middle - (int)(middle*joy_value/100);
		PIOD->PIO_SODR |= PIO_SODR_P10;
		break;
	case 0: //gauche
		motor_pos = middle + (int)(middle*joy_value/100);
		PIOD->PIO_CODR |= PIO_CODR_P10;
		break;
	default:
		motor_pos = middle;
		break;
	}
	
	
	printf("MOTOR POS : %d \r\n", motor_pos);
	int y = (int)encoder_read();
	int e = motor_pos - y;
	float kp = 0.0005;
	float u = kp * e;
	if (u < 0) {
		u = -u;
	}
	printf("UUUUUUUUUU : %d \r\n", (int)u);
	
	DAC_send_voltage(&u);
	
}