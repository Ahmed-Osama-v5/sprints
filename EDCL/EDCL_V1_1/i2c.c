/*
 * i2c.c
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

void I2C_Master_Init()
{
    /* set SCL_FREQ @ 100 KHz for 16 MHz osc*/
    TWBR = 72;
    //enable TWI
    TWCR = (1<<TWEN);
}

void I2C_Send_start()
{
    // I2C send start
    TWCR |= (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    while(!(TWCR & (1 << TWINT)));
}

void I2C_Stop()
{
    TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);  //transmit stop condition
	while(TWCR & (1<<TWSTO));                    //wait for it to complete
}

void I2C_Send_Repeated_start()
{
    // I2C send repeated start
    TWCR |= (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    while(!(TWCR & (1 << TWINT)));
}

void I2C_Send_Address(uint8_t address)
{
    // I2C send address
    TWDR = address;
    TWCR &= ~(1 << TWSTA);
    TWCR |= (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
}

void I2C_Send_Mem_Address(uint16_t address)
{
    /* Send 1st byte */
    TWDR = address >> 8;
    TWCR &= ~(1 << TWSTA);
    TWCR |= (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));

    /* Send 2nd byte */
    TWDR = address;
    TWCR &= ~(1 << TWSTA);
    TWCR |= (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
}

void I2C_Send_data(uint8_t data)
{
    // I2C send data
    TWDR = data;
    TWCR |= (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
}

uint8_t I2C_Receive_Data()
{
    // I2C receive data
    TWCR |= (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));

    return TWDR;
}

