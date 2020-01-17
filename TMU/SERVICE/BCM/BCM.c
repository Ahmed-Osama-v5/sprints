/*
 * BCM.c
 *
 *  Created on: Jan 16, 2020
 *      Author: Ahmed Osama
 */

/*- INCLUDES ----------------------------------------------*/
#include "system_ErrorHandling.h"
#include "retval.h"
#include "uart.h"
#include "BCM.h"

/*- LOCAL MACROS ------------------------------------------*/

/*- LOCAL Data types --------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
/**
* @brief: BCM Initialization
* @param: void
* @return: sint8 status code with error code if one occurred
*/
static void BCM_OneByte_TxComplete_CBK(void);

/**
* @brief: BCM Initialization
* @param: void
* @return: sint8 status code with error code if one occurred
*/
static void BCM_OneByte_RxComplete_CBK(void);

/*- GLOBAL STATIC VARIABLES -------------------------------*/
static uint8 gu8_BCM_InitState = NOT_INITIALIZED;
static ptrBuffer gptr_TxBuffer = NULL;
static uint16 gu16_TxSize = 0;
static uint8 gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_IDLE;
static uint8 gu8_BCM_TxDispatcher_Trasmit_State = BCM_TX_DISPATCHER_ID_TX;
static uint8 gu8_BCM_TxBuffer_LockState = BCM_TX_BUFFER_UNLOCKED;
static uint8 gu8_BCM_SendFlag = BCM_SEND_NOT_TRIGGERED;
static uint8 gu8_BCM_TxBuffer_Index = 0;
static uint8 gu8_BCM_TxChecksum = 0;
static gptr_BCM_TransmitComplete_User_CBK_t gptr_BCM_TxComplete_User_CBK = NULL;
static volatile uint8 gu8_BCM_TxC_Flag = BCM_TXC_FLAG_NOT_TRIGGERED;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/**
* @brief: BCM Initialization
* @param: void
* @return: sint8 status code with error code if one occurred
*/
static void BCM_OneByte_TxComplete_CBK(void)
{
    /* Indicate a byte has been transmitted */
    gu8_BCM_TxC_Flag = BCM_TXC_FLAG_TRIGGERED;
}

/**
* @brief: BCM Initialization
* @param: void
* @return: sint8 status code with error code if one occurred
*/
static void BCM_OneByte_RxComplete_CBK(void)
{

}

/*- APIs IMPLEMENTATION -----------------------------------*/
/**
* @brief: BCM Initialization
* @param: gptr_BCM_TxComplete_CBK: pointer to user TxComplete callback
* @return: sint8 status code with error code if one occurred
*/
sint8 BCM_Init(gptr_BCM_TransmitComplete_User_CBK_t gptr_BCM_TxComplete_CBK)
{
  sint8 retval = BCM_BASE_ERROR + SUCCESS;

  /* Create instance of UART config struct */
  UART_cfg_s str_UART_Cfg_s = {0};

  /* Configure UART */
  str_UART_Cfg_s.u32_BaudRate = UART_BAUD_RATE;
  str_UART_Cfg_s.DataRegisterEmpty_Cbk_ptr = NULL;
  str_UART_Cfg_s.Transmit_Cbk_ptr = BCM_OneByte_TxComplete_CBK;
  str_UART_Cfg_s.Resceive_Cbk_ptr = BCM_OneByte_RxComplete_CBK;
  str_UART_Cfg_s.u8_DataSize = UART_8_BIT;
  str_UART_Cfg_s.u8_DesiredOperation = UART_TX_RX_CONFIG;
  str_UART_Cfg_s.u8_DoubleSpeed = UART_NO_DOUBLE_SPEED;
  str_UART_Cfg_s.u8_InterruptMode = UART_INTERRUPT;
  str_UART_Cfg_s.u8_ParityBit = UART_NO_PARITY;
  str_UART_Cfg_s.u8_StopBit = UART_ONE_STOP_BIT;

  /* TODO: Edit UART error handling */
  /* Initialize UART */
  if(UART_Init(&str_UART_Cfg_s) == E_NOK)
  {
      retval = BCM_BASE_ERROR + ERROR_RESOURCE_NOT_FOUND;
  }
  else
  {
      /* Reset global variable to the init state */
      gptr_TxBuffer = NULL;
      gu16_TxSize = 0;
      gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_IDLE;
      gu8_BCM_TxBuffer_Index = 0;
      gu8_BCM_TxChecksum = 0;
      gu8_BCM_TxC_Flag = BCM_TXC_FLAG_NOT_TRIGGERED;

      if(NULL == gptr_BCM_TxComplete_CBK)
      {
	  retval = BCM_BASE_ERROR + ERROR_NULL_POINTER;
      }
      else
      {
	  gptr_BCM_TxComplete_User_CBK = gptr_BCM_TxComplete_CBK;
      }

      /* Indicate BCM is initialized */
      gu8_BCM_InitState = INITIALIZED;
  }
  return retval;
}

