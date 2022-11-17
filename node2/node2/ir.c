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
	
	//PIOA->PIO_PER |= PIO_PA24;
	//PIOA->PIO_ODR |= PIO_PA24;
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID37;
	
	ADC->ADC_CR |= ADC_CR_SWRST;
	
	
	 
	
	ADC->ADC_MR |= (1 << 4);
	ADC->ADC_MR |= ADC_MR_FREERUN_ON;
	
	ADC->ADC_CHER |= ADC_CHER_CH6;
	ADC->ADC_CR = ADC_CR_START;

}


uint32_t adc_read(){
	//return (int)(ADC->ADC_LCDR & ADC_LCDR_LDATA_Msk);
	uint32_t data =  ADC->ADC_CDR[6];
	return data;
}


int score(){
	
	
	//uint32_t reader = adc_read();
	if (adc_read() < 200) {
		//printf("BALL IN GOAL !!!! \r\n");
		while (adc_read() < 200) {};
		for (int i = 0; i < 10000000; i++){
			
		}
		return 1;
	}
	
	return 0;
	
	
	
}