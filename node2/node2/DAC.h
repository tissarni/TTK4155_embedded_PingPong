/*
 * DAC.h
 *
 * Created: 17.11.2022 18:18:08
 *  Author: floriaca
 */ 
#include <stdio.h>

#ifndef DAC_H_
#define DAC_H_


void DAC_init();
void DAC_send_voltage(float* voltage);

#endif /* DAC_H_ */