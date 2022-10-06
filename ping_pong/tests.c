/*
 * tests.c
 *
 * Created: 15.09.2022 14:42:35
 *  Author: titouani
 */ 


#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

#include "tests.h"
#include "JOYSTICK.h"
#include "SLIDER.h"

void test_blinking()
{
	PORTA = 0b00000001;
	_delay_ms(1000);
	PORTA = 0b00000000;
	_delay_ms(1000);
	
}

void test_transmit()
{
	UART_Transmit('c');
	_delay_ms(1000);
}

void test_Receive()
{
	UART_Receive();
	_delay_ms(1000);
}

void test_printf()
{
	printf("YEAAH\n\r");
}

void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
	}
	
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}

void SRAM_mapping_test()
{	
	//SRAM_test();
	while(1) {
		
		xmem_write("c", 0x0400);
		printf("\n ADC \n\r");
		_delay_ms(1000);
		
		/*xmem_write("c", 0x0800);
		printf("\n SRAM \n\r");
		_delay_ms(500);*/
	}
}

void USB_multi_test() {
	
	
	
	while(1) {
		joystick_pos pos = get_joystick_pos();
		printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n");
		printf("Left button : %d   Right button : %d  \n\rLeft slider : %d   Right slider : %d  \n\rJoystick pos : X =  %d Y = %d\r\n", Left_Button(), Right_Button(), ADC_Read(2), ADC_Read(3), pos.x, pos.y);
		printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n");

		_delay_ms(15000);
	}
	
}
