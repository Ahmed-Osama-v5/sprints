/*
 * SPI_Pb.h
 *
 * Created: 12/20/2019 3:25:15 PM
 *  Author: Wave7
 */ 



#ifndef SPI_H_
#define SPI_H_


/*- INCLUDES -----------------------------------------------*/
#include "std_types.h"
#include "mega8.h"
#include "interrupt.h"
#include "dio.h"

/*- CONSTANTS ----------------------------------------------*/

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/
typedef enum
{
	SPI_PRESCALER_2,
	SPI_PRESCALER_4,
	SPI_PRESCALER_8,
	SPI_PRESCALER_16,
	SPI_PRESCALER_32,
	SPI_PRESCALER_64,
	SPI_PRESCALER_128
}SPI_Prescaler_TypeDef;

typedef enum
{
	SPI_MASTER,
	SPI_SLAVE
}SPI_Mode_TypeDef;

typedef enum
{
	SPI_MODE_0,
	SPI_MODE_1,
	SPI_MODE_2,
	SPI_MODE_3
}SPI_DataMode_TypeDef;

typedef enum
{
	SPI_MSB,
	SPI_LSB
}SPI_DataOrder_TypeDef;

typedef enum
{
	SPI_INTERRUPT,
	SPI_PULLING
}SPI_InterruptMode_TypeDef;

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
	SPI_Mode_TypeDef 			SPI_Mode;
	SPI_DataMode_TypeDef 		SPI_DataMode;
	SPI_DataOrder_TypeDef 		SPI_DataOrder;
	SPI_InterruptMode_TypeDef	SPI_InterruptMode;
	SPI_Prescaler_TypeDef		SPI_Prescaler;
	void (*CBK_Func) (void);
}SPI_Cfg_s;

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

/**
* @brief: Initialize SPI module
* @param:
* Input : SPI_Cfg_s* "Pointer to Struct of SPI Configuration
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


/**
 * @brief Blocking transmit a certain amount of data to a register over SPI
 * @param address
 * @param data
 * @param size
 */
void SPI_memTransmit(uint8 address, uint8 *data, uint16 size);

#endif /* SPI_H_ */
