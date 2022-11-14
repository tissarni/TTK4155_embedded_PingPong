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

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	can_init_def_tx_rx_mb(0x00290165);
	
	WDT->WDT_MR = WDT_MR_WDDIS;

	//printf("CE SOIR JE ME DEVISSE LE CRANE !!!");

	PIOA->PIO_OER |= PIO_OER_P19;
	PIOA->PIO_OER |= PIO_OER_P20;
	unsigned toto;
	CAN_MESSAGE receive;
	

    /* Replace with your application code */
    while (1) 
    {	
		toto =  can_receive(&receive, 0);
		printf("RECEIVE => length:  %d \n\rid: %d \n\rdata: %s \n\r toto %d \n\r ", receive.data_length, receive.id, receive.data, toto);
		
		//PIOA->PIO_SODR = PIO_SODR_P19;
		//PIOA->PIO_SODR = PIO_SODR_P20;
		
		
	
    }
}
