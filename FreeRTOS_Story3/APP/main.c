/********************************************/
/* 		FileName: main.c					*/
/*		Version: 							*/
/*      Author: Ahmed Osama					*/
/********************************************/


//#include "Tasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"
#include "DIO.h"


MessageBufferHandle_t xMessageBuffer;
uint8 gu8_buff;
uint8 gu8_Error_State;

void vDIO_Init(void * pvParameters)
{
	/* The parameter value is expected to be 1 as 1 is passed in the
	 pvParameters value in the call to xTaskCreate() below. */
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

	for (;;)
	{
		/* Task code goes here. */
		DIO_Cfg_s DIO_test =
		{ GPIOB, UPPER_NIBBLE, OUTPUT };
		DIO_init(&DIO_test);
		vTaskSuspend(NULL);
	}
}

void vToggleLED1(void * pvParameters)
{
	/* The parameter value is expected to be 1 as 1 is passed in the
	 pvParameters value in the call to xTaskCreate() below. */
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

	uint16 u16_delVar = 1000;
	uint8 u8_send = 7;
	for (;;)
	{
		/* Task code goes here. */
		DIO_Toggle(GPIOB, PIN5);
		xMessageBufferSend(xMessageBuffer, &u8_send, 1, 0);

		vTaskDelay(u16_delVar);
	}
}

void vToggleLED2(void * pvParameters)
{
	/* The parameter value is expected to be 1 as 1 is passed in the
	 pvParameters value in the call to xTaskCreate() below. */
	configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

	uint16 u16_delVar = 500;
	size_t xReceivedBytes;
	for (;;)
	{
		/* Task code goes here. */
		DIO_Toggle(GPIOB, PIN6);
		xReceivedBytes = xMessageBufferReceive(xMessageBuffer, &gu8_buff, 1, 5);
		if(xReceivedBytes > 0)
		{
			/* xMessageBuffer contains data */
			//if(u16_delVar == 1000)
			//{
				DIO_Toggle(GPIOB, PIN4);
			//}
		}
		else
		{
			/* Do nothing */
		}
		vTaskDelay(u16_delVar);
	}
}

int main(void)
{
	TaskHandle_t xToggleLED1_Handle = NULL;
	TaskHandle_t xToggleLED2_Handle = NULL;
	TaskHandle_t xDio_Init_Handle = NULL;

	xMessageBuffer = xMessageBufferCreate(1);
	if( xMessageBuffer == NULL )
	{
		/* There was not enough heap memory space available to create the
		message buffer. */
		gu8_Error_State = 0xFF;
	}
	else
	{
		/* The message buffer was created successfully and can now be used. */
		gu8_Error_State = 0;
	}

	xTaskCreate(vDIO_Init, "DIO", 100, (void *) 1, 1, &xDio_Init_Handle);
	xTaskCreate(vToggleLED1, "LED1", 100, (void *) 1, 1, &xToggleLED1_Handle);
	xTaskCreate(vToggleLED2, "LED2", 100, (void *) 1, 1, &xToggleLED2_Handle);

	/* Start Scheduler */
	vTaskStartScheduler();

	while (1)
	{

	}
	return 0;
}
