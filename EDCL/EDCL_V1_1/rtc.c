/*
 * rtc.c
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

#include <stdint.h>
#include <avr/io.h>
#include "rtc.h"
#include "i2c.h"

/***************************************************

Function To Read Internal Registers of DS1307
---------------------------------------------

address : Address of the register
data: value of register is copied to this.


Returns:
0= Failure
1= Success
***************************************************/


// Convert binary coded decimal to normal decimal numbers
uint8_t bcdToDec(uint8_t val)
{
return( (val/16*10) + (val%16) );
}

// Convert normal decimal numbers to binary coded decimal
uint8_t decToBcd(uint8_t val)
{
return( (val/10*16) + (val%10) );
}

void DS1307_set_time(uint8_t second, uint8_t minute, uint8_t hour)
{
    DS1307Write(0x02, decToBcd(hour));
    DS1307Write(0x01, decToBcd(minute));
    DS1307Write(0x00, decToBcd(second));
}

void DS1307_set_date(uint8_t day, uint8_t month, uint8_t year)
{
    DS1307Write(0x04, decToBcd(day));
    DS1307Write(0x05, decToBcd(month));
    DS1307Write(0x06, decToBcd(year));
}

uint8_t DS1307Read(uint8_t address)
{
   uint8_t data;   //result

   //Start
   I2C_Send_start();

   //SLA+W (for dummy write to set register pointer)
   I2C_Send_Address(DS1307_ADDR_W);

   //Now send the address of required register
   I2C_Send_data(address);

   //Repeat Start
   I2C_Send_Repeated_start();

   //SLA + R
   I2C_Send_Address(DS1307_ADDR_R); //DS1307 Address + R

   //Now read the value with NACK
   data=I2C_Receive_Data();

   //STOP
   I2C_Stop();
   return data;
}

/***************************************************

Function To Write Internal Registers of DS1307

---------------------------------------------

address : Address of the register
data: value to write.


Returns:
0= Failure
1= Success
***************************************************/

void DS1307Write(uint8_t address,uint8_t data)
{
   //Start
   I2C_Send_start();

   //SLA+W
   I2C_Send_Address(DS1307_ADDR_W);

   //Now send the address of required register
   I2C_Send_data(address);

   //Now write the value
   I2C_Send_data(data);

   //STOP
   I2C_Stop();
}

