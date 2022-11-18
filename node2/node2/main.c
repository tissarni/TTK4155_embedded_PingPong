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
	DAC_init();
	motor_init();	
	//solenoid_init();
	
	
	int points = 0;
	/* PIOA->PIO_PUDR |= PIO_PA19;
	 /* Enable PIO controller on bit PC2(D0) */
	 PIOA->PIO_PER |= PIO_PA19;
	 /* Set output enable on PC2(D0) */
	 PIOA->PIO_OER |= PIO_PA19;

	
	uint32_t baud_rate = 0x00290165;
	can_init_def_tx_rx_mb(baud_rate);
	
	


	//PIOA->PIO_OER |= PIO_OER_P19;
	//PIOA->PIO_OER |= PIO_OER_P20;
	//unsigned toto;
	
	CAN_MESSAGE receive;
	//receive.data_length = 0;
	//receive.id = 0;
	PIOC->PIO_PER |= PIO_PC9;
	PIOC->PIO_OER |= PIO_PC9;
	set_pin();
	
	float toto = 4;
    /* Replace with your application code */
    while (1) 
    {	
		//encoder_read();
		//DAC_send_voltage(&toto);
		
		set_pin();
		
		/*points += score();
		

		printf("SCOORE : %d \r\n", points);*/
		
		can_receive(&receive, 0);
		set_positon(receive.data[0], receive.data[2]);
		
		/*if (receive.data[3] == 1)
		{
			solenoid_fire();
		}*/
		
		
		//pwm_set_duty(receive.data[1], receive.data[2]);
		
		//can_receive(&receive, 0);
		//printf("Vertical : %d     dir : %d      \r\n", receive.data[0], receive.data[2]);
		//printf("--------------------------");
		
		//PIOA->PIO_SODR = PIO_SODR_P19;
		//PIOA->PIO_SODR = PIO_SODR_P20;
		
		
	
    }
}
