/*
 * CAN.c
 *
 * Created: 27.10.2022 14:22:02
 *  Author: titouani
 */ 


#include "CAN.h"
#include "MCP.h"
#include "mcp2515.h"
#include "SPI.h"


void can_init() {
	mcp_init();
	
	mcp_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
}

	
void can_send(can_message* message) {  //TODO : Synchro clock noeud
	mcp_write(MCP_TXB0SIDH, message->id >> 3);
	mcp_write(MCP_TXB0SIDL, message->id << 5);
	mcp_write(MCP_TXB0DLC, message->length);
	
	for(int i = 0; i < message->length; i++) {
		mcp_write(MCP_TXB0D0 + i, message->data[i]);
	}
	
	mcp_request_send(0);
	
}
	
can_message can_receive() {
	can_message message;
	
	message.length = mcp_read(MCP_RXB0DLC);
	message.id = (mcp_read(MCP_RXB0SIDH)  << 3) | (mcp_read(MCP_RXB0SIDL) >> 5);
	
	
	for(int i = 0; i < message.length; i++) {
		message.data[i] = mcp_read(MCP_RXB0D0 + i);
	}
	mcp_reset();
	return message;
}