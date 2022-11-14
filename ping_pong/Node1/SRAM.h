/*
 * SRAM.h
 *
 * Created: 15.09.2022 13:53:22
 *  Author: titouani
 */ 


#ifndef SRAM_H_
#define SRAM_H_

void SRAM_Init();
void xmem_write ( uint8_t data , uint16_t addr );
uint8_t xmem_read ( uint16_t addr );


#endif /* SRAM_H_ */