/**
* @brief: takes pointer to the TX buffer and
* 	  its size, checks if size is <= MAX_BUFFER_SIZE,
* 	  and passes them to the dispatcher.
* @param: ptr_Buffer, u16_Size
* @return: sint8 status code with error code if one occurred
*/
sint8 BCM_Send(ptrBuffer ptr_Buffer, uint16 u16_Size)
{
  sint8 retval = BCM_BASE_ERROR + SUCCESS;

  /* Check if ptr_Buffer points to NULL */
  if(NULL == ptr_Buffer)
  {
      /* Error NULL pointer */
      retval = BCM_BASE_ERROR + ERROR_NULL_POINTER;
  }
  else
  {
      gptr_TxBuffer = ptr_Buffer;
      gu16_TxSize = u16_Size;
      gu8_BCM_SendFlag = BCM_SEND_TRIGGERED;
  }
  return retval;
}

/**
* @brief: takes pointer to the RX buffer
* 	  and passes it to the dispatcher.
* @param: ptr_Buffer
* @return: sint8 status code with error code if one occurred
*/
sint8 BCM_SetupReceive(ptrBuffer ptr_Buffer)
{
  sint8 retval = BCM_BASE_ERROR + SUCCESS;
  return retval;
}

/**
* @brief: Handles data reception.
* @param: void
* @return: sint8 status code with error code if one occurred
*/
sint8 BCM_RxDispatcher(void)
{
  sint8 retval = BCM_BASE_ERROR + SUCCESS;
  return retval;
}

