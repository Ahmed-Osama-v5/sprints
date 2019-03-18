/*
 * spi.c
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

/*********************************
 * Title  : SPI.
 * Author : Ahmed Osama.
 * Date   : 03 Oct 2015.
 * Contact: engahmed2015@gmail.com
 *********************************/
#include <avr/io.h>
#include <stdint.h>
#include "spi.h"

void SPI_Master_Init(SPI_Mode_t mode)
{
    SPCR = ((1 << SPE) | (1 << MSTR) | (1 << SPR1));  // Enable SPI Master mode @ 250 KHz.
    switch(mode)
    {
    case MODE0:
    	SPCR &= ~(1 << CPOL);
    	SPCR &= ~(1 << CPHA);
    	break;
    case MODE1:
    	SPCR &= ~(1 << CPOL);
    	SPCR |= (1 << CPHA);
        break;
    case MODE2:
    	SPCR |= (1 << CPOL);
	    SPCR &= ~(1 << CPHA);
        break;
    case MODE3:
    	SPCR |= (1 << CPOL);
    	SPCR |= (1 << CPHA);
        break;
    default:
    	SPCR &= ~(1 << CPOL);
    	SPCR &= ~(1 << CPHA);
        break;
    }
    DDRB |= ((1 << MOSI) | (1 << SCK));   // Setting MOSI and SCK as digital outputs.
}

void SPI_Write_To_Address(uint8_t addr, uint8_t data)
{
    SPDR = addr;
    while(! (SPSR & (1 << SPIF)));

    SPDR = data;
    while(! (SPSR & (1 << SPIF)));
}

void SPI_Write(uint8_t data)
{
    SPDR = data;
    while(! (SPSR & (1 << SPIF)));
}

uint8_t SPI_Read(uint8_t addr)
{
    while(! (SPSR & (1 << SPIF)));
    return SPDR;
}

