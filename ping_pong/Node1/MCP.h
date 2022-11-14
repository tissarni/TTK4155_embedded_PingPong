/*
 * MCP.h
 *
 * Created: 27.10.2022 10:41:26
 *  Author: titouani
 */ 


#ifndef MCP_H_
#define MCP_H_

uint8_t mcp_init();
uint8_t mcp_read(uint8_t address);
void mcp_write(uint8_t address, uint8_t data);
void mcp_request_send();
void mcp_bit_modify(uint8_t address_register, uint8_t mask, uint8_t data);
void mcp_reset();
void mcp_read_status();



#endif /* MCP_H_ */