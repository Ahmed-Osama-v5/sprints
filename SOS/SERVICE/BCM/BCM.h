/*
 * BCM.h
 *
 *  Created on: Jan 16, 2020
 *      Author: Ahmed Osama
 */

#ifndef SERVICE_BCM_BCM_H_
#define SERVICE_BCM_BCM_H_

/*- INCLUDES -----------------------------------------------*/
#include "std_types.h"
#include "BCM_cfg.h"

/*- CONSTANTS ----------------------------------------------*/
/* BCM_ID */
#define BCM_ID                                  (0x7F)

/*- PRIMITIVE TYPES ----------------------------------------*/
/* define buffer pointer as pointer to 8-bit integer */
typedef uint8* ptrBuffer;

/* Transmit complete User callback function typedef */
typedef void (*gptr_BCM_TransmitComplete_User_CBK_t) (void);

/* Receive complete User callback function typedef */
typedef void (*gptr_BCM_ReceiveComplete_User_CBK_t) (void);

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/
/**
* @brief: BCM Initialization
* @param: gptr_BCM_TxComplete_CBK: pointer to user TxComplete callback
* @return: sint8 status code with error code if one occurred
*/
sint8 BCM_Init(gptr_BCM_TransmitComplete_User_CBK_t gptr_BCM_TxComplete_CBK);

/**
* @brief: takes pointer to the TX buffer and
* 	  its size, checks if size is <= MAX_BUFFER_SIZE,
* 	  and passes them to the dispatcher.
* @param: ptr_Buffer, u16_Size
* @return: sint8 status code with error code if one occurred
*/
sint8 BCM_Send(ptrBuffer ptr_Buffer, uint16 u16_Size);

/**
* @brief: takes pointer to the RX buffer
* 	  and passes it to the dispatcher.
* @param: ptr_Buffer
* @return: sint8 status code with error code if one occurred
*/
sint8 BCM_SetupReceive(ptrBuffer ptr_Buffer);

/**
* @brief: Handles data reception.
* @param: void
* @return: sint8 status code with error code if one occurred
*/
sint8 BCM_RxDispatcher(void);

/**
* @brief: Handles data transmission.
* @param: void
* @return: sint8 status code with error code if one occurred
*/
sint8 BCM_TxDispatcher(void);

/**
* @brief: Indicates user has finished processing data
* 	  in the Rx_Buffer.
* @param: void
* @return: sint8 status code with error code if one occurred
*/
sint8 BCM_RxUnlock(void);

#endif /* SERVICE_BCM_BCM_H_ */
