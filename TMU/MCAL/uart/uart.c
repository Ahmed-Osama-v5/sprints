/*
 * uart.c
 *
 *  Created on: Dec 28, 2019
 *      Author: Ahmed
 */

#include <math.h>
#include <stdlib.h>
#include "uart.h"

static uint8 gu8_initState = NOT_INITIALIZED;
static uint8 UCSRC_Buffer = 0x80;

/**
* @brief: UART TXC callback function
* @param:
* Input : void
* Output: None
* @return: void
*/
static void (*UART_TXC_CBK_Ptr)(void) = {NULL};

/**
* @brief: UART RXC callback function
* @param:
* Input : void
* Output: None
* @return: void
*/
static void (*UART_RXC_CBK_Ptr)(void) = {NULL};

/**
* @brief: UART UDRE callback function
* @param:
* Input : void
* Output: None
* @return: void
*/
static void (*UART_UDRE_CBK_Ptr)(void) = {NULL};

/**
 * \brief UART_Init :
 *
 * \param *pUART_cfg_s : A pointer to a struct that holds the desired UART configuration
 * \return ERROR_STATUS : Indication to the function execution
 *
 **/
ERROR_STATUS UART_Init(UART_cfg_s *pUART_cfg_s)
{
	if(NULL != pUART_cfg_s)
	{
		/* Calculate baud rate and store equivalent value in UBRR */
		uint16 UBRR_value = lrint((F_CPU /(16UL * pUART_cfg_s->u32_BaudRate)) - 1);
		/* Put the upper part of the baud number here */
		UBRRH = (uint8) (UBRR_value >> 8);

		/* Put the remaining part of the baud number here */
		UBRRL = (uint8) UBRR_value;

		/* Handle data size */
		if(pUART_cfg_s->u8_DataSize == UART_5_BIT)
		{
			UCSRC_Buffer &= ~(UCSZ1 | UCSZ0);
			UCSRC = UCSRC_Buffer;
			UCSRB &= ~UCSZ2;
		}
		else if(pUART_cfg_s->u8_DataSize == UART_6_BIT)
		{
			UCSRC_Buffer &= ~UCSZ1;
			UCSRC_Buffer |= UCSZ0;
			UCSRC = UCSRC_Buffer;
			UCSRB &= ~UCSZ2;
		}
		else if(pUART_cfg_s->u8_DataSize == UART_7_BIT)
		{
			UCSRC_Buffer |= UCSZ1;
			UCSRC_Buffer &= ~UCSZ0;
			UCSRC = UCSRC_Buffer;
			UCSRB &= ~UCSZ2;
		}
		else if(pUART_cfg_s->u8_DataSize == UART_8_BIT)
		{
			UCSRC_Buffer |= (UCSZ1 | UCSZ0);
			UCSRC = UCSRC_Buffer;
			UCSRB &= ~UCSZ2;
		}
		else if(pUART_cfg_s->u8_DataSize == UART_9_BIT)
		{
			UCSRC_Buffer |= (UCSZ1 | UCSZ1);
			UCSRC = UCSRC_Buffer;
			UCSRB |= UCSZ2;
		}
		else
		{
			return E_NOK;
		}

		/* Handle parity selection */
		if(pUART_cfg_s->u8_ParityBit == UART_NO_PARITY)
		{
			UCSRC_Buffer &= ~(UPM1 | UPM0);
			UCSRC = UCSRC_Buffer;
		}
		else if(pUART_cfg_s->u8_ParityBit == UART_EVEN_PARITY)
		{
			UCSRC_Buffer &= ~UPM0;
			UCSRC_Buffer |= UPM1;
			UCSRC = UCSRC_Buffer;
		}
		else if(pUART_cfg_s->u8_ParityBit == UART_ODD_PARITY)
		{
			UCSRC_Buffer |= (UPM1 | UPM0);
			UCSRC = UCSRC_Buffer;
		}
		else
		{
			return E_NOK;
		}

		/* Handle stop bits selection */
		if(pUART_cfg_s->u8_StopBit == UART_ONE_STOP_BIT)
		{
			UCSRC_Buffer &= ~USBS;
			UCSRC = UCSRC_Buffer;
		}
		else if(pUART_cfg_s->u8_StopBit == UART_TWO_STOP_BIT)
		{
			UCSRC_Buffer |= USBS;
			UCSRC = UCSRC_Buffer;
		}
		else
		{
			return E_NOK;
		}

		/* Handle double speed selection */
		if(pUART_cfg_s->u8_DoubleSpeed == UART_NO_DOUBLE_SPEED)
		{
			UCSRA &= ~U2X;
		}
		else if(pUART_cfg_s->u8_DoubleSpeed == UART_DOUBLE_SPEED)
		{
			UCSRA |= U2X;
		}
		else
		{
			return E_NOK;
		}

		/* Handle Interrupt selection */
		switch(pUART_cfg_s->u8_InterruptMode)
		{
		case (UART_POLLING):
			/* Handle desired operation selection */
			if(pUART_cfg_s->u8_DesiredOperation == TRANSMITTER)
			{
				UCSRB &= ~(RXCIE | TXCIE | RXEN);
				UCSRB |= TXEN;
			}
			else if(pUART_cfg_s->u8_DesiredOperation == RECEIVER)
			{
				UCSRB &= ~(RXCIE | TXCIE | TXEN);
				UCSRB |= RXEN;
			}
			else if(pUART_cfg_s->u8_DesiredOperation == TRANSCEIVER)
			{
				UCSRB &= ~(RXCIE | TXCIE);
				UCSRB |= (RXEN | TXEN);
			}
			else
			{
				return E_NOK;
			}
			break;
		case (UART_INTERRUPT):
			/* Handle desired operation selection */
			if(pUART_cfg_s->u8_DesiredOperation == TRANSMITTER)
			{
				UCSRB &= ~RXEN;
				UCSRB |= (RXCIE | TXCIE | TXEN);
			}
			else if(pUART_cfg_s->u8_DesiredOperation == RECEIVER)
			{
				UCSRB &= ~TXEN;
				UCSRB |= (RXCIE | TXCIE | RXEN);
			}
			else if(pUART_cfg_s->u8_DesiredOperation == TRANSCEIVER)
			{
				UCSRB |= (RXCIE | TXCIE | RXEN | TXEN);
			}
			else
			{
				return E_NOK;
			}
			break;
		default:
			return E_NOK;
			break;
		}

		/* Pass pointer to TXC callback function */
		if(NULL != pUART_cfg_s->Transmit_Cbk_ptr)
		{
			UART_TXC_CBK_Ptr = pUART_cfg_s->Transmit_Cbk_ptr;
		}
		else
		{

		}

		/* Pass pointer to RXC callback function */
		if(NULL != pUART_cfg_s->Resceive_Cbk_ptr)
		{
			UART_RXC_CBK_Ptr = pUART_cfg_s->Resceive_Cbk_ptr;
		}
		else
		{

		}

		/* Pass pointer to DRE callback function */
		if(NULL != pUART_cfg_s->DataRegisterEmpty_Cbk_ptr)
		{
			UART_UDRE_CBK_Ptr = pUART_cfg_s->DataRegisterEmpty_Cbk_ptr;
		}
		else
		{

		}

		gu8_initState = INITIALIZED;
	}
	return E_OK;
}

