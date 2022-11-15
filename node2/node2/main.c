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
	//unsigned toto;
	
	CAN_MESSAGE receive;
	//receive.data_length = 0;
	//receive.id = 0;
	
	

    /* Replace with your application code */
    while (1) 
    {	
		
		
		//can_receive(&receive, 0);
		//printf("Vertical : %d      Horizontal  %d  \r\n LENGHT : %d     ID : %d \r\n", receive.data[1], receive.data[0], receive.data_length, receive.id);
		//printf(" %d", toto);
		
		//PIOA->PIO_SODR = PIO_SODR_P19;
		//PIOA->PIO_SODR = PIO_SODR_P20;
		
		
	
    }
}