/**
* @brief: Handles data transmission.
* @param: void
* @return: sint8 status code with error code if one occurred
*/
sint8 BCM_TxDispatcher(void)
{
  sint8 retval = BCM_BASE_ERROR + SUCCESS;
  /* BCM_TxDispatcher state machine */
  switch(gu8_BCM_TxDispatcher_State)
  {
    case (BCM_DISPATCHER_IDLE):
	if((gu8_BCM_SendFlag == BCM_SEND_TRIGGERED) && (gu8_BCM_TxBuffer_LockState == BCM_TX_BUFFER_UNLOCKED))
	{
	    /* Lock the TX buffer */
	    gu8_BCM_TxBuffer_LockState = BCM_TX_BUFFER_LOCKED;

	    /* Transmit BCM_ID */
	    UART_SendByte(BCM_ID);

	    /* Switch Tx state to sizeL */
	    gu8_BCM_TxDispatcher_Trasmit_State = BCM_TX_DISPATCHER_SIZEL_TX;

	    /* Switch state to BCM_DISPATCHER_TRANSMIT_BYTE */
	    gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE;
	}
	else
	{
	    /* Do nothing */
	}
	break;
    case (BCM_DISPATCHER_TRANSMIT_BYTE):
	if(gu8_BCM_TxC_Flag == BCM_TXC_FLAG_TRIGGERED)
	{
	    /* Reset BCM_TxC flag */
	    gu8_BCM_TxC_Flag = BCM_TXC_FLAG_NOT_TRIGGERED;

	    if(gu8_BCM_TxDispatcher_Trasmit_State == BCM_TX_DISPATCHER_SIZEL_TX)
	    {
		/* Transmit SizeL */
		UART_SendByte((uint8)gu16_TxSize);

		/* Switch BCM_TxDispatcher_State to BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE */
		gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE;
	    }
	    else if(gu8_BCM_TxDispatcher_Trasmit_State == BCM_TX_DISPATCHER_SIZEH_TX)
	    {
		/* Transmit SizeH */
		UART_SendByte((uint8)(gu16_TxSize >> 8));

		/* Switch BCM_TxDispatcher_State to BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE */
		gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE;
	    }
	    else if(gu8_BCM_TxDispatcher_Trasmit_State == BCM_TX_DISPATCHER_DATA_TX)
	    {
		/* Loop through TX buffer and transmit each byte */
		if(gu8_BCM_TxBuffer_Index < gu16_TxSize)
		{
		    /* Send the byte which index is pointing at */
		    UART_SendByte(gptr_TxBuffer[gu8_BCM_TxBuffer_Index]);
		    gu8_BCM_TxChecksum += gptr_TxBuffer[gu8_BCM_TxBuffer_Index++];

		    /* Switch BCM_TxDispatcher_State to BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE */
		    gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE;
		}
		else
		{
		    /* Send checksum */
		    UART_SendByte(gu8_BCM_TxChecksum);

		    /* Switch BCM_TxDispatcher_State to BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE */
		    gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE;
		}
	    }
	}
	else
	{
	    /* Do nothing */
	}
	break;
    case (BCM_DISPATCHER_TRANSMIT_BYTE_COMPLETE):
	if(gu8_BCM_TxDispatcher_Trasmit_State == BCM_TX_DISPATCHER_ID_TX)
    	{
    	    /* Switch gu8_BCM_TxDispatcher_Trasmit_State to BCM_TX_DISPATCHER_SIZEL_TX */
    	    gu8_BCM_TxDispatcher_Trasmit_State = BCM_TX_DISPATCHER_SIZEL_TX;

	    /* Switch BCM_TxDispatcher_State to BCM_DISPATCHER_TRANSMIT_BYTE */
	    gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE;
    	}
    	else if(gu8_BCM_TxDispatcher_Trasmit_State == BCM_TX_DISPATCHER_SIZEL_TX)
    	{
    	    /* Switch gu8_BCM_TxDispatcher_Trasmit_State to BCM_TX_DISPATCHER_SIZEH_TX */
    	    gu8_BCM_TxDispatcher_Trasmit_State = BCM_TX_DISPATCHER_SIZEH_TX;

	    /* Switch BCM_TxDispatcher_State to BCM_DISPATCHER_TRANSMIT_BYTE */
	    gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE;
    	}
    	else if(gu8_BCM_TxDispatcher_Trasmit_State == BCM_TX_DISPATCHER_SIZEH_TX)
    	{
    	    /* Switch gu8_BCM_TxDispatcher_Trasmit_State to BCM_TX_DISPATCHER_DATA_TX */
    	    gu8_BCM_TxDispatcher_Trasmit_State = BCM_TX_DISPATCHER_DATA_TX;

	    /* Switch BCM_TxDispatcher_State to BCM_DISPATCHER_TRANSMIT_BYTE */
	    gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_TRANSMIT_BYTE;
    	}
    	else if(gu8_BCM_TxDispatcher_Trasmit_State == BCM_TX_DISPATCHER_DATA_TX)
    	{
    	    /* Loop through TX buffer and transmit each byte */
    	    if(gu8_BCM_TxBuffer_Index < gu16_TxSize)
    	    {
    		/* Increment index */
    		gu8_BCM_TxBuffer_Index++;
    	    }
    	    else
    	    {
    		/* Switch gu8_BCM_TxDispatcher_Trasmit_State to BCM_TX_DISPATCHER_ID_TX */
    		gu8_BCM_TxDispatcher_Trasmit_State = BCM_TX_DISPATCHER_ID_TX;

    		/* Execute TransmitComplete user callback */
    		gptr_BCM_TxComplete_User_CBK();

    		/* Unlock the Tx buffer */
    		gu8_BCM_TxBuffer_LockState = BCM_TX_BUFFER_UNLOCKED;

    		/* Indicate Send has finished */
    		gu8_BCM_SendFlag = BCM_SEND_NOT_TRIGGERED;

		/* Switch BCM_TxDispatcher_State to BCM_DISPATCHER_IDLE */
		gu8_BCM_TxDispatcher_State = BCM_DISPATCHER_IDLE;
    	    }
    	}
    	else
	{
    	    /* TODO: Handle this error */
	}
	break;
    default:
        /* TODO: Add retval.h for BCM module and handle this error */
        break;
  }
  return retval;
}

/**
* @brief: Indicates user has finished processing data
* 	  in the Rx_Buffer.
* @param: void
* @return: sint8 status code with error code if one occurred
*/
sint8 BCM_RxUnlock(void)
{
  sint8 retval = BCM_BASE_ERROR + SUCCESS;
  return retval;
}
