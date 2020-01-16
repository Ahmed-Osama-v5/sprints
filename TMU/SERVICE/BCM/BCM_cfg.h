/*
 * BCM_cfg.h
 *
 *  Created on: Jan 16, 2020
 *      Author: Ahmed Osama
 */

#ifndef SERVICE_BCM_BCM_CFG_H_
#define SERVICE_BCM_BCM_CFG_H_

/*- INCLUDES -----------------------------------------------*/

/*- CONSTANTS ----------------------------------------------*/
#define MAX_BUFFER_SIZE   (1000)

/* TODO: Add support for SPI and I2C */
/* UART configuration parameters */
#define UART_BAUD_RATE    (9600)

/* UART module states */
#define TX_ONLY           (0)
#define RX_ONLY           (1)
#define TX_RX             (2)

/* Configure UART module state to be used to initialize UART module */
#define UART_TX_RX_CONFIG TX_RX

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/


#endif /* SERVICE_BCM_BCM_CFG_H_ */
