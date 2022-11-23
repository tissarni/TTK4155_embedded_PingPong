/*
 * node2.c
 *
 * Created: 03.11.2022 15:20:16
 * Author : floriaca
 */ 


#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "can_controller.h"
#include "PWM.h"
#include "ir.h"
#include "motor.h"
#include "DAC.h"
#include "solenoid.h"
#include <stdio.h>


int main(void)
{
	WDT->WDT_MR = WDT_MR_WDDIS;
	
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	pwm_init();
	adc_init();
	solenoid_init();
	DAC_init();
	motor_init();	
	
	
	
	
	PIOA->PIO_PER |= PIO_PA19;
	PIOA->PIO_OER |= PIO_PA19;

	PIOC->PIO_PER |= PIO_PC9;
	PIOC->PIO_OER |= PIO_PC9;
	
	uint32_t baud_rate = 0x00290165;
	int points = 0;
	
	can_init_def_tx_rx_mb(baud_rate);
	
	CAN_MESSAGE receive;
	
	double max_encoder = encoder_read();
	printf("########### %d \r\n", (int)max_encoder);
	
	double max_encode1r = encoder_read();
	//printf("ouui %d \r\n", (int)max_encode1r);
	
	double max_encode2r = encoder_read();
	//printf("nooooon %d \r\n", (int)max_encode2r);
	
	
    while (1) 
    {	
		
		points += score();

		printf("SCORE : %d \r\n", points);
		
		can_receive(&receive, 0);
		//printf("FEU : %d       Horizontal : %d        Vertical : %d \r\n", receive.data[3], receive.data[1], receive.data[0]);

		pwm_set_duty(receive.data[1], receive.data[2]);
		
		set_positon(receive.data[0], receive.data[2], &max_encode2r);
		
		solenoid_fire(receive.data[3]);
		
		
	
    }
}
