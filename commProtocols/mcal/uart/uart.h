/*
 * UART.h
 *
 * Created: 12/20/2019 10:41:42 AM
 *  Author: Wave7
 */ 


#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "interrupt.h"

/*
*	Definition of UART registers
*/
#define UART_CSRC ( *((volatile unsigned char *) (0x40) ) )  /* Multiple use with USART_BRRH >> URSEL is set to choose which one will override */
#define UART_BRRH ( *((volatile unsigned char *) (0x40) ) )  /* Multiple use with USART_CSRC >> URSEL is set to choose which one will override */
#define UART_BRRL ( *((volatile unsigned char *) (0x29) ) )

#define UART_DR   ( *((volatile unsigned char *) (0x2c) ) )

#define UART_CSRA ( *((volatile unsigned char *) (0x2b) ) )
#define UART_CSRB ( *((volatile unsigned char *) (0x2a) ) )


/*
*	Definition of UART register's bits
*/

/*CSRA*/
#define UART_MPCM  0
#define UART_U2X   1
#define UART_PE    2
#define UART_DOR   3
#define UART_FE    4
#define UART_DRE   5
#define UART_TXC   6
#define UART_RXC   7

/*CSRB*/
#define UART_TXB8  0
#define UART_RXB8  1
#define UART_UCSZ2 2
#define UART_TXEN  3
#define UART_RXEN  4
#define UART_DRIE  5
#define UART_TXCIE 6
#define UART_RXCIE 7

/*CSRC*/
#define UART_CPOL  0
#define UART_CSZ0  1
#define UART_CSZ1  2
#define UART_SBS   3
#define UART_PM0   4
#define UART_PM1   5
#define UART_MSEL  6
#define UART_RSEL  7

/*
*	Used macros 
*/
#define UART_POLLING   0U
#define UART_INTERRUPT 1U

#define TRANSMITTER    0U
#define RECEIVER       1U
#define TRANSCEIVER    2U

typedef struct 
{
	uint8 u8_InterruptMode ;
	uint8 u8_DesiredOperation ;
	uint32 u32_BaudRate ;	
}UART_cfg_s;

/** 
 * \brief UART_Init : 
 *
 * \param *pUART_cfg_s : A pointer to a struct that holds the desired UART configuration
 * \return ERROR_STATUS : Indication to the function execution 
 *
 **/     
extern ERROR_STATUS UART_Init(UART_cfg_s *pUART_cfg_s);

/** 
 * \brief UART_Deinit : Deinitialize the UART module
 *
 * \param void
 * \return ERROR_STATUS : Indication to the function execution 
 *
 **/     
extern ERROR_STATUS UART_Deinit(void);

/** 
 * \brief  UART_SendByte : Sends a certain byte
 *
 * \param u8_Data : The byte the user wants to send
 * \return ERROR_STATUS : Indication to the function execution 
 *
 **/  
extern ERROR_STATUS UART_SendByte(uint8 u8_Data);

/** 
 * \brief  UART_ReceiveByte : Receives a certain byte
 *
 * \param pu8_ReceivedData : The sent byte will be stored in the passed pointer 
 * \return ERROR_STATUS : Indication to the function execution 
 *
 **/  
extern ERROR_STATUS UART_ReceiveByte(uint8 *pu8_ReceivedData);
   
#endif /* UART_H_ */
