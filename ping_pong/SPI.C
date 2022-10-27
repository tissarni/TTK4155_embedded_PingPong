/*
 * SPI.C
 *
 * Created: 21.10.2022 10:21:28
 *  Author: titouani
 */ 

#include <avr/io.h>

void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB |= (1 << DDB5) | (1 << DDB7) | (1 << DDB4);
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1 << SPE) | (1 << MSTR) | (1<<SPR0);
	SPCR &= ~(1 << CPOL);
	SPCR &= ~(1 << CPHA);
}

void SPI_MasterTransmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}

char SPI_MaserRead() {
	
	SPI_MasterTransmit(0);
	
	while(!(SPSR & (1<<SPIF)))
	;
	
	return SPDR;
	
}


