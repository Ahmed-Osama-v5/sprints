/*
 * ext_eep.c
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

#include <avr/io.h>
#include <util/delay.h>
#include "ext_eep.h"
#include "i2c.h"
#include "uart.h"


uint8_t EEWriteByte(uint16_t address,uint8_t data)
{
    //Put Start Condition on TWI Bus
    I2C_Send_start();

    //Now write SLA+W
    I2C_Send_Address(EE_ADDR_W);

    if((TWSR & 0xF8) != 0x18)
        {
            UART_Send_String("NAC after SLA+W\n");
            return 0;
        }

	//Now write memory address
	I2C_Send_Mem_Address(address);

	//Check status
	if((TWSR & 0xF8) != 0x28)
		{
            UART_Send_String("NAC after MEM Add\n");
            return 0;
        }

	//Now write data
	I2C_Send_data(data);

	//Check status
	if((TWSR & 0xF8) != 0x28)
		{
            UART_Send_String("NAC after Data\n");
            return 0;
        }

	// I2C send stop
	I2C_Stop();

	//Wait until Writing is complete
	_delay_ms(12);

	return 1;
}

uint8_t EEReadByte(uint16_t address)
{
	uint8_t data;

	// I2C send start
    I2C_Send_start();

    // I2C send address
    I2C_Send_Address(EE_ADDR_W);

	//Now write memory address
	I2C_Send_Mem_Address(address);

    // I2C send repeated start
    I2C_Send_Repeated_start();

    // I2C send address
    I2C_Send_Address(EE_ADDR_R);

    // I2C receive data
    data = I2C_Receive_Data();

    // I2C send stop
    I2C_Stop();

    return data;
}

void EE_Erase(void)
{
    uint16_t add = 0;
    for(add=0; add<4096; add++)
    {
        EEWriteByte(add, 0);
    }
}