/**
 * \brief UART_Deinit : Deinitialize the UART module
 *
 * \param void
 * \return ERROR_STATUS : Indication to the function execution
 *
 **/
ERROR_STATUS UART_Deinit(void)
{
	if(gu8_initState == INITIALIZED)
	{
		UCSRA = 0;
		UCSRB = 0;
		UCSRC_Buffer = 0x80;
		UCSRC = UCSRC_Buffer;
		UBRRL = 0;
		UBRRH = 0;
		gu8_initState = NOT_INITIALIZED;
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}

/**
 * @brief  Non blocking function to send one byte over UART
 *
 * @param u8_Data : The byte the user wants to send
 * @return ERROR_STATUS : Indication to the function execution
 **/
ERROR_STATUS UART_SendByte(uint8 u8_Data)
{
	if(gu8_initState == INITIALIZED)
	{
		UDR = u8_Data;
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}

/**
 * \brief  UART_ReceiveByte : Receives a certain byte
 *
 * \param pu8_ReceivedData : The sent byte will be stored in the passed pointer
 * \return ERROR_STATUS : Indication to the function execution
 *
 **/
ERROR_STATUS UART_ReceiveByte(uint8 *pu8_ReceivedData)
{
	if(gu8_initState == INITIALIZED)
	{
		/* Wait for data to be received */
		while (! (UCSRA & RXC));
		*pu8_ReceivedData = UDR;
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}

ISR(USART_TXC_vect)
{
	/* Call the callback function */
	UART_TXC_CBK_Ptr();
}

ISR(USART_RXC_vect)
{
	/* Call the callback function */
	UART_RXC_CBK_Ptr();
}

ISR(USART_UDRE_vect)
{
	/* Call the callback function */
	UART_UDRE_CBK_Ptr();
}
