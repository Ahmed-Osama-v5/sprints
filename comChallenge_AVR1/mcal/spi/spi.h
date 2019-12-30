/*
 * SPI_Pb.h
 *
 * Created: 12/20/2019 3:25:15 PM
 *  Author: Wave7
 */ 



#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
#include "interrupt.h"
#include "dio.h"

typedef struct {
/* Master or Slave */
uint8 u8_SPIMode;
/* SPI Mode */
uint8 u8_DataMode;
/* MSB or LSB */
uint8 u8_DataOrder;
/* Interrupt or Polling */
uint8 u8_InterruptMode;
/* SPI_PRESCALER_2 to SPI_PRESCALER_128 */
uint8 u8_Prescaler;
void (*CBK_Func) (void);
}SPI_Cfg_s;


#define NOT_INITIALIZED		(0)
#define INITIALIZED			(1)

#define NOT_TRIGGERED		(0)
#define TRIGGERED			(1)

/* NORMAL SPEED */
#define SPI_PRESCALER_2     (0)
#define SPI_PRESCALER_4     (1)
#define SPI_PRESCALER_8     (2)
#define SPI_PRESCALER_16    (3)
#define SPI_PRESCALER_32    (4)
#define SPI_PRESCALER_64    (5)
#define SPI_PRESCALER_128   (6)

/* YOU CAN USE PRE_SCALER_F_64 FROM NORMAL SPEED ! */


/* Polling or Interrupt */
#define POLLING         (0)
#define INTERRUPT       (1)

/* Master or Slave */
#define SLAVE           (0)
#define MASTER          (1)

/* Most SB or Least SB */
#define MSB             (0)
#define LSB             (1)

/* Data modes */
#define MODE_0			(0)
#define MODE_1			(1)
#define MODE_2			(2)
#define MODE_3			(3)

/**
* @brief: Initialize SPI module
* @param:
* Input : SPI_Cfg_s* "Pointer to Struct of SPI Configration
* Output: None
* @return: Error codes if present
*/
ERROR_STATUS SPI_Init(SPI_Cfg_s* pstr_SPI_Confg);


/**
* @brief: Transmit one byte over SPI
* @param:
* Input : u8_Data "Byte to be sent"
* Output: None
* @return: Error codes if present
*/
ERROR_STATUS SPI_SendByte(uint8 u8_Data);

/**
* @brief: Receive one byte over SPI
* @param:
* Input : None
* Output: *ptru8_Data "points to where received byte is going to be stored in"
* @return: Error codes if present
*/
ERROR_STATUS SPI_ReceiveByte(uint8 *ptru8_Data);

/**
* @brief: Get status of SPI interrupt flag
* @param:
* Input : None
* Output: *u8_Data "points to where flag value is going to be stored in"
* @return: Error codes if present
*/
ERROR_STATUS SPI_GetStatus(uint8 *u8_Data);

/**
* @brief: Clears flag of SPI
* @param:
* Input : void
* Output: None
* @return: Error codes if present
*/
ERROR_STATUS SPI_ClearFlag(void);


#endif /* SPI_H_ */
