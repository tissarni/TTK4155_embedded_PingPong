/*
 * adc.c
 *
 * Created: 17.11.2022 15:00:47
 *  Author: floriaca
 */ 

#include "ir.h"
#include "sam.h"
#include <stdio.h>

void adc_init(void){
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID37;
	
	ADC->ADC_CR |= ADC_CR_SWRST;
	
	ADC->ADC_MR |= (1 << 4);
	ADC->ADC_MR |= ADC_MR_FREERUN_ON;
	
	ADC->ADC_CHER |= ADC_CHER_CH6;
	ADC->ADC_CR = ADC_CR_START;

}


uint32_t adc_read(){
	uint32_t data =  ADC->ADC_CDR[6];
	return data;
}


int score(){
	int j = 0;
	if (adc_read() < 600) {
		//printf("BALL IN GOAL !!!! \r\n");
		while (adc_read() < 600) {};
		for (int i = 0; i < 40000000; i++){
		}
		return 1;
	}
	return 0;
}