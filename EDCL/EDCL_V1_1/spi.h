/*
 * spi.h
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#define MOSI    5
#define MISO    6
#define SCK     7
#define SS      4

#define MASTER  1
#define SLAVE   2

typedef enum{MODE0, MODE1, MODE2, MODE3} SPI_Mode_t;

void SPI_Master_Init(SPI_Mode_t mode);
void SPI_Write_To_Address(uint8_t addr, uint8_t data);
void SPI_Write(uint8_t data);
uint8_t SPI_Read(uint8_t addr);

#endif /* INC_SPI_H_ */
