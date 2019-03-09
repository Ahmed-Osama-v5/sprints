/*
 * adc_mcp3202.c
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

#include <avr/io.h>
#include "spi.h"
#include "adc_mcp3202.h"


void MCP3202_Init(void)
{
	ADC_CE_DDR |= (1 << ADC_CE_PIN); // ADC_CE set as digital output
    SPI_Init();
}

uint16_t MCP3202_read(uint8_t channel)
{
    uint8_t highByte = 0, lowByte = 0;

    ADC_CE_PORT &= ~(1 << ADC_CE_PIN); // CE is LOW to start communication

    SPI_Write(1);
    highByte = SPDR;

    if(channel == 0)
        SPI_Write(0xA0);
    else
        SPI_Write(0xE0);

    highByte = SPDR;

    SPI_Write(0);
    lowByte = SPDR;

    ADC_CE_PORT |= (1 << ADC_CE_PIN); // CE is HIGH to stop communication

    return((highByte << 8) | lowByte);
}

void MCP3208_Init(void)
{
	ADC_CE_DDR |= (1 << ADC_CE_PIN); // ADC_CE set as digital output
    SPI_Init();
}

uint16_t MCP3208_read(uint8_t channel, uint8_t sngOrDif)
{


    uint8_t  tempHigh,tempLow,tempADtype;

    tempADtype = (sngOrDif & 0x01) << 1;
    tempLow = (channel & 0x03) << 6;
    tempHigh = (channel & 0x04) >> 2;
    tempHigh |= (0x04)|(tempADtype);     // 0x04 --> startBit


    ADC_CE_PORT &= ~(1 << ADC_CE_PIN); // CE is LOW to start communication

    SPDR = tempHigh;
    while(! (SPSR & (1 << SPIF)));

    SPDR = tempLow;
    while(! (SPSR & (1 << SPIF)));
    tempHigh = SPDR;

    SPDR = 0x00; // Don't care.
    while(! (SPSR & (1 << SPIF)));
    tempLow = SPDR;

    ADC_CE_PORT |= (1 << ADC_CE_PIN); // CE is HIGH to stop communication

    return(((tempHigh & 0x0f) << 8) | tempLow);
}

