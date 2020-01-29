/********************************************/
/* 		FileName: main.c					*/
/*		Version: 							*/
/*      Author: Ahmed Khalaf				*/
/********************************************/


//#include "Tasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"
#include "DIO.h"


MessageBufferHandle_t xMessageBuffer;

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
	for (;;)
	{
		/* Task code goes here. */
		DIO_Toggle(GPIOB, PIN5);
		xMessageBufferSend(xMessageBuffer, &u16_delVar, sizeof(uint16), (TickType_t) 0);
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
		xReceivedBytes = xMessageBufferReceive(xMessageBuffer, &u16_delVar, sizeof(uint16), (TickType_t) 5);
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

	xTaskCreate(vDIO_Init, "DIO", 100, (void *) 1, 1, &xDio_Init_Handle);
	xTaskCreate(vToggleLED1, "LED1", 100, (void *) 1, 1, &xToggleLED1_Handle);
	xTaskCreate(vToggleLED2, "LED2", 100, (void *) 1, 1, &xToggleLED2_Handle);

	xMessageBuffer = xMessageBufferCreate(1 * sizeof(uint8));

	/* Start Scheduler */
	vTaskStartScheduler();

	while (1)
	{

	}
	return 0;
}
