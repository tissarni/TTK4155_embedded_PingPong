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
	mcp_write(MCP_CNF1, 0x03);
	mcp_write(MCP_CNF2, 0xb1);
	mcp_write(MCP_CNF3, 0x05);

	
	mcp_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
}

	
void can_send(can_message* message) {  //TODO : Synchro clock noeud
	mcp_write(MCP_TXB0SIDH, message->id >> 3);
	mcp_write(MCP_TXB0SIDL, message->id << 5);
	mcp_write(MCP_TXB0DLC, message->length);
	
	for(int i = 0; i < message->length; i++) {
		mcp_write(MCP_TXB0D0 + (uint8_t)i, message->data[i]);
	}
	
	mcp_request_send(0);
	
}
	
can_message can_receive() {
	can_message message;
	
	message.length = mcp_read(MCP_RXB0DLC);
	message.id = (mcp_read(MCP_RXB0SIDH)  << 3) | (mcp_read(MCP_RXB0SIDL) >> 5);
	
	
	for(int i = 0; i < message.length; i++) {
		message.data[i] = mcp_read(MCP_RXB0D0 + (uint8_t)i);
	}
	
	mcp_bit_modify(MCP_CANINTF,MCP_RX0IF, 0x00);
	
	return message;
}