/*
 * PWN.c
 *
 * Created: 17.11.2022 10:42:59
 *  Author: floriaca
 */ 

#include "sam.h"
#include "PWM.h"

void pwm_init(void) {
	PIOC->PIO_ABSR |= PIO_PC19;
	PIOC->PIO_PDR |= PIO_PC19;
	
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;
	PWM->PWM_CLK = PWM_CLK_PREB(0x9) | PWM_CLK_DIVB(0x1);
	
	
	PWM->PWM_CH_NUM[5].PWM_CMR |= PWM_CMR_CPRE_CLKB | PWM_CMR_CPOL;
	PWM->PWM_CH_NUM[5].PWM_CPRD |= 0xCD1; 
	
	PWM->PWM_CH_NUM[5].PWM_CDTY |= 0xF6;
	PWM->PWM_ENA |= PWM_ENA_CHID5;
}

void pwm_set_duty(int input, int dir) {
	if(input > 100) {
		input = 100;
	}
	if (input < 0) {
		input = 0;
	}
	
	float pulse = 0.000006 * input;
	float percent = 3281 / 0.02;
	float result;
	
	switch (dir)
	{
	case 2 : //Joystick LEFT -> servo rotate left
		pulse = 0.0015 - pulse;
		result = pulse * percent;
		PWM->PWM_CH_NUM[5].PWM_CDTYUPD |= (int)result;
		break;
	
	case 3 : //Joystick RIGHT -> servo rotate right
		
		pulse = 0.0015 + pulse;
		result = pulse * percent;
		PWM->PWM_CH_NUM[5].PWM_CDTYUPD |= (int)result;
		break;
	default :
		PWM->PWM_CH_NUM[5].PWM_CDTYUPD |= 0xF6;
		break;
		
	}
}