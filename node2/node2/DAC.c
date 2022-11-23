/*
 * DAC.c
 *
 * Created: 17.11.2022 18:17:46
 *  Author: floriaca
 */ 

#include <stdio.h>

#include "DAC.h"
#include "sam.h"


void DAC_init(){
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID38;
	
	DACC ->DACC_WPMR &= ~(0x1u << 1);
	DACC -> DACC_CHER  |= DACC_CHER_CH1;
	DACC -> DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;	
	DACC -> DACC_MR |= DACC_MR_WORD_HALF;
}


void DAC_send_voltage(float* voltage){
	if (*voltage > 5){
		*voltage = 5;
	}
	if (*voltage < 0){
		*voltage = 0;
	}
	uint16_t command = (uint16_t)((*voltage)*4095/5);
	DACC->DACC_CDR = DACC_CDR_DATA(command);
}