/*
 * MCP.c
 *
 * Created: 27.10.2022 10:41:11
 *  Author: titouani
 */ 

#include <avr/io.h>

#include "MCP.h"
#include "SPI.h"
#include "mcp2515.h"

uint8_t mcp_init()
{
	uint8_t value ;
	SPI_MasterInit() ; // Initialize SPI
	mcp_reset(); // Send reset - command
	// Self - test
	value = mcp_read(MCP_CANSTAT) ;
	
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf (" MCP2515 is NOT in configuration mode after reset !\ n ") ;
		return 1;
	}
	// More initialization
	
	return 0;
}



uint8_t mcp_read(uint8_t address)
{
	uint8_t result ;
	// Select CAN - controller
	PORTB &= ~(1 << PINB4); 
	
	// Send read instruction
	SPI_MasterTransmit(MCP_READ); 
	
	// Send address
	SPI_MasterTransmit(address); 
	
	// Read result
	result = SPI_MaserRead();
	
	// Deselect CAN - controller
	PORTB |= (1 << PINB4); 
	
	return result ;
}

void mcp_write(uint8_t address, uint8_t data) {
	
	PORTB &= ~(1 << PINB4); 
	
	SPI_MasterTransmit(MCP_WRITE);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(data);
	
	PORTB |= (1 << PINB4);
};
	
void mcp_request_send(int buffer) {
	PORTB &= ~(1 << PINB4); 
	
	switch (buffer){
		case 0:
			SPI_MasterTransmit(MCP_RTS_TX0);
			break;
		case 1:
			SPI_MasterTransmit(MCP_RTS_TX1);
			break;
		case 2:
			SPI_MasterTransmit(MCP_RTS_TX2);
			break;
		case 3: 
			SPI_MasterTransmit(MCP_RTS_ALL);
			break;
		default:
			SPI_MasterTransmit(0x80);
			break;
	}
	
	//SPI_MasterTransmit(MCP_RTS_TX0);
	
	PORTB |= (1 << PINB4);
};
	
	
void mcp_reset() {
	PORTB &= ~(1 << PINB4);
	
	SPI_MasterTransmit(MCP_RESET);
	
	PORTB |= (1 << PINB4);
};

void mcp_read_status() {
		uint8_t result ;
		PORTB &= ~(1 << PINB4);
		
		SPI_MasterTransmit(MCP_READ_STATUS);
		result = SPI_MaserRead();
		
		PORTB |= (1 << PINB4);
		return result ;
	};
	
void mcp_bit_modify(uint8_t address_register, uint8_t mask, uint8_t data) {  // NOT FOR ALL REGISTERS. SEE REGISTER MAP.
	PORTB &= ~(1 << PINB4);
	
	SPI_MasterTransmit(MCP_BITMOD);
	SPI_MasterTransmit(address_register);
	SPI_MasterTransmit(mask);
	SPI_MasterTransmit(data);
	
	PORTB |= (1 << PINB4);
};
	