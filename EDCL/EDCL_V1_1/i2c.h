/*
 * i2c.h
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

void I2C_Master_Init();
void I2C_Send_start();
void I2C_Send_Address(uint8_t address);
void I2C_Send_Mem_Address(uint16_t address);
void I2C_Send_data(uint8_t data);
void I2C_Send_Repeated_start();
uint8_t I2C_Receive_Data();
void I2C_Stop();

#endif /* INC_I2C_H_ */